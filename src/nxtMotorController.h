#ifndef NXTMOTORCONTROLLER_H
#define NXTMOTORCONTROLLER_H

#include "ecrobot_interface.h"
#include "sys_defs.h"
#include "types.h"

void rotateMotorToAngle(int speedPercent, int targetAngle, U32 motorPort);

void rotateMotorByDegrees(int speedPercent, U32 degreesToRotate, bool clockwise,
                          U32 motorPort);
#endif