#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to handle errors during encryption or decryption
void handleErrors();

// Function to generate a random IV (Initialization Vector)
std::string generateIV();

// Function to encrypt plaintext using AES-256-CBC
std::string encrypt(const std::string& plaintext, const std::string& key, const std::string& iv);

// Function to decrypt ciphertext using AES-256-CBC
std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv);

// Function to encrypt a message, including a randomly generated IV
std::string encrypt_message(const std::string& plaintext, const std::string& key);

// Function to decrypt a message that includes the IV
std::string decrypt_message(const std::string& ciphertext_with_iv, const std::string& key);

#endif // ENCRYPTION_H
