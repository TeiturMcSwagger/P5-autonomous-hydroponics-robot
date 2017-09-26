import lejos.nxt.Motor;

public class sluseTest {

    public static void main(String[] args) {
        Motor.A.setSpeed(200);
        while(true){
            Motor.A.rotate(70);
            Motor.A.rotate(-70);
        }
    }



    /**
     *  Tests the consistency of the throughput of the motor
     */
    public static void consistency_Test() {
        // does it return to the same point?
        // does speed affect the results?

        // wait

        latency_Test();
    }

    /**
     * Tests how quickly we can stop the motor
     */
    public static void latency_Test() {
    }
}
