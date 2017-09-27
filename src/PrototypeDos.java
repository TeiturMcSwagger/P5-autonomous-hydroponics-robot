import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

import static tests.NXTTest.connectBluetooth;

public class PrototypeDos {
    private static NXTRegulatedMotor motor;
    private static NXTRegulatedMotor motorArm;
    private static NXTRegulatedMotor steeringMotor;

    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        motor = Motor.A;
        motorArm = Motor.B;
        steeringMotor = Motor.C;
        connectBluetooth();
        RConsole.println("Expecting color sensor to be in port 1");
        RConsole.println("Expecting driving motor to be in port A");
        RConsole.println("Expecting arm motor to be in port B");
        RConsole.println("Expecting steering motor to be in port C");

        while(Button.readButtons() != Button.ID_ESCAPE) {
            // drive indefinitely
            motor.forward();

            // scan color
            ColorSensor.Color color = colorSensor.getColor();
            if(color.toString() == "goodStuff") {
                motor.stop();
                // take into account the robot might be angled wrong in regards to the plant
                nourish();
            } else if(color.toString() == "someOtherStuff") {
                // turn a bit left
//                steeringMotor.rotate(-3);
            } else if(color.toString() == "someOtherOtherStuff") {
                // turn a bit right
//                steeringMotor.rotate(3);
            }
        }
    }

    private static void nourish() {
        RConsole.println("Nourishing the plant..");
        motorArm.rotate(180);
        // wait for ball to drop
    }
}
