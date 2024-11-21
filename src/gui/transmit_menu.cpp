#include "gui_utils.h"
#include "transmitter.h"
#include <iostream>
#include <string>
#include <iomanip>

// Funzione per inviare messaggi
void transmit_menu() {

    bool menuExit = false;

    clearTerminal();
    printTitle();
    printBorder("SEND MESSAGE");
    std::cout << "| Enter a bit sequence (type '[Q]' to return):    |\n";
    std::cout << "+-------------------------------------------------+\n";

    while (!menuExit) {
        
        std::cout << "> ";
        std::string message;
        std::cin >> message;

        if (message == "q" || message == "Q") {
            menuExit = true; // Torna al menu
        }
        else {

            std::cout << "\n\033[1;32mMessage sent: \033[0m" << message;
            transmit(message);
            std::cout << std::endl << std::endl;
        }
    }
}