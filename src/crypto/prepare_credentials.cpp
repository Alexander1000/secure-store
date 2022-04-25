#include <secure-store.h>

#include <memory>
#include <openssl/evp.h>

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

        return nullptr;
    }
}
