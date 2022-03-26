#include <secure-store.h>

namespace SecureStore::View
{
    Application::Application(SecureStore::Storage::DB* db)
    {
        this->db = db;
    }
}
