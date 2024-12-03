// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "gui_utils.h"
#include "transmitter.h"
#include "serialization.h"
#include <iostream>
#include <string>
#include <iomanip>

// Transmit menu
void transmit_menu() {

    bool menuExit = false;

    clearTerminal();
    printTitle();
    printBorder("SEND MESSAGE");
    std::cout << "| Enter message (type [Q] to return):             |\n";
    std::cout << "+-------------------------------------------------+\n";

    while (!menuExit) {
        
        // Get message from user
        std::cout << "> ";
        std::string message;
        std::getline(std::cin, message);

        if (message == "q" || message == "Q") {
            menuExit = true;
        }
        else {

            // Check that message is not empty
            if(!message.empty()){
                // Convert message into bit string and transmit
                transmit(stringToBits(message));
                std::cout << "\n\033[1;32mMessage sent: \033[0m" << message;
                std::cout << std::endl << std::endl;
            }
        }
    }
}