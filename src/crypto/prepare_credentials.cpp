#include <secure-store.h>

#include <memory>
#include <openssl/evp.h>
#include <io-buffer.h>

namespace SecureStore::Crypto
{
    SecureStore::DataPack* prepare_credentials(const char* user, const char* password, const char* salt)
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

        auto params = (SecureStore::Crypto::cipher_params_t*) malloc(sizeof(SecureStore::Crypto::cipher_params_t));
        params->key = hashData;
        params->iv = hashData + 32;
        params->encrypt = 1;
        params->cipher_type = EVP_aes_256_cbc();

        return encrypt_decrypt(params, input);
    }
}
