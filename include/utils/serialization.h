// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <vector>
#include <string>

/**
 * Serializes a string into a vector of bits (represented as booleans).
 *
 * This function converts each character of the input string into its corresponding binary 
 * representation. Each character is split into 8 bits, and these bits are stored in a vector 
 * of booleans (true for 1 and false for 0).
 *
 * @param str The input string to serialize.
 * @return A vector of booleans representing the binary form of the string.
 */
std::vector<bool> serializeString(const std::string& str);

/**
 * Deserializes a vector of bits back into a string.
 *
 * This function takes a vector of booleans representing binary data and reconstructs the 
 * original string. The vector is expected to contain bits in the order they represent 
 * characters, with each 8 bits forming one character.
 *
 * @param bitVector The vector of bits (true for 1 and false for 0) to deserialize.
 * @return The deserialized string formed from the bits.
 */
std::string deserializeBitVector(const std::vector<bool>& bitVector);

/**
 * Converts a string into its binary representation.
 *
 * This function takes an input string and converts each character into an 8-bit binary string. 
 * The binary representation of each character is concatenated together to form the final 
 * binary string.
 *
 * @param str The input string to convert.
 * @return A binary string representing the input string.
 */
std::string stringToBits(const std::string& str);

/**
 * Converts a binary string (bits) back into the original string.
 *
 * This function takes a string of binary digits (0s and 1s) and converts it back into a 
 * human-readable string. The bit string must have a length that is a multiple of 8 to 
 * ensure proper byte alignment (each character is represented by 8 bits).
 *
 * @param bits A string of binary digits (must be a multiple of 8 in length).
 * @return The original string represented by the binary input.
 * @throws std::string If the bit string length is not a multiple of 8, an error is logged, 
 *         and an empty string is returned.
 */
std::string bitsToString(const std::string& bits);

#endif // SERIALIZATION_H
