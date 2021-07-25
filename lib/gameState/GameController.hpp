#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <array>
#include "Piece.hpp"

#define NUM_PIECES 32

using namespace std;
class GameController {
    private:
        uint8_t gameID;
        // TODO (low): Implement std::arrays throughout code
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
        uint8_t getTransposition(array<uint8_t, 2> position);
        uint8_t getTransposition(Piece p);
        void initializePieces();
};

#endif