#ifndef RECEIVER_H
#define RECEIVER_H

#include <atomic>
#include <mutex>
#include <deque>
#include <vector>

// Function to detect the start tone (used for synchronization)
bool detect_start_tone(const std::vector<short> &samples, unsigned int sample_rate);

// Function to detect the end tone (used to terminate the reception)
bool detect_end_tone(const std::vector<short> &samples, unsigned int sample_rate);

// Function to detect the bit tone (for both 1 and 0)
bool detect_bit_tone(const std::vector<short> &samples, unsigned int sample_rate);

// Simulated receiver thread
void receiver_thread_sim(std::atomic<bool> &running);

// Receiver thread
void receiver_thread(std::atomic<bool> &running);

extern std::deque<std::string> receivedMessages;
extern std::mutex bufferMutex;

#endif
