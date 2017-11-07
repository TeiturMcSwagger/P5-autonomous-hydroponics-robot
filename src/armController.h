#ifndef ARMCONTROLLER_H
#define ARMCONTROLLER_H

typedef struct nutrition {
    void (*feedProc)(void *amount);
    void *amount;
} nutrition;

void feed(nutrition n);
void feedPills(void *amount);

#endif