#include <secure-store.h>
#include <openssl/rand.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    int DB::save()
    {
        this->save(this->fileName, this->password);
        return 0;
    }
}
