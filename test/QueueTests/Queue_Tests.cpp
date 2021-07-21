#include <Arduino.h>
#include <unity.h>

#include "Queue.hpp"

void test_Create_Queue(void) {
    try {
        Queue subject;

        if (subject.getHead() == nullptr) {
            TEST_FAIL_MESSAGE("ERROR:  HEAD IS NULL");
        }

        if (subject.getHead() != subject.getTail()) {
            TEST_FAIL_MESSAGE("ERROR:  TAIL != HEAD");
        }

        throw (-1);
    }
    catch (...) {
        TEST_FAIL_MESSAGE("ERROR:  COULD NOT INITIALIZE QUEUE");
    }
}

void test_EnQueue(void) {

}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_Create_Queue);
    RUN_TEST(test_EnQueue);
}

void loop() {
    UNITY_END();
}