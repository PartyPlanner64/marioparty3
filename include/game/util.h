#ifndef _GAME_UTIL_H
#define _GAME_UTIL_H

#include "ultra64.h"
#include "game/object.h"
#include "game/hu3d.h"

#define rand16() ((rand8() << 8) | rand8())

u16 func_8000B108_main(s32 arg0, s32 arg1);
u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
s16 func_8000B13C_main(s32 arg0);
u8 rand8(void);
void ScissorSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void ViewportSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_8000B460_main(omObjData *, u16, s32);

u16 func_8000B0A0_main(s32 arg0, s32 arg1);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_8000B1A0_main(s32 arg0, u8 sectionFlags);
void OvlLoad(s32 overlayIndex);
s8 func_8000B4B4_main(void);
s16 HmfAnimRead(HmfData* arg0, s32 arg1, char* arg2);
s16 func_8000B5BC_main(s32 arg0);

#endif //_GAME_UTIL_H
