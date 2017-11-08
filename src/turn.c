#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"

int translationFactor = MAX_STEERING_ANGLE / OPTIMAL_LIGHT_VALUE;

void turnMe() {
    int lightValue = 100;
    // nxt_motor_set_count(0, 180);

    while (1) {
        if (lightValue <= OPTIMAL_LIGHT_VALUE) {
            /*MAX_STEERING_ANGLE-(lightValue*translationFactor) is the amount of
             * degress to be turned*/

            rotateMotorToAngle(
                100, 0, (MAX_STEERING_ANGLE - (lightValue * translationFactor)),
                NXT_PORT_A, 0);

        } else if (lightValue >= OPTIMAL_LIGHT_VALUE) {
            /*The bitch should turn all sails due east, cuz shit's about to go
             * down.*/
            rotateMotorToAngle(
                100, 0, (MAX_STEERING_ANGLE - (lightValue * translationFactor)),
                NXT_PORT_A, 0);
        }
    }
}
