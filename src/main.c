#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#include "motorController.h"
#include "path.h"
#include "feed.h"
#include "types.h"
#include <stdlib.h>

U32 armFireCounter = 0;
U8 feedAmount = 0;

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(SamplePlantColourAlarm);
DeclareAlarm(SamplePathAlarm);
DeclareAlarm(SensorBackgroundAlarm);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
    ecrobot_init_nxtcolorsensor(PLANT_SENSOR_PORT, NXT_COLORSENSOR);
}

void ecrobot_device_terminate() {
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
    ecrobot_term_nxtcolorsensor(PLANT_SENSOR_PORT);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

// Keeps the color sensor alive
// is neccessary or the color sensor won't work
TASK(SensorBackgroundTask) {
    ecrobot_process_bg_nxtcolorsensor();
    TerminateTask();
}

TASK(SamplePlantColourTask) {
    if (systick_get_ms() < armFireCounter + 3000) {
        TerminateTask();
    }

    feedAmount = getFeedAmount();
    if (feedAmount == 0) {
        TerminateTask();
    }

    armFireCounter = systick_get_ms();
    stopDriving();
    feedPills(feedAmount);
    TerminateTask();
}

TASK(SamplePathTask) {
    if (systick_get_ms() < armFireCounter + 500 * feedAmount) {
        TerminateTask();
    }

    followLine();
    TerminateTask();
}

TASK(Calibrate) {
    // hack to fix the feeding not working the first time
    feedPills(1);
    calibrateOptimalLight();
    TerminateTask();
}
