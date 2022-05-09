#ifndef H_SECURE_STORE_CRYPTO
#define H_SECURE_STORE_CRYPTO

#include <openssl/evp.h>
#include <secure-store/data-pack.h>

/* 32 byte key (256 bit key) */
#define AES_256_KEY_SIZE 32
/* 16 byte block size (128 bits) */
#define AES_BLOCK_SIZE 16

#define BUFSIZE 100

namespace SecureStore::Crypto
{
    typedef struct _cipher_params_t{
        unsigned char* key;
        unsigned char* iv;
        unsigned int encrypt;
        const EVP_CIPHER* cipher_type;
    } cipher_params_t;

    SecureStore::DataPack* encrypt_decrypt(cipher_params_t* params, SecureStore::DataPack* input);

    uint8_t* hash_md5(SecureStore::DataPack* input);

    uint8_t* hash_sha3_512(SecureStore::DataPack* input);
}

#endif
