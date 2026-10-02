#ifndef _WIPE_H
#define _WIPE_H

#include "ultra64.h"

void WipeInit(void);
void WipeCreateIn(s16, s16);
void WipeCreateOut(s16, s16);
s32 WipeStatGet(void);
void WipeColorSet(u8, u8, u8);

#endif //_WIPE_H
