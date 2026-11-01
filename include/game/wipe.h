#ifndef _WIPE_H
#define _WIPE_H

#include "ultra64.h"

typedef enum
{
    WIPE_STRIPES = 0,
    WIPE_CIRCLE = 1,
    WIPE_STARS = 2,
    WIPE_STRIPES2 = 3,
    WIPE_FADE = 11,
    WIPE_BOO = 12,
} EWipeType;

#define WIPE_TYPE_NORMAL 0
#define WIPE_TYPE_CROSS 0xFE
#define WIPE_TYPE_PREV 0xFF

#define WIPE_MODE_DUMMY 0
#define WIPE_MODE_IN 1
#define WIPE_MODE_OUT 2
#define WIPE_MODE_BLANK 3

extern u8 wipeType;
extern u8 wipeMode;
extern u8 wipeStat;
extern f32 wipeDuration;
extern f32 wipeTime;

void WipeInit(void);
void WipeCreateIn(s16, s16);
void WipeCreateOut(s16, s16);
s32 WipeStatGet(void);
void WipeColorSet(u8, u8, u8);

#endif //_WIPE_H
