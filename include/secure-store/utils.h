#ifndef H_SECURE_STORE_UTILS
#define H_SECURE_STORE_UTILS

#include <memory.h>

#define INIT_CHAR_STRING(str, length) \
    char* str = new char[(length)];   \
    memset(str, 0, (length) * sizeof(char));

#endif
