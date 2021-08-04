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
        array<Motor *, NUM_MOTORS> motors;
        
    public:
        volatile bool moveComplete = true;
        RobotControl(); // Default Constructor
        //--------------------------- Get Methods ---------------------------//

        //--------------------------- Set Methods ---------------------------//

        //========================== Helper Methods =========================//

        void disableMagnet() { digitalWrite(MAGNET_PIN, HIGH); }
        void enableMagnet() { digitalWrite(MAGNET_PIN, LOW); }

        //------------------- Defined in RobotControl.cpp -------------------//
        void disableMotors();
        void enableMotors();
        void initializeMotors();
        void stepMotors();

        void home();

        void loadMove(Move m);

        void printReport();
};

#endif