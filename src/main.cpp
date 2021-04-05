#include <Arduino.h>

#include "CubePlexer.hpp"

namespace T27
{
    CubePlexer app{};
} // namespace T27


unsigned long start_time;
const unsigned long next_step_interval = 150;

void setup()
{
    randomSeed(analogRead(0));
    delay(2000);

    Serial.begin(9600L);

    T27::CubePlexer::setup();

    start_time = millis();
}

void turn_random_on() 
{
    for (int x = 0; x < T27::CubePlexer::N; ++x)
    {
        for (int y = 0; y < T27::CubePlexer::N; ++y)
        {
            if (random(0, 5) == 1)
                T27::app.on(x, y, 0);
        }
    }
}

void loop()
{
    
    if (start_time + next_step_interval < millis()) 
    {
        Serial.println(millis());
        for (int x = 0; x < T27::CubePlexer::N; ++x)
        {
            for (int y = 0; y < T27::CubePlexer::N; ++y)
            {
                for (int z = T27::CubePlexer::N-1; z >= 0; --z) 
                {
                    if (T27::app.is_on(x, y, z)) 
                    {
                        T27::app.off(x, y, z);
                        if (z + 1 < T27::CubePlexer::N)
                            T27::app.on(x, y, z+1);
                    }
                }
            }
        }
        turn_random_on();
        start_time = millis();
    }
    for (int z = 0; z < T27::CubePlexer::N; ++z)
    {
        T27::app.activate_level(z);
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
