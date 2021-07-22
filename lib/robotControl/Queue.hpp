#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <Arduino.h>

#include <array>
#include <queue>

#include "config.hpp"
#include "Move.hpp"

class Queue {
    private :
        std::queue<Move> stdQueue;

    public :
        Queue();
        
        //--------------------------- Get Methods ---------------------------//

        Move getHead() { return stdQueue.front(); }
        Move getTail() { return stdQueue.back(); }
        uint8_t getSize() { return stdQueue.size(); }
        Move getNextMove() { return getHead(); } // Kept for depracated code
        bool hasMoves() { return stdQueue.empty(); }

        //--------------------------- Set Methods ---------------------------//

        //========================== Helper Methods =========================//
        void enQueue(Move m) { stdQueue.push(m); }
        void enQueue(std::array<uint8_t, NUM_MOTORS> dirs, std::array<uint32_t, NUM_MOTORS> steps);
        Move deQueue();
};

#endif