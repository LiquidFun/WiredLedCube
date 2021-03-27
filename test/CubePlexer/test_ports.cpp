#include <stdint.h>

#include <Arduino.h>
#include <unity.h>

#include "Port.hpp"

namespace T27
{
#ifndef ARDUINO
    namespace
    {
#undef portOutputRegister
        volatile uint8_t *portOutputRegister(uint8_t port_idx)
        {
            return ports[port_idx].output().ptr();
        }

#undef portInputRegister
        volatile uint8_t *portInputRegister(uint8_t port_idx)
        {
            return ports[port_idx].input().ptr();
        }

#undef portModeRegister
        volatile uint8_t *portModeRegister(uint8_t port_idx)
        {
            return ports[port_idx].mode().ptr();
        }
    }
#endif

    void test_ports()
    {
        uint8_t port_idx = 0;
        for (const Port &port : ports)
        {
            TEST_ASSERT_EQUAL_UINT8(
                port_idx,
                port.idx());

            TEST_ASSERT_EQUAL_PTR(
                portInputRegister(port_idx),
                port.input().ptr());

            TEST_ASSERT_EQUAL_PTR(
                portModeRegister(port_idx),
                port.mode().ptr());

            TEST_ASSERT_EQUAL_PTR(
                portOutputRegister(port_idx),
                port.output().ptr());

            ++port_idx;
        }

        {
            const Port &portb = ports[2];
            TEST_ASSERT_EQUAL_CHAR('B', portb.x());
            TEST_ASSERT_EQUAL_PTR(&PORTB, portb.output().ptr());
        }

        {
            const Port &portc = ports[3];
            TEST_ASSERT_EQUAL_CHAR('C', portc.x());
            TEST_ASSERT_EQUAL_PTR(&PORTC, portc.output().ptr());
        }

        {
            const Port &portd = ports[4];
            TEST_ASSERT_EQUAL_CHAR('D', portd.x());
            TEST_ASSERT_EQUAL_PTR(&PORTD, portd.output().ptr());
        }
    }

} // namespace T27
