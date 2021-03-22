#pragma once

#include "Constant.hpp"

namespace T27
{
    template <class T, class U>
    struct IsSame : False
    {
    }; // IsSame

    template <class T>
    struct IsSame<T, T> : True
    {
    }; // IsSame specialization
} // namespace T27
