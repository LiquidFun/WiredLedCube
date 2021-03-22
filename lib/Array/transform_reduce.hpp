#pragma once

#include <stddef.h>

#include "Array.hpp"

namespace T27
{
    namespace intern
    {
        template <class T, size_t length, size_t remaining>
        struct TransformReduce_
        {
            static_assert(remaining >= 1, "see specialization");
            static constexpr size_t idx = length - remaining;

            template <
                class Transformer,
                class Reducer,
                class Ret>
            static constexpr Ret call(
                const Array<T, length> &lhs,
                const Array<T, length> &rhs,
                Transformer transformer,
                Reducer reducer,
                Ret value)
            {
                return TransformReduce_<T, length, remaining - 1>::call(
                    lhs,
                    rhs,
                    transformer,
                    reducer,
                    reducer(value,
                            transformer(lhs[idx], rhs[idx])));
            }
        }; // TransformReduce_

        template <class T, size_t length>
        struct TransformReduce_<T, length, 0>
        {
            static constexpr size_t remaining = 0;
            static constexpr size_t idx = length - remaining;

            template <
                class Transformer,
                class Reducer,
                class Ret>
            static constexpr Ret call(
                const Array<T, length> &lhs,
                const Array<T, length> &rhs,
                Transformer transformer,
                Reducer reducer,
                Ret value)
            {
                return value;
            }
        }; // TransformReduce_ specialization

    } // namespace intern

    template <class T, size_t size, class Transformer, class Reducer>
    constexpr auto transform_reduce(
        const Array<T, size> &lhs,
        const Array<T, size> &rhs,
        Transformer transformer,
        Reducer reducer) -> decltype(transformer(lhs[0], rhs[0]))
    {
        static_assert(size >= 1, "see overloads");

        return intern::TransformReduce_<T, size, size - 1>::call(
            lhs,
            rhs,
            transformer,
            reducer,
            transformer(lhs[0], rhs[0]));
    }

    template <class T, class Transformer, class Reducer>
    constexpr auto transform_reduce(
        const Array<T, 1> &lhs,
        const Array<T, 1> &rhs,
        Transformer transformer,
        Reducer reducer) -> decltype(transformer(lhs[0], rhs[0]))
    {
        return transformer(lhs[0], rhs[0]);
    }

    template <class T, class Transformer, class Reducer>
    constexpr auto transform_reduce(
        const Array<T, 0> &lhs,
        const Array<T, 0> &rhs,
        Transformer transformer,
        Reducer reducer) -> decltype(transformer(T{}, T{}))
    {
        return decltype(transformer(T{}, T{})){};
    }

} // namespace T27
