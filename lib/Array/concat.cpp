#include "concat.hpp"

#include "Array.hpp"
#include "make_array.hpp"

namespace T27
{
    namespace
    {
        constexpr auto empty = make_array<int>();

        constexpr auto three = make_array<int>(3);
        constexpr auto eight_mEleven = make_array<int>(8, -11);

        constexpr auto three_eight_mEleven = concat(three, eight_mEleven);
        static_assert(three_eight_mEleven[0] == 3);
        static_assert(three_eight_mEleven[1] == 8);
        static_assert(three_eight_mEleven[2] == -11);

        constexpr auto three_empty = concat(three, empty);
        static_assert(three_empty.size() == 1);
        static_assert(three_empty[0] == 3);

        constexpr auto empty_three = concat(empty, three);
        static_assert(empty_three[0] == 3);

        constexpr auto empty_empty = concat(empty, empty);
        static_assert(empty_empty.size() == 0);

    }
} // namespace T27
