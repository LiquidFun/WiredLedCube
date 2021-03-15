#pragma once

namespace T27
{
    class CubePlexer
    {
    private:
        bool led_is_active_[27]{};

    public:
        CubePlexer() = default;

    public:
        static void setup();

        void activate_level(int z_active) const;

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
            return (x + 1) * 9 + (y + 1) * 3 + (z + 1);
        }
    }; // class CubePlexer

} // namespace T27
