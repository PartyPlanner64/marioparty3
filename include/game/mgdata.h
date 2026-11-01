#ifndef _GAME_MGDATA_H
#define _GAME_MGDATA_H

#include "ultra64.h"

typedef struct MinigameTable {
    /* 0x00 */ u8 minigameType;
    /* 0x01 */ char unk_01[5];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[6];
} MinigameTable;

extern MinigameTable D_800A6D44_main[];

s32 func_800341C0_main(void);

#endif
