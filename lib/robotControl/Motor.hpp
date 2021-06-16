#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include "robotControl.hpp"

#define DRIVER_ADDRESS     0b00        // TMC2209 Driver address
#define R_SENSE            0.11f       // E_SENSE for current calc.  
#define STALL_VALUE        2           // [0..255]
#define EN_PIN             14          // Active Low

using namespace TMC2208_n;


/**
 * Configures TMC2209 motor with defined ID, and serial port.
 * @param mID Unique ID of this motor
 * @param s   HardwareSerial port to communicate with. (1-2)
*/ 
class Motor {
    private:
        uint32_t motorPosition = 0;
        uint32_t targetPosition;
        uint8_t motorID;

        uint8_t diagPin;
        uint8_t dirPin;
        uint8_t stepPin;
        uint8_t rxPin;
        uint8_t txPin;

        HardwareSerial mcuSerial;
        TMC2209Stepper driver;

    public:
        //-------------------------- Get Functions --------------------------//
        int getID() { return motorID; }
        uint32_t getPosition() { return motorPosition; }
        uint8_t getDirPin() { return dirPin; }
        //-------------------------- Set Functions --------------------------//
        void setPosition() { motorPosition = 0; }
        void setTarget(uint32_t t) { targetPosition = t; }
        void setID(uint8_t mID) { motorID = mID; }
        void setSerial(uint8_t s) { mcuSerial = s; }
        void setDir(uint8_t d) { digitalWrite(dirPin, d); }
        void setPins(uint8_t diagP, uint8_t dirP, uint8_t sP, 
                     uint8_t rxP, uint8_t txP) {
                         diagPin = diagP;
                         dirPin = dirP;
                         stepPin = sP;
                         rxPin = rxP;
                         txPin = txP;
                     }
        //------------------------- Helper Functions ------------------------//
        void toggleEnable() {digitalWrite(EN_PIN, !digitalRead(EN_PIN));}
        void step() { digitalWrite(stepPin, !digitalRead(stepPin)); }

        //----------------------- Defined in Motor.cpp ----------------------//
        Motor(uint8_t mID, uint8_t s, uint8_t diagP, uint8_t dirP, 
              uint8_t sPin, uint8_t rxP, uint8_t txP);
        /**
         * Initializes TMC2209 Stepper Motor Driver
        */
        boolean init();
};

#endif