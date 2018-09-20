#include "../vendor/Unity/src/unity.h"
#include "../src/helpers.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_something(void)
{
    TEST_ASSERT_EQUAL_STRING(something(), "something");
}

void test_something_else(void)
{
    TEST_IGNORE();
}

int main(void)
{
   UnityBegin("test/test_helpers.c");

   RUN_TEST(test_something);
   RUN_TEST(test_something_else);

   return UnityEnd();
}
