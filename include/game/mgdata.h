#ifndef _GAME_MGDATA_H
#define _GAME_MGDATA_H

#include "ultra64.h"

typedef struct MinigameTable {
    /* 0x00 */ s32 overlay;
    /* 0x04 */ u8 minigameType;
    /* 0x05 */ u8 unk_05;
    /* 0x06 */ u16 flags;
    /* 0x08 */ s16 message;
    /* 0x0A */ s16 unk_0A[4];
    /* 0x12 */ s16 finalMessage;
} MinigameTable; // sizeof 0x14

extern const MinigameTable D_800A6D40_main[];

s32 func_800341C0_main(s32 minigameIndex);

#endif
