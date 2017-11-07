#ifndef NXTMOTORCONTROLLER_H
#define NXTMOTORCONTROLLER_H

#include "ecrobot_interface.h"
#include "sys_defs.h"
#include "types.h"

void rotateMotorToAngle(int speedPercent, int brakeLength, int targetAngle,
                        U32 motorPort, int allowedDeviation);

void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool clockwise, U32 motorPort,
                          int allowedDeviation);
#endif