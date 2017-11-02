#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "path.h"
#include <stdlib.h>

#define PATH_SENSOR_PORT NXT_PORT_S2

int lightValue;

/* OSEK declarations */
DeclareTask(ScanPathTask);
DeclareCounter(SysTimerCnt);
DeclareAlarm(ScanPathAlarm);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
}

void ecrobot_device_terminate() {
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

void printf(int row, char *str, int val)
{
        display_clear(0);
        display_goto_xy(0,row);
        display_string(str);
        display_int(val, 0);
        display_update();

}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
}
TASK(FeedingTask)
{
}
TASK(CalibrateTask)
{

}
TASK(ScanPlantTask)
{
}

TASK(ScanPathTask)
{
    printf(0, "asd", 0);
    systick_wait_ms(1000);   
}

TASK(MotorTask)
{
}

TASK(TurnTask)
{
}
