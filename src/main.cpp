#include <Arduino.h>

#include "CubePlexer.hpp"
#include "MatrixMode.hpp"
#include "PinLayout.hpp"

namespace T27
{
    constexpr PinLayout layout = PinLayout::v0;
    CubePlexer cube(layout);
    MatrixMode matrix_mode(cube);
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

    T27::matrix_mode.update();
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
