#include "globalConstants.h"
#include "kernel.h"
#include "kernel_id.h"

int lightValue = 0;

int getLightValue() {
    int sum = 0;
    int numLoops = 5;
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}

void scanPath() {
    lightValue = getLightValue();
    display_clear(0);
    display_goto_xy(0, 0);
    display_int(lightValue, 0);
    display_update();
}