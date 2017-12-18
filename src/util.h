#ifndef UTIL_H
#define UTIL_H
#include "types.h"

void printString(char *str);
void printStringAndInt(char *str, int val);
void clearScreen();
void printInt(int value);
int clampInt(int val, int min, int max);
bool sameSignInt(int num1, int num2);

#endif
