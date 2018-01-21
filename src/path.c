#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#include "calibrate.h"
#include "path.h"

#define PROPORTIONAL 0.1
#define INTEGRAL 0.004
#define DERIVATIVE 0.3
#define BASE_SPEED 60
#define MAX_SPEED 85

void turn(double pid);

// used for derivative
int previousError = 0;
// used for integral
int errorSum = 0;
int lastIntegralCount = 0;

// Assumes the robot is placed on the right side of the tape
void followLine() {
    int error = getPathLight() - optimalLight;
    errorSum = sameSignInt(error, previousError) ? errorSum + error : 0;
    double proportional = error * PROPORTIONAL;
    double integral = errorSum * INTEGRAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pid = proportional + integral + derivative;
    previousError = error;
    turn(pid);
}

// Returns the light intensity of the path
int getPathLight() {
    return ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
}

// Assumes the robot is placed on the right side of the tape
// Translates the pid input to two outputs for the left and right motor
void turn(double pid) {
    // Guards to make sure we don't send too high values to the motor
    int rightSpeed = clampInt(BASE_SPEED + pid, -MAX_SPEED, MAX_SPEED);
    int leftSpeed = clampInt(BASE_SPEED - pid, -MAX_SPEED, MAX_SPEED);

    nxt_motor_set_speed(LEFT_MOTOR, leftSpeed, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, rightSpeed, 1);
}

// Stops the left and right motor
void stopDriving() {
    nxt_motor_set_speed(LEFT_MOTOR, 0, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 0, 1);
}
