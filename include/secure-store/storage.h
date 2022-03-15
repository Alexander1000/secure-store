#ifndef H_SECURE_STORE_DB
#define H_SECURE_STORE_DB

#include <string>

namespace SecureStore::Storage
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
        std::string* comment;
        std::list<std::string>* keywords;
        uint64_t createTime;
    };

    class DataPack
    {
    public:
        DataPack(int, void*);
    private:
        int length;
        void* data;
    };

    DataPack* pack(Record*);
    Record* unpack(DataPack*);
}

#endif