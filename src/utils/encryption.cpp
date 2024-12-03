#include "logger.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <openssl/evp.h>
#include <openssl/rand.h>

// Function to generate a random IV (Initialization Vector)
std::string generateIV() {
    unsigned char iv[16]; // 16 bytes for AES-256-CBC (128-bit IV)
    if (!RAND_bytes(iv, 16)) { // Generate random bytes
        Logger::getLogger()->error("Unable to generate IV.");
        return "";
    }
    // Return the IV as a string
    return std::string(reinterpret_cast<char*>(iv), 16);
}

// Function to encrypt data using AES-256-CBC
int encrypt(const std::string& plaintext, const std::string& key, const std::string& iv, std::string& ciphertext) {
    
    if (key.size() != 32) {
        Logger::getLogger()->error("Key size must be 32 bytes for AES-256");
        return -1;
    }
    if (iv.size() != 16) {
        Logger::getLogger()->error("IV size must be 16 bytes for AES");
        return -1;
    }
    
    // Create a new encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        Logger::getLogger()->error("Failed to create encryption context");
        return -1;
    }

    // Initialize the context with AES-256-CBC, key, and IV
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()),
                           reinterpret_cast<const unsigned char*>(iv.c_str())) != 1) {

        Logger::getLogger()->error("Failed to initialize encryption operation");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    // Allocate space for the ciphertext (may include padding)
    std::string tmp_ciphertext(plaintext.size() + 16, '\0');
    int len = 0, ciphertext_len = 0;

    // Encrypt the plaintext
    if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&tmp_ciphertext[0]), &len,
                          reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size()) != 1) {
        Logger::getLogger()->error("Failed to encrypt plaintext");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len += len;

    // Finalize encryption and handle padding
    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&tmp_ciphertext[0]) + len, &len) != 1) {
        Logger::getLogger()->error("Failed to finalize encryption");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    ciphertext_len += len;

    // Resize the ciphertext to the actual length
    tmp_ciphertext.resize(ciphertext_len);
    ciphertext = tmp_ciphertext;
    EVP_CIPHER_CTX_free(ctx); // Free the encryption context

    return 0;
}

// Function to decrypt data using AES-256-CBC
int decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv, std::string& plaintext) {
    
    if (key.size() != 32) {
        Logger::getLogger()->error("Key size must be 32 bytes for AES-256");
        return -1;
    }
    if (iv.size() != 16) {
        Logger::getLogger()->error("IV size must be 16 bytes for AES");
        return -1;
    }
    
    // Create a new decryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        Logger::getLogger()->error("Failed to create decryption context");
        return -1;
    }

    // Initialize the context with AES-256-CBC, key, and IV
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()),
                           reinterpret_cast<const unsigned char*>(iv.c_str())) != 1) {
        Logger::getLogger()->error("Failed to initialize decryption operation");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }

    // Allocate space for the plaintext
    std::string tmp_plaintext(ciphertext.size(), '\0');
    int len = 0, plaintext_len = 0;

    // Decrypt the ciphertext
    if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&tmp_plaintext[0]), &len,
                          reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size()) != 1) {
        Logger::getLogger()->error("Failed to decrypt ciphertext");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;

    // Finalize decryption and handle padding removal
    if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&tmp_plaintext[0]) + len, &len) != 1) {
        Logger::getLogger()->error("Failed to finalize decryption");
        EVP_CIPHER_CTX_free(ctx);
        return -1;
    }
    plaintext_len += len;

    // Resize the plaintext to the actual length
    tmp_plaintext.resize(plaintext_len);
    plaintext = tmp_plaintext;
    EVP_CIPHER_CTX_free(ctx); // Free the decryption context

    return 0;
}

// Function to encrypt a message with a generated IV
int encrypt_message(const std::string& plaintext, const std::string& key, std::string& result) {
    std::string iv = generateIV(); // Generate a random IV
    if (iv.empty()) {
        return -1; // Error during IV generation
    }

    // Encrypt the message
    std::string ciphertext;
    if (encrypt(plaintext, key, iv, ciphertext) != 0) {
        return -1; // Error during encryption
    }

    // Prepend IV to ciphertext
    result = iv + ciphertext; 

    return 0;
}

// Function to decrypt a message that includes the IV
int decrypt_message(const std::string& ciphertext_with_iv, const std::string& key, std::string& result) {

    if (ciphertext_with_iv.size() < 16) {
        Logger::getLogger()->error("Ciphertext is too short to contain an IV");
        return -1;
    }

    // Extract the IV (first 16 bytes)
    std::string iv = ciphertext_with_iv.substr(0, 16);
    
    // Extract the actual ciphertext (remaining bytes)
    std::string ciphertext = ciphertext_with_iv.substr(16);

    // Decrypt using the extracted IV
    if (decrypt(ciphertext, key, iv, result) != 0) {
        return -1; // Error during decryption
    }

    return 0;
}
