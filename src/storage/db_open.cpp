#include <secure-store.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    int DB::open(const char* fileName, const char* user, const char* password)
    {
        DEBUG_MESSAGE("Storage::DB::open <called>");

        this->createEmpty();

        this->_fileName = fileName;
        this->_user = user;
        this->_password = password;

        auto fileReader = new IOBuffer::IOFileReader(fileName);

        MEMORY_ALLOC(headerData, DB_HEADER_BYTE_SIZE);

        int readLength = fileReader->read((char*) headerData, DB_HEADER_BYTE_SIZE);
        if (readLength < DB_HEADER_BYTE_SIZE) {
            // error: incorrect file length
            delete fileReader;
            return 1;
        }

        memcpy(this->format, headerData, 3 * sizeof(uint8_t));
        if (std::string((char*) this->format) != "xdb") {
            // error: unsupported format
            delete fileReader;
            return 2;
        }

        memcpy(&this->cipherAlgorithm, (char*) headerData + 3, sizeof(uint8_t));
        if (this->cipherAlgorithm != CIPHER_ALGORITHM_AES_256_CBC) {
            // error: unsupported cipher algorithm
            delete fileReader;
            return 3;
        }

        memcpy(&this->verMajor, (char*) headerData + 4, sizeof(uint16_t));
        if (this->verMajor > VERSION_MAJOR) {
            // error: unsupported version
            delete fileReader;
            return 4;
        }

        memcpy(&this->verMinor, (char*) headerData + 6, sizeof(uint16_t));

        auto checksum = (uint8_t*) malloc(16 * sizeof(uint8_t));
        memcpy(checksum, (char*) headerData + 8, 16 * sizeof(uint8_t));

        this->_salt = (unsigned char*) malloc(sizeof(unsigned char) * DB_HEADER_SALT_BYTE_SIZE);
        memset(this->_salt, 0, sizeof(unsigned char) * DB_HEADER_SALT_BYTE_SIZE);
        memcpy(this->_salt, (char*) headerData + DB_HEADER_BYTE_SIZE - DB_HEADER_SALT_BYTE_SIZE, DB_HEADER_SALT_BYTE_SIZE * sizeof(unsigned char));

        MEMORY_FREE(headerData);

        // read data
        int ioBufferSize = 4096;
        IOBuffer::IOMemoryBuffer memoryBuffer;
        auto buffer = (char*) malloc(ioBufferSize * sizeof(uint8_t));
        bool first = true;
        bool empty = false;

        do {
            memset(buffer, 0, ioBufferSize * sizeof(uint8_t));
            readLength = fileReader->read(buffer, ioBufferSize);

            if (readLength == 0 && first) {
                empty = true;
                break;
            }

            if (readLength > 0) {
                memoryBuffer.write(buffer, readLength);
            }

            if (readLength != ioBufferSize) {
                break;
            }

            first = false;
        } while (true);

        if (empty) {
            delete fileReader;
            return 0;
        }

        delete fileReader;

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
        params->encrypt = 0;
        params->cipher_type = EVP_aes_256_cbc();

        void* data = malloc(memoryBuffer.length());
        memset(data, 0, memoryBuffer.length());
        memoryBuffer.read((char*) data, memoryBuffer.length());
        DataPack dataPack(memoryBuffer.length(), data);

        auto decrypted = SecureStore::Crypto::encrypt_decrypt(params, &dataPack);
        if (decrypted == nullptr) {
            DEBUG_MESSAGE("error: Crypto::encrypt_decrypt returns nullptr");
            return 6;
        }

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
            return 7;
        }

        int headBlockRecordSize = 5;
        auto decryptedData = decrypted->getData();
        uint16_t countRecords;
        memcpy(&countRecords, decryptedData, sizeof(uint16_t));

        uint16_t offset;
        uint16_t length;
        uint8_t status;

        uint16_t heapOffsetStart = 0;

        for (uint16_t i = 0; i < countRecords; i++) {
            memcpy(&offset, (uint8_t*) decryptedData + i * headBlockRecordSize, sizeof(uint16_t));
            memcpy(&length, (uint8_t*) decryptedData + i * headBlockRecordSize + 2, sizeof(uint16_t));
            memcpy(&status, (uint8_t*) decryptedData + i * headBlockRecordSize + 4, sizeof(uint8_t));

            if (i == 0) {
                // first element offset = count elements
                heapOffsetStart = offset * headBlockRecordSize;
                // first element always have offset = 0
                offset = 0;
            }

            MEMORY_ALLOC(heapData, length);
            memcpy(heapData, (uint8_t*) decryptedData + heapOffsetStart + offset, length * sizeof(uint8_t));

            SecureStore::DataPack dataPackSecret(length, heapData);
            Record* record = unpack(&dataPackSecret);
            this->addRecord(record);

            MEMORY_FREE(heapData);
        }

        return 0;
    }
}
