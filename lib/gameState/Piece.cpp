#include <Arduino.h>
#include "Piece.hpp"

/**
 * Returns whether a piece can reach the specified position in 1 move
 * @param end an int array of size 2 containing the end position [x,y]
*/
Piece::Piece(int* p, String n) {
    setPosition(p);
    setName(n);
}

boolean Piece::movePiece(int* end) {
    setPosition(end);
    return true;
}