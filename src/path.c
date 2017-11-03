#include "ecrobot_interface.h"
#include "globalConstants.h"

int translationFactor = MAX_STEERING_ANGLE / OPTIMAL_LIGHT_VALUE;
int lightValue = 0;

void turn() {
    if (lightValue <= OPTIMAL_LIGHT_VALUE) {
        /*MAX_STEERING_ANGLE-(lightValue*translationFactor) is the amount of
         * degress to be turned*/
    } else if (lightValue >= OPTIMAL_LIGHT_VALUE) {
        /*the bitch should turn all sails due east, cuz shit's about to go
         * down.*/
    }
}
