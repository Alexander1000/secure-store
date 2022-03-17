#include <tests.h>
#include <cpp-unit-test.h>

int main() {
    CppUnitTest::TestSuite testSuite;

    testSuite.addTestCase(SecureStoreTest::testPack_case0());

    testSuite.printTotal();

    return 0;
}
