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
                // bool led_on = (random(2) == 1);
                // bool led_on = (x + y + z + 100) % 2 == 0;
                bool led_on = true;
                T27::app(x, y, z) = led_on;
            }
        }
    }
}

void loop()
{
    T27::app.activate_all_levels();
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
