#pragma once

namespace T27
{
    template <class T, T val>
    struct Constant
    {
        using type = T;

        static constexpr type value = val;
    }; // Constant

    template <bool val>
    struct BoolConstant : Constant<bool, val>
    {
    }; // BoolConstant

    using True = BoolConstant<true>;
    using False = BoolConstant<false>;

    template <int val>
    struct IntConstant : Constant<int, val>
    {
    }; // IntConstant

} // namespace T27
