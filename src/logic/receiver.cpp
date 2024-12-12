// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "app_config.h"
#include "receiver.h"
#include "audio_device.h"
#include "serialization.h"
#include "fft.h"
#include "logger.h"
#include "get_time.h"
#include "encryption.h"
#include <fftw3.h>
#include <vector>
#include <cmath>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <atomic>

Config::AppConfig &config = Config::get();

std::deque<std::string> receivedMessages;
std::mutex bufferMutex;

// Function to detect tone
bool detect_tone(const std::vector<short> &samples, unsigned int sample_rate, double target_frequency, double tolerance = 10)
{
    // Convert samples from short to double
    std::vector<double> double_samples(samples.begin(), samples.end());

    // Get the magnitudes using compute_fft
    std::vector<double> magnitudes = compute_fft(double_samples, sample_rate);

    // Find the dominant frequency
    double dominant_frequency = find_dominant_frequency(magnitudes, sample_rate);

    // Compare with target frequency
    return std::abs(dominant_frequency - target_frequency) < tolerance;
}

// Clear received messages buffer
void clear_received_messages()
{
    std::lock_guard<std::mutex> lock(bufferMutex);
    receivedMessages.clear();
}

// Simulated receiver thread function
void receiver_thread_sim(std::atomic<bool> &running)
{
    int counter = 0; // Simulate receive counter
    while (running)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate receiver delay
        std::lock_guard<std::mutex> lock(bufferMutex);
        receivedMessages.push_back("Received message #" + std::to_string(++counter)); // Simulate receiver
    }
}

// Receiver thread function
void receiver_thread(std::atomic<bool> &running)
{
    AudioDevice audio;
    auto start_time = std::chrono::steady_clock::now();
    auto timeout_duration = std::chrono::seconds(config.tone_end_deadline); // Timeout for the current message
    std::string binary_sequence;
    bool start_detected = false;
    bool separator_detected = false;

    std::vector<short> captured_samples;
    size_t samples_per_bit = config.sample_rate * (config.tone_bit_duration / 1e6);
    size_t samples_to_capture = samples_per_bit / 2;

    // Initialize the audio device for capture
    if (!audio.init(config.sample_rate, true))
    {
        Logger::getLogger()->error("Failed to initialize audio device for capture! Receiver thread will terminate.");
        return;
    }

    while (running.load())
    {
        // Capture samples and check for the start tone
        if (!audio.capture(captured_samples, samples_to_capture))
        {
            Logger::getLogger()->error("Audio capture failed! Receiver thread will terminate.");
            return;
        }

        if (!start_detected)
        {
            // Detect the start tone
            if (detect_tone(captured_samples, config.sample_rate, config.tone_start))
            {
                Logger::getLogger()->info("Start tone detected! Decoding message...");
                start_detected = true;
                start_time = std::chrono::steady_clock::now();
                binary_sequence.clear(); // Clear previous binary sequence
            }
        }
        else
        {
            if (!separator_detected)
            {
                // Detect the separator tone
                if (detect_tone(captured_samples, config.sample_rate, config.tone_separator))
                {
                    separator_detected = true;
                }
            }
            else
            {
                // Detect bit tones
                if (detect_tone(captured_samples, config.sample_rate, config.tone_0))
                {
                    separator_detected = false;
                    binary_sequence += "0";
                }
                else if (detect_tone(captured_samples, config.sample_rate, config.tone_1))
                {
                    separator_detected = false;
                    binary_sequence += "1";
                }
                // Detect the end tone
                else if (detect_tone(captured_samples, config.sample_rate, config.tone_end))
                {
                    separator_detected = false;
                    Logger::getLogger()->info("End tone detected! Transmission completed. " + binary_sequence);

                    // Insert the message into the buffer
                    {
                        std::lock_guard<std::mutex> lock(bufferMutex);

                        // Decrypt the message if encryption is enabled
                        if (config.enable_encryption)
                        {
                            std::string decrypted_message;

                            // Decrypt the message
                            if (decrypt_message(bitsToString(binary_sequence), config.encryption_key, decrypted_message) != 0)
                            {
                                Logger::getLogger()->error("Failed to decrypt the message.");
                                break;
                            }

                            Logger::getLogger()->info("Message successfully decrypted.");

                            // Add decrypted message to received messages buffer
                            receivedMessages.push_back("\033[1;32m[" + getCurrentTime() + "] \033[0m: " + decrypted_message);
                        }
                        else
                        {
                            // Add message to received messages buffer
                            receivedMessages.push_back("\033[1;32m[" + getCurrentTime() + "] \033[0m: " + bitsToString(binary_sequence));
                        }
                    }

                    start_detected = false; // Message received, go back to looking for a new message
                }
            }
            // Check timeout
            /*auto elapsed_time = std::chrono::steady_clock::now() - start_time;
            if (elapsed_time > timeout_duration)
            {
                Logger::getLogger()->error("Timeout! Stopping reception of current message.");
                start_detected = false; // Exit decoding and look for a new message
            }*/
        }
    }

    // Drop and clean up the audio device
    audio.drop();
    audio.cleanup();
}