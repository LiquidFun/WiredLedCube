#include <Arduino.h>
#include <unity.h>

#include "MultiArray.hpp"

namespace T27
{
    void test_multi_array()
    {
        MultiArray<int, 2, 1, 2> arr{};

        TEST_ASSERT_EQUAL_INT(arr(0, 0, 0), 0);
        TEST_ASSERT_EQUAL_INT(arr(1, 0, 1), 0);

        arr.ref(0, 0, 0) = 4;
        arr.ref(1, 0, 1) = 8000;

        TEST_ASSERT_EQUAL_INT(arr(0, 0, 0), 4);
        TEST_ASSERT_EQUAL_INT(arr(1, 0, 1), 8000);
    }

} // namespace T27
