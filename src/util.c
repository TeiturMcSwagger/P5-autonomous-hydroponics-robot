#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include "util.h"
#include <stdlib.h>

int displayRow = 0;

void printString(char *str) {
    if (displayRow == 7)
        clearScreen();
    display_goto_xy(0, displayRow++);
    display_string(str);
    display_update();
}

void printInt(int value) {
    if (displayRow == 7)
        clearScreen();
    display_goto_xy(0, displayRow++);
    display_int(value, 0);
    display_update();
}

void printStringAndInt(char *str, int val) {
    if (displayRow == 7)
        clearScreen();
    display_goto_xy(0, displayRow++);
    display_string(str);
    display_int(val, 0);
    display_update();
}

void clearScreen() {
    display_clear(0);
    displayRow = 0;
}
