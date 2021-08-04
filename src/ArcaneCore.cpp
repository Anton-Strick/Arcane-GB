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

    wireless.connectWiFi();
    wireless.socketConnect();
    timerInit();
}

void loop() {
    delay(100);
    wireless.idle(); // Handles Server Connection
    if (wireless.hasJson()) {
        game.queueJsonMove(wireless.deQueue());
    }

    else if (robot.moveComplete) {
        if (game.hasMoves()) {
            robot.loadMove(game.getNextMove());
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