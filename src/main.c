#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

/* OSEK declarations */

/* LEJOS OSEK hooks */
// void ecrobot_device_initialize()
// {
// }

/*void ecrobot_device_terminate()
{
}*/

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
TASK(ScanPathTask){
}
TASK(MotorTask){
}
TASK(TurnTask){
}
