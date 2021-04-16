#include <Arduino.h>

#include "Array.hpp"
#include "CubePlexer.hpp"
#include "FreezeMode.hpp"
#include "IBlinkMode.hpp"
#include "MatrixMode.hpp"
#include "SpeedMode.hpp"
#include "PinLayout.hpp"
#include "PlayerMode.hpp"

// TODO: fix library dependencies
#include "IntegerSequence.hpp"
#include "Sum.hpp"

namespace T27
{
    constexpr PinLayout layout = PinLayout::v0;
    CubePlexer cube(layout);

    MatrixMode matrix_mode{cube};
    SpeedMode speed_mode{cube};
    PlayerMode player_mode{cube};
    FreezeMode freeze_mode{cube};

    auto modes = make_array<IBlinkMode *>(
        &freeze_mode // 0
        ,
        &speed_mode // 1
        ,
        &matrix_mode // 1
        ,
        &player_mode // 2
    );

    IBlinkMode *curr_mode = modes[1];
} // namespace T27

unsigned long start_time;
const unsigned long next_step_interval = 150;

void setup()
{
    randomSeed(analogRead(0));
    delay(2000);

    Serial.begin(9600L);

    T27::cube.setup();
}

void loop()
{
    if (Serial.available())
    {
        int key = Serial.read();
        constexpr unsigned first_mode_key = static_cast<unsigned>('0');
        unsigned next_mode_idx = static_cast<unsigned>(key) - first_mode_key;
        if (next_mode_idx < T27::modes.length)
        {
            T27::curr_mode = T27::modes[next_mode_idx];
        }
        // TODO: should we really forward the consumed key to the new mode?
        T27::curr_mode->update(key);
    }
    else
    {
        T27::curr_mode->update();
    }

    for (int z = 0; z < T27::CubePlexer::N; ++z)
    {
        T27::cube.activate_level(z);
        delay(5);
    }
}

#ifndef ARDUINO

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}

#endif
