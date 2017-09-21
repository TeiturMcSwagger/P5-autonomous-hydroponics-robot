import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

import static tests.NXTTest.connectBluetooth;

public class WaterThePlants {
    private static NXTRegulatedMotor motor;
    private static NXTRegulatedMotor motorArm;

    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        motor = Motor.A;
        motorArm = Motor.B;
        connectBluetooth();
        RConsole.println("Expecting color sensor to be in port 1");
        RConsole.println("Expecting motor to be in port A");

        while(Button.readButtons() != Button.ID_ESCAPE) {
            // drive indefinitely
            motor.forward();

            // scan color
            ColorSensor.Color color = colorSensor.getColor();
            if(color.toString() == "stuff") {
                motor.stop();
                waterThePlant();
            }

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }

    private static void waterThePlant() {
        RConsole.println("Watering the plant..");
        motorArm.rotate(90);
        // wait
        // rotate back
    }
}
