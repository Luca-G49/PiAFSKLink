// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "logger.h"
#include <spdlog/sinks/basic_file_sink.h>

// Definition of the static logger
std::shared_ptr<spdlog::logger> Logger::logger = nullptr;


// Initializes the logger and sets up the logging system.
void Logger::init()
{
    if (logger)
    {
        // Avoid reinitialization if the logger is already set
        return;
    }

    try
    {
        // Create the logger and assign it to the static logger variable
        logger = spdlog::basic_logger_mt("PiAFSKLink", "logs/system.log");

        // Set the logging level and flush policy
        logger->set_level(spdlog::level::info);
        spdlog::flush_on(spdlog::level::info);

        // Log initialization success
        logger->info("Logger initialized successfully.");
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        throw std::runtime_error(std::string("Logger initialization failed: ") + ex.what());
    }
}

// Retrieves the initialized logger instance.
std::shared_ptr<spdlog::logger> &Logger::getLogger()
{
    if (!logger)
    {
        throw std::runtime_error("Logger is not initialized. Call Logger::init() first.");
    }
    return logger;
}
