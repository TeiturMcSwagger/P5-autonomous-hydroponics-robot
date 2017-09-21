package tests;

import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

public class UltrasonicTest {
    public static void main(String[] args) {
        UltrasonicSensor ultrasonicSensor = new UltrasonicSensor(SensorPort.S1);
        RConsole.println("Connecting to USB");
        RConsole.openUSB(20000);
        RConsole.println("Connected to USB");

        while(Button.readButtons() != Button.ID_ESCAPE) {
            RConsole.println("" + ultrasonicSensor.getDistance());
        }
    }
}