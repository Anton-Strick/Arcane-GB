#include <Arduino.h>
#include "Move.hpp"

/**
 * Constructs a new Move instance with -1 steps. Additionally, the 'next' 
 * pointer points to itself - lending itself to be used as a head/tail
*/
Move::Move() {
    for (int i = 0; i < NUM_MOTORS; i++) {
        dirs[i] = Clockwise;
        numSteps[i] = -1; //uint = 4294967295
    }

    delta = {0, 0};
}

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor. (Assumes magnet is disabled)
 * @param dirs {uint8_t[NUM_MOTORS]} Contains the direction flag of each motor 
 *                                   contained at the corresponding index
 * @param steps {uint32_t[NUM_MOTORS]} Contains the number of steps required 
 *                                     from each motor, respectively.
 */
Move::Move(std::array<uint8_t, NUM_MOTORS> dir, std::array<uint32_t, NUM_MOTORS> steps) {
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        dirs[i] = dir[i];
        numSteps[i] = steps[i];
    }
    delta = {0, 0};
}

/**
 * A single node of a linked list containing the direction and magnitude 
 * of the travel required by each motor as well as if the magnet is enabled
 * @param dirs {uint8_t[NUM_MOTORS]} Contains the direction flag of each motor 
 *                                   contained at the corresponding index
 * @param steps {uint32_t[NUM_MOTORS]} Contains the number of steps required 
 *                                     from each motor, respectively.
 */
Move::Move(std::array<uint8_t, NUM_MOTORS> dir, std::array<uint32_t, NUM_MOTORS> steps, bool magEnable) {
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        dirs[i] = dir[i];
        numSteps[i] = steps[i];
    }
    magnetEnabled = magEnable;

    delta = {0, 0};
}

Move::Move(std::array<uint8_t, NUM_MOTORS> dir, std::array<uint32_t, NUM_MOTORS> steps, bool magEnable, std::array<int8_t, 2> d) {
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        dirs[i] = dir[i];
        numSteps[i] = steps[i];
    }
    magnetEnabled = magEnable;

    delta = d;
}

/**
 * Deallocates the memory assigned to the Move instance
 */ 
void Move::destroy() {
    delete this;
}

/**
 * Prints out the direction and steps to be taken in a particular move.
 * (Includes a newline character)
 */
void Move::printMove() {
    Serial.printf("M0 - %d, %d steps | M1 - %d, %d steps\n", 
                   dirs[0], numSteps[0],
                   dirs[1], numSteps[1]);
}

bool Move::operator== (const Move& param) {
    bool out = true;
    out = out && (dirs == param.dirs);
    out = out && (numSteps == param.numSteps);
    out = out && (magnetEnabled == param.magnetEnabled);

    return out;
}

bool Move::operator!= (const Move& param) {
    return !(*this == param);
}

Move& Move::operator= (const Move& param) {
    dirs = param.dirs;
    numSteps = param.numSteps;
    magnetEnabled = param.magnetEnabled;

    return *this;
}

void Move::halfSteps() {
    for (int i ; i < NUM_MOTORS ; i++)
        numSteps[i] = uint32_t((numSteps[i] / 2) * 1.4142);
}