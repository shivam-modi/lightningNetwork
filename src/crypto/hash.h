# SHA256 Hashing Utilities

// This header file provides utility functions for SHA256 hashing
// specifically tailored for Lightning Network cryptographic operations.

#ifndef HASH_H
#define HASH_H

#include <stdint.h>

// Function to compute SHA256 hash of input data
void sha256(const uint8_t *data, size_t length, uint8_t output[32]);

// Function to compute SHA256 hash of a file
int sha256_file(const char *filename, uint8_t output[32]);

// Function to compare two hashes
int compare_hashes(const uint8_t hash1[32], const uint8_t hash2[32]);

#endif // HASH_H
