import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

import static tests.NXTTest.connectBluetooth;

public class WaterThePlants {
    public static void main(String[] args) {
        UltrasonicSensor ultrasonicSensor = new UltrasonicSensor(SensorPort.S1);

        connectBluetooth();
        RConsole.println("Initiating..");

        while(Button.readButtons() != Button.ID_ESCAPE) {
            Motor.A.forward();
            int distance = ultrasonicSensor.getDistance();
            System.out.println(distance);

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
