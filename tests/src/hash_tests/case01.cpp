#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>
#include <memory>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testHash_Data_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("testHash_Data_case01");
        t->printTitle();

        std::string message = "test";
        auto input = new SecureStore::DataPack((int) message.size(), (void*) message.c_str());

        auto data = SecureStore::Crypto::hash_sha3_512(input);

        t->finish();
        return t;
    }
}
