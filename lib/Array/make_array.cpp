#include "make_array.hpp"

#include "Array.hpp"

namespace T27
{
    namespace
    {
        constexpr auto empty = make_array<int>();
        static_assert(empty.size() == 0);

        constexpr auto arr = make_array<int>(6, -2, 4);
        static_assert(arr[0] == 6, "");
        static_assert(arr[1] == -2, "");
        static_assert(arr[2] == 4, "");
        static_assert(arr.size() == 3);
    }
} // namespace T27
