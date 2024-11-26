// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef GET_TIME_H
#define GET_TIME_H

#include <string>

/**
 * Retrieves the current system time formatted as a string.
 *
 * This function returns the current system time in the format "YYYY-MM-DD HH:MM:SS".
 * It uses the system clock to get the time and then converts it to a formatted string
 * using `std::chrono` for time handling and `std::put_time` for formatting the output.
 *
 * @return A string representing the current time in the format "YYYY-MM-DD HH:MM:SS", 
 *         for example: "2024-11-26 15:30:00".
 */
std::string getCurrentTime();

#endif // GET_TIME_H