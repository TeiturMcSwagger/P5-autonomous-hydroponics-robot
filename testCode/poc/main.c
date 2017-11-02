/* rms.c */
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "nxtMotorController.h"

/* OSEK declarations */

/* LEJOS OSEK hooks */
// void ecrobot_device_initialize()
// {
// }

/*void ecrobot_device_terminate()
{
}*/

/* LEJOS OSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void)
{
}

void printString(char* str, int row)
{
  display_goto_xy(0, row);
  display_string(str);
  display_update();
}

void printStringAndInt(char* str, int val, int row)
{
  display_goto_xy(0, row);
  display_string(str);
  display_int(val, 0);
  display_update();
}

TASK(FeedingTask)
{
  while (1)
  {
    rotateMotor(100, 40, 90, 1, NXT_PORT_A);
  }
  TerminateTask();
}
