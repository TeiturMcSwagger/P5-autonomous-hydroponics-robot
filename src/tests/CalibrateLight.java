package tests;

import lejos.nxt.Button;
import lejos.nxt.ColorSensor;
import lejos.nxt.SensorPort;

public class CalibrateLight {
    public static void main(String[] args) {
        ColorSensor colorSensor = new ColorSensor(SensorPort.S1);
        while (Button.readButtons() != Button.ID_ESCAPE) {
            System.out.println("Left = low, Right = high");
            int clickedButtonId = Button.waitForAnyPress();
            if (clickedButtonId == Button.ID_LEFT) {
                System.out.println("Calibrating low");
                colorSensor.calibrateLow();
            } else if (clickedButtonId == Button.ID_RIGHT) {
                System.out.println("Calibrating low");
                colorSensor.calibrateHigh();
            }
        }
    }
}
