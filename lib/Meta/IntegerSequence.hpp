#pragma once

#include <stddef.h>

namespace T27
{
    template <class I, I... is>
    struct IntegerSequence
    {
        using value_type = I;

        static constexpr size_t size = sizeof...(is);
    }; // IntegerSequence

    template <size_t... inds>
    using IndexSequence = IntegerSequence<size_t, inds...>;

    template <int... ints>
    using IntSequence = IntegerSequence<int, ints...>;

} // namespace T27
