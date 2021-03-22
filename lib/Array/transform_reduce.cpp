#include "transform_reduce.hpp"

#include "make_array.hpp"
#include "Product.hpp"
#include "Sum.hpp"

namespace T27
{
    namespace
    {
        constexpr auto lhs = make_array<int>(1, 2, 3);
        constexpr auto rhs = make_array<int>(2, 3, 4);
        const int dot_product = transform_reduce(
            lhs,
            rhs,
            Product<int>{},
            Sum<int>{});

        static_assert(dot_product == 20, "");
    }
} // namespace T27
