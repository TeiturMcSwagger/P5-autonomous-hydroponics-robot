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
        RConsole.println("Expecting driving motor to be in port A");
        RConsole.println("Expecting arm motor to be in port B");

        while(Button.readButtons() != Button.ID_ESCAPE) {
            // drive indefinitely
            motor.forward();

            // scan color
            ColorSensor.Color color = colorSensor.getColor();
            if(color.toString() == "stuff") {
                motor.stop();
                nourish();
            }
        }
    }

    private static void nourish() {
        RConsole.println("Nourishing the plant..");
        motorArm.rotate(180);
        // wait for ball to drop
    }
}
