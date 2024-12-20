// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "gui_utils.h"
#include "transmitter.h"
#include "serialization.h"
#include "app_config.h"
#include "logger.h"
#include "encryption.h"
#include <iostream>
#include <string>
#include <iomanip>

// Transmit menu
void transmit_menu()
{

    bool menuExit = false;

    clearTerminal();
    printTitle();
    printBorder("SEND MESSAGE");
    std::cout << "| Enter message (type [Q] to return):             |\n";
    std::cout << "+-------------------------------------------------+\n";

    // Clear any residual characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (!menuExit)
    {
        // Get message from user
        std::cout << "> ";
        std::string message;

        std::getline(std::cin, message);

        if (message == "q" || message == "Q")
        {
            menuExit = true;
        }
        else
        {
            // Check that message is not empty
            if (!message.empty())
            {
                // Get App configuration
                Config::AppConfig &config = Config::get();

                // Get the start time before transmission
                auto start = std::chrono::steady_clock::now();

                // Encrypt the message if encryption is enabled
                if (config.enable_encryption)
                {
                    std::string encrypted_message;

                    // Encrypt the message
                    if (encrypt_message(message, config.encryption_key, encrypted_message) != 0)
                    {
                        Logger::getLogger()->error("Failed to encrypt the message.");
                        continue;
                    }

                    Logger::getLogger()->info("Message successfully encrypted.");

                    // Convert the encrypted message into bit string and transmit
                    transmit(stringToBits(encrypted_message));
                }
                else
                {
                    // Convert message into bit string and transmit
                    transmit(stringToBits(message));
                }

                // Get the end time after transmission
                auto end = std::chrono::steady_clock::now();

                // Calculate the duration
                std::chrono::duration<double> duration = end - start;

                std::cout << "\n\033[1;32mMessage sent: \033[0m" << message
                          << "\n\033[1;32mTransmission time: \033[0m"
                          << std::fixed << std::setprecision(5) << duration.count() << " seconds";

                if (config.enable_encryption)
                {
                    std::cout << "\n\033[1;32mStatus: \033[34mEncrypted\033[0m";
                }
                else
                {
                    std::cout << "\n\033[1;32mStatus: \033[31mNot Encrypted\033[0m";
                }

                std::cout << std::endl
                          << std::endl;
            }
        }
    }
}