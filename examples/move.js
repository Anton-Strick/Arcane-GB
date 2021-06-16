/**
 * This file serves as an example of the move JavaScript object to be recieved
 * by the arcane game board from the web server
 */

class Move{
    /**
     * @param {number} turn    - should increment only after BOTH players have gone
     * @param {string} piece   - A unique identifier for the piece being moved
     * @param {string} origin  - Starting position (A1 - H8)
     * @param {string} end     - Ending position (A1-H8)
     * @param {string} special - For codes indicating capture, check, etc
     */
    constructor(turn, piece, origin, end, special) {
        this.turn = turn;
        this.piece = piece;
        this.origin = origin;
        this.end = end;
        this.special = special;
    }
}

/**
 * =========================== Formatting Guidelines ==========================
 * Factions
 * 
 * W - White
 * B - Black
 * ----------------------------------------------------------------------------
 * Pieces
 * 
 * K - King
 * Q - Queen
 * R - Rook
 * B - Bishop
 * N - Knight
 * P - Pawn
 * ----------------------------------------------------------------------------
 * Numbers
 * 
 * 1-8 corresponds with starting positions in columns A-B
 * EG: WR1 is the rook that begins on A1, BR2 is the rook that begins on H8
 * ----------------------------------------------------------------------------
 * Special
 * 
 * x   - Capture
 * 00  - Kingside Castle
 * 000 - Queenside Castle
 * +   - Check
 * #   - Checkmate
 * ----------------------------------------------------------------------------
 */