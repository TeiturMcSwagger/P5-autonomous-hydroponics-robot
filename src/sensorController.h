#ifndef SENSORCONTROLLER_H
#define SENSORCONTROLLER_H

#include "kernel.h"
#include "kernel_id.h"

U16 sampleColour(U8 sensorPort);
U8 getAmountFromSample(U16 colour);

#endif