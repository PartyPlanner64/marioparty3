#ifndef MSETUP_H
#define MSETUP_H

#include "ultra64.h"

typedef struct UnkMsetupEntry {
    /* 0x00 */ s16 value;
    /* 0x02 */ char unk_02[0x12];
} UnkMsetupEntry; // sizeof 0x14

typedef struct MsetupMenuState {
    s16 state;
    s16 unk02;
    s16 result;
} MsetupMenuState;

#endif
