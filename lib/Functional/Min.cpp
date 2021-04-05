#include "Min.hpp"

namespace T27
{
    namespace
    {
        constexpr int min = Min<int>{}(-10, 7);
        static_assert(min == -10, "");

    }
} // namespace T27
