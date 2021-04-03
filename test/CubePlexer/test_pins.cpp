#include <stdint.h>

#include <Arduino.h>
#include <unity.h>

#include "Pin.hpp"

namespace T27
{
#ifndef ARDUINO
    namespace
    {
#undef digitalPinToPort
        constexpr uint8_t digitalPinToPort(uint8_t pin_idx)
        {
            return pins[pin_idx].port_idx_;
        }

#undef digitalPinToBitMask
        constexpr uint8_t digitalPinToBitMask(uint8_t pin_idx)
        {
            return pins[pin_idx].mask();
        }
    }
#endif

    void test_pins()
    {
        uint8_t pin_idx = 0;
        for (const Pin &pin : pins)
        {
            TEST_ASSERT_EQUAL_UINT8(
                pin_idx,
                pin.idx());

            TEST_ASSERT_EQUAL_UINT8(
                digitalPinToPort(pin_idx),
                pin.port().idx());

            TEST_ASSERT_EQUAL_UINT8(
                digitalPinToBitMask(pin_idx),
                pin.mask());

            ++pin_idx;
        }
    }

} // namespace T27
