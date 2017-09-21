package tests;

import lejos.nxt.comm.RConsole;

import static tests.NXTTest.connectUSB;

public class RConsoleHelloWorld {
    public static void main(String[] args) {
        connectUSB();
        RConsole.println("Hello, World!");
    }
}
