#pragma once

#include <stdint.h>

#include "Reg.hpp"

namespace T27
{
    struct Port
    {
        const uint8_t idx_;
        const char x_;           //     x
        const uintptr_t input_;  //  PINx
        const uintptr_t mode_;   //  DDRx
        const uintptr_t output_; // PORTx

        constexpr Port x(char val) const
        {
            return Port{idx_, val, input_, mode_, output_};
        }

        constexpr Port input(uintptr_t val) const
        {
            return Port{idx_, x_, val + sfr_offset, mode_, output_};
        }

        constexpr Port mode(uintptr_t val) const
        {
            return Port{idx_, x_, input_, val + sfr_offset, output_};
        }

        constexpr Port output(uintptr_t val) const
        {
            return Port{idx_, x_, input_, mode_, val + sfr_offset};
        }

        constexpr uint8_t idx() const
        {
            return idx_;
        }

        constexpr char x() const
        {
            return x_;
        }

        constexpr Reg<uint8_t> input() const
        {
            return Reg<uint8_t>{input_};
        }

        constexpr Reg<uint8_t> mode() const
        {
            return Reg<uint8_t>{mode_};
        }

        constexpr Reg<uint8_t> output() const
        {
            return Reg<uint8_t>{output_};
        }
    };

    constexpr Port ports[]{
        Port{0},
        Port{1},
        Port{2, 'B'}.input(0x03).mode(0x04).output(0x05),
        Port{3, 'C'}.input(0x06).mode(0x07).output(0x08),
        Port{4, 'D'}.input(0x09).mode(0x0A).output(0x0B),
    };

} // namespace T27
