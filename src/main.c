#include "armController.h"
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
<<<<<<< HEAD
=======
#include "nxtMotorController.h"
>>>>>>> TurnFinsih
#include "path.h"
#include "sym.h"
#include "turn.h"
#include "types.h"
#include "util.h"
#include <stdlib.h>

/* OSEK declarations */
DeclareTask(TurnTask);
DeclareTask(FeedingTask);
DeclareTask(ScanPathTask);
DeclareTask(ScanPlantTask);
DeclareTask(ScanPathBackgroundTask);
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

<<<<<<< HEAD
=======
TASK(FeedingTask) {
    rotateMotorToAngle(100, 40, 15, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 40, 0, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 40, -15, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorToAngle(100, 40, 0, NXT_PORT_A, 0);

    systick_wait_ms(5000);

    rotateMotorByDegrees(100, 40, 180, TRUE, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorByDegrees(100, 40, 180, TRUE, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorByDegrees(100, 40, 180, FALSE, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    rotateMotorByDegrees(100, 40, 180, FALSE, NXT_PORT_A, 0);

    TerminateTask();
}

>>>>>>> TurnFinsih
/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    (void)SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
}

TASK(FeedingTask) {
    int amount = 3;
    nutrition n = {.feedProc = feedPills, .amount = &amount};
    feed(n);
    TerminateTask();
}

TASK(ScanPathTask) {
    while (1) {
        WaitEvent(PathEvent);
        ClearEvent(PathEvent);
        scanPath();
    }
    TerminateTask();
}
TASK(CalibrateTask) {}
TASK(SensorBackgroundTask) {}
TASK(ScanPlantTask) {}
TASK(MotorTask) {}
TASK(TurnTask) {
    printString("gfff");
    turnMe();
    TerminateTask();
}

/* Background Task */
TASK(ScanPathBackgroundTask) {
    // set event
    SetRelAlarm(ScanPathAlarm, 1, 100);
    SetRelAlarm(ScanPlantTask, 1, 100);
    while (1) {
        ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
                                             // Sensor (this must be executed
                                             // repeatedly in a background Task)
    }
}
