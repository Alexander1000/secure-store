#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>
#include <memory>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testEncryptDecrypt_Data_case02()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("cipher data test-case 02");
        t->printTitle();

        auto params = (SecureStore::Storage::cipher_params_t*) malloc(sizeof(SecureStore::Storage::cipher_params_t));

        /* Key to use for encrpytion and decryption */
        unsigned char key[AES_256_KEY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32};

        /* Initialization Vector */
        unsigned char iv[AES_BLOCK_SIZE] = {50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65};

        params->key = key;
        params->iv = iv;

        /* Indicate that we want to encrypt */
        params->encrypt = 1;

        /* Set the cipher type you want for encryption-decryption */
        params->cipher_type = EVP_aes_256_cbc();

        std::string textForCipher = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                                    "Phasellus augue odio, scelerisque sit amet malesuada suscipit, "
                                    "maximus id magna. Nulla vel nisi lectus. Aliquam ut purus odio. "
                                    "Fusce vulputate leo massa, sed egestas nunc tempus sed. Class "
                                    "aptent taciti sociosqu ad litora torquent per conubia nostra, "
                                    "per inceptos himenaeos. Ut ullamcorper lorem nec tellus rutrum placerat. "
                                    "Nullam urna urna, ultricies sed neque nec, aliquam scelerisque magna.\n";

        SecureStore::Storage::DataPack input((int) textForCipher.length(), (void*) textForCipher.c_str());

        SecureStore::Storage::DataPack* output = SecureStore::Storage::encrypt_decrypt(params, &input);

        params->encrypt = 0;
        SecureStore::Storage::DataPack* decoded = SecureStore::Storage::encrypt_decrypt(params, output);

        CppUnitTest::assertEquals(t, input.getLength(), decoded->getLength());
        CppUnitTest::assertEquals(t, std::string((char*) input.getData()), std::string((char*) decoded->getData()));

        free(params);

        t->finish();

        return t;
    }
}
