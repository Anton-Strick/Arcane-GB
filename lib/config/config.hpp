#pragma once

#ifndef CONGIG_HPP
#define CONFIG_HPP

#define NUM_MOTORS 2
#define XSTEP_PMM  80
#define YSTEP_PMM  80

#define DRIVER_ADDRESS     0b00        // TMC2209 Driver address
#define R_SENSE            0.11f       // E_SENSE for current calc.  
#define STALL_VALUE        2           // [0..255]

#define STEP_BIT_POS        0          // Faster access to base position

// --------------------------------- Motor 1 Definition ---------------------------------
#define EN_PIN0             14         // Enable
#define DIAG_PIN0           15         // STALL readout
#define DIR_PIN0            4          // Direction
#define STEP_PIN0           2          // Step
#define RXD0                16         // RX pin, can be any GPIO
#define TXD0                17         // TX pin, can be any GPIO
#define SERIAL_PORT0        Serial2

// --------------------------------- Motor 2 Definition ---------------------------------
#define EN_PIN1             14         // Enable
#define DIAG_PIN1           25         // STALL readout
#define DIR_PIN1            26         // Direction
#define STEP_PIN1           27         // Step
#define RXD1                22         // RX pin, can be any GPIO
#define TXD1                23         // TX pin, can be any GPIO
#define SERIAL_PORT1        Serial1

enum dir { AntiClockwise, Clockwise };

void configMotorPins();

#endif