#pragma once

#include "Array.hpp"
#include "make_array.hpp"
#include "Product.hpp"
#include "shift.hpp"
#include "scan_right.hpp"
#include "Sum.hpp"
#include "transform_reduce.hpp"

namespace T27
{
    template <class T, int... extents_>
    class MultiArray
    {
    public:
        using element_type = T;

        static constexpr int Nd = sizeof...(extents_);

        static constexpr Array<int, sizeof...(extents_)> extent_arr =
            make_array<int>(extents_...);

        static constexpr Array<int, sizeof...(extents_)> stride_arr =
            shift(scan_right(extent_arr, Product<int>{}, 1));

        static constexpr int total_count =
            scan_right(extent_arr, Product<int>{}, 1)[0];

    private:
        Array<T, total_count> data_{};

    public:
        MultiArray() = default;

    public:
        template <class... Inds>
        T &ref(Inds... inds)
        {
            return data_.ref(calc_offset(make_array<int>(inds...)));
            // can overload operator() with constexpr since C++14
        }

        template <class... Inds>
        constexpr const T &operator()(Inds... inds) const
        {
            return data_[calc_offset(make_array<int>(inds...))];
        }

    private:
        constexpr static int calc_offset(Array<int, Nd> inds)
        {
            return transform_reduce(
                inds,
                stride_arr,
                Product<int>{},
                Sum<int>{});
        }
    }; // class MultiArray

    // to be removed with C++17
    template <class T, int... extents>
    constexpr int MultiArray<T, extents...>::Nd;

    // to be removed with C++17
    template <class T, int... extents>
    constexpr Array<int, sizeof...(extents)> MultiArray<T, extents...>::extent_arr;

    // to be removed with C++17
    template <class T, int... extents>
    constexpr Array<int, sizeof...(extents)> MultiArray<T, extents...>::stride_arr;

} // namespace T27
