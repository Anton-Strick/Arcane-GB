#include <Arduino.h>


class Piece {
    public:
        int* position;
        String name;

        Piece(int* p, String n) {
            position = p;
            name = n;

        }

        void displayPiece() {
            Serial.printf("\n%s is located at (%d, %d)\n", 
                          name, position[0], position[1]);
        }

        /**
         * Returns whether a piece can reach the specified position in 1 move
         * @param end an int array of size 2 containing the end position [x,y]
         */
        boolean isValidMove(int* end) {
            return true;
        }

        boolean movePiece(int* end) {
            if (isValidMove(end)) {
                position = end;
                return true;
            } // End if valid move

            else return false;
        }
};

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
uint8_t getTransposition(int* position) {
    uint8_t indicator;
    
    if (position[0] >= 4)
        indicator = indicator | 0xb01;  // Transpose Left

    else indicator = indicator | 0xb00; // Transpose Right

    if (position[1] >= 4)
        indicator = indicator | 0xb10;  // Transpose Down
    
    else 
        indicator = indicator | 0xb00;  // Transpose Up

    return indicator;

}

