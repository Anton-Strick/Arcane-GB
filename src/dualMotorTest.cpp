/** Notes for Testing
 *  - Our motors use 200 steps per revolution
 *  - Converting Motors to classes would help a bit
 */

#include <Arduino.h>
#include "robotControl.hpp"
#include <config.h>

#define STEP_BIT_POS        0         // Faster Register Access = Faster Step Speed

Motor* motors[2];

hw_timer_t * timer0 = NULL;

using namespace TMC2208_n;

void timerInit();

void IRAM_ATTR motorISR() {
    for (Motor* m : motors)
        m->step();
}

void configMotorPins() {
    pinMode(DIAG_PIN0, INPUT);
    pinMode(DIR_PIN0, OUTPUT);
    pinMode(STEP_PIN0, OUTPUT);
    pinMode(EN_PIN0, OUTPUT);

    pinMode(DIAG_PIN1, INPUT);
    pinMode(DIR_PIN1, OUTPUT);
    pinMode(STEP_PIN1, OUTPUT);
    pinMode(EN_PIN1, OUTPUT);
}

void setup() {
    //------------------------------ Connect to Computer ------------------------------//
    Serial.begin(9600);
    while (!Serial);
    //----------------------------- Connect to Motors 1+2 -----------------------------//
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);

    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    TMC2209Stepper driver1(&SERIAL_PORT1, R_SENSE, DRIVER_ADDRESS);

    motors[0] = new Motor((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);
    motors[1] = new Motor((uint8_t) 1, driver1, DIAG_PIN1, DIR_PIN1, STEP_PIN1);

    for (Motor* m : motors) {
        m->init();
    }

    configMotorPins(); // pinMode() calls

    digitalWrite(EN_PIN0, LOW);
    digitalWrite(EN_PIN1, LOW);

    digitalWrite(DIR_PIN0, Clockwise);
    motors[0]->setTarget(1600);
    digitalWrite(DIR_PIN1, AntiClockwise);
    motors[1]->setTarget(800);

    Serial.println("======== Begin Dual Motor Test ========");
    Serial.println("| Clear:  motors spin in opposing     |");
    Serial.println("|         directions. Clockwise       |");
    Serial.println("|         motor should travel 360d    |");
    Serial.println("|         and anticlockwise should    |");
    Serial.println("|         travel 180 degrees.         |");
    Serial.println("=======================================");

    timerInit();
}
void loop() {
    static uint32_t lastTime = 0;
    uint32_t ms = millis();
    if ((ms - lastTime) > 1000) { // Print Reports every second
        lastTime = ms;
        for (Motor* m : motors)
            m->displayReport();
    } // End Report

    if (motors[0]->getStepsToGo() == 0 && motors[1]->getStepsToGo() == 0) {
        Serial.printf("\n============= Arcs Complete =============\n");
        delay(5000); // Wait 5 Seconds
        for (Motor* m : motors) {
            switch (m->getDir()) {
                case Clockwise :
                    m->setDir(AntiClockwise);
                    m->setTarget(800); // 180 degrees
                    break;
                
                case AntiClockwise : 
                    m->setDir(Clockwise);
                    m->setTarget(1600); // 360 degrees
                    break;
            }
        }
    } // End Motors Finished
} // End Loop

void timerInit() {
    cli(); // Stops Interrupts
    //----------------------- Configure Motor 0 Timer -----------------------//
    timer0 = timerBegin(3, 16, true);
    timerAttachInterrupt(timer0, &motorISR, true);
    timerAlarmWrite(timer0, 10000, true);
    timerAlarmEnable(timer0);
    sei(); // Re-Enables interrupts
}

void displayReport(Motor m, int motorID) {

}