#ifndef _GAME_HMFDRAW_H
#define _GAME_HMFDRAW_H

#include "ultra64.h"
#include "game/mallocblock.h"
#include "game/hu3d.h"
#include "types.h"

typedef struct {
    union {
        Mtx mtx;
        Hilite hilite;
    } data;
    LookAt lookAt;
} HmfLookAtData;

typedef struct {
    s16 count;
    s16 indices[4];
    u8 flags;
    char unk0B[1];
    HmfMaterialData *material;
    HmfData_Unk84_Entry *texture;
} HmfDrawFace;

void Hu3DDrawInit(HuAllocFunc alloc, HuFreeFunc free, u16 vertexCount, u16 matrixCount, u16 gfxCount, u8 bufferCount);
void Hu3DPreProc(void);
void Hu3DDrawListInit(void);
void MakeDisplayList(HmfData *arg0);
void MakeVtxBuf(HmfData *arg0);
void MakeVtxGroup(HmfData *arg0);
void MakeTexAnim(HmfData *arg0);
s32 RemakeDisplayList(HmfData *arg0);
void Hu3DDraw(HmfData *arg0, HuMtx4F arg1, HuMtx4F arg2);
void mtxCopy(HuMtx4F dst, HuMtx4F src);
void objCallSkeleton(HmfData *arg0, s16 arg1);
void objCall(HmfData *arg0, s16 arg1);
void objCallNoAnim(HmfData *arg0, s16 arg1);
void objCallLink(HmfData *arg0, s16 arg1);
void objMesh(HmfData *arg0, s16 arg1, HmfDrawObject *arg2);
void Hu3DDrawEntryAddL(HmfData *arg0, s16 arg1, Mtx *arg2);
void Hu3DDrawEntryAdd(HmfData *arg0, s16 arg1, Mtx *arg2, HuMtx4F arg3);
Gfx *Hu3DDrawLayer(s16 arg0, Gfx *arg1, Gfx *arg2);
void FaceDraw(HmfData *hmf, s16 objectIndex);
void MaterialSet(HmfData *hmf, s32 *flags);
void ObjCullCheck(HmfData *hmf, s16 objectIndex);
void SetBlendMode(HmfMaterialData *material, HmfData_Unk84_Entry *texture, u32 flags);
void SetFogMode(u16 flags);
void SetClipRatio(void);
void SetupGeometry(HmfData *hmf, s32 flags, s16 objectIndex);
void SetReflect(HmfData *hmf, s16 objectIndex);
void LoadTexture(HmfData_Unk84_Entry2 *texture, s16 wrapS, s16 wrapT);
void SetHilite(HmfData *hmf, s16 objectIndex);
s32 objBillboardCheck(HmfData *arg0, s16 arg1, HuMtx4F arg2, HuMtx4F arg3);
void Hu3DModelObjMtxGet(HmfData *hmf, s16 nodeIndex, HuMtx4F mtx);
s32 objMtxCalc(HmfData *hmf, s16 nodeIndex, s16 targetIndex);
s16 SearchObjectIndex(HmfData *arg0, const char *name);
void Hu3DObjReplace(HmfData *hmf, char *name, HmfData *replacement);
void Hu3DObjReplaceIdx(HmfData *hmf, s16 objectIndex, HmfData *replacement);
void Hu3DMtxCalc(HmfData *hmf);
void objMtxCalcSkeleton(HmfData *hmf, s16 nodeIndex);
void objMtxCalcMotion(HmfData *hmf, s16 nodeIndex);
void SetLightColor(Gfx **arg0, s16 arg1, s32 color);
void Hu3DMotionInit(void);
s16 Hu3DMotionCreateSub(HmfMotionFile *file, HmfData *hmf);
s32 Hu3DMotionCreateNoHmf(HmfMotionFile *file);
s32 MotionLoad(HmfData *hmf, HmfMotionFile *file, s32 arg2);
void Hu3DMotionKill(s32 arg0);
void Hu3DMotionAllKill(void);
s32 MotionLoadTransform(HmfModelData_Unk64_Unk8C_Struct *motion, HmfData *hmf);
s32 MotionLoadChannel(HmfModelData_Unk64_Unk8C_Struct *motion, s16 channelIndex, u8 *data);
s32 MotionLoadMaterial(HmfData *hmf, s16 trackIndex, u8 *data);
s32 MotionLoadFixup(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionFile *file);
void Hu3DMotionExec(HmfData *hmf, f32 frame, HmfModelData_Unk64_Unk8C_Struct *motion, s32 reset);
f32 GetLinear(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame);
f32 GetCurve(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame);
void Hu3DSubMotionExec(HmfData *hmf, f32 frame, f32 weight);
s32 SetObjMatMotion(HmfData *hmf);
void Hu3DAnimTimeStep(HmfData *arg0, f32 arg1);
void Hu3DMotionTimeStepFwd(HmfData *arg0, f32 arg1);
void Hu3DMotionTimeStepBwd(HmfData *arg0, f32 arg1);
f32 Hu3DMotionTimeCalc(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed);
void Hu3DMotionTimeReset(HmfData *arg0);
void Hu3DMotionTimeEnd(HmfData *arg0);
s16 Hu3DMotionTimeGet(HmfData *arg0);
void Hu3DMotionNoMotSet(s16 arg0, s16 arg1, const char *arg2, s16 arg3, s16 arg4);
void Hu3DMotionNoMotReset(s16 arg0, s16 arg1, const char *arg2, s16 arg3, s16 arg4);
void Hu3DMotionNoMotSetEx(s16 modelIndex, s16 motionIndex, const char *name, s16 target, s16 component, s16 flags);
void Hu3DMotionGlobalSpeedSet(f32 arg0);

#endif
