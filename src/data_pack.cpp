#include <secure-store.h>

namespace SecureStore
{
    DataPack::DataPack(int length, void* data)
    {
        this->length = length;
        this->data = data;
    }

    int DataPack::getLength()
    {
        return this->length;
    }

    void* DataPack::getData()
    {
        return this->data;
    }
}
