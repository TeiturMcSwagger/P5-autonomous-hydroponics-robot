void rotateMotorToAngle(int speedPercent, int brakeLength, U32 targetAngle,
                        U32 motorPort, int allowedDeviation);

void rotateMotorByDegrees(int speedPercent, int brakeLength,
                          U32 degreesToRotate, bool turnDirection,
                          U32 motorPort, int allowedDeviation);