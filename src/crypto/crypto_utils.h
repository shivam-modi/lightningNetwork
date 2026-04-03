// crypto_utils.h

#ifndef CRYPTO_UTILS_H
#define CRYPTO_UTILS_H

#include <stdint.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/x509.h>

// Function to compute SHA256 hash
void sha256(const char *str, uint8_t hash[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char*)str, strlen(str), hash);
}

// Function to verify RSA signature
int verify_signature(const uint8_t *data, size_t data_len,
                     const uint8_t *signature, size_t signature_len,
                     const char *public_key_pem) {
    EVP_PKEY *pubkey = NULL;
    BIO *bio = BIO_new_mem_buf((void*)public_key_pem, -1);
    if (bio == NULL) return -1;
    pubkey = PEM_read_bio_PublicKey(bio, NULL, NULL, NULL);
    BIO_free(bio);
    if (pubkey == NULL) return -1;

    EVP_MD_CTX *ctx = EVP_MD_CTX_create();
    EVP_VerifyInit_ex(ctx, EVP_sha256(), NULL);
    EVP_VerifyUpdate(ctx, data, data_len);
    int verified = EVP_VerifyFinal(ctx, signature, signature_len, pubkey);
    EVP_MD_CTX_destroy(ctx);
    EVP_PKEY_free(pubkey);

    return verified == 1;
}

#endif // CRYPTO_UTILS_H