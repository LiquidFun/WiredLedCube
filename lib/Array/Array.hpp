#pragma once

#include <stddef.h>

namespace T27
{
    template <class T, size_t length_>
    class Array
    {
    public:
        using value_type = T;
        static constexpr size_t length = length_;
        static_assert(length != 0, "see specialization");

    private:
        T data_[length]{};

    public:
        constexpr Array() = default;

        template <class... Us>
        explicit constexpr Array(Us... values) : data_{values...}
        {
            static_assert(sizeof...(Us) == length, "must init all elements");
        }

    public:
        constexpr size_t size() const
        {
            return length;
        }

    public:
        constexpr const T &operator[](size_t idx) const
        {
            return data_[idx];
        }
    }; // Array

    template <class T>
    class Array<T, 0>
    {
    public:
        using value_type = T;
        static constexpr size_t length = 0;
        static_assert(length == 0, "specialization for length = 0");

    private:
        // T data_[length]{};

    public:
        constexpr Array() = default;

        template <class... Us>
        explicit constexpr Array(Us... values)
        {
            static_assert(sizeof...(Us) == length, "must init all elements");
        }

    public:
        constexpr size_t size() const
        {
            return length;
        }

    public:
        constexpr const T &operator[](size_t idx) const
        {
            // undefined behavior
            return 0;
        }
    }; // Array specialization

} // namespace T27
