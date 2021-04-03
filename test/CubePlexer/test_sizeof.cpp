#include <stddef.h>
#include <stdint.h>

#include <Arduino.h>
#include <unity.h>

namespace T27
{
    void test_sizeof()
    {
#ifndef ARDUINO
        TEST_IGNORE_MESSAGE("Arduino only.");
#endif

        TEST_ASSERT_EQUAL_INT(2, sizeof(void *));

        using Size = decltype(sizeof(void *));
        TEST_ASSERT_EQUAL_INT(2, sizeof(Size));

        TEST_ASSERT_EQUAL_INT(1, sizeof(bool));
        TEST_ASSERT_EQUAL_INT(1, sizeof(byte));
        TEST_ASSERT_EQUAL_INT(2, sizeof(wchar_t));

        TEST_ASSERT_EQUAL_INT(1, sizeof(char));
        TEST_ASSERT_EQUAL_INT(1, sizeof(signed char));
        TEST_ASSERT_EQUAL_INT(1, sizeof(unsigned char));

        TEST_ASSERT_EQUAL_INT(2, sizeof(short));
        TEST_ASSERT_EQUAL_INT(2, sizeof(int));
        TEST_ASSERT_EQUAL_INT(4, sizeof(long));
        TEST_ASSERT_EQUAL_INT(8, sizeof(long long));

        TEST_ASSERT_EQUAL_INT(2, sizeof(unsigned short));
        TEST_ASSERT_EQUAL_INT(2, sizeof(unsigned int));
        TEST_ASSERT_EQUAL_INT(4, sizeof(unsigned long));
        TEST_ASSERT_EQUAL_INT(8, sizeof(unsigned long long));

        TEST_ASSERT_EQUAL_INT(4, sizeof(float));
        TEST_ASSERT_EQUAL_INT(4, sizeof(double));
        TEST_ASSERT_EQUAL_INT(4, sizeof(long double));

        TEST_ASSERT_EQUAL_INT(8, sizeof(intmax_t));
        TEST_ASSERT_EQUAL_INT(2, sizeof(intptr_t));

        TEST_ASSERT_EQUAL_INT(2, sizeof(uintptr_t));
        TEST_ASSERT_EQUAL_INT(8, sizeof(uintmax_t));
    }

} // namespace T27
