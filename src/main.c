#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.c"
#include "path.h"
#include "turn.h"
#include <stdlib.h>

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

void printf(int row, char *str, int val) {
    display_clear(0);
    display_goto_xy(0, row);
    display_string(str);
    display_int(val, 0);
    display_update();
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {}
TASK(FeedingTask) {}
TASK(CalibrateTask) {}
TASK(ScanPlantTask) {}
TASK(ScanPlantBackgroundTask) {}

TASK(ScanPathTask) { scanPath(); }

TASK(MotorTask) {}

TASK(TurnTask) {
    turnMe();
    TerminateTask();
}

/* Background Task */
TASK(ScanPathBackgroundTask) {
    SetRelAlarm(AlarmTask2, 1, 100); // set event for Task2 by Alarm
    while (1) {
        ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
                                             // Sensor (this must be executed
                                             // repeatedly in a background Task)
    }
}
