#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"

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
    clearScreen();
    printInt(lightValue);
}