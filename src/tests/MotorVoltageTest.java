package tests;

import lejos.nxt.Battery;
import lejos.nxt.Motor;
import lejos.nxt.NXTRegulatedMotor;
public class MotorVoltageTest {
    private static NXTRegulatedMotor motor;

    public static void main(String[] args) throws InterruptedException
    {
        motor = Motor.A;
        double v1 = Battery.getVoltageMilliVolt();
        System.out.println("Idle volt: " + v1);
        motor.setSpeed(900);
//        motor.rotate(360);
        motor.forward();
        Thread.sleep(500);
        double v2 = Battery.getVoltageMilliVolt();
        motor.stop();
        System.out.println("Running volt: " + v2);
        Thread.sleep(5000);
        while(true) {
            v2 = Battery.getVoltageMilliVolt();
            System.out.println("Running volt: " + v2);
        }
    }
}
