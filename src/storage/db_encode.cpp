#include <secure-store.h>

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>
#include <memory>
#include <io-buffer.h>

#define BUFSIZE 100

namespace SecureStore::Storage
{
    DataPack *DB::encode(DataPack* input, std::string* password)
    {
        cipher_params_t *params = (cipher_params_t*) malloc(sizeof(cipher_params_t));
        if (!params) {
            /* Unable to allocate memory on heap*/
            // fprintf(stderr, "ERROR: malloc error: %s\n", strerror(errno));
            return nullptr;
        }

        /* Key to use for encrpytion and decryption */
        unsigned char key[AES_256_KEY_SIZE];

        /* Initialization Vector */
        unsigned char iv[AES_BLOCK_SIZE];

        /* Generate cryptographically strong pseudo-random bytes for key and IV */
        if (!RAND_bytes(key, sizeof(key)) || !RAND_bytes(iv, sizeof(iv))) {
            /* OpenSSL reports a failure, act accordingly */
            // fprintf(stderr, "ERROR: RAND_bytes error: %s\n", strerror(errno));
            return nullptr;
        }

        params->key = key;
        params->iv = iv;

        /* Indicate that we want to encrypt */
        params->encrypt = 1;

        /* Set the cipher type you want for encryption-decryption */
        params->cipher_type = EVP_aes_256_cbc();

        /* Allow enough space in output buffer for additional block */
        int cipher_block_size = EVP_CIPHER_block_size(params->cipher_type);
        unsigned char in_buf[BUFSIZE], out_buf[BUFSIZE + cipher_block_size];

        int num_bytes_read, out_len;
        EVP_CIPHER_CTX *ctx;

        ctx = EVP_CIPHER_CTX_new();
        if(ctx == NULL){
            fprintf(stderr, "ERROR: EVP_CIPHER_CTX_new failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            // cleanup(params, ifp, ofp, ERR_EVP_CTX_NEW);
        }

        /* Don't set key or IV right away; we want to check lengths */
        if(!EVP_CipherInit_ex(ctx, params->cipher_type, NULL, NULL, NULL, params->encrypt)){
            fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            // cleanup(params, ifp, ofp, ERR_EVP_CIPHER_INIT);
        }

        OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == AES_256_KEY_SIZE);
        OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);

        /* Now we can set key and IV */
        if(!EVP_CipherInit_ex(ctx, NULL, NULL, params->key, params->iv, params->encrypt)){
            fprintf(stderr, "ERROR: EVP_CipherInit_ex failed. OpenSSL error: %s\n",
                    ERR_error_string(ERR_get_error(), NULL));
            EVP_CIPHER_CTX_cleanup(ctx);
            // cleanup(params, ifp, ofp, ERR_EVP_CIPHER_INIT);
        }

        int index = 0;

        IOBuffer::IOMemoryBuffer buffer(BUFSIZE);
        buffer.write((char*) input->getData(), input->getLength());
        buffer.setPosition(0);

        while(1) {
            // Read in data in blocks until EOF. Update the ciphering with each read.
            // memcpy(in_buf, (uint8_t*) input->getData() + index * BUFSIZ, sizeof(uint8_t) * BUFSIZE);
            // num_bytes_read = buffer.read();
            num_bytes_read = buffer.read((char*) in_buf, BUFSIZE);
//            if (ferror(ifp)){
//                fprintf(stderr, "ERROR: fread error: %s\n", strerror(errno));
//                EVP_CIPHER_CTX_cleanup(ctx);
//                // cleanup(params, ifp, ofp, errno);
//            }
            if(!EVP_CipherUpdate(ctx, out_buf, &out_len, in_buf, num_bytes_read)){
                fprintf(stderr, "ERROR: EVP_CipherUpdate failed. OpenSSL error: %s\n",
                        ERR_error_string(ERR_get_error(), NULL));
                EVP_CIPHER_CTX_cleanup(ctx);
                // cleanup(params, ifp, ofp, ERR_EVP_CIPHER_UPDATE);
            }
//            fwrite(out_buf, sizeof(unsigned char), out_len, ofp);
//            if (ferror(ofp)) {
//                fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
//                EVP_CIPHER_CTX_cleanup(ctx);
//                // cleanup(params, ifp, ofp, errno);
//            }
//            if (num_bytes_read < BUFSIZE) {
//                /* Reached End of file */
//                break;
//            }
        }

        /* Now cipher the final block and write it out to file */
//        if(!EVP_CipherFinal_ex(ctx, out_buf, &out_len)){
//            fprintf(stderr, "ERROR: EVP_CipherFinal_ex failed. OpenSSL error: %s\n",
//                    ERR_error_string(ERR_get_error(), NULL));
//            EVP_CIPHER_CTX_cleanup(ctx);
//            // cleanup(params, ifp, ofp, ERR_EVP_CIPHER_FINAL);
//        }
//        fwrite(out_buf, sizeof(unsigned char), out_len, ofp);
//        if (ferror(ofp)) {
//            fprintf(stderr, "ERROR: fwrite error: %s\n", strerror(errno));
//            EVP_CIPHER_CTX_cleanup(ctx);
//            // cleanup(params, ifp, ofp, errno);
//        }
//        EVP_CIPHER_CTX_cleanup(ctx);

        return nullptr;
    }
}
