#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testSaveDb_Data_case01()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("save db in file");
        t->printTitle();

        SecureStore::Storage::Record *record;
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "testSaveDb_Data_case01";
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

        std::string fileName = "save_case01.xdb";
        std::string key = "Qwerty123!";

        db.save(&fileName, &key);

        t->finish();

        return t;
    }
}
