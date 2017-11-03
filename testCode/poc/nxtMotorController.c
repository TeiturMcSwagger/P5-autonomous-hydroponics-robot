#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "types.h"
#include <stdlib.h>

int printRow = 0;

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool rotateClockwiseToTarget(U32 startAngle, U32 targetAngle);

void rotateMotor(int speedPercent, int brakeLength, bool turnDirection,
                 U32 motorPort, int allowedDeviation, int targetAngle);

                 //Util
                 
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
                 
                 //End of util
                 
                 /*  */
void rotateMotorToAngle(int speedPercent, int brakeLength, U32 targetAngle,
                        U32 motorPort, int allowedDeviation) {
                            printString("@ RotateMotorToAngle", printRow++);

  rotateMotor(
      speedPercent, brakeLength,
      rotateClockwiseToTarget(nxt_motor_get_count(motorPort), targetAngle),
      motorPort, allowedDeviation, targetAngle);
}

/*  */
void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool turnDirection,
                          U32 motorPort, int allowedDeviation) {
                              printString("@ rotateMotorByDegrees", printRow++);
  U32 targetAngle =
      getDestinationAngle(nxt_motor_get_count(motorPort), degreesToRotate);
  rotateMotor(speedPercent, brakeLength, turnDirection, motorPort,
              allowedDeviation, targetAngle);
}

/*  */
void rotateMotor(int speedPercent, int brakeLength, bool turnDirection,
                 U32 motorPort, int allowedDeviation, int targetAngle) {
                     printString("@ rotateMotor", printRow++);
  if (turnDirection) {
      printString("If true", printRow++);
    nxt_motor_set_speed(motorPort, speedPercent, 1);
    while (nxt_motor_get_count(motorPort) + brakeLength < targetAngle)
      ;

  } else {
      printString("If false", printRow++);
    nxt_motor_set_speed(motorPort, -speedPercent, 1);
    while (nxt_motor_get_count(motorPort) + brakeLength > targetAngle)
      ;
  }

  nxt_motor_set_speed(motorPort, 0, 1);
  systick_wait_ms(150);

  U32 variation = targetAngle - nxt_motor_get_count(motorPort);

  printStringAndInt("Variation: ", variation, printRow++);
  
  //if (variation >= -allowedDeviation && variation <= allowedDeviation) {
    if(variation == 0){
      printString("Return..", printRow++);
    return;
  }
  bool direction =
      rotateClockwiseToTarget(nxt_motor_get_count(motorPort), targetAngle);
      printString("Adjusting..", printRow++);
      systick_wait_ms(3000);
      display_clear(0);
      printRow = 0;
  rotateMotor(10, 0, variation, direction, motorPort, allowedDeviation);
}

/*  */
bool rotateClockwiseToTarget(U32 startAngle, U32 targetAngle) {
    printString("@ rotateClockwiseToTarget", printRow++);
  return (startAngle > targetAngle) ? 0 : 1;
}

/*  */
U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
    printString("@ getDestinationAngle", printRow++);
  return startAngle + degreesToRotate;
}
