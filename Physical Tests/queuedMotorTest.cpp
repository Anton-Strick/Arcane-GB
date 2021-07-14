#include <Arduino.h>
#include <robotControl.hpp>


Move* toTheRight;
Move* toTheLeft;
Move* nowKick;
Move* nowWalkItByYourself;
RobotControl* controller;

volatile boolean complete;
volatile uint32_t steps[NUM_MOTORS] = {0, 0};

volatile uint moveCounter = 0;
hw_timer_t * timer = NULL;

void IRAM_ATTR stepperISR();
void timerInit();
void displaySteps();

void setup() {
    //------------------------------ Connect to Computer ------------------------------//
    Serial.begin(9600);
    while (!Serial);

    Serial.println("\nStart");

    //------------------------------- Prepare Movements -------------------------------//
    uint8_t tmpDirs[NUM_MOTORS];
    uint32_t tmpSteps[NUM_MOTORS];

    tmpDirs[0] = Clockwise; tmpDirs[1] = Clockwise;
    tmpSteps[0] = STEPS_PER_MM * 25; tmpSteps[1] = STEPS_PER_MM * 25;
    toTheRight = new Move(tmpDirs, tmpSteps);

    tmpDirs[0] = AntiClockwise; tmpDirs[1] = AntiClockwise;
    tmpSteps[0] = STEPS_PER_MM * 50; tmpSteps[1] = STEPS_PER_MM * 50;
    toTheLeft = new Move(tmpDirs, tmpSteps);

    tmpDirs[1] = Clockwise;

    nowKick = new Move(tmpDirs, tmpSteps);

    tmpDirs[0] = Clockwise; tmpDirs[1] = AntiClockwise;
    nowWalkItByYourself = new Move(tmpDirs, tmpSteps);


    //----------------------------- Initialize RobotControl ---------------------------//
    controller = new RobotControl();
    controller->initializeMotors();

    controller->queueMove(toTheRight);
    Serial.print("QUEUED:   ");
    toTheRight->printMove();
    controller->queueMove(toTheLeft);
    Serial.print("QUEUED:   ");
    toTheLeft->printMove();
    controller->queueMove(nowKick);
    Serial.print("QUEUED:   ");
    nowKick->printMove();
    controller->queueMove(nowWalkItByYourself);
    Serial.print("QUEUED:   ");
    nowWalkItByYourself->printMove();

    timerInit();
}

void loop() {
    static uint32_t lastTime = 0;
    static int timesComplete = 0;
    uint32_t ms = millis();

    if ((ms - lastTime) > 1000) { // Print Reports every 1/2 second
        lastTime = ms;
        controller->printReport();
        if (controller->moveComplete) { // Loads moves upon completion
            Serial.printf("\n\n");
            Serial.println("============== Loading Move... ==============");
            Serial.printf("\n\n");
            delay(250);
            controller->loadMove(controller->dequeueMove());
            timesComplete += 1;
        }

        if (timesComplete == 10) {
            delay(50000);
        }
    }

    
}

void timerInit() {
    cli(); // Stops Interrupts
    timer = timerBegin(3, 8, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    sei(); // Re-Enables interrupts
}


void IRAM_ATTR stepperISR() {
        controller->stepMotors();
}

void displaySteps() {
    Serial.printf("There are %d steps remaining.\n", steps[0]);
}