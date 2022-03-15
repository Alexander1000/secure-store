#include <secure-store.h>

namespace SecureStore::Storage
{
    Record::Record()
    {
        this->name = nullptr;
        this->user = nullptr;
        this->password = nullptr;
        this->comment = nullptr;
        this->keywords = nullptr;
        this->createTime = 0;
    }
}
