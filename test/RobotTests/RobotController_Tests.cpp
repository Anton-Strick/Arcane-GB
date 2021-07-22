#include <Arduino.h>
#include <array>
#include <unity.h>

#include "config.hpp"
#include "RobotControl.hpp"

void test_Enable_Magnet(void) {
    RobotControl subject;
    subject.enableMagnet();
    TEST_ASSERT_EQUAL(LOW, digitalRead(MAGNET_PIN));
}

void test_Disable_Magnet(void) {
    RobotControl subject;
    subject.disableMagnet();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MAGNET_PIN));
}

void setup() {
    configPins(); // located in config
    UNITY_BEGIN();
}

void loop() {
    static uint8_t loops = 0;

    RUN_TEST(test_Enable_Magnet);
    delay(1500);

    RUN_TEST(test_Disable_Magnet);    
    delay(1500);

    if (loops > 5) {
        UNITY_END();
    }

    loops++;
}