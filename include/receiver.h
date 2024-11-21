#ifndef RECEIVER_H
#define RECEIVER_H

#include <atomic>
#include <mutex>
#include <deque>

void receiver_thread(std::atomic<bool>& running);

extern std::deque<std::string> receivedMessages;
extern std::mutex bufferMutex;

#endif
