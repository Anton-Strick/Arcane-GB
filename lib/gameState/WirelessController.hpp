#ifndef WIRELESSCONTROLLER_HPP
#define WIRELESSCONTROLLER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebSocketsClient.h>

#include <array>
#include <queue>

enum mode { Bluetooth, WIFI };

#define TIMEOUT 15
#define NUM_JSON_MEMBERS 7

using namespace std;

const int jsonCapacity = 512;

/**
 * JsonMoves are responsible for storing critical data found in SAN
 * @param flag can be n, b, e, or c
 * @param start an array with the initial coordinates (x, y)
 * @param end   an array with the terminal coordinates (x, y)
 */
struct JsonMove {
    string specialFlag;
    array<int8_t, 2> startPos, endPos;

    JsonMove() {
        specialFlag = "n";
        startPos = { 0, 0 };
        endPos = { 0, 0 };
    }

    JsonMove(string flag, array<int8_t, 2> start, array<int8_t, 2> end) {
        specialFlag = flag;
        startPos = start;
        endPos = end;
    }
};

void printJsonMove(JsonMove m);

/**
 * WirelessControllers are responsible for initiating a WiFi connection to a local
 * network, as well as a websocket. When web socket events are detected, a flag is
 * raised which is dealt with when WirelessController::idle() is called.
 * @param ssid the WiFi Network Name
 * @param password the WiFi Network Password
 * @param url the URL or IP address of the websocket
 */
class WirelessController {
    private : 
        String password;
        String ssid;
        String url;
        uint8_t bluFiMode;
        WebSocketsClient webSocket;
        std::queue<JsonMove> moves;

    public :
        WirelessController(String pass, String ssid, String url);
        WirelessController();
        
        //--------------------------- Get Methods ---------------------------//

        String getPassword() { return password; }
        String getSSID() { return ssid; }
        String getURL() { return url; }
        
        //--------------------------- Set Methods ---------------------------//

        void setPassword(String p) { password = p; }
        void setSSID(String s) { ssid = s; }
        void setURL(String u) { url = u; }

        //========================== Helper Methods =========================//

        bool hasJson() { return !moves.empty(); }
        void idle() { webSocket.loop(); }

        //---------------- Defined in WirelessController.cpp ----------------//
        
        boolean connectWiFi(String ssid, String password);
        boolean connectWiFi();

        /**
         * Takes the a serialized JSON file and parses it into a JsonMove Struct.
         * The new struct is placed into the Controller's queue to be accessed later.
         */
        void queueJsonMove(unsigned char * payload);

        /**
         * Takes in chars in SAN format, and returns an array with the corresponding
         * position on the board.
         */
        std::array<int8_t, 2> parseXNToArray(const char* xN);

        /**
         * Sets the ESP32s BluFi module to the appropriate mode.
         */
        void setMode(uint8_t mode);

        /**
         * Wrapper function to connect to the Websocket found at the given URL
         */
        boolean connectSocket();

        /**
         * When a socket event is registered, this function assesses the type and
         * responds accordingly. Should only be used in WirelessController
         * constructors.
         */
        void _socketEventRecieved(WStype_t type, uint8_t * payload, size_t length);

        JsonMove deQueue() { JsonMove out = moves.front(); moves.pop(); return out; }
};

#endif