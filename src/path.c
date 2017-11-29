#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#include "types.h"

int getLight();
int getAverageLightValue(int numLoops);
void turn(double pid);

double integral = 0;
int previousError = 0, maxLight = 0, minLight = 0, optimalLight = 0;
bool skip = FALSE;

// Assumes the robot is placed on the right side of the tape
void followLine() {
    int error = getLight() - optimalLight;
    double proportional = error * PROPORTIONAL;
    double derivative = (error - previousError) * DERIVATIVE;
    double pid = proportional + derivative;
    previousError = error;
    turn(pid);
}

void calibratePID()
{
    systick_wait_ms(1000);

    //Calibrate Right
    nxt_motor_set_speed(LEFT_MOTOR, -20, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 20, 1);
    systick_wait_ms(CALIBRATE_MS);
    nxt_motor_set_speed(LEFT_MOTOR, 0, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 0, 1);
    systick_wait_ms(1000);
    minLight = getLight();

    //Calibrate Left
    nxt_motor_set_speed(LEFT_MOTOR, 20, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, -20, 1);
    systick_wait_ms(CALIBRATE_MS * 2);
    nxt_motor_set_speed(LEFT_MOTOR, 0, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 0, 1);
    systick_wait_ms(1000);
    maxLight = getLight();
    
    //Reset Heading
    nxt_motor_set_speed(LEFT_MOTOR, -20, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 20, 1);
    systick_wait_ms(CALIBRATE_MS);
    nxt_motor_set_speed(LEFT_MOTOR, 0, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 0, 1);

    optimalLight = maxLight - minLight;
}

void turn(double pid) {
    clearScreen();
    const int rightBaseSpeed = 60;
    const int leftBaseSpeed = 65;
    const int maxSpeed = 100;
    int leftSpeed = 0;
    int rightSpeed = 0;
    printStringAndInt("PID: ", pid);

    if(pid >= 20)
    {
        leftSpeed = -leftBaseSpeed;
        rightSpeed = rightBaseSpeed;
    }
    else if(pid <= -18)
    {
        leftSpeed = leftBaseSpeed;
        rightSpeed = -rightBaseSpeed;
    }
    else
    {
        leftSpeed = rightBaseSpeed - pid;
        if(pid < -10) {
            leftSpeed += 10;
        }
        rightSpeed = rightBaseSpeed + pid;
    }

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

    printStringAndInt("SpeedR: ", rightSpeed);
    printStringAndInt("SpeedL: ", leftSpeed);
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