package tests;

import lejos.nxt.*;
import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class ColorSensorConsistencyTest {
    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        colorSensor.setFloodlight(true);
        RConsole.openBluetooth(20000);
        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){
            ColorSensor.Color color = colorSensor.getColor();
            RConsole.println("RGB (" + color.getRed() + "," + color.getGreen() + "," + color.getBlue() + ")");
            i++;
        }
    }
}                
