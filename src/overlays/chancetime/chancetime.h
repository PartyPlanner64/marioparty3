#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

extern s32 D_8010FAE4_chancetime;
extern s8 D_801100D0_chancetime[4];

void func_80106F10_chancetime(void);
void func_8010705C_chancetime(void);
void func_801071A8_chancetime(void);
void func_80108A88_chancetime(void);
void func_80108B50_chancetime(void);
void func_8010BF48_chancetime(void);

#endif
