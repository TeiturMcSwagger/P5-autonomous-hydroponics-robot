#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "sym.h"
#include "types.h"
#include "util.h"
#include <stdlib.h>

int lastCount = DEFAULT_TURN_POSITION;

void rotateMotor(int speedPercent, bool clockwise, U32 motorPort,
                 int targetAngle);
int getBrakeLength(int speedPercent);
void rotateToTarget(int speedPercent, int targetAngle, U32 motorPort,
                    int brakeLength, bool clockwise);
U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate);
bool isTargetClockwise(U32 startAngle, U32 targetAngle);

void rotateMotorToAngle(int speedPercent, int targetAngle, U32 motorPort) {

    U32 actualTargetAngle = DEFAULT_TURN_POSITION + targetAngle;
    bool clockwise =
        isTargetClockwise(nxt_motor_get_count(motorPort), actualTargetAngle);
    rotateMotor(speedPercent, clockwise, motorPort, actualTargetAngle);
}

void rotateMotorByDegrees(int speedPercent, U32 degreesToRotate, bool clockwise,
                          U32 motorPort) {

    U32 targetAngle =
        getDestinationAngle(nxt_motor_get_count(motorPort), degreesToRotate);
    rotateMotor(speedPercent, clockwise, motorPort, targetAngle);
}

void rotateMotor(int speedPercent, bool clockwise, U32 motorPort,
                 int targetAngle) {
    int brakeLength = getBrakeLength(speedPercent);
    nxt_motor_set_count(NXT_PORT_A, lastCount);

    if (nxt_motor_get_count(motorPort) - brakeLength < targetAngle) {
        rotateToTarget(speedPercent, targetAngle, motorPort, brakeLength,
                       clockwise);
    } else {
        rotateToTarget(speedPercent, targetAngle, motorPort, 0, clockwise);
    }

    nxt_motor_set_speed(motorPort, 0, 1);
    systick_wait_ms(150);

    U32 variation = targetAngle - nxt_motor_get_count(motorPort);

    lastCount = nxt_motor_get_count(NXT_PORT_A);

    if (variation == 0) {
        return;
    }

    clockwise = isTargetClockwise(nxt_motor_get_count(motorPort), targetAngle);
    rotateMotor(10, clockwise, motorPort, targetAngle);
}

int getBrakeLength(int speedPercent) {
    if (speedPercent == 100) {
        return MAX_SPEED_BRAKE_LENGTH;
    }
    return 0;
}

void rotateToTarget(int speedPercent, int targetAngle, U32 motorPort,
                    int brakeLength, bool clockwise) {
    if (clockwise) {
        nxt_motor_set_speed(motorPort, speedPercent, 1);
        while (nxt_motor_get_count(motorPort) + brakeLength < targetAngle)
            ;
    } else {
        nxt_motor_set_speed(motorPort, -speedPercent, 1);
        while (nxt_motor_get_count(motorPort) + brakeLength > targetAngle)
            ;
    }
}

bool isTargetClockwise(U32 startAngle, U32 targetAngle) {
    return startAngle < targetAngle;
}

U32 getDestinationAngle(U32 startAngle, U32 degreesToRotate) {
    return startAngle + degreesToRotate;
}
