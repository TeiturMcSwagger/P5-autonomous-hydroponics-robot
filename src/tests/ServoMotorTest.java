package tests;


import lejos.nxt.Button;
import lejos.nxt.Motor;
import lejos.nxt.NXTRegulatedMotor;
import lejos.nxt.comm.RConsole;

public class ServoMotorTest {
    private static NXTRegulatedMotor motor;

    public static void main(String[] args) {
        connectBluetooth();

        motor = Motor.A;

        sleep_Test();
    }

    /**
     * Prints status messages while connecting RConsole to bluetooth
     */
    public static void connectBluetooth() {
        RConsole.println("Connecting to bluetooth");
        RConsole.openBluetooth(20000);
        RConsole.println("Connected to bluetooth");
    }

    private static void sleep_Test() {
        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE) {

            RConsole.println(Double.toString(i));

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            i++;
        }
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
