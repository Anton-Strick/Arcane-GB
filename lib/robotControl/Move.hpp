#ifndef MOVE_HPP
#define MOVE_HPP

#include <Arduino.h>

#include <array>

#include "config.hpp"

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 */
class Move {
    private :
        Move* next;
        std::array<uint8_t, NUM_MOTORS> direction;
        std::array<uint32_t, NUM_MOTORS> numSteps;

    public :
        Move(); // Default Constructor
        Move(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]);

        //--------------------------- Get Methods ---------------------------//

        Move* getNext() {return this->next; }
        std::array<uint8_t, NUM_MOTORS> getDirs() { return direction; }
        std::array<uint32_t, NUM_MOTORS> getSteps() {return numSteps; }

        //--------------------------- Set Methods ---------------------------//

        void setNext(Move* m) { this->next = m; }

        //========================== Helper Methods =========================//
        
        void destroy();

        void printMove();
};

#endif