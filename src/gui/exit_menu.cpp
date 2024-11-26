// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "gui_utils.h"
#include <thread>

// Exit menu
void exit_menu(){
    clearTerminal();
    printBorder("Goodbye, thank you for using PiAFSKLink!");
    std::this_thread::sleep_for(std::chrono::seconds(2));
    clearTerminal();
}