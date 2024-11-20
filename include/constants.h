#ifndef CONSTANTS_H
#define CONSTANTS_H

// Audio configuration
constexpr int SAMPLE_RATE = 44100;          // Sample rate in Hz
constexpr double VOLUME = 0.5;              // Playback volume level (0.0 - 1.0)
constexpr int TONE_DURATION = 100000;       // Duration of each tone in microseconds

// AFSK tone frequencies
constexpr double TONE_0 = 2200.0; // Tone frequency for bit 0 in Hz
constexpr double TONE_1 = 3600.0; // Tone frequency for bit 1 in Hz

#endif // CONSTANTS_H