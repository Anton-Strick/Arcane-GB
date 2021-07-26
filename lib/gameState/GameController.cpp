#include <array>

#include "config.hpp"
#include"GameController.hpp"

GameController::GameController() {
    initializePieces();
}

/**
 * Returns an integer (0-4) to indicate which direcection a piece should
 * transpose to in order to avoid knocking into other pieces.
 * 0b00 - up and right
 * 0b01 - up and left
 * 0b10 - down and right
 * 0b11 - down and left
 * @param position An int array of size 2 which contains the starting
 *                 position of a piece. [x,y]
 */
Move transpose(std::array<int8_t, 2> position, bool deTranspose) {
    int8_t dX, dY;
    
    if (position[0] > 4)
        dX = int8_t(-1);  // Transpose Left

    else dX = int8_t(1); // Transpose Right

    if (position[1] > 5)
        dY = int8_t(-1);  // Transpose Down
    
    else dY = int8_t(1);  // Transpose Up

    int32_t dA = ((dX - dY) * STEPS_PER_MM * MM_PER_SQUARE) / 2;
    int32_t dB = ((dX + dY) * STEPS_PER_MM * MM_PER_SQUARE) / 2;

    std::array<uint8_t, NUM_MOTORS> dirs;
    dirs[0] = (dA < 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB < 0) ? AntiClockwise : Clockwise;

    std::array<uint32_t, NUM_MOTORS> steps;
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    Move out(dirs, steps, true);
}

Move transpose(Piece p, bool deTranspose) {
    return transpose(p.getPosition());
}

Queue retire(Piece p) {
    Queue retirePath; // Output
    //---------------------- Transposing Piece------------------//
    retirePath.enQueue(transpose(p));

    //------------------ Move to Correct Column ----------------//
    
    //-------------------- Move to Correct Row -----------------//

    //---------------------- Detranspose Piece -----------------//

    return retirePath;
}

Piece GameController::pieceAt(std::array<int8_t, 2> pos) {
    
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
    std::array<int8_t, 2> whiteTmpPos = { 3, 0 };
    std::array<int8_t, 2> blackTmpPos = { 8, 0 };
    
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