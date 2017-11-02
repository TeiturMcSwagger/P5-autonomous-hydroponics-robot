#include <stdlib.h>
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);

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
  rotateMotor(10, 0, variation, direction, outputPort);
}

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate)
{
  return startAngle + degreesToRotate;
}
