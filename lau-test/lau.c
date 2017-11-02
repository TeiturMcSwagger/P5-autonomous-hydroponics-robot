/* helloworld.c for TOPPERS/ATK(OSEK) */
#include "ecrobot_interface.h"
#include "kernel.h"
#include "kernel_id.h"

#define PATH_SENSOR_PORT NXT_PORT_S1

/* LEJOS OSEK hooks */
void ecrobot_device_initialize() {
  ecrobot_init_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
}

void ecrobot_device_terminate() {
  ecrobot_term_nxtcolorsensor(PATH_SENSOR_PORT);
}

/* nxtOSEK hook to be invoked from an ISR in category 2 */
void user_1ms_isr_type2(void) { /* do nothing */
}

void print(int row, char *str, int value) {
  display_goto_xy(0, row);
  display_string(str);
  display_int(value);
  display_update();
}

TASK(Scan_Path) {
  display_clear(0);
  int row = 0;
  display_goto_xy(0, 0);
  while (1) {
    if (row == 10) {
      row = 0;
      display_clear(0);
    }
    ecrobot_set_nxtcolorsensor(PATH_SENSOR_PORT, NXT_LIGHTSENSOR_RED);
    print(row++, "gayfish ", ecrobot_get_light_sensor(PATH_SENSOR_PORT), 0);
    systick_wait_ms(500);
  }
}
