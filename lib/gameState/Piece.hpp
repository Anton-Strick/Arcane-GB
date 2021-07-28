#ifndef Piece_HPP
#define Piece_HPP

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

#define PIECE_FACTION_MASK 0b10000000
enum Faction {
    White = 0b00000000, 
    Black = 0b10000000
};

#define PIECE_TYPE_MASK 0b01110000
enum Piece_Type {
    Pawn   = 0b00000000,
    Rook   = 0b00010000,
    Knight = 0b00100000,
    Bishop = 0b00110000,
    Queen  = 0b01000000,
    King   = 0b01010000
};

#define PIECE_COL_MASK 0b00001111

class Piece {
    private:
        std::array<int8_t, 2> position;
        uint8_t pieceID;

    public:
        
        //--------------------------- Get Methods ---------------------------//
        std::array<int8_t, 2> getPosition() { return position; }
        uint8_t getID() { return pieceID; }

        //-------------------------- Set Functions --------------------------//
        void setPosition(std::array<int8_t, 2> p) { position = p; }
        void setID(uint8_t id) { pieceID = id; }

        //========================== Helper Methods =========================//
        int8_t getRetireCol() { return int8_t(pieceID & PIECE_COL_MASK); }
        int8_t getRetireRow();
        uint8_t getPieceType() { return (pieceID & PIECE_TYPE_MASK); }
        uint8_t getPieceColor() { return (pieceID & PIECE_FACTION_MASK); }

        //------------------- Defined in gameState.cpp ----------------------//
        Piece(std::array<int8_t, 2> p, uint8_t id);
        Piece();
};

#endif