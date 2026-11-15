#ifndef _GAME_LIGHTDEBUG_H
#define _GAME_LIGHTDEBUG_H

#include "ultra64.h"
#include "game/object.h"

s32 func_800465D0_main(void);
void func_800465DC_main(s8 arg0);
s32 func_800465E8_main(void);
void func_800465F4_main(s8 arg0);
void LightDebugCreate(void);
void LightDebugKill(void);
void LightDebugExec(omObjData *object);

#endif
