#include <secure-store.h>

namespace SecureStore::Storage
{
    void DB::save(std::string* fileName, std::string* key)
    {
        this->fileName = fileName;

        uint8_t* headerData = (uint8_t*) malloc(24 * sizeof(uint8_t));
        memset(headerData, 0, 24 * sizeof(uint8_t));

        auto rawSecrets = this->pack();
        auto md5Hash = hash_md5(rawSecrets);
    }
}
