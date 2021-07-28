#include <array>

#include "config.hpp"
#include"GameController.hpp"

GameController::GameController() {
    initializePieces();
    robotPosition = { 0, (NUM_ROWS - 1) };
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
    double dX, dY;
    
    if (position[0] > 4)
        dX = int8_t(-0.5);  // Transpose Left

    else dX = int8_t(0.5); // Transpose Right

    if (position[1] > 5)
        dY = int8_t(-0.5);  // Transpose Down
    
    else dY = int8_t(0.5);  // Transpose Up

    return xyToMotors(dX, dY);
}

Move transpose(Piece p, bool deTranspose) {
    return transpose(p.getPosition());
}

void GameController::retire(Piece p) {
    Queue retirePath; // Output
    std::array<int8_t, 2> pos = p.getPosition();
    double dX, dY, transposeX, transposeY;
    dX = p.getRetireCol() - pos[0];
    dY = p.getRetireRow() - pos[1];

    if (dX == 0) {
        transposeX = (pos[0] > 3) ? 0.5 : -0.5;
        transposeY = (0 > dY) ? -0.5 : 0.5;

        dY += ( 0 > dY ) ? 1 : -1;

        retirePath.enQueue(xyToMotors(transposeX, transposeY));
        retirePath.enQueue(xyToMotors(dX, 0));
        retirePath.enQueue(xyToMotors(0, dY));
        retirePath.enQueue(xyToMotors((-1 * transposeX), transposeY));
    }

    else {
        transposeX = (0 > dX) ? -0.5 : 0.5;
        transposeY = (0 > dY) ? -0.5 : 0.5;

        dX += ( 0 > dX ) ? 1 : -1;
        dY += ( 0 > dY ) ? 1 : -1;

        retirePath.enQueue(xyToMotors(transposeX, transposeY));
        retirePath.enQueue(xyToMotors(dX, 0));
        retirePath.enQueue(xyToMotors(0, dY));
        retirePath.enQueue(xyToMotors(transposeX, transposeY));
    }


    std::array<int8_t, 2> end = { p.getRetireCol(), p.getRetireRow() };
    pieces[pieceAt(pos)]->setPosition(end);  // Set Pieces future position
    robotPosition = pos; // Update robot's future position

    gameQueue.enQueue(retirePath);
}

void GameController::movePieceToPosition(Piece p, std::array<int8_t, 2> pos) {
    if (p.getPieceType() == Knight) {
        moveKnightToPosition(p, pos);
        return;
    }

    Queue path;
    double dX, dY;
    std::array<int8_t, 2> start = p.getPosition();

    //---------------- Move to Piece ---------------//
    dX = double(start[0] - robotPosition[0]);
    dY = double(start[1] - robotPosition[1]);

    path.enQueue(xyToMotors(dX, dY));

    //---------------- Move the Piece --------------//
    dX = pos[0] - start[0];
    dY = pos[1] - start[1];

    path.enQueue(xyToMotors(dX, dY, true));
    pieces[pieceAt(start)]->setPosition(pos);
    robotPosition = pos;

    gameQueue.enQueue(path);
}

void GameController::moveKnightToPosition(Piece p, std::array<int8_t, 2> pos) {
    Queue path;
    double dX, dY;
    double transposeX, transposeY;
    std::array<int8_t, 2> start = p.getPosition();

    //---------------- Move to Piece ---------------//
    dX = double(start[0] - robotPosition[0]);
    dY = double(start[1] - robotPosition[1]);

    path.enQueue(xyToMotors(dX, dY));

    //---------- Transpose Based on delta ----------//
    dX = double(pos[0] - start[0]);
    dY = double(pos[1] - start[1]);

    transposeX = (dX > 0) ? 0.5 : -0.5;
    transposeY = (dY > 0) ? 0.5 : -0.5;

    path.enQueue(xyToMotors(transposeX, transposeY, true));

    dX -= transposeX * 2 ;
    dY -= transposeY * 2;

    path.enQueue(xyToMotors(dX, dY, true));
    path.enQueue(xyToMotors(transposeX, transposeY, true));

    pieces[pieceAt(start)]->setPosition(pos);
    robotPosition = pos;

    gameQueue.enQueue(path);
}

/**
 * Moves a piece at a given start position to the end position.
 * @param start a valid coordinate location (x, y)
 * @param end   a valid coordinate location (x, y)
 */
void GameController::movePieceAtPos(std::array<int8_t, 2> start, std::array<int8_t, 2> end) {
    int8_t pieceIndex = pieceAt(start);
    if (pieceIndex >= 0) {
        movePieceToPosition(*getPiece(pieceIndex), end);
    }
}

