#ifndef MOTORCONTROL_HPP
#define MOTORCONTROL_HPP

#include <Arduino.h>

#include <array>

#include <Motor.hpp>
#include <Queue.hpp>
#include "config.hpp"

using namespace std;

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
        array<Motor *, NUM_MOTORS> motors;
        array<uint8_t, 2> currentPosition;
        
    public:
        bool moveComplete = true;
        RobotControl(); // Default Constructor
        //--------------------------- Get Methods ---------------------------//

        Move getNextMove() { return queue.getNextMove(); }
        array<uint8_t, 2> getCurrentPosition() { return currentPosition; }

        //--------------------------- Set Methods ---------------------------//
        
        void setCurrentPosition(array<uint8_t, 2> pos) { currentPosition = pos; }

        //========================== Helper Methods =========================//
        /**
         * Places a Move in the queue of the RobotController
         */
        void queueMove(Move m) { queue.enQueue(m); }

        /**
         * Dequeues the next move in the RobotController's queue
         * @return The Move just dequeued
         */

        Move dequeueMove() { return queue.deQueue(); } 
        void disableMagnet() { digitalWrite(MAGNET_PIN, HIGH); }
        void enableMagnet() { digitalWrite(MAGNET_PIN, LOW); }

        //------------------- Defined in RobotControl.cpp -------------------//
        void disableMotors();
        void enableMotors();
        void initializeMotors();
        void stepMotors();

        void transpose(uint8_t indicator);

        void loadMove();
        void queueMoves(Queue q);

        void printReport();
};

Move xyToMotors(int8_t dx, int8_t dy, bool mE = false);

#endif