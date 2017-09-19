import lejos.nxt.*;

public class ColorSensorTest {

  // test ping/scan interval

  // test moving bricks

  // test range/proximity
  public void rangeTest() {
    ColorSensor cs = new ColorSensor(SensorPort.S1);
    System.out.println(cs.getColor());
  }

}
