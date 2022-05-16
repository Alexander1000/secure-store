#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>
#include <memory>
#include <openssl/rand.h>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testPrepareCredentials_Data_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("testPrepareCredentials_Data_case01");
        t->printTitle();

        const char* user = "alexander";
        const char* password = "123Qwerty!";
        const char* salt = "qwertyuiopasdfghjklzxcvbnm12345";

        auto data = SecureStore::Crypto::prepare_credentials(user, password, salt);
        CppUnitTest::assertEquals(t, 64, data->getLength());

        uint8_t expectedData[64] = {
            0xb1, 0x37, 0x9f, 0x53, 0xe2, 0x76, 0x95, 0x93,
            0xe8, 0xf4, 0x38, 0x9f, 0x64, 0x21, 0xf4, 0x22,
            0xae, 0x65, 0x22, 0xce, 0xe9, 0xd7, 0x8b, 0x11,
            0x5c, 0x45, 0x4b, 0xbc, 0x57, 0x87, 0x5f, 0x2d,
            0xde, 0xdb, 0xb0, 0xe8, 0xb6, 0x11, 0x5b, 0x51,
            0xa1, 0x6d, 0x2a, 0xc4, 0x0f, 0x49, 0x26, 0x2c,
            0x34, 0xc0, 0x17, 0x92, 0x4b, 0xc9, 0x2f, 0x38,
            0xca, 0xce, 0xe9, 0x47, 0xfe, 0x48, 0x76, 0x66,
        };

        for (int i = 0; i < data->getLength(); i++) {
            auto curChar = *((uint8_t*) data->getData() + i);
            CppUnitTest::assertEquals(t, expectedData[i], curChar);
        }

        t->finish();
        return t;
    }
}
