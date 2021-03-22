#pragma once

namespace T27
{
    template <class T>
    struct Sum
    {
        constexpr T operator()(const T &a, const T &b) const
        {
            return a + b;
        }
    }; // Sum

} // namespace T27
