#pragma once

namespace T27
{
    class CubePlexer
    {
    public:
        static constexpr int N = 3;

    private:
        bool led_is_active_[N * N * N]{};

    public:
        CubePlexer() = default;

    public:
        static void setup();

        void activate_level(int z_active) const;
        void activate_all_levels() const;

    public:
        bool &operator()(int x, int y, int z)
        {
            return led_is_active_[calc_offset(x, y, z)];
        }

        const bool &operator()(int x, int y, int z) const
        {
            return led_is_active_[calc_offset(x, y, z)];
        }

    private:
        int calc_offset(int x, int y, int z) const
        {
            return x * (N * N) + y * N + z;
        }
    }; // class CubePlexer

} // namespace T27
