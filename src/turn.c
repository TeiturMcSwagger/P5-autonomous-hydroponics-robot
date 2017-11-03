#include "globalConstants.h"
#include "ecrobot_interface.h"
#include "path.h"
#include "nxtMotorController.h"


int translationFactor = MAX_STEERING_ANGLE / OPTIMAL_LIGHT_VALUE;

void turnasd()
{
	lightValue = 100;

	if (lightValue <= OPTIMAL_LIGHT_VALUE)
	{
		/*MAX_STEERING_ANGLE-(lightValue*translationFactor) is the amount of degress to be turned*/
		rotateMotorToAngle(100, 40, 180 + (MAX_STEERING_ANGLE - (lightValue*translationFactor)), 0, 0);
	}
	else if (lightValue >= OPTIMAL_LIGHT_VALUE)
	{
		/*The bitch should turn all sails due east, cuz shit's about to go down.*/

	}
}