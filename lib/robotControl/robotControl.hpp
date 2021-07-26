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
        array<int8_t, 2> currentPosition;
        
    public:
        bool moveComplete = true;
        RobotControl(); // Default Constructor
        //--------------------------- Get Methods ---------------------------//

        Move getNextMove() { return queue.getNextMove(); }
        Move getLastMove() { return queue.getTail(); }
        array<int8_t, 2> getCurrentPosition() { return currentPosition; }

        bool hasMoves() { return queue.hasMoves(); };

        //--------------------------- Set Methods ---------------------------//
        
        void setCurrentPosition(array<int8_t, 2> pos) { currentPosition = pos; }

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

        void transpose(uint8_t indicator, bool toJunction = false);
        void home();

        void loadMove();
        void queueMoves(Queue q);

        void changePosition(std::array<int8_t, 2> delta);

        void printReport();
};

#endif