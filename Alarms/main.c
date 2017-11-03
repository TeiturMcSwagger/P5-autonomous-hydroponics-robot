/* rms.c */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include <stdlib.h>

DeclareCounter(SysTimerCnt);

int displayCount = 0;

void printString(char *str, int row);

/* OSEK declarations */

/* LEJOS OSEK hooks */
/*
void ecrobot_device_initialize()
{
  printString("Initialize", displayCount++);
}

void ecrobot_device_terminate()
{
  printString("Terminating..", displayCount++);
}
*/

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void){
  StatusType ercd;

/*
 *  Increment OSEK Alarm System Timer Count
 */
  ercd = SignalCounter( SysTimerCnt );
  if( ercd != E_OK ){
    ShutdownOS( ercd );
  }
}

void printString(char *str, int row) {
  display_goto_xy(0, row);
  display_string(str);
  display_update();
}

TASK(AlarmTask) {
  printString("Hello World", displayCount++);

  TerminateTask();
}
