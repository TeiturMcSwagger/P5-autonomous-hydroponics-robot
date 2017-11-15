#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"
#include "calibrate.h"
#include "util.h"

void drive(){
    int normalspeed = 50;
    int newspeed = 0;
    int diviation = getDiviation();
    if(diviation > normalspeed){
        nxt_motor_set_speed(1, -normalspeed, 1);
        nxt_motor_set_speed(0, normalspeed, 1);
    }
    else if(diviation < -normalspeed){
        nxt_motor_set_speed(1, normalspeed, 1);
        nxt_motor_set_speed(0, -normalspeed, 1);
    }
    else if(diviation < optimalLightValue){
        newspeed = diviation + normalspeed;
        nxt_motor_set_speed(1, newspeed, 1);
        nxt_motor_set_speed(0, normalspeed, 1);
    }
    else if(diviation > optimalLightValue){
        newspeed = diviation - normalspeed;
        nxt_motor_set_speed(1, normalspeed, 1);
        nxt_motor_set_speed(0, newspeed, 1);
    }
    else{
        nxt_motor_set_speed(1, normalspeed, 1);
        nxt_motor_set_speed(0, normalspeed, 1);
    }
}

void stopMotor(){
    int stop = 0;
    nxt_motor_set_speed(0, stop, 1);
    nxt_motor_set_speed(1, stop, 1);
}
/*
void turnMe() {
    lightValue = 250;
    // Rotate motor to angle based on lightValue
    rotateMotorToAngle(
        100, MAX_STEERING_ANGLE - (lightValue * translationfactor), NXT_PORT_A);
}
*/