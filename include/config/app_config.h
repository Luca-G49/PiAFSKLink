// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

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
    int tone_duration = 20000;        // Duration of each tone in microseconds
    double tone_0 = 2200.0;           // Tone frequency for bit 0 in Hz
    double tone_1 = 3600.0;           // Tone frequency for bit 1 in Hz
    double tone_start = 500.0;        // Tone frequency for start bit sequence in Hz
    double tone_end = 1000.0;         // Tone frequency for stop bit sequence in Hz
    int tone_end_deadline = 10;       // Tone end deadline from tone start in seconds

    // Reset default configuration
    void resetToDefault();
};

// Return configuration
AppConfig& get();

} // namespace Config

#endif // APP_CONFIG_H
