#pragma once

#include "MultiArray.hpp"

namespace T27
{
    class CubePlexer
    {
    public:
        static constexpr int N = 3;

    private:
        MultiArray<bool, N, N, N> led_is_active_{};

    public:
        CubePlexer() = default;

    public:
        static void setup();

        void activate_level(int z_active) const;
        void activate_all_levels() const;

    public:
        bool &operator()(int x, int y, int z)
        {
            return led_is_active_.ref(x, y, z);
        }

        const bool &operator()(int x, int y, int z) const
        {
            return led_is_active_(x, y, z);
        }
    }; // class CubePlexer

} // namespace T27
