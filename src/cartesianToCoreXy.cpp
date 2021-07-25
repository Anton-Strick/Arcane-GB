#include <Arduino.h>
#include <robotControl.hpp>

RobotControl controller;

volatile boolean complete;
volatile uint32_t steps[NUM_MOTORS] = {0, 0};

volatile uint moveCounter = 0;
hw_timer_t * timer = NULL;

void IRAM_ATTR stepperISR();
void timerInit();
void displaySteps();

void setup() {
    //------------------------------ Connect to Computer ------------------------------//
    Serial.begin(115200);
    Serial.println("Start");
    delay(5000);
    controller.disableMagnet();

    //------------------------------- Prepare Movements -------------------------------//
    std::array<uint8_t, NUM_MOTORS> tmpDirs;
    std::array<uint32_t, NUM_MOTORS> tmpSteps;

    tmpDirs[0] = Clockwise; tmpDirs[1] = Clockwise;
    tmpSteps[0] = STEPS_PER_MM * MM_PER_SQUARE * 2; 
    tmpSteps[1] = STEPS_PER_MM * MM_PER_SQUARE * 2;

    Move right = controller.xyToMotors(3, 0);
    Move rightMagnetOn(tmpDirs, tmpSteps, true);

    tmpDirs[0] = AntiClockwise;
    Move up = controller.xyToMotors(0, 3);
    Move upMagnetOn(tmpDirs, tmpSteps, true);

    tmpDirs[1] = AntiClockwise;
    Move left = controller.xyToMotors(-3, 0);
    Move leftMagnetOn(tmpDirs, tmpSteps, true);

    tmpDirs[0] = Clockwise;
    Move down = controller.xyToMotors(0, -3);
    Move downMagnetOn(tmpDirs, tmpSteps, true);

    Move up_right = controller.xyToMotors(2, 2);
    Move up_left = controller.xyToMotors(-2, 2);
    Move down_right = controller.xyToMotors(2, -2);
    Move down_left = controller.xyToMotors(-2, -2);

    Serial.println("Finished creating moves, initializing motors");
    delay(250);

    //----------------------------- Initialize RobotControl ---------------------------//
    //SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    //SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);
    controller.initializeMotors();

    Serial.println("==== Motors initialized, queueing moves ====");
    delay(250);
    
    controller.queueMove(right);
    Serial.print("QUEUED:   ");
    right.printMove();

    controller.queueMove(up_right);
    Serial.print("QUEUED:   ");
    up_right.printMove();

    controller.queueMove(up);
    Serial.print("QUEUED:   ");
    up.printMove();

    controller.queueMove(up_left);
    Serial.print("QUEUED:   ");
    up_left.printMove();
    
    controller.queueMove(left);
    Serial.print("QUEUED:   ");
    left.printMove();

    controller.queueMove(down_left);
    Serial.print("QUEUED:   ");
    down_left.printMove();

    controller.queueMove(down);
    Serial.print("QUEUED:   ");
    down.printMove();

    controller.queueMove(down_right);
    Serial.print("QUEUED:   ");
    down_left.printMove();

    timerInit();
}

void loop() {
    static uint32_t lastTime = 0;
    static int timesComplete = 0;
    uint32_t ms = millis();

    if ((ms - lastTime) > 1000) { // Print Reports every 1/2 second
        lastTime = ms;
        controller.printReport();
        if (controller.moveComplete) { // Loads moves upon completion
            Serial.printf("\n\n");
            Serial.println("============== Loading Move... ==============\n");
            controller.getNextMove().printMove();
            controller.queueMove(controller.dequeueMove());
            controller.loadMove();
            Serial.printf("\n");
            delay(250);
            timesComplete += 1;
        }
    }
}

void timerInit() {
    cli(); // Stops Interrupts
    timer = timerBegin(3, 4, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    sei(); // Re-Enables interrupts
}


void IRAM_ATTR stepperISR() {
        controller.stepMotors();
}

void displaySteps() {
    Serial.printf("There are %d steps remaining.\n", steps[0]);
}