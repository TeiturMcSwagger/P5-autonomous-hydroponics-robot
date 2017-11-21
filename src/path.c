#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#define PROPORTIONAL 0.2
#define INTEGRAL 0.1
#define DERIVATIVE 0.4

int getLight();
int getAverageLightValue(int numLoops);
void turn(double pid);

double integral = 0;
int previousError = 0;

// Assumes to robot is placed on the right side of the tape
void followLine() {
    int error = getLight() - OPTIMAL_LIGHT;
    double proportional = error * PROPORTIONAL;
    integral = integral + error;
    // double integ = integral * INTEGRAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pid = proportional + derivative;
    previousError = error;
    turn(pid);
}

void turn(double pid) {
    printStringAndInt("PID: ", pid);

    const int baseSpeed = 20;
    const int maxSpeed = 50;

    int leftSpeed = baseSpeed + pid;
    int rightSpeed = baseSpeed - pid;

    if(leftSpeed > maxSpeed) {
        leftSpeed = maxSpeed;
    }
    if(rightSpeed > maxSpeed) {
        rightSpeed = maxSpeed;
    }

    if(leftSpeed < -maxSpeed) {
        leftSpeed = -maxSpeed;
    }
    if(rightSpeed < -maxSpeed) {
        rightSpeed = -maxSpeed;
    }

    nxt_motor_set_speed(LEFT_MOTOR, leftSpeed, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, rightSpeed, 1);
}

void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
}

int getLight() {
    return getAverageLightValue(3);
}

// Returns the average light value based on a number of readings, because the sensor is not reliable
int getAverageLightValue(int numLoops) {
    int sum = 0;
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}

