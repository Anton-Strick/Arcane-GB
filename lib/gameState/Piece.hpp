#ifndef Piece_HPP
#define Piece_HPP

#include<Arduino.h>
#include<array>
/**
 * Piece IDs are stored in the form of 8-bit uints. See below:
 * | Fact |       Piece      |         Number         |
 *    X            XXX                  XXXX
 * The piece number is assigned according to the starting column.
 * For example, the white rook starting in column A would be:
 *                  PieceID 0-010-0000
 * While the black rook starting in column H would be:
 *                  PieceID 1-010-1000
 */

#define PIECE_FACTION_MASK 0xb10000000
enum Faction {
    White = 0xb00000000, 
    Black = 0xb10000000
};

#define PIECE_TYPE_MASK 0xb01110000
enum Piece_Type {
    Pawn   = 0xb00000000,
    Rook   = 0xb00010000,
    Knight = 0xb00100000,
    Bishop = 0xb00110000,
    Queen  = 0xb01000000,
    King   = 0xb01010000
};

#define PIECE_NUMBER_MASK 0xb00001111


class Piece {
    private:
        std::array<uint8_t, 2> position = { { 0, 0 } };
        uint8_t pieceID;

    public:
        Piece(std::array<uint8_t, 2> p, uint8_t id);
        //--------------------------- Get Methods ---------------------------//
        std::array<uint8_t, 2> getPosition() { return position; }
        uint8_t getID() { return pieceID; }

        //-------------------------- Set Functions --------------------------//
        void setPosition(std::array<uint8_t, 2> p) { position[0] = p[0]; 
                                                     position[1] = p[1]; }
        void setID(uint8_t id) { pieceID = id; }

        //------------------- Defined in gameState.cpp ----------------------//
        Piece(int* p, String n);
};

#endif