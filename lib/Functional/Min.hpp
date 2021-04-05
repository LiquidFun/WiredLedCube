#pragma once

namespace T27
{
    template <class T>
    struct Min
    {
        constexpr T operator()(const T &a, const T &b) const
        {
            return (b < a) ? b : a;
        }
    }; // Min

} // namespace T27
