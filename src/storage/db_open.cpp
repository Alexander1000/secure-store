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

        fileReader.read((char*) headerData, DB_HEADER_BYTE_SIZE);

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
    }
}