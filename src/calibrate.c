#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"

int translationfactor;


int getOptimalLightValue() {
    int sum = 0;
    int numLoops = 100;
    printString("getlight");
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    return sum / numLoops;
}

void scanPathToCalibrate() {
    int optimalLightValue = getOptimalLightValue();
    translationfactor = MAX_STEERING_ANGLE / optimalLightValue;
    clearScreen();
    printString("Calib. Lightvalue: ");
    printInt(optimalLightValue);
    // turnMe(v);
}
