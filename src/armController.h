#ifndef ARMCONTROLLER_H
#define ARMCONTROLLER_H

typedef struct nutrition {
    void (*feed)(void *amount);
    void *amount;
} nutrition;

void feed(nutrition n);
void feedPills(int amount);

#endif