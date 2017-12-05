#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "ecrobot_interface.h"
#include "sys_defs.h"
#include "types.h"

void rotateMotorByDegrees(int speedPercent, U32 degreesToRotate, bool clockwise,
                          U32 motorPort);
#endif
