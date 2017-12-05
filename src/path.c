#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"

int getLight();
int getAverageLightValue(int numLoops);
void turn(double pid);

// used for integral
int errorSum = 0;
// used for derivative
int previousError = 0;

// Assumes the robot is placed on the right side of the tape
void followLine() {
    int error = getLight() - optimalLight;
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

// Assumes the robot is placed on the right side of the tape
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

void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
}

int getLight() { return getAverageLightValue(3); }

// Returns the average light value based on a number of readings, because the
// sensor is not reliable
// Since we figured out the background task samples the sensors, this function
// is probably unnecessary
int getAverageLightValue(int numLoops) {
    int sum = 0;
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}
