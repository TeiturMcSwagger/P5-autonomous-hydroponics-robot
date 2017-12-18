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

int sbTaskItr = 0; 
int sbTaskMean = 0; 
int sbTaskWorst = -100; 
 
int spcTaskItr = 0; 
int spcTaskMean = 0; 
int spcTaskWorst = -100; 
 
int spTaskItr = 0; 
int spTaskMean = 0; 
int spTaskWorst = -100; 
 
int calTaskItr = 0; 
int calTaskMean = 0; 
int calTaskWorst = -100; 

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(SamplePlantColourAlarm);
DeclareAlarm(SamplePathAlarm);
DeclareAlarm(SensorBackgroundAlarm);
DeclareResource(ColourSensorResource);
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
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

// Keeps the color sensor alive / samples
// is neccessary or the color sensor won't work
TASK(SensorBackgroundTask) {
    if(sbTaskItr >= 1000 && spcTaskItr >= 1000 && spTaskItr >= 1000) 
    { 
        //int sumWorst = sbTaskWorst + spcTaskWorst + spTaskWorst + calTaskWorst; 
        //int sumMean = sbTaskMean + spcTaskMean + spTaskMean + calTaskMean; 
 
        nxt_motor_set_speed(LEFT_MOTOR, 0, 1); 
        nxt_motor_set_speed(RIGHT_MOTOR, 0, 1); 
 
        display_goto_xy(0, 0);
        display_int(sbTaskWorst, 0);
        display_goto_xy(0, 1);
        display_int(sbTaskMean, 0);
        display_goto_xy(0, 2);
        display_int(spcTaskWorst, 0);
        display_goto_xy(0, 3);
        display_int(spcTaskMean, 0);
        display_goto_xy(0, 4);
        display_int(spTaskWorst, 0);
        display_goto_xy(0, 5);
        display_int(spTaskMean, 0);
        display_goto_xy(0, 6);
        display_int(calTaskWorst, 0);
        display_goto_xy(0, 7);
        display_int(calTaskMean, 0);
        display_update(); 
        systick_wait_ms(100000000); 
    } 
    sbTaskItr++; 
    int startTime = systick_get_ms();

    GetResource(ColourSensorResource);
    ecrobot_process_bg_nxtcolorsensor();
    ReleaseResource(ColourSensorResource);

    int taskTime = systick_get_ms() - startTime; 
    if(taskTime > sbTaskWorst) 
        sbTaskWorst = taskTime; 
    sbTaskMean = (sbTaskMean + taskTime) / sbTaskItr; 

    TerminateTask();
}

TASK(SamplePlantColourTask) {
    spcTaskItr++; 
    int startTime = systick_get_ms(); 
    // delays the scan after feeding
    // so we're not stuck in an infinite feeding loop
    if (systick_get_ms() < armFireCounter + 1200 * feedAmount) {
        int taskTime = systick_get_ms() - startTime; 
        if(taskTime > spcTaskWorst) 
            spcTaskWorst = taskTime; 
        spcTaskMean = (spcTaskMean + taskTime) / spcTaskItr; 

        TerminateTask();
    }

    GetResource(ColourSensorResource);
    feedAmount = getFeedAmount();
    ReleaseResource(ColourSensorResource);

    if (feedAmount == 0) {
        int taskTime = systick_get_ms() - startTime; 
        if(taskTime > spcTaskWorst) 
            spcTaskWorst = taskTime; 
        spcTaskMean = (spcTaskMean + taskTime) / spcTaskItr; 

        TerminateTask();
    }

    SetEvent(FeedingTask, FeedEvent);
    
    int taskTime = systick_get_ms() - startTime; 
        if(taskTime > spcTaskWorst) 
            spcTaskWorst = taskTime; 
    spcTaskMean = (spcTaskMean + taskTime) / spcTaskItr; 

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

TASK(SamplePathTask) {
    spTaskItr++; 
    int startTime = systick_get_ms(); 

    followLine();

    int taskTime = systick_get_ms() - startTime; 
    if(taskTime > spTaskWorst) 
        spTaskWorst = taskTime; 
    spTaskMean = (spTaskMean + taskTime) / spTaskItr; 

    TerminateTask();
}

TASK(Calibrate) {
    calTaskItr++; 
    int startTime = systick_get_ms(); 

    calibrateOptimalLight();

    int taskTime = systick_get_ms() - startTime; 
    if(taskTime > calTaskWorst) 
        calTaskWorst = taskTime; 
    calTaskMean = (calTaskMean + taskTime) / calTaskItr; 

    TerminateTask();
}
