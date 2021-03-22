#include "Sum.hpp"

namespace T27
{
    namespace
    {
        constexpr int sum = Sum<int>{}(4, 7);
        static_assert(sum == 11, "");

    }
} // namespace T27
