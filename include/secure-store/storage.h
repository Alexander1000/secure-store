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

        uint32_t getId();
        std::string* getName();
        std::string* getUser();
        std::string* getPassword();
        std::string* getComment();
        std::list<std::string>* getKeywords();
        uint64_t getCreateTime();

    private:
        uint32_t id;
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
