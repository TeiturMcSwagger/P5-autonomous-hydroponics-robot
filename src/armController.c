#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include "armController.h"
#include "sym.h"
#include "types.h"

bool areWeFeeding;

void feed(nutrition n){
    n.feedProc(n.amount);
}
void feedPills(void *amount) {
    areWeFeeding = TRUE;
    int countOfPills = *((U8 *)amount);
    while (countOfPills-- > 0) {
        rotateMotorByDegrees(100, 90, TRUE, ARM_MOTOR_PORT);
    }
    areWeFeeding = FALSE;
}
