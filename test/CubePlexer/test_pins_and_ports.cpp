#include <stdint.h>

#include <Arduino.h>
#include <unity.h>

#include "Pin.hpp"
#include "Port.hpp"

namespace T27
{
#ifndef ARDUINO
#undef digitalPinToPort
    constexpr uint8_t digitalPinToPort(uint8_t pin_idx)
    {
        return pins[pin_idx].port_idx_;
    }

#undef portOutputRegister
    volatile uint8_t *portOutputRegister(uint8_t port_idx)
    {
        return ports[port_idx].reg();
    }

#undef digitalPinToBitMask
    constexpr uint8_t digitalPinToBitMask(uint8_t pin_idx)
    {
        return pins[pin_idx].bit_mask();
    }
#endif

    void test_pins_and_ports()
    {
        uint8_t pin_idx = 0;
        for (const Pin &pin : pins)
        {
            TEST_ASSERT_EQUAL_UINT8(pin_idx, pin.pin_idx_);

            uint8_t port_idx = digitalPinToPort(pin_idx);
            TEST_ASSERT_EQUAL_UINT8(port_idx, pin.port_idx_);

            const Port &port = ports[port_idx];
            TEST_ASSERT_EQUAL_UINT8(port_idx, port.port_idx_);

            volatile uint8_t *reg = portOutputRegister(port_idx);
            TEST_ASSERT_EQUAL_PTR(reg, port.reg());

            uint8_t expected_mask = digitalPinToBitMask(pin_idx);
            TEST_ASSERT_EQUAL_UINT8(expected_mask, pin.bit_mask());

            ++pin_idx;
        }
    }

} // namespace T27
