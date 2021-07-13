#ifndef WIRELESSCONTROLLER_HPP
#define WIRELESSCONTROLLER_HPP

#include <Arduino.h>
#include <array>
#include <ArduinoJson.h>

enum mode { Bluetooth, WiFi };

#define JSON_SIZE 200

class WirelessController {
    private : 
        String password;
        String ssid;
        String url;
        uint8_t bluFiMode;
        
    public :
        //--------------------------- Get Methods ---------------------------//

        String getPassword() { return password; }
        String getSSID() { return ssid; }
        String getURL() { return url; }
        
        //--------------------------- Set Methods ---------------------------//

        void setPassword(String p) { password = p; }
        void setSSID(String s) { ssid = s; }
        void setURL(String u) { url = u; }

        //========================== Helper Methods =========================//

        //---------------- Defined in WirelessController.cpp ----------------//
        String getMove();
        void setMode(uint8_t mode);
        array<String, 2> getCredentials();
        boolean sendReport();
};

#endif