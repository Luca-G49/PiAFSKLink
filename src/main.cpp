#include "gui/main_menu.h"
#include "gui/gui_utils.h"
#include "audio/audio_device.h"
#include "transmitter.h"
#include "receiver.h"
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

// Flag per controllare l'esecuzione del programma
std::atomic<bool> running(true);

int main() {

    // Create receiver thread
    std::thread receiverThread(receiver_thread, std::ref(running));

    // Show main menu
    main_menu();

    // Stop receiver thread and wait conclusion
    running = false;
    receiverThread.join();

    std::cout << "Program terminated." << std::endl;
    return 0;
}
