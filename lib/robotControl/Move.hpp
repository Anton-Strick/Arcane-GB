#ifndef MOVE_HPP
#define MOVE_HPP

#include <Arduino.h>

#include <array>

#include "config.hpp"

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor
 */
class Move {
    private :
        std::array<uint8_t, NUM_MOTORS> dirs;
        std::array<uint32_t, NUM_MOTORS> numSteps;
        std::array<int8_t, 2> delta;
        bool magnetEnabled = false;

    public :
        Move(); // Default Constructor
        Move(std::array<uint8_t, NUM_MOTORS> d, std::array<uint32_t, NUM_MOTORS> s);
        Move(std::array<uint8_t, NUM_MOTORS> dir, std::array<uint32_t, NUM_MOTORS> steps, bool magEnable);
        Move(std::array<uint8_t, NUM_MOTORS> dir, std::array<uint32_t, NUM_MOTORS> steps, bool magEnable, std::array<int8_t, 2> d);

        //--------------------------- Get Methods ---------------------------//

        std::array<uint8_t, NUM_MOTORS> getDirs() { return dirs; }
        std::array<uint32_t, NUM_MOTORS> getSteps() {return numSteps; }
        bool getMagnetEnabled() { return magnetEnabled; }
        std::array<int8_t, 2> getDelta() { return delta; }

        //--------------------------- Set Methods ---------------------------//

        void setDirs(std::array<uint8_t, NUM_MOTORS> d) { dirs = d; }
        void setNumSteps(std::array<uint32_t, NUM_MOTORS> nS) { numSteps = nS; }
        void setMagnetEnabled(bool mE) { magnetEnabled = mE; }

        //========================== Helper Methods =========================//
        
        void destroy();

        void printMove();

        bool operator== (const Move& param);
        bool operator!= (const Move& param);
        Move& operator= (const Move& param);

        void halfSteps();
};

#endif