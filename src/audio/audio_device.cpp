#include "audio_device.h"
#include <iostream>

AudioDevice::AudioDevice() : handle(nullptr), sample_rate(0), is_capture(false) {}

AudioDevice::~AudioDevice() {
    cleanup();
}

bool AudioDevice::init(unsigned int sample_rate, bool is_capture) {
    this->sample_rate = sample_rate;
    this->is_capture = is_capture;

    const char* device = "default";
    auto mode = is_capture ? SND_PCM_STREAM_CAPTURE : SND_PCM_STREAM_PLAYBACK;

    // Open the ALSA device
    if (snd_pcm_open(&handle, device, mode, 0) < 0) {
        std::cerr << "Error: Unable to open audio device." << std::endl;
        return false;
    }

    // Configure the device
    return configure_device();
}

bool AudioDevice::configure_device() {
    snd_pcm_hw_params_t* params;
    snd_pcm_hw_params_alloca(&params);

    // Set the device parameters
    if (snd_pcm_hw_params_any(handle, params) < 0) {
        std::cerr << "Error: Unable to configure hardware parameters." << std::endl;
        return false;
    }

    // Set access type
    if (snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0) {
        std::cerr << "Error: Unable to set interleaved access." << std::endl;
        return false;
    }

    // Set the audio format
    if (snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE) < 0) {
        std::cerr << "Error: Unable to set audio format." << std::endl;
        return false;
    }

    // Set the number of channels (Mono)
    if (snd_pcm_hw_params_set_channels(handle, params, 1) < 0) {
        std::cerr << "Error: Unable to set channel count." << std::endl;
        return false;
    }

    // Set the sample rate
    if (snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, nullptr) < 0) {
        std::cerr << "Error: Unable to set sample rate." << std::endl;
        return false;
    }

    // Apply the hardware parameters
    if (snd_pcm_hw_params(handle, params) < 0) {
        std::cerr << "Error: Unable to apply hardware parameters." << std::endl;
        return false;
    }

    return true;
}

// Playback function
bool AudioDevice::playback(const std::vector<short>& samples) {
    int frames = samples.size();
    const short* data = samples.data();

    // Write audio samples to the device
    while (frames > 0) {
        int written = snd_pcm_writei(handle, data, frames);
        if (written == -EPIPE) {
            std::cerr << "Buffer underrun occurred. Recovering..." << std::endl;
            snd_pcm_prepare(handle);
        } else if (written < 0) {
            std::cerr << "Error during playback: " << snd_strerror(written) << std::endl;
            return false;
        } else {
            frames -= written;
            data += written;
        }
    }

    return true;
}

// Capture function
bool AudioDevice::capture(std::vector<short>& buffer, size_t frames) {
    buffer.resize(frames);
    int read = snd_pcm_readi(handle, buffer.data(), frames);
    if (read < 0) {
        std::cerr << "Error during capture: " << snd_strerror(read) << std::endl;
        return false;
    }
    return true;
}

// Cleanup funtion
void AudioDevice::cleanup() {
    if (handle) {
        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        handle = nullptr;
    }
}
