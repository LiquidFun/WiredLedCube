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
            BlockAppears, BlockMovesOut, BlockMovesIn, BlockCrashes, BlockSlidesDown
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

        void block_appears() 
        {
            for (int z = 0; z < CubePlexer::N; ++z)
            {
                if (cube_.is_on(0, 0, z))
                    continue;
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int y = 0; y < CubePlexer::N; ++y)
                    {
                        cube_.on(x, y, z);
                    }
                }
                return;
            }
            state = State::BlockMovesOut;
        }

        void block_moves_out() 
        {
            for (int y = 0; y < CubePlexer::N; ++y)
            {
                if (cube_.is_off(0, y, 0))
                    continue;
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int z = 0; z < CubePlexer::N; ++z)
                    {
                        cube_.off(x, y, z);
                    }
                }
                return;
            }
            current_cycle_++;
            state = State::BlockMovesIn;
        }
        void block_moves_in() 
        {
            for (int y = 0; y < CubePlexer::N; ++y)
            {
                if (cube_.is_on(0, y, 0))
                    continue;
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int z = 0; z < CubePlexer::N; ++z)
                    {
                        cube_.on(x, y, z);
                    }
                }
                return;
            }
            if (current_cycle_ < ACC_CYCLES)
                state = State::BlockMovesOut;
            else
                state = State::BlockCrashes;
        }

        void block_crashes() 
        {
            for (int y = 0; y < CubePlexer::N - 1; ++y)
            {
                if (cube_.is_off(0, y, 0))
                    continue;
                for (int x = 0; x < CubePlexer::N; ++x)
                {
                    for (int z = 0; z < CubePlexer::N; ++z)
                    {
                        cube_.off(x, y, z);
                    }
                }
                return;
            }
            current_cycle_ = 0;
            state = State::BlockSlidesDown;
        }

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
            state = State::BlockAppears;
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
                        block_appears();
                        break;
                    case State::BlockMovesIn:
                        block_moves_in();
                        break;
                    case State::BlockMovesOut:
                        block_moves_out();
                        break;
                    case State::BlockCrashes:
                        block_crashes();
                        break;
                    case State::BlockSlidesDown:
                        block_slides_down();
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
