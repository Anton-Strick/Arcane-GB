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
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);

    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    TMC2209Stepper driver1(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    motors[0] = new Motor((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);
    motors[1] = new Motor((uint8_t) 1, driver1, DIAG_PIN1, DIR_PIN1, STEP_PIN1);

    for (Motor* m : motors) {
        m->init();
    }

    configMotorPins(); // located in config
}

/**
 * Initilializes a blank queue to be assigned to the Robot Control Class
 */
void RobotControl::initializeQueue() {

}

void RobotControl::stepMotors() {
    for (Motor* m : this->motors) {
        m->step();
    }
}

/**
 * Converts cartesian movement into coreXY movement
 * @param {int16_t} dX The number of steps in the X direction
 * @param {int16_t} dY The number of steps in the Y direction
 * @return Move containing the direction and number of steps required
 *         to achieve the desired motion
 */
Move RobotControl::xyToMotors(int16_t dX, int16_t dY) {
    int16_t dA = (0.5) * (dX + dY);
    int16_t dB = (0.5) * (dX - dY);

    uint8_t dirs[NUM_MOTORS];
    dirs[0] = (dA > 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB > 0) ? AntiClockwise : Clockwise;

    uint32_t steps[NUM_MOTORS];
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    Move newMove(dirs, steps);
    return newMove;
}