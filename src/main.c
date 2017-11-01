#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "path.h"

#define PATH_SENSOR_PORT NXT_PORT_S2

int lightValue;

/* OSEK declarations */
// DeclareTask(ScanPathTask);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize()
{
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
}

void ecrobot_device_terminate()
{
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
}

TASK(FeedingTask){
}
TASK(CalibrateTask){

}
TASK(ScanPlantTask){
}

TASK(ScanPathTask)
{
    scanPath();
}

TASK(MotorTask){
}

TASK(TurnTask){
}
