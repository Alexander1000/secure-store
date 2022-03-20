#include <secure-store.h>
#include <list>

namespace SecureStore::Storage
{
    DB::DB()
    {
        this->records = new std::list<DBRecord>;
    }
}
