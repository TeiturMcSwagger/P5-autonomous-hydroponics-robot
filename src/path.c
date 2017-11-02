#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "main.h"

int lightValue;

void scanPath() {
    // lightValue = ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    // display_goto_xy(0, 1);
    // display_string("LIGHT:");
    // display_int(lightValue);
    // display_clear(0);
    while(1) {
        print(0, "hello");
    }
}
