#ifndef MOTORCONTROL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>
#include <Motor.hpp>
#include <Queue.hpp>

class robotControl {
    private:
        Queue q;
        Motor* motors[NUM_MOTORS];
    public:
        //-------------------------- Get Functions --------------------------//


        //-------------------------- Set Functions --------------------------//
        

        //------------------------ Helper Functions -------------------------//
        void enableMotors() { 
            digitalWrite(EN_PIN0, LOW);
            digitalWrite(EN_PIN1, LOW); 
        }

        void queue(Move m) {
            q.enQ(m);
        }

        Move dequeue() {
            return q.deQ();
        }

        void disableMotors() { 
            digitalWrite(EN_PIN0, HIGH);
            digitalWrite(EN_PIN1, HIGH);
        }

        //------------------- Defined in robotControl.cpp -------------------//
        void queueMove(Move m);
        Move xyToMotors(int16_t dx, int16_t dy);
        void initializeMotors();
};

#endif