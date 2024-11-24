#include "logger.h"
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

// Definition of the static logger
std::shared_ptr<spdlog::logger> Logger::logger = nullptr;

void Logger::init() {
    // Create a sink for the terminal (stdout) and one for the log file
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/app.log", true);
    file_sink->set_level(spdlog::level::info);

    // Create the logger with the two sinks
    logger = std::make_shared<spdlog::logger>("multi_sink", spdlog::sinks_init_list{console_sink, file_sink});

    // Set the global log level
    logger->set_level(spdlog::level::debug); // All logs >= debug
}

std::shared_ptr<spdlog::logger>& Logger::getLogger() {
    return logger;
}
