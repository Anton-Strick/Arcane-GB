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