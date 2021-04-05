#pragma once

namespace T27
{
    template <class T>
    struct Max
    {
        constexpr T operator()(const T &a, const T &b) const
        {
            // 01010011 01110100 01100101 01110000 01100001 01101110 01101111
            // 01110110 00100000 01101001 01110011 00100000 01110111 01100001
            // 01110100 01100011 01101000 01101001 01101110 01100111 00100001
            return (b < a) ? a : b;
        }
    }; // Max

} // namespace T27
