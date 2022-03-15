#ifndef H_SECURE_STORE_DB
#define H_SECURE_STORE_DB

#include <string>

namespace SecureStore
{
    class DB
    {
    public:
        DB();
        void createEmpty();
    };

    class Record
    {
    public:
        Record();

    private:
        std::string* name;
        std::string* user;
        std::string* password;
    };
}

#endif
