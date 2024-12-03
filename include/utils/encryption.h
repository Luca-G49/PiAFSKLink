#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to generate a random IV (Initialization Vector)
std::string generateIV();

// Function to encrypt plaintext using AES-256-CBC
int encrypt(const std::string& plaintext, const std::string& key, const std::string& iv, std::string& ciphertext);

// Function to decrypt ciphertext using AES-256-CBC
int decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv, std::string& plaintext);

// Function to encrypt a message, including a randomly generated IV
int encrypt_message(const std::string& plaintext, const std::string& key, std::string& result);

// Function to decrypt a message that includes the IV
int decrypt_message(const std::string& ciphertext_with_iv, const std::string& key, std::string& result);

#endif // ENCRYPTION_H
