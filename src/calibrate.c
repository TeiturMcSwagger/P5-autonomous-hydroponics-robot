#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"

int translationfactor;
int optimalLightValue;

void getOptimalLightValue() {
    int sum = 0;
    int numLoops = 100;
    for (int i = 0; i < numLoops; i++) {
        sum += ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    }
    optimalLightValue = sum / numLoops;  
}

void scanPathToCalibrate() {
    translationfactor = MAX_STEERING_ANGLE / optimalLightValue;
    clearScreen();
    // turnMe(v);
}
