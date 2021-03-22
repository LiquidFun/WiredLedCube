#include "Constant.hpp"

namespace T27
{
    namespace
    {
        static_assert(
            True::value == true,
            "");

        static_assert(
            False::value == false,
            "");

        static_assert(
            IntConstant<-1>::value == -1,
            "");

        static_assert(
            IntConstant<0>::value == 0,
            "");

        static_assert(
            IntConstant<1>::value == 1,
            "");

        static_assert(
            IntConstant<23406>::value == 23406,
            "");

        static_assert(
            IntConstant<(1 << 15)>::value == (1 << 15),
            "");

    }
} // namespace T27
