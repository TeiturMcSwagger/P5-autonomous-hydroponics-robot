#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "types.h"
#include <stdlib.h>

int printRow = 0;

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool isTargetClockwise(U32 startAngle, U32 targetAngle);

void rotateMotor(int speedPercent, int brakeLength, bool turnDirection,
                 U32 motorPort, int allowedDeviation, int targetAngle);

// Util

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

// End of util

void rotateMotorToAngle(int speedPercent, int brakeLength, U32 targetAngle,
                        U32 motorPort, int allowedDeviation) {
  bool turnClockwise =
      isTargetClockwise(nxt_motor_get_count(motorPort), targetAngle);
  rotateMotor(speedPercent, brakeLength, turnClockwise, motorPort,
              allowedDeviation, targetAngle);
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
  if (turnClockwise) {
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

  if (variation == 0) {
    return;
  }
  bool isClockwise =
      isTargetClockwise(nxt_motor_get_count(motorPort), targetAngle);
  printRow = 0;
  rotateMotor(10, 0, isClockwise, motorPort, allowedDeviation, targetAngle);
}

bool isTargetClockwise(U32 startAngle, U32 targetAngle) {
  return startAngle > targetAngle;
}

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
  return startAngle + degreesToRotate;
}