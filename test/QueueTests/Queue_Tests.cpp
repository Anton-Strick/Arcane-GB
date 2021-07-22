#include <Arduino.h>
#include <unity.h>

#include "Queue.hpp"

void test_Create_Queue(void) {
    Queue subject;

    if (subject.getHead() == nullptr) {
        TEST_FAIL_MESSAGE("ERROR:  HEAD IS NULL");
    }

    if (subject.getHead() != subject.getTail()) {
        TEST_FAIL_MESSAGE("ERROR:  TAIL != HEAD");
    }

    if (subject.hasMoves != false) {
        TEST_FAIL_MESSAGE("ERROR:  INITIALIZES WITH HAS MOVES");
    }

    if (subject.getSize() != uint8_t(0)) {
        TEST_FAIL_MESSAGE("ERROR:  INITIALIZES WITH SIZE > 0");
    }
}

void test_Enqueue(void) {
    Queue subject;
    std::array<uint8_t, NUM_MOTORS> dirs = 
        { Clockwise, Clockwise };
    std::array<uint32_t, NUM_MOTORS> steps = 
        { 20, 20 };
    Move test(dirs, steps);
    subject.enQueue(test);

    if (subject.getSize() != 1) {
        TEST_FAIL_MESSAGE("ERROR:  SIZE WAS NOT INCREMENTED");
    }

    if (subject.getNextMove()->getSteps() != steps) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT STEPS COUNT");
    }

    if (subject.getNextMove()->getDirs() != dirs) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT MOTOR DIRECTIONS");
    } 
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_Create_Queue);
    RUN_TEST(test_Enqueue);
}

void loop() {
    UNITY_END();
}