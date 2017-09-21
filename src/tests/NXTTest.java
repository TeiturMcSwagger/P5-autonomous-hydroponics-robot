import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class NXTTest {
    public static void main(String[] args) {
        connectBluetooth();
        sleep_Test();
    }

    /**
     * Tests if Thread.sleep works on the NXT
     */
    private static void sleep_Test() {
        int i = 0;
        RConsole.println("Testing Thread.sleep");
        while(Button.readButtons() != Button.ID_ESCAPE || i < 5) {

            RConsole.println(Double.toString(i));

            try {
                Thread.sleep(1000);
            } catch (Exception e) {
                RConsole.println(e.toString());
                e.printStackTrace();
            }

            i++;
        }
    }

    /**
     * Prints status messages while connecting RConsole to bluetooth
     */
    public static void connectBluetooth() {
        RConsole.println("Connecting to bluetooth");
        RConsole.openBluetooth(20000);
        RConsole.println("Connected to bluetooth");
    }

    /**
     * Prints status messages while connecting RConsole to USB
     */
    public static void connectUSB() {
        RConsole.println("Connecting to USB");
        RConsole.openUSB(20000);
        RConsole.println("Connected to USB");
    }
}
