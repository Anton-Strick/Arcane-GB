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
        
        //------------------------------ Get Methods -----------------------------//

        uint8_t getID() { return gameID; }
        Piece * getPiece(int index) { return pieces[index]; }
        Move getNextMove() { return gameQueue.deQueue(); }

        //------------------------------ Set Methods -----------------------------//

        void setID(uint8_t id) { gameID = id; }

        //============================= Helper Methods ===========================//

        bool hasMoves() { return gameQueue.hasMoves(); }

        //--------------------- Defined in GameController.cpp --------------------//
        
        /**
         * Constructs a new GameController with a blank gameboard
         */
        GameController();

        /**
         * Initializes the initial chess board by populating the Pieces array
         * with pointers to valid Piece objects using the proper ID organization
         */
        void initializePieces();
        /**
         * Returns the index of a piece at the specified position. If there is no piece
         * there, the method returns -1
         */
        int8_t pieceAt(std::array<int8_t, 2> pos);
        void insertPiece(int8_t i, Piece p);

        /**
         * Queues the given JsonMove into the game controller, if needed, 
         * a retirement function is called to remove the captured Piece
         * @param jMove A valid JsonMove with a piece's start and end position
         */
        void queueJsonMove(JsonMove jMove);
        
        /**
         * Moves a piece at a given start position to the end position.
         * @param start a valid coordinate location (x, y)
         * @param end   a valid coordinate location (x, y)
         */
        void movePieceAtPos(std::array<int8_t, 2> start, std::array<int8_t, 2> end );
        /**
         * Retires a Piece given its capture position
         * @param pos a valid coordinate location within the play-space
         */
        void retirePieceAt(std::array<int8_t, 2> pos);
        /**
         * Moves a non-knight Piece to the given end position
         * @param p A valid Piece object
         * @param pos A valid position within a 8x12 grid
         */
        void movePieceToPosition(Piece p, std::array<int8_t, 2> pos);
        /**
         * Moves a knight Piece to the given end position, this move avoids other
         * pieces.
         * @param p A valid knight Piece object
         * @param pos A valid position within a 8x12 grid
         */
        void moveKnightToPosition(Piece p, std::array<int8_t, 2> pos);
        /**
         * Retires any Piece with a valid ID to a graveyard slot, regardless of
         * the Piece's current position
         */
        void retire(Piece p);
        
        /**
         * Queues a move to return the robot head to the home position from its
         * current location on the board.
         */
        void moveHome();
};

/**
 * Converts cartesian movement into coreXY movement
 * @param  dX The number of steps in the X direction
 * @param  dY The number of steps in the Y direction
 * @return Move containing the direction and number of steps required
 *         to achieve the desired motion
 */
Move xyToMotors(double dx, double dy, bool mE = false);

#endif