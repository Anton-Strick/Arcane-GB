#include <Arduino.h>
#include "robotControl.hpp"


void robotControl::queueMove(Move m) {
    this->q.enQ(m);
}

Move robotControl::xyToMotors(int16_t dX, int16_t dY) {
    int16_t dA = dX + dY;
    int16_t dB = dX - dY;

    uint8_t dirs[NUM_MOTORS];
    dirs[0] = (dA > 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB > 0) ? AntiClockwise : Clockwise;

    uint32_t steps[NUM_MOTORS];
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    Move newMove(dirs, steps);
    return newMove;
}

void robotControl::initializeMotors() {
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