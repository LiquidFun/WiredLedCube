#pragma once

#include "Arduino.h"

#include "Array.hpp"
#include "CubePlexer.hpp"
#include "IBlinkMode.hpp"
#include "make_array.hpp"
#include "Max.hpp"
#include "Min.hpp"

namespace T27
{
    class MatrixMode : public IBlinkMode
    {
    private:
        static constexpr auto interval_steps = make_array<unsigned long>(
            50ul,
            100ul,
            150ul,
            300ul,
            500ul,
            1000ul,
            1500ul,
            3000ul,
            5000ul,
            10000ul);

        static constexpr auto fill_percentage_steps = make_array<long>(
            0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100);

    private:
        CubePlexer &cube_;

        unsigned long start_time_{millis()};

        int curr_interval_idx_{2};
        int curr_fill_idx_{4};

    public:
        MatrixMode(CubePlexer &cube) : cube_{cube}
        {
        }

    public:
        virtual void update() override
        {
            unsigned long interval = interval_steps[curr_interval_idx_];
            long fill_percentage = fill_percentage_steps[curr_fill_idx_];
            if (start_time_ + interval < millis())
            {
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int y = 0; y < CubePlexer::N; ++y)
                    {
                        bool next_state = (random(100) < fill_percentage);
                        for (int z = CubePlexer::N; z >= 1; --z)
                        {
                            next_state = cube_.exchange(next_state, x, y, z - 1);
                        }
                    }
                }
                start_time_ = millis();
            }
        }

        virtual void update(int key) override
        {
            switch (key)
            {
            case '=': // faster
            case '+': // faster
                curr_interval_idx_ = Max<int>{}(
                    curr_interval_idx_ - 1,
                    0);
                break;
            case '-': // slower
                curr_interval_idx_ = Min<int>{}(
                    curr_interval_idx_ + 1,
                    interval_steps.length - 1);
                break;
            case '>': // more
                curr_fill_idx_ = Min<int>{}(
                    curr_fill_idx_ + 1,
                    fill_percentage_steps.length - 1);
                break;
            case '<': // fewer
                curr_fill_idx_ = Max<int>{}(
                    curr_fill_idx_ - 1,
                    0);
                break;
            }

            this->update();
        }
    }; // class MatrixMode
} // namespace T27
