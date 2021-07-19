#ifndef WIRELESSCONTROLLER_HPP
#define WIRELESSCONTROLLER_HPP

#include <Arduino.h>
#include <array>
#include <ArduinoJson.h>
#include <HTTPClient.h>

enum mode { Bluetooth, WIFI };

#define TIMEOUT 15
#define NUM_JSON_MEMBERS 7

using namespace std;

const int jsonCapacity = JSON_OBJECT_SIZE(NUM_JSON_MEMBERS);

struct JsonMove {
    uint8_t turn;
    char specialFlag;
    array<uint8_t, 2> startPos, endPos;

    JsonMove() {
        turn = 0;
        specialFlag = 'n';
        startPos = { 0, 0 };
        endPos = { 0, 0 };
    }

    /**
     * Creates a new instance of the JsonMove data structure
     * @param turn the current turn (increments after black)
     * @param flag can be n, b, e, or c
     * @param start an array with the initial coordinates (x, y)
     * @param end   an array with the terminal coordinates (x, y)
     */
    JsonMove(uint8_t turn, char flag, 
             array<uint8_t, 2> start, array<uint8_t, 2> end) {
        turn = turn;
        specialFlag = specialFlag;
        startPos = start;
        endPos = end;
    }
};

class WirelessController {
    private : 
        String password;
        String ssid;
        String url;
        uint8_t bluFiMode;
        HTTPClient httpClient;
        
    public :
        WirelessController(String pass, String ssid, String url);
        WirelessController();
        
        //--------------------------- Get Methods ---------------------------//

        String getPassword() { return password; }
        String getSSID() { return ssid; }
        String getURL() { return url; }
        int httpGet() { return httpClient.GET(); }
        WiFiClient httpGetStream() { return httpClient.getStream(); }
        
        //--------------------------- Set Methods ---------------------------//

        void setPassword(String p) { password = p; }
        void setSSID(String s) { ssid = s; }
        void setURL(String u) { url = u; }

        //========================== Helper Methods =========================//

        //---------------- Defined in WirelessController.cpp ----------------//
        
        boolean connectWiFi(String ssid, String password);
        boolean connectWiFi();
        boolean httpConnect();
        JsonMove getMove(StaticJsonDocument<jsonCapacity> doc);
        std::array<uint8_t, 2> parseXNToArray(const char* xN);
        void setMode(uint8_t mode);
        array<String, 2> getCredentials();
        boolean sendReport();
};

#endif