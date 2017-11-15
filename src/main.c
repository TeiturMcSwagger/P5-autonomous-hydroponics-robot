#include "calibrate.h"
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include "path.h"
#include "sensorController.h"
#include "sym.h"
#include "turn.h"
#include "types.h"
#include "util.h"
#include <stdlib.h>
#include "armController.h"

/* OSEK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(SamplePlantColourAlarm);
DeclareAlarm(SensorBackgroundAlarm);
DeclareAlarm(ScanPathAlarm);

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
    ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
    ecrobot_init_nxtcolorsensor(PLANT_SENSOR_PORT, NXT_COLORSENSOR);
}

void ecrobot_device_terminate() {
    ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    StatusType ercd;

    ercd = SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
    if (ercd != E_OK) {
        ShutdownOS(ercd);
    }
}

TASK(CalibrateTask) {
    printString("CALIBRATES");
    ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
    getOptimalLightValue();
    TerminateTask();
}
TASK(SensorBackgroundTask) {
    ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
    TerminateTask();
}
TASK(SamplePlantColourTask) {
    printString("Sampling");
    U16 colour = sampleColour(PLANT_SENSOR_PORT);
    U8 amount = getAmountFromSample(colour);

    if (amount != ERROR) {
        stopMotor();
        nutrition n = {.feedProc = feedPills, .amount = &amount};
        feed(n);
    }
    TerminateTask();
}

TASK(ScanPathTask) {
    if(areWeFeeding){
        TerminateTask();
    }
    scanPath();
    drive();
    TerminateTask();
}

TASK(FeedingTask) {
    int amount = 3;
    nutrition n = {.feedProc = feedPills, .amount = &amount};
    feed(n);
    TerminateTask();
}

TASK(MotorTask) {}
TASK(TurnTask) {
    
    TerminateTask();
}
