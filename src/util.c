#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"
#include <stdlib.h>

int displayCount = 0;

void printString(char *str) {
  display_goto_xy(0, displayCount++);
  display_string(str);
  display_update();
}

void printStringAndInt(char *str, int val) {
  display_goto_xy(0, displayCount++);
  display_string(str);
  display_int(val, 0);
  display_update();
}
