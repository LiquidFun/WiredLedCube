#pragma once

#include <stdint.h>

#include "Pin.hpp"
#include "PinLayout.hpp"

namespace T27
{
    class CubePlexer
    {
    public:
        static constexpr int N = 3;

        static constexpr Pin z_pins[2][N]{
            {
                // PinLayout::v0 (hard-wired)
                pins[12], // z = 0 (bottom)
                pins[11], // z = 1
                pins[10], // z = 2 (top)
            },
            {
                // PinLayout::v1 (cable plugs; subject to changes)
                pins[10], // z = 0 (bottom)
                pins[11], // z = 1
                pins[12], // z = 2 (top)
            }};

        static constexpr Pin yx_pins[2][CubePlexer::N][CubePlexer::N]{
            {
                // PinLayout::v0 (hard-wired)
                // {  0,       1,       2 } ∋ x
                {pins[0], pins[1], pins[2]}, // 0 = y
                {pins[5], pins[4], pins[3]}, // 1 = y
                {pins[6], pins[7], pins[8]}, // 2 = y
                // (viewed from the top. 6 7 8 is the side closer to the USB output)
            },
            {
                // PinLayout::v1 (cable plugs; subject to changes)
                // {  0,       1,       2 } ∋ x
                {pins[9], pins[13], pins[2]}, // 0 = y
                {pins[5], pins[4], pins[3]},  // 1 = y
                {pins[6], pins[7], pins[8]},  // 2 = y
                // (viewed from the top. 6 7 8 is the side closer to the USB output)
            }};

    private:
        PinLayout layout_;

        uint8_t ports_BD_by_z[N][2]{};

    public:
        CubePlexer(PinLayout layout)
            : layout_{layout}
        {
            for (int z = 0; z < N; ++z)
            {
                const Pin &pin = z_to_pin(z);
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
        void setup();

        void activate_level(int z_active) const;
        void activate_all_levels() const;

    public:
        void on(int x, int y, int z)
        {
            const Pin &pin = xy_to_pin(x, y);
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] &= ~pin.mask();
        }
        bool is_on(int x, int y, int z)
        {
            const Pin &pin = xy_to_pin(x, y);
            uint8_t port_offset = get_port_offset(pin.port());
            return !(ports_BD_by_z[z][port_offset] & pin.mask());
        }
        bool is_off(int x, int y, int z)
        {
            return !is_on(x, y, z);
        }
        void off(int x, int y, int z)
        {
            const Pin &pin = xy_to_pin(x, y);
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] |= pin.mask();
        }
        void toggle(int x, int y, int z)
        {
            const Pin &pin = xy_to_pin(x, y);
            uint8_t port_offset = get_port_offset(pin.port());
            ports_BD_by_z[z][port_offset] ^= pin.mask();
        }
        bool exchange(bool should_be_on, int x, int y, int z)
        {
            bool was_on = is_on(x, y, z);
            if (should_be_on)
            {
                on(x, y, z);
            }
            else
            {
                off(x, y, z);
            }
            return was_on;
        }
        void move_all_by(int by_x, int by_y, int by_z, bool fill_with_on = false) 
        {
            // Moves all LED states by the given amount.
            // To make sure that no data is lost, each target variable
            // is reversed if needed. Then the LED coordinate is computed
            // which should take the target's place. If it doesn't exist,
            // then use the fill_with_on variable.
            for (int z = 0; z < N; ++z)
            {
                int target_z = by_z > 0 ? N - z - 1 : z;
                int from_z = target_z - by_z;
                for (int x = 0; x < N; ++x)
                {
                    int target_x = by_x > 0 ? N - x - 1 : x;
                    int from_x = target_x - by_x;
                    for (int y = 0; y < N; ++y)
                    {
                        int target_y = by_y > 0 ? N - y - 1 : y;
                        int from_y = target_y - by_y;
                        bool fill = fill_with_on;
                        if (is_inside(from_x, from_y, from_z)) 
                            fill = is_on(from_x, from_y, from_z);
                        exchange(fill, target_x, target_y, target_z);
                    }
                }
            }
        }
        void set_all_to(bool is_on)
        {
            for (int x = 0; x < N; ++x)
                for (int y = 0; y < N; ++y)
                    for (int z = 0; z < N; ++z)
                        exchange(is_on, x, y, z);
        }
        void all_on()
        {
            set_all_to(true);
        }
        void all_off()
        {
            set_all_to(false);
        }

    private:
        bool is_inside(int coord)
        {
            return 0 <= coord && coord < N;
        }

        bool is_inside(int x, int y, int z)
        {
            return is_inside(x) && is_inside(y) && is_inside(z);
        }

        const Pin &z_to_pin(int z) const
        {
            return z_pins[static_cast<uint8_t>(layout_)][z];
        }

        const Pin &xy_to_pin(int x, int y) const
        {
            return yx_pins[static_cast<uint8_t>(layout_)][y][x];
        }

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
