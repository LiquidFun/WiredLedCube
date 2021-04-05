#pragma once

#include "Arduino.h"

#include "CubePlexer.hpp"
#include "IBlinkMode.hpp"

namespace T27
{
    class MatrixMode : public IBlinkMode
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

    public:
        virtual void update() override
        {
            if (start_time_ + next_step_interval_ < millis())
            {
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int y = 0; y < CubePlexer::N; ++y)
                    {
                        bool next_state = (random(0, 5) == 1);
                        for (int z = CubePlexer::N; z >= 1; --z)
                        {
                            next_state = cube_.exchange(next_state, x, y, z - 1);
                        }
                    }
                }
                start_time_ = millis();
            }
        }

        virtual void update(int /*key*/) override
        {
            this->update();
        }
    }; // class MatrixMode
} // namespace T27
