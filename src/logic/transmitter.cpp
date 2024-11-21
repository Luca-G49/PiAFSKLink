#include "transmitter.h"
#include "app_config.h"
#include "audio_device.h"
#include <cmath>
#include <iostream>

// Get App configuration
Config::AppConfig& config = Config::get();

// Generate a sine wave tone of the specified frequency, volume, and duration
void generate_tone(double frequency, snd_pcm_t* handle, double volume, int duration) {

    const int NUM_SAMPLES = config.sample_rate * (duration / 1000000.0); // Number of samples
    short* buffer = new short[NUM_SAMPLES];
    const double two_pi = 2.0 * M_PI;

    // Generate sine wave samples
    for (int t = 0; t < NUM_SAMPLES; t++) {
        buffer[t] = static_cast<short>(volume * 32767 * sin(two_pi * frequency * t / config.sample_rate));
    }

    // Write samples to the audio device
    //Stereo: 4 bytes per frame (2 sample, 1 sx + 1 dx))
    //Mono: 2 bytes per frame (1 sample))
    int frames = NUM_SAMPLES; // (Stereo => NUM_SAMPLES / 2)
    int res = snd_pcm_writei(handle, buffer, frames);
    if (res == -EPIPE) {
        std::cerr << "Buffer underrun occurred!" << std::endl;
    }

    delete[] buffer;
}

// Play a sequence of bits as tones
void play_bit_sequence(const std::vector<int>& bit_sequence, snd_pcm_t* handle) {
    for (int bit : bit_sequence) {
        // Determine the frequency based on the bit value
        double frequency = (bit == 0) ? config.tone_0 : config.tone_1;
        generate_tone(frequency, handle, config.volume, config.tone_duration);
    }
}

void transmit(std::string input_bits) {

    snd_pcm_t *handle;

    // Initialize the audio device for playback
    int result = initialize_audio_device(handle, config.sample_rate);
    if (result < 0)
    {
        std::cerr << "Audio initialization failed with error code: " << result << std::endl;
    }

    // Bit sequence
    std::vector<int> bit_sequence;

    // Convert input string to a bit sequence
    for (char bit : input_bits)
    {
        if (bit == '0' || bit == '1')
        {
            bit_sequence.push_back(bit - '0'); // Convert char to int
        }
    }
    
    play_bit_sequence(bit_sequence, handle);

    // Clean up the audio device
    cleanup_audio_device(handle);

}
