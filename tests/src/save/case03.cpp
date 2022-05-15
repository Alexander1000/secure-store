#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testSaveDb_AppendData_case03, "save db - append data in storage")
        std::string fileName = "testSaveDb_AppendData_case03.xdb";
        std::string password = "bigOlolo5224^%@";

        auto db = new SecureStore::Storage::DB;
        db->save(fileName.c_str(), password.c_str());

        auto record = new SecureStore::Storage::Record;
        record->setId(1);
        std::string name = "testSaveDb_AppendData_case03_record1";
        record->setName(&name);
        std::string user = "tutu";
        record->setUser(&user);
        std::string recPassword = "flkjliw85";
        record->setPassword(&recPassword);
        std::string comment = "It is example record in secure store - for test case testSaveDb_AppendData_case03";
        record->setComment(&comment);
        record->setCreateTime(9734827842);

        db->addRecord(record);
        db->save();

        delete db;
        db = new SecureStore::Storage::DB;

        int result = db->open(fileName.c_str(), password.c_str());
        CppUnitTest::assertEquals(t, 0, result);
    END_TEST_CASE()
}
