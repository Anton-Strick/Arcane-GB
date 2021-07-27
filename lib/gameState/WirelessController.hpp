#ifndef WIRELESSCONTROLLER_HPP
#define WIRELESSCONTROLLER_HPP

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <ArduinoWebsockets.h>

#include <array>
#include <queue>

enum mode { Bluetooth, WIFI };

#define TIMEOUT 15
#define NUM_JSON_MEMBERS 7

using namespace std;

const int jsonCapacity = 512;

struct JsonMove {
    string specialFlag;
    array<int8_t, 2> startPos, endPos;

    JsonMove() {
        specialFlag = "n";
        startPos = { 0, 0 };
        endPos = { 0, 0 };
    }

    /**
     * Creates a new instance of the JsonMove data structure
     * @param flag can be n, b, e, or c
     * @param start an array with the initial coordinates (x, y)
     * @param end   an array with the terminal coordinates (x, y)
     */
    JsonMove(string flag, array<int8_t, 2> start, array<int8_t, 2> end) {
        specialFlag = flag;
        startPos = start;
        endPos = end;
    }
};

void printJsonMove(JsonMove m);

class WirelessController {
    private : 
        String password;
        String ssid;
        String url;
        uint8_t bluFiMode;
        websockets::WebsocketsClient webSocket;
        JsonMove newMove;
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

        //---------------- Defined in WirelessController.cpp ----------------//
        
        boolean connectWiFi(String ssid, String password);
        boolean connectWiFi();

        /**
         * Takes a deserialized JSON file and loads it into a struct
         * containing only unsigned integers and a char – saves space in the
         * stack during runtime and avoids memory leaks. from JsonDocument
         */
        void queueJsonMove(StaticJsonDocument<jsonCapacity> doc);
        std::array<int8_t, 2> parseXNToArray(const char* xN);
        void setMode(uint8_t mode);

        boolean socketConnect();
        static void socketMessageRecieved(websockets::WebsocketsMessage message);

        JsonMove deQueue() { JsonMove out = moves.front(); moves.pop(); return out; }
};

#endif