#include "app_config.h"

namespace Config {

// Global configuration
AppConfig& get() {
    static AppConfig instance;
    return instance;
}

// Reset default configuration
void AppConfig::resetToDefault() {
    appName = "PiAFSKLink";
    sample_rate = 44100;          // Sample rate in Hz
    volume = 0.5;                 // Playback volume level (0.0 - 1.0)
    tone_duration = 10000;        // Duration of each tone in microseconds
    tone_0 = 2200.0;              // Tone frequency for bit 0 in Hz
    tone_1 = 3600.0;              // Tone frequency for bit 1 in Hz
    tone_start = 200.0;           // Tone frequency for start bit sequence in Hz
    tone_end = 500.0;             // Tone frequency for stop bit sequence in Hz
}

} // namespace Config
