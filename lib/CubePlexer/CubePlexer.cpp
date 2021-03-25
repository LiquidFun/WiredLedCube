#include "CubePlexer.hpp"

#include <stdint.h>

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
        {6, 7, 8}, // y = 2
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

    namespace
    {
#ifdef ARDUINO
        void write_without_cli(uint8_t pin, uint8_t state)
        {
            uint8_t port = digitalPinToPort(pin);
            uint8_t bit = digitalPinToBitMask(pin);
            volatile uint8_t *reg = portOutputRegister(port);

            uint8_t old_val = *reg;
            uint8_t new_val = (state == HIGH)
                                  ? (old_val | bit)
                                  : (old_val & ~bit);
            *reg = new_val;
        }
#else
        void write_without_cli(uint8_t pin, uint8_t state)
        {
        }
#endif
    }

    void CubePlexer::activate_level(int z_active) const
    {
#ifndef ARDUINO
        uint8_t SREG = 0;
#endif

        uint8_t initial_SREG = SREG;
        cli();

        for (int z = 0; z < CubePlexer::N; ++z)
        {
            uint8_t pin = z0 + z;
            uint8_t state = LOW;
            write_without_cli(pin, state);
        }

        for (int y = 0; y < CubePlexer::N; ++y)
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                uint8_t pin = yx_to_pin[y][x];
                uint8_t state = led_is_active_(x, y, z_active) ? LOW : HIGH;
                write_without_cli(pin, state);
            }
        }

        uint8_t pin = z0 + z_active;
        uint8_t state = HIGH;
        write_without_cli(pin, state);

        SREG = initial_SREG;
    }

    void CubePlexer::activate_all_levels() const
    {
        for (int z = 0; z < CubePlexer::N; ++z)
        {
            activate_level(z);
            delay(1);
        }
    }

} // namespace T27
