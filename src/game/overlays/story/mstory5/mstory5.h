#ifndef _MSTORY5_H
#define _MSTORY5_H

#include "common.h"

typedef struct StoryObjWork {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} StoryObjWork; // sizeof 0x18

typedef struct Mstory5FireParticle {
    /* 0x00 */ f32 time;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
} Mstory5FireParticle; // sizeof 0x1C

#endif
