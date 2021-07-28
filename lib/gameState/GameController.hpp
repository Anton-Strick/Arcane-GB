#pragma once

#ifndef GAMECONTROLLER_HPP
#define GAMECONTROLLER_HPP

#include <array>

#include "Piece.hpp"
#include "Queue.hpp"
#include "WirelessController.hpp"

#define NUM_PIECES 32

class GameController {
    private:
        uint8_t gameID;
        std::array<int8_t, 2> robotPosition;
        Queue gameQueue;
        std::array<Piece *, NUM_PIECES> pieces;

    public:
        
        //--------------------------- Get Methods ---------------------------//

        uint8_t getID() { return gameID; }
        Piece * getPiece(int index) { return pieces[index]; }
        Move getNextMove() { return gameQueue.deQueue(); }

        //--------------------------- Set Methods ---------------------------//

        void setID(uint8_t id) { gameID = id; }

        //========================== Helper Methods =========================//
        bool hasMoves() { return gameQueue.hasMoves(); }
        //------------------ Defined in GameController.cpp ------------------//
        GameController();

        void initializePieces();
        int8_t pieceAt(std::array<int8_t, 2> pos);
        void insertPiece(int8_t i, Piece p);

        void movePieceAtPos(std::array<int8_t, 2> start, std::array<int8_t, 2> end );

        void movePieceToPosition(Piece p, std::array<int8_t, 2> pos);
        void moveKnightToPosition(Piece p, std::array<int8_t, 2> pos);
        void retire(Piece p);
        void retirePieceAt(std::array<int8_t, 2> pos);

        void queueJsonMove(JsonMove jMove);
};

Move xyToMotors(double dx, double dy, bool mE = false);

Move transpose(std::array<int8_t, 2> position, bool deTranspose = false);
Move transpose(Piece p, bool deTranspose = false);

#endif