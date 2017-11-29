#ifndef SYM_H
#define SYM_H

#define ARM_MOTOR_PORT NXT_PORT_S3
#define PATH_SENSOR_PORT NXT_PORT_S1
#define PLANT_SENSOR_PORT NXT_PORT_S2
#define LEFT_MOTOR NXT_PORT_B
#define RIGHT_MOTOR NXT_PORT_A

#define RED_AMOUNT 1
#define GREEN_AMOUNT 2
#define BLUE_AMOUNT 3

#define MAX_SPEED_BRAKE_LENGTH 40
#define MAX_STEERING_ANGLE 40
#define DEFAULT_TURN_POSITION 180

//PID
#define CALIBRATE_MS 250
#define PROPORTIONAL 0.1
#define DERIVATIVE 0.22

#endif
