#include "ecrobot_interface.h"
#include "globalConstants.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.c"
#include "path.h"
#include "turn.h"
#include <stdlib.h>

/* OSEK declarations */
DeclareTask(ScanPathTask);
// DeclareTask(ScanPlantTask);
DeclareCounter(SysTimerCnt);
DeclareAlarm(ScanPathAlarm);
DeclareEvent(PathEvent);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
}

void ecrobot_device_terminate() {
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

void printf(int row, char *str, int val) {
    display_clear(0);
    display_goto_xy(0, row);
    display_string(str);
    display_int(val, 0);
    display_update();
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    (void)SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
}

TASK(ScanPathTask) {
    while (1) {
        WaitEvent(PathEvent);
        ClearEvent(PathEvent);
        scanPath();
    }
    TerminateTask();
}

TASK(TurnTask) {
    while (1) {
        turnMe();
    }
    TerminateTask();
}

/* Background Task */
TASK(ScanPathBackgroundTask) {
    // set event
    SetRelAlarm(ScanPathAlarm, 1, 100);
    // SetRelAlarm(ScanPlantTask, 1, 100);
    while (1) {
        ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
                                             // Sensor (this must be executed
                                             // repeatedly in a background Task)
    }
}
