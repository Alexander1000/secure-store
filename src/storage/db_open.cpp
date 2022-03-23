#include <secure-store.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    void DB::open(std::string *fileName, std::string *password)
    {
        this->createEmpty();

        IOBuffer::IOFileReader fileReader(*fileName);

        auto headerData = (uint8_t*) malloc(DB_HEADER_BYTE_SIZE * sizeof(uint8_t));
        memset(headerData, 0, DB_HEADER_BYTE_SIZE * sizeof(uint8_t));

        fileReader.read((char*) headerData, DB_HEADER_BYTE_SIZE);

        memcpy(this->format, headerData, 3 * sizeof(uint8_t));
        if (std::string((char*) this->format) == "xdb") {
            // it is xdb
        }
    }
}
