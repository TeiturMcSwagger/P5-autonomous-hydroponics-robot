#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"
#include "path.h"
#include "calibrate.h"

#define CALIBRATE_MS 1000
#define CALIBRATE_SPEED 20

int optimalLight;

void calibrateOptimalLight() {
    // Calibrate Left
    nxt_motor_set_speed(LEFT_MOTOR, -CALIBRATE_SPEED, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, CALIBRATE_SPEED, 1);
    // the light sensor returns a result between 0-1023
    int minLight = 1024;
    for (int i = 0; i < 100; i++) {
        systick_wait_ms(CALIBRATE_MS / 100);
        int lightIntensity = getPathLight();
        if (lightIntensity < minLight) {
            minLight = lightIntensity;
        }
    }
    stopDriving();

    // Reset Heading
    nxt_motor_set_speed(LEFT_MOTOR, CALIBRATE_SPEED, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, -CALIBRATE_SPEED, 1);
    systick_wait_ms(CALIBRATE_MS);
    stopDriving();

    // Calibrate Right
    nxt_motor_set_speed(LEFT_MOTOR, CALIBRATE_SPEED, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, -CALIBRATE_SPEED, 1);
    // the light sensor returns a result between 0-1023
    int maxLight = -1;
    for (int i = 0; i < 100; i++) {
        systick_wait_ms(CALIBRATE_MS / 100);
        int lightIntensity = getPathLight();
        if (lightIntensity > maxLight) {
            maxLight = lightIntensity;
        }
    }
    stopDriving();

    // Reset Heading
    nxt_motor_set_speed(LEFT_MOTOR, -CALIBRATE_SPEED, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, CALIBRATE_SPEED, 1);
    systick_wait_ms(CALIBRATE_MS);
    stopDriving();
    optimalLight = maxLight - minLight;
}
