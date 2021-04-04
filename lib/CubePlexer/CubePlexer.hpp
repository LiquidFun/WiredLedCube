#pragma once

#include "Pin.hpp"

namespace T27
{
    class CubePlexer
    {
    public:
        static constexpr int N = 3;

        static constexpr Pin z_pins[N]{
            pins[10], // z = 0 (bottom)
            pins[11], // z = 1
            pins[12], // z = 2 (top)
        };

        static constexpr Pin yx_pins[CubePlexer::N][CubePlexer::N]{
            // (viewed from the top. 6 7 8 is the side closer to the USB output)
            // {  0,       1,       2 } ∋ x
            {pins[0], pins[1], pins[2]}, // 0 = y
            {pins[5], pins[4], pins[3]}, // 1 = y
            {pins[6], pins[7], pins[8]}, // 2 = y
            // ATTENTION: above coordinate system is left-handed: eˣ × eʸ = −eᶻ
        };

    private:
        uint8_t ports_BD_by_z[N][2]{};

    public:
        CubePlexer()
        {
            for (int z = 0; z < N; ++z)
            {
                const Pin &pin = z_pins[z];
                uint8_t port_offset = get_port_offset(pin.port());
                ports_BD_by_z[z][port_offset] |= pin.mask();

                for (int y = 0; y < N; ++y)
                {
                    for (int x = 0; x < N; ++x)
                    {
                        off(x, y, z);
                    }
                }
            }
        }

    public:
        static void setup();

        void activate_level(int z_active) const;
        void activate_all_levels() const;

    public:
        void on(int x, int y, int z)
        {
            const Pin &pin = yx_pins[y][x];
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] &= ~pin.mask();
        }
        bool is_on(int x, int y, int z)
        {
            const Pin &pin = yx_pins[y][x];
            uint8_t port_offset = get_port_offset(pin.port());
            return !(ports_BD_by_z[z][port_offset] & pin.mask());
        }
        void off(int x, int y, int z)
        {
            const Pin &pin = yx_pins[y][x];
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] |= pin.mask();
        }
        void toggle(int x, int y, int z)
        {
            const Pin &pin = yx_pins[y][x];
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] ^= pin.mask();
        }
        void highlight(int z_to_be_highlighted);

    private:
        static constexpr uint8_t get_port_offset(const Port &port)
        {
            return (port.x() == 'B')
                       ? 0
                       : ((port.x() == 'D')
                              ? 1
                              : -1);
        }

    }; // class CubePlexer

} // namespace T27
