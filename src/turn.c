#include "calibrate.h"
#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"
#include "util.h"

/*
 * assumes to robot is placed on the right side of the tape
 */
void drive() {
    int error = getLightValue() - optimalLightValue;
    U32 leftMotor = NXT_PORT_A;
    U32 rightMotor = NXT_PORT_B;

    // robot is way of the tape to the right
    if (error > 60) {
        //printString("error > 50");
        nxt_motor_set_speed(leftMotor, -20, 1);
        nxt_motor_set_speed(rightMotor, 20, 1);
    }
    // robot is almost to the right of the tape
    else if (error > 30) {
        //printString("error > 30");
        nxt_motor_set_speed(leftMotor, 20, 1);
        nxt_motor_set_speed(rightMotor, 70, 1);
    }
    // robot is sligty too far right
    else if (error > 10) {
        //printString("error > 10");
        nxt_motor_set_speed(leftMotor, 50, 1);
        nxt_motor_set_speed(rightMotor, 70, 1);
    }
    // robot is way of the tape to the left
    else if (error > -50) {
        //printString("error > -50");
        nxt_motor_set_speed(leftMotor, 50, 1);
        nxt_motor_set_speed(rightMotor, -50, 1);
    }
    // robot is almost to the left of the tape
    else if (error > -30) {
        //printString("error > -30");
        nxt_motor_set_speed(leftMotor, 70, 1);
        nxt_motor_set_speed(rightMotor, 40, 1);
    }
    // robot is sligty too far left
    else if (error > -10) {
        //printString("error > -10");
        nxt_motor_set_speed(leftMotor, 70, 1);
        nxt_motor_set_speed(rightMotor, 50, 1);
    }
    // almost at optimal position, drive straight
    else {
        //printString("drive straight");
        nxt_motor_set_speed(leftMotor, 20, 1);
        nxt_motor_set_speed(rightMotor, -20, 1);
    }
}

void stopMotor() {
    int stop = 0;
    nxt_motor_set_speed(0, stop, 1);
    nxt_motor_set_speed(1, stop, 1);
}
/*
void turnMe() {
    lightValue = 250;
    // Rotate motor to angle based on lightValue
    rotateMotorToAngle(
        100, MAX_STEERING_ANGLE - (lightValue * translationfactor), NXT_PORT_A);
}
*/
