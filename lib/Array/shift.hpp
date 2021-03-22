#pragma once

#include <stddef.h>

#include "Array.hpp"
#include "IntegerSequence.hpp"
#include "MakeIntegerSequence.hpp"

namespace T27
{
    namespace intern
    {
        template <class T, size_t... inds>
        constexpr Array<T, sizeof...(inds)> shift_(
            const Array<T, 1 + sizeof...(inds)> &arr,
            IndexSequence<inds...>)
        {
            return Array<T, sizeof...(inds)>{
                arr[inds + 1]...};
        }

    } // namespace intern

    template <class T, size_t length>
    constexpr Array<T, length - 1> shift(
        const Array<T, length> &arr)
    {
        static_assert(length >= 1, "");
        return intern::shift_(
            arr,
            MakeIndexSequence<length - 1>{});
    }

} // namespace T27
