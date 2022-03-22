#include <secure-store.h>

namespace SecureStore::Storage
{
    void DB::save(std::string* fileName, std::string* key)
    {
        this->fileName = fileName;
        auto rawSecrets = this->pack();
    }
}
