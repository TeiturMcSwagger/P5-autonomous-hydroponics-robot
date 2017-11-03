#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "types.h"
#include "globalConstants.h"
#include <stdlib.h>

#include "util.h"

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool isTargetClockwise(U32 startAngle, U32 targetAngle);

void rotateMotor(int speedPercent, int brakeLength, bool turnDirection,
                 U32 motorPort, int allowedDeviation, int targetAngle);

void rotateMotorToAngle(int speedPercent, int brakeLength, int targetAngle, U32 motorPort, int allowedDeviation) {
    display_clear(0);
    printStringAndInt("Motor Count; ", nxt_motor_get_count(motorPort)); 
  U32 actualTargetAngle = DEFAULT_TURN_POSITION + targetAngle;
  bool turnClockwise =
      isTargetClockwise(nxt_motor_get_count(motorPort), actualTargetAngle);
  rotateMotor(speedPercent, brakeLength, turnClockwise, motorPort,
              allowedDeviation, actualTargetAngle);
}

void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool turnDirection,
                          U32 motorPort, int allowedDeviation) {
  U32 targetAngle =
      getDestinationAngle(nxt_motor_get_count(motorPort), degreesToRotate);
  rotateMotor(speedPercent, brakeLength, turnDirection, motorPort,
              allowedDeviation, targetAngle);
}

void rotateMotor(int speedPercent, int brakeLength, bool turnClockwise,
                 U32 motorPort, int allowedDeviation, int targetAngle) {
  printString("@ rotateMotor");
  if (turnClockwise) {
    printString("true");
    nxt_motor_set_speed(motorPort, speedPercent, 1);
    while (nxt_motor_get_count(motorPort) + brakeLength < targetAngle);

  } else {
    printString("false");
    nxt_motor_set_speed(motorPort, -speedPercent, 1);
    printStringAndInt("Start: ", nxt_motor_get_count(motorPort) + brakeLength);
    printStringAndInt("Target: ", targetAngle);
    while (nxt_motor_get_count(motorPort) + brakeLength > targetAngle);
  }

  nxt_motor_set_speed(motorPort, 0, 1);
  systick_wait_ms(150);

  U32 variation = targetAngle - nxt_motor_get_count(motorPort);

  printStringAndInt("Variation: ", variation);

  if (variation == 0) {
    return;
  }
  
  printString("Adjusting..");

  systick_wait_ms(2000);
  display_clear(0);
  displayCount = 0;
  
  bool isClockwise =
      isTargetClockwise(nxt_motor_get_count(motorPort), targetAngle);
  rotateMotor(10, 0, isClockwise, motorPort, allowedDeviation, targetAngle);
}

bool isTargetClockwise(U32 startAngle, U32 targetAngle) {
  return startAngle > targetAngle;
}

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
  return startAngle + degreesToRotate;
}
