#include <secure-store.h>

#include <memory>

namespace SecureStore::Storage
{
    DataPack* pack(Record* record)
    {
        if (record == nullptr || record->getId() == 0 || record->getName() == nullptr) {
            return nullptr;
        }

        uint16_t headerSize = 12; // id (16-bit) + index_name (16-bit) + createTime (64-bit)
        uint16_t heapSize = record->getName()->length();
        uint8_t countKeywords = 0;

        uint8_t bitmask = 0;

        if (record->getUser() != nullptr) {
            bitmask |= DATA_PACK_USER;
            headerSize += 4; // user_index (32-bit)
            heapSize += record->getUser()->length();
        }

        if (record->getPassword() != nullptr) {
            bitmask |= DATA_PACK_PASSWORD;
            headerSize += 4; // password_index (32-bit)
            heapSize += record->getPassword()->length();
        }

        if (record->getComment() != nullptr) {
            bitmask |= DATA_PACK_COMMENT;
            headerSize += 4; // comment_index (32-bit)
            heapSize += record->getComment()->length();
        }

        if (record->getKeywords() != nullptr && !record->getKeywords()->empty()) {
            bitmask |= DATA_PACK_KEYWORDS;
            headerSize += 1; // count_keywords (8-bit)
            countKeywords = record->getKeywords()->size();

            for (auto & it : *record->getKeywords()) {
                heapSize += it.length() + 1;
            }
        }

        void* headerData = malloc(sizeof(uint8_t) * headerSize);
        void* keywordsData = nullptr;
        void* heapData = malloc(sizeof(uint8_t) * heapSize);

        if (countKeywords > 0) {
            keywordsData = malloc(countKeywords * sizeof(uint16_t));
        }

        uint16_t currentHeapOffset = 0;
        uint16_t currentHeaderOffset = 0;

        // write id
        {
            uint16_t id = record->getId();
            memcpy(headerData, &id, sizeof(uint16_t));
            currentHeaderOffset += 2;
        }

        // write name
        {
            int length = record->getName()->length();
            // write data in heap
            memcpy(heapData, record->getName()->c_str(), sizeof(char) * length);
            currentHeapOffset += length;
            // write data in header
            memcpy((uint8_t*) headerData + currentHeaderOffset, &length, sizeof(uint16_t));
            currentHeaderOffset += 2;
        }

        if (record->getUser() != nullptr) {
            uint16_t length = record->getUser()->length();
            // write heap
            memcpy((uint8_t*) heapData + currentHeapOffset, record->getUser()->c_str(), length * sizeof(char));
            currentHeapOffset += length;
            // write data in header
            uint32_t index = currentHeaderOffset + (length << 16);
            memcpy((uint8_t*) headerData + currentHeaderOffset, &index, sizeof(uint32_t));
            currentHeaderOffset += 4;
        }

        if (record->getPassword() != nullptr) {
            uint16_t length = record->getPassword()->length();
            // write heap
            memcpy((uint8_t*) heapData + currentHeapOffset, record->getPassword()->c_str(), length * sizeof(char));
            currentHeapOffset += length;
            // write data in header
            uint32_t index = currentHeaderOffset + (length << 16);
            memcpy((uint8_t*) headerData + currentHeaderOffset, &index, sizeof(uint32_t));
            currentHeaderOffset += 4;
        }

        if (record->getComment() != nullptr) {
            uint16_t length = record->getComment()->length();
            // write heap
            memcpy((uint8_t*) heapData + currentHeapOffset, record->getComment()->c_str(), length * sizeof(char));
            currentHeapOffset += length;
            // write data in header
            uint32_t index = currentHeaderOffset + (length << 16);
            memcpy((uint8_t*) headerData + currentHeaderOffset, &index, sizeof(uint32_t));
            currentHeaderOffset += 4;
        }

        if (countKeywords > 0 && keywordsData != nullptr) {
            // write data in header
            memcpy((uint8_t*) headerData + currentHeaderOffset, &countKeywords, sizeof(uint8_t));
            currentHeaderOffset++;

            uint16_t length;
            uint16_t currentKeywordOffset = 0;

            for (auto & it : *record->getKeywords()) {
                // write keywords in heap
                length = it.length();
                memcpy((uint8_t*) heapData + currentHeapOffset, it.c_str(), length * sizeof(uint8_t));

                // write keyword indexes
                uint16_t index = currentHeapOffset;
                memcpy((uint8_t*) keywordsData + currentKeywordOffset, &index, sizeof(uint16_t));

                currentHeapOffset += length + 1;
                currentKeywordOffset += 2;
            }
        }

        // write createTime
        {
            // write data in header
            uint64_t createTime = record->getCreateTime();
            memcpy((uint8_t*) headerData + currentHeaderOffset, &createTime, sizeof(uint64_t));
            currentHeaderOffset += 8;
        }

        return nullptr;
    }
}
