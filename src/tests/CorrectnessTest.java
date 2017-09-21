import lejos.nxt.*;
import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

public class CorrectnessTest {
    public static void main(String[] args) {
        ColorSensor blankColorSensor = new ColorSensor(SensorPort.S2);
        ColorSensor blueColorSensor = new ColorSensor(SensorPort.S1);
        RConsole.openBluetooth(20000);
        int i = 0;
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){
            ColorSensor.Color color = blankColorSensor.getColor();
            RConsole.println("Blank : RGB (" + color.getRed() + "," + color.getGreen() + "," + color.getBlue() + ") " + color.getColor());
            i++;
        }    
        while(Button.readButtons() != Button.ID_ESCAPE){}
        i = 0;
        try{
            Thread.sleep(3000);
        }
        catch(Exception e){
        }
        while(Button.readButtons() != Button.ID_ESCAPE && i < 1000){
            ColorSensor.Color color = blueColorSensor.getColor();
            RConsole.println(" Blue  :  RGB (" + color.getRed() + "," + color.getGreen() + "," + color.getBlue() + ") " + color.getColor());
            i++;
        }
    }
}                
