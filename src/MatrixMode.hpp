#pragma once

#include "Arduino.h"

#include "CubePlexer.hpp"

namespace T27
{
    class MatrixMode
    {
    private:
        static constexpr unsigned long next_step_interval_ = 150;

    private:
        CubePlexer &cube_;

        unsigned long start_time_;

    public:
        MatrixMode(CubePlexer &cube)
            : cube_{cube}, start_time_{millis()}
        {
        }

    private:
        void turn_random_on()
        {
            for (int x = 0; x < CubePlexer::N; ++x)
            {
                for (int y = 0; y < CubePlexer::N; ++y)
                {
                    if (random(0, 5) == 1)
                    {
                        cube_.on(x, y, 0);
                    }
                }
            }
        }

    public:
        void update()
        {
            if (start_time_ + next_step_interval_ < millis())
            {
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int y = 0; y < CubePlexer::N; ++y)
                    {
                        for (int z = CubePlexer::N - 1; z >= 0; --z)
                        {
                            if (cube_.is_on(x, y, z))
                            {
                                cube_.off(x, y, z);
                                if (z + 1 < CubePlexer::N)
                                {
                                    cube_.on(x, y, z + 1);
                                }
                            }
                        }
                    }
                }
                turn_random_on();
                start_time_ = millis();
            }
        }
    }; // class MatrixMode
} // namespace T27
