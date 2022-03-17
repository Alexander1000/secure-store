#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testPack_case0()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("test case0");
        t->printTitle();

        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "TestCase01";
        record->setName(&name);

        SecureStore::Storage::DataPack *dataPack = SecureStore::Storage::pack(record);

        t->finish();

        return t;
    }
}
