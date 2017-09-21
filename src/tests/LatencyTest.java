import lejos.nxt.*;
import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class LatencyTest {
    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        RConsole.openBluetooth(20000);
        RConsole.println("HELLO MAN");

        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){

            long start = System.nanoTime();  
            ColorSensor.Color color = colorSensor.getColor();
            long elapsedTime = System.nanoTime() - start;
            RConsole.println(elapsedTime + " nanoseconds");
            i++;
        }
    }
}
