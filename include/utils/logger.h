// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>

class Logger
{
public:
    /**
     * Initializes the logger and sets up the logging system.
     *
     * This function initializes a basic file logger that writes log entries to "logs/system.log".
     * It sets the logging level to `info` and ensures logs at the `info` level or higher are flushed
     * to the log file immediately. The function will only initialize the logger once, avoiding
     * reinitialization if it is already set up.
     *
     * @throws std::runtime_error if the logger cannot be initialized or any error occurs during setup.
     */
    static void init();

    /**
     * Retrieves the initialized logger instance.
     *
     * This function returns a reference to the static logger instance. It ensures that the logger
     * is properly initialized before use. If the logger has not been initialized, it throws a runtime error.
     *
     * @return A reference to the logger instance.
     * @throws std::runtime_error if the logger has not been initialized. Ensure `Logger::init()` is called first.
     */
    static std::shared_ptr<spdlog::logger> &getLogger();

private:
    static std::shared_ptr<spdlog::logger> logger;
};

#endif // LOGGER_H
