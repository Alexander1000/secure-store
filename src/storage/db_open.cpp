#include <secure-store.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    int DB::open(const char* fileName, const char* password)
    {
        this->createEmpty();

        this->fileName = fileName;
        this->password = password;

        IOBuffer::IOFileReader fileReader(fileName);

        auto headerData = (uint8_t*) malloc(DB_HEADER_BYTE_SIZE * sizeof(uint8_t));
        memset(headerData, 0, DB_HEADER_BYTE_SIZE * sizeof(uint8_t));

        int readLength = fileReader.read((char*) headerData, DB_HEADER_BYTE_SIZE);
        if (readLength < DB_HEADER_BYTE_SIZE) {
            // error: incorrect file length
            return 1;
        }

        memcpy(this->format, headerData, 3 * sizeof(uint8_t));
        if (std::string((char*) this->format) != "xdb") {
            // error: unsupported format
            return 2;
        }

        memcpy(&this->cipherAlgorithm, headerData + 3, sizeof(uint8_t));
        if (this->cipherAlgorithm != CIPHER_ALGORITHM_AES_256_CBC) {
            // error: unsupported cipher algorithm
            return 3;
        }

        memcpy(&this->verMajor, headerData + 4, sizeof(uint16_t));
        if (this->verMajor > VERSION_MAJOR) {
            // error: unsupported version
            return 4;
        }

        memcpy(&this->verMinor, headerData + 6, sizeof(uint16_t));

        auto checksum = (uint8_t*) malloc(16 * sizeof(uint8_t));
        memcpy(checksum, headerData + 8, 16 * sizeof(uint8_t));

        unsigned char iv[AES_BLOCK_SIZE];
        readLength = fileReader.read((char*) iv, AES_BLOCK_SIZE);
        if (readLength != AES_BLOCK_SIZE) {
            // error: corrupted file
            return 5;
        }

        // read data
        int ioBufferSize = 4096;
        IOBuffer::IOMemoryBuffer memoryBuffer;
        auto buffer = (char*) malloc(ioBufferSize * sizeof(uint8_t));
        bool first = true;
        bool empty = false;

        do {
            memset(buffer, 0, ioBufferSize * sizeof(uint8_t));
            readLength = fileReader.read(buffer, ioBufferSize);

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
            return 0;
        }

        auto params = (SecureStore::Crypto::cipher_params_t*) malloc(sizeof(SecureStore::Crypto::cipher_params_t));
        unsigned char key[AES_256_KEY_SIZE];
        memset(key, 0, sizeof(key));
        int passwordLength = strlen(password);
        if (passwordLength > 32) {
            passwordLength = 32;
        }
        memcpy(key, password, passwordLength);
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

            auto heapData = malloc(length * sizeof(uint8_t));
            memcpy(heapData, (uint8_t*) decryptedData + heapOffsetStart + offset, length * sizeof(uint8_t));

            SecureStore::DataPack dataPackSecret(length, heapData);
            Record* record = unpack(&dataPackSecret);
            this->addRecord(record);

            free(heapData);
        }

        return 0;
    }
}
