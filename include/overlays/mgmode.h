#ifndef _OVL_MGMODE_H
#define _OVL_MGMODE_H

#include "ultra64.h"
#include "humath.h"

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 espriteSlot;
} MgmodeEsprite;

typedef struct {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ u16 attr;
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
} MgmodeEspriteDef; // sizeof 0xC

typedef struct MgmodeModelEntry {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 motAttr;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} MgmodeModelEntry; // sizeof 0x24

#endif
