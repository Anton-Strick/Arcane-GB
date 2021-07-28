#include <Arduino.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#include <array>
#include <string>

#include "WirelessController.hpp"

WirelessController::WirelessController(String s, String p, String u) {
    ssid = s;
    password = p;
    url = u;
    bluFiMode = WIFI;
    webSocket.onEvent([this](WStype_t type, uint8_t * payload, size_t length) {
        socketEventRecieved(type, payload, length);
    });
}

WirelessController::WirelessController() {
    bluFiMode = WIFI;

}

boolean WirelessController::connectWiFi(String ssid, String password) {
    const char* tmpSSID =  ssid.c_str();
    const char* tmpPass = password.c_str();

    Serial.printf("\n======= Connecting to Wifi  =======\n");
    Serial.print("SSID:      ");
    Serial.println(ssid);
    Serial.print("Password:  ");
    Serial.println(password);
    WiFi.begin(tmpSSID, tmpPass);

    for (int i = 0 ; i < TIMEOUT || WiFi.status() != WL_CONNECTED ; i++) {
        Serial.println("...");
        delay(250); // Waiting to connect
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("Successfully connected!\n\n");
        return true;
    }

    else {
        Serial.printf("ERROR:  COULD NOT CONNECT\n\n");
        return false;
    }
}

boolean WirelessController::connectWiFi() {
    return connectWiFi(ssid, password);
}

boolean WirelessController::socketConnect() {
    if (WiFi.status() != WL_CONNECTED)
        return false;
    webSocket.begin(url, 8000);

    return true;
}

void WirelessController::queueJsonMove(unsigned char * payload) {
    static uint8_t move = 1;
    String jsonString( reinterpret_cast< char const *> (payload) );
    std::string specialFlag;

    StaticJsonDocument<jsonCapacity> doc;
    DeserializationError err = deserializeJson(doc, jsonString);

    if (!err) {
        std::array<int8_t, 2> start, end;
        try {
            Serial.printf("Move %d: ", move++);
            specialFlag = doc["flags"].as<string>();
            start = parseXNToArray(doc["from"].as<const char *>());
            Serial.printf("%s to ", doc["from"].as<const char *>());

            end = parseXNToArray(doc["to"].as<const char*>());
            Serial.printf("%s\n", doc["to"].as<const char *> ());

            JsonMove out(specialFlag, start, end);
            moves.push(out);
        } catch (...) {
            Serial.println("ERROR:  COULD NOT getMove!");
        }
    }
}

std::array<int8_t, 2> WirelessController::parseXNToArray(const char* xN) {
    std::array<int8_t, 2> out;
    /**
     * Since only lowercase, the char can be converted to decimal with
     * a logical AND operation
     *          a = 0110 0001, ... , z = 0111 1010
     *     a & 0x1f = 0110 0001 * 0001 1111 = 0000 0001 (d1)
     *     z & 0x1f = 0111 1010 * 0001 1111 = 0001 1010 (d26)
     */
    out[0] = (xN[0] & 0x1f) - 1; // a = 0
    out[1] = (xN[1] & 0xf) + 1;  // Must account for the graveyard
    return out;
}


void WirelessController::socketEventRecieved(WStype_t type, uint8_t * payload, size_t length) {
    switch (type) {
        case WStype_DISCONNECTED : 
            Serial.println("[WebSocket] Disconnected");
            break;
        
        case WStype_CONNECTED :
            Serial.println("[WebSocket] Connected");
            break;

        case WStype_TEXT : 
            queueJsonMove(payload);
            break;

        case WStype_BIN :
            Serial.println("[WebSocket] Recieved Binary");
            break;
        
        case WStype_ERROR :
            Serial.println("[WebSocket] ERROR");
        default :
            break;
    }
}

void printJsonMove(JsonMove m) {
    Serial.printf("--------- JSON Move ---------\n");
    Serial.printf("Start:   %u, %u\n", m.startPos[0], m.startPos[1]);
    Serial.printf("End:     %u, %u\n", m.endPos[0], m.endPos[1]);
    Serial.printf("Special: %s", m.specialFlag.c_str());
    Serial.println();
}