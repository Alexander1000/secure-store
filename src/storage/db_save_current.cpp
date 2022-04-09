#include <secure-store.h>

namespace SecureStore::Storage
{
    int DB::save()
    {
        this->save(this->fileName, this->password);
        return 0;
    }
}
