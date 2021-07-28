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
    std::array<int8_t, 2> position = { 7, 7 };
	bool expected = true;
	bool test = true;
	uint8_t pieceID = (int8_t) 0b10101000;
	Piece bRook(position, pieceID);

	test = test && ( position == bRook.getPosition() );
	test = test && ( pieceID == bRook.getID() );

	TEST_ASSERT_EQUAL(expected, test);
}

void test_Piece_Move(void) {
    GameController subject;
    std::array<int8_t, 2> newPosition = { 0, 7 };
    subject.getPiece(0)->setPosition(newPosition);
    bool test = (newPosition == subject.getPiece(0)->getPosition());
    TEST_ASSERT_EQUAL(7, subject.getPiece(0)->getPosition()[1]);
}

void test_Piece_Get_Color(void) {
    uint8_t pieceID = White | Pawn | 0b0000;
    Piece whitePawn;
    whitePawn.setID(pieceID);
    TEST_ASSERT_EQUAL(White, whitePawn.getPieceColor());
}

void test_Piece_Get_Type(void) {
    uint8_t pieceID = White | Pawn | 0b0000;
    Piece whitePawn;
    whitePawn.setID(pieceID);
    TEST_ASSERT_EQUAL(Pawn, whitePawn.getPieceType());
}

void test_Piece_Get_Retire_Col(void) {
    uint8_t pieceID = White | Pawn | 0b0000;
    Piece whitePawn;
    whitePawn.setID(pieceID);
    TEST_ASSERT_EQUAL(0, whitePawn.getRetireCol());
}

void test_Piece_Get_Retire_Row(void) {
    uint8_t pieceID = White | Pawn | 0b0000;
    Piece whitePawn;
    whitePawn.setID(pieceID);
    TEST_ASSERT_EQUAL(0, whitePawn.getRetireCol());
}
/**
 * GameController Class Tests
 */
void test_Controller_Construction(void) {
    GameController subject;
}

void test_Get_Piece(void) {
    GameController subject;
    Piece * test = subject.getPiece(0); // Should be pawn-0
    std::array<int8_t, 2> pos = { 0, 3 };
    uint8_t id = uint8_t(0b00000000);

    if (pos != test->getPosition()) {
        TEST_FAIL_MESSAGE("ERROR:  INCORRECT POSITION");
    }

    if (id != test->getID()) {
        TEST_FAIL_MESSAGE("ERROR: INCORRECT ID");
    }
}

void test_Get_Piece_At(void) {
    GameController subject;
    std::array<int8_t, 2> pos = {4, 3};
    int8_t index = subject.pieceAt(pos);
    TEST_ASSERT_EQUAL(4, index);
}

void test_Get_Transposition(void) {
    GameController subject;
}

void test_Plan_Path(void) {
    GameController subject;
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_Piece_Construction);
    RUN_TEST(test_Piece_Move);
    RUN_TEST(test_Piece_Get_Color);
    RUN_TEST(test_Piece_Get_Type);
    RUN_TEST(test_Piece_Get_Retire_Col);
    RUN_TEST(test_Piece_Get_Retire_Row);
    RUN_TEST(test_Get_Piece_At);
    //RUN_TEST(test_Controller_Construction);
    //RUN_TEST(test_Get_Transposition);
}

void loop() {
    UNITY_END();
}
