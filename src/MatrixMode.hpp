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
                        boolean next_state = (random(0, 5) == 1);
                        for (int z = CubePlexer::N; z >= 1; --z)
                        {
                            boolean curr_state = cube_.is_on(x, y, z - 1);
                            if (next_state)
                            {
                                cube_.on(x, y, z - 1);
                            }
                            else
                            {
                                cube_.off(x, y, z - 1);
                            }
                            next_state = curr_state;
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
