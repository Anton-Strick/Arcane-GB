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
    
}

void setup() {
    configPins(); // located in config
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);
    UNITY_BEGIN();
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