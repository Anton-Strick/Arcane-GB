#include <Arduino.h>
#include "Move.hpp"

/**
 * Constructs a new Move instance with -1 steps. Additionally, the 'next' 
 * pointer points to itself - lending itself to be used as a head/tail
*/
Move::Move() {
    next = this;
    for (int i = 0; i < NUM_MOTORS; i++) {
        direction[i] = Clockwise;
        numSteps[i] = -1; //uint = 4294967295
    }
}

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 * @param dirs {uint8_t[NUM_MOTORS]} Contains the direction flag of each motor 
 *                                   contained at the corresponding index
 * @param steps {uint32_t[NUM_MOTORS]} Contains the number of steps required 
 *                                     from each motor, respectively.
 */
Move::Move(uint8_t dirs[NUM_MOTORS], uint32_t steps[NUM_MOTORS]) {
    next = this;
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        direction[i] = dirs[i];
        numSteps[i] = steps[i];
    }
}

/**
 * Deallocates the memory assigned to the Move instance
 */ 
void Move::destroy() {
    delete this->direction;
    delete this->next;
    delete this->numSteps;
    delete this;
}

/**
 * Prints out the direction and steps to be taken in a particular move.
 * (Includes a newline character)
 */
void Move::printMove() {
    Serial.printf("M0 - %d, %d steps | M1 - %d, %d steps\n", 
                   this->direction[0], this->numSteps[0],
                   direction[1], numSteps[1]);
}