#ifndef H_SECURE_STORE_DB
#define H_SECURE_STORE_DB

#include <string>

namespace SecureStore::Storage
{
    class Record
    {
    public:
        Record();

        uint16_t getId();
        std::string* getName();
        std::string* getUser();
        std::string* getPassword();
        std::string* getComment();
        std::list<std::string>* getKeywords();
        uint64_t getCreateTime();

        void setId(uint16_t);
        void setName(std::string*);
        void setUser(std::string*);
        void setPassword(std::string*);
        void setComment(std::string*);
        void setKeywords(std::list<std::string>*);
        void setCreateTime(uint64_t);

    private:
        uint16_t id;
        std::string* name;
        std::string* user;
        std::string* password;
        std::string* comment;
        std::list<std::string>* keywords;
        uint64_t createTime;
    };

    class DBRecord
    {
    public:
        DBRecord();

    private:
        Record* record;
        uint8_t status;
    };

    const uint8_t DATA_PACK_USER     = 0x1;
    const uint8_t DATA_PACK_PASSWORD = 0x2;
    const uint8_t DATA_PACK_COMMENT  = 0x4;
    const uint8_t DATA_PACK_KEYWORDS = 0x8;

    /**
     * bit mask signature (8-bit)
     * +------+----------+---------+----------+
     * | USER | PASSWORD | COMMENT | KEYWORDS |
     * +------+----------+---------+----------+
     * header:
     * +----+------------+------------+----------------+---------------+----------------+------------+
     * | id | index_name | index_user | index_password | index_comment | count_keywords | createTime |
     * +----+------------+------------+----------------+---------------+----------------+------------+
     * id (16-bit)
     * index_name (16-bit) - only length of string, because always offset - 0, than skip it
     * index_<name> (32-bit) = offset in heap (16-bit) + length (16-bit)
     * count_keywords (8-bit)
     * createTime (64-bit)
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

        int getLength();
        void* getData();
    private:
        int length;
        void* data;
    };

    DataPack* pack(Record*);

    Record* unpack(DataPack*);

    /**
     * Format stored data
     * ===================================================
     * signature:
     * +--------+-----------+-----------+----------+
     * | FORMAT | VER_MAJOR | VER_MINOR | CHECKSUM |
     * +--------+-----------+-----------+----------+
     * format (32-bit) - simple identifier
     * ver_major (16-bit) - major version
     * ver_minor (16-bit) - minor version
     * checksum (32-bit) - checksum of ciphered content
     * ===================================================
     * ciphered block:
     * header:
     * +---------------+--------+--------+
     * | OFFSET(COUNT) | LENGTH | STATUS |
     * +---------------+--------+--------+
     * offset (16-bit) - offset in heap data, but first element means is count records in table (offset always equal 0)
     * length (16-bit) - length of data
     * status (8-bit) - ACTIVE(0); HIDE(1) - reserved
     * ===================================================
     * heap data:
     * +--------+--------+-----+--------+
     * | DATA_0 | DATA_1 | ... | DATA_N |
     * +--------+--------+-----+--------+
     */
    class DB
    {
    public:
        DB();
        void createEmpty();

    private:
        std::list<DBRecord>* records;
    };
}

#endif
