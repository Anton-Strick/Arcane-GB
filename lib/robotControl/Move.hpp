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
        Move(std::array<uint8_t, NUM_MOTORS> d, std::array<uint32_t, NUM_MOTORS> s);

        //--------------------------- Get Methods ---------------------------//

        Move* getNext() {return next; }
        std::array<uint8_t, NUM_MOTORS> getDirs() { return direction; }
        std::array<uint32_t, NUM_MOTORS> getSteps() {return numSteps; }

        //--------------------------- Set Methods ---------------------------//

        void setNext(Move m) { next = &m; }

        //========================== Helper Methods =========================//
        
        void destroy();

        void printMove();
};

#endif