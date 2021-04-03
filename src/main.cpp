#include <Arduino.h>

#include "CubePlexer.hpp"

namespace T27
{
    CubePlexer app{};
} // namespace T27

void setup()
{
    delay(2000);

    Serial.begin(9600L);
    Serial.println(__AVR_LIBC_VERSION__);

    T27::CubePlexer::setup();

    for (int x = 0; x < T27::CubePlexer::N; ++x)
    {
        for (int y = 0; y < T27::CubePlexer::N; ++y)
        {
            for (int z = 0; z < T27::CubePlexer::N; ++z)
            {
                T27::app.on(x, y, z);
            }
        }
    }

    T27::app.highlight(2);
}

void loop()
{
    T27::app.activate_all_levels();
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
