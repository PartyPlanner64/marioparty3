#ifndef _GAME_ESPRITE_H
#define _GAME_ESPRITE_H

#include "ultra64.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04; // gid?
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA; // x center
    /* 0x0C */ s16 unkC; // y center
    /* 0x0E */ s16 unkE;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ char unk22[2];
} ESPRITE; // Size 0x24

extern ESPRITE *D_800CD1DC_main;

s16 func_8000B838_main(s32 arg0);
void espDispOn(u16 arg0);
void espDispOff(u16 arg0);
void func_8000BA30_main(void);
void espPosSet(u16 spriteId, s16 x, s16 y);
void espPriSet(u16, s32);
void func_8000BD50_main(u16 spriteId, s16 arg1);
void func_8000BDDC_main(u16 spriteId, s32 arg1);
s16 espEntry(s16 arg0, s16 arg1, u16 arg2);
void espKill(u16);

#endif
