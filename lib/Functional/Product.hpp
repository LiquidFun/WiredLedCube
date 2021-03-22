#pragma once

namespace T27
{
    template <class T>
    struct Product
    {
        constexpr T operator()(const T &a, const T &b) const
        {
            return a * b;
        }
    }; // Product

} // namespace T27
