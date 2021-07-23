#include <Arduino.h>
#include "config.hpp"

void configPins() {
    //----------------- Motor 0 Pin Configuration -----------------//
    pinMode(DIAG_PIN0, INPUT);
    pinMode(DIR_PIN0, OUTPUT);
    pinMode(STEP_PIN0, OUTPUT);
    pinMode(EN_PIN0, OUTPUT);

    //----------------- Motor 1 Pin Configuration -----------------//

    pinMode(DIAG_PIN1, INPUT);
    pinMode(DIR_PIN1, OUTPUT);
    pinMode(STEP_PIN1, OUTPUT);
    pinMode(EN_PIN1, OUTPUT);

    //------------------------- Misc Pins -------------------------//

    pinMode(MAGNET_PIN, OUTPUT);
    pinMode(PAIR_BTN_PIN, INPUT);
    pinMode(RST_BTN_PIN, INPUT);
}