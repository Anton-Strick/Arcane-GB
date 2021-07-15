#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include "config.hpp"

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
        uint32_t targetPosition = 0;

        uint8_t diagPin;
        uint8_t dirPin;
        uint8_t motorID;
        uint8_t stepPin;

        TMC2209Stepper driver;

        boolean isComplete = true;

    public:
        //-------------------------- Get Functions --------------------------//
        uint32_t getPosition() { return motorPosition; }
        uint8_t getDir() { return digitalRead(dirPin); }
        uint32_t getTarget() { return targetPosition; }
        uint8_t getID() { return motorID; }
        uint16_t getSG() { return driver.SG_RESULT(); }
        uint16_t getCS() { return driver.cs2rms(driver.cs_actual()); }
        boolean getComplete() { return isComplete; }
        //-------------------------- Set Functions --------------------------//
        void setPosition(uint32_t p) { motorPosition = p; }
        
        void setDir(uint8_t d) { digitalWrite(dirPin, d); }
        void setPins(uint8_t diagP, uint8_t dirP, uint8_t sP) {
                         diagPin = diagP;
                         dirPin = dirP;
                         stepPin = sP;
                     }
        //------------------------- Helper Functions ------------------------//
        void toggleEnable() {digitalWrite(EN_PIN, !digitalRead(EN_PIN));}
        

        //----------------------- Defined in Motor.cpp ----------------------//
        Motor(uint8_t mid, TMC2209Stepper d, uint8_t diagP, uint8_t dirP, 
              uint8_t stepP);
        
        /**
         * Initializes TMC2209 Stepper Motor Driver
        */
        boolean init();

        uint32_t getStepsToGo();

        void step();

        void displayReport();

        void setTarget(uint32_t t);
};

TMC2209Stepper createDriver(HardwareSerial serial, float RS, uint8_t addr);

#endif