#include <Arduino.h>
#include <array>
#include <unity.h>

#include "config.hpp"
#include "RobotControl.hpp"


std::array<uint8_t, NUM_MOTORS> dirs = { 
    Clockwise, Clockwise
};
std::array<uint32_t, NUM_MOTORS> steps = { 
    STEPS_PER_MM * MM_PER_SQUARE, 
    STEPS_PER_MM * MM_PER_SQUARE 
};
Move expected(dirs, steps);

/**
 * Motor Class Tests
 */
void test_Motor_Initial_Position(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    TEST_ASSERT_EQUAL(0, motor0.getPosition());
}

void test_Motor_Initial_Target(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    TEST_ASSERT_EQUAL(0, motor0.getTarget());
}

void test_Motor_Init(void) {
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    TEST_ASSERT_EQUAL(true, motor0.init());
}

void test_Motor_Set_Target(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    motor0.setTarget(1500);
    TEST_ASSERT_EQUAL(1500, motor0.getTarget());
}

void test_Motor_Get_Steps_To_Go(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    uint32_t target = 1500;
    motor0.setTarget(target);
    TEST_ASSERT_EQUAL(target, motor0.getStepsToGo());
}

void test_Motor_Set_Direction(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    motor0.setDir(AntiClockwise);
    TEST_ASSERT_EQUAL(AntiClockwise, digitalRead(DIR_PIN0));
}

void test_Motor_Step(void) {
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    Motor motor0((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);

    motor0.setDir(Clockwise);
    uint32_t target = STEPS_PER_MM * MM_PER_SQUARE;
    motor0.setTarget(target);
    motor0.step();

    if (motor0.getPosition() != 1) {
        TEST_FAIL_MESSAGE("ERROR:  STEP DID NOT INCREMENT POSITIVE");
    }

    motor0.setDir(AntiClockwise);
    motor0.step();

    if (motor0.getPosition() != 0) {
        TEST_FAIL_MESSAGE("ERROR:  STEP DID NOT INCREMENT NEGATIVE");
    }
}

void test_Construct_Controller(void) {
    RobotControl subject;
}


void test_Queue_Move(void) {
    RobotControl subject;

    subject.queueMove(expected);
}

void test_Dequeue_Move(void) {
    RobotControl subject;

    subject.queueMove(expected);
    Move test = subject.dequeueMove();

    if (test.getSteps() != expected.getSteps()) {
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT STEPS RETURNED");
    }

    if (test.getDirs() != expected.getDirs()) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT DIRECTIONS RETURNED");
    }
}

void test_Initialize_Motors(void) {
    RobotControl subject;
    subject.initializeMotors();
}

void test_Load_Move (void) {
    RobotControl subject;
    subject.queueMove(expected);
}

void test_XY_To_Motors(void) {
    RobotControl subject;
}

void test_Enable_Magnet(void) {
    RobotControl subject;
    subject.enableMagnet();
    TEST_ASSERT_EQUAL(LOW, digitalRead(MAGNET_PIN));
}

void test_Disable_Magnet(void) {
    RobotControl subject;
    subject.disableMagnet();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MAGNET_PIN));
}

void test_Step_Motors(void) {
    RobotControl subject;

    std::array<uint8_t, 2> dirs { Clockwise, Clockwise };
    std::array<uint32_t, 2> steps { 
        2 * STEPS_PER_MM * MM_PER_SQUARE,
        2 * STEPS_PER_MM * MM_PER_SQUARE 
    };
}

void setup() {
    configPins(); // located in config
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);
    UNITY_BEGIN();
    RUN_TEST(test_Motor_Initial_Position);
    RUN_TEST(test_Motor_Initial_Target);
    RUN_TEST(test_Motor_Init);
    SERIAL_PORT0.end(); // Shut down serial used during Motor.init()

    RUN_TEST(test_Motor_Set_Target);
    RUN_TEST(test_Motor_Get_Steps_To_Go);
    RUN_TEST(test_Motor_Set_Direction);
    RUN_TEST(test_Motor_Step);

    RUN_TEST(test_Construct_Controller);
    RUN_TEST(test_Queue_Move);
    RUN_TEST(test_Dequeue_Move);
    RUN_TEST(test_XY_To_Motors);

    RUN_TEST(test_Initialize_Motors);
    RUN_TEST(test_Step_Motors);
}

void loop() {
    static uint8_t loops = 0;

    RUN_TEST(test_Enable_Magnet);
    delay(3000);

    RUN_TEST(test_Disable_Magnet);    
    delay(3000);

    if (loops >= 1000) {

        UNITY_END();
    }

    loops++;
}