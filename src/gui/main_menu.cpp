#include "main_menu.h"
#include "receive_menu.h"
#include "transmit_menu.h"
#include "setup_menu.h"
#include "gui_utils.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>

// Funzione per il menu principale
void main_menu() {

    bool menuExit = true;

    while (menuExit) {
        clearTerminal();
        printTitle();
        printBorder("MAIN MENU");
        std::cout << "| 1. View received messages                       |\n";
        std::cout << "| 2. Send message                                 |\n";
        std::cout << "| 3. Setup                                        |\n";
        std::cout << "| 4. Exit                                         |\n";
        std::cout << "+-------------------------------------------------+\n";
        std::cout << "> Enter your choice: ";

        int choice;
        std::cin >> choice;

        // Se l'input non è valido (numero non tra 1, 2, 3, 4)
        if (std::cin.fail() || choice < 1 || choice > 4) {
            // Pulire l'errore di cin e ignorare tutto il contenuto nel buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid choice, please try again.\033[0m\n";  // Colore rosso per l'errore
            std::this_thread::sleep_for(std::chrono::seconds(2)); // Pausa prima di continuare
            continue; // Torna all'inizio del ciclo
        }

        switch (choice) {
            case 1:
                receive_menu();
                break;
            case 2:
                transmit_menu();
                break;
            case 3:
                setup_menu();
                break;
            case 4:
                menuExit = false;
                return;
            default:
                menuExit = false;
                return;
        }
    }
}
