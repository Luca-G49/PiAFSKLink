// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include <iostream>
#include <chrono>
#include <iomanip>

// Retrieves the current system time formatted as a string.
std::string getCurrentTime() {
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();
    
    // Convert the time_point to a time_t for formatting
    auto time = std::chrono::system_clock::to_time_t(now);
    
    // Convert time_t to tm (local time structure)
    std::tm localTime = *std::localtime(&time);
    
    // Format the time into a string
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
    
    return oss.str();
}