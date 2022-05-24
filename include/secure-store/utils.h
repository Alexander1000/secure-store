#ifndef H_SECURE_STORE_UTILS
#define H_SECURE_STORE_UTILS

#include <io-buffer.h>
#include <memory.h>

#if DEBUG_LOGGER_TYPE == 1
    #define LOGGER_INIT() SecureStore::StdoutLogger log;
#elif DEBUG_LOGGER_TYPE == 2
    #define LOGGER_INIT() SecureStore::FileLogger log(DEBUG_LOGGER_FILE_PATH);
#else
    #error Unsupported debug logger type
#endif

#ifdef DEBUG_LOGGER
#define INIT_CHAR_STRING(str, length) \
    { \
        LOGGER_INIT(); \
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
        LOGGER_INIT(); \
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
        LOGGER_INIT(); \
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
