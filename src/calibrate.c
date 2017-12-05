#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"

int optimalLight;

void calibrateOptimalLight() {
    int speedPercent = 20;
    // Calibrate Left
    nxt_motor_set_speed(LEFT_MOTOR, -speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
    // the light sensor returns a result between 0-1023
    int minLight = 1024;
    for (int i = 0; i < 100; i++) {
        systick_wait_ms(CALIBRATE_MS / 100);
        int lightIntensity = getLight();
        if (lightIntensity < minLight) {
            minLight = lightIntensity;
        }
    }
    stopDriving();

    // Reset Heading
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, -speedPercent, 1);
    systick_wait_ms(CALIBRATE_MS);
    stopDriving();

    // Calibrate Right
    nxt_motor_set_speed(LEFT_MOTOR, speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, -speedPercent, 1);
    // the light sensor returns a result between 0-1023
    int maxLight = -1;
    for (int i = 0; i < 100; i++) {
        systick_wait_ms(CALIBRATE_MS / 100);
        int lightIntensity = getLight();
        if (lightIntensity > maxLight) {
            maxLight = lightIntensity;
        }
    }
    stopDriving();

    // Reset Heading
    nxt_motor_set_speed(LEFT_MOTOR, -speedPercent, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, speedPercent, 1);
    systick_wait_ms(CALIBRATE_MS);
    stopDriving();
    optimalLight = maxLight - minLight;
}
