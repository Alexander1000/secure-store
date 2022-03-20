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
        std::list<DataPack*> dbRecords;

        // pack all secrets
        for (auto & dbRecord : *this->records) {
            if (dbRecord->getRecord() != nullptr) {
                dbRecords.emplace_back(SecureStore::Storage::pack(dbRecord->getRecord()));
            }
        }

        return nullptr;
    }
}
