package tests;

import lejos.nxt.*;
import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class ColorSensorLatencyTest {
    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        ColorSensor blueColorSensor = new ColorSensor(SensorPort.S2);
        RConsole.openBluetooth(20000);
        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){

            long start = System.nanoTime();  
            ColorSensor.Color color = colorSensor.getColor();
            long elapsedTime = System.nanoTime() - start;

            start = System.nanoTime();  
            color = blueColorSensor.getColor();
            elapsedTime = System.nanoTime() - start;

            RConsole.println("Blank sensor : "+ elapsedTime + "nanoseconds");
            RConsole.println("Bluee sensor : "+ elapsedTime + "nanoseconds");
            i++;
        }
    }
}
