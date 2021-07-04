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
        void enQ(Move m);
        void enQ(uint8_t d[NUM_MOTORS], uint32_t s[NUM_MOTORS]);
        Move deQ();
};

#endif