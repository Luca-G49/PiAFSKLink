// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <vector>
#include <string>

// Serialize a string into a sequence of bits (vector of bools)
std::vector<bool> serializeString(const std::string& str);

// Deserialize a sequence of bits (vector of bools) back into a string
std::string deserializeBitVector(const std::vector<bool>& bitVector);

// Convert a string to its binary representation (a string of bits)
std::string stringToBits(const std::string& str);

// Convert a binary string (bits) back into the original string
std::string bitsToString(const std::string& bits);

#endif // SERIALIZATION_H
