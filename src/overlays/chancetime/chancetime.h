#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

typedef struct ChanceTimeUnkFED0 {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14[3];
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ s8 unk1B[4];
    /* 0x1F */ char unk1F[9];
} ChanceTimeUnkFED0; // size = 0x28

typedef struct ChanceTimeTransfer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
} ChanceTimeTransfer; // size = 0x8

#ifndef NO_EXTERN_VARIABLES
extern s32 D_8010FAE4_chancetime;
extern s8 D_801100D0_chancetime[4];
extern s8 D_801100DC_chancetime;
#endif

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
