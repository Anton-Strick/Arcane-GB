#pragma once

#ifndef CONGIG_HPP
#define CONFIG_HPP

#define NUM_MOTORS 2
#define STEPS_PER_MM 80

#define DRIVER_ADDRESS     0b00        // TMC2209 Driver address
#define R_SENSE            0.11f       // E_SENSE for current calc.  
#define STALL_VALUE        2           // [0..255]

#define STEP_BIT_POS        0          // Faster access to base position

// --------------------------------- Motor 0 Definition ---------------------------------
#define EN_PIN0             18         // Enable
#define DIAG_PIN0           21         // STALL readout
#define DIR_PIN0            19         // Direction
#define STEP_PIN0           5          // Step
#define RXD0                16         // RX2 pin
#define TXD0                17         // TX2 pin
#define SERIAL_PORT0        Serial2

// --------------------------------- Motor 1 Definition ---------------------------------
#define EN_PIN1             33         // Enable
#define DIAG_PIN1           35         // STALL readout
#define DIR_PIN1            32         // Direction
#define STEP_PIN1           25         // Step
#define RXD1                27         // RX pin, can be any GPIO
#define TXD1                26         // TX pin, can be any GPIO
#define SERIAL_PORT1        Serial1

enum dir { AntiClockwise, Clockwise };

void configMotorPins();

#endif