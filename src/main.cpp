#include <Arduino.h>

#include "CubePlexer.hpp"

namespace T27
{
    CubePlexer app{};
} // namespace T27

void setup()
{
    delay(2000);

    randomSeed(analogRead(9));

    T27::CubePlexer::setup();

    for (int x = 0; x < T27::CubePlexer::N; ++x)
    {
        for (int y = 0; y < T27::CubePlexer::N; ++y)
        {
            for (int z = 0; z < T27::CubePlexer::N; ++z)
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
