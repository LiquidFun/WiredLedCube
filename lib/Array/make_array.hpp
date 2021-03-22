#pragma once

#include "Array.hpp"

namespace T27
{
    template <class T, class... Us>
    constexpr Array<T, sizeof...(Us)> make_array(Us... us)
    {
        return Array<T, sizeof...(Us)>{us...};
    }

} // namespace T27
