#include <secure-store.h>
#include <list>

namespace SecureStore::Storage
{
    DB::DB()
    {
        this->records = new std::list<DBRecord*>;
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

        return nullptr;
    }
}
