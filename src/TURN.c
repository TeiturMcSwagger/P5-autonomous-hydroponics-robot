#include globalConstants.h

public void turn() {
	typedef char bool;
	#define left 'l'
	#define right 'r'
	bool locationFromTape = left;

	int targetLightLevel = 200;

	if (lightValue < optimalLightValue)
	{
		/*Turn right*/

	}
	else if (lightValue > optimalLightValue)
	{
		/*Turn left*/
	}
	else if (lightValue == optimalLightValue)
	{
		/*This is an unncesesary call of the TURN task*/
	}
}