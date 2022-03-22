#include <secure-store.h>
#include <list>
#include <memory>

namespace SecureStore::Storage
{
    DB::DB()
    {
        this->records = new std::list<DBRecord*>;
        this->fileName = nullptr;
    }

    void DB::addRecord(Record *record)
    {
        DBRecord* dbRecord = nullptr;
        dbRecord = new DBRecord(record);
        this->records->emplace_back(dbRecord);
    }

    DataPack* DB::pack()
    {
        std::list<DataPack*> dataPackList;

        uint16_t heapSize = 0;

        // pack all secrets
        for (auto & dbRecord : *this->records) {
            if (dbRecord->getRecord() != nullptr) {
                DataPack* dp = SecureStore::Storage::pack(dbRecord->getRecord());
                dataPackList.emplace_back(dp);
                heapSize += dp->getLength();
            }
        }

        uint16_t headerSize = dataPackList.size() * 5; // (offset(count) + length + status) * count

        void* rawData = malloc(headerSize + heapSize);

        uint16_t heapOffset = 0;
        bool first = true;
        uint16_t index = 0;

        // pack all secrets
        for (auto & dbRecord : *this->records) {
            if (dbRecord->getRecord() != nullptr) {
                DataPack* dp = SecureStore::Storage::pack(dbRecord->getRecord());
                uint16_t length = dp->getLength();

                // write heap
                memcpy((uint8_t*) rawData + heapSize + heapOffset, dp->getData(), length);

                uint16_t indexOffset = index * 5;

                // write header
                uint16_t pointer;
                if (first) {
                    first = false;
                    pointer = dataPackList.size();
                } else {
                    pointer = heapOffset;
                }
                // write offset(count) in header
                memcpy((uint8_t*) rawData + indexOffset, &pointer, sizeof(uint16_t));
                // write length data in header
                memcpy((uint8_t*) rawData + indexOffset + sizeof(uint16_t), &length, sizeof(uint16_t));
                // write status in header
                uint8_t status = dbRecord->getStatus();
                memcpy((uint8_t*) rawData + indexOffset + 2 * sizeof(uint16_t), &status, sizeof(uint8_t));

                // move offset in next block
                heapOffset += length;
                // move offset in header
                index++;
            }
        }

        return new DataPack(headerSize + heapSize, rawData);
    }
}
