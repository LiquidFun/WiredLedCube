#pragma once

#include <stdint.h>

namespace T27
{
    struct Pin
    {
        const uint8_t pin_idx_;
        const uint8_t port_idx_;
        const uint8_t bit_idx_;

        constexpr Pin port_idx(uint8_t port_idx) const
        {
            return Pin{pin_idx_, port_idx, bit_idx_};
        }

        constexpr Pin bit_idx(uint8_t bit_idx) const
        {
            return Pin{pin_idx_, port_idx_, bit_idx};
        }

        constexpr uint8_t bit_mask() const
        {
            return (1u << bit_idx_);
        }
    };

    constexpr Pin pins[]{
        Pin{+0}.port_idx(4).bit_idx(0),
        Pin{+1}.port_idx(4).bit_idx(1),
        Pin{+2}.port_idx(4).bit_idx(2),
        Pin{+3}.port_idx(4).bit_idx(3),
        Pin{+4}.port_idx(4).bit_idx(4),
        Pin{+5}.port_idx(4).bit_idx(5),
        Pin{+6}.port_idx(4).bit_idx(6),
        Pin{+7}.port_idx(4).bit_idx(7),

        Pin{+8}.port_idx(2).bit_idx(0),
        Pin{+9}.port_idx(2).bit_idx(1),
        Pin{10}.port_idx(2).bit_idx(2),
        Pin{11}.port_idx(2).bit_idx(3),
        Pin{12}.port_idx(2).bit_idx(4),
        Pin{13}.port_idx(2).bit_idx(5),

        Pin{14}.port_idx(3).bit_idx(0),
        Pin{15}.port_idx(3).bit_idx(1),
    };

} // namespace T27
