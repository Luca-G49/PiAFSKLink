#include "audio_device.h"
#include <iostream>

int initialize_audio_device(snd_pcm_t*& handle, unsigned int sample_rate) {
    const char* device = "default"; // Default audio device
    snd_pcm_hw_params_t* params;

    // Open the ALSA device for playback
    int err = snd_pcm_open(&handle, device, SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0) {
        std::cerr << "Error: Unable to open audio device '" << device 
                  << "'. Reason: " << snd_strerror(err) << std::endl;
        return -1; // Device open error
    }
    std::cout << "Audio device opened successfully!" << std::endl;

    // Allocate and initialize hardware parameters
    snd_pcm_hw_params_alloca(&params);
    err = snd_pcm_hw_params_any(handle, params);
    if (err < 0) {
        std::cerr << "Error: Unable to get device parameters. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -2; // Hardware parameter allocation error
    }

    // Set access type
    err = snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0) {
        std::cerr << "Error: Unable to set interleaved access. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -3; // Access type setup error
    }

    // Set the audio format
    err = snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);
    if (err < 0) {
        std::cerr << "Error: Unable to set audio format. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -4; // Audio format setup error
    }

    // Set the number of channels
    err = snd_pcm_hw_params_set_channels(handle, params, 1); // Mono channel
    if (err < 0) {
        std::cerr << "Error: Unable to set the number of channels. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -5; // Channel setup error
    }

    // Set the sample rate
    err = snd_pcm_hw_params_set_rate_near(handle, params, &sample_rate, nullptr);
    if (err < 0) {
        std::cerr << "Error: Unable to set sample rate. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -6; // Sample rate setup error
    }

    // Apply the hardware parameters
    err = snd_pcm_hw_params(handle, params);
    if (err < 0) {
        std::cerr << "Error: Failed to configure hardware parameters. Reason: " 
                  << snd_strerror(err) << std::endl;
        snd_pcm_close(handle);
        return -7; // Hardware parameters application error
    }

    std::cout << "Audio device initialized with sample rate: " << sample_rate << " Hz" << std::endl;
    return 0; // Success
}

void cleanup_audio_device(snd_pcm_t* handle) {
    if (handle) {
        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        std::cout << "Audio device cleaned up and closed successfully." << std::endl;
    }
}