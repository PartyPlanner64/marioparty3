#ifndef _OVL_MGRESULTBOARD_H
#define _OVL_MGRESULTBOARD_H

#include "ultra64.h"

typedef struct PlayerResult {
    /* 0x00 */ s8 idx;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s16 score;
    /* 0x06 */ s16 coin;
    /* 0x08 */ s16 gameCoin;
    /* 0x0A */ s16 bonusCoin;
} PlayerResult; // sizeof 0x0C

#endif
