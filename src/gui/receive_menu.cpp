#include "gui_utils.h"
#include "receiver.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <atomic>
#include <iomanip>

// Buffer for view messages
std::deque<std::string> viewMessages;

// Receive menu
void receive_menu() {
    bool menuExit = false;

    while (!menuExit) {
        // Copy messages from receiver buffer to view buffer
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            while (!receivedMessages.empty()) {
                viewMessages.push_back(receivedMessages.front());
				receivedMessages.pop_front();
            }
        }

        // Print received messages
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

        // User option
        std::cout << "\n[R] Refresh messages   [Q] Return to main menu\n";
        std::cout << "> ";
        char choice;
        std::cin >> choice;

        if (choice == 'q' || choice == 'Q') {
            menuExit = true;
        }
    }
}