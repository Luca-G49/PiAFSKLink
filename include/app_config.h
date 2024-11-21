#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <string>

// Configuration namespace
namespace Config {

// Dati di configurazione globali
struct AppConfig {
    std::string appName = "PiAFSKLink";
    int sample_rate = 44100;          // Sample rate in Hz
    double volume = 0.5;              // Playback volume level (0.0 - 1.0)
    int tone_duration = 100000;       // Duration of each tone in microseconds
    double tone_0 = 2200.0;           // Tone frequency for bit 0 in Hz
    double tone_1 = 3600.0;           // Tone frequency for bit 1 in Hz
};

// Return configuration
AppConfig& get();

} // namespace Config

#endif // APP_CONFIG_H
