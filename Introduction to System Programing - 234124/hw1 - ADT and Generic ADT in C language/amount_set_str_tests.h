#ifndef AMOUNT_SET_STR_TESTS
#define AMOUNT_SET_STR_TESTS
#include "tests/test_utilities.h"
#define ASSERT_OR_DESTROY(expr) ASSERT_TEST_WITH_FREE((expr), asDestroy(as))

bool testAsCreateEmptySet();
bool testAsDeleteEmptySet();
bool testAsAddingToSet();
bool testAsCopySet();
bool testAsSize();
bool testAsContains();
bool testAsIteratorInvalid();
bool testAsClear();
bool testAsAmount();


#endif // AMOUNT_SET_STR_TESTS
