#include "receiver.h"
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <atomic>

std::deque<std::string> receivedMessages;
std::mutex bufferMutex;

void receiver_thread(std::atomic<bool>& running) {
    int counter = 0; // Simulate receive counter
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate receiver delay
        std::lock_guard<std::mutex> lock(bufferMutex);
        receivedMessages.push_back("Received message #" + std::to_string(++counter));
    }
}
