#include <Arduino.h>
#include "RobotControl.hpp"

/**
 * Creates a blank instance of RobotControl. Requires the user to call 
 * "this.intializeMotors() in order to function properly."
 */
RobotControl::RobotControl() {
    this->initializeQueue();
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
    SERIAL_PORT0.begin(115200, SERIAL_8N1, RXD0, TXD0);
    SERIAL_PORT1.begin(115200, SERIAL_8N1, RXD1, TXD1);

    TMC2209Stepper driver0(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    TMC2209Stepper driver1(&SERIAL_PORT0, R_SENSE, DRIVER_ADDRESS);
    motors[0] = new Motor((uint8_t) 0, driver0, DIAG_PIN0, DIR_PIN0, STEP_PIN0);
    motors[1] = new Motor((uint8_t) 1, driver1, DIAG_PIN1, DIR_PIN1, STEP_PIN1);

    for (Motor* m : motors) {
        m->init();
    }

    configPins(); // located in config
}

/**
 * Initilializes a blank queue to be assigned to the Robot Control Class
 */
void RobotControl::initializeQueue() {
    this->queue = new Queue();
}

void RobotControl::stepMotors() {
    this->moveComplete = true;
    for (Motor* m : this->motors) {
        m->step();
        moveComplete = moveComplete && m->getComplete();
    }
}

/**
 * Converts cartesian movement into coreXY movement
 * @param {int16_t} dX The number of steps in the X direction
 * @param {int16_t} dY The number of steps in the Y direction
 * @return Move containing the direction and number of steps required
 *         to achieve the desired motion
 */
Move* RobotControl::xyToMotors(int16_t dX, int16_t dY) {
    int16_t dA = (0.5) * (dX + dY);
    int16_t dB = (0.5) * (dX - dY);

    std::array<uint8_t, NUM_MOTORS> dirs;
    dirs[0] = (dA > 0) ? AntiClockwise : Clockwise;
    dirs[1] = (dB > 0) ? AntiClockwise : Clockwise;

    std::array<uint32_t, NUM_MOTORS> steps;
    steps[0] = (dA > 0) ? (uint32_t) dA : (uint32_t) (dA * -1);
    steps[1] = (dB > 0) ? (uint32_t) dB : (uint32_t) (dB * -1);

    Move* newMove = new Move(dirs, steps);
    return newMove;
}

void RobotControl::printReport() {
    Serial.println("========== R-Control Report ===========");
    Serial.printf("Number of Moves in Queue:  %d", this->queue->getSize());
    motors[0]->displayReport();
    motors[1]->displayReport();
    Serial.printf("\nNext Move:     ");
    this->queue->getTail()->printMove();
}

Move* RobotControl::dequeueMove() {
    if (this->queue->getTail() == this->queue->getHead())
        return NULL;

    return this->queue->deQueue(); 
}

void RobotControl::loadMove(Move* m ) {
    std::array<uint8_t, NUM_MOTORS> dirs = m->getDirs();
    std::array<uint32_t, NUM_MOTORS> steps = m->getSteps();
    for (int i = 0 ; i < NUM_MOTORS ; i++) {
        this->motors[i]->setDir(dirs[i]);
        this->motors[i]->setTarget(steps[i]);
    }
}