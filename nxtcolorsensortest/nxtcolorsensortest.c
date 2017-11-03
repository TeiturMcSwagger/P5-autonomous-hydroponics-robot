/* nxtcolorsensortest.c */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"

#define PORT_ID NXT_PORT_S1

/* TOPPERS/ATK declarations */
DeclareCounter(SysTimerCnt);
DeclareAlarm(AlarmTask2);
DeclareEvent(EventTask2);

/* nxtOSEK hooks */
void ecrobot_device_initialize(void) {
    ecrobot_init_nxtcolorsensor(PORT_ID,
                                NXT_LIGHTSENSOR_WHITE); // initialize a sensor
}

void ecrobot_device_terminate(void) {
    ecrobot_term_nxtcolorsensor(PORT_ID); // terminate a sensor
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {
    (void)SignalCounter(SysTimerCnt); /* Increment OSEK Alarm Counter */
}

void getLightValue()
{

    while (1) {
    int sum = 0;
        for (int i = 0; i <= 9; i++)
        {
       		WaitEvent(EventTask2);
        	ClearEvent(EventTask2);
        	ecrobot_set_nxtcolorsensor(PORT_ID, NXT_LIGHTSENSOR_WHITE);
        	display_clear(0);
        	display_goto_xy(0, 0);
        	int lightValue = ecrobot_get_nxtcolorsensor_light(PORT_ID);
        	display_int(lightValue, 0);
        	sum += lightValue;
        	display_update();
        }
	  sum = sum / 10;
    display_int(sum, 1);
    display_update();
    }
}

/* Alarm executed Task2 */
TASK(Task2)
{
	getLightValue();
	TerminateTask();
}

/* Background Task */
TASK(Task1) {
    SetRelAlarm(AlarmTask2, 1, 100); // set event for Task2 by Alarm
    while (1) {
        ecrobot_process_bg_nxtcolorsensor(); // communicates with NXT Color
                                             // Sensor (this must be executed
                                             // repeatedly in a background Task)
    }
}
