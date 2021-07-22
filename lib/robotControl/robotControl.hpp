#ifndef MOTORCONTROL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>

#include <array>

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
        Queue queue;
        std::array<Motor *, NUM_MOTORS> motors;
        
    public:
        bool moveComplete = true;
        RobotControl(); // Default Constructor
        //--------------------------- Get Methods ---------------------------//


        //--------------------------- Set Methods ---------------------------//
        

        //========================== Helper Methods =========================//
        /**
         * Places a Move in the queue of the RobotController
         */
        void queueMove(Move m) { queue.enQueue(m); }
        /**
         * Dequeues the next move in the RobotController's queue
         * @return The Move just dequeued
         */
        Move dequeueMove(); 
        void disableMagnet() { digitalWrite(MAGNET_PIN, HIGH); }
        void enableMagnet() { digitalWrite(MAGNET_PIN, LOW); }
        //------------------- Defined in RobotControl.cpp -------------------//
        void disableMotors();
        void enableMotors();

        void initializeMotors();

        void stepMotors();
        void loadMove();

        void printReport();
        
        Move xyToMotors(int16_t dx, int16_t dy);
};

#endif