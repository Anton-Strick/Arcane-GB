#include <Arduino.h>
#include <robotControl.hpp>

Motor* motor;
hw_timer_t* timer = NULL;

void IRAM_ATTR stepperISR();
void timerInit();
void displayReport();

void setup() {
    Serial.begin(9600);         // Init serial port and set baudrate
    while(!Serial);               // Wait for serial port to connect
    Serial.println("\nStart...");
  
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);

    pinMode(DIAG_PIN0, INPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(STEP_PIN0, OUTPUT);
    pinMode(DIR_PIN0, OUTPUT);

    digitalWrite(EN_PIN, LOW);
    digitalWrite(DIR_PIN0, Clockwise);

    TMC2209Stepper tmpDriver(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    motor = new Motor(0, tmpDriver, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    motor->init();

    motor->setTarget(1600);

    timerInit();
}

void loop() {
    if (motor->getPosition() < 1600) {
        delay(100);
        Serial.printf("\nCurrently at step %d\n", motor->getPosition());
    } // End Motor Not Finished
    else {
        delay(5000);
        Serial.printf("\n========= 180 Degree Arc Complete =========\n");
        switch (motor->getDir()) {
            case AntiClockwise :
                motor->setDir(Clockwise);
                motor->setTarget(1600);
                break;
            case Clockwise :
                motor->setDir(AntiClockwise);
                motor->setTarget(0);
                break;
        }
    } // End Motor Finished
}

void IRAM_ATTR stepperISR() {
    motor->step();
}

void timerInit() {
    cli(); // Stops Interrupts
    timer = timerBegin(3, 16, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    sei(); // Re-Enables interrupts
}

void displayReport() {
    Serial.printf("\nReporting...\n");
}