#ifndef _GAME_HMFSPR_H
#define _GAME_HMFSPR_H

#include "ultra64.h"
#include "game/hu3d.h"
#include "types.h"
#include "common_structs.h"

#ifndef NO_EXTERN_VARIABLES
extern u8 D_800D20B8_main[16][3];
extern u8 D_800D5570_main[16][3];
extern Gfx *D_800D1360[8];
#endif

void Hu3DSprModelInit(s32 count);
void Hu3DSprModelBufSwap(void);
u16 Hu3DSprModelCreate(void *data, u32 flags, u16 attr);
u16 Hu3DSprModelLink(s16 idx, u16 attr);
void Hu3DSprModelAttrSet(s16 arg0, u16 arg1, u16 arg2);
void Hu3DSprModelFrameSet(s16 arg0, u16 arg1);
void Hu3DSprModelPointSet(s16 arg0, u16 arg1);
u16 Hu3DSprModelFrameGet(s16 arg0);
void Hu3DSprModelTPLvlSet(s16 arg0, s16 arg1);
void Hu3DSprModelColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3);
void Hu3DSprModelReset(s16 arg0);
void Hu3DSprModelColorFadeSet(s16 idx, u8 r0, u8 g0, u8 b0, u8 a0, u8 r1, u8 g1, u8 b1, u8 a1);
void Hu3DSprModelColorKeySet(s16 arg0, HmfColorKey *arg1);
void Hu3DSprModelExec(s32 frames);
void Hu3DSprModelKill(s32 idx);
void Hu3DSprModelAllKill(void);
HmfModelSet *Hu3DMotionBake(s16 model, s16 step);
HmfModelSet *Hu3DMotionBakeObj(s16 model, s16 step, char *name);
void Hu3DMotionBakeSub(s16 model, s16 step, HmfModelSet *set, s16 target);
void Hu3DModelObjMtxFrameGet(s16 model, s16 frame, const char *name, HuMtx4F *out);
void objMtxCalcFrame(HmfData *hmf, s16 nodeIdx, s16 target);
void Hu3DMotionBakeApply(s16 model, HmfModelSet *set, s16 frame);
void Hu3DMotionBakeMtxGet(s16 model, HmfModelSet *set, HuMtx4F mtx, s16 frame);
void Hu3DMotionBakeFree(HmfModelSet *set);
void Hu3DModelObjCopy(s16 srcModel, const char *srcName, s16 dstModel, const char *dstName);
void CharAnimInit(void);
s16 CharAnimCreate(s16 model, s16 slot, s16 chr, s32 dataNum);
void CharAnimSet(s16 model, s16 slot, s16 chr, s16 animIdx);
void CharAnimFrameSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
s16 Hu3DAnimDataRead(s32 dataNum);
void CharAnimAttrSet(s16 arg0, s16 arg1, u8 arg2, u8 arg3);
s32 CharMotionDataNumGetTbl(s16 chr, s16 arg1, s16 arg2);
s32 CharMotionDataNumGet(s16 chr, s16 animId);

#endif
