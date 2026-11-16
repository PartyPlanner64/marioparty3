#ifndef _MSTORY3_H
#define _MSTORY3_H

#include "common.h"

typedef struct Mstory3ObjWork {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} Mstory3ObjWork; // sizeof 0x14

#endif
