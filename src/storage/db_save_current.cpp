#include <secure-store.h>

namespace SecureStore::Storage
{
    int DB::save()
    {
        this->save(this->_fileName, this->_user, this->_password);
        return 0;
    }
}
