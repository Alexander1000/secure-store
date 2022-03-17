#include <secure-store.h>

namespace SecureStore::Storage
{
    Record* unpack(DataPack* dataPack)
    {
        int length = dataPack->getLength();
        void* rawData = dataPack->getData();

        if (length == 0 || rawData == nullptr) {
            return nullptr;
        }

        uint8_t bitmask;
        memcpy(&bitmask, rawData, sizeof(uint8_t));

        return nullptr;
    }
}
