#include "serialization.h"
#include <iostream>
#include <bitset>

// Function to serialize a string into a vector of bits (bools)
std::vector<bool> serializeString(const std::string& str) {
    std::vector<bool> bitVector;

    // Iterate through each character in the string
    for (char c : str) {
        // For each character, extract the individual bits
        for (int i = 7; i >= 0; --i) {
            // Shift the character and extract each bit
            bitVector.push_back((c >> i) & 1);
        }
    }

    return bitVector;
}

// Deserialize a vector of bits back into a string
std::string deserializeBitVector(const std::vector<bool>& bitVector) {
    std::string str = ""; 
    char currentChar = 0;      
    int bitCount = 0;

    // Iterate through the bits in the bitVector
    for (bool bit : bitVector) {
        currentChar = (currentChar << 1) | bit;
        bitCount++;

        // Every 8 bits form a character
        if (bitCount == 8) {
            str += currentChar;
            currentChar = 0;
            bitCount = 0;
        }
    }

    return str;
}

// Convert a string into its binary representation (a string of bits)
std::string stringToBits(const std::string& str) {
    std::string bits = "";
    
    // Iterate through each character in the string
    for (char c : str) {
        std::bitset<8> b(c);  // Convert the character to a bitset (8 bits per character)
        bits += b.to_string();  // Append the 8 bits to the binary string
    }

    return bits;
}

// Convert a binary string (bits) back into the original string
std::string bitsToString(const std::string& bits) {
    std::string str = "";
    
    // Ensure the bit string length is a multiple of 8 (valid byte sequence)
    if (bits.length() % 8 != 0) {
        std::cerr << "Error: The bit string length must be a multiple of 8!" << std::endl;
        return "";
    }

    // Iterate through the bits in chunks of 8 (1 byte at a time)
    for (size_t i = 0; i < bits.length(); i += 8) {
        // Take 8 bits at a time
        std::bitset<8> b(bits.substr(i, 8));  // Create a bitset from the 8-bit substring
        str += char(b.to_ulong());            // Convert the bitset to an unsigned long and cast to char
    }

    return str;
}

