#include <array>

#include "config.hpp"
#include"GameController.hpp"

GameController::GameController() {
    initializePieces();
}

/**
 * Returns an integer (0-4) to indicate which direcection a piece should
 * transpose to in order to avoid knocking into other pieces.
 * 0xb00 - up and right
 * 0xb01 - up and left
 * 0xb10 - down and right
 * 0xb11 - down and left
 * @param position An int array of size 2 which contains the starting
 *                 position of a piece. [x,y]
 */
uint8_t GameController::getTransposition(std::array<uint8_t, 2> position) {
    uint8_t indicator = 0;
    
    if (position[0] > 4)
        indicator = indicator | 0b01;  // Transpose Left

    else indicator = indicator | 0b00; // Transpose Right

    if (position[1] > 5)
        indicator = indicator | 0b10;  // Transpose Down
    
    else 
        indicator = indicator | 0b00;  // Transpose Up

    return indicator;
}

uint8_t GameController::getTransposition(Piece p) {
    return getTransposition(p.getPosition());
}

void GameController::initializePieces() {
    /**
     * White Piece Indexes
     * 0-7   :  Pawns
     * 8-9   :  Rooks
     * 10-11 :  Knights
     * 12-13 :  Bishops
     * 14    :  Queen
     * 15    :  King
     * ---------------------
     * Black Piece Indexes
     * White Index + 16
     */
    // Initialize Pawns
    std::array<uint8_t, 2> whiteTmpPos = { 3, 0 };
    std::array<uint8_t, 2> blackTmpPos = { 8, 0 };
    
    uint8_t whiteID;
    uint8_t blackID;
    
    uint8_t currCol = 0;

    uint8_t whiteIndex = 0;
    uint8_t blackIndex = 16;

    uint8_t piece = uint8_t(Pawn); // can be incremented with += 16

    for (currCol = 0 ; currCol < NUM_ROWS ; currCol++, whiteIndex++, blackIndex++) {
        whiteID = White | piece | currCol;
        blackID = Black | piece | currCol;

        whiteTmpPos[1] = currCol;
        blackTmpPos[1] = currCol;

        pieces[whiteIndex] = Piece(whiteTmpPos, whiteID);
        pieces[blackIndex] = Piece(blackTmpPos, blackID);
    }

    // Initialize Rooks, knights, and bishops. Piece enum increments by 16
    piece = uint8_t(Rook);
    whiteTmpPos[0] = 2; // Shift Rows back 1
    blackTmpPos[0] = 9;

    for (currCol = 0 ; currCol < 3 ; currCol++, piece += 16) {
        whiteID = White | piece | currCol;
        blackID = Black | piece | currCol;

        whiteTmpPos[1] = currCol;
        blackTmpPos[1] = currCol;

        pieces[++whiteIndex] = Piece(whiteTmpPos, whiteID);
        pieces[++blackIndex] = Piece(blackTmpPos, blackID);

        //----------------- Instantiate the Other Twin -----------------//
        whiteTmpPos[1] = NUM_ROWS - 1 - currCol;
        blackTmpPos[1] = whiteTmpPos[1];

        whiteID = White | piece | whiteTmpPos[1];
        blackID = Black | piece | blackTmpPos[1];

        pieces[++whiteIndex] = Piece(whiteTmpPos, whiteID);
        pieces[++blackIndex] = Piece(blackTmpPos, blackID);
    }

    // Initialize Queens
    piece = uint8_t(Queen);
    currCol++;

    whiteID = White | piece | currCol;
    blackID = Black | piece | currCol;

    whiteTmpPos[1] = currCol;
    blackTmpPos[1] = currCol;

    pieces[++whiteIndex] = Piece(whiteTmpPos, whiteID);
    pieces[++blackIndex] = Piece(blackTmpPos, blackID);

    // Initialize Kings
    piece = uint8_t(King);
    currCol++;

    whiteID = White | piece | currCol;
    blackID = Black | piece | currCol;

    whiteTmpPos[1] = currCol;
    blackTmpPos[1] = currCol;

    pieces[++whiteIndex] = Piece(whiteTmpPos, whiteID);
    pieces[++blackIndex] = Piece(blackTmpPos, blackID);
}