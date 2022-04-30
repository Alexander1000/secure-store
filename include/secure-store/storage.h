#ifndef H_SECURE_STORE_DB
#define H_SECURE_STORE_DB

#include <string>
#include <list>
#include <secure-store/data-pack.h>

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

    const uint8_t DB_RECORD_STATUS_ACTIVE = 0;

    class DBRecord
    {
    public:
        DBRecord();
        explicit DBRecord(Record*);
        Record* getRecord();
        uint8_t getStatus();

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

    SecureStore::DataPack* pack(Record*);

    Record* unpack(SecureStore::DataPack*);

    const uint8_t CIPHER_ALGORITHM_AES_256_CBC = 1;

    const uint8_t DB_HEADER_BYTE_SIZE = 24;

    /**
     * Format stored data
     * ===================================================
     * signature (24 bytes):
     * +--------+-------------+-----------+-----------+---------------+
     * | FORMAT | CIPHER_ALGO | VER_MAJOR | VER_MINOR | CHECKSUM(md5) |
     * +--------+-------------+-----------+-----------+---------------+
     * format (24-bit) - simple identifier
     * cipher_algo (8-bit) - cipher algorithm, identifier
     * ver_major (16-bit) - major version
     * ver_minor (16-bit) - minor version
     * checksum (128-bit) - checksum of ciphered content
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
        void addRecord(Record*);

        int open(const char* fileName, const char* user, const char* password); // open file

        int save(); // save opened file

        void save(const char* fileName, const char* user, const char* key); // save new file

        std::list<DBRecord*>* getRecords();

    private:
        std::list<DBRecord*>* records;

        const char* fileName;
        const char* user;
        const char* password;

        unsigned char* format;

        uint8_t cipherAlgorithm;
        uint16_t verMajor;
        uint16_t verMinor;

        SecureStore::DataPack* pack();
    };
}

#endif
