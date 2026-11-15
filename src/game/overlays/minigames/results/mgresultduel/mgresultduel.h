#ifndef _MGRESULTDUEL_H
#define _MGRESULTDUEL_H

#include "game/object.h"

typedef struct ResultDuelObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultDuelObj;

typedef struct UnkResultDuelStruct {
    /* 0x00 */ u8 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec pos;
    /* 0x14 */ f32 unk14;
} UnkResultDuelStruct; // size = 0x18

#endif
