#include <Arduino.h>
#include <array>
#include <unity.h>

#include <sstream>
#include <string>

#include "config.hpp"
#include "Piece.hpp"
#include "GameController.hpp"

/**
 * Piece Class Tests
 */
void test_Piece_Construction(void) {
    std::array<uint8_t, 2> position = { 7, 7 };
	bool expected = true;
	bool test = true;
	uint8_t pieceID = (uint8_t) 0xb10101000;
	Piece bRook(position, pieceID);

	test = test && ( position == bRook.getPosition() );
	test = test && ( pieceID == bRook.getID() );

	TEST_ASSERT_EQUAL(expected, test);
}

void test_Piece_Move(void) {
    std::array<uint8_t, 2> position = { 7, 7 };
    uint8_t pieceID = (uint8_t) 0xb10101000;
    Piece bRook(position, pieceID);
    std::array<uint8_t, 2> newPosition = { 0, 7 };
    bRook.setPosition(newPosition);
    bool test = newPosition == bRook.getPosition();
    TEST_ASSERT_EQUAL(true, test);
}

/**
 * GameController Class Tests
 */
void test_Controller_Construction(void) {
    GameController subject;
}

void test_Get_Transposition(void) {

}

void test_Plan_Path(void) {
    
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_Piece_Construction);
    RUN_TEST(test_Piece_Move);
    RUN_TEST(test_Controller_Construction);
    RUN_TEST(test_Get_Transposition);
}

void loop() {
    UNITY_END();
}
