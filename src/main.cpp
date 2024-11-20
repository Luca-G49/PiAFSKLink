#include "audio_utils.h"
#include "transmitter.h"
#include "receiver.h"
#include "constants.h"
#include <thread>
#include <vector>
#include <iostream>

bool running = true;  // Shared flag for threads stop

void transmitter_thread() {
    while (running)
    {
        snd_pcm_t *handle;

        // Initialize the audio device for playback
        int result = initialize_audio_device(handle, SAMPLE_RATE);
        if (result < 0)
        {
            std::cerr << "Audio initialization failed with error code: " << result << std::endl;
        }

        // Input the bit sequence
        std::vector<int> bit_sequence;
        std::string input_bits;
        std::cout << "Enter a bit sequence (e.g., 101010) to transmit (or type 'exit' to quit): ";
        std::cin >> input_bits;

        // Check if the user wants to exit
        if (input_bits == "exit") {
            running = false;  // Stop threads
            break;
        }

        // Convert input string to a bit sequence
        for (char bit : input_bits)
        {
            if (bit == '0' || bit == '1')
            {
                bit_sequence.push_back(bit - '0'); // Convert char to int
            }
        }

        play_bit_sequence(bit_sequence, handle);

        // Clean up the audio device
        cleanup_audio_device(handle);
    }
}

void receiver_thread() {
    // Start the receiver to listen for AFSK tones
    start_receiver();

    // Listen for incoming signals
    while (running) {
        ;
    }
}

int main() {

    // Create separate threads for transmitter and receiver
    std::thread tx(transmitter_thread);
    std::thread rx(receiver_thread);

    // Wait for both threads to complete
    tx.join();
    rx.join();

    std::cout << "Program terminated." << std::endl;
    return 0;
}
