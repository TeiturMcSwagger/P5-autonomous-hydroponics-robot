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

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    StatusType ercd;

    /*
     *  Increment OSEK Alarm System Timer Count
     */
    ercd = SignalCounter(SysTimerCnt);
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

void print(int row, char *str) {
    display_clear(0);
    display_goto_xy(0, row);
    display_string(str);
    display_update();
}

TASK(FeedingTask) {}
TASK(CalibrateTask) {}
TASK(ScanPlantTask) {}

TASK(ScanPathTask) { scanPath(); }

TASK(MotorTask) {}

TASK(TurnTask) {}
