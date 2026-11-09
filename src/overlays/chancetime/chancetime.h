#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

extern s32 D_8010FAE4_chancetime;
extern s8 D_801100D0_chancetime[4];
extern s8 D_801100DC_chancetime;

void func_80106320_chancetime(void);
void func_80106B18_chancetime(void);
void func_80106F10_chancetime(void);
void func_8010705C_chancetime(void);
void func_801071A8_chancetime(void);
void func_80107300_chancetime(void);
void func_80108704_chancetime(void);
void func_80108A88_chancetime(void);
void func_80108B50_chancetime(void);
void func_80108CDC_chancetime(void);
void func_801094CC_chancetime(void);
void func_80109A00_chancetime(void);
void func_80109F34_chancetime(void);
void func_8010A468_chancetime(void);
void func_8010A99C_chancetime(void);
void func_8010B030_chancetime(void);
void func_8010BF48_chancetime(void);
void func_8010BF80_chancetime(void);
void func_8010D92C_chancetime(s8 arg0);
void func_8010DBB0_chancetime(void);

#endif
