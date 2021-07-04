#include <Arduino.h>
#include "Move.hpp"

/**
 * Constructs a new Move instance with -1 steps. Used for head
 * and tail of a Queue.
*/
Move::Move() {
    this->next = NULL;
    for (int i = 0; i < NUM_MOTORS; i++) {
        this->direction[i] = Clockwise;
        this->numSteps[i] = -1;
    }
}

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 * @param {uint8_t[NUM_MOTORS]} An array containing the direction
 *        flag of each motor contained at the corresponding index
 * @param {uint32_t[NUM_MOTORS]} An array containing the number of
 *        steps required from each motor, respectively.
 */
Move::Move(uint8_t dirs[NUM_MOTORS], uint32_t steps[NUM_MOTORS]) {
    this->next = NULL;
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        this->direction[i] = dirs[i];
        this->numSteps[i] = steps[i];
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