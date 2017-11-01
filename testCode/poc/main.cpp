#include <stdlib.h>

// ECRobot++ API
#include "Motor.h"
#include "Lcd.h"
#include "Clock.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

Motor motorA(PORT_A);
TASK(FeedingTask)
{

}
