#include <Arduino.h>

#include "CubePlexer.hpp"

namespace T27
{
    CubePlexer app{};
} // namespace T27

void setup()
{
    randomSeed(analogRead(9));

    T27::CubePlexer::setup();

    for (int x = -1; x <= 1; ++x)
    {
        for (int y = -1; y <= 1; ++y)
        {
            for (int z = -1; z <= 1; ++z)
            {
                bool led_on = (random(2) == 1);
                T27::app(x, y, z) = led_on;
            }
        }
    }
}

void loop()
{
    for (int z = -1; z <= 1; ++z)
    {
        T27::app.activate_level(z);
        delay(10);
    }
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
