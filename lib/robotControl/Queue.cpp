#include <Arduino.h>
#include "Queue.hpp"

Queue::Queue() {

}

/**
 * Places a new move generated from the given parameters in the queue
 * @param dirs {uint8_t[NUM_MOTORS]} Contains the direction flag of each motor 
 *                                   contained at the corresponding index
 * @param steps {uint32_t[NUM_MOTORS]} Contains the number of steps required 
 *                                     from each motor, respectively.
 */
void Queue::enQueue(std::array<uint8_t, NUM_MOTORS> dirs, std::array<uint32_t, NUM_MOTORS> steps) {
    Move* newMove = new Move(dirs, steps);
    enQueue(*newMove);
}

Move Queue::deQueue() {
    Move out = stdQueue.front();
    stdQueue.pop();
    return out;
}