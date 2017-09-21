package tests;


import lejos.nxt.Motor;
import lejos.nxt.NXTRegulatedMotor;

import static tests.NXTTest.connectBluetooth;

public class ServoMotorTest {
    private static NXTRegulatedMotor motor;

    public static void main(String[] args) {
        connectBluetooth();
        motor = Motor.A;
    }



    /**
     *  Tests the consistency of the throughput of the motor
     */
    public static void consistency_Test() {
        // does it return to the same point?
        // does speed affect the results?

        motor.setSpeed(720);
        motor.rotate(360);
        // wait

        latency_Test();
    }

    /**
     * Tests how quickly we can stop the motor
     */
    public static void latency_Test() {
        motor.forward();
        motor.stop();
    }
}
