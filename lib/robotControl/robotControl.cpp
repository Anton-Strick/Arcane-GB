#include <Arduino.h>
#include "RobotControl.hpp"

/**
 * Creates a blank instance of RobotControl. Requires the user to call 
 * "this.intializeMotors() in order to function properly."
 */
RobotControl::RobotControl() {
    
}

/**
 * Sets the motors to DISABLED using the pins defined in config.hpp
 */
void RobotControl::disableMotors() { 
    digitalWrite(EN_PIN0, HIGH);
    digitalWrite(EN_PIN1, HIGH);
}

/**
 * Sets the motors to ENABLED using the pins defined in config.hpp
 */
void RobotControl::enableMotors() { 
    digitalWrite(EN_PIN0, LOW);
    digitalWrite(EN_PIN1, LOW); 
}

/**
 * Initializes all required components of the Motors controlled by this
 * instance of RobotControl. (Serial, TMC2209Stepper, Motor Pins)
 */
void RobotControl::initializeMotors() {
    configPins(); // located in config
    
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    TMC2209Stepper driver1(&SERIAL_PORT1, R_SENSE, DRIVER_ADDRESS);
    motors[0] = new Motor((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);
    motors[1] = new Motor((uint8_t) 1, driver1, DIAG_PIN1, DIR_PIN1, STEP_PIN1);

    for (Motor * m : motors) {
        m->init();
    }
}

void RobotControl::stepMotors() {
    bool temp = true;
    for (Motor * m : this->motors) {
        m->step();
        temp = temp && m->getComplete();
    }

    moveComplete = temp;
}

void RobotControl::loadMove(Move m) {
    if (m.getMagnetEnabled()) {
        enableMagnet();
        delay(250);
    }

    else {
        disableMagnet();
    }

    for (int8_t i = 0 ; i < NUM_MOTORS ; i++) {
        motors[i]->setDir(m.getDirs()[i]);
        motors[i]->setTarget(m.getSteps()[i]);
    }

    moveComplete = false;
}


void RobotControl::home() {

}

void RobotControl::printReport() {
    Serial.println("========== R-Control Report ===========");
    motors[0]->displayReport();
    motors[1]->displayReport();
}