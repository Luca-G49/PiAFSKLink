// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "app_config.h"
#include "receiver.h"
#include "audio_device.h"
#include "serialization.h"
#include "fft.h"
#include "logger.h"
#include "get_time.h"
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
bool detect_tone(const std::vector<short> &samples, unsigned int sample_rate, double target_frequency, double tolerance = 10) {
    // Convert samples from short to double
    std::vector<double> double_samples(samples.begin(), samples.end());

    // Get the magnitudes using compute_fft
    std::vector<double> magnitudes = compute_fft(double_samples, sample_rate);

    // Find the dominant frequency
    double dominant_frequency = find_dominant_frequency(magnitudes, sample_rate);

    // Compare with target frequency
    return std::abs(dominant_frequency - target_frequency) < tolerance;
}

// Simulated receiver thread
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

void receiver_thread(std::atomic<bool>& running) {
    AudioDevice audio;

    // Initialize the audio device for capture
    if (!audio.init(config.sample_rate, true)) {
        Logger::getLogger()->error("Failed to initialize audio device for capture!");
        return;
    }

    std::vector<short> captured_samples;
    size_t samples_per_bit = config.sample_rate * (config.tone_duration / 1e6);

    while (running.load()) {
        // Detect start tone
        //std::cout << "Waiting for start tone..." << std::endl;

        // Capture samples and check for the start tone
        if (!audio.capture(captured_samples, samples_per_bit)) {
            Logger::getLogger()->error("Audio capture failed!");
            continue; // Go back to looking for the start tone
        }

        // Detect the start tone
        if (detect_tone(captured_samples, config.sample_rate, config.tone_start)) {
            Logger::getLogger()->info("Start tone detected! Decoding message...");

            auto start_time = std::chrono::steady_clock::now();
            auto timeout_duration = std::chrono::seconds(config.tone_end_deadline); // Timeout for the current message
            std::string binary_sequence;

            // Start decoding the bits
            while (running.load()) {
                if (!audio.capture(captured_samples, samples_per_bit)) {
                    Logger::getLogger()->error("Failed to capture samples!");
                    break; // Exit decoding and look for a new message
                }

                // Check if the samples are sufficient
                if (captured_samples.size() < samples_per_bit) {
                    Logger::getLogger()->error("Insufficient captured samples!");
                    break; // Exit decoding and look for a new message
                }

                // Detect bit tones
                if (detect_tone(captured_samples, config.sample_rate, config.tone_0)) {
                    binary_sequence += "0";
                } else if (detect_tone(captured_samples, config.sample_rate, config.tone_1)) {
                    binary_sequence += "1";
                }

                // Detect the end tone
                if (detect_tone(captured_samples, config.sample_rate, config.tone_end)) {
                    Logger::getLogger()->info("End tone detected! Transmission completed.");
                    
                    // Insert the message into the buffer
                    {
                        std::lock_guard<std::mutex> lock(bufferMutex);
                        receivedMessages.push_back("[" + getCurrentTime() + "] : " + bitsToString(binary_sequence));
                    }
                    
                    break; // Message received, go back to looking for a new message
                }

                // Check timeout
                auto elapsed_time = std::chrono::steady_clock::now() - start_time;
                if (elapsed_time > timeout_duration) {
                    Logger::getLogger()->error("Timeout! Stopping reception of current message.");
                    break; // Exit decoding and look for a new message
                }
            }
        }
    }

    // Clean up the audio device
    audio.cleanup();

    //std::cout << "Receiver thread terminated." << std::endl;
}
