#ifndef Piece_HPP
#define Piece_HPP

#include<Arduino.h>

class Piece {
    private:
        uint8_t position[2] = {0, 0};
        String name;

    public:
        //------------------------ Reporting Functions ----------------------//    
        void displayPiece() {
            Serial.printf("\n%s is located at (%d, %d)\n",
                          name, position[0], position[1]);
        }

        //-------------------------- Set Functions --------------------------//
        void setPosition(int* p) { position[0] = p[0]; position[1] = p[1]; }
        void setName(String n) { name = n; }

        //------------------- Defined in gameState.cpp ----------------------//
        Piece(int* p, String n);
        boolean movePiece(int* end);
};

#endif