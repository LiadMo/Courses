#include "amount_set_str_tests.h"

int main() {
    RUN_TEST(testAsCreateEmptySet);
    RUN_TEST(testAsDeleteEmptySet);
    RUN_TEST(testAsAddingToSet);
    RUN_TEST(testAsCopySet);
    RUN_TEST(testAsSize);
    RUN_TEST(testAsContains);
    RUN_TEST(testAsIteratorInvalid);
    RUN_TEST(testAsClear);
    RUN_TEST(testAsAmount);

    return 0;
}

