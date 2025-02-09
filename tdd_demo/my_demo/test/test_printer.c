
#ifdef TEST

#include "unity.h"

#include "printer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_printer_NeedToImplement(void)
{
    TEST_ASSERT_EQUAL_INT(6, sum(1,2));
    TEST_ASSERT_EQUAL_INT(10, sum(2,3));
    TEST_ASSERT_EQUAL_INT(6, sum(2,2));
    TEST_IGNORE_MESSAGE("Need to Implement printer");
}

#endif // TEST
