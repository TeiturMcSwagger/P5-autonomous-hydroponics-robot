package tests;

import lejos.nxt.*;
import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class ColorSensorConsistencyTest {
    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        ColorSensor blueColorSensor = new ColorSensor(SensorPort.S2);
        RConsole.openBluetooth(20000);
        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){
            ColorSensor.Color color = colorSensor.getColor();
            RConsole.println("BLUE : RGB (" + color.getRed() + "," + color.getGreen() + "," + color.getBlue() + ") " + color.getColor() );
            color = blueColorSensor.getColor();
            RConsole.println("BLANK RGB (" + color.getRed() + "," + color.getGreen() + "," + color.getBlue() + ")\n");
            i++;
        }
    }
}                
