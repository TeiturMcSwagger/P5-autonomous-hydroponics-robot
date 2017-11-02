#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "types.h"
#include <stdlib.h>

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool rotateClockwiseToTarget(U32 startAngle, U32 targetAngle);
/*  */
void rotateMotorToAngle(int speedPercent, int brakeLength, U32 targetAngle,
                        U32 motorPort, int allowedDeviation) {

  rotateMotor(
      speedPercent, brakeLength,
      rotateClockwiseToTarget(nxt_motor_get_count(motorPort), targetAngle),
      motorPort allowedDeviation, targetAngle);
}

/*  */
void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool turnDirection,
                          U32 motorPort, int allowedDeviation) {
  U32 targetAngle =
      getDestinationAngle(nxt_motor_get_count(motorPort), degreesToRotate);
  rotateMotor(speedPercent, brakeLength, turnDirection, motorPort,
              allowedDeviation, targetAngle);
}

/*  */
void rotateMotor(int speedPercent, int brakeLength, bool turnDirection,
                 U32 motorPort, int allowedDeviation, int targetAngle) {
  if (turnDirection) {
    nxt_motor_set_speed(motorPort, speedPercent, 1);
    while (nxt_motor_get_count(motorPort) + brakeLength < targetAngle)
      ;

  } else {
    nxt_motor_set_speed(motorPort, -speedPercent, 1);
    while (nxt_motor_get_count(motorPort) + brakeLength > targetAngle)
      ;
  }

  nxt_motor_set_speed(motorPort, 0, 1);
  systick_wait_ms(150);

  U32 variation = targetAngle - nxt_motor_get_count(motorPort);

  if (variation >= -allowedDeviation && variation <= allowedDeviation) {
    return;
  }
  bool direction =
      rotateClockwiseToTarget(nxt_motor_get_count(motorPort), targetAngle);
  rotateMotor(10, 0, variation, direction, motorPort, allowedDeviation);
}

/*  */
bool rotateClockwiseToTarget(U32 startAngle, U32 targetAngle) {
  return (startAngle > targetAngle) ? 0 : 1;
}

/*  */
U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
  return startAngle + degreesToRotate;
}
