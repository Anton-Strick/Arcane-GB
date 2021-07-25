#include <Arduino.h>
#include "robotControl.hpp"
#include "GameController.hpp"
#include "WirelessController.hpp"

RobotControl robot;
GameController game;
WirelessController wireless;

volatile bool complete;

hw_timer_t * timer = NULL;

void IRAM_ATTR stepperISR();
void timerInit();

void setup() {
    //-------------------------------- Configure Robot --------------------------------//
    configPins();
    robot.disableMagnet(); // Active LOW
    delay(5000);
    
    //------------------------------- Prepare Movements -------------------------------//
    robot.queueMove(xyToMotors(5, -8));
    robot.queueMove(xyToMotors(0, 2, true));

    robot.queueMove(xyToMotors(4, -1));
    robot.queueMove(xyToMotors(0, -1, true));

    robot.queueMove(xyToMotors(0, -4));
    robot.queueMove(xyToMotors(0, 2, true));

    robot.queueMove(xyToMotors(3, 4));
    robot.transpose(uint8_t(3));
    robot.queueMove(xyToMotors(0, -1, true));
    robot.transpose(uint8_t(3));

    robot.queueMove(xyToMotors(-4, -5));
    robot.transpose(uint8_t(0));
    robot.queueMove(xyToMotors(0, 1));
    
}

void loop() {

}

void timerInit() {
    cli()
    timer = timerBegin(3, 4, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
}

void IRAM_ATTR stepperISR() {
    robot.stepMotors();
}