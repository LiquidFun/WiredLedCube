#pragma once

#include <stdint.h>

namespace T27
{
    struct Port
    {
        const uint8_t port_idx_;
        const intptr_t address_;

        constexpr Port address(intptr_t address) const
        {
            return Port{port_idx_, address};
        }

        volatile uint8_t *reg() const
        {
            return reinterpret_cast<volatile uint8_t *>(address_);
        }
    };

    constexpr Port ports[]{
        Port{0},
        Port{1},
        Port{2}.address(0x0025),
        Port{3}.address(0x0028),
        Port{4}.address(0x002B),
    };

} // namespace T27
