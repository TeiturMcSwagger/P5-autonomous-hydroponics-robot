#include "ecrobot_interface.h"
#include "globalConstants.h"
#include "kernel.h"
#include "kernel_id.h"

int getLightValue() {
    int sum = 0;
    int numLoops = 10;
    for (int i = 0; i < numLoops; i++) {
        WaitEvent(EventTask2);
        ClearEvent(EventTask2);
        sum += ecrobot_get_nxtcolorsensor_light(PORT_ID);
    }
    sum = sum / numLoops;

    display_clear(0);
    display_goto_xy(0, 0);
    display_string("LightValue: ");
    display_int(sum, 1);
    display_update();
    // for testing purposes
    ecrobot_get_systick_ms(1000);
}

void scanPath() {
    while (1) {
        getLightValue();
        TerminateTask();
    }
}
