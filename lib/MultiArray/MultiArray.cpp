#include "MultiArray.hpp"

namespace T27
{
    namespace
    {
        constexpr auto arr = MultiArray<int, 3, 4, 5>{};
        static_assert(arr.stride_arr[2] == 1, "");
        static_assert(arr.stride_arr[1] == 5, "");
        static_assert(arr.stride_arr[0] == 20, "");
        static_assert(arr.total_count == 60, "");

        static_assert(arr(0, 0, 0) == 0);

        constexpr auto arr0 = MultiArray<int>{};
        static_assert(arr0.stride_arr.size() == 0);
        static_assert(arr0.total_count == 1, "");

        static_assert(arr0() == 0);
    }
} // namespace T27
