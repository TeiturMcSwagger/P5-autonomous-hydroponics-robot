package test;

import lejos.nxt.Battery;
import lejos.nxt.Button;
import lejos.nxt.ButtonListener;
import lejos.nxt.LCD;
import lejos.nxt.Motor;
import lejos.nxt.comm.RConsole;

public class HelloWorld {
	
  public static boolean shouldIRun = true;
  public static int direction = 0;
    
  public static void main (String[] args) {
      
          test();
          
  }
  
  public static void test() {
      
      int counter = 2;
      
      while(counter-- >= 0) {
          
          RConsole.println(""+getBatteryDrain(1));
          RConsole.println("lol");
          
      }
      
      Button.waitForAnyPress();
  }
  
  public static void turnMotorLeft() {
      Motor.C.rotateTo(-40);
      System.out.println("Left");
  }
  
  public static void turnMotorStraight() {
      Motor.C.rotateTo(0);
      System.out.println("Straight");
  }
  
  public static void turnMotorRight() {
      Motor.C.rotateTo(40);
      System.out.println("Right");
  }
  
  public static void motorDriveArm(int duration, int speed) {
  	  
	  Motor.A.setSpeed(speed);
	  Motor.A.forward();
	  countdownWait(duration);
	  Motor.A.stop();
	  
  }
  
  public static void motorDriveSteering(int duration, int speed) {
  	  
	  Motor.B.setSpeed(speed);
	  Motor.B.forward();
	  countdownWait(duration);
	  Motor.B.stop();
	  
  }
  
  public static void motorDriveWheels(int duration, int speed) {
  	  
	  Motor.C.setSpeed(speed);
	  Motor.C.forward();
	  countdownWait(duration);
	  Motor.C.stop();
	  
  }
    
  public static float getBatteryDrain(int seconds) {
	  
	  float startVoltage = Battery.getVoltage();
	  
	  countdownWait(seconds);
	  
	  float endVoltage = Battery.getVoltage();
	  
	  
	  
	  float returnString = 0;
	  
	  if (startVoltage < endVoltage) {
		  
		  float differenceVoltage = (endVoltage-startVoltage)/seconds;
		  
		  returnString = differenceVoltage;
		  
	  }
	  
	  else {
		  
		  float differenceVoltage = (startVoltage-endVoltage)/seconds;
		  
		  returnString = differenceVoltage;
		  
	  }
	  
	  return returnString;
	  
  }
  
  public static void countdownWait(int seconds) {
	  if(seconds > 0) {
		  lejos.util.Delay.msDelay(1000);
		  //System.out.println(seconds + " seconds left.");
		  countdownWait(--seconds);
	  }
  }
  
  public static void countdownWait(float seconds) {
	  if(seconds > 0) {
		  lejos.util.Delay.msDelay(1000);
		  //System.out.println(seconds + " seconds left.");
		  countdownWait(--seconds);
	  }
  }
  
}