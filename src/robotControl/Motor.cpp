#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>
#include "Motor.hpp"

using namespace TMC2208_n;

Motor::Motor(uint8_t mID, uint8_t s) : mcuSerial(HardwareSerial(s)),
             driver(TMC2209Stepper(&mcuSerial, R_SENSE, DRIVER_ADDRESS)) {
    motorID = mID;
    mcuSerial = s;
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
}