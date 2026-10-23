#ifndef _OVERLAYS_OPTION_H
#define _OVERLAYS_OPTION_H

#include "common.h"

typedef struct UnkOption {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s32 unk_28;
} UnkOption;

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OptSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
} OptSprSlot; // sizeof 0x2

typedef struct {
    /* 0x00 */ s16 winID;
    /* 0x04 */ void *unk_04;
    /* 0x08 */ s32 unk_08;
} OptWinEntry; // sizeof 0xC

#endif
