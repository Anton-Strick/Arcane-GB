#include <array>
#include "Piece.hpp"

Piece::Piece(std::array<int8_t, 2> p, uint8_t id) {
    this->setPosition(p);
    this->setID(id);
}

Piece::Piece() {
    std::array<int8_t, 2> tmpPosition = { 0, 0 };
    this->setPosition(tmpPosition);
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
            return 11;
        }
        else return 10;
    }
}