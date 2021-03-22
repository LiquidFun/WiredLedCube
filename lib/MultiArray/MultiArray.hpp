#pragma once

#include "Array.hpp"
#include "make_array.hpp"
#include "Product.hpp"
#include "shift.hpp"
#include "scan_right.hpp"

namespace T27
{
    template <class T, int... extents_>
    class MultiArray
    {
    public:
        using element_type = T;

        static constexpr int Nd = sizeof...(extents_);

        static constexpr Array<int, Nd> extent_arr =
            make_array<int>(extents_...);

        static constexpr Array<int, Nd> stride_arr =
            shift(scan_right(extent_arr, Product<int>{}, 1));

        static constexpr int total_count =
            scan_right(extent_arr, Product<int>{}, 1)[0];

    private:
        Array<T, total_count> data_{};

    public:
        MultiArray() = default;

    public:
        template <class... Inds>
        /*constexpr since C++14*/ T &operator()(Inds... inds)
        {
            return data_[calc_offset(make_array<int>(inds...))];
        }

        template <class... Inds>
        constexpr const T &operator()(Inds... inds) const
        {
            return data_[calc_offset(make_array<int>(inds...))];
        }

    private:
        constexpr static int calc_offset(Array<int, Nd> inds)
        {
            return 0;
        }
    }; // class CubePlexer

} // namespace T27
