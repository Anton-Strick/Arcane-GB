#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * Replace these values with your local variables  *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
  const char* ssid = "The Pack Net";               //
  const char* password = "3a$tmarInternet11202";   //
  const char* url = "url";                         //
/////////////////////////////////////////////////////

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed, Rebooting...");
        delay(5000);
        ESP.restart();
    }
}