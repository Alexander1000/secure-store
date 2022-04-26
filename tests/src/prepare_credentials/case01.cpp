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
            0xef, 0xa1, 0x4f, 0xa5, 0x0f, 0x31, 0x25, 0x87,
            0x9b, 0x17, 0x09, 0x8e, 0xe0, 0xd2, 0x9c, 0x0d,
            0x27, 0x5c, 0x7c, 0x72, 0x3e, 0xd1, 0x8e, 0xd4,
            0xd6, 0x3f, 0x3d, 0x35, 0x9b, 0x20, 0xe5, 0x10,
            0xf2, 0x1d, 0x6d, 0x64, 0x46, 0x37, 0x86, 0x6a,
            0x56, 0x42, 0x3f, 0xcf, 0x88, 0xf6, 0x43, 0xfc,
            0x84, 0xde, 0x7a, 0xd6, 0x40, 0x7d, 0x4d, 0xed,
            0x6c, 0x2e, 0x07, 0x33, 0x75, 0xc0, 0xd2, 0xb3,
        };

        for (int i = 0; i < data->getLength(); i++) {
            auto curChar = *((uint8_t*) data->getData() + i);
            CppUnitTest::assertEquals(t, expectedData[i], curChar);
        }

        t->finish();
        return t;
    }
}
