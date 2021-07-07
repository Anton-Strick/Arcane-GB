#include <Arduino.h>
#include "Queue.hpp"

Queue::Queue() {
    this->hasMoves = false;
    this->head = new Move();
    this->tail = this->head;
}

/**
 * Places a pre-existing move in the queue
 * @param m {Move} a valid Move object. It's 'next' pointer will be lost
 */
void Queue::enQueue(Move* m) {
    this->tail->setNext(m); // Inserts node at end of list
    this->setTail(this->tail->getNext());  // Move becomes the tail
    this->tail->setNext(this->head); // Preserve the loop

    if (!this->hasMoves)
        this->hasMoves = true;

    this->setSize(this->getSize() + 1);
}

/**
 * Places a new move generated from the given parameters in the queue
 * @param dirs {uint8_t[NUM_MOTORS]} Contains the direction flag of each motor 
 *                                   contained at the corresponding index
 * @param steps {uint32_t[NUM_MOTORS]} Contains the number of steps required 
 *                                     from each motor, respectively.
 */
void Queue::enQueue(uint8_t dirs[NUM_MOTORS], uint32_t steps[NUM_MOTORS]) {
    Move* newMove = new Move(dirs, steps);
    this->enQueue(newMove);
}

Move* Queue::deQueue() {
    if (this->tail == this->head) {
        this->hasMoves = false;
        return this->head; // Cannot deQ
    }

    else {
        Move* tmp = this->head->getNext(); // Isolate desired move

        if (tmp == this->tail) { // On Empty
            this->tail = this->head;
            this->tail->setNext(this->head);
            this->hasMoves = false;
        }
        this->head->setNext(tmp->getNext()); // Remove from queue

        this->setSize(this->getSize() - 1);
        return tmp; // Return freshly de-queued move
    }
}