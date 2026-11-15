#ifndef _OVL_MGRESULTBOARD_H
#define _OVL_MGRESULTBOARD_H

#include "ultra64.h"

typedef struct PlayerResult {
    /* 0x00 */ s8 idx;
    /* 0x01 */ s8 rank;
    /* 0x02 */ s8 chr;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 star;
    /* 0x06 */ s16 coin;
    /* 0x08 */ s16 gameCoin;
    /* 0x0A */ s16 bonusCoin;
} PlayerResult; // sizeof 0x0C

typedef struct UnkTemp { // is this just a copy of PlayerResult ?
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} UnkTemp; // sizeof 0xC

#endif
