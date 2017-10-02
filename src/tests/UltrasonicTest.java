import lejos.nxt.*;
import lejos.nxt.comm.RConsole;

/**
 * Tests the consistency and latency of ultrasonic sensors
 * 0016530A7CD6
 */
public class UltrasonicTest {

    public static void main(String[] args) {
//        UltrasonicSensor IJOUltrasonicSensor = new UltrasonicSensor(SensorPort.S2);
       UltrasonicSensor blankUltrasonicSensor = new UltrasonicSensor(SensorPort.S1);
        RConsole.openUSB(20000);

        int i = 0;
       while(Button.readButtons() != Button.ID_ESCAPE && i < 200) {
           getDistance_Test("Blank ", blankUltrasonicSensor);
           i++;
       }

//        i = 0;
//        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000) {
//            getDistance_Test("IJO ", IJOUltrasonicSensor);
//            i++;
//        }
    }

    /**
     * Tests how consistent the distance measurements are
     */
    private static void getDistance_Test(String s, UltrasonicSensor sensor) {
        try {
            Thread.sleep(100);
        } catch (Exception e) {
            
        }
        RConsole.println(s + Double.toString(sensor.getDistance()));
    }

    /**
     * Tests how often the Ultrasonic Sensor can be pinged
     */
    private static void latency_Test(String s, UltrasonicSensor sensor) {
        long startTime = System.nanoTime();
        sensor.getDistance();
        long endTime = System.nanoTime();
        long latency = endTime - startTime;
        RConsole.println(s + latency);
    }
}
