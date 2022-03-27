#ifndef H_SECURE_STORE_VIEW
#define H_SECURE_STORE_VIEW

#include <secure-store/storage.h>

namespace SecureStore::View
{
    struct TermSize {
        unsigned short rows;
        unsigned short cols;
    };

    class Application
    {
    public:
        Application(SecureStore::Storage::DB*);
        void render();
        int run();

    private:
        SecureStore::Storage::DB* db;

        void termSize(TermSize*);
    };
}

#endif
