#include "unshift.hpp"

#include "Array.hpp"

namespace T27
{
    namespace
    {
        constexpr auto empty = make_array<int>();
        static_assert(empty.size() == 0, "");

        constexpr auto nine = unshift(empty, 9);
        static_assert(nine[0] == 9, "");
        static_assert(nine.size() == 1, "");

        constexpr auto mTwo_nine = unshift(nine, -2);
        static_assert(mTwo_nine[0] == -2, "");
        static_assert(mTwo_nine[1] == 9, "");
        static_assert(mTwo_nine.size() == 2, "");

        constexpr auto three_mTwo_nine = unshift(mTwo_nine, 3);
        static_assert(three_mTwo_nine[0] == 3, "");
        static_assert(three_mTwo_nine[1] == -2, "");
        static_assert(three_mTwo_nine[2] == 9, "");
        static_assert(three_mTwo_nine.size() == 3, "");
    }
} // namespace T27
