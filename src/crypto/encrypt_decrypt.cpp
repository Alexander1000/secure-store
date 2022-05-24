#include <secure-store.h>

#include <openssl/evp.h>
#include <openssl/err.h>
#include <memory>
#include <io-buffer.h>

namespace SecureStore::Crypto
{
    DataPack* encrypt_decrypt(cipher_params_t* params, SecureStore::DataPack* input)
    {
        DEBUG_MESSAGE("Crypto::encrypt_decrypt <called>");

        /* Allow enough space in output buffer for additional block */
        int cipher_block_size = EVP_CIPHER_block_size(params->cipher_type);

        MEMORY_ALLOC(in_buf, BUFSIZE);
        MEMORY_ALLOC(out_buf, BUFSIZE + cipher_block_size);

        int num_bytes_read, out_len;
        EVP_CIPHER_CTX *ctx;

        ctx = EVP_CIPHER_CTX_new();
        if (ctx == nullptr) {
            fprintf(stderr, "ERROR: EVP_CIPHER_CTX_new failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            MEMORY_FREE(in_buf);
            MEMORY_FREE(out_buf);
            return nullptr;
        }

        /* Don't set key or IV right away; we want to check lengths */
        if (!EVP_CipherInit_ex(ctx, params->cipher_type, NULL, NULL, NULL, params->encrypt)) {
            fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            MEMORY_FREE(in_buf);
            MEMORY_FREE(out_buf);
            return nullptr;
        }

        OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == AES_256_KEY_SIZE);
        OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);

        /* Now we can set key and IV */
        if (!EVP_CipherInit_ex(ctx, NULL, NULL, params->key, params->iv, params->encrypt)) {
            fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            EVP_CIPHER_CTX_cleanup(ctx);
            MEMORY_FREE(in_buf);
            MEMORY_FREE(out_buf);
            return nullptr;
        }

        IOBuffer::IOMemoryBuffer buffer;
        buffer.write((char*) input->getData(), input->getLength());
        buffer.setPosition(0);

        auto outBuffer = new IOBuffer::IOMemoryBuffer;

        while (true) {
            // Read in data in blocks until EOF. Update the ciphering with each read.
            num_bytes_read = buffer.read((char*) in_buf, BUFSIZE);
            if(!EVP_CipherUpdate(ctx, (unsigned char*) out_buf, &out_len, (unsigned char*) in_buf, num_bytes_read)){
                fprintf(stderr, "ERROR: EVP_CipherUpdate failed. OpenSSL error: %s\n",
                        ERR_error_string(ERR_get_error(), NULL));
                EVP_CIPHER_CTX_cleanup(ctx);
                MEMORY_FREE(in_buf);
                MEMORY_FREE(out_buf);
                return nullptr;
            }

            outBuffer->write((char*) out_buf, out_len);
            if (num_bytes_read < BUFSIZE) {
                /* Reached End of file */
                break;
            }
        }

        if (!EVP_CipherFinal_ex(ctx, (unsigned char*) out_buf, &out_len)) {
            EVP_CIPHER_CTX_cleanup(ctx);
            MEMORY_FREE(in_buf);
            MEMORY_FREE(out_buf);
            return nullptr;
        }

        outBuffer->write((char*) out_buf, out_len);
        EVP_CIPHER_CTX_cleanup(ctx);

        MEMORY_ALLOC(data, outBuffer->length());
        outBuffer->setPosition(0);
        outBuffer->read((char*) data, outBuffer->length());

        auto output = new SecureStore::DataPack(outBuffer->length(), data);

        MEMORY_FREE(in_buf);
        MEMORY_FREE(out_buf);

        delete outBuffer;

        return output;
    }
}
