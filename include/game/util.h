#ifndef _GAME_UTIL_H
#define _GAME_UTIL_H

#include "ultra64.h"
#include "game/object.h"
#include "game/hu3d.h"

#define rand16() ((rand8() << 8) | rand8())

u16 Hu3DModelRead(s32 arg0, s32 arg1);
u16 SprModelRead(s32 arg0, s32 arg1, s32 arg2);
s16 Hu3DMotionModelRead(s32 arg0);
u8 rand8(void);
void ScissorSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void ViewportSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void omObjMotionRead(omObjData *, u16, s32);

u16 Hu3DModelRead2(s32 arg0, s32 arg1);
u16 Hu3DModelRead3(s32 arg0, s32 arg1);
void OvlModeLoad(s32 arg0, u8 sectionFlags);
void OvlLoad(s32 overlayIndex);
s8 PadNextIndexGet(void);
s16 Hu3DAnimRead(HmfData* arg0, s32 arg1, char* arg2);
s16 Hu3DModelReadNum(s32 arg0);

#endif //_GAME_UTIL_H
