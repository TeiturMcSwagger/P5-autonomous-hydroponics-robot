#include "ecrobot_interface.h"
#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"


int translationFactor = MAX_STEERING_ANGLE / OPTIMAL_LIGHT_VALUE;

void turnMe() {
    lightValue = 100;
    int i = 0;
    nxt_motor_set_count(0, 180);
    while (1) {
        display_int(
            180 + (MAX_STEERING_ANGLE - (lightValue * translationFactor)), i++);
        display_int(lightValue, i++);
        display_update();
        if (lightValue <= OPTIMAL_LIGHT_VALUE) {
            /*MAX_STEERING_ANGLE-(lightValue*translationFactor) is the amount of
             * degress to be turned*/
            // nxt_motor_set_speed(0, 100, 1);
            rotateMotorToAngle(
                100, 40,
                180 + (MAX_STEERING_ANGLE - (lightValue * translationFactor)),
                NXT_PORT_A, 0);

        } else if (lightValue >= OPTIMAL_LIGHT_VALUE) {
            /*The bitch should turn all sails due east, cuz shit's about to go
             * down.*/
        }
    }
}
