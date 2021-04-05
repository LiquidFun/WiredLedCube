#include "CubePlexer.hpp"

#include <stdint.h>

#include <Arduino.h>

#include "Pin.hpp"

namespace T27
{
    constexpr Pin CubePlexer::z_pins[2][CubePlexer::N];
    constexpr Pin CubePlexer::yx_pins[2][CubePlexer::N][CubePlexer::N];

    void CubePlexer::setup()
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            const Pin &pin = z_to_pin(z);
            pinMode(pin.idx(), OUTPUT);
            digitalWrite(pin.idx(), HIGH);
        }

        for (int y = 0; y < CubePlexer::N; ++y)
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                const Pin &pin = xy_to_pin(x, y);
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
        // TODO: precompute bitmasks once (e.g., on construction)?
        uint8_t maskb_z = z_to_pin(0).mask() | z_to_pin(1).mask() | z_to_pin(2).mask();
        uint8_t maskb_xyz = ((layout_ == PinLayout::v0)
                                 ? (maskb_z | pins[8].mask())
                                 : (maskb_z | pins[8].mask() | pins[9].mask() | pins[13].mask()));

        constexpr uint8_t maskd_xy = 0xFFu ^ (1u << 0u) ^ (1u << 1u);

        uint8_t portb_next = ports_BD_by_z[z_active][0];
        uint8_t portd_next = ports_BD_by_z[z_active][1];

        uint8_t status = SREG;
        cli();

        uint8_t portb_prev = PORTB;
        uint8_t portd_prev = PORTD;

        PORTB = (portb_prev & ~maskb_z);
        PORTD = (portd_prev & ~maskd_xy) | portd_next;
        PORTB = (portb_prev & ~maskb_xyz) | portb_next;

        SREG = status;
    }
} // namespace T27
