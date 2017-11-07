#include "armController.h"
#include "nxtMotorController.h"
void feed(nutrition n) {
    //
    n.feed(n.amount);
}
void feedPills(int amount) {
    while (amount > 0) {
        rotateMotorByDegrees(100, 40, 90, TRUE, 0, 0);
    }
}