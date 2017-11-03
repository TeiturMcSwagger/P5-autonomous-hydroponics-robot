/* rms.c */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include <stdlib.h>

/* OSEK declarations */

/* LEJOS OSEK hooks */
// void ecrobot_device_initialize()
// {
// }

/*void ecrobot_device_terminate()
{
}*/

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) {}

void printString(char *str, int row) {
  display_goto_xy(0, row);
  display_string(str);
  display_update();
}

void printStringAndInt(char *str, int val, int row) {
  display_goto_xy(0, row);
  display_string(str);
  display_int(val, 0);
  display_update();
}

TASK(FeedingTask) {
  //nxt_motor_set_count(NXT_PORT_A, 180);
  
  while (1) {
    rotateMotorByDegrees(100, 40, 90, 1, NXT_PORT_B, 0);
    
    //rotateMotorToAngle(100, 0, 210, NXT_PORT_A, 0);
    systick_wait_ms(1000);
    //rotateMotorToAngle(100, 0, 180, NXT_PORT_A, 0);
  }
  TerminateTask();
}
