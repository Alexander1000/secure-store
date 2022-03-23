#include <secure-store.h>

namespace SecureStore::Storage
{
    SecureStore::DataPack* DB::encrypt(std::string* key)
    {
        // todo: mixin signature, headers, checksum
        return this->encode(this->pack(), key);
    }
}
