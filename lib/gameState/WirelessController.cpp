#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "WirelessController.hpp"

#include <array>

WirelessController::WirelessController(String s, String p, String u) {
    ssid = s;
    password = p;
    url = u;
    bluFiMode = WIFI;
}

boolean WirelessController::connectWiFi(String ssid, String password) {
    const char* tmpSSID =  ssid.c_str();
    const char* tmpPass = password.c_str();

    WiFi.begin(tmpSSID, tmpPass);

    for (int i = 0 ; i < TIMEOUT || WiFi.status() != WL_CONNECTED ; i++) {
        delay(250); // Waiting to connect
    }

    if (WiFi.status() == WL_CONNECTED)
        return true;

    else return false;
}

boolean WirelessController::connectWiFi() {
    return connectWiFi(ssid, password);
}

boolean WirelessController::httpConnect() {
    return httpClient.begin(url);
}

JsonMove WirelessController::getMove(StaticJsonDocument<jsonCapacity> doc) {
    uint8_t turn;
    char specialFlag;
    std::array<uint8_t, 2> start, end;

    turn = doc["turn"].as<uint8_t>();
    specialFlag = doc["flag"].as<char>();
    start = parseXNToArray(doc["from"].as<const char*>());
    end = parseXNToArray(doc["to"].as<const char*>());
    
    return JsonMove(turn, specialFlag, start, end);
}

std::array<uint8_t, 2> WirelessController::parseXNToArray(const char* xN) {
    std::array<uint8_t, 2> out;
    /**
     * Since only lowercase, the char can be converted to decimal with
     * a logical AND operation
     *          a = 0110 0001, ... , z = 0111 1010
     *     a & 0x1f = 0110 0001 * 0001 1111 = 0000 0001 (d1)
     *     z & 0x1f = 0111 1010 * 0001 1111 = 0001 1010 (d26)
     */
    out[0] = (xN[0] & 0x1f) - 1; // a = 0, not 1
    out[1] = (xN[1] & 0xf) - 1; // Similar Process
    return out;
}