#include <Arduino.h>
#include "WirelessController.hpp"
#include <WiFi.h>
#include <HTTPClient.h>

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