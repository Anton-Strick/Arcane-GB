#include <Arduino.h>

#include "ArcaneCore.hpp"

void setup() {
    //-------------------------------- Configure Robot --------------------------------//
    Serial.begin(115200);
    Serial.println("Start");

    configPins();
    robot.initializeMotors();
    robot.disableMagnet(); // Active LOW

    Serial.flush();
    delay(1000);
    while (in != 'B') {
        in = Serial.read();
    }

    Serial.println("Start");
    wireless.connectWiFi();
    wireless.socketConnect();
 
    startPos = { 4, 3 };
    endPos   = { 4, 5 };
    game.movePieceAtPos(startPos, endPos);
    
    startPos = { 3, 8 };
    endPos   = { 3, 7 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 3, 3 };
    endPos   = { 3, 5 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 6, 9 };
    endPos   = { 5, 7 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 1, 2 };
    endPos   = { 2, 4 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 6, 8 };
    endPos   = { 6, 7 };
    game.movePieceAtPos(startPos, endPos);
    
    startPos = { 2, 2 };
    endPos   = { 4, 4 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 5, 9 };
    endPos   = { 6, 8 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 3, 2 };
    endPos   = { 3, 3 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 2, 8 };
    endPos   = { 2, 7 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 5, 3 };
    endPos   = { 5, 4 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 1, 8 };
    endPos   = { 1, 6 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 6, 2 };
    endPos   = { 4, 3 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 1, 9 };
    endPos   = { 3, 8 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 4, 4 };
    endPos   = { 7, 7 };
    game.movePieceAtPos(startPos, endPos);

    startPos = { 6, 8 };
    endPos   = { 7, 7 };
    game.retirePieceAt(startPos);
    game.movePieceAtPos(startPos, endPos);    
    
    robot.queueMoves(game.getGameQueue());
    timerInit();
}

void loop() {
    delay(100);
    if (robot.moveComplete) {
        if (robot.hasMoves()) {
            robot.printReport();
            robot.loadMove();
        }
    }
}

void timerInit() {
    cli()
    timer = timerBegin(3, 4, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 6666, true);
    timerAlarmEnable(timer);
    sei();
}

void IRAM_ATTR stepperISR() {
    robot.stepMotors();
}