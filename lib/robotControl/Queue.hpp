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

        Move* getHead() { return this->head; }
        Move* getTail() { return this->tail; }
        uint8_t getSize() { return this->queueSize; }

        //--------------------------- Set Methods ---------------------------//

        void setHead(Move* m) { this->head = m; }
        void setSize(uint8_t i) { this->queueSize = i; }
        void setTail(Move* m) { this->tail = m; }

        //========================== Helper Methods =========================//
        void enQueue(Move* m);
        void enQueue(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]);
        Move deQueue();
};

#endif