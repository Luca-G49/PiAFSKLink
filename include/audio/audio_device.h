// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <vector>
#include <alsa/asoundlib.h>

// AudioDevice class handles initialization, playback, and capture for an ALSA device
class AudioDevice
{
public:
    // Constructor
    AudioDevice();

    // Destructor
    ~AudioDevice();

    /**
     * Initializes the audio device for capture or playback.
     *
     * This function opens the ALSA audio device with the specified parameters
     * and configures the hardware settings for either capturing or playing audio.
     *
     * @param sample_rate The sample rate (in Hz) to be used for audio capture or playback.
     * @param is_capture A boolean flag indicating whether the device should be
     *        initialized for capture (true) or playback (false).
     * @return True if the initialization was successful, false otherwise.
     */
    bool init(unsigned int sample_rate, bool is_capture = false);

    /**
     * Plays back audio samples to the device.
     *
     * This function writes the provided audio samples to the device in chunks,
     * handling buffer underruns and errors during the playback process.
     *
     * @param samples A vector containing the audio samples to be played.
     * @return True if the playback was successful, false otherwise.
     */
    bool playback(const std::vector<short> &samples);

    /**
     * Captures audio samples from the device.
     *
     * This function reads audio samples from the device into the provided buffer.
     * It handles potential errors during the capture process and ensures
     * the buffer is filled with the specified number of frames.
     *
     * @param buffer A vector to hold the captured audio samples.
     * @param frames The number of frames to capture.
     * @return True if the capture was successful, false otherwise.
     */
    bool capture(std::vector<short> &buffer, size_t frames);

    /**
     * Cleans up resources and closes the audio device.
     *
     * This function releases any resources associated with the audio device
     * and ensures that the device is properly closed. It is called when the
     * AudioDevice object is destroyed or no longer needed.
     */
    void cleanup();

    /**
     * Drops the current audio device connection.
     *
     * This function drops the current ALSA connection, which can be useful
     * for handling errors or when the connection is no longer needed.
     * After calling this function, the handle is set to nullptr.
     */
    void drop();

private:
    snd_pcm_t *handle;        // ALSA device handle
    unsigned int sample_rate; // Sampling rate in Hz
    bool is_capture;          // Indicates if the device is used for capture

    /**
     * Configures the audio device's hardware parameters.
     *
     * This function sets the access type, format, channels, and sample rate
     * of the audio device based on the configuration. It ensures the ALSA
     * hardware parameters are correctly applied.
     *
     * @return True if the device configuration was successful, false otherwise.
     */
    bool configure_device();
};

#endif // AUDIO_DEVICE_H
