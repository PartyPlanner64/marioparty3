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

#ifndef NO_EXTERN_VARIABLES
extern ESPRITE *D_800CD1DC_main;
#endif

s16 HuSprAnimDataRead(s32 dataNum);
void espDispOn(u16 arg0);
void espDispOff(u16 arg0);
void espMain(void);
void espPosSet(u16 spriteId, s16 x, s16 y);
void espPriSet(u16, s32);
void espPatNoSet(u16 spriteId, s16 arg1);
void espAnimModeSet(u16 spriteId, s32 arg1);
s16 espEntry(s16 arg0, s16 arg1, u16 arg2);
void espKill(u16);

void espInit(void);
void espPalColorSet(s16 arg0, f32 r, f32 g, f32 b);
void espClose(void);
void espTPLvlSet(u16 spriteId, s16 arg1);
void espAttrSet(u16 arg0, u16 arg1);
void espAttrReset(u16 arg0, u16 arg1);
void espSpeedSet(u16 spriteId, f32 arg1);
void espBankSet(u16 spriteId, s32 arg1, s32 arg2);
u8 espAnimStatGet(u16 spriteId);
void espScaleSet(u16 spriteId, f32 x, f32 y);
void espColorSet(u16 spriteId, s32 arg1, s32 arg2, s32 arg3);
void espZRotSet(u16 spriteId, f32 arg1);
void espTPLvlFadeSet(u16 spriteId, s16 arg1, s16 arg2, s16 arg3);
void espTPLvlFadeReset(u16 spriteId, s16 arg1);

#endif
