#include <secure-store.h>

namespace SecureStore::Storage
{
    void DB::createEmpty()
    {
        this->records = new std::list<DBRecord*>;
        this->fileName = nullptr;
        this->cipherAlgorithm = CIPHER_ALGORITHM_AES_256_CBC;
    }
}
