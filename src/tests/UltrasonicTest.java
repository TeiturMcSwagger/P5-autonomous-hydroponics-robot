package tests;

import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

/**
 * Tests the consistency and latency of ultrasonic sensors
 */
public class UltrasonicTest {
    private static UltrasonicSensor ultrasonicSensor;

    public static void main(String[] args) {
        ultrasonicSensor = new UltrasonicSensor(SensorPort.S1);
        RConsole.println("Connecting to USB");
        RConsole.openBluetooth(20000);
        RConsole.println("Connected to USB");

        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE || i == 1000) {
            getDistance_Test();
//        latency_Test();
            i++;
        }
    }

    /**
     * Tests how consistent the distance measurements are
     */
    private static void getDistance_Test() {
        RConsole.println("Testing distance consistency");
        RConsole.println(Double.toString(ultrasonicSensor.getDistance()));
    }

    /**
     * Tests how often the Ultrasonic Sensor can be pinged
     */
    private static void latency_Test() {
        RConsole.println("Testing distance latency");
        double startTime = System.nanoTime();
        ultrasonicSensor.getDistance();
        double endTime = System.nanoTime();
        double latency = endTime - startTime;
        RConsole.println(Double.toString(latency));
    }
}