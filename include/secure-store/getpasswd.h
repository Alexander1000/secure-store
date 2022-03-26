#ifndef H_SECURE_STORE_GETPASSWD
#define H_SECURE_STORE_GETPASSWD

namespace SecureStore
{
    ssize_t getpasswd(char **pw, size_t sz, int mask, FILE *fp);
}

#endif