void GameController::retirePieceAt(std::array<int8_t, 2> pos) {
    int8_t pieceIndex = pieceAt(pos);
    if (pieceIndex >= 0) {
        retire(*getPiece(pieceIndex));
    }
}

/**
 * Returns the index of a piece at the specified position. If there is no piece
 * there, the method returns -1
 */
int8_t GameController::pieceAt(std::array<int8_t, 2> pos) {
    int8_t i;
    for (i = 0 ; i < NUM_PIECES ; i++) {
        if (pieces[i]->getPosition() == pos) {
            return i;
        }
    }
    return int8_t(-1);
}

/**
 * Queues the given JsonMove into the game controller, if needed
 * a retirement function is called.
 * @param jMove A valid JsonMove with a piece's start and end position
 */
void GameController::queueJsonMove(JsonMove jMove) {
    int8_t index = pieceAt(jMove.endPos);
    if (index >= 0 ) {
        Serial.println("Retiring");
        retirePieceAt(jMove.endPos);
    }
    movePieceAtPos(jMove.startPos, jMove.endPos);

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
    std::array<int8_t, 2> whiteTmpPos = { 0, 3 };
    std::array<int8_t, 2> blackTmpPos = { 0, 8 };
    
    uint8_t whiteID;
    uint8_t blackID;
    
    uint8_t currCol = 0;

    uint8_t whiteIndex = 0;
    uint8_t blackIndex = 16;

    uint8_t piece = uint8_t(Pawn); // can be incremented with += 16
    
    for (currCol = 0 ; currCol < NUM_COLS ; currCol++) {
        whiteID = White | piece | currCol;
        blackID = Black | piece | currCol;

        whiteTmpPos[0] = currCol;
        blackTmpPos[0] = currCol;

        pieces[whiteIndex++] = new Piece(whiteTmpPos, whiteID);
        pieces[blackIndex++] = new Piece(blackTmpPos, blackID);
    }

    // Initialize Rooks, knights, and bishops. Piece enum increments by 16
    piece = uint8_t(Rook);
    whiteTmpPos[1] = 2; // Shift Rows back 1
    blackTmpPos[1] = 9;
    currCol = 0;

    for (currCol = 0 ; currCol < 3 ; currCol++) {
        whiteID = White | piece | currCol;
        blackID = Black | piece | currCol;

        whiteTmpPos[0] = currCol;
        blackTmpPos[0] = currCol;

        pieces[whiteIndex++] = new Piece(whiteTmpPos, whiteID);
        pieces[blackIndex++] = new Piece(blackTmpPos, blackID);

        //----------------- Instantiate the Other Twin -----------------//
        whiteTmpPos[0] = NUM_COLS - 1 - currCol;
        blackTmpPos[0] = whiteTmpPos[0];

        whiteID = White | piece | whiteTmpPos[0];
        blackID = Black | piece | blackTmpPos[0];

        pieces[whiteIndex++] = new Piece(whiteTmpPos, whiteID);
        pieces[blackIndex++] = new Piece(blackTmpPos, blackID);

        piece += 16;
    }

    // Initialize Queens
    piece = uint8_t(Queen);
    currCol++;

    whiteID = White | piece | currCol;
    blackID = Black | piece | currCol;

    whiteTmpPos[0] = currCol;
    blackTmpPos[0] = currCol;

    pieces[whiteIndex++] = new Piece(whiteTmpPos, whiteID);
    pieces[blackIndex++] = new Piece(blackTmpPos, blackID);

    // Initialize Kings
    piece = uint8_t(King);
    currCol++;

    whiteID = White | piece | currCol;
    blackID = Black | piece | currCol;

    whiteTmpPos[0] = currCol;
    blackTmpPos[0] = currCol;

    pieces[whiteIndex] = new Piece(whiteTmpPos, whiteID);
    pieces[blackIndex] = new Piece(blackTmpPos, blackID);
}

/**
 * Converts cartesian movement into coreXY movement
 * @param  dX The number of steps in the X direction
 * @param  dY The number of steps in the Y direction
 * @return Move containing the direction and number of steps required
 *         to achieve the desired motion
 */
Move xyToMotors(double dX, double dY, bool mE /*= false*/) {
    int32_t dA = (dX - dY) * STEPS_PER_MM * MM_PER_SQUARE;
    int32_t dB = (dX + dY) * STEPS_PER_MM * MM_PER_SQUARE;

    std::array<uint8_t, NUM_MOTORS> dirs;
    dirs[0] = (dA < 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB < 0) ? AntiClockwise : Clockwise;

    std::array<uint32_t, NUM_MOTORS> steps;
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    std::array<int8_t, 2> d = {int8_t(dX), int8_t(dY)};

    Move newMove(dirs, steps, mE, d);
    return newMove;
}