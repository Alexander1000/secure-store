#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>
#include <memory>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testEncyptDecrypt_Data_case02()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("cipher data test-case 01");
        t->printTitle();

        SecureStore::Storage::cipher_params_t* params = (SecureStore::Storage::cipher_params_t*) malloc(sizeof(SecureStore::Storage::cipher_params_t));

        std::string textForCipher = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                                    "Phasellus augue odio, scelerisque sit amet malesuada suscipit, "
                                    "maximus id magna. Nulla vel nisi lectus. Aliquam ut purus odio. "
                                    "Fusce vulputate leo massa, sed egestas nunc tempus sed. Class "
                                    "aptent taciti sociosqu ad litora torquent per conubia nostra, "
                                    "per inceptos himenaeos. Ut ullamcorper lorem nec tellus rutrum placerat. "
                                    "Nullam urna urna, ultricies sed neque nec, aliquam scelerisque magna.\n";

        SecureStore::Storage::DataPack input((int) textForCipher.length(), (void*) textForCipher.c_str());

        SecureStore::Storage::DataPack* output = SecureStore::Storage::encrypt_decrypt(params, &input);

        free(params);

        t->finish();

        return t;
    }
}
