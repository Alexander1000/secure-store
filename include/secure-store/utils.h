#ifndef H_SECURE_STORE_UTILS
#define H_SECURE_STORE_UTILS

#include <io-buffer.h>
#include <memory.h>

#if DEBUG_LOGGER_TYPE == 1
    #define LOGGER_INIT() SecureStore::StdoutLogger* log = new SecureStore::StdoutLogger;
#elif DEBUG_LOGGER_TYPE == 2
    #define LOGGER_INIT() SecureStore::FileLogger* log = new SecureStore::FileLogger(DEBUG_LOGGER_FILE_PATH);
#else
    #error Unsupported debug logger type
#endif

#ifdef DEBUG_LOGGER
#define INIT_CHAR_STRING(str, length) \
    { \
        LOGGER_INIT(); \
        log->allocateMemory(#str, length); \
        delete log; \
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
        log->allocateMemory(#varName, length); \
        delete log; \
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
        log->freeMemory(#varName); \
        delete log; \
    } \
    free(varName);
#else
#define MEMORY_FREE(varName) \
    free(varName);
#endif

#ifdef DEBUG_LOGGER
#define DEBUG_MESSAGE(str) \
    { \
        LOGGER_INIT(); \
        log->debug(str);    \
        delete log; \
    }
#else
#define DEBUG_MESSAGE(str)
#endif

namespace SecureStore
{
    class Log
    {
    public:
        virtual void allocateMemory(const char* varName, int length) = 0;
        virtual void freeMemory(const char* varName) = 0;
        virtual void debug(const char* data) = 0;
    };

    class StdoutLogger : public Log
    {
    public:
        void allocateMemory(const char* varName, int length) override;
        void freeMemory(const char* varName) override;
        void debug(const char* data) override;
    };

    class FileLogger : public Log
    {
    public:
        FileLogger(const char*);
        ~FileLogger();
        void allocateMemory(const char* varName, int length) override;
        void freeMemory(const char* varName) override;
        void debug(const char* data) override;

    private:
        IOBuffer::IOFileWriter* fileWriter;
    };
}

#endif
