#ifndef _GAME_AUDIOMGR_H
#define _GAME_AUDIOMGR_H

#include "ultra64.h"
#include "common_structs.h"

s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap);
void amStart(str800D5298 *cfg);
void amDestroyAudioMgr(str800D5298 *cfg);
void __amMain(void *arg);
s32 __amDMA(s32 addr, s32 len, void *state);
void __clearAudioDMA(void);
void amSchedClientSet(s32 arg0, s32 remove);

#endif
