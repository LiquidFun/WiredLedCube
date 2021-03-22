#pragma once

#include <stddef.h>

#include "Array.hpp"
#include "concat.hpp"
#include "make_array.hpp"

namespace T27
{
    template <class T, size_t length>
    constexpr Array<T, length + 1> unshift(
        const Array<T, length> &arr,
        const T &val)
    {
        return concat(
            make_array<T>(val),
            arr);
    } // unshift

} // namespace T27
