#include <secure-store.h>

namespace SecureStore::Storage
{
    void DB::save(std::string* fileName, std::string* key)
    {
        this->fileName = fileName;

        uint8_t* headerData = (uint8_t*) malloc(24 * sizeof(uint8_t));
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
        auto md5Hash = hash_md5(rawSecrets);
    }
}
