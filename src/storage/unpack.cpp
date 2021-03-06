#include <secure-store.h>

#include <string>
#include <memory>

namespace SecureStore::Storage
{
    Record* unpack(SecureStore::DataPack* dataPack)
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

        // read heap
        uint16_t heapSize = length - rawOffset;
        void* heapData = malloc(sizeof(uint8_t) * heapSize);
        memcpy(heapData, (uint8_t*) rawData + rawOffset, heapSize * sizeof(uint8_t));

        Record* record;
        record = new Record;

        // id
        uint16_t id;
        memcpy(&id, headerData, sizeof(uint16_t));
        record->setId(id);

        uint16_t currentOffsetHeader = 2;

        // read name
        uint16_t nameLength;
        memcpy(&nameLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
        currentOffsetHeader += 2;
        char* strName = (char*) malloc(sizeof(uint8_t) * (nameLength + 1));
        memset(strName, 0, (nameLength + 1) * sizeof(uint8_t));
        memcpy(strName, heapData, nameLength * sizeof(uint8_t));
        std::string* sName;
        sName = new std::string(strName);
        free(strName);
        record->setName(sName);

        // read user_index
        if ((bitmask & DATA_PACK_USER) != 0) {
            uint16_t userOffset;
            memcpy(&userOffset, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            uint16_t userLength;
            memcpy(&userLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            char* strUser = (char*) malloc(sizeof(uint8_t) * (userLength + 1));
            memset(strUser, 0, (userLength + 1) * sizeof(uint8_t));
            memcpy(strUser, (uint8_t*) heapData + userOffset, userLength);

            std::string* sUser;
            sUser = new std::string(strUser);
            record->setUser(sUser);

            free(strUser);
        }

        // read password_index
        if ((bitmask & DATA_PACK_PASSWORD) != 0) {
            uint16_t heapOffset;
            memcpy(&heapOffset, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            uint16_t heapLength;
            memcpy(&heapLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            char* str = (char*) malloc(sizeof(uint8_t) * (heapLength + 1));
            memset(str, 0, (heapLength + 1) * sizeof(uint8_t));
            memcpy(str, (uint8_t*) heapData + heapOffset, heapLength);

            std::string* sPassword;
            sPassword = new std::string(str);
            record->setPassword(sPassword);

            free(str);
        }

        // read comment_index
        if ((bitmask & DATA_PACK_COMMENT) != 0) {
            uint16_t heapOffset;
            memcpy(&heapOffset, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            uint16_t heapLength;
            memcpy(&heapLength, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint16_t));
            currentOffsetHeader += 2;

            char* str = (char*) malloc(sizeof(uint8_t) * (heapLength + 1));
            memset(str, 0, (heapLength + 1) * sizeof(uint8_t));
            memcpy(str, (uint8_t*) heapData + heapOffset, heapLength);

            std::string* sComment;
            sComment = new std::string(str);
            record->setComment(sComment);

            free(str);
        }

        // read keywords
        if ((bitmask & DATA_PACK_KEYWORDS) != 0) {
            // skip key, because already read
            currentOffsetHeader++;

            if (countKeywords > 0) {
                std::list<std::string>* keywords;
                keywords = new std::list<std::string>;

                for (uint8_t i  = 0; i < countKeywords; i++) {
                    // unpack offset in heap
                    uint16_t offset;
                    memcpy(&offset, (uint8_t*) keywordsIndex + i * 2, sizeof(uint16_t));
                    uint16_t length = strlen((char*) heapData + offset);
                    char* str = (char*) malloc((length + 1) * sizeof(char));
                    memset(str, 0, (length + 1) * sizeof(char));
                    memcpy(str, (uint8_t*) heapData + offset, length * sizeof(uint8_t));
                    keywords->emplace_back(std::string(str));
                }

                record->setKeywords(keywords);
            }
        }

        // read createTime
        uint64_t createTime;
        memcpy(&createTime, (uint8_t*) headerData + currentOffsetHeader, sizeof(uint64_t));
        record->setCreateTime(createTime);

        return record;
    }
}
