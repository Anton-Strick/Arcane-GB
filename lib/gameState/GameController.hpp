#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <array>
#include "Piece.hpp"
#include "Queue.hpp"

#define NUM_PIECES 32

using namespace std;
class GameController {
    private:
        uint8_t gameID;
        array<Piece, NUM_PIECES> pieces;

    public:
        //--------------------------- Get Methods ---------------------------//

        uint8_t getID() { return gameID; }
        Piece getPiece(int index) { return pieces[index]; }

        //--------------------------- Set Methods ---------------------------//

        void setID(uint8_t id) { gameID = id; }

        //========================== Helper Methods =========================//

        //------------------ Defined in GameController.cpp ------------------//
        GameController();

        void initializePieces();

        Piece pieceAt(array<int8_t, 2> pos);
};

Move transpose(array<int8_t, 2> position, bool deTranspose = false);
Move transpose(Piece p, bool deTranspose = false);

Move deTranspose(array<int8_t, 2> position) 
    { return transpose(position, true); }
Move deTranspose(Piece p) 
    { return transpose(p, true); }

Queue retire(Piece p);

#endif