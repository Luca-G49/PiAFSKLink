// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "gui_utils.h"
#include "app_config.h"
#include <iostream>
#include <string>
#include <iomanip>

// Clean terminal
void clearTerminal() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Mac
#endif
}

// Print title
void printTitle() {

    // Get App configuration
    Config::AppConfig& config = Config::get();

    std::cout << "\033[1;34m" << std::string(51, '=') << "\033[0m" << std::endl;
    std::cout << "\033[1;33m" << std::setw(30) << std::right << config.appName << "\033[0m" << std::endl;
    std::cout << "\033[1;34m" << std::string(51, '=') << "\033[0m" << std::endl;
}

// Print border
void printBorder(const std::string& title) {
    std::cout << "\033[1;34m+-------------------------------------------------+\033[0m\n";
    if (!title.empty()) {
        std::cout << "\033[1;32m| " << std::setw(48) << std::left << title << "|\033[0m\n";
        std::cout << "\033[1;34m+-------------------------------------------------+\033[0m\n";
    }
}