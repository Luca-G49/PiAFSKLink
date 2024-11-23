#include "app_config.h"
#include "receiver.h"
#include "audio_device.h"
#include "serialization.h"
#include "fft.h"
#include <fftw3.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <atomic>

Config::AppConfig &config = Config::get();

std::deque<std::string> receivedMessages;
std::mutex bufferMutex;

// Function to detect the start tone (used for synchronization)
bool detect_start_tone(const std::vector<short> &samples, unsigned int sample_rate)
{
    size_t samples_per_tone = sample_rate * (config.start_tone_duration / 1e6);
    std::vector<short> segment(samples.begin(), samples.begin() + samples_per_tone);

    // Convert segment from short to double
    std::vector<double> double_segment(segment.begin(), segment.end());

    // Get the magnitudes using compute_fft
    std::vector<double> magnitudes = compute_fft(double_segment, sample_rate);

    double dominant_frequency = find_dominant_frequency(magnitudes, sample_rate);
    return std::abs(dominant_frequency - config.start_tone) < 10;
}

// Function to detect the end tone (used to terminate the reception)
bool detect_end_tone(const std::vector<short> &samples, unsigned int sample_rate)
{
    size_t samples_per_tone = sample_rate * (config.end_tone_duration / 1e6);
    std::vector<short> segment(samples.begin(), samples.begin() + samples_per_tone);

    // Convert segment from short to double
    std::vector<double> double_segment(segment.begin(), segment.end());

    // Get the magnitudes using compute_fft
    std::vector<double> magnitudes = compute_fft(double_segment, sample_rate);

    double dominant_frequency = find_dominant_frequency(magnitudes, sample_rate);
    return std::abs(dominant_frequency - config.end_tone) < 10;
}

// Function to detect the bit tone (for both 1 and 0)
bool detect_bit_tone(const std::vector<short> &samples, unsigned int sample_rate)
{
    // Convert samples from short to double
    std::vector<double> double_samples(samples.begin(), samples.end());

    // Get the magnitudes using compute_fft
    std::vector<double> magnitudes = compute_fft(double_samples, sample_rate);

    double dominant_frequency = find_dominant_frequency(magnitudes, sample_rate);
    return std::abs(dominant_frequency - config.tone_1) < 10;
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
        std::cerr << "Failed to initialize audio device for capture!" << std::endl;
        return;
    }

    std::vector<short> captured_samples;
    size_t samples_per_bit = config.sample_rate * (config.tone_duration / 1e6);

    while (running.load()) {
        // Detect start tone
        //std::cout << "Waiting for start tone..." << std::endl;

        // Capture samples and check for the start tone
        if (!audio.capture(captured_samples, samples_per_bit)) {
            std::cerr << "Audio capture failed!" << std::endl;
            continue; // Go back to looking for the start tone
        }

        if (detect_start_tone(captured_samples, config.sample_rate)) {
            //std::cout << "Start tone detected! Decoding message..." << std::endl;

            captured_samples.clear(); // Reset the samples
            //audio.capture(captured_samples, samples_per_bit); // Capture a synchronized initial block

            auto start_time = std::chrono::steady_clock::now();
            auto timeout_duration = std::chrono::seconds(10); // Timeout for the current message
            std::string binary_sequence;

            // Start decoding the bits
            while (running.load()) {
                if (!audio.capture(captured_samples, samples_per_bit)) {
                    std::cerr << "Failed to capture samples!" << std::endl;
                    break; // Exit decoding and look for a new message
                }

                // Check if the samples are sufficient
                if (captured_samples.size() < samples_per_bit) {
                    std::cerr << "Insufficient captured samples!" << std::endl;
                    break; // Exit decoding and look for a new message
                }

                // Detect the end tone
                if (detect_end_tone(captured_samples, config.sample_rate)) {
                    //std::cout << "End tone detected! Transmission completed." << std::endl;
                    
                    // Insert the message into the buffer
                    {
                        std::lock_guard<std::mutex> lock(bufferMutex);
                        
                        //std::cout << binary_sequence << std::endl;
                        //std::cout << bitsToString(binary_sequence) << std::endl;

                        receivedMessages.push_back(bitsToString(binary_sequence));
                    }
                    
                    break; // Message received, go back to looking for a new message
                }

                // Decode the bit
                if (detect_bit_tone(captured_samples, config.sample_rate)) {
                    binary_sequence += "1";
                } else {
                    binary_sequence += "0";
                }

                // Check timeout
                auto elapsed_time = std::chrono::steady_clock::now() - start_time;
                if (elapsed_time > timeout_duration) {
                    std::cerr << "Timeout! Stopping reception of current message." << std::endl;
                    break; // Exit decoding and look for a new message
                }
            }
        }
    }

    //std::cout << "Receiver thread terminated." << std::endl;
}
