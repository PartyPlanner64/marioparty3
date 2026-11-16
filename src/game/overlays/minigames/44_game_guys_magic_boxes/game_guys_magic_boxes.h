#ifndef _GAME_GUYS_MAGIC_BOXES_H
#define _GAME_GUYS_MAGIC_BOXES_H

#include "common.h"

void m268_SpotIntroInit(s16 x, s16 y);
void m268_SpotBeamInit(void);
s16 m268_SpotIntroUpdate(void);
s32 m268_SpotBeamUpdate(s32 x);
void m268_SpotDispOff(void);

#endif
