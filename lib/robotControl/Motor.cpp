#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include "Motor.hpp"

using namespace TMC2208_n;

/**
 * Creates a new motor with a unique id and serial connection
 * @param mID  Unique ID of the created motor
 * @param s    The HardwareSerial port ID to be used (1-2)
 * @param pins Various pins required for operation
*/
Motor::Motor(uint8_t mid, TMC2209Stepper d, uint8_t diagP, uint8_t dirP, 
              uint8_t stepP) :
              driver(d) {
    this->setPins(diagP, dirP, stepP);
    this->setPosition();
}


/**
 * Initializes required parameters for TMC2209 use. Parameters can be found in 
 * Motor.hpp
 */
boolean Motor::init() {
    this->driver.begin();
    this->driver.toff(4); // Can be any value between 1-15
    this->driver.blank_time(24);
    this->driver.rms_current(500); // mA
    this->driver.microsteps(8);
    this->driver.TCOOLTHRS(0xFFFFF);
    this->driver.semin(0);
    this->driver.semax(2);
    this->driver.shaft(false);
    this->driver.sedn(0xb01);
    this->driver.SGTHRS(STALL_VALUE);
    return true;
}

void Motor::step()  { 
    if (motorPosition != targetPosition) {
        digitalWrite(stepPin, !digitalRead(stepPin));

        switch (this->getDir()) {
            case Clockwise : 
                motorPosition += 1;
                break;
            case AntiClockwise :
                motorPosition -= 1;
                break;
        }
    }

    
}

TMC2209Stepper createDriver(HardwareSerial serial, float RS, uint8_t addr) {
    TMC2209Stepper tmp(&serial, RS, addr);
    return tmp;
}

HardwareSerial getSerial(uint8_t s) {
    switch(s) {
        case 0 :
            return Serial2;

        case 1 :
            return Serial1;

        default :
            return Serial;
    }
}