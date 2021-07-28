#include <array>
#include "config.hpp"
#include "Piece.hpp"

Piece::Piece(std::array<int8_t, 2> p, uint8_t id) {
    this->setPosition(p);
    this->setID(id);
}

Piece::Piece() {
    position = { 0, 0 };
    this->setID(0);
}

int8_t Piece::getRetireRow() {
    if (this->getPieceColor() == White) {
        if (this->getPieceType() != Pawn) {
            return 0;
        }
        else return 1;
    }

    else {
        if (this->getPieceType() != Pawn) {
            return NUM_ROWS - 1;
        }
        else return NUM_ROWS - 2;
    }
}