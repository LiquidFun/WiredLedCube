#include "Product.hpp"

namespace T27
{
    namespace
    {
        constexpr int product = Product<int>{}(4, 7);
        static_assert(product == 28, "");

    }
} // namespace T27
