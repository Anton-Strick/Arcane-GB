#include <Arduino.h>
#include <array>
#include"GameController.hpp"
/**
 * Returns an integer (0-4) to indicate which direcection a piece should
 * transpose to in order to avoid knocking into other pieces.
 * 0xb00 - up and right
 * 0xb01 - up and left
 * 0xb10 - down and right
 * 0xb11 - down and left
 * @param position An int array of size 2 which contains the starting
 *                 position of a piece. [x,y]
 */
uint8_t GameController::getTransposition(std::array<uint8_t, 2> position) {
    uint8_t indicator = 0;
    
    if (position[0] >= 4)
        indicator = indicator | 0xb01;  // Transpose Left

    else indicator = indicator | 0xb00; // Transpose Right

    if (position[1] >= 4)
        indicator = indicator | 0xb10;  // Transpose Down
    
    else 
        indicator = indicator | 0xb00;  // Transpose Up

    return indicator;
}

