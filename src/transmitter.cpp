#include "transmitter.h"
#include "constants.h"
#include <cmath>
#include <iostream>

// Generate a sine wave tone of the specified frequency, volume, and duration
void generate_tone(double frequency, snd_pcm_t* handle, double volume, int duration) {
    const int SAMPLE_RATE = 44100; // Audio sample rate
    const int NUM_SAMPLES = SAMPLE_RATE * (duration / 1000000.0); // Number of samples
    short* buffer = new short[NUM_SAMPLES];
    const double two_pi = 2.0 * M_PI;

    // Generate sine wave samples
    for (int t = 0; t < NUM_SAMPLES; t++) {
        buffer[t] = static_cast<short>(volume * 32767 * sin(two_pi * frequency * t / SAMPLE_RATE));
    }

    // Write samples to the audio device
    int frames = NUM_SAMPLES / 2; // Two bytes per frame
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
        double frequency = (bit == 0) ? TONE_0 : TONE_1;
        generate_tone(frequency, handle, VOLUME, TONE_DURATION);
    }
}
