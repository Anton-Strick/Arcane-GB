#pragma once

#ifndef CONGIG_HPP
#define CONFIG_HPP

#define NUM_MOTORS 2

#define DRIVER_ADDRESS     0b00        // TMC2209 Driver address
#define R_SENSE            0.11f       // E_SENSE for current calc.  
#define STALL_VALUE        2           // [0..255]

#define STEP_BIT_POS       0           // Faster access to base position

#define STEPS_PER_MM       39.6
#define MM_PER_SQUARE      37.25

enum dir { AntiClockwise = 1, Clockwise = 0 };

// --------------------------------- Motor 0 Definition ---------------------------------
#define EN_PIN0             18         // Enable
#define DIAG_PIN0           19         // STALL readout
#define DIR_PIN0            13         // Direction
#define STEP_PIN0           15         // Step
#define RXD0                16         // RX pin, can be any GPIO
#define TXD0                17         // TX pin, can be any GPIO
#define SERIAL_PORT0        Serial1

// --------------------------------- Motor 1 Definition ---------------------------------
#define EN_PIN1             12         // Enable
#define DIAG_PIN1           21         // STALL readout
#define DIR_PIN1            27         // Direction
#define STEP_PIN1           14         // Step
#define RXD1                3          // RX pin, can be any GPIO
#define TXD1                1          // TX pin, can be any GPIO
#define SERIAL_PORT1        Serial2

//--------------------------------- Electromagnet Definition -------------------------//
#define MAGNET_PIN          23         // Used to toggle the magnet relay

void configPins();

#define RST_BTN_PIN         0
#define PAIR_BTN_PIN        35

#define NUM_ROWS 12
#define NUM_COLS 8

#endif