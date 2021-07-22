#include <Arduino.h>
#include <array>
#include <unity.h>

#include "config.hpp"
#include "RobotControl.hpp"

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

void setup() {
    configPins(); // located in config
    UNITY_BEGIN();
    RUN_TEST(test_Motor_Initial_Position);
    RUN_TEST(test_Motor_Initial_Target);
    RUN_TEST(test_Motor_Init);
    SERIAL_PORT0.end(); // Shut down serial used during Motor.init()

    RUN_TEST(test_Motor_Set_Target);
    RUN_TEST(test_Motor_Get_Steps_To_Go);
    RUN_TEST(test_Motor_Set_Direction);
    RUN_TEST(test_Motor_Step);
}

void loop() {
    UNITY_END();
}
