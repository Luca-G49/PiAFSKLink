#include "main_menu.h"
#include "exit_menu.h"
#include "gui_utils.h"
#include "audio_device.h"
#include "transmitter.h"
#include "receiver.h"
#include <thread>
#include <vector>
#include <iostream>
#include <atomic>

// Program loop execution flag
std::atomic<bool> running(true);

int main() {

    // Create receiver thread
    std::thread receiverThread(receiver_thread, std::ref(running));

    // Show main menu
    main_menu();

    // Stop receiver thread and wait conclusion
    running.store(false);
    receiverThread.join();

    // Show exit menu
    exit_menu();

    return 0;
}
