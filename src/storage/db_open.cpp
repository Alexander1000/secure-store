#include <secure-store.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    void DB::open(std::string *fileName, std::string *password)
    {
        this->createEmpty();

        IOBuffer::IOFileReader fileReader(*fileName);

        auto headerData = (uint8_t*) malloc(DB_HEADER_BYTE_SIZE * sizeof(uint8_t));
        memset(headerData, 0, DB_HEADER_BYTE_SIZE * sizeof(uint8_t));

        int readLength = fileReader.read((char*) headerData, DB_HEADER_BYTE_SIZE);
        if (readLength < DB_HEADER_BYTE_SIZE) {
            // error: incorrect file length
            return;
        }

        memcpy(this->format, headerData, 3 * sizeof(uint8_t));
        if (std::string((char*) this->format) != "xdb") {
            // error: unsupported format
            return;
        }

        memcpy(&this->cipherAlgorithm, headerData + 3, sizeof(uint8_t));
        if (this->cipherAlgorithm != CIPHER_ALGORITHM_AES_256_CBC) {
            // error: unsupported cipher algorithm
            return;
        }

        memcpy(&this->verMajor, headerData + 4, sizeof(uint16_t));
        if (this->verMajor > VERSION_MAJOR) {
            // error: unsupported version
            return;
        }

        memcpy(&this->verMinor, headerData + 6, sizeof(uint16_t));

        auto checksum = (uint8_t*) malloc(16 * sizeof(uint8_t));
        memcpy(checksum, headerData + 8, 16 * sizeof(uint8_t));

        unsigned char iv[AES_BLOCK_SIZE];
        readLength = fileReader.read((char*) iv, AES_BLOCK_SIZE);
        if (readLength != AES_BLOCK_SIZE) {
            // error: corrupted file
            return;
        }

        // read data
        int ioBufferSize = 4096;
        IOBuffer::IOMemoryBuffer memoryBuffer;
        auto buffer = (char*) malloc(ioBufferSize * sizeof(uint8_t));

        do {
            memset(buffer, 0, ioBufferSize * sizeof(uint8_t));
            readLength = fileReader.read(buffer, ioBufferSize);

            if (readLength > 0) {
                memoryBuffer.write(buffer, readLength);
            }

            if (readLength != ioBufferSize) {
                break;
            }
        } while (true);

        auto params = (SecureStore::Crypto::cipher_params_t*) malloc(sizeof(SecureStore::Crypto::cipher_params_t));
        unsigned char key[AES_256_KEY_SIZE];
        memset(key, 0, sizeof(key));
        int passwordLength = password->length();
        if (passwordLength > 32) {
            passwordLength = 32;
        }
        memcpy(key, password->c_str(), passwordLength);
        params->key = key;
        params->iv = iv;
        params->encrypt = 0;
        params->cipher_type = EVP_aes_256_cbc();

        void* data = malloc(memoryBuffer.length());
        memset(data, 0, memoryBuffer.length());
        memoryBuffer.read((char*) data, memoryBuffer.length());
        DataPack dataPack(memoryBuffer.length(), data);

        auto decrypted = SecureStore::Crypto::encrypt_decrypt(params, &dataPack);
        auto hashDecrypted = SecureStore::Crypto::hash_md5(decrypted);

        bool equal = true;
        for (uint8_t i = 0; i < 16; i++) {
            if (checksum[i] != hashDecrypted[i]) {
                equal = false;
                break;
            }
        }

        if (!equal) {
            // error: wrong decrypt
            return;
        }

        int headBlockRecordSize = 5;
        auto decryptedData = decrypted->getData();
        uint16_t countRecords;
        memcpy(&countRecords, decryptedData, sizeof(uint16_t));

        for (uint16_t i = 0; i < countRecords; i++) {
            // unpack data
        }
    }
}
