#ifndef H_SECURE_STORE_UTILS
#define H_SECURE_STORE_UTILS

#include <memory.h>

// #define DEBUG

#ifdef DEBUG
#define INIT_CHAR_STRING(str, length) \
    { \
        SecureStore::StdoutLogger log; \
        log.initCharString(#str, length); \
    }                                 \
    char* str = (char*) malloc((length) * sizeof(char));   \
    memset(str, 0, (length) * sizeof(char));
#else
#define INIT_CHAR_STRING(str, length) \
    char* str = (char*) malloc((length) * sizeof(char));   \
    memset(str, 0, (length) * sizeof(char));
#endif

#define MEMORY_ALLOC(varName, length) \
    void* varName = malloc((length) * sizeof(unsigned char)); \
    memset(varName, 0, (length) * sizeof(unsigned char));

#define MEMORY_FREE(varName) \
    free(varName);

namespace SecureStore
{
    class Log
    {
    public:
        virtual void initCharString(const char* varName, int length) = 0;
    };

    class StdoutLogger : public Log
    {
    public:
        void initCharString(const char* varName, int length) override;
    };
}

#endif
