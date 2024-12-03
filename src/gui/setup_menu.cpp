// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#include "setup_menu.h"
#include "gui_utils.h"
#include "app_config.h"
#include "receiver.h"
#include <iostream>
#include <string>
#include <thread>

// Setup menu
void setup_menu()
{

    // Get App configuration
    Config::AppConfig &config = Config::get();

    bool menuExit = false;

    while (!menuExit)
    {
        clearTerminal();
        printTitle();
        printBorder("SETUP");
        std::cout << "| 1. Sample rate                                  |\n";
        std::cout << "| 2. Volume                                       |\n";
        std::cout << "| 3. Tone duration                                |\n";
        std::cout << "| 4. Tone for bit0                                |\n";
        std::cout << "| 5. Tone for bit1                                |\n";
        std::cout << "| 6. Tone for start                               |\n";
        std::cout << "| 7. Tone for end                                 |\n";
        std::cout << "| 8. Tone end deadline                            |\n";
        std::cout << "| 9. Enable message encryption                    |\n";
        std::cout << "| 10. Encryption key                              |\n";
        std::cout << "| 11. View current setup                          |\n";
        std::cout << "| 12. Restore default setup                       |\n";
        std::cout << "| 13. Delete received messages                    |\n";
        std::cout << "| 14. Return to main menu                         |\n";
        std::cout << "+-------------------------------------------------+\n";
        std::cout << "> Enter your choice: ";

        int choice;
        std::cin >> choice;

        // Check for valid input
        if (std::cin.fail() || choice < 1 || choice > 14)
        {
            // Clear cin buffer, ignore and continue
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\033[1;31mInvalid choice, please try again.\033[0m\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));
            continue;
        }

        switch (choice)
        {
        case 1:
        {
            // Change sample rate
            int inputSampleRate{};

            std::cout << "Enter new sample rate (Hz): ";
            std::cin >> inputSampleRate;

            if (!std::cin.fail() && inputSampleRate > 0)
            {
                config.sample_rate = inputSampleRate;
                std::cout << "\033[1;32mSample rate set to \033[0m" << config.sample_rate << "\033[1;32m Hz\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 2:
        {
            // Change volume
            double inputVolume{};

            std::cout << "Enter new volume (0.0-1.0): ";
            std::cin >> inputVolume;

            if (!std::cin.fail() && inputVolume >= 0.0 && inputVolume <= 1.0)
            {
                config.volume = inputVolume;
                std::cout << "\033[1;32mVolume set to \033[0m" << config.volume << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 3:
        {
            // Change tone duration
            int inputToneDuration{};

            std::cout << "Enter new tone_duration (us): ";
            std::cin >> inputToneDuration;

            if (!std::cin.fail() && inputToneDuration > 0)
            {
                config.tone_duration = inputToneDuration;
                std::cout << "\033[1;32mTone duration set to \033[0m" << config.tone_duration << "\033[1;32m us\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 4:
        {
            // Change tone for bit0
            double inputToneBit0{};

            std::cout << "Enter new tone for bit0 (Hz): ";
            std::cin >> inputToneBit0;

            if (!std::cin.fail() && inputToneBit0 > 0)
            {
                config.tone_0 = inputToneBit0;
                std::cout << "\033[1;32mTone for bit0 set to \033[0m" << config.tone_0 << "\033[1;32m Hz\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 5:
        {
            // Change tone for bit1
            double inputToneBit1{};

            std::cout << "Enter new tone for bit1 (Hz): ";
            std::cin >> inputToneBit1;

            if (!std::cin.fail() && inputToneBit1 > 0)
            {
                config.tone_1 = inputToneBit1;
                std::cout << "\033[1;32mTone for bit1 set to \033[0m" << config.tone_1 << "\033[1;32m Hz\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 6:
        {
            // Change tone for start
            double inputToneBit1{};

            std::cout << "Enter new tone for start (Hz): ";
            std::cin >> inputToneBit1;

            if (!std::cin.fail() && inputToneBit1 > 0)
            {
                config.tone_1 = inputToneBit1;
                std::cout << "\033[1;32mTone for start set to \033[0m" << config.tone_1 << "\033[1;32m Hz\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 7:
        {
            // Change tone for end
            double inputToneBit1{};

            std::cout << "Enter new tone for end (Hz): ";
            std::cin >> inputToneBit1;

            if (!std::cin.fail() && inputToneBit1 > 0)
            {
                config.tone_1 = inputToneBit1;
                std::cout << "\033[1;32mTone for end set to \033[0m" << config.tone_1 << "\033[1;32m Hz\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 8:
        {
            // Change tone for tone end deadline
            double inputToneEndDeadline{};

            std::cout << "Enter new tone end deadline (s): ";
            std::cin >> inputToneEndDeadline;

            if (!std::cin.fail() && inputToneEndDeadline > 0)
            {
                config.tone_end_deadline = inputToneEndDeadline;
                std::cout << "\033[1;32mDeadline for tone end set to \033[0m" << config.tone_end_deadline << "\033[1;32m s\033[0m" << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 9:
        {
            // Enable message encryption
            bool inputEnableEncryption{};

            std::cout << "Enable message encryption [0] [1]: ";
            std::cin >> inputEnableEncryption;

            if (!std::cin.fail())
            {
                config.enable_encryption = inputEnableEncryption;
                std::cout << "\033[1;32mEnable message encryption set to \033[0m" << config.enable_encryption << std::endl;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 10:
        {
            // Message encryption key
            std::string inputEncryptionKey{};
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter new message encryption key (32 bytes for AES-256): ";
            std::getline(std::cin, inputEncryptionKey);

            if (!std::cin.fail() && (inputEncryptionKey.size() == 32))
            {
                config.encryption_key = inputEncryptionKey;
                std::cout << "\033[1;32mMessage encryption key set to \033[0m" << config.encryption_key << std::endl;
            }
            else
            {
                std::cout << "\033[1;31mInvalid value, please try again.\033[0m\n";
            }

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 11:
        {
            // View current setup
            std::cout << "\033[1;32mSample rate: \033[0m" << config.sample_rate << "\033[1;32m Hz\033[0m" << std::endl;
            std::cout << "\033[1;32mVolume: \033[0m" << config.volume << std::endl;
            std::cout << "\033[1;32mTone duration: \033[0m" << config.tone_duration << "\033[1;32m us\033[0m" << std::endl;
            std::cout << "\033[1;32mTone for bit0: \033[0m" << config.tone_0 << "\033[1;32m Hz\033[0m" << std::endl;
            std::cout << "\033[1;32mTone for bit1: \033[0m" << config.tone_1 << "\033[1;32m Hz\033[0m" << std::endl;
            std::cout << "\033[1;32mTone for start: \033[0m" << config.tone_start << "\033[1;32m Hz\033[0m" << std::endl;
            std::cout << "\033[1;32mTone for end: \033[0m" << config.tone_end << "\033[1;32m Hz\033[0m" << std::endl;
            std::cout << "\033[1;32mDeadline for tone end: \033[0m" << config.tone_end_deadline << "\033[1;32m s\033[0m" << std::endl;
            std::cout << "\033[1;32mEnable message encryption: \033[0m" << config.enable_encryption << std::endl;
            std::cout << "\033[1;32mMessage encryption key: \033[0m" << config.encryption_key << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        case 12:
        {
            // Restore default setup
            std::cout << "Are you sure [Y] [N]" << std::endl;
            char confirm;
            std::cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                config.resetToDefault();
                std::cout << "\033[1;32mDefault setup restored \033[0m" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }

            break;
        }

        case 13:
        {
            // Delete received messages
            std::cout << "Are you sure [Y] [N]" << std::endl;
            char confirm;
            std::cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {

                std::cout << "\033[1;32mReceived messages deleted \033[0m" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }

            break;
        }

        case 14:
        {
            menuExit = true;
            break;
        }

        default:
        {
            menuExit = true;
            break;
        }
        }
    }
}