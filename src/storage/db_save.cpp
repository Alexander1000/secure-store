#include <secure-store.h>
#include <openssl/rand.h>
#include <io-buffer.h>
#include <memory.h>

namespace SecureStore::Storage
{
    void DB::save(const char* fileName, const char* user, const char* password)
    {
        this->_fileName = fileName;
        this->_user = user;
        this->_password = password;

        this->_salt = (unsigned char*) malloc(sizeof(unsigned char) * DB_HEADER_SALT_BYTE_SIZE);
        memset(this->_salt, 0, sizeof(unsigned char) * DB_HEADER_SALT_BYTE_SIZE);
        RAND_bytes(this->_salt, sizeof(unsigned char) * DB_HEADER_SALT_BYTE_SIZE);

        auto headerData = (uint8_t*) malloc(DB_HEADER_BYTE_SIZE * sizeof(uint8_t));
        memset(headerData, 0, DB_HEADER_BYTE_SIZE * sizeof(uint8_t));

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

        // write salt
        memcpy(headerData + DB_HEADER_BYTE_SIZE - DB_HEADER_SALT_BYTE_SIZE, this->_salt, DB_HEADER_SALT_BYTE_SIZE * sizeof(unsigned char));

        if (this->cipherAlgorithm == CIPHER_ALGORITHM_AES_256_CBC) {
            auto keyData = SecureStore::Crypto::prepare_credentials(this->_user, this->_password, (const char*) this->_salt);

            auto params = (SecureStore::Crypto::cipher_params_t*) malloc(sizeof(SecureStore::Crypto::cipher_params_t));

            unsigned char key[AES_256_KEY_SIZE];
            memset(key, 0, sizeof(key));
            memcpy(key, keyData->getData(), AES_256_KEY_SIZE);

            unsigned char iv[AES_BLOCK_SIZE];
            memset(iv, 0, sizeof(iv));
            memcpy(iv, (unsigned char*) keyData->getData() + AES_256_KEY_SIZE, AES_BLOCK_SIZE);

            params->key = key;
            params->iv = iv;
            params->encrypt = 1;
            params->cipher_type = EVP_aes_256_cbc();

            SecureStore::DataPack* encryptedSecrets = nullptr;
            if (rawSecrets->getLength() > 0) {
                encryptedSecrets = encrypt_decrypt(params, rawSecrets);
            }

            IOBuffer::IOFileWriter* fileWriter = nullptr;
            fileWriter = new IOBuffer::IOFileWriter(this->_fileName, "w+");
            fileWriter->write((char*) headerData, DB_HEADER_BYTE_SIZE);
            if (encryptedSecrets != nullptr) {
                fileWriter->write((char *) encryptedSecrets->getData(), encryptedSecrets->getLength());
            }
            delete fileWriter;
        }
    }
}
