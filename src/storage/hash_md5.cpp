#include <secure-store.h>

#include <memory>
#include <openssl/evp.h>

namespace SecureStore::Storage
{
    uint8_t* hash_md5(SecureStore::DataPack* input)
    {
        EVP_MD_CTX *ctx;
        ctx = EVP_MD_CTX_new();
        EVP_DigestInit(ctx, EVP_md5());
        EVP_DigestUpdate(ctx, input->getData(), input->getLength());
        uint8_t* md5 = (uint8_t*) malloc(16);
        unsigned int size;
        EVP_DigestFinal(ctx, md5, &size);
        return md5;
    }
}
