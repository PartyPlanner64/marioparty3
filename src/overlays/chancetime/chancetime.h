#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

extern s8 D_801100D0_chancetime[4];

#endif
