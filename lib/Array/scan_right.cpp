#include "scan_right.hpp"

#include "Array.hpp"
#include "make_array.hpp"
#include "Sum.hpp"

namespace T27
{
    namespace
    {
        constexpr auto arr = make_array<int>(3, -5, 1);
        constexpr auto result = scan_right(arr, Sum<int>{}, 2);
        static_assert(result.size() == 4);
        static_assert(result[3] == 2);
        static_assert(result[2] == 3);
        static_assert(result[1] == -2);
        static_assert(result[0] == 1);
    }
} // namespace T27
