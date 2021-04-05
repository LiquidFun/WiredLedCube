#include "Max.hpp"

namespace T27
{
    namespace
    {
        constexpr int max = Max<int>{}(-10, 7);
        static_assert(max == 7, "");

    }
} // namespace T27
