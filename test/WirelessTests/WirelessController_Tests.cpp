#include <Arduino.h>
#include <array>
#include <unity.h>
#include <WiFi.h>

#include "WirelessController.hpp"
#include "config.hpp"
#include "RobotControl.hpp"

void test_WiFi_Connect(void) {
    const char* ssid = "The Pack Net";
    const char* password = "3a$tmarInternet11202";
    
    WiFi.begin(ssid, password);
    delay(5000);
    TEST_ASSERT_EQUAL(WL_CONNECTED, WiFi.status());
}

void setup() {
    configMotorPins(); // located in config
    UNITY_BEGIN();
    
    RUN_TEST(test_WiFi_Connect);
}

void loop() {
    UNITY_END();
}