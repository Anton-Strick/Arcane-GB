#include <Arduino.h>
#include "robotControl.hpp"
#include "GameController.hpp"
#include "WirelessController.hpp"

RobotControl robot;
//GameController game;
//WirelessController wireless;

volatile bool complete;

hw_timer_t * timer = NULL;
char in;

void IRAM_ATTR stepperISR();
void timerInit();
void loadMoves();

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

    loadMoves();

    timerInit();
}

void loop() {
    static uint32_t lastTime = 0;
    uint32_t ms = millis();

    if ((ms - lastTime) > 1000) {
        lastTime = ms;
        //robot.printReport();
        if (robot.moveComplete) {
            if (robot.hasMoves()) {
                robot.printReport();
                robot.loadMove();
            }
        }
    }

    in = Serial.read();
    if (in == 'B')
        loadMoves();
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

void loadMoves() {
    //------------------------------- Prepare Movements -------------------------------//
    robot.queueMove(xyToMotors(4, -8));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, 2, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    
    robot.queueMove(xyToMotors(-1, 3));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, -1, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    robot.queueMove(xyToMotors(0, -4));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, 2, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    robot.queueMove(xyToMotors(3, 4));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(3));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, -1, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(3));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    robot.queueMove(xyToMotors(-4, -5));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(0));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, 1, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(0));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    // Retire Pawn
    robot.queueMove(xyToMotors(2, 1));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(2));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(0, -3, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.transpose(uint8_t(3));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    robot.queueMove(xyToMotors(1, 6));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();
    robot.queueMove(xyToMotors(-1, -2, true));
    Serial.print("QUEUED:   ");
    robot.getLastMove().printMove();

    robot.queueMove(xyToMotors(-4, 6));
}