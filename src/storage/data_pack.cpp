#include <secure-store.h>

namespace SecureStore::Storage
{
    DataPack::DataPack(int length, void* data)
    {
        this->length = length;
        this->data = data;
    }
}
