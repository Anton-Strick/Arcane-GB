#include <array>
#include "config.hpp"
#include "Piece.hpp"

/**
 * A Dataclass which contains the starting position, type, and current position
 * of a given chess piece. Pieces should only be generated in the initializePieces
 * function within GameController.cpp
 * @param position A C++ std array containing the current position as integers
 * @param id an 8-bit ID signifying the faction, piece type, and starting col
 */
Piece::Piece(std::array<int8_t, 2> p, uint8_t id) {
    this->setPosition(p);
    this->setID(id);
}

Piece::Piece() {
    position = { 0, 0 };
    setID(0);
}

int8_t Piece::getRetireRow() {
    if (getPieceColor() == White) {
        if (getPieceType() != Pawn) {
            return 0;
        }
        else return 1;
    }

    else {
        if (getPieceType() != Pawn) {
            return NUM_ROWS - 1;
        }
        else return NUM_ROWS - 2;
    }
}