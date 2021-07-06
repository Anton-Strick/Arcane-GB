#include <Arduino.h>
#include <robotControl.hpp>


Motor *motors[NUM_MOTORS];
Queue *q = new Queue();
Move nextMove;

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

    //----------------------------- Connect to Motors 1/2 -----------------------------//
    Serial1.begin(115200, SERIAL_8N1, RXD0, TXD0);
    Serial2.begin(115200, SERIAL_8N1, RXD1, TXD1);

    //---------------------------------- Pin Modes ------------------------------------//
    pinMode(DIAG_PIN0, INPUT);
    pinMode(DIAG_PIN1, INPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(STEP_PIN0, OUTPUT);
    pinMode(STEP_PIN1, OUTPUT);
    pinMode(DIR_PIN0, OUTPUT);
    pinMode(DIR_PIN1, OUTPUT);

    digitalWrite(EN_PIN, LOW);
    digitalWrite(DIR_PIN0, HIGH);
    digitalWrite(DIR_PIN1, HIGH);

    Serial.println("====== Beginning Queued Motor Test =====");

    uint8_t  moveDirs[NUM_MOTORS];
    uint32_t moveSteps[NUM_MOTORS];

    for (uint8_t d : moveDirs) {
        d = Clockwise;
    }
    
    for (uint32_t s : moveSteps) {
        s = 400;
    }
    

    
    // Queue Synched Motors, 180 Degrees clockwise
    Serial.printf("Queueing synched motors: 180 degrees clockwise\n");
    q->enQ(moveDirs, moveSteps);

    for (uint8_t d : moveDirs) {
        d = AntiClockwise;
    }

    // Queue Synched Motors, 180 Degrees Anti-Clockwise
    Serial.printf("Queueing synched motors: 180 degrees anticlockwise\n");
    q->enQ(moveDirs, moveSteps);

    moveDirs[1] = Clockwise;
    moveSteps[0] = 800;

    
    /* Queue Counter-rotating motors:
            Motor0: Anti-Clockwise for 360d
            Motor1: Clockwise for 180d
    */
    Serial.printf("Queueing opposing motors\n",
                   "\tMotor0: Anticlockwise for 360d",
                   "\tMotor1: Clockwise for 180d");
    q->enQ(moveDirs, moveSteps);

    Serial.printf("============ Queue Complete ============\n\n");

    Serial.println("Enabling Motor Drivers...");
    motors[0] = new Motor(0, SERIAL_PORT0, DIAG_PIN0, DIR_PIN0, 
                          STEP_PIN0, RXD0, TXD0);
    motors[1] = new Motor(1, SERIAL_PORT1, DIAG_PIN1, DIR_PIN1, 
                          STEP_PIN1, RXD1, TXD1);

    motors[0]->init();
    motors[1]->init();
    Serial.printf("Drivers Enabled!\n\n");

    timerInit();
}

void loop() {
    static uint32_t lastTime = 0;
    uint32_t ms = millis();
    if ((ms - lastTime) > 500) { // Print Reports every 1/2 second
        if (q->hasMoves) {
            //Serial.printf("Executing Move %d/3...\n", moveCounter);
        }
            

        else if (moveCounter > 0) {
            //Serial.println("Executing Final Move...");
        }

        else {
            Serial.println("Test complete! Sleeping...");
            sleep(10000);
        }
    }
}

void timerInit() {
    cli(); // Stops Interrupts
    timer = timerBegin(3, 16, true);
    timerAttachInterrupt(timer, &stepperISR, true);
    timerAlarmWrite(timer, 10000, true);
    timerAlarmEnable(timer);
    sei(); // Re-Enables interrupts
}


void IRAM_ATTR stepperISR() {
        motors[0]->step();
        motors[1]->step();
}

void displaySteps() {
    Serial.printf("There are %d steps remaining.\n", steps[0]);
}