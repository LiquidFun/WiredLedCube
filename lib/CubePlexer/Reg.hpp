#pragma once

#include <stdint.h>

namespace T27
{
    template <class T>
    struct Reg
    {
        const uintptr_t address_;

        volatile T *ptr() const
        {
            return reinterpret_cast<volatile T *>(address_);
        }

        T read() const
        {
            return *ptr();
        }

        void write(T val) const
        {
            *ptr() = val;
        }
    };

    constexpr uintptr_t sfr_offset = 0x20;

    // constexpr Reg<uint8_t> sreg{0x3F + sfr_offset};

} // namespace T27
