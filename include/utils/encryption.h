// Copyright (c) 2024 Luca-G49
// Distribuited under the MIT License. See the LICENSE file for more details.

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>

/**
 * Generates a random Initialization Vector (IV) for AES encryption.
 *
 * @return A 16-byte IV as a string. Returns an empty string in case of an error.
 */
std::string generateIV();

/**
 * Encrypts the provided plaintext using AES-256-CBC.
 *
 * @param plaintext The plaintext to encrypt.
 * @param key The encryption key (32 bytes for AES-256).
 * @param iv The Initialization Vector (16 bytes).
 * @param ciphertext Reference to a string to store the encrypted ciphertext.
 * @return 0 if successful, -1 if an error occurs.
 */
int encrypt(const std::string& plaintext, const std::string& key, const std::string& iv, std::string& ciphertext);

/**
 * Decrypts the provided ciphertext using AES-256-CBC.
 *
 * @param ciphertext The ciphertext to decrypt.
 * @param key The decryption key (32 bytes for AES-256).
 * @param iv The Initialization Vector (16 bytes).
 * @param plaintext Reference to a string to store the decrypted plaintext.
 * @return 0 if successful, -1 if an error occurs.
 */
int decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv, std::string& plaintext);

/**
 * Encrypts the provided plaintext, automatically generating an IV.
 *
 * @param plaintext The plaintext to encrypt.
 * @param key The encryption key (32 bytes for AES-256).
 * @param result Reference to a string to store the concatenated IV and ciphertext.
 * @return 0 if successful, -1 if an error occurs.
 */
int encrypt_message(const std::string& plaintext, const std::string& key, std::string& result);

/**
 * Decrypts the provided message that includes an IV.
 *
 * @param ciphertext_with_iv The concatenated IV and ciphertext to decrypt.
 * @param key The decryption key (32 bytes for AES-256).
 * @param result Reference to a string to store the decrypted plaintext.
 * @return 0 if successful, -1 if an error occurs.
 */
int decrypt_message(const std::string& ciphertext_with_iv, const std::string& key, std::string& result);

#endif // ENCRYPTION_H
