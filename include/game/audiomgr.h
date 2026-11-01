#ifndef _GAME_AUDIOMGR_H
#define _GAME_AUDIOMGR_H

#include "ultra64.h"
#include "common_structs.h"

s32 amCreateAudioMgr(str800D5298 *cfg, ALHeap *heap);
void func_80008678_main(str800D5298 *cfg);
void func_8000870C_main(str800D5298 *cfg);
void __amMain(void *arg);
s32 __amDMA(s32 addr, s32 len, void *state);
void __clearAudioDMA(void);
void func_80008CC0_main(s32 arg0, s32 remove);

#endif
