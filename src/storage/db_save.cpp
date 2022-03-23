#include <secure-store.h>
#include <openssl/rand.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    void DB::save(std::string* fileName, std::string* password)
    {
        this->fileName = fileName;

        auto headerData = (uint8_t*) malloc(24 * sizeof(uint8_t));
        memset(headerData, 0, 24 * sizeof(uint8_t));

        // format
        memcpy(headerData, this->format, 3 * sizeof(uint8_t));
        // cipher algorithm
        memcpy(headerData + 3, &this->cipherAlgorithm, sizeof(uint8_t));
        // major version
        memcpy(headerData + 4, &this->verMajor, sizeof(uint16_t));
        // minor version
        memcpy(headerData + 6, &this->verMinor, sizeof(uint16_t));

        auto rawSecrets = this->pack();
        auto md5Hash = SecureStore::Crypto::hash_md5(rawSecrets);
        memcpy(headerData + 8, md5Hash, 16 * sizeof(uint8_t));

        if (this->cipherAlgorithm == CIPHER_ALGORITHM_AES_256_CBC) {
            auto params = (SecureStore::Crypto::cipher_params_t*) malloc(sizeof(SecureStore::Crypto::cipher_params_t));
            unsigned char key[AES_256_KEY_SIZE];
            memset(key, 0, sizeof(key));
            int passwordLength = password->length();
            if (passwordLength > 32) {
                passwordLength = 32;
            }
            memcpy(key, password->c_str(), passwordLength);
            unsigned char iv[AES_BLOCK_SIZE];
            RAND_bytes(iv, sizeof(iv));
            params->key = key;
            params->iv = iv;
            params->encrypt = 1;
            params->cipher_type = EVP_aes_256_cbc();
            auto encryptedSecrets = encrypt_decrypt(params, rawSecrets);

            IOBuffer::IOFileWriter fileWriter(*this->fileName);
            fileWriter.write((char*) headerData, 24);
            fileWriter.write((char*) iv, AES_BLOCK_SIZE);
            fileWriter.write((char*) encryptedSecrets->getData(), encryptedSecrets->getLength());
        }
    }
}
