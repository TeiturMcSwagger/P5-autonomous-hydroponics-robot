#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "turn.h"
#include "util.h"
#include "calibrate.h"

int getLightValue() {
    int sum = 0;
    int numLoops = 1;
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}

void scanPath() {
    int v = getLightValue();
    clearScreen();
//    printStringAndInt("Lightvalue: ", v);
}

int getDiviation(){
    int currentValue = getLightValue();
    return (((float)(currentValue) / (float)(optimalLightValue)) * 100) - 100;
}