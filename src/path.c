#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"

int getPathLight();
void turn(double pid);

DeclareResource(ColourSensorResource);

// used for derivative
int previousError = 0;

// Assumes the robot is placed on the right side of the tape
void followLine() {
    int error = getPathLight() - optimalLight;
    double proportional = error * PROPORTIONAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pd = proportional + derivative;
    if (pd < 0) {
        // multiply by a constant to make SARAH turn more right
        // because the robot struggles with right turns
        pd = pd * 1.4;
    }
    previousError = error;
    turn(pd);
}

// Returns the light intensity of the path
int getPathLight() {
    GetResource(ColourSensorResource);
    int lightValue = ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    ReleaseResource(ColourSensorResource);
    return lightValue;
}

// Assumes the robot is placed on the right side of the tape
// Translates the pd input to two outputs for the left and right motor
void turn(double pd) {
    const int baseSpeed = 60;
    const int maxSpeed = 85;
    int leftSpeed = 0;
    int rightSpeed = 0;

    // turn 90 degrees left
    if (pd >= 25) {
        leftSpeed = -baseSpeed;
        rightSpeed = baseSpeed;
    }
    // turn 90 degrees right
    else if (pd <= -25) {
        leftSpeed = baseSpeed;
        rightSpeed = -baseSpeed;
    } else {
        leftSpeed = baseSpeed - pd;
        rightSpeed = baseSpeed + pd;
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

    nxt_motor_set_speed(LEFT_MOTOR, leftSpeed, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, rightSpeed, 1);
}

// Stops the left and right motor
void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
}
