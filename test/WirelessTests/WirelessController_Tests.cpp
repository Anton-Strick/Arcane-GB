#include <Arduino.h>
#include <unity.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include <array>
#include <iostream>
#include <sstream>
#include <fstream>

#include "WirelessController.hpp"
#include "config.hpp"
#include "RobotControl.hpp"

String ssid = "The Pack Net";
String password = "3a$tmarInternet11202";
String url = "http://arduinojson.org/example.json";

void test_WiFi_Connect(void) {


    WirelessController subject(ssid, password, url);

    if (subject.connectWiFi())
        TEST_PASS();
    
    else TEST_FAIL_MESSAGE("UNABLE TO CONNECT");
}

void test_HTTP_Connect(void) {
    if(WiFi.status() == WL_CONNECTED) {
        WirelessController subject(ssid, password, url);

        if (subject.httpConnect())
            TEST_PASS();

        else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO URL");
    }

    else TEST_FAIL_MESSAGE("WIFI DISCONNECTED");
}

void test_HTTP_Get(void) {
    if (WiFi.status() == WL_CONNECTED) {
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

void test_Parse_XN_To_Array(void) {
    const char* xN = "h8";
    std::array<uint8_t, 2> expected = {9, 7};

    WirelessController subject(ssid, password, url);

    std::array<uint8_t, 2> out;
    out = subject.parseXNToArray(xN);
    if (expected == out)
        TEST_PASS();
    
    else if (expected[0] == out[0])
        TEST_FAIL_MESSAGE("ERROR:  ROW MISMATCH");
    
    else if (expected[1] == out[1]) 
        TEST_FAIL_MESSAGE("ERROR:  COL MISMATCH");

    else TEST_FAIL_MESSAGE("ERROR: COL AND ROW MISMATCH");
}

void test_Get_Move(void) {
    String json = 
        "{\"turn\":0,"
        "\"piece\":168,"
        "\"from\":\"a1\","
        "\"to\":\"a4\","
        "\"special\":\"n\"}";
    
    StaticJsonDocument<jsonCapacity> doc;
    DeserializationError err = deserializeJson(doc, json);
    if (err)
        TEST_FAIL_MESSAGE("ERROR DESERIALIZING JSON FILE");
    
    else {
        WirelessController subject(ssid, password, url);
        JsonMove test = subject.getMove(doc);
        std::array<uint8_t, 2> start, end;
        start = { 0, 0 };
        end   = { 0, 3 };
        JsonMove expected(0, 'n', start, end);

        if (expected.turn != test.turn)
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT TURN NUMBER");

        else if (expected.specialFlag != test.specialFlag)
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT SPECIAL FLAG");

        else if (expected.startPos != test.startPos)
            TEST_FAIL_MESSAGE("ERROR: INCORRECT START POSITION");
        
        else if (expected.endPos != test.endPos)
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT END POSITION");

        TEST_PASS();
    }
}

void setup() {
    configPins(); // located in config
    UNITY_BEGIN();
    //RUN_TEST(test_WiFi_Connect);
    //RUN_TEST(test_HTTP_Connect);
    //RUN_TEST(test_HTTP_Get);
    RUN_TEST(test_Parse_XN_To_Array);
    RUN_TEST(test_Get_Move);
}

void loop() {
    UNITY_END();
}