#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "util.h"
#include "motorController.h"
#include "calibrate.h"
#include "path.h"
#include "feed.h"
#include "types.h"
#include <stdlib.h>

U32 armFireCounter = 0;
// shared resource
bool isFeeding = FALSE;

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(SamplePlantColourAlarm);
DeclareAlarm(SamplePathAlarm);
DeclareAlarm(SensorBackgroundAlarm);
DeclareResource(FeedingResource);


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

// Keeps the color sensor alive / samples
// is neccessary or the color sensor won't work
TASK(SensorBackgroundTask) {
    ecrobot_process_bg_nxtcolorsensor();
    TerminateTask();
}

TASK(SamplePlantColourTask) {
    // delays the scan after feeding
    // so we're not stuck in an infinite feeding loop
    if (systick_get_ms() < armFireCounter + 3000) {
        TerminateTask();
    }

    U8 feedAmount = getFeedAmount();
    if (feedAmount == 0) {
        TerminateTask();
    }
    GetResource(FeedingResource);
    isFeeding = TRUE;
    armFireCounter = systick_get_ms();
    stopDriving();
    feedPills(feedAmount);
    // wait a bit for the ball to fall into the plant
    systick_wait_ms(500);
    isFeeding = FALSE;
    ReleaseResource(FeedingResource);
    TerminateTask();
}

TASK(SamplePathTask) {
    GetResource(FeedingResource);
    if(isFeeding == TRUE) {
        ReleaseResource(FeedingResource);
        TerminateTask();
    }
    ReleaseResource(FeedingResource);
    followLine();
    TerminateTask();
}

TASK(Calibrate) {
    calibrateOptimalLight();
    TerminateTask();
}
