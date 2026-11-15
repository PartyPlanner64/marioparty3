#ifndef _MGRESULTDEALER_H
#define _MGRESULTDEALER_H

#include "game/object.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultDealerObj;

typedef struct {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ s16 unk_02[3];
    /* 0x08 */ u16 unk_08[3];
} UnkDealerSprGroup; // Size 0xE

typedef struct {
    /* 0x00 */ UnkDealerSprGroup groups[3];
    /* 0x2A */ u16 unk_2A;
    /* 0x2C */ u16 unk_2C;
} UnkDealerSprites;

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc objFunc;
} UnkDealerFadeProc;

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ Vec unk_08;
    /* 0x14 */ f32 unk_14;
} UnkDealerCoin; // Size 0x18

#ifndef NO_EXTERN_VARIABLES
extern ResultDealerObj D_8010A250_mgresultdealer;
#endif

#endif
