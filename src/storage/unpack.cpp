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

        // read bitmask
        uint8_t bitmask;
        memcpy(&bitmask, rawData, sizeof(uint8_t));

        // id (16-bit) + index_name (16-bit) + ... + createTime (64-bit)
        uint16_t headerSize = 12;

        uint16_t offsetKeywords = 4; // id (16-bit) + index_name (16-bit)

        if ((bitmask & DATA_PACK_USER) != 0) {
            headerSize += 4; // index_user (32-bit)
            offsetKeywords += 4;
        }

        if ((bitmask & DATA_PACK_PASSWORD) != 0) {
            headerSize += 4; // index_password (32-bit)
            offsetKeywords += 4;
        }

        if ((bitmask & DATA_PACK_COMMENT) != 0) {
            headerSize += 4; // index_comment (32-bit)
            offsetKeywords += 4;
        }

        if ((bitmask & DATA_PACK_KEYWORDS) != 0) {
            headerSize++; // count_keywords (8-bit)
        }

        uint16_t rawOffset = 1; // skip bitmask

        // read header
        void* headerData = malloc(sizeof(uint8_t) * headerSize);
        memset(headerData, 0, sizeof(uint8_t) * headerSize);
        memcpy(headerData, (uint8_t*) rawData + 1, sizeof(uint8_t) * headerSize);
        rawOffset += headerSize; // skip header block

        // read keywords data
        void* keywordsIndex = nullptr;
        uint8_t countKeywords = 0;
        if ((bitmask & DATA_PACK_KEYWORDS) != 0) {
            memcpy(&countKeywords, (uint8_t*) headerData + offsetKeywords, sizeof(uint8_t));
            if (countKeywords > 0) {
                keywordsIndex = malloc(countKeywords * sizeof(uint16_t));
                memset(keywordsIndex, 0, countKeywords * sizeof(uint16_t));
                memcpy(keywordsIndex, (uint8_t*) rawData + rawOffset, countKeywords * sizeof(uint16_t));
                rawOffset += countKeywords * sizeof(uint16_t); // skip keywords block
            }
        }

        // id
        uint16_t id;
        memcpy(&id, headerData, sizeof(uint16_t));

        uint16_t currentOffsetHeader = 2;

        // read name
        uint16_t nameLength;
        memcpy(&nameLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
        currentOffsetHeader += 2;

        // read user_index
        if ((bitmask & DATA_PACK_USER) != 0) {
            uint16_t userOffset;
            memcpy(&userOffset, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            uint16_t userLength;
            memcpy(&userLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;
        }

        Record* record;
        record = new Record;
        record->setId(id);

        return record;
    }
}