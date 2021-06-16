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
Motor::Motor(uint8_t mID, uint8_t s, uint8_t diagP, uint8_t dirP, 
              uint8_t sP, uint8_t rxP, uint8_t txP) : 
                mcuSerial(HardwareSerial(s)),
                driver(TMC2209Stepper(&mcuSerial, R_SENSE, DRIVER_ADDRESS)) {
    this->setID(mID);
    this->setSerial(s);
    this->setPins(diagP, dirP, sP, rxP, txP);
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