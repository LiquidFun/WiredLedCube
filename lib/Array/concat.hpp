#pragma once

#include <stddef.h>

#include "Array.hpp"
#include "IntegerSequence.hpp"
#include "make_array.hpp"
#include "MakeIntegerSequence.hpp"

namespace T27
{
    namespace intern
    {
        template <class T, int... inds1, int... inds2>
        constexpr Array<T, sizeof...(inds1) + sizeof...(inds2)> concat_(
            const Array<T, sizeof...(inds1)> &arr1,
            IntSequence<inds1...>,
            const Array<T, sizeof...(inds2)> &arr2,
            IntSequence<inds2...>)
        {
            return make_array<T>(arr1[inds1]..., arr2[inds2]...);
        }
    } // namespace intern

    template <class T, size_t size1, size_t size2>
    constexpr Array<T, size1 + size2> concat(
        const Array<T, size1> &arr1,
        const Array<T, size2> &arr2)
    {
        return intern::concat_(
            arr1,
            MakeIntSequence<size1>{},
            arr2,
            MakeIntSequence<size2>{});
    }

} // namespace T27
