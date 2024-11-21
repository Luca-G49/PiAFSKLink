#ifndef AUDIO_DEVICE_H
#define AUDIO_DEVICE_H

#include <alsa/asoundlib.h>

// Function to initialize the audio device with the given sample rate
int initialize_audio_device(snd_pcm_t*& handle, unsigned int sample_rate);

// Function to clean up and close the audio device
void cleanup_audio_device(snd_pcm_t* handle);

#endif