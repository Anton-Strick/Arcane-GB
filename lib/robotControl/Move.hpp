#ifndef MOVE_HPP
#define MOVE_HPP

#include <Arduino.h>
#include "config.hpp"

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 */
class Move {
    private :
        Move* next;
        uint8_t direction[NUM_MOTORS];
        uint32_t numSteps[NUM_MOTORS];

    public :
        Move(); // Default Constructor
        Move(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]);

        //--------------------------- Get Methods ---------------------------//

        Move* getNext() {return this->next; }
        uint8_t* getDirs() { return this->direction; }
        uint32_t* getSteps() {return this->numSteps; }

        //--------------------------- Set Methods ---------------------------//

        void setNext(Move* m) { this->next = m; }

        //========================== Helper Methods =========================//
        
        void destroy();
};

#endif