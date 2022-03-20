#include <secure-store.h>

namespace SecureStore::Storage
{
    DBRecord::DBRecord()
    {
        this->record = nullptr;
        this->status = DB_RECORD_STATUS_ACTIVE;
    }

    DBRecord::DBRecord(Record *record)
    {
        this->record = record;
        this->status = DB_RECORD_STATUS_ACTIVE;
    }

    Record* DBRecord::getRecord()
    {
        return this->record;
    }

    uint8_t DBRecord::getStatus()
    {
        return this->status;
    }
}
