#ifndef MOVE_HPP
#define MOVE_HPP

#include <Arduino.h>
#include "config.hpp"

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 */
class Move {
    public:
        Move* next;
        uint8_t direction[NUM_MOTORS];
        uint32_t numSteps[NUM_MOTORS];

        Move(); // Default Constructor
        //----------------------- Defined in Move.cpp -----------------------//
        
        Move(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]);
        void destroy();
};

#endif