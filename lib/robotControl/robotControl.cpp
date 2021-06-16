#include <Arduino.h>
#include "robotControl.hpp"


void robotControl::queueMove(Move m) {
    this->q.enQ(m);
}