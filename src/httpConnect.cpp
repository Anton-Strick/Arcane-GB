#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#include "config.h"
#include "robotControl.hpp"


/* * * * * * * * * * * * * * * * * * * * * * * * * *
 * Replace these values with your local variables  *
 * * * * * * * * * * * * * * * * * * * * * * * * * */
  const char* ssid = "The Pack Net";               //
  const char* password = "3a$tmarInternet11202";   //
  const char* url = "http://example.com/index.html";//
/////////////////////////////////////////////////////

String move; // Contains last move from server

unsigned long lastTime = 0;      // TODO: Replace with ISR
unsigned long timerDelay = 5000; // ^^^^^^^^^^^^^^^^^^^^^^

/*
 * Initializes a serial connection (Baud = 115200), a WiFi Connection
 * with the network denoted by ssid. Serial connection is used to
 * confirm status
 */
void setup() {
  Serial.begin(9600); // Should be the correct Baud

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi!\n\n");
}

/* 
 * Checks for a new move every 5 seconds for a new move posted from  
 * the server                                                        
 */
void loop() {
  static uint32_t lastTime = 0;
  static uint16_t count = 0;
  uint32_t ms = millis();
  if ((ms - lastTime) > timerDelay) {
    lastTime = ms;
    // Check WiFi status, cannot transmit if unconnected
    if (WiFi.status() == WL_CONNECTED) {
      count += 5;
      Serial.print(count);
      Serial.println(" seconds since connection...");

      //---------------------- Connect to HTTP Server ------------------//
      HTTPClient client;
      Serial.println("Connecting to HTTP server...");
      while (!client.begin(url)) {
        Serial.println("...");
      } // End connection loop
      Serial.printf("Connected to %s!\n", url);

      int32_t httpCode = (int32_t) client.GET();

      //------------------- Recieve Move from Server -------------------//
      if (httpCode > 0) {
        move = client.getString();
        if (move != NULL) {
          Serial.printf("\nRecieved new move:"  );
          Serial.println(move);
        } // End received move

        else {
          Serial.println("\nNo move found...\n");
        } // End no recieved move
      }

      else Serial.printf("\nRecieved error code:  %d\n", httpCode);
      
    } // End WiFi Connected
    
    else {
      Serial.println("ERROR: LOST WIFI CONNECTION");
      count += 5;
    } // End WiFi Unconnected
  }
}