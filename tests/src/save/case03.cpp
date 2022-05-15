#include <tests.h>
#include <secure-store.h>
#include <cpp-unit-test.h>
#include <string>

namespace SecureStoreTest
{
    BEGIN_TEST_CASE(testSaveDb_AppendData_case03, "save db - append data in storage")
        std::string fileName = "testSaveDb_AppendData_case03.xdb";
        std::string password = "bigOlolo5224^%@";

        SecureStore::Storage::DB db;
        db.save(fileName.c_str(), password.c_str());
    END_TEST_CASE()
}
