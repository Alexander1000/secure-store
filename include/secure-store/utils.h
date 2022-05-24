#ifndef H_SECURE_STORE_UTILS
#define H_SECURE_STORE_UTILS

#include <io-buffer.h>
#include <memory.h>

#ifdef DEBUG_LOGGER
#define INIT_CHAR_STRING(str, length) \
    { \
        SecureStore::StdoutLogger log; \
        log.allocateMemory(#str, length); \
    } \
    char* str = (char*) malloc((length) * sizeof(char));   \
    memset(str, 0, (length) * sizeof(char));
#else
#define INIT_CHAR_STRING(str, length) \
    char* str = (char*) malloc((length) * sizeof(char));   \
    memset(str, 0, (length) * sizeof(char));
#endif

#ifdef DEBUG_LOGGER
#define MEMORY_ALLOC(varName, length) \
    { \
        SecureStore::StdoutLogger log; \
        log.allocateMemory(#varName, length); \
    } \
    void* varName = malloc((length) * sizeof(unsigned char)); \
    memset(varName, 0, (length) * sizeof(unsigned char));
#else
#define MEMORY_ALLOC(varName, length) \
    void* varName = malloc((length) * sizeof(unsigned char)); \
    memset(varName, 0, (length) * sizeof(unsigned char));
#endif

#ifdef DEBUG_LOGGER
#define MEMORY_FREE(varName) \
    { \
        SecureStore::StdoutLogger log; \
        log.freeMemory(#varName); \
    } \
    free(varName);
#else
#define MEMORY_FREE(varName) \
    free(varName);
#endif

namespace SecureStore
{
    class Log
    {
    public:
        virtual void allocateMemory(const char* varName, int length) = 0;
        virtual void freeMemory(const char* varName) = 0;
    };

    class StdoutLogger : public Log
    {
    public:
        void allocateMemory(const char* varName, int length) override;
        void freeMemory(const char* varName) override;
    };

    class FileLogger : public Log
    {
    public:
        FileLogger(const char*);
        void allocateMemory(const char* varName, int length) override;
        void freeMemory(const char* varName) override;

    private:
        IOBuffer::IOFileWriter* fileWriter;
    };
}

#endif
