#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <Arduino.h>
#include <array>
#include "Piece.hpp"
#include "WirelessController.hpp"

#define NUM_PIECES 32

using namespace std;
class GameController {
    private:
        uint8_t gameID;
        // TODO (low): Implement std::arrays throughout code
        array<Piece, NUM_PIECES> pieces;
        WirelessController wireless;

    public:
        //--------------------------- Get Methods ---------------------------//

        uint8_t getID() { return gameID; }

        //--------------------------- Set Methods ---------------------------//

        void setID(uint8_t id) { gameID = id; }

        //========================== Helper Methods =========================//

        //------------------ Defined in GameController.cpp ------------------//
        
        uint8_t getTransposition(uint8_t* position);
        array<uint8_t, 2> parseMove(String);
        boolean reportToServer(String message);
};

#endif