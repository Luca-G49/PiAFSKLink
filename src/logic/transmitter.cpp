#include "transmitter.h"
#include "audio_device.h"
#include "app_config.h"
#include <vector>
#include <cmath>
#include <iostream>

// Generate sine wave samples for a specific tone
std::vector<short> generate_tone_samples(double frequency, double volume, int duration_us, unsigned int sample_rate) {
    const double two_pi = 2.0 * M_PI;
    int num_samples = sample_rate * (duration_us / 1e6);
    std::vector<short> samples(num_samples);

    for (int t = 0; t < num_samples; ++t) {
        samples[t] = static_cast<short>(volume * 32767 * sin(two_pi * frequency * t / sample_rate));
    }
    return samples;
}

void transmit(const std::string& input_bits) {
    Config::AppConfig& config = Config::get();
    AudioDevice audio;

    // Initialize the audio device
    if (!audio.init(config.sample_rate, false)) {
        std::cerr << "Failed to initialize audio device!" << std::endl;
        return;
    }

    // Pre-generate tone samples for start and end tone
    std::vector<short> start_tone_samples = generate_tone_samples(config.tone_start, config.volume, config.tone_duration, config.sample_rate);
    std::vector<short> end_tone_samples = generate_tone_samples(config.tone_end, config.volume, config.tone_duration, config.sample_rate);

    // Pre-generate tone samples for bit 0 and bit 1
    std::vector<short> tone_0_samples = generate_tone_samples(config.tone_0, config.volume, config.tone_duration, config.sample_rate);
    std::vector<short> tone_1_samples = generate_tone_samples(config.tone_1, config.volume, config.tone_duration, config.sample_rate);

    // Create the buffer for the entire transmission
    std::vector<short> buffer;

    // Add start tone to buffer
    buffer.insert(buffer.end(), start_tone_samples.begin(), start_tone_samples.end());

    // Construct the buffer by appending pre-generated tone samples
    for (char bit : input_bits) {
        if (bit == '0') {
            buffer.insert(buffer.end(), tone_0_samples.begin(), tone_0_samples.end());
        } else if (bit == '1') {
            buffer.insert(buffer.end(), tone_1_samples.begin(), tone_1_samples.end());
        }
    }

    // Add end tone to buffer
    buffer.insert(buffer.end(), end_tone_samples.begin(), end_tone_samples.end());

    // Play the entire buffer
    if (!audio.playback(buffer)) {
        std::cerr << "Error during playback!" << std::endl;
    }

    // Clean up the audio device
    audio.cleanup();
}
