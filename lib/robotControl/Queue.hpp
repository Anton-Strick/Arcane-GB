#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <Arduino.h>
#include "config.hpp"
#include "Move.hpp"

class Queue {
    private:
        uint8_t queueSize = 0;
        Move *head;
        Move *tail;

    public:
        boolean hasMoves;

        Queue();
        
        //--------------------------- Get Methods ---------------------------//

        Move getHead() { return *head; }
        Move getTail() { return *tail; }
        uint8_t getSize() { return queueSize; }
        Move getNextMove() { return head->getNext(); }

        //--------------------------- Set Methods ---------------------------//

        void setHead(Move m) { head = &m; }
        void setSize(uint8_t i) { queueSize = i; }
        void setTail(Move m) { tail = &m; }

        //========================== Helper Methods =========================//
        void enQueue(Move m);
        void enQueue(std::array<uint8_t, NUM_MOTORS> dirs, std::array<uint32_t, NUM_MOTORS> steps);
        Move deQueue();

        boolean isHead(Move m) { return ( m == *head ) ? true : false; }
};

#endif