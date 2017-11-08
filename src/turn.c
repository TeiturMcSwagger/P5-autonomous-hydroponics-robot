#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"

void turnMe() {
    while (1) {
        //Rotate motor to angle based on lightValue
        rotateMotorToAngle(100, 0,
            MAX_STEERING_ANGLE - (lightValue * TRANSLATIONFACTOR),
            NXT_PORT_A, 0);
    }
}