#include <Arduino.h>
#include <unity.h>

namespace T27
{
    void test_avr_libc_version()
    {
        TEST_ASSERT_EQUAL_UINT32(20000, __AVR_LIBC_VERSION__);
    }

} // namespace T27
