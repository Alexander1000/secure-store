#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    CppUnitTest::TestCase* testSaveDb_MultiRecordsData_case02()
    {
        CppUnitTest::TestCase* t = nullptr;
        t = new CppUnitTest::TestCase("testSaveDb_MultiRecordsData_case02");
        t->printTitle();

        SecureStore::Storage::DB db;

        SecureStore::Storage::Record *record;

        // first record
        record = new SecureStore::Storage::Record;

        record->setId(1);
        std::string name = "testSaveDb_MultiRecordsData_case02_record1";
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

        db.addRecord(record);

        // second record

        record = new SecureStore::Storage::Record;

        record->setId(2);
        std::string name2 = "testSaveDb_MultiRecordsData_case02_record2";
        record->setName(&name2);

        std::string user2 = "nagibator_3000";
        record->setUser(&user2);

        std::string password2 = "zxcvb123$%^";
        record->setPassword(&password2);

        std::string comment2 = "This is secret for me";
        record->setComment(&comment2);

        record->setCreateTime(747828722);

        db.addRecord(record);

        // third record
        record = new SecureStore::Storage::Record;

        record->setId(3);
        std::string name3 = "testSaveDb_MultiRecordsData_case02_record3";
        record->setName(&name3);

        std::string user3 = "sashok";
        record->setUser(&user3);

        std::string password3 = "ojfmlw$2ffs$2fkiib";
        record->setPassword(&password3);

        std::list<std::string> keywords3;
        keywords3.emplace_back("tests");
        keywords3.emplace_back("ololo");
        keywords3.emplace_back("super");
        keywords3.emplace_back("top");
        record->setKeywords(&keywords3);

        record->setCreateTime(893753837);

        db.addRecord(record);

        std::string fileName = "save_case02.xdb";
        std::string key = "vmbzyirhkfs342iyvsmm5@%";

        db.save(&fileName, &key);

        t->finish();

        return t;
    }
}
