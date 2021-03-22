#pragma once

#include <stddef.h>

#include "Array.hpp"
#include "unshift.hpp"

namespace T27
{
    namespace intern
    {
        template <size_t remaining>
        struct ScanRight_
        {
            static_assert(remaining != 0, "see specialization");
            static constexpr size_t idx = remaining - 1;

            template <class T, size_t length, class Op>
            static constexpr Array<T, length + 1> call(
                const Array<T, length> &arr,
                Op op,
                const Array<T, length + 1 - remaining> prev)
            {
                return ScanRight_<idx>::call(
                    arr,
                    op,
                    unshift(
                        prev,
                        op(prev[0], arr[idx])));
            }
        }; // ScanRight_

        template <>
        struct ScanRight_<0>
        {
            template <class T, size_t length, class Op>
            static constexpr Array<T, length + 1> call(
                const Array<T, length> &arr,
                Op op,
                const Array<T, length + 1> prev)
            {
                return prev;
            }
        }; // ScanRight_ specialization

    } // namespace intern

    template <class T, size_t size, class Op>
    constexpr Array<T, size + 1> scan_right(
        const Array<T, size> &arr,
        Op op,
        T curr)
    {
        return intern::ScanRight_<size>::call(
            arr,
            op,
            make_array<T>(curr));
    }

} // namespace T27
