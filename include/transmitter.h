#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <string>
#include <vector>
#include <alsa/asoundlib.h>

// Generate a tone of the given frequency, volume, and duration
void generate_tone(double frequency, snd_pcm_t* handle, double volume, int duration);

// Play a sequence of bits as AFSK tones
void play_bit_sequence(const std::vector<int>& bit_sequence, snd_pcm_t* handle);

// Transmit bit sequence
void transmit(std::string input_bits);

#endif
