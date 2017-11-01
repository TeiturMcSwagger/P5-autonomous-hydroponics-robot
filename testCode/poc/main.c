/* rms.c */
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

int count = 0;

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

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate)
{
  return startAngle + degreesToRotate;
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

void rotateMotor(int speedPercent, int breakDistance, U32 degreesToRotate, char turnDirection, U32 outputPort)
{
  U32 targetAngle = getDestinationAngle(nxt_motor_get_count(outputPort), degreesToRotate);
  
  if(turnDirection)
  {
    nxt_motor_set_speed(outputPort, speedPercent, 1);
    while(nxt_motor_get_count(outputPort) + breakDistance < targetAngle){}
  }
  else
  {
    nxt_motor_set_speed(outputPort, -speedPercent, 1);
    while(nxt_motor_get_count(outputPort) + breakDistance > targetAngle){}
  }
  
  nxt_motor_set_speed(outputPort, 0, 1);
  systick_wait_ms(150);
  
  U32 variation = targetAngle - nxt_motor_get_count(outputPort);
  
  if(variation == 0)
  {
    return;
  }
  
  char direction = (nxt_motor_get_count(outputPort)>targetAngle) ? 0 : 1;
  
  display_clear(0);
  count++;
  rotateMotor(10, 0, variation, direction, outputPort);
}
TASK(FeedingTask)
{
  while (1)
  {
    rotateMotor(100, 40, 90, 1, NXT_PORT_A);
  }
  TerminateTask();
}
