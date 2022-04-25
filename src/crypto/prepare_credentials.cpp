#include <secure-store.h>

#include <memory>
#include <openssl/evp.h>
#include <io-buffer.h>

namespace SecureStore::Crypto
{
    cipher_key* prepare_credentials(const char* user, const char* password, const char* salt)
    {
        int userLength = strlen(user);
        if (userLength > 32) {
            userLength = 32;
        }

        int passwordLength = strlen(password);
        if (passwordLength > 32) {
            passwordLength = 32;
        }

        int baseStringLength = userLength + 1 + passwordLength + 1 + 32;
        char* baseString = (char*) malloc(baseStringLength);
        memset(baseString, 0, baseStringLength);

        memcpy(baseString, user, userLength);
        memcpy(baseString + userLength, password, passwordLength);
        memcpy(baseString + userLength + passwordLength, salt, 32);

        auto input = new SecureStore::DataPack(baseStringLength, baseString);
        auto hashData = hash_sha3_512(input);
        IOBuffer::IOMemoryBuffer outBuffer;

        auto cipherType = EVP_bf_cbc();
        int cipher_block_size = EVP_CIPHER_block_size(cipherType);
        unsigned char in_buf[BUFSIZE], out_buf[BUFSIZE + cipher_block_size];
        int num_bytes_read, out_len;

        EVP_CIPHER_CTX *ctx;
        ctx = EVP_CIPHER_CTX_new();
        EVP_CipherInit_ex(ctx, EVP_bf_cbc(), NULL, hashData, hashData + 32, 1);
        EVP_CipherUpdate(ctx, out_buf, &out_len, in_buf, num_bytes_read);
        outBuffer.write((char*) out_buf, out_len);
        EVP_CipherFinal_ex(ctx, out_buf, &out_len);

        outBuffer.write((char*) out_buf, out_len);

        EVP_CIPHER_CTX_cleanup(ctx);

        return nullptr;
    }
}
