#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <list>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testCipherData_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("cipher data test-case 01");
        t->printTitle();

        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "TestCase01";
        record->setName(&name);

        std::string user = "some-login";
        record->setUser(&user);

        std::string password = "12345Qwerty!@#";
        record->setPassword(&password);

        std::string comment = "It is example record in secure store";
        record->setComment(&comment);

        std::list<std::string> keywords;
        keywords.emplace_back("system");
        keywords.emplace_back("critical");
        record->setKeywords(&keywords);

        record->setCreateTime(187766224);

        SecureStore::Storage::DB db;
        db.addRecord(record);

        t->finish();

        return t;
    }
}
