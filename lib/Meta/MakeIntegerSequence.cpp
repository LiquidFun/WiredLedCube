#include "MakeIntegerSequence.hpp"

#include "IntegerSequence.hpp"
#include "IsSame.hpp"

namespace T27
{
    namespace
    {
        // int
        static_assert(
            IsSame<
                IntSequence<>,
                MakeIntSequence<0>>::value,
            "");

        static_assert(
            IsSame<
                IntSequence<0>,
                MakeIntSequence<1>>::value,
            "");

        static_assert(
            IsSame<
                IntSequence<0, 1, 2, 3, 4>,
                MakeIntSequence<5>>::value,
            "");

        // unsigned
        static_assert(
            IsSame<
                IntegerSequence<unsigned>,
                MakeIntegerSequence<unsigned, 0u>>::value,
            "");

        static_assert(
            IsSame<
                IntegerSequence<unsigned, 0u>,
                MakeIntegerSequence<unsigned, 1u>>::value,
            "");

        static_assert(
            IsSame<
                IntegerSequence<unsigned, 0u, 1u, 2u, 3u, 4u>,
                MakeIntegerSequence<unsigned, 5u>>::value,
            "");

        // size_t
        static_assert(
            IsSame<
                IndexSequence<>,
                MakeIndexSequence<0u>>::value,
            "");

        static_assert(
            IsSame<
                IndexSequence<0u>,
                MakeIndexSequence<1u>>::value,
            "");

        static_assert(
            IsSame<
                IndexSequence<0u, 1u, 2u, 3u, 4u>,
                MakeIndexSequence<5u>>::value,
            "");

    }
} // namespace T27
