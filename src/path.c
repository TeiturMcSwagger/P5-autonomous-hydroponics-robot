#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"

int getPathLight();
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
    int lightValue = ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    return lightValue;
}

// Assumes the robot is placed on the right side of the tape
// Translates the pid input to two outputs for the left and right motor
void turn(double pid) {
    const int baseSpeed = 60;
    const int maxSpeed = 85;
    int leftSpeed = 0;
    int rightSpeed = 0;

    // Guards to make sure we don't send too high values to the motor
    rightSpeed = clampInt(baseSpeed + pid, -maxSpeed, maxSpeed);
    leftSpeed = clampInt(baseSpeed - pid, -maxSpeed, maxSpeed);

    nxt_motor_set_speed(LEFT_MOTOR, leftSpeed, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, rightSpeed, 1);
}

// Stops the left and right motor
void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
}
