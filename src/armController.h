#ifndef ARMCONTROLLER_H
#define ARMCONTROLLER_H

#include "types.h"

extern bool areWeFeeding;

typedef struct nutrition {
    void (*feedProc)(void *amount);
    void *amount;
} nutrition;

void feed(nutrition n);
void feedPills(void *amount);

#endif
