#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#include <array>

#include "WirelessController.hpp"

WirelessController::WirelessController(String s, String p, String u) {
    ssid = s;
    password = p;
    url = u;
    bluFiMode = WIFI;
    //webSocket.onMessage(socketMessageRecieved);
}

WirelessController::WirelessController() {
    
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

boolean WirelessController::socketConnect() {
    if (WiFi.status() != WL_CONNECTED)
        connectWiFi(ssid, password);
    return webSocket.connect(url, 8080, "/");
}

JsonMove WirelessController::getMove(StaticJsonDocument<jsonCapacity> doc) {
    string specialFlag;
    std::array<uint8_t, 2> start, end;

    try {
        specialFlag = doc["flags"].as<string>();
        start = parseXNToArray(doc["from"].as<const char*>());
        end = parseXNToArray(doc["to"].as<const char*>());
    } catch (...) {
        Serial.println("ERROR:  COULD NOT getMove!");
    }
    
    
    return JsonMove(specialFlag, start, end);
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
    out[0] = (xN[0] & 0x1f) + 1; // a = 2, not 0, due to graveyard
    out[1] = (xN[1] & 0xf) - 1; // Similar Process. No side
    return out;
}


void WirelessController::socketMessageRecieved(websockets::WebsocketsMessage message) {
    StaticJsonDocument<jsonCapacity> doc;
    DeserializationError err = deserializeJson(doc, message.data());
    newMove = getMove(doc);
}

void printJsonMove(JsonMove m) {
    Serial.printf("--------- JSON Move ---------\n");
    Serial.printf("Start:   %u, %u\n", m.startPos[0], m.startPos[1]);
    Serial.printf("End:     %u, %u\n", m.endPos[0], m.endPos[1]);
    Serial.printf("Special: %s", m.specialFlag.c_str());
    Serial.println();
}