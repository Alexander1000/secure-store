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

        // write id
        {
            uint16_t id = record->getId();
            memcpy(headerData, &id, sizeof(uint16_t));
        }

        return nullptr;
    }
}
