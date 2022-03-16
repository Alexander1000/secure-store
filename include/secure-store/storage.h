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

    /**
     * index_<name> = offset in heap + length
     * +---------------------------------------------------------------------------------------------+
     * | id | index_name | index_user | index_password | index_comment | count_keywords | createTime |
     * +---------------------------------------------------------------------------------------------+
     * keyword tables:
     * +--------------+
     * | k0 | k1 | k2 |
     * +--------------+
     * heap:
     * +--------------------------------------------------+
     * | plain_text_0 | plain_text_1 | ... | plain_text_N |
     * +--------------------------------------------------+
     */
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
