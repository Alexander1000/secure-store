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
     * index_<name> (32-bit) = offset in heap (16-bit) + length (16-bit)
     * bit mask signature (8-bit)
     * +------+----------+---------+----------+
     * | USER | PASSWORD | COMMENT | KEYWORDS |
     * +------+----------+---------+----------+
     * header:
     * +----+------------+------------+----------------+---------------+----------------+------------+
     * | id | index_name | index_user | index_password | index_comment | count_keywords | createTime |
     * +----+------------+------------+----------------+---------------+----------------+------------+
     * index_name (16-bit) - have always offset - 0, than skip it
     * keyword tables (offsets in heap):
     * +----+----+----+
     * | k0 | k1 | k2 |
     * +----+----+----+
     * heap:
     * +--------------+--------------+-----+--------------+
     * | plain_text_0 | plain_text_1 | ... | plain_text_N |
     * +--------------+--------------+-----+--------------+
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
