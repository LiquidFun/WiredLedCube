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
    class SpeedMode : public IBlinkMode
    {
    private:
        enum class State {
            BlockAppears, BlockMovesOut, BlockMovesIn, BlockCrashes, BlockSlidesDown, Blinking
        };
        State state = State::BlockAppears;

    private:
        CubePlexer &cube_;

        unsigned long start_time_{millis()};
        unsigned int current_cycle_{0};
        const unsigned START_MS_PER_FRAME{500};
        const unsigned TARGET_MS_PER_FRAME{40};
        const unsigned ACC_CYCLES{20};
        unsigned long interval = START_MS_PER_FRAME;

        void block_slides_down() 
        {
            for (int z = CubePlexer::N - 1; z >= 1; --z)
            {
                if (cube_.is_on(0, CubePlexer::N - 1, z)) 
                {
                    for (int x = 0; x < CubePlexer::N; ++x)
                    {
                        cube_.off(x, CubePlexer::N - 1, z);
                        cube_.on(x, CubePlexer::N - z, 0);
                    }
                    return;
                }
            }
            state = State::Blinking;
        }

        double next_interval_time(int cycle) 
        {
            // Function visualised: https://www.desmos.com/calculator/hhiugobenp 
            return START_MS_PER_FRAME / exp(cycle * 5.0 / ACC_CYCLES) + TARGET_MS_PER_FRAME;
        }

    public:
        SpeedMode(CubePlexer &cube) : cube_{cube}
        {
        }

    public:
        virtual void update() override
        {
            if (start_time_ + interval < millis())
            {
                switch(state) {
                    case State::BlockAppears:
                        current_cycle_ = 0;
                        if (cube_.is_on(0, 0, CubePlexer::N - 1))
                            state = State::BlockMovesOut;
                        else
                            cube_.move_all_by(0, 0, 1, true);
                        break;

                    case State::BlockMovesOut:
                        if (cube_.is_off(0, CubePlexer::N - 1, CubePlexer::N - 1)) 
                        {
                            state = State::BlockMovesIn;
                            current_cycle_++;
                        }
                        else
                            cube_.move_all_by(0, 1, 0, false);
                        break;

                    case State::BlockMovesIn:
                        if (cube_.is_on(0, CubePlexer::N - 1, CubePlexer::N - 1))
                            state = (current_cycle_ < ACC_CYCLES
                                ? State::BlockMovesOut
                                : State::BlockCrashes);
                        else
                            cube_.move_all_by(0, 1, 0, true);
                        break;

                    case State::BlockCrashes:
                        current_cycle_ = 0;
                        if (cube_.is_off(0, CubePlexer::N - 2, CubePlexer::N - 1)) 
                            state = State::BlockSlidesDown;
                        else
                            cube_.move_all_by(0, 1, 0, false);
                        break;

                    case State::BlockSlidesDown:
                        block_slides_down();
                        break;

                    case State::Blinking:
                        current_cycle_++;
                        if (current_cycle_ % 5 == 0)
                            state = State::BlockAppears;
                        else if (current_cycle_ % 2 == 0)
                            cube_.all_off();
                        else
                            cube_.all_on();
                        break;
                }
                start_time_ = millis();
                interval = next_interval_time(current_cycle_);
            }
        }

        virtual void update(int key) override
        {

        }
    }; // class SpeedMode
} // namespace T27
