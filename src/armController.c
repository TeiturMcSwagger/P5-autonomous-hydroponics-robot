#include "armController.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include "sym.h"
void feed(nutrition n) { n.feedProc(n.amount); }
void feedPills(void *amount) {
    int countOfPills = *((U8 *)amount);
    while (countOfPills-- > 0) {
        rotateMotorByDegrees(100, 90, TRUE, ARM_MOTOR_PORT);
    }
}