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
    std::cout << "| Enter a bit sequence (type '[Q]' to return):    |\n";
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
            // Convert message into bit string and transmit
            transmit(stringToBits(message));
            std::cout << "\n\033[1;32mMessage sent: \033[0m" << message << " -> " << stringToBits(message);
            std::cout << std::endl << std::endl;
        }
    }
}