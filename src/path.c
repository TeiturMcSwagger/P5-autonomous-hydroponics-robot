#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "turn.h"
#include "util.h"

int lightValue = 0;

int getLightValue() {
    int sum = 0;
    int numLoops = 5;
    printString("getlight");
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}

void scanPath() {
    int v = getLightValue();
    clearScreen();
    printString("Lightvalue: ");
    printInt(v);
    turnMe(v);
}