#include "nxtMotorController.h"
#include "path.h"
#include "sym.h"
#include "calibrate.h"
#include "util.h"

void drive(){
    int normalspeed = 100;
    int newspeed = 0;
    int diviation = getDiviation();
    printStringAndInt("Calib. Lightvalue: ", optimalLightValue);
    printStringAndInt("diviation: ", diviation);
    if(diviation > normalspeed){
        nxt_motor_set_speed(1, 0, 1);
        nxt_motor_set_speed(0, normalspeed, 1);
    }
    else if(diviation < -normalspeed){
        nxt_motor_set_speed(1, normalspeed, 1);
        nxt_motor_set_speed(0, 0, 1);
    }
    else if(diviation < optimalLightValue){
        newspeed = diviation + normalspeed;
        printStringAndInt("newspeed ", newspeed);
        nxt_motor_set_speed(1, newspeed, 1);
        nxt_motor_set_speed(0, normalspeed, 1);
    }
    else if(diviation > optimalLightValue){
        newspeed = diviation - normalspeed;
        printStringAndInt("newspeed ", newspeed);
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
    systick_wait_ms(3000);
}
/*
void turnMe() {
    lightValue = 250;
    // Rotate motor to angle based on lightValue
    rotateMotorToAngle(
        100, MAX_STEERING_ANGLE - (lightValue * translationfactor), NXT_PORT_A);
}
*/