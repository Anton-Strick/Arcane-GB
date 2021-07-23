#include <Arduino.h>
#include <unity.h>

#include <queue>

#include "Queue.hpp"

void test_Create_Queue(void) {
    Queue subject;
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

    if (subject.getNextMove().getSteps() != steps) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT STEPS COUNT");
    }

    if (subject.getNextMove().getDirs() != dirs) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT MOTOR DIRECTIONS");
    } 
}

void test_Dequeue(void) {
    Queue subject;
    std::array<uint8_t, NUM_MOTORS> dirs = { 
        Clockwise, Clockwise
    };
    std::array<uint32_t, NUM_MOTORS> steps = { 
        STEPS_PER_MM * MM_PER_SQUARE, 
        STEPS_PER_MM * MM_PER_SQUARE 
    };
    
    Move expected(dirs, steps);
    subject.enQueue(expected);

    try {
        Move test = subject.deQueue();

        if (subject.getSize() != 0) {
            TEST_FAIL_MESSAGE("ERROR:  SIZE WAS NOT DECREMENTED");
        }

        if (test.getSteps() != expected.getSteps()) {
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT STEPS RETURNED");
        }

        if (test.getDirs() != expected.getDirs()) {
            TEST_FAIL_MESSAGE("ERROR:  INCORRECT DIRECTIONS RETURNED");
        }
    }

    catch(...) {
        TEST_FAIL_MESSAGE("ERROR:  PROGRAM CRASHED DURING DEQUEUE");
    }
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_Create_Queue);
    RUN_TEST(test_Enqueue);
    RUN_TEST(test_Dequeue);
}

void loop() {
    UNITY_END();
}