#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include <stdlib.h>

bool first = TRUE;

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool isTargetClockwise(U32 startAngle, U32 targetAngle);
void rotateMotor(int speedPercent, int brakeLength, bool clockwise,
                 U32 motorPort, int allowedDeviation, int targetAngle);

void rotateMotorToAngle(int speedPercent, int brakeLength, int targetAngle,
                        U32 motorPort, int allowedDeviation) {
    if (first) {
        first = FALSE;
        nxt_motor_set_count(NXT_PORT_A, DEFAULT_TURN_POSITION);
    }

    U32 actualTargetAngle = DEFAULT_TURN_POSITION + targetAngle;
    bool clockwise =
        isTargetClockwise(nxt_motor_get_count(motorPort), actualTargetAngle);
    rotateMotor(speedPercent, brakeLength, clockwise, motorPort,
                allowedDeviation, actualTargetAngle);
}

void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool clockwise, U32 motorPort,
                          int allowedDeviation) {
    if (first) {
        first = FALSE;
        nxt_motor_set_count(NXT_PORT_A, DEFAULT_TURN_POSITION);
    }

    U32 targetAngle =
        getDestinationAngle(nxt_motor_get_count(motorPort), degreesToRotate);
    rotateMotor(speedPercent, brakeLength, clockwise, motorPort,
                allowedDeviation, targetAngle);
}

void rotateMotor(int speedPercent, int brakeLength, bool clockwise,
                 U32 motorPort, int allowedDeviation, int targetAngle) {
    if (clockwise) {
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

    clockwise = isTargetClockwise(nxt_motor_get_count(motorPort), targetAngle);
    rotateMotor(10, 0, clockwise, motorPort, allowedDeviation, targetAngle);
}

bool isTargetClockwise(U32 startAngle, U32 targetAngle) {
    return startAngle < targetAngle;
}

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
    return startAngle + degreesToRotate;
}
