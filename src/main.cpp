#include <iostream>
#include <cmath>
#include <vector>
#include <alsa/asoundlib.h>

const int SAMPLE_RATE = 44100;  // Sample rate (Hz)
const double VOLUME = 0.5;      // Volume (0.0 - 1.0)
const int DURATION = 100000;    // Duration of each tone in microseconds
const double TONE_0 = 2200.0;   // Tone in Hz for bit 0
const double TONE_1 = 3600.0;   // Tone in Hz for bit 1

void generate_tone(double frequency, snd_pcm_t* handle) {
    const int NUM_SAMPLES = SAMPLE_RATE * (DURATION / 1000000.0);
    short *buffer = new short[NUM_SAMPLES];
    const double two_pi = 2.0 * M_PI;

    // Generate the sine wave for the tone
    for (int t = 0; t < NUM_SAMPLES; t++) {
        buffer[t] = static_cast<short>(VOLUME * 32767 * sin(two_pi * frequency * t / SAMPLE_RATE));
    }

    // Write the buffer to the audio device
    int frames = NUM_SAMPLES / 2;  // Two bytes per sample
    int res = snd_pcm_writei(handle, buffer, frames);

    if (res == -EPIPE) {
        std::cerr << "Error: Buffer underrun!" << std::endl;
    } else if (res < 0) {
        std::cerr << "Error writing to the audio device: " << snd_strerror(res) << std::endl;
    }

    // Free the buffer memory
    delete[] buffer;
}

void play_bit_sequence(const std::vector<int>& bit_sequence, snd_pcm_t* handle) {
    for (int bit : bit_sequence) {
        // Choose frequency based on bit value
        double frequency = (bit == 0) ? TONE_0 : TONE_1;
        generate_tone(frequency, handle);
    }
}

int main() {
    const char* device = "default";  // ALSA audio device
    snd_pcm_t* handle;
    snd_pcm_hw_params_t* params;

    // Open the audio device
    int err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        std::cerr << "Error: Unable to open audio device '" << device << "'. Reason: " << snd_strerror(err) << std::endl;
        return 1;
    }

    std::cout << "Audio device opened successfully!" << std::endl;

    // Allocate and configure hardware parameters
    snd_pcm_hw_params_alloca(&params);
    err = snd_pcm_hw_params_any(handle, params);
    if (err < 0) {
        std::cerr << "Error: Unable to get device parameters. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0) {
        std::cerr << "Error: Unable to set interleaved access. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    if (err < 0) {
        std::cerr << "Error: Unable to set audio format. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    err = snd_pcm_hw_params_set_channels(handle, params, 1);  // Mono
    if (err < 0) {
        std::cerr << "Error: Unable to set the number of channels. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    unsigned int rate = SAMPLE_RATE;
    err = snd_pcm_hw_params_set_rate_near(handle, params, &rate, nullptr);
    if (err < 0) {
        std::cerr << "Error: Unable to set sample rate. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    err = snd_pcm_hw_params(handle, params);
    if (err < 0) {
        std::cerr << "Error: Failed to configure hardware parameters. Reason: " << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return 1;
    }

    // Input the bit sequence
    std::vector<int> bit_sequence;
    std::string input_bits;
    std::cout << "Enter a bit sequence (e.g., 101010): ";
    std::cin >> input_bits;

    for (char bit : input_bits) {
        if (bit == '0' || bit == '1') {
            bit_sequence.push_back(bit - '0');  // Convert char to int
        }
    }

    // Play the sequence of tones based on the bits
    play_bit_sequence(bit_sequence, handle);

    // Clean up
    snd_pcm_drain(handle);
    snd_pcm_close(handle);
    std::cout << "Bit sequence played successfully!" << std::endl;

    return 0;
}
