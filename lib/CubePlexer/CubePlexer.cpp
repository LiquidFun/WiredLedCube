#include "CubePlexer.hpp"

//#include <cstdint>

#include <Arduino.h>

namespace T27
{
    // | GPIO idx |  z |
    // |----------|----|
    // |       12 | +1 |
    // |       11 |  0 |
    // |       10 | -1 |
    //
    //
    // horizontal GPIO pattern
    // (viewed from the top. 6 7 8 is the side closer to the USB port)
    //
    // | \ x | -1    0   +1 |
    // | y \ |              |
    // |-----|--------------|
    // |  -1 |  0    1    2 |
    // |   0 |  5    4    3 |
    // |  +1 |  6    7    8 |
    //
    // ATTENTION: above coordinate system is left-handed: eˣ × eʸ = −eᶻ

    void CubePlexer::setup()
    {
        for (int i = 10; i <= 12; ++i)
        {
            pinMode(i, OUTPUT);
            digitalWrite(i, HIGH);
        }

        for (int i = 0; i <= 8; ++i)
        {
            pinMode(i, OUTPUT);
            digitalWrite(i, LOW);
        }
    }

    void CubePlexer::activate_level(int z_active) const
    {
        for (int z = -1; z <= 1; ++z)
        {
            digitalWrite(11 + z, LOW);
        }

        for (int x = -1; x <= 1; ++x)
        {
            for (int y = -1; y <= 1; ++y)
            {
                uint8_t led_state = (*this)(x, y, z_active) ? LOW : HIGH;
                int sign_of_x = (y == 0) ? -1 : 1;// see GPIO pin layout at y=0
                uint8_t pin = static_cast<uint8_t>(
                    (y + 1) * 3 + (sign_of_x * x + 1));
                digitalWrite(pin, led_state);
            }
        }

        digitalWrite(11 + z_active, HIGH);
    }

    void CubePlexer::activate_all_levels() const
    {
        for (int z = -1; z <= 1; ++z)
        {
            activate_level(z);
        }
    }

} // namespace T27
