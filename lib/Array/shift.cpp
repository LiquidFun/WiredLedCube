#include "shift.hpp"

#include "Array.hpp"
#include "make_array.hpp"

namespace T27
{
    namespace
    {
        constexpr auto three_mTwo_nine = make_array<int>(3, -2, 9);
        static_assert(three_mTwo_nine[0] == 3, "");
        static_assert(three_mTwo_nine[1] == -2, "");
        static_assert(three_mTwo_nine[2] == 9, "");
        static_assert(three_mTwo_nine.size() == 3, "");

        constexpr auto mTwo_nine = shift(three_mTwo_nine);
        static_assert(mTwo_nine[0] == -2, "");
        static_assert(mTwo_nine[1] == 9, "");
        static_assert(mTwo_nine.size() == 2, "");

        constexpr auto nine = shift(mTwo_nine);
        static_assert(nine[0] == 9, "");
        static_assert(nine.size() == 1, "");

        constexpr auto empty = shift(nine);
        static_assert(empty.size() == 0, "");

    }
} // namespace T27
