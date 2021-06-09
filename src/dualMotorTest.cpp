/** Notes for Testing
 *  - Our motors use 200 steps per revolution
 *  - Converting Motors to classes would help a bit
 */

#include <Arduino.h>
#include <HardwareSerial.h>
#include <TMCStepper.h>

#define DRIVER_ADDRESS     0b00        // TMC2209 Driver address
#define R_SENSE            0.11f       // E_SENSE for current calc.  
#define STALL_VALUE        2           // [0..255]
#define EN_PIN             14         // Enable

// --------------------------------- Motor 1 Definition ---------------------------------
#define DIAG1_PIN          15          // STALL readout
#define DIR1_PIN            4          // Direction
#define STEP1_PIN           2          // Step
#define RXD0                1          // RX pin, can be any GPIO
#define TXD0                3          // TX pin, can be any GPIO
#define STEP1_BIT_POS       0          // Faster Reguster Access = Faster Step Speed
HardwareSerial Serial0(1);             // Serial Port
TMC2209Stepper driver0(&Serial0, R_SENSE, DRIVER_ADDRESS);

// --------------------------------- Motor 2 Definition ---------------------------------
#define DIAG2_PIN           25         // STALL readout
#define DIR2_PIN            26         // Direction
#define STEP2_PIN           27         // Step
#define RXD2                16         // RX pin, can be any GPIO
#define TXD2                17         // TX pin, can be any GPIO
#define STEP1_BIT_POS        0         // Faster Reguster Access = Faster Step Speed
HardwareSerial Serial1(2);             // Serial port
TMC2209Stepper driver1(&Serial1, R_SENSE, DRIVER_ADDRESS);

uint32_t motorPosition[2];

hw_timer_t * timer0 = NULL;
hw_timer_t * timer1 = NULL;

using namespace TMC2208_n;

void timerInit();

void IRAM_ATTR motor0() {
    // Serial.println("Motor 1 steps");
    digitalWrite(STEP1_PIN, !digitalRead(STEP1_PIN));
    motorPosition[0]++;
}

void IRAM_ATTR motor1() {
    //Serial.println("Motor 2 steps");
    digitalWrite(STEP2_PIN,!digitalRead(STEP2_PIN));
    motorPosition[1]++;
}

void setup() {
    //------------------------------ Connect to Computer ------------------------------//
    Serial.begin(115200);
    while (!Serial);

    Serial.println("Start");

    //----------------------------- Connect to Motors 1/2 -----------------------------//
    Serial1.begin(115200, SERIAL_8N1, RXD0, TXD0);
    Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);

    //---------------------------------- Pin Modes ------------------------------------//
    pinMode(DIAG1_PIN, INPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(STEP1_PIN, OUTPUT);
    pinMode(STEP2_PIN, OUTPUT);
    pinMode(DIR1_PIN, OUTPUT);
    pinMode(DIR2_PIN, OUTPUT);

    digitalWrite(EN_PIN, LOW);
    digitalWrite(DIR1_PIN, HIGH);
    digitalWrite(DIR2_PIN, LOW);

    //--------------------------------- Driver Init -----------------------------------//
    driver0.begin();
    driver0.toff(4); // Can be any value between 1-15
    driver0.blank_time(24);
    driver0.rms_current(500); //mA
    driver0.microsteps(8);
    driver0.TCOOLTHRS(0xFFFFF);
    driver0.semin(0);
    driver0.semax(2);
    driver0.shaft(false);
    driver0.sedn(0xb01);
    driver0.SGTHRS(STALL_VALUE);

    driver1.begin();
    driver1.toff(4); // Can be any value between 1-15
    driver1.blank_time(24);
    driver1.rms_current(500);
    driver1.microsteps(8);
    driver1.TCOOLTHRS(0xFFFFF);
    driver1.semin(0);
    driver1.semax(2);
    driver1.shaft(false);
    driver1.sedn(0xb01);
    driver1.SGTHRS(STALL_VALUE);

    for (uint32_t n : motorPosition)
        n = 0; // Set all positions to 0

    timerInit();
}
void loop() {
    static uint32_t lastTime = 0;
    uint32_t ms = millis();
    if ((ms - lastTime) > 500) { // Print Reports every second
        lastTime = ms;
        Serial.printf("\nDriver 0 Report\n ===============");
        displayReport(driver0, 0);
        Serial.printf("\nDriver 1 Report\n ===============");
        displayReport(driver1, 1);
    }
}

void timerInit() {
    cli(); // Stops Interrupts
    //----------------------- Configure Motor 0 Timer -----------------------//
    timer0 = timerBegin(3, 16, true);
    timerAttachInterrupt(timer0, &motor1, true);
    timerAlarmWrite(timer0, 10000, true);
    timerAlarmEnable(timer0);
    //----------------------- Configure Motor 1 Timer -----------------------//
    timer1 = timerBegin(3, 8, true); // Spins 2x as fast as Motor 0
    timerAttachInterrupt(timer1, &motor1, true);
    timerAlarmWrite(timer1, 10000, true);
    timerAlarmEnable(timer1);
    sei(); // Re-Enables interrupts
}

void displayReport(TMC2209Stepper d, int motorID) {
    Serial.printf("Stallguard: %5.2f \nCS Actual: %5.2f\nuSteps Made: %d\n", 
                  d.SG_RESULT(),
                  d.cs_actual(),
                  motorPosition[motorID]);

}