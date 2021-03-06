#include <secure-store.h>

namespace SecureStore::Storage
{
    void DB::createEmpty()
    {
        this->records = new std::list<DBRecord*>;
        this->_fileName = nullptr;
        this->_user = nullptr;
        this->_password = nullptr;
        this->cipherAlgorithm = CIPHER_ALGORITHM_AES_256_CBC;
        this->verMajor = VERSION_MAJOR;
        this->verMinor = VERSION_MINOR;
        this->format = new unsigned char[3]{'x', 'd', 'b'};
    }
}
