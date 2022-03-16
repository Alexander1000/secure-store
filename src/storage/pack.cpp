#include <secure-store.h>

namespace SecureStore::Storage
{
    DataPack* pack(Record* record)
    {
        if (record == nullptr) {
            return nullptr;
        }

        uint8_t bitmask = 0;

        if (record->getUser() != nullptr) {
            bitmask &= DATA_PACK_USER;
        }

        if (record->getPassword() != nullptr) {
            bitmask &= DATA_PACK_PASSWORD;
        }

        if (record->getComment() != nullptr) {
            bitmask &= DATA_PACK_COMMENT;
        }

        if (record->getKeywords() != nullptr && !record->getKeywords()->empty()) {
            bitmask &= DATA_PACK_KEYWORDS;
        }

        int size = 0; // 4 (id)
        return nullptr;
    }
}
