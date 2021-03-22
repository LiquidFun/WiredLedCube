#include "IsSame.hpp"

namespace T27
{
    namespace
    {

        static_assert(
            IsSame<
                int,
                int>::value,
            "");

        static_assert(
            IsSame<
                unsigned,
                unsigned>::value,
            "");

        static_assert(
            IsSame<
                double,
                double>::value,
            "");

        static_assert(
            !IsSame<
                int,
                unsigned>::value,
            "");

        static_assert(
            IsSame<
                char,
                char>::value,
            "");

        static_assert(
            !IsSame<
                char,
                signed char>::value,
            "");

        static_assert(
            !IsSame<
                char,
                unsigned char>::value,
            "");

    }
} // namespace T27
