// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "audio_device.h"
#include "logger.h"
#include <iostream>

// Constructor
AudioDevice::AudioDevice() : handle(nullptr), sample_rate(0), is_capture(false) {}

// Destructor
AudioDevice::~AudioDevice()
{
    cleanup();
}

// Initializes the audio device for capture or playback.
bool AudioDevice::init(unsigned int sample_rate, bool is_capture)
{
    this->sample_rate = sample_rate;
    this->is_capture = is_capture;

    const char *device = "default";
    auto mode = is_capture ? SND_PCM_STREAM_CAPTURE : SND_PCM_STREAM_PLAYBACK;

    // Open the ALSA device
    if (snd_pcm_open(&handle, device, mode, 0) < 0)
    {
        Logger::getLogger()->error("Unable to open audio device.");
        return false;
    }

    // Configure the device
    return configure_device();
}

// Configures the audio device's hardware parameters.
bool AudioDevice::configure_device()
{
    snd_pcm_hw_params_t *params;
    snd_pcm_hw_params_alloca(&params);

    // Set the device parameters
    if (snd_pcm_hw_params_any(handle, params) < 0)
    {
        Logger::getLogger()->error("Unable to configure hardware parameters.");
        return false;
    }

    // Set access type
    if (snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
    {
        Logger::getLogger()->error("Unable to set interleaved access.");
        return false;
    }

    // Set the audio format
    if (snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE) < 0)
    {
        Logger::getLogger()->error("Unable to set audio format.");
        return false;
    }

    // Set the number of channels (Mono)
    if (snd_pcm_hw_params_set_channels(handle, params, 1) < 0)
    {
        Logger::getLogger()->error("Unable to set channel count.");
        return false;
    }

    // Set the sample rate
    if (snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, nullptr) < 0)
    {
        Logger::getLogger()->error("Unable to set sample rate..");
        return false;
    }

    // Apply the hardware parameters
    if (snd_pcm_hw_params(handle, params) < 0)
    {
        Logger::getLogger()->error("Unable to apply hardware parameters.");
        return false;
    }

    return true;
}

// Plays back audio samples to the device.
bool AudioDevice::playback(const std::vector<short> &samples)
{
    int frames = samples.size();
    const short *data = samples.data();

    // Write audio samples to the device
    while (frames > 0)
    {
        int written = snd_pcm_writei(handle, data, frames);
        if (written == -EPIPE)
        {
            Logger::getLogger()->error("Buffer underrun occurred. Recovering...");
            snd_pcm_prepare(handle);
        }
        else if (written < 0)
        {
            std::string message = "Error during playback: ";
            message.append(snd_strerror(written));
            Logger::getLogger()->error(message);

            return false;
        }
        else
        {
            frames -= written;
            data += written;
        }
    }

    return true;
}

// Captures audio samples from the device.
bool AudioDevice::capture(std::vector<short> &buffer, size_t frames)
{
    buffer.resize(frames);
    int read = snd_pcm_readi(handle, buffer.data(), frames);
    if (read < 0)
    {
        std::string message = "Error during capture: ";
        message.append(snd_strerror(read));
        Logger::getLogger()->error(message);

        return false;
    }
    return true;
}

// Cleans up resources and closes the audio device.
void AudioDevice::cleanup()
{
    if (handle)
    {
        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        handle = nullptr;
    }
}

// Drops the current audio device connection.
void AudioDevice::drop()
{
    if (handle)
    {
        snd_pcm_drop(handle);
        handle = nullptr;
    }
}
