#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "path.h"
#include "globalConstants.h"
#include "types.h"
#include "nxtMotorController.h"
#include <stdlib.h>

#include "util.h"

int lightValue;

bool first = TRUE;

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

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
}
TASK(FeedingTask)
{
    if(first){
        first = FALSE;
        nxt_motor_set_count(NXT_PORT_A, DEFAULT_TURN_POSITION);
    }

    rotateMotorToAngle(100, 0, 15, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 0, 0, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 0, -15, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 0, 15, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 0, 0, NXT_PORT_A, 0);

    TerminateTask();
}
TASK(CalibrateTask)
{

}
TASK(ScanPlantTask)
{
}

TASK(ScanPathTask)
{
    printString("asd");
    systick_wait_ms(1000);   
}

TASK(MotorTask)
{
}

TASK(TurnTask)
{
}
