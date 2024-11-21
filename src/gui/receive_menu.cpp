#include "gui_utils.h"
#include "receiver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <atomic>
#include <iomanip>

// Buffer copia per i messaggi ricevuti
std::deque<std::string> viewMessages;

// Funzione per visualizzare i messaggi ricevuti
void receive_menu() {
    bool menuExit = false;

    while (!menuExit) {
        // Copia i messaggi dal buffer principale al buffer locale
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            while (!receivedMessages.empty()) {
                viewMessages.push_back(receivedMessages.front());
				receivedMessages.pop_front();
            }
        }

        // Mostra i messaggi dal buffer locale
        clearTerminal();
        printTitle();
        printBorder("MESSAGES RECEIVED");
        if (!viewMessages.empty()) {
            for (const auto& msg : viewMessages) {
                std::cout << "| " << std::setw(48) << std::left << msg << "|\n";
            }
        } else {
            std::cout << "| " << std::setw(48) << std::left << "No new messages." << "|\n";
        }
        std::cout << "+-------------------------------------------------+\n";

        // Opzioni per l'utente
        std::cout << "\n[R] Refresh messages   [Q] Return to main menu\n";
        std::cout << "> ";
        char choice;
        std::cin >> choice;

        if (choice == 'q' || choice == 'Q') {
            menuExit = true; // Torna al menu
        }
    }
}