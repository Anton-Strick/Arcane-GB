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