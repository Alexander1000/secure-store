#include <secure-store.h>
#include <io-buffer.h>

namespace SecureStore::Storage
{
    void DB::open(std::string *fileName, std::string *password)
    {
        IOBuffer::IOFileReader fileReader(*fileName);

        auto headerData = (uint8_t*) malloc(DB_HEADER_BYTE_SIZE * sizeof(uint8_t));
        memset(headerData, 0, DB_HEADER_BYTE_SIZE * sizeof(uint8_t));

        fileReader.read((char*) headerData, DB_HEADER_BYTE_SIZE);
    }
}
