#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "path.h"

int lightValue;

void printf(int row, char *str, int val)
{
	display_clear(0);
	display_goto_xy(0,row);
	display_string(str);
	display_int(val, 0);
	display_update();

}

void scanPath() 
{
while(1)
	printf(0, "FAGGOT", 0);
    // lightValue = ecrobot_get_nxtcolorsensor_light(PATH_SENSOR_PORT);
    // display_goto_xy(0, 1);
    // display_string("LIGHT:");
    // display_int(lightValue);
    // display_clear(0);
    while(1) {
        print(0, "hello");
    }
}
