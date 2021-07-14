/** Notes for Testing
 *  - Our motors use 200 steps per revolution
 *  - This test includes use of config.h for setup
      Procedures
 */

#include <Arduino.h>
#include "robotControl.hpp"
#include "config.hpp"

void setup() {
     //------------------------------ Connect to Computer ------------------------------//
    Serial.begin(9600); // Make sure your system is communicating at this Baud
    while (!Serial);

     /**
      * TODO
      * - Initialize robotController
      * - run init method
      * - queue moves
      * - enable motors
      */
}

void loop() {
     /**
      * TODO 
      * - Multi-proto-threading implementation
      * - T1A:  Queue Management
      * - T1B:  Wireless Communications
      * - T2A:  Motor Control
      */
}