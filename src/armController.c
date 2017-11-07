#include "armController.h"
#include "nxtMotorController.h"
#include "sym.h"
void feed(nutrition n) { n.feedProc(n.amount); }
void feedPills(void *amount) {
    int countOfPills = *((int *)amount);
    while (countOfPills-- > 0) {
        rotateMotorByDegrees(100, 40, 90, TRUE, ARM_MOTOR_PORT, 0);
    }
}