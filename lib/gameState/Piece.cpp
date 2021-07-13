#include <Arduino.h>
#include "Piece.hpp"

Piece::Piece(std::array<uint8_t, 2> p, uint8_t id) {
    this->setPosition(p);
    this->setID(id);
}