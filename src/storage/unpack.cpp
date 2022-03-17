#include <secure-store.h>

#include <memory>

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

        // id (16-bit) + index_name (16-bit) + ... + createTime (64-bit)
        uint16_t headerSize = 12;

        if ((bitmask & DATA_PACK_USER) != 0) {
            headerSize += 4; // index_user (32-bit)
        }

        if ((bitmask & DATA_PACK_PASSWORD) != 0) {
            headerSize += 4; // index_password (32-bit)
        }

        if ((bitmask & DATA_PACK_COMMENT) != 0) {
            headerSize += 4; // index_comment (32-bit)
        }

        if ((bitmask & DATA_PACK_KEYWORDS) != 0) {
            headerSize++; // count_keywords (8-bit)
        }

        void* headerData = malloc(sizeof(uint8_t) * headerSize);
        memset(headerData, 0, sizeof(uint8_t) * headerSize);
        memcpy(headerData, (uint8_t*) rawData + 1, sizeof(uint8_t) * headerSize);

        uint16_t id;
        memcpy(&id, headerData, sizeof(uint16_t));

        uint16_t nameLength;
        memcpy(&nameLength, (uint8_t*) headerData + 2, sizeof(uint16_t));

        Record* record;
        record = new Record;
        record->setId(id);

        return record;
    }
}
