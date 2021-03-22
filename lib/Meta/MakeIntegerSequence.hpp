#pragma once

#include <stddef.h>

#include "IntegerSequence.hpp"
#include "IsSame.hpp"

namespace T27
{
    namespace intern
    {
        template <class I, size_t N, I... is>
        struct MakeIntegerSequence_ : MakeIntegerSequence_<I, N - 1, N - 1, is...>
        {
        }; // MakeIntegerSequence

        template <class I, I... is>
        struct MakeIntegerSequence_<I, 0, is...>
        {
            using type = IntegerSequence<I, is...>;
        }; // MakeIntegerSequence specialization

    } // namespace intern

    template <class I, I length>
    using MakeIntegerSequence = typename intern::MakeIntegerSequence_<I, length>::type;

    template <size_t length>
    using MakeIndexSequence = MakeIntegerSequence<size_t, length>;

    template <int length>
    using MakeIntSequence = MakeIntegerSequence<int, length>;

} // namespace T27
