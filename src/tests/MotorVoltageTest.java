package tests;

import lejos.nxt.Motor;
import lejos.nxt.NXTRegulatedMotor;

import static lejos.nxt.Battery.getVoltageMilliVolt;

public class MotorVoltageTest {
    private static NXTRegulatedMotor motor;

    public static void main(String[] args) throws InterruptedException
    {
        motor = Motor.A;
        double v1 = getVoltageMilliVolt();
        System.out.println("Idle volt: " + v1);
        motor.setSpeed(900);
//        motor.rotate(360);
        motor.forward();
        Thread.sleep(500);
        double v2 = getVoltageMilliVolt();
        motor.stop();
        System.out.println("Running volt: " + v2);
        Thread.sleep(5000);
        while(true) {
            v2 = getVoltageMilliVolt();
            System.out.println("Running volt: " + v2);
        }
    }
}
