#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>

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

        HardwareSerial mcuSerial;
        TMC2209Stepper driver;

    public:
        Motor(uint8_t mID, uint8_t s);
        //-------------------------- Get Functions --------------------------//
        int getID() { return motorID; }
        int getPosition() { return motorPosition; };
        //-------------------------- Set Functions --------------------------//
        void setPosition() { motorPosition = 0; }
        void setTarget(uint32_t t) { targetPosition = t; }
        //------------------------- Helper Functions ------------------------//
        void toggleEnable() {digitalWrite(EN_PIN, !digitalRead(EN_PIN));}

        //------------------- Defined in robotControl.cpp -------------------//
        boolean init();
};

#endif