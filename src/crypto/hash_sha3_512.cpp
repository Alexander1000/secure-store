#include <secure-store.h>

#include <memory>
#include <openssl/evp.h>

namespace SecureStore::Crypto
{
    uint8_t* hash_sha3_512(SecureStore::DataPack* input)
    {
        DEBUG_MESSAGE("Crypto::hash_sha3_512 <called>");

        EVP_MD_CTX *ctx;
        ctx = EVP_MD_CTX_new();
        EVP_DigestInit(ctx, EVP_sha3_512());
        EVP_DigestUpdate(ctx, input->getData(), input->getLength());
        uint8_t* hash = (uint8_t*) malloc(64);
        memset(hash, 0, 64);
        unsigned int size;
        EVP_DigestFinal(ctx, hash, &size);
        return hash;
    }
}
