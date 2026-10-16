#ifndef MSETUP_H
#define MSETUP_H

#include "ultra64.h"
#include "math.h"

typedef struct MsetupPlayerConfig {
    u8 controllerPorts[4];
    u8 characters[4];
    u8 cpuDifficulty[4];
    u8 stars[4];
    u8 humanCount;
    u8 cpuCount;
    u8 totalTurns;
    u8 unk13;
    u8 connectedCount;
    u8 boardIndex;
    u8 unk16;
    u8 unk17;
} MsetupPlayerConfig;

typedef struct UnkMsetupEntry {
    /* 0x00 */ s16 value;
    /* 0x02 */ char unk_02[0x12];
} UnkMsetupEntry; // sizeof 0x14

typedef struct MsetupLinkedModel {
    Vec pos;
    Vec rot;
    s16 model;
    s16 unk1A;
    s16 targetPosition;
    s16 currentPosition;
    u16 flags;
    s16 unk22;
} MsetupLinkedModel;

typedef struct MsetupMenuState {
    s16 state;
    s16 unk02;
    s16 result;
} MsetupMenuState;

#endif
