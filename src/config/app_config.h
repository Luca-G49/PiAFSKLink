#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <string>

// Configuration namespace
namespace Config {

// Global configuration
struct AppConfig {
    std::string appName = "PiAFSKLink";
    int sample_rate = 44100;          // Sample rate in Hz
    double volume = 0.5;              // Playback volume level (0.0 - 1.0)
    int tone_duration = 10000;       // Duration of each tone in microseconds
    double tone_0 = 2200.0;           // Tone frequency for bit 0 in Hz
    double tone_1 = 3600.0;           // Tone frequency for bit 1 in Hz
    int start_tone_duration = 10000; // Duration of start tone in microseconds
    int end_tone_duration = 10000;   // Duration of end tone in microseconds
    double start_tone = 500.0;       // Tone frequency for start bit sequence in Hz
    double end_tone = 1000.0;         // Tone frequency for stop bit sequence in Hz

    // Reset default configuration
    void resetToDefault();
};

// Return configuration
AppConfig& get();

} // namespace Config

#endif // APP_CONFIG_H
