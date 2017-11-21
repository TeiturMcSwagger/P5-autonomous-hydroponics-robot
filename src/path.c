#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#define PROPORTIONAL 0.5
#define INTEGRAL 0.3
#define DERIVATIVE 0.2

int getLight();
int getAverageLightValue(int numLoops);

double integral = 0;
int previousError = 0;

// Assumes to robot is placed on the right side of the tape
void followLine() {
    int error = getLight() - OPTIMAL_LIGHT;
    double proportional = error * PROPORTIONAL;
    integral = integral + error;
    double integ = integral * INTEGRAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pid = proportional + integ + derivative;
    previousError = error;
    turn(pid);
}

void stopDriving() {
    int speedPercent = 0;
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
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

