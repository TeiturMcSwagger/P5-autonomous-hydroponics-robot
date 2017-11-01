/* rms.c */
#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

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
U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate){
  return startAngle + degreesToRotate;
}
void printS(char* str, int val, int row){
  display_goto_xy(0, row);
  display_string(str);
  display_int(val, 0);
  display_update();
}
void rotateMotor(int speedPercent, U32 degreesToRotate, char turnDirection, U32 outputPort){
  printS("@rotateMotor ", nxt_motor_get_count(outputPort),0);
  U32 targetAngle = getDestinationAngle(nxt_motor_get_count(outputPort), degreesToRotate);
  if(turnDirection)
  {
    printS("if true", 42, 1);
    nxt_motor_set_speed(outputPort, speedPercent, 1);
  }
  else
  {
    printS("if false", 42, 1);
    nxt_motor_set_speed(outputPort, -speedPercent, 1);
  }
  while(nxt_motor_get_count(outputPort) + 40 < targetAngle){}
  nxt_motor_set_speed(outputPort, 0, 1);
  systick_wait_ms(150);
    printS("foerif", 42, 2);
  if(nxt_motor_get_count(outputPort)-targetAngle == 0){
    return;
  }
    printS("underif", 42, 3);


  U32 variation = (nxt_motor_get_count(outputPort) > targetAngle)
  ? nxt_motor_get_count(outputPort) - targetAngle
  : targetAngle-nxt_motor_get_count(outputPort);
  printS("VARIATION ", variation, 4);
  printS("target ", targetAngle, 5);
  printS("current ", nxt_motor_get_count(outputPort), 6);
  char direction = (nxt_motor_get_count(outputPort)>targetAngle) ? 0 : 1;
  printS("DIRECTION ", direction, 7);

  //printS("getCount: ", nxt_motor_get_count(NXT_PORT_A),row);
  //printS("target: ", targetDegrees,++row);
  systick_wait_ms(1000);
  display_clear(0);
  //rotateMotor(10, 20, direction, outputPort);
}
TASK(FeedingTask){
  while (1) {
    rotateMotor(1, 20, 1, NXT_PORT_A);
    systick_wait_ms(5000);
  }
  TerminateTask();
}
