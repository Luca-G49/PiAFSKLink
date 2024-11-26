// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "app_config.h"

namespace Config {

// Retrieves the global configuration instance.
AppConfig& get() {
    static AppConfig instance;
    return instance;
}

// Resets the configuration to its default values.
void AppConfig::resetToDefault() {
    appName = "PiAFSKLink";
    sample_rate = 44100;          // Sample rate in Hz
    volume = 0.5;                 // Playback volume level (0.0 - 1.0)
    tone_duration = 20000;        // Duration of each tone in microseconds
    tone_0 = 2200.0;              // Tone frequency for bit 0 in Hz
    tone_1 = 3600.0;              // Tone frequency for bit 1 in Hz
    tone_start = 200.0;           // Tone frequency for start bit sequence in Hz
    tone_end = 500.0;             // Tone frequency for stop bit sequence in Hz
    tone_end_deadline = 10;       // Tone end deadline from tone start in seconds
}

} // namespace Config
