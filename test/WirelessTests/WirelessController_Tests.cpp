#include <Arduino.h>
#include <unity.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#include <array>

#include "WirelessController.hpp"
#include "config.hpp"
#include "RobotControl.hpp"

String ssid = "The Wifi";
String password = "ThePassword";
String url = "ws://example.com/websocket";

void test_WiFi_Connect(void) {
    WirelessController subject(ssid, password, url);

    if (subject.connectWiFi())
        TEST_PASS();
    
    else TEST_FAIL_MESSAGE("UNABLE TO CONNECT");
}

void test_Socket_Connect(void) {
    if(WiFi.status() == WL_CONNECTED) {
        WirelessController subject(ssid, password, url);

        if (subject.socketConnect())
            TEST_PASS();

        else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO URL");
    }

    else TEST_FAIL_MESSAGE("WIFI DISCONNECTED");
}

/* 
TODO:  Design unit test methodology for recieving websocket messages
        - Spoofing with on-board server?
        - Substituting game message with other message? 
void test_Message_Recieved(void) {
    if (WiFi.status() == WL_CONNECTED) {
        WirelessController subject(ssid, password, url);
        if (subject.socketConnect()) {
            
        }

        else TEST_FAIL_MESSAGE("UNABLE TO CONNECT TO URL");
    }

    else TEST_FAIL_MESSAGE("WIFI DISCONNECTED");
}
*/

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
        "{\"color\":\"w\","
        "\"piece\":\"r\","
        "\"from\":\"a1\","
        "\"to\":\"a4\","
        "\"flags\":\"n\"}";
    
    StaticJsonDocument<258> doc;
    DeserializationError err = deserializeJson(doc, json);
    if (err)
        TEST_FAIL_MESSAGE("ERROR DESERIALIZING JSON FILE");
    
    else {
        WirelessController subject(ssid, password, url);
        JsonMove test = subject.getMove(doc);
        std::array<uint8_t, 2> start, end;
        start = { 2, 0 };
        end   = { 2, 3 };
        JsonMove expected("n", start, end);

        if (expected.specialFlag.compare(test.specialFlag) != 0)
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
    RUN_TEST(test_WiFi_Connect);
    RUN_TEST(test_Socket_Connect);
    //RUN_TEST(test_Message_Recieved);
    RUN_TEST(test_Parse_XN_To_Array);
    RUN_TEST(test_Get_Move);
}

void loop() {
    UNITY_END();
}