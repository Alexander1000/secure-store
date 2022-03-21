#include <secure-store.h>

#include <openssl/evp.h>
#include <openssl/rand.h>

namespace SecureStore::Storage
{
    DataPack *DB::encode(DataPack* input, std::string* password)
    {
        cipher_params_t *params = (cipher_params_t*) malloc(sizeof(cipher_params_t));
        if (!params) {
            /* Unable to allocate memory on heap*/
            // fprintf(stderr, "ERROR: malloc error: %s\n", strerror(errno));
            return nullptr;
        }

        /* Key to use for encrpytion and decryption */
        unsigned char key[AES_256_KEY_SIZE];

        /* Initialization Vector */
        unsigned char iv[AES_BLOCK_SIZE];

        /* Generate cryptographically strong pseudo-random bytes for key and IV */
        if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
            /* OpenSSL reports a failure, act accordingly */
            // fprintf(stderr, "ERROR: RAND_bytes error: %s\n", strerror(errno));
            return nullptr;
        }

        params->key = key;
        params->iv = iv;

        /* Indicate that we want to encrypt */
        params->encrypt = 1;

        /* Set the cipher type you want for encryption-decryption */
        params->cipher_type = EVP_aes_256_cbc();

        return nullptr;
    }
}
