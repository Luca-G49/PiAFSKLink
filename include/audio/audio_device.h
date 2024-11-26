// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <vector>
#include <alsa/asoundlib.h>

// AudioDevice class handles initialization, playback, and capture for an ALSA device
class AudioDevice {
public:
    AudioDevice();
    ~AudioDevice();

    // Initialize the audio device for playback or capture
    bool init(unsigned int sample_rate, bool is_capture = false);

    // Play a buffer of audio samples
    bool playback(const std::vector<short>& samples);

    // Capture audio samples from the device
    bool capture(std::vector<short>& buffer, size_t frames);

    // Clean up and close the audio device
    void cleanup();

    // Drop audio device
    void drop();

private:
    snd_pcm_t* handle;        // ALSA device handle
    unsigned int sample_rate; // Sampling rate in Hz
    bool is_capture;          // Indicates if the device is used for capture

    // Configure ALSA hardware parameters
    bool configure_device();
};

#endif // AUDIO_DEVICE_H
