#include <secure-store.h>

namespace SecureStore::Storage
{
    DataPack* pack(Record* record)
    {
        if (record == nullptr) {
            return nullptr;
        }

        int headerSize = 12; // id (16-bit) + index_name (16-bit) + createTime (64-bit)
        uint8_t bitmask = 0;

        if (record->getUser() != nullptr) {
            bitmask |= DATA_PACK_USER;
            headerSize += 4; // user_index (32-bit)
        }

        if (record->getPassword() != nullptr) {
            bitmask |= DATA_PACK_PASSWORD;
            headerSize += 4; // password_index (32-bit)
        }

        if (record->getComment() != nullptr) {
            bitmask |= DATA_PACK_COMMENT;
            headerSize += 4; // comment_index (32-bit)
        }

        if (record->getKeywords() != nullptr && !record->getKeywords()->empty()) {
            bitmask |= DATA_PACK_KEYWORDS;
            headerSize += 1; // count_keywords (8-bit)
        }

        int size = 0; // 4 (id)
        return nullptr;
    }
}
