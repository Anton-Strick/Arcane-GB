#ifndef MOTORCONTROL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>
#include <Motor.hpp>
#include <Queue.hpp>

class robotControl {
    private:
        Queue q;
        Motor motors[NUM_MOTORS];
    public:
        //-------------------------- Get Functions --------------------------//


        //-------------------------- Set Functions --------------------------//


        //------------------- Defined in robotControl.cpp -------------------//
        void queueMove(Move m);
};

#endif