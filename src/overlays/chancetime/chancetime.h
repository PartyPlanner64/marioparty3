#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

#endif
