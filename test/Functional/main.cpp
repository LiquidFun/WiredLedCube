#include <Arduino.h>
#include <unity.h>

namespace T27
{
    void test_max();
    void test_min();

    int run_tests()
    {
        UNITY_BEGIN();

        RUN_TEST(T27::test_min);
        RUN_TEST(T27::test_max);

        return UNITY_END();
    }

} // namespace T27

#ifdef ARDUINO

void setup()
{
    delay(2000);

    T27::run_tests();

    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
}

#else

int main()
{
    return T27::run_tests();
}

#endif
