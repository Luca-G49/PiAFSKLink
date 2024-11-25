// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef LOGGER_H
#define LOGGER_H

#include <spdlog/spdlog.h>

class Logger {
public:
    static void init();
    static std::shared_ptr<spdlog::logger>& getLogger();

private:
    static std::shared_ptr<spdlog::logger> logger;
};

#endif // LOGGER_H
