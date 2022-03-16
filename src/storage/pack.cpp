#include <secure-store.h>

#include <memory>

namespace SecureStore::Storage
{
    DataPack* pack(Record* record)
    {
        if (record == nullptr || record->getId() == 0 || record->getName() == nullptr) {
            return nullptr;
        }

        int headerSize = 12; // id (16-bit) + index_name (16-bit) + createTime (64-bit)
        uint16_t heapSize = record->getName()->length();
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

            for (auto & it : *record->getKeywords()) {
                heapSize += it.length() + 1;
            }
        }

        void* headerData = malloc(sizeof(uint8_t) * headerSize);
        void* heapData = malloc(sizeof(uint8_t) * heapSize);

        int currentHeapOffset = 0;
        int currentHeaderOffset = 0;

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
            int length = record->getUser()->length();
            // write heap
            memcpy((uint8_t*) heapData + currentHeapOffset, record->getUser()->c_str(), length * sizeof(char));
            currentHeapOffset += length;
            // write data in header
            uint32_t indexUser = 0;
            memcpy((uint8_t*) headerData + currentHeaderOffset, &indexUser, sizeof(uint32_t));
            currentHeaderOffset += 4;
        }

        return nullptr;
    }
}
