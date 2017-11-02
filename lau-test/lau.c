/* helloworld.c for TOPPERS/ATK(OSEK) */
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

#define PATH_SENSOR_PORT NXT_PORT_S1


/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
}

void ecrobot_device_terminate()
{
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){ /* do nothing */ }

void print(int row, char *str, int value) {
    display_clear(0);
    display_goto_xy(0, row);
    display_string(str);
    // display_int();
    display_update();
}

TASK(Scan_Path)
{
	while(1)
	{
        ecrobot_set_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
        display_clear(0);
        display_goto_xy(0,0);
        display_int(ecrobot_get_light_sensor(PATH_SENSOR_PORT),0);
        display_update();
		systick_wait_ms(500);
	}
}
