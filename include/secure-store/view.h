#ifndef H_SECURE_STORE_VIEW
#define H_SECURE_STORE_VIEW

#include <secure-store/storage.h>

namespace SecureStore::View
{
    class Application
    {
    public:
        Application(SecureStore::Storage::DB*);
        void render();

    private:
        SecureStore::Storage::DB* db;
    };
}

#endif
