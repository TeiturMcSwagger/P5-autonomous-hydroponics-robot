#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"

int getPathLight();
void turn(double pid);

// used for integral
int errorSum = 0;
// used for derivative
int previousError = 0;

// Assumes the robot is placed on the right side of the tape
void followLine() {
    int error = getPathLight() - optimalLight;
    errorSum = errorSum + error;
    double proportional = error * PROPORTIONAL;
    double integral = errorSum * INTEGRAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pid = proportional + integral + derivative;
    if (pid < 0) {
        // multiply by a constant to make SARAH turn more right
        // because the robot struggles with right turns
        pid = pid * 1.4;
    }
    previousError = error;
    turn(pid);
}

// Returns the light intensity of the path
int getPathLight() {
    GetResource(ColourSensorResource);
    int lightValue = ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    ReleaseResource(ColourSensorResource);
    return lightValue;
}

// Assumes the robot is placed on the right side of the tape
// Translates the pid input to two outputs for the left and right motor
void turn(double pid) {
    clearScreen();
    const int baseSpeed = 60;
    const int maxSpeed = 85;
    int leftSpeed = 0;
    int rightSpeed = 0;
    printStringAndInt("PID: ", pid);

    // turn 90 degrees left
    if (pid >= 25) {
        leftSpeed = -baseSpeed;
        rightSpeed = baseSpeed;
    }
    // turn 90 degrees right
    else if (pid <= -25) {
        leftSpeed = baseSpeed;
        rightSpeed = -baseSpeed;
    } else {
        leftSpeed = baseSpeed - pid;
        rightSpeed = baseSpeed + pid;
    }

    // lots of guards to make sure we don't send too high values to the motor
    if (leftSpeed > maxSpeed) {
        leftSpeed = maxSpeed;
    }
    if (rightSpeed > maxSpeed) {
        rightSpeed = maxSpeed;
    }

    if (leftSpeed < -maxSpeed) {
        leftSpeed = -maxSpeed;
    }
    if (rightSpeed < -maxSpeed) {
        rightSpeed = -maxSpeed;
    }

    printStringAndInt("SpeedR: ", rightSpeed);
    printStringAndInt("SpeedL: ", leftSpeed);
    printStringAndInt("PID: ", pid);
    nxt_motor_set_speed(LEFT_MOTOR, leftSpeed, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, rightSpeed, 1);
}

// Stops the left and right motor
void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
}
