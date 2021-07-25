#include <Arduino.h>
#include "RobotControl.hpp"

/**
 * Creates a blank instance of RobotControl. Requires the user to call 
 * "this.intializeMotors() in order to function properly."
 */
RobotControl::RobotControl() {
    
}

/**
 * Sets the motors to DISABLED using the pins defined in config.hpp
 */
void RobotControl::disableMotors() { 
    digitalWrite(EN_PIN0, HIGH);
    digitalWrite(EN_PIN1, HIGH);
}

/**
 * Sets the motors to ENABLED using the pins defined in config.hpp
 */
void RobotControl::enableMotors() { 
    digitalWrite(EN_PIN0, LOW);
    digitalWrite(EN_PIN1, LOW); 
}

/**
 * Initializes all required components of the Motors controlled by this
 * instance of RobotControl. (Serial, TMC2209Stepper, Motor Pins)
 */
void RobotControl::initializeMotors() {
    configPins(); // located in config
    
    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    TMC2209Stepper driver1(&SERIAL_PORT1, R_SENSE, DRIVER_ADDRESS);
    motors[0] = new Motor((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);
    motors[1] = new Motor((uint8_t) 1, driver1, DIAG_PIN1, DIR_PIN1, STEP_PIN1);

    for (Motor * m : motors) {
        m->init();
    }
}

void RobotControl::stepMotors() {
    bool temp = true;
    for (Motor * m : this->motors) {
        m->step();
        temp = temp && m->getComplete();
    }

    moveComplete = temp;
}

/**
 * Converts cartesian movement into coreXY movement
 * @param {int16_t} dX The number of steps in the X direction
 * @param {int16_t} dY The number of steps in the Y direction
 * @return Move containing the direction and number of steps required
 *         to achieve the desired motion
 */
Move RobotControl::xyToMotors(int8_t dX, int8_t dY, bool mE = false) {
    int32_t dA = (dX - dY) * STEPS_PER_MM * MM_PER_SQUARE;
    int32_t dB = (dX + dY) * STEPS_PER_MM * MM_PER_SQUARE;

    std::array<uint8_t, NUM_MOTORS> dirs;
    dirs[0] = (dA < 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB < 0) ? AntiClockwise : Clockwise;

    std::array<uint32_t, NUM_MOTORS> steps;
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    Move newMove(dirs, steps, mE);
    return newMove;
}

void RobotControl::printReport() {
    Serial.println("========== R-Control Report ===========");
    Serial.printf("Number of Moves in Queue:  %d", queue.getSize());
    motors[0]->displayReport();
    motors[1]->displayReport();
    Serial.printf("\nNext Move:     ");
    queue.getTail().printMove();
}

void RobotControl::loadMove() {
    disableMagnet();
    if (queue.hasMoves()) { // If has Moves
        moveComplete = false;
        Move tmp = dequeueMove();

        // Magnet disable or enable
        if (tmp.getMagnetEnabled()) {
            enableMagnet();
        }

        delay(250);

        // Motor direction and steps
        for (uint8_t i = 0 ; i < NUM_MOTORS ; i++) {
            motors[i]->setDir(tmp.getDirs()[i]);
            motors[i]->setTarget(tmp.getSteps()[i]);
        }
    } // End has Moves

    // No action if ! has moves
}

void RobotControl::queueMoves(Queue q) {
    while (q.hasMoves()) {
        queue.enQueue(q.deQueue());
    }
}