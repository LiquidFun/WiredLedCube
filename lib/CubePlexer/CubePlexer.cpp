#include "CubePlexer.hpp"

#include <stdint.h>

#include <Arduino.h>

#include "Pin.hpp"

namespace T27
{
    constexpr Pin CubePlexer::z_pins[CubePlexer::N];
    constexpr Pin CubePlexer::yx_pins[CubePlexer::N][CubePlexer::N];

    void CubePlexer::setup()
    {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, LOW);

        for (int z = 0; z < CubePlexer::N; ++z)
        {
            const Pin &pin = z_pins[z];
            pinMode(pin.idx(), OUTPUT);
            digitalWrite(pin.idx(), HIGH);
        }

        for (int y = 0; y < CubePlexer::N; ++y)
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                const Pin &pin = yx_pins[y][x];
                if (pin.idx() == 0 || pin.idx() == 1)
                {
                    continue;
                }
                pinMode(pin.idx(), OUTPUT);
                digitalWrite(pin.idx(), LOW);
            }
        }
    }

    void CubePlexer::activate_level(int z_active) const
    {
        constexpr uint8_t maskb_z = z_pins[0].mask() | z_pins[1].mask() | z_pins[2].mask();
        constexpr uint8_t maskb_xyz_e = pins[8].mask() | maskb_z | pins[LED_BUILTIN].mask();

        constexpr uint8_t maskd_xy = 0xFFu ^ (1u << 0u) ^ (1u << 1u);

        uint8_t portb_next = ports_BD_by_z[z_active][0];
        uint8_t portd_next = ports_BD_by_z[z_active][1];

        uint8_t status = SREG;
        cli();

        uint8_t portb_prev = PORTB;
        uint8_t portd_prev = PORTD;

        PORTB = (portb_prev & ~maskb_z);
        PORTD = (portd_prev & ~maskd_xy) | portd_next;
        PORTB = (portb_prev & ~maskb_xyz_e) | portb_next;

        SREG = status;
    }

    void CubePlexer::activate_all_levels() const
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            activate_level(z);
            delay(1);
        }
    }

    void CubePlexer::highlight(int z_to_be_highlighted)
    {
        const Pin &pin = pins[LED_BUILTIN];
        uint8_t port_offset = get_port_offset(pin.port());
        for (int z = 0; z < N; ++z)
        {
            ports_BD_by_z[z][port_offset] &= ~pin.mask();
        }
        ports_BD_by_z[z_to_be_highlighted][port_offset] |= pin.mask();
    }
} // namespace T27
