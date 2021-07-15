#include <Arduino.h>
#include <array>
#include <unity.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "WirelessController.hpp"
#include "config.hpp"
#include "RobotControl.hpp"

void test_WiFi_Connect(void) {
    String ssid = "The Pack Net";
    String password = "3a$tmarInternet11202";
    String url = "http://example.com/index.html";

    WirelessController subject(ssid, password, url);

    if (subject.connectWiFi())
        TEST_PASS();
    
    else TEST_FAIL_MESSAGE("UNABLE TO CONNECT");
}

void test_HTTP_Connect(void) {
    if(WiFi.status() == WL_CONNECTED) {
        String ssid = "The Pack Net";
        String password = "3a$tmarInternet11202";
        String url = "http://example.com/index.html";

        WirelessController subject(ssid, password, url);

        if (subject.httpConnect())
            TEST_PASS();

        else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO URL");
    }

    else TEST_FAIL_MESSAGE("WIFI DISCONNECTED");
}

void test_HTTP_Get(void) {
    if (WiFi.status() == WL_CONNECTED) {
        String ssid = "The Pack Net";
        String password = "3a$tmarInternet11202";
        String url = "http://example.com/index.html";

        WirelessController subject(ssid, password, url);
        if (subject.httpConnect()) {
            if (subject.httpGet() > 0) // Negative codes are errors
                TEST_PASS();

            else TEST_FAIL_MESSAGE("HTTP ERROR CODE THROWN");
        }

        else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO URL");
    }

    else TEST_FAIL_MESSAGE("WIFI DISCONNECTED");
}

void test_HTTP_Get_JSON(void) {
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.useHTTP10(true);
        http.begin("http://arduinojson.org/example.json");
        int32_t httpCode = (int32_t) http.GET();
        
        // Negative codes indicate an error
        if(httpCode > 0) {
            DynamicJsonDocument doc(2048);
            DeserializationError err = 
                deserializeJson(doc, http.getStream());
            if (err)
                TEST_FAIL_MESSAGE("ERROR DESERIALIZING JSON");

            TEST_ASSERT_EQUAL(1351824120, doc["time"].as<long>());
        }

        else TEST_FAIL_MESSAGE("Received HTTP Error Code");
    }

    else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO WIFI");
}

void setup() {
    configMotorPins(); // located in config
    UNITY_BEGIN();
    RUN_TEST(test_WiFi_Connect);
    RUN_TEST(test_HTTP_Connect);
    RUN_TEST(test_HTTP_Get);
    RUN_TEST(test_HTTP_Get_JSON);
}

void loop() {
    UNITY_END();
}