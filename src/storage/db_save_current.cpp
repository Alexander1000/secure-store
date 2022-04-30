#include <secure-store.h>

namespace SecureStore::Storage
{
    int DB::save()
    {
        this->save(this->fileName, this->user, this->password);
        return 0;
    }
}
