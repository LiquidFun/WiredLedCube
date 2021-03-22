#include "IntegerSequence.hpp"

#include <stddef.h>

#include "IsSame.hpp"

namespace T27
{
    namespace
    {
        static_assert(
            IsSame<
                IntegerSequence<int, 4, 2, -8>,
                IntSequence<4, 2, -8>>::value,
            "");

        static_assert(
            IsSame<
                IntegerSequence<int>,
                IntSequence<>>::value,
            "");

        static_assert(
            IsSame<
                IntegerSequence<size_t, 4, 2, 0>,
                IndexSequence<4, 2, 0>>::value,
            "");

        static_assert(
            IsSame<
                IntegerSequence<size_t>,
                IndexSequence<>>::value,
            "");
    }
} // namespace T27
