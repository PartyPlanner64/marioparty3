#ifndef _GAME_EFFECT_H
#define _GAME_EFFECT_H

#include "ultra64.h"
#include "game/object.h"

s16 func_8000CBA0_main(s32 fileId, s32 attr);
s16 func_8000CC98_main(s32 fileId, s32 attr);
void func_8000CD00_main(s16 model, f32 arg1, f32 arg2, f32 arg3);
s32 func_8000CD74_main(s16 model, f32 x, f32 y, f32 z);
s16 func_8000CED8_main(s32 fileId, s32 attr);
void func_8000CFA4_main(s16 model, f32 x, f32 y, f32 z);
void func_8000CFD8_main(s16 model, s16 time);
void func_8000D018_main(s16 model, f32 range);
void func_8000D044_main(s16 model);
void func_8000D06C_main(omObjData *obj);
void func_8000D268_main(s16 model);
void func_8000D3AC_main(void);
s16 func_8000D3E0_main(s32 fileId, s32 attr, s16 count, void (*func)(s16));
s16 func_8000D550_main(s16 index, f32 x, f32 y, f32 z);
s16 func_8000D658_main(s32 attr, s16 count);
void func_8000D694_main(s16 model);

#endif
