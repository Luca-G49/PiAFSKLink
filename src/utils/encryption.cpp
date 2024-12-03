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
        Logger::getLogger()->error("Error: Unable to generate IV.");
        exit(1); // Exit the program if IV generation fails
    }
    // Return the IV as a string
    return std::string(reinterpret_cast<char*>(iv), 16);
}

// Function to encrypt data using AES-256-CBC
std::string encrypt(const std::string& plaintext, const std::string& key, const std::string& iv) {
    
    if (key.size() != 32) {
        Logger::getLogger()->error("Error: Key size must be 32 bytes for AES-256");
        exit(1);
    }
    if (iv.size() != 16) {
        Logger::getLogger()->error("Error: IV size must be 16 bytes for AES");
        exit(1);
    }
    
    // Create a new encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        Logger::getLogger()->error("Error: Failed to create encryption context");
        exit(1);
    }

    // Initialize the context with AES-256-CBC, key, and IV
    if (EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()),
                           reinterpret_cast<const unsigned char*>(iv.c_str())) != 1) {

        Logger::getLogger()->error("Error: Failed to initialize encryption operation");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }

    // Allocate space for the ciphertext (may include padding)
    std::string ciphertext(plaintext.size() + 16, '\0');
    int len = 0, ciphertext_len = 0;

    // Encrypt the plaintext
    if (EVP_EncryptUpdate(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]), &len,
                          reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size()) != 1) {
        Logger::getLogger()->error("Error: Failed to encrypt plaintext");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    ciphertext_len += len;

    // Finalize encryption and handle padding
    if (EVP_EncryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&ciphertext[0]) + len, &len) != 1) {
        Logger::getLogger()->error("Error: Failed to finalize encryption");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    ciphertext_len += len;

    // Resize the ciphertext to the actual length
    ciphertext.resize(ciphertext_len);
    EVP_CIPHER_CTX_free(ctx); // Free the encryption context

    return ciphertext;
}

// Function to decrypt data using AES-256-CBC
std::string decrypt(const std::string& ciphertext, const std::string& key, const std::string& iv) {
    
    if (key.size() != 32) {
        Logger::getLogger()->error("Error: Key size must be 32 bytes for AES-256");
        exit(1);
    }
    if (iv.size() != 16) {
        Logger::getLogger()->error("Error: IV size must be 16 bytes for AES");
        exit(1);
    }
    
    // Create a new decryption context
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        Logger::getLogger()->error("Error: Failed to create decryption context");
        exit(1);
    }

    // Initialize the context with AES-256-CBC, key, and IV
    if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                           reinterpret_cast<const unsigned char*>(key.c_str()),
                           reinterpret_cast<const unsigned char*>(iv.c_str())) != 1) {
        Logger::getLogger()->error("Error: Failed to initialize decryption operation");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }

    // Allocate space for the plaintext
    std::string plaintext(ciphertext.size(), '\0');
    int len = 0, plaintext_len = 0;

    // Decrypt the ciphertext
    if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char*>(&plaintext[0]), &len,
                          reinterpret_cast<const unsigned char*>(ciphertext.c_str()), ciphertext.size()) != 1) {
        Logger::getLogger()->error("Error: Failed to decrypt ciphertext");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    plaintext_len += len;

    // Finalize decryption and handle padding removal
    if (EVP_DecryptFinal_ex(ctx, reinterpret_cast<unsigned char*>(&plaintext[0]) + len, &len) != 1) {
        Logger::getLogger()->error("Error: Failed to finalize decryption");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    plaintext_len += len;

    // Resize the plaintext to the actual length
    plaintext.resize(plaintext_len);
    EVP_CIPHER_CTX_free(ctx); // Free the decryption context

    return plaintext;
}

// Function to encrypt a message with a generated IV
std::string encrypt_message(const std::string& plaintext, const std::string& key) {
    std::string iv = generateIV(); // Generate a random IV
    std::string ciphertext = encrypt(plaintext, key, iv); // Encrypt the message

    // Prepend the IV to the ciphertext
    return iv + ciphertext;
}

// Function to decrypt a message that includes the IV
std::string decrypt_message(const std::string& ciphertext_with_iv, const std::string& key) {

    // Extract the IV (first 16 bytes)
    std::string iv = ciphertext_with_iv.substr(0, 16);
    
    // Extract the actual ciphertext (remaining bytes)
    std::string ciphertext = ciphertext_with_iv.substr(16);

    // Decrypt using the extracted IV
    return decrypt(ciphertext, key, iv);
}
