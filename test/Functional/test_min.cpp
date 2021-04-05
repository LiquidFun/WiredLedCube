#include <Arduino.h>
#include <unity.h>

#include "Min.hpp"

namespace T27
{
    namespace
    {
        struct IntWithId final
        {
            int value;
            char id; // for stability checks

            constexpr friend bool operator<(const IntWithId &lhs, const IntWithId &rhs)
            {
                return lhs.value < rhs.value;
            }
        };
    }

    void test_min()
    {
        constexpr auto f = Min<int>{};

        // usual numbers
        TEST_ASSERT_EQUAL_INT(4, f(4, 7));
        TEST_ASSERT_EQUAL_INT(4, f(7, 4));

        TEST_ASSERT_EQUAL_INT(-4, f(-4, 7));
        TEST_ASSERT_EQUAL_INT(-4, f(7, -4));

        TEST_ASSERT_EQUAL_INT(-7, f(4, -7));
        TEST_ASSERT_EQUAL_INT(-7, f(-7, 4));

        TEST_ASSERT_EQUAL_INT(-7, f(-4, -7));
        TEST_ASSERT_EQUAL_INT(-7, f(-7, -4));

        // INT_MIN and INT_MAX
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MIN, INT_MAX));
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MAX, INT_MIN));

        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MIN, INT_MAX - 1));
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MAX - 1, INT_MIN));

        TEST_ASSERT_EQUAL_INT(INT_MIN + 1, f(INT_MIN + 1, INT_MAX));
        TEST_ASSERT_EQUAL_INT(INT_MIN + 1, f(INT_MAX, INT_MIN + 1));

        TEST_ASSERT_EQUAL_INT(INT_MIN + 1, f(INT_MIN + 1, INT_MAX - 1));
        TEST_ASSERT_EQUAL_INT(INT_MIN + 1, f(INT_MAX - 1, INT_MIN + 1));

        // INT_MIN and INT_MIN
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MIN, INT_MIN));
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MIN, INT_MIN + 1));
        TEST_ASSERT_EQUAL_INT(INT_MIN, f(INT_MIN + 1, INT_MIN));
        TEST_ASSERT_EQUAL_INT(INT_MIN + 1, f(INT_MIN + 1, INT_MIN + 1));

        // INT_MAX and INT_MAX
        TEST_ASSERT_EQUAL_INT(INT_MAX, f(INT_MAX, INT_MAX));
        TEST_ASSERT_EQUAL_INT(INT_MAX - 1, f(INT_MAX, INT_MAX - 1));
        TEST_ASSERT_EQUAL_INT(INT_MAX - 1, f(INT_MAX - 1, INT_MAX));
        TEST_ASSERT_EQUAL_INT(INT_MAX - 1, f(INT_MAX - 1, INT_MAX - 1));

        // stability in case of equality
        //
        // see, e.g., http://stepanovpapers.com/notes.pdf on page 63
        // > It is hard for me to blame people who do so: after all, they just
        // > follow the C++ standard specification of max written by me. It
        // > took me several years to see that I was mistaken.
        int same_int_value = 4;
        IntWithId a{same_int_value, 'a'};
        IntWithId b{same_int_value, 'b'};

        TEST_ASSERT_EQUAL_CHAR('a', (Min<IntWithId>{}(a, b).id));
        TEST_ASSERT_EQUAL_CHAR('b', (Min<IntWithId>{}(b, a).id));
    }
} // namespace T27
