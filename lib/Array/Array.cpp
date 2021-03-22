#include "Array.hpp"

namespace T27
{
    namespace
    {
        constexpr Array<int, 0> empty{};
        static_assert(empty.size() == 0);

        constexpr Array<int, 3> arr{6, -2, 4};
        static_assert(arr[0] == 6, "");
        static_assert(arr[1] == -2, "");
        static_assert(arr[2] == 4, "");
        static_assert(arr.size() == 3);
    }
} // namespace T27
