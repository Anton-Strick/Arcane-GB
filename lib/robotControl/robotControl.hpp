#ifndef MOTORCONTROL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>
#include <Motor.hpp>
#include <Queue.hpp>
#include "config.hpp"


/**
 * Primary high-level control class for the H-Bot.
 * @param q The current Queue of Moves planned by the 
 *                      RobotController
 * @param motors An array containing members of the Motor class used by the 
 *               RobotController with parameters defined in config.hpp
 */
class RobotControl {
    private:
        Queue* queue;
        Motor* motors[NUM_MOTORS];
    public:
        boolean moveComplete;
        RobotControl(); // Default Constructor
        //--------------------------- Get Methods ---------------------------//


        //--------------------------- Set Methods ---------------------------//
        

        //========================== Helper Methods =========================//
        /**
         * Places a Move in the queue of the RobotController
         */
        void queueMove(Move* m) { this->queue->enQueue(m); }
        /**
         * Dequeues the next move in the RobotController's queue
         * @return The Move just dequeued
         */
        Move* dequeueMove(); 
        //------------------- Defined in RobotControl.cpp -------------------//
        void disableMotors();
        void enableMotors();

        void initializeMotors();
        void initializeQueue();

        void stepMotors();

        void printReport();
        
        Move* xyToMotors(int16_t dx, int16_t dy);
        void loadMove(Move* m);
};

#endif