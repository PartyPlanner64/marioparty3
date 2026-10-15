#ifndef MSETUP_H
#define MSETUP_H

#include "ultra64.h"
#include "math.h"

typedef struct UnkMsetupEntry {
    /* 0x00 */ s16 value;
    /* 0x02 */ char unk_02[0x12];
} UnkMsetupEntry; // sizeof 0x14

typedef struct MsetupLinkedModel {
    Vec pos;
    Vec rot;
    s16 model;
    char unk1A[6];
    u16 flags;
    s16 unk22;
} MsetupLinkedModel;

typedef struct MsetupMenuState {
    s16 state;
    s16 unk02;
    s16 result;
} MsetupMenuState;

#endif
