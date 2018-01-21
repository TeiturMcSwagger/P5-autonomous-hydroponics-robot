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
U8 feedAmount = 0;

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(SamplePlantAlarm);
DeclareAlarm(SamplePathAlarm);
DeclareAlarm(ColourSensorBGAlarm);
DeclareResource(SensorBuffer);
DeclareEvent(FeedEvent);
DeclareTask(FeedingTask);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
    ecrobot_init_nxtcolorsensor(PLANT_SENSOR_PORT, NXT_COLORSENSOR);
}

void ecrobot_device_terminate() {
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
    ecrobot_term_nxtcolorsensor(PLANT_SENSOR_PORT);
    nxt_motor_set_speed(LEFT_MOTOR, 0, 1);
    nxt_motor_set_speed(RIGHT_MOTOR, 0, 1);
    nxt_motor_set_speed(ARM_MOTOR_PORT, 0, 1);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    StatusType ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

// Keeps the color sensor alive / samples
// is neccessary or the color sensor won't work
TASK(ColourSensorBG) {
    GetResource(SensorBuffer);
    ecrobot_process_bg_nxtcolorsensor();
    ReleaseResource(SensorBuffer);

    TerminateTask();
}

TASK(SamplePlant) {
    // delays the scan after feeding
    // so we're not stuck in an infinite feeding loop
    if (systick_get_ms() < armFireCounter + 1200 * feedAmount) {
        TerminateTask();
    }

    GetResource(SensorBuffer);
    feedAmount = getFeedAmount();
    ReleaseResource(SensorBuffer);

    if (feedAmount == 0) {
        TerminateTask();
    }

    SetEvent(FeedingTask, FeedEvent);

    TerminateTask();
}

TASK(FeedingTask){
    while(1)
    {
        WaitEvent(FeedEvent); /* Task is in waiting status until the Event comes */ 
        ClearEvent(FeedEvent);

        armFireCounter = systick_get_ms();
        stopDriving();
        feedPills(feedAmount);
    }
    TerminateTask();
}

TASK(SamplePath) {
    GetResource(SensorBuffer);
    followLine();
    ReleaseResource(SensorBuffer);

    TerminateTask();
}

TASK(Calibrate) {
    calibrateOptimalLight();

    TerminateTask();
}
