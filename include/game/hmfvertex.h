#ifndef _GAME_HMFVERTEX_H
#define _GAME_HMFVERTEX_H

#include "ultra64.h"

typedef struct {
    char unk00[0x1C];
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    char unk22[2];
    f32 unk24;
    s16 *unk28;
    s16 *unk2C;
    u8 *unk30;
} HmfDispData;

typedef struct {
    s16 unk00;
    s16 unk02;
    s16 *unk04;
} HmfMtnData;

#endif
