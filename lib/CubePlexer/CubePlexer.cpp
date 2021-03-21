#include "CubePlexer.hpp"

//#include <cstdint>

#include <Arduino.h>

namespace T27
{
    // | GPIO idx | z |
    // |----------|---|
    // |       12 | 2 |
    // |       11 | 1 |
    // |       10 | 0 |
    //
    constexpr uint8_t z0 = 10;

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
    constexpr uint8_t yx_to_pin[CubePlexer::N][CubePlexer::N]{
        // {0, 1, 2} ∋ x
        {0, 1, 2}, // y = 0
        {5, 4, 3}, // y = 1
        {6, 7, 8}  // y = 2
    };
    // ATTENTION: above coordinate system is left-handed: eˣ × eʸ = −eᶻ
    //
    // ATTENTION:
    //   * state has row-major order: (x, y, z)
    //   * pin has col-major order: [y][x]

    void CubePlexer::setup()
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            pinMode(z0 + z, OUTPUT);
            digitalWrite(z0 + z, HIGH);
        }

        for (int y = 0; y < CubePlexer::N; ++y)
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                uint8_t pin = yx_to_pin[y][x];
                pinMode(pin, OUTPUT);
                digitalWrite(pin, LOW);
            }
        }
    }

    void CubePlexer::activate_level(int z_active) const
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            digitalWrite(z0 + z, LOW);
        }

        for (int y = 0; y < CubePlexer::N; ++y)
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                uint8_t pin = yx_to_pin[y][x];
                uint8_t led_state = (*this)(x, y, z_active) ? LOW : HIGH;
                digitalWrite(pin, led_state);
            }
        }

        digitalWrite(z0 + z_active, HIGH);
    }

    void CubePlexer::activate_all_levels() const
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            activate_level(z);
        }
    }

} // namespace T27
