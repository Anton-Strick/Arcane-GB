#include <Arduino.h>
#include "Queue.hpp"

Queue::Queue() {
    this->hasMoves = false;
    this->head = new Move();
    this->tail = this->head;
}

void Queue::enQ(Move m) {
    this->tail->next = &m; // Inserts node at end of list
    this->tail = this->tail->next; // Move becomes the tail
    this->tail->next = this->head; // Tail loops to head

    if (!this->hasMoves)
        this->hasMoves = true;
}

void Queue::enQ(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]) {
    Move* newMove = new Move(d, s);
    
    this->tail->next = newMove; // Inserts node at end
    this->tail = this->tail->next; // Tail is maintained
    this->tail->next = head; // List loops

    if (!this->hasMoves)
        this->hasMoves = true; // Alert Moves are available
}

Move Queue::deQ() {
    if (this->tail == this->head) {
        this->hasMoves = false;
        return *this->head; // Cannot deQ
    }

    else {
        Move* tmp = this->head->next; // Isolate desired move

        if (tmp == this->tail) { // On Empty
            this->tail = this->head;
            this->tail->next = this->head;
            this->hasMoves = false;
        }
        this->head->next = tmp->next; // Remove from queue
        return *tmp; // Return freshly de-queued move
    }
}