#include <Arduino.h>
#include "Queue.hpp"

Queue::Queue() {
    hasMoves = false;
    head = new Move();
    tail = head;
}

/**
 * Places a pre-existing move in the queue
 * @param m {Move} a valid Move object. It's 'next' pointer will be lost
 */
void Queue::enQueue(Move m) {
    m.setNext(*head);
    tail->setNext(m); // Inserts node at end of list
    setTail(tail->getNext());  // Move becomes the tail

    if (!hasMoves)
        hasMoves = true;

    setSize(getSize() + 1);
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
    if (!hasMoves) {
        return *head; // Cannot deQ
    }

    else {
        Move tmp = head->getNext(); // Isolate desired move

        if (tmp.getNext() == getHead()) { // On last move
            hasMoves = false;
        } // End on Last Move

        head->setNext(tmp.getNext());

        queueSize -= 1;
        
        return tmp; // Return freshly de-queued move
    }
}