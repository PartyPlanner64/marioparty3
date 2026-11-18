#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfdraw.h"
#include "game/board.h"
#include "game/effect.h"
#include "game/hmfload.h"
#include "game/hmfshape.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/hmfanim.h"
#include "game/graphics.h"
#include "game/profiler.h"
#include "game/hmfparticle.h"
#include "game/wipe.h"
#include "game/printfunc.h"
#include "gcc/string.h"
#include "game/hu3d.h"
#include "game/camera.h"
#include "game/hmflight.h"
#include "macros.h"
#include "game/mallocblock.h"
#include "include_asm.h"

extern s32 HuDbgStatus;
extern s32 Hu3DCurAttr;

// hmfanim.c
extern HmfData_Unk84_Entry2 *Hu3DTexData;

extern Gfx *gMainGfxPos;

extern u8 Hu3DBGColR;
extern u8 Hu3DBGColG;
extern u8 Hu3DBGColB;
extern s16 Hu3DCameraNum;
extern s32 Hu3DCurAttr;
extern u16 Hu3DDLModelNum[];
extern s8 Hu3DClipRatio;
extern s16 Hu3DFogEnd;
extern void (*Hu3DLayerHook[])(Gfx **, HuCamMtxs *, s16);
extern u16 Hu3DDLModelId;
extern s8 Hu3DFogColB;
extern s16 Hu3DModelTag;
extern HmfData Hu3DMotionHmf;
extern u8 Hu3DLayerNo;
extern s8 Hu3DFogF;
extern HuCamMtxs *Hu3DCurCamMtx;
extern s8 Hu3DFogColR;
extern u16 Hu3DDLModelList[][128];
extern Gfx *Hu3DGfxStart;
extern u8 Hu3DCameraNo;
extern s16 Hu3DCamMtxNo;
extern HmfDrawEntry *Hu3DDrawList[8];
extern HmfDrawObject *DrawObjData;
extern HuCamera *Hu3DCurCamera;
extern s32 Hu3DDrawDoneCnt;
extern s32 Hu3DModelNum;
extern u8 Hu3DBufNo;
extern u16 Hu3DDrawEnableF;
extern s8 Hu3DFogColG;
extern u16 Hu3DModelDataTag;
extern s16 Hu3DFogStart;

s32 Hu3DExecCnt = 0;

Gfx rdpInitGfx[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_NPRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(0, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTile(0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx rspInitGfx[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPClipRatio(FRUSTRATIO_2),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx scrClearGfx0[] = {
    gsSPDisplayList(rspInitGfx),
    gsSPDisplayList(rdpInitGfx),
    gsSPEndDisplayList(),
};

Gfx Hu3DExecInitGfx[] = {
    gsDPPipeSync(),
    gsSPDisplayList(scrClearGfx0),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0, 0, 0, 0),
    gsDPSetPrimColor(0, 0, 0, 0, 0, 255),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

Gfx scrClearGfx1[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPSetFillColor(0xFFFCFFFC),
    gsDPFillRectangle(0, 0, 319, 239),
    gsSPEndDisplayList(),
};

Gfx scrClearGfx2[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_FILL),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_NOOP2),
    gsDPFillRectangle(0, 0, 319, 239),
    gsDPNoOp(),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPEndDisplayList(),
};

s16 Hu3DMotionSpeedMul = 1;
f32 Hu3DVtxWaveAngle = 0.0f;

const char hexFmtStr[] = "%x\n";
const char modelEntryOverStr[] = "Model Entry Over!\n";

void Hu3DInit(void *arg0, void *arg1, u16 vertexCount, u16 gfxCount, u16 matrixCount, u8 bufferCount) {
    s16 modelId;

    Hu3DDrawInit(arg0, arg1, vertexCount, gfxCount, matrixCount, bufferCount);
    Hu3DMotionInit();
    Hu3DData = HuMemAlloc(HU3D_MODEL_MAX * sizeof(HmfModel));
    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        Hu3DData[modelId].hmf = NULL;
    }
    Hu3DPreProc();
    Hu3DFrameCnt = 0;
    Hu3DDrawDoneCnt = 0;
    Hu3DDrawEnableF = 1;
    Hu3DPauseF = 0;
    Hu3DScreenClearF = 1;
    Hu3DLayerHook[0] = Hu3DLayerHook[1] = 0;
    EffectGroupInit();
    Hu3DModelNum = 0;
}

s32 Hu3DModelCreate(u8 *data, u32 arg1) {
    HmfModel *modelP;
    HmfData *hmf;
    void *var_a1;
    s16 modelId;
    s16 var_a0;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (Hu3DData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(modelEntryOverStr);
        return -1;
    }
    Hu3DModelDataTag = TAG_MODEL + modelId * 2;
    Hu3DModelTag = TAG_MODEL + 1 + modelId * 2;
    modelP = &Hu3DData[modelId];
    modelP->unk08 = 0xFF;
    hmf = modelP->hmf = HuMemAlloc(sizeof(HmfData));
    hmf->unk0E = Hu3DModelDataTag;
    if (data[0] == 'M' && data[1] == 'T') {
        hmf->unk14 = 0;
        hmf->unk84 = 0;
        hmf->unk38 = 0;
        hmf->unkC8 = 0;
        hmf->unk98 = NULL;
        if (data[2] == 'N' && data[3] == 'X') {
            modelP->motId = Hu3DMotionCreateNoHmf((HmfMotionFile *)data);
            arg1 &= ~(0x10 | 0x1);
        } else {
            var_a1 = data + 8;
            if (data[8] == 'M') {
                if (data[9] == 'T' && data[10] == 'N' && data[11] == 'X') {
                    modelP->motId = Hu3DMotionCreateNoHmf(var_a1);
                    arg1 &= ~0x11;
                    var_a1 = HmfChunkNext(data + 12);
                } else {
                    modelP->motId = 0xFF;
                }
            } else {
                modelP->motId = 0xFF;
            }
            modelP->unk08 = Hu3DShapeCreate((HmfData *)data, var_a1);
        }
    } else {
        LoadHMF(hmf, data, arg1);
        if (hmf->unk38 != 0) {
            HuMemSetTag(hmf->unk50, Hu3DModelTag);
            modelP->unk10 = MapCollCreate(modelId);
        } else {
            modelP->unk10 = -1;
        }
        hmf->unk00 = (arg1 >> HU3D_ATTR_LAYER_SHIFT) & 7;
        modelP->attr = arg1;
        modelP->motId = Hu3DMotionCreateSub((HmfMotionFile *)data, hmf);
        if (modelP->motId != 0xFF) {
            if (hmf->unk14 == 0) {
                MotionNodeFree(hmf);
            } else {
                goto skip;
            }
        }
    }
    if (hmf->unk14 == 0) {
        arg1 |= HU3D_ATTR_DISPOFF;
    }
skip:
    modelP->attr = arg1;
    if (arg1 & HU3D_ATTR_FILEFREE) {
        gFreeFunc(data);
    }
    if (arg1 & HU3D_ATTR_STATIC) {
        Hu3DCurAttr = modelP->attr;
        MakeDisplayList(hmf);
    }
    hmf->unk0B = 1;
    if (arg1 & HU3D_ATTR_DYNAMICFREE) {
        for (var_a0 = 0; var_a0 < hmf->unk10; var_a0++) {
            if (hmf->unk60[var_a0].unk50 & 0x06000000) {
                break;
            }
        }
        if (var_a0 == hmf->unk10) {
            HuMemFreeAllWithTag(Hu3DModelDataTag);
        }
    }
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 =
                            modelP->motShapeTime =
                                modelP->motShapeAttr =
                                    modelP->unk60 = 0;
    modelP->motShapeSpeed = 1.0f;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShape = -1;
    modelP->motIdShift = -1;
    modelP->unk09 = -1;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->cameraBit = HU3D_CAM_ALL;
    modelP->unk00 = 0;
    modelP->unkB4 = 0;
    HuMtxIdentF(modelP->mtx);
    Hu3DModelNum++;
    return modelId;
}

s32 Hu3DModelLink(s16 linkMdlId) {
    HmfModel *modelP;
    s16 modelId;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (Hu3DData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(modelEntryOverStr);
        return -1;
    }
    modelP = &Hu3DData[modelId];
    modelP->hmf = Hu3DData[linkMdlId].hmf;
    modelP->attr = Hu3DData[linkMdlId].attr;
    modelP->unk00 = Hu3DData[linkMdlId].unk00;
    modelP->unk10 = Hu3DData[linkMdlId].unk10;
    modelP->motId = Hu3DData[linkMdlId].motId;
    modelP->hmf->unk0B++;
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 =
                            modelP->motShapeTime =
                                modelP->motShapeAttr =
                                    modelP->unk60 = 0;
    modelP->motShapeSpeed = 1.0f;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShape = -1;
    modelP->motIdShift = -1;
    modelP->unk09 = -1;
    modelP->unk08 = -1;
    modelP->unkB4 = 0;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    modelP->cameraBit = HU3D_CAM_ALL;
    HuMtxIdentF(modelP->mtx);
    Hu3DModelNum++;
    return modelId;
}

s32 Hu3DModelDLCreate(u32 flags, void *dl, s32 mode) {
    HmfModel *modelP;
    HmfData *hmf;
    s16 modelId;

    for (modelId = 0; modelId < HU3D_MODEL_MAX; modelId++) {
        if (Hu3DData[modelId].hmf == NULL) {
            break;
        }
    }
    if (modelId == HU3D_MODEL_MAX) {
        osSyncPrintf(modelEntryOverStr);
        return -1;
    }
    Hu3DModelDataTag = TAG_MODEL + modelId * 2;
    Hu3DModelTag = TAG_MODEL + 1 + modelId * 2;
    modelP = &Hu3DData[modelId];
    hmf = modelP->hmf = HuMemAllocTag(sizeof(HmfData), Hu3DModelTag);
    hmf->unk0E = Hu3DModelDataTag;
    hmf->unk3C = dl;
    hmf->unk0B = 1;
    hmf->unk00 = (flags >> HU3D_ATTR_LAYER_SHIFT) & 7;
    modelP->hookFunc = NULL;
    modelP->hmf->unk98 = NULL;
    modelP->unk08 = 0xFF;
    modelP->attr = flags | HU3D_ATTR_STATIC;
    modelP->motTime =
        modelP->motAttr =
            modelP->unk48 =
                modelP->motShiftTime =
                    modelP->motShiftAttr =
                        modelP->unk54 = 0;
    modelP->motShiftSpeed = 1.0f;
    modelP->motSpeed = 1.0f;
    modelP->motIdShift = 0xFF;
    modelP->motId = 0xFF;
    modelP->unk09 = 0xFF;
    modelP->unkB4 = NULL;
    modelP->pos.x = modelP->pos.y = modelP->pos.z = 0.0f;
    modelP->rot.x = modelP->rot.y = modelP->rot.z = 0.0f;
    modelP->scale.x = modelP->scale.y = modelP->scale.z = 1.0f;
    switch (mode & 6) {
        case 4:
            HuMtxIdentF(modelP->mtx);
            hmf->unk3C = HuMemAllocTag(4, Hu3DModelTag);
            hmf->unk3C->unk00[0] = dl;
            hmf->unk60 = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk60_Struct), Hu3DModelTag);
            hmf->unk10 = 1;
            hmf->unk14 = 1;
            hmf->unk38 = NULL;
            hmf->unkC8 = NULL;
            hmf->unk60->unk50 = 0;
            hmf->unk60->unk20 = -1;
            hmf->unk60->unk5C = (HmfData_Unk84_Entry *)-1;
            hmf->unk60->unk60 = NULL;
            hmf->unkB4 = NULL;
            hmf->unk0A = 0;
            hmf->unkD4 = mtxRotCat;
            hmf->unkD8 = HuRotateRPYF;
            hmf->unk60->boundsMin[0] = hmf->unk60->boundsMin[1] = hmf->unk60->boundsMin[2] = -0x8000;
            hmf->unk60->boundsMax[0] = hmf->unk60->boundsMax[1] = hmf->unk60->boundsMax[2] = -0x8000;
        case 0:
        case 2:
            modelP->cameraBit = HU3D_CAM_ALL;
            break;
        case 6:
            modelP->cameraBit = HU3D_CAM_NONE;
            break;
    }
    modelP->unk00 = mode | 1;
    Hu3DModelNum++;
    return modelId;
}
s16 Hu3DModelLinkModeSet(s16 arg0, s8 arg1) {
    s16 idx = Hu3DModelLink(arg0);

    if (idx < 0) {
        return -1;
    }
    Hu3DData[idx].unk00 = arg1;
    return idx;
}

void Hu3DModelModeSet(s16 arg0, s32 arg1) {
    HmfModel *model = &Hu3DData[arg0];
    u8 flags = (model->unk00 & 0xF9) | 1;
    u8 newFlags = arg1 | flags;

    model->unk00 = newFlags;
    if ((arg1 & 0xFF) == 6) {
        model->cameraBit = HU3D_CAM_NONE;
    } else {
        model->cameraBit = HU3D_CAM_ALL;
    }
}

s32 Hu3DHookFuncCreate(s32 arg0, void (*arg1)(Gfx **, s32, s32), u8 arg2) {
    s16 idx = Hu3DModelDLCreate(arg0, NULL, arg2);
    HmfModel *var_v1 = &Hu3DData[idx];

    var_v1->hookFunc = arg1;
    return idx;
}

void Hu3DModelKill(s16 idx) {
    HmfData *hmf;
    s16 i;

    if (Hu3DData[idx].hmf == NULL) {
        return;
    }
    Hu3DModelNum--;
    if (Hu3DData[idx].unk09 != 0xFF && Hu3DData[idx].unk14 != 0.0f) {
        hmf = Hu3DData[idx].unk6C;
    } else {
        hmf = Hu3DData[idx].hmf;
    }
    Hu3DData[idx].hmf = NULL;
    if (Hu3DData[idx].unk00 & 1) {
        if (--hmf->unk0B == 0) {
            HuMemDelayFreeAllWithTag(hmf->unk0E);
            HuMemDelayFreeAllWithTag(hmf->unk0E + 1);
        }
        return;
    }
    if (Hu3DData[idx].unk00 != 0) {
        return;
    }
    if (--hmf->unk0B != 0) {
        return;
    }
    if (hmf->unkBC != NULL) {
        for (i = 0; i < 6; i++) {
            if (gCameraList[i].unk4 == idx) {
                gCameraList[i].unk4 = -1;
                break;
            }
        }
    }
    HuMemDelayFreeAllWithTag(hmf->unk0E);
    HuMemDelayFreeAllWithTag(hmf->unk0E + 1);
    Hu3DTexRelease(hmf);
    if (hmf->unk38 != NULL) {
        MapCollKill(Hu3DData[idx].unk10);
    }
    if (Hu3DData[idx].unk08 != 0xFF) {
        Hu3DShapeKill(Hu3DData[idx].unk08);
    }
    if (hmf->unkC8 != NULL) {
        for (i = 0; i < hmf->unk2A; i++) {
            Hu3DAnimKill(hmf->unkC8[i]);
        }
    }
    HuMemDelayFree(hmf);
    if (Hu3DData[idx].motId != 0xFF) {
        Hu3DMotionKill((s16)Hu3DData[idx].motId);
    }
}
void Hu3DAllKill(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (Hu3DData[i].hmf != NULL) {
            Hu3DModelKill(i);
        }
    }
    Hu3DTexAllKill();
    Hu3DAnimAllKill();
    Hu3DShapeAllKill();
    MapCollAllKill();
    Hu3DMotionAllKill();
    Hu3DFogClear();
    Hu3DLayerHook[0] = Hu3DLayerHook[1] = 0;
    Hu3DMotionGlobalSpeedSet(1.0f);
    Hu3DLightModeSet(1);
    EffectGroupInit();
}

void Hu3DExec(void *arg0, u16 arg1) {
    HuMtx4F mtx;
    HuMtx4F scaleMtx;
    HuMtx4F camMtx;
    HmfModel *model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *bc;
    Gfx *bgDl;
    Gfx *gfxStart;
    Gfx *gfx;
    s32 mask;
    s32 sample;
    s32 count;
    s32 i;
    s32 group;

    mask = 1;
    gfxStart = NULL;
    if (Hu3DDrawEnableF == 0) {
        return;
    }
    gSPEndDisplayList(gMainGfxPos++);
    Hu3DDLModelNum[0] = Hu3DDLModelNum[1] = Hu3DDLModelNum[2] = Hu3DDLModelNum[3] = 0;
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        model = &Hu3DData[i];
        if (model->hmf != NULL && !(model->attr & HU3D_ATTR_DISPOFF) && model->unk00 != 0) {
            group = (model->unk00 & 6) >> 1;
            Hu3DDLModelList[group][Hu3DDLModelNum[group]] = i;
            Hu3DDLModelNum[group]++;
        }
    }
    bgDl = Hu3DGfxStart;
    Hu3DLayerNo = 0;
    for (Hu3DCameraNo = 0; Hu3DCameraNo < Hu3DCameraNum; Hu3DCameraNo++) {
        if (bgDl == NULL) {
            gfxStart = Hu3DDLModelDraw(gfxStart, 1, mask);
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            HuGfxTaskSend(gfxStart, Hu3DLayerNo, 0, NULL, 0);
        }
        Hu3DDrawListInit();
        Hu3DCurCamera = &gCameraList[Hu3DCameraNo];
        Hu3DCurCamMtx = &Hu3DCurCamera->mtxs[Hu3DCamMtxNo];
        gfxStart = gMainGfxPos;
        if (Hu3DCurCamera->unk4 != -1) {
            Hu3DCameraMotionExec(Hu3DCameraNo);
        }
        Hu3DCameraSet(Hu3DCameraNo, &gMainGfxPos);
        Hu3DCameraScissorDraw(Hu3DCameraNo, &gMainGfxPos);
        mask = 1 << (s16)Hu3DCameraNo;
        gSPDisplayList(gMainGfxPos++, Hu3DExecInitGfx);
        gSPEndDisplayList(gMainGfxPos++);
        gfx = gMainGfxPos;
        if (bgDl != NULL) {
            gSPDisplayList(gMainGfxPos++, bgDl);
        }
        Hu3DCameraScissorDraw(Hu3DCameraNo, &gMainGfxPos);
        if (Hu3DCurCamera->unkA8 != NULL) {
            Hu3DCurCamera->unkA8(Hu3DCameraNo);
        }
        if (Hu3DLayerHook[0] != NULL) {
            Hu3DLayerHook[0](&gMainGfxPos, Hu3DCurCamMtx, Hu3DCameraNo);
        }
        if (Hu3DLayerHook[1] != NULL) {
            Hu3DLayerHook[1](&gMainGfxPos, Hu3DCurCamMtx, Hu3DCameraNo);
        }
        gfx = Hu3DDLModelDraw(gfx, 0, mask);
        gSPEndDisplayList(gMainGfxPos++);
        sample = HuProfCpuBegin(200, 255, 0);
        count = Hu3DModelNum;
        for (i = 0; count != 0; i++) {
            model = &Hu3DData[i];
            if (model->hmf == NULL) {
                continue;
            }
            count--;
            if (model->attr & HU3D_ATTR_REMAKESTATIC) {
                Hu3DModelRemakeStatic(i);
            }
            hmf = model->hmf;
            if (Hu3DCameraNo == 0) {
                hmf->unk0C = 0;
            }
            if (model->attr & HU3D_ATTR_DISPOFF) {
                continue;
            }
            if (!(model->cameraBit & mask)) {
                continue;
            }
            if (model->unk00 != 0 && (model->unk00 & 6) != 4) {
                continue;
            }
            if (hmf->unk38 != NULL && Hu3DCurCamera->unkA0 != NULL) {
                Hu3DCurCamera->unkA0(Hu3DCurCamera->unkA4, model);
                continue;
            }
            if (model->unk09 != 0xFF) {
                Hu3DModelLODExec(i);
            }
            if (model->attr & HU3D_ATTR_PARTICLE) {
                bc = model->unkBC;
                if ((!Hu3DPauseF || (model->attr & HU3D_ATTR_NOPAUSE)) && !(bc->unk04 & 2)) {
                    bc->unk18(i);
                }
                Hu3DParticleDraw(i, bc->unk00);
            }
            hmf->unk0A = 1;
            hmf->unk01 = model->unk00;
            Hu3DCurAttr = model->attr;
            if (!(model->attr & HU3D_ATTR_NOVIEW)) {
                guMtxL2F(camMtx, &Hu3DCurCamMtx->lookAtMtx);
                if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
                    mtxTransCat(camMtx, model->pos.x, model->pos.y, model->pos.z);
                }
                if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
                    mtxRotCat(camMtx, model->rot.x, model->rot.y, model->rot.z);
                }
                if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
                    mtxScaleCat(camMtx, model->scale.x, model->scale.y, model->scale.z);
                    scaleMtx[0][0] = model->scale.x;
                    scaleMtx[1][1] = model->scale.y;
                    scaleMtx[2][2] = model->scale.z;
                    scaleMtx[3][3] = 1.0f;
                    scaleMtx[0][1] = scaleMtx[0][2] = scaleMtx[0][3] = scaleMtx[1][0] = scaleMtx[1][2] =
                        scaleMtx[1][3] = scaleMtx[2][0] = scaleMtx[2][1] = scaleMtx[2][3] = scaleMtx[3][0] =
                            scaleMtx[3][1] = scaleMtx[3][2] = 0.0f;
                } else {
                    HuMtxIdentF(scaleMtx);
                }
                mtxCat(model->mtx, camMtx, mtx);
            } else {
                mtxCopy(mtx, model->mtx);
                if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
                    mtxTransCat(mtx, model->pos.x, model->pos.y, model->pos.z);
                }
                if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
                    mtxRotCat(mtx, model->rot.x, model->rot.y, model->rot.z);
                }
                if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
                    mtxScaleCat(mtx, model->scale.x, model->scale.y, model->scale.z);
                    scaleMtx[0][0] = model->scale.x;
                    scaleMtx[1][1] = model->scale.y;
                    scaleMtx[2][2] = model->scale.z;
                    scaleMtx[3][3] = 1.0f;
                    scaleMtx[0][1] = scaleMtx[0][2] = scaleMtx[0][3] = scaleMtx[1][0] = scaleMtx[1][2] =
                        scaleMtx[1][3] = scaleMtx[2][0] = scaleMtx[2][1] = scaleMtx[2][3] = scaleMtx[3][0] =
                            scaleMtx[3][1] = scaleMtx[3][2] = 0.0f;
                } else {
                    HuMtxIdentF(scaleMtx);
                }
            }
            hmf->unkD0 = model->unkB4;
            if (model->unkB4 != NULL) {
                Hu3DLLightSet(model->unkB4);
            }
            if (model->motId != 0xFF) {
                hmf->unk8C = &Hu3DMotion[model->motId];
                hmf->unkA0 = model->motTime;
                if (model->motIdShape != 0xFF) {
                    hmf->unk94 = &Hu3DMotion[model->motIdShape];
                    hmf->unkAC = model->motShapeTime;
                } else {
                    hmf->unk94 = NULL;
                }
                if (model->motIdShift != 0xFF) {
                    if (model->unk0C != 0) {
                        hmf->unk90 = &Hu3DMotion[model->motIdShift];
                        hmf->unkA4 = model->motShiftTime;
                        hmf->unkA8 = (f32)model->unk0E / model->unk0C;
                        if (!Hu3DPauseF) {
                            model->unk0E += arg1;
                        }
                        if (model->unk0E >= model->unk0C) {
                            model->motId = model->motIdShift;
                            model->motTime = model->motShiftTime;
                            model->motAttr = model->motShiftAttr;
                            model->unk48 = model->unk54;
                            model->motIdShift = 0xFF;
                        }
                    } else {
                        hmf->unk90 = NULL;
                    }
                } else {
                    hmf->unk90 = NULL;
                }
            } else {
                hmf->unk8C = hmf->unk90 = hmf->unk94 = NULL;
            }
            if (Hu3DCurAttr & HU3D_ATTR_HOOK) {
                HuMtxL2F(mtx, DrawObjData[Hu3DDrawList[model->unk68->unk00][model->unk68->unk60[model->unk0A].unk1D].objectIndex].fixedMtx);
            }
            Hu3DDraw(hmf, mtx, scaleMtx);
            hmf->unk0C++;
            if (model->unk08 != 0xFF || hmf->unkB4 != NULL) {
                Hu3DShapeExec(model, model->motTime);
            }
            if (hmf->unk98 != NULL) {
                SetObjMatMotion(hmf);
            }
            if (hmf->unkC8 != NULL) {
                Hu3DMotionExecAnim(model);
            }
        }
        HuProfCpuEnd(sample);
        bgDl = NULL;
        gfxStart = Hu3DDrawLayer(Hu3DCameraNo, gfxStart, gfx);
        if (Hu3DCurCamera->unkAC != NULL) {
            Hu3DCurCamera->unkAC(Hu3DCameraNo);
        }
    }
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        model = &Hu3DData[i];
        if (model->hmf == NULL || (model->attr & HU3D_ATTR_DISPOFF)) {
            continue;
        }
        if (Hu3DPauseF && !(model->attr & HU3D_ATTR_NOPAUSE)) {
            continue;
        }
        if (model->motId == 0xFF) {
            continue;
        }
        Hu3DMotionNext(model, arg1);
        if (model->hmf->unk98 != NULL && model->unk00 == 0) {
            model->hmf->unk98->unk08 = model->motTime;
        }
    }
    if (!Hu3DPauseF) {
        Hu3DAnimExec(arg1);
    }
    gfxStart = Hu3DDLModelDraw(gfxStart, 1, mask);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    gfxStart = Hu3DDLModelDraw(gfxStart, 3, 0);
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    WipeExecAlways(&gMainGfxPos);
    gMainGfxPos = pfDrawFonts(gMainGfxPos);
    gDPFullSync(gMainGfxPos++);
    gSPEndDisplayList(gMainGfxPos++);
    HuGfxTaskSend(gfxStart, Hu3DLayerNo, 1, arg0, 0x309);
    Hu3DExecCnt++;
}

Gfx *Hu3DDLModelDraw(Gfx *arg0, s16 arg1, u16 arg2) {
    s16 i;

    for (i = 0; i < Hu3DDLModelNum[arg1]; i++) {
        HmfModel *temp_s0 = &Hu3DData[Hu3DDLModelList[arg1][i]];

        if (!(temp_s0->cameraBit & arg2) && arg2 != 0) {
            continue;
        }
        Hu3DDLModelId = Hu3DDLModelList[arg1][i];
        if (temp_s0->hmf->unk00 != Hu3DLayerNo) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            HuGfxTaskSend(arg0, Hu3DLayerNo, 0, NULL, 0);
            Hu3DLayerNo = temp_s0->hmf->unk00;
            arg0 = gMainGfxPos;
        }
        if (temp_s0->hookFunc != NULL) {
            temp_s0->hookFunc(&gMainGfxPos, (s32)Hu3DCurCamMtx, (s32)Hu3DCurCamera);
        } else if (temp_s0->hmf->unk3C != NULL) {
            gSPDisplayList(gMainGfxPos++, temp_s0->hmf->unk3C);
        }
    }
    return arg0;
}

void Hu3DModelAllReset(void) {
    s16 i;

    HuMemSetDirty();
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        Hu3DData[i].hmf = NULL;
    }
    gCameraList = NULL;
    Hu3DCameraNum = 0;
    Hu3DBufNo = 0;
    Hu3DDrawEnableF = 0;
}

void Hu3DScreenClear(u32 arg0, u32 arg1) {
    gSPSegment(gMainGfxPos++, 0x00, 0x00000000);
    gSPDisplayList(gMainGfxPos++, scrClearGfx0);
    gDPSetDepthImage(gMainGfxPos++, arg1);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg1);
    gSPDisplayList(gMainGfxPos++, scrClearGfx1);
    gDPSetColorImage(gMainGfxPos++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, arg0);
    if (Hu3DScreenClearF != 0) {
        gDPSetFillColor(gMainGfxPos++, PACK_FILL_COLOR(Hu3DBGColR, Hu3DBGColG, Hu3DBGColB, 1));
        gSPDisplayList(gMainGfxPos++, scrClearGfx2);
    }
}

void Hu3DModelPosSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && Hu3DData[idx].hmf != NULL) {
        Hu3DData[idx].pos.x = x;
        Hu3DData[idx].pos.y = y;
        Hu3DData[idx].pos.z = z;
    }
}

void Hu3DModelPosGet(s16 idx, Vec *arg1) {
    arg1->x = Hu3DData[idx].pos.x;
    arg1->y = Hu3DData[idx].pos.y;
    arg1->z = Hu3DData[idx].pos.z;
}

void Hu3DModelRotSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && Hu3DData[idx].hmf != NULL) {
        Hu3DData[idx].rot.x = x;
        Hu3DData[idx].rot.y = y;
        Hu3DData[idx].rot.z = z;
    }
}

void Hu3DModelScaleSet(s16 idx, f32 x, f32 y, f32 z) {
    if (idx >= 0 && Hu3DData[idx].hmf != NULL) {
        Hu3DData[idx].scale.x = x;
        Hu3DData[idx].scale.y = y;
        Hu3DData[idx].scale.z = z;
    }
}

void Hu3DModelAllAttrSet(s16 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        Hu3DModelAttrSet(i, arg0, arg1);
    }
}

void Hu3DModelAttrSet(s16 idx, s32 arg1, s32 arg2) {
    HmfModel *model = &Hu3DData[idx];

    if (model->hmf != NULL) {
        if (arg1 & HU3D_ATTR_REMAKE_MASK) {
            arg2 |= HU3D_ATTR_REMAKESTATIC;
        }
        if (arg1 & HU3D_ATTR_LAYER_MASK) {
            Hu3DModelLayerSet(idx, arg2 & HU3D_ATTR_LAYER_MASK);
        }
        model->attr &= ~arg1;
        model->attr |= arg2;
    }
}

void Hu3DModelObjAttrSet(s16 idx, s32 arg1, s32 arg2) {
    HmfData *temp_a3 = Hu3DData[idx].hmf;
    s16 var_t0;

    for (var_t0 = 0; var_t0 < temp_a3->unk10; var_t0++) {
        temp_a3->unk60[var_t0].unk50 &= ~arg1;
        temp_a3->unk60[var_t0].unk50 |= arg2;
    }
}

void Hu3DModelObjAttrSetByName(s16 idx, char *name, s32 arg2, s32 arg3) {
    HmfData *temp_s0 = Hu3DData[idx].hmf;
    s16 temp_v0 = SearchObjectIndex(temp_s0, name);

    if (temp_v0 >= 0) {
        temp_s0->unk60[temp_v0].unk50 &= ~arg2;
        temp_s0->unk60[temp_v0].unk50 |= arg3;
    }
}

void Hu3DModelRemakeStatic(s16 arg0) {
    Hu3DModelAttrSet(arg0, HU3D_ATTR_REMAKESTATIC | HU3D_ATTR_STATIC, HU3D_ATTR_STATIC);
    Hu3DCurAttr = Hu3DData[arg0].attr;

    if (Hu3DCurAttr & HU3D_ATTR_DYNAMICFREE) {
        osSyncPrintf("RemakeStatic Error! Executed DynamicFree already!\n");
        HuDbgStatus = 0x10002;
        return;
    }

    if (RemakeDisplayList(Hu3DData[arg0].hmf) != NULL) {
        Hu3DModelVtxBufMake(arg0);
    }
}

void Hu3DModelDynamicFree(s16 idx) {
    if (Hu3DData[idx].hmf->unk0A != 0) {
        HuMemDelayFreeAllWithTag(Hu3DData[idx].hmf->unk0E);
    } else {
        HuMemFreeAllWithTag(Hu3DData[idx].hmf->unk0E);
    }
    Hu3DModelAttrSet(idx, HU3D_ATTR_DYNAMICFREE, HU3D_ATTR_DYNAMICFREE);
}

void Hu3DMotionModelSet(s16 idx, s16 arg1) {
    HmfModel *model = &Hu3DData[idx];

    model->motId = Hu3DData[arg1].motId;
    model->motAttr = 0;
    model->unk48 = model->motTime = 0.0f;
    model->motSpeed = 1.0f;
    model->motIdShift = 0xFF;
}

void Hu3DMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfModel *temp_a0;

    temp_a0 = &Hu3DData[arg0];
    if (temp_a0->motIdShift != 0xFF) {
        temp_a0->motId = temp_a0->motIdShift;
        temp_a0->motTime = temp_a0->motShiftTime;
        temp_a0->motAttr = temp_a0->motShiftAttr;
        temp_a0->unk48 = temp_a0->unk54;
    }
    temp_a0->motIdShift = (u8)arg1;
    temp_a0->motShiftTime = arg2;
    temp_a0->unk0E = (u16)0;
    temp_a0->unk0C = arg3;
    temp_a0->motShiftAttr = (u8)arg4;
    temp_a0->unk54 = 0.0f;
}

void Hu3DMotionTimeSet(s16 arg0, f32 arg1) {
    HmfModel *model = &Hu3DData[arg0];

    if (Hu3DMotion[model->motId].unk02 < arg1) {
        model->motTime = Hu3DMotion[model->motId].unk02;
    } else {
        model->motTime = arg1;
    }
}

f32 Hu3DMotionShapeTimeGet(s16 arg0) {
    if (Hu3DData[arg0].motShapeTime < 0.0f) {
        return 0.0f;
    }
    return Hu3DData[arg0].motShapeTime;
}

f32 Hu3DMotionShapeMaxTimeGet(s16 arg0) {
    if (Hu3DData[arg0].motShapeTime < 0.0f) {
        return 0.0f;
    }
    return Hu3DMotion[Hu3DData[arg0].motIdShape].unk02;
}

f32 Hu3DMotionShiftTimeGet(s16 idx) {
    if (Hu3DData[idx].motIdShift == 0xFF) {
        return -1.0f;
    }
    return Hu3DData[idx].motShiftTime;
}

void Hu3DMotionAttrSet(s16 idx, s16 arg1, s16 arg2) {
    HmfModel *temp_a3 = &Hu3DData[idx];

    temp_a3->motAttr &= ~arg1;
    temp_a3->motAttr |= arg2;
    if (temp_a3->hmf->unk98 != NULL) {
        temp_a3->hmf->unk98->unk02 &= ~arg1;
        temp_a3->hmf->unk98->unk02 |= arg2;
    }
    if (temp_a3->motIdShift != 0xFF) {
        temp_a3->motShiftAttr &= ~arg1;
        temp_a3->motShiftAttr |= arg2;
    }
}

void Hu3DModelCameraSet(s16 idx, s16 arg1) {
    if (idx >= 0 && Hu3DData[idx].hmf != NULL) {
        Hu3DData[idx].cameraBit = arg1;
    }
}

void Hu3DModelLayerSet(s16 idx, u32 arg1) {
    Hu3DData[idx].attr &= ~HU3D_ATTR_LAYER_MASK;
    Hu3DData[idx].attr |= arg1;
    Hu3DData[idx].hmf->unk00 = (arg1 >> HU3D_ATTR_LAYER_SHIFT) & 7;
}

void Hu3DMotionSpeedSet(s16 idx, f32 arg1) {
    HmfModel *model = &Hu3DData[idx];
    model->motSpeed = arg1;
}

void Hu3DModelVtxBufMake(s16 idx) {
    HmfData *hmf = Hu3DData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    s16 count;
    s16 i;
    s16 j;

    for (i = 0; i < Hu3DBufNum; i++) {
        src = hmf->unk40;
        if (hmf->unk44[i] == src) {
            count = hmf->unk18;
            dst = hmf->unk44[i] = HuMemAllocTag(count * sizeof(Vtx), hmf->unk0E + 1);
            for (j = 0; j < count; j++) {
                dst->v = src->v;
                src++;
                dst++;
            }
        }
    }
}
void Hu3DModelVtxMorph(s16 idx1, s16 idx2, f32 t) {
    HmfData *hmf = Hu3DData[idx1].hmf;
    Vtx_tn *src1 = (Vtx_tn *)hmf->unk40;
    Vtx_tn *src2 = (Vtx_tn *)Hu3DData[idx2].hmf->unk40;
    Vtx_tn *dst = (Vtx_tn *)hmf->unk44[Hu3DBufNo];
    s16 count;
    s16 i;

    count = hmf->unk18;
    for (i = 0; i < count; i++) {
        *dst = *src1;
        if (src1->ob[0] != src2->ob[0] || src1->ob[1] != src2->ob[1] || src1->ob[2] != src2->ob[2]) {
            dst->ob[0] = src1->ob[0] * t + src2->ob[0] * (1.0f - t);
            dst->ob[1] = src1->ob[1] * t + src2->ob[1] * (1.0f - t);
            dst->ob[2] = src1->ob[2] * t + src2->ob[2] * (1.0f - t);
            dst->n[0] = src1->n[0] * t + src2->n[0] * (1.0f - t);
            dst->n[1] = src1->n[1] * t + src2->n[1] * (1.0f - t);
            dst->n[2] = src1->n[2] * t + src2->n[2] * (1.0f - t);
        }
        src1++;
        src2++;
        dst++;
    }
}
void Hu3DModelObjVtxMorph(s16 idx1, s16 idx2, f32 arg2, char *name, s32 arg4) {
    HmfData *hmf1 = Hu3DData[idx1].hmf;
    HmfData *hmf2 = Hu3DData[idx2].hmf;
    s16 node1 = SearchObjectIndex(hmf1, name);
    s16 node2 = SearchObjectIndex(hmf2, name);

    if (node1 == -1 || node2 == -1) {
        return;
    }
    HmfObjVtxMorph(hmf1, hmf2, arg2, node1, node2, arg4);
}
void Hu3DModelObjVtxMorph2(s16 idx1, s16 idx2, f32 arg2, char *name1, char *name2, s32 arg5) {
    HmfData *hmf1 = Hu3DData[idx1].hmf;
    HmfData *hmf2 = Hu3DData[idx2].hmf;
    s16 node1 = SearchObjectIndex(hmf1, name1);
    s16 node2 = SearchObjectIndex(hmf2, name2);

    if (node1 == -1 || node2 == -1) {
        return;
    }
    HmfObjVtxMorph(hmf1, hmf2, arg2, node1, node2, arg5);
}
void HmfObjVtxMorph(HmfData *hmf1, HmfData *hmf2, f32 t, s16 node1, s16 node2, s32 full) {
    Vtx_tn *src1;
    Vtx_tn *src2;
    Vtx_tn *dst;
    s16 start = 0;
    s16 count;
    s16 i;

    if (full) {
        src1 = (Vtx_tn *)hmf1->unk40;
        dst = (Vtx_tn *)hmf1->unk44[Hu3DBufNo];
        start = hmf1->unk60[node1].unk28;
        for (i = 0; i < start; i++) {
            *dst = *src1;
            src1++;
            dst++;
        }
    }
    src1 = (Vtx_tn *)&hmf1->unk40[hmf1->unk60[node1].unk28];
    src2 = (Vtx_tn *)&hmf2->unk40[hmf2->unk60[node2].unk28];
    dst = (Vtx_tn *)&hmf1->unk44[Hu3DBufNo][hmf1->unk60[node1].unk28];
    count = hmf1->unk60[node1].unk2A;
    for (i = 0; i < count; i++) {
        *dst = *src1;
        if (src1->ob[0] != src2->ob[0] || src1->ob[1] != src2->ob[1] || src1->ob[2] != src2->ob[2]) {
            dst->ob[0] = src1->ob[0] * t + src2->ob[0] * (1.0f - t);
            dst->ob[1] = src1->ob[1] * t + src2->ob[1] * (1.0f - t);
            dst->ob[2] = src1->ob[2] * t + src2->ob[2] * (1.0f - t);
            dst->n[0] = src1->n[0] * t + src2->n[0] * (1.0f - t);
            dst->n[1] = src1->n[1] * t + src2->n[1] * (1.0f - t);
            dst->n[2] = src1->n[2] * t + src2->n[2] * (1.0f - t);
        }
        src1++;
        src2++;
        dst++;
    }
    if (full) {
        start += count;
        count = hmf1->unk18;
        for (i = start; i < count; i++) {
            *dst = *src1;
            src1++;
            dst++;
        }
    }
}
void Hu3DMotionSpeedMulSet(s16 mul) {
    Hu3DMotionSpeedMul = mul;
}

void *Hu3DModelObjPtrGet(s16 idx, const char *name) {
    HmfData *hmf = Hu3DData[idx].hmf;
    s16 node = SearchObjectIndex(hmf, name);
    s16 count;
    s16 i;
    s16 j;

    if (hmf->unk80 != (HmfMotionNode *)-1) {
        for (i = 0; i < hmf->unk16; i++) {
            count = hmf->unk80[i].unk00;
            for (j = 0; j < count; j++) {
                if (hmf->unk80[i].unk50[j] == node) {
                    break;
                }
            }
            if (j != count) {
                break;
            }
        }
        if (i == hmf->unk16) {
            return (void *)-1;
        }
        return &hmf->unk80[i];
    } else {
        for (i = 0; i < hmf->unk64; i++) {
            if (hmf->unk68[i].unk00 == node) {
                break;
            }
        }
        if (i == hmf->unk64) {
            return (void *)-1;
        }
        return &hmf->unk68[i];
    }
}
void Hu3DModelVtxWave(s16 idx, f32 arg1, f32 arg2, s32 mode) {
    HmfData *hmf = Hu3DData[idx].hmf;

    if (hmf != NULL) {
        switch (mode & 0xF) {
            case 0:
                HmfVtxWave0(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
            case 1:
                HmfVtxWave1(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
            case 2:
                HmfVtxWave2(hmf, arg1, arg2, 0, hmf->unk1A);
                break;
        }
    }
}
void Hu3DModelObjVtxWave(s16 idx, f32 arg1, f32 arg2, char *name, s16 mode) {
    HmfData *hmf = Hu3DData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    node = SearchObjectIndex(hmf, name);
    if (node == -1) {
        return;
    }
    if (mode & 0x80) {
        src = hmf->unk40;
        dst = hmf->unk44[Hu3DBufNo];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = src->v;
            src++;
            dst++;
        }
    }
    switch (mode & 0xF) {
        case 0:
            HmfVtxWave0(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
        case 1:
            HmfVtxWave1(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
        case 2:
            HmfVtxWave2(hmf, arg1, arg2, hmf->unk60[node].unk2C, hmf->unk60[node].unk2E);
            break;
    }
}
void HmfVtxWave0(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 n;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++, group++) {
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale;
        sy = cy * scale;
        sz = cz * scale;
        n = group->count & 0x7F;
        indices = group->indices;
        for (j = 0; j < n; j++, indices++) {
            src = &hmf->unk40[*indices];
            dst = &hmf->unk44[Hu3DBufNo][*indices];
            dst->v.ob[0] = (src->v.ob[0] - cx) * inv + sx;
            dst->v.ob[1] = (src->v.ob[1] - cy) * inv + sy;
            dst->v.ob[2] = (src->v.ob[2] - cz) * inv + sz;
        }
    }
}
void HmfVtxWave1(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    f32 jitter[8] = { 0.0f, -0.1f, 0.5f, 0.8f, -0.2f, 0.1f, 0.3f, -0.3f };
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 n;
    s16 i;
    s16 j;

    for (i = 0; i < count; i++, group++) {
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale + cx * (1.0f - scale) * jitter[i & 7];
        sy = cy * scale + cy * (1.0f - scale) * jitter[i & 7];
        sz = cz * scale + cz * (1.0f - scale) * jitter[i & 7];
        n = group->count & 0x7F;
        indices = group->indices;
        for (j = 0; j < n; j++, indices++) {
            src = &hmf->unk40[*indices];
            dst = &hmf->unk44[Hu3DBufNo][*indices];
            dst->v.ob[0] = (src->v.ob[0] - cx) * inv + sx;
            dst->v.ob[1] = (src->v.ob[1] - cy) * inv + sy;
            dst->v.ob[2] = (src->v.ob[2] - cz) * inv + sz;
        }
    }
}

void HmfVtxWave2(HmfData *hmf, f32 t, f32 scale, u16 start, u16 count) {
    f32 sinTbl[4];
    f32 cosTbl[4];
    f32 jitter[8] = { 0.0f, -0.1f, 0.5f, 0.8f, -0.2f, 0.1f, 0.3f, -0.3f };
    HmfVertexGroup *group = &hmf->unkB0[start];
    f32 inv = 1.0f - t;
    f32 s;
    f32 c;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 *indices;
    Vtx *src;
    Vtx *dst;
    s16 cx;
    s16 cy;
    s16 cz;
    s16 sx;
    s16 sy;
    s16 sz;
    s16 nx;
    s16 ny;
    s16 nz;
    s16 n;
    s16 i;
    s16 j;

    sinTbl[0] = sindf(Hu3DVtxWaveAngle);
    cosTbl[0] = cosdf(Hu3DVtxWaveAngle);
    sinTbl[1] = sindf(-Hu3DVtxWaveAngle / 2.0f);
    cosTbl[1] = cosdf(-Hu3DVtxWaveAngle / 2.0f);
    sinTbl[2] = sindf(Hu3DVtxWaveAngle / 2.0f);
    cosTbl[2] = cosdf(Hu3DVtxWaveAngle / 2.0f);
    sinTbl[3] = sindf(-Hu3DVtxWaveAngle);
    cosTbl[3] = cosdf(-Hu3DVtxWaveAngle);
    for (i = 0; i < count; i++, group++) {
        s = sinTbl[i & 3];
        c = cosTbl[i & 3];
        cx = group->center.x;
        cy = group->center.y;
        cz = group->center.z;
        sx = cx * scale + cx * (1.0f - scale) * jitter[i & 7];
        sy = cy * scale + cy * (1.0f - scale) * jitter[i & 7];
        sz = cz * scale + cz * (1.0f - scale) * jitter[i & 7];
        n = group->count & 0x7F;
        indices = group->indices;
        nx = group->normal[0];
        if (nx < 0) {
            nx = -nx;
        }
        ny = group->normal[1];
        if (ny < 0) {
            ny = -ny;
        }
        nz = group->normal[2];
        if (nz < 0) {
            nz = -nz;
        }
        if (nx > ny && nx > nz) {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[Hu3DBufNo][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = (dx * c + dy * s) * inv + sx;
                dst->v.ob[1] = (-dx * s + dy * c) * inv + sy;
                dst->v.ob[2] = dz * inv + sz;
            }
        } else if (ny > nz) {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[Hu3DBufNo][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = dx * inv + sx;
                dst->v.ob[1] = (dy * c + dz * s) * inv + sy;
                dst->v.ob[2] = (-dy * s + dz * c) * inv + sz;
            }
        } else {
            for (j = 0; j < n; j++, indices++) {
                src = &hmf->unk40[*indices];
                dst = &hmf->unk44[Hu3DBufNo][*indices];
                dx = src->v.ob[0] - cx;
                dy = src->v.ob[1] - cy;
                dz = src->v.ob[2] - cz;
                dst->v.ob[0] = (dx * c - dz * s) * inv + sx;
                dst->v.ob[1] = dy * inv + sy;
                dst->v.ob[2] = (dx * s + dz * c) * inv + sz;
            }
        }
    }
}
void Hu3DModelTexAnimChange(s16 idx, char *oldName, char *newName) {
    HmfData_Unk84_Entry2 *found = NULL;
    HmfData *hmf = Hu3DData[idx].hmf;
    u16 hash;
    s16 i;

    hash = HmfNameHash((u8 *)newName);
    for (i = 0; i < 128; i++) {
        if (Hu3DTexData[i].nameHash != 0 && Hu3DTexData[i].nameHash == hash &&
            strcmp(Hu3DTexData[i].name, newName) == 0) {
            found = &Hu3DTexData[i];
            break;
        }
    }
    hash = HmfNameHash((u8 *)oldName);
    for (i = 0; i < hmf->unk12; i++) {
        if (hmf->unk84[i].unkC->nameHash == hash) {
            hmf->unk84[i].unkC = found;
        }
    }
}
void Hu3DModelTexScroll(s16 idx, f32 x, f32 y, s32 width, s32 height) {
    HmfData *hmf = Hu3DData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    u16 w;
    u16 h;
    u16 s;
    u16 t;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    src = hmf->unk40;
    dst = hmf->unk44[Hu3DBufNo];
    count = hmf->unk18;
    w = width * 32;
    h = height * 32;
    s = x * 32.0f;
    t = y * 32.0f;
    if (x < 0.0f) {
        x = -x;
    }
    if (y < 0.0f) {
        y = -y;
    }
    if (x * 32.0f > w) {
        s %= w;
    }
    if (y * 32.0f > h) {
        t %= h;
    }
    for (i = 0; i < count; i++) {
        dst->v.tc[0] = src->v.tc[0] + s;
        dst->v.tc[1] = src->v.tc[1] + t;
        src++;
        dst++;
    }
}
void Hu3DModelObjTexScroll(s16 idx, f32 x, f32 y, u16 width, u16 height, const char *name, u8 reset) {
    HmfData *hmf = Hu3DData[idx].hmf;
    Vtx *src;
    Vtx *dst;
    u16 s;
    u16 t;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    if (reset) {
        src = hmf->unk40;
        dst = hmf->unk44[Hu3DBufNo];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = src->v;
            src++;
            dst++;
        }
    }
    node = SearchObjectIndex(hmf, name);
    count = hmf->unk60[node].unk2A;
    src = &hmf->unk40[hmf->unk60[node].unk28];
    dst = &hmf->unk44[Hu3DBufNo][hmf->unk60[node].unk28];
    width <<= 5;
    height <<= 5;
    s = x * 32.0f;
    t = y * 32.0f;
    if (x < 0.0f) {
        x = -x;
    }
    if (y < 0.0f) {
        y = -y;
    }
    if (x * 32.0f > width) {
        s %= width;
    }
    if (y * 32.0f > height) {
        t %= height;
    }
    for (i = 0; i < count; i++) {
        dst->v.tc[0] = src->v.tc[0] + s;
        dst->v.tc[1] = src->v.tc[1] + t;
        src++;
        dst++;
    }
}
void Hu3DModelObjVtxColorSet(s16 idx, char *name, u8 r, u8 g, u8 b, u8 reset) {
    HmfData *hmf = Hu3DData[idx].hmf;
    Vtx *vtx;
    Vtx *dst;
    s16 node;
    s16 count;
    s16 i;

    if (hmf == NULL) {
        return;
    }
    if (reset) {
        vtx = hmf->unk40;
        dst = hmf->unk44[Hu3DBufNo];
        count = hmf->unk18;
        for (i = 0; i < count; i++) {
            dst->v = vtx->v;
            vtx++;
            dst++;
        }
    }
    node = SearchObjectIndex(hmf, name);
    count = hmf->unk60[node].unk2A;
    vtx = &hmf->unk44[Hu3DBufNo][hmf->unk60[node].unk28];
    for (i = 0; i < count; i++) {
        vtx->v.cn[0] = r;
        vtx->v.cn[1] = g;
        vtx->v.cn[2] = b;
        vtx++;
    }
}
void Hu3DModelFaceFlip(s16 idx) {
    HmfData *hmf = Hu3DData[idx].hmf;
    HmfModelData_Unk64_Unk60_Struct *obj;
    HmfModelData_Unk64_Unk60_Unk54_Struct *face;
    s16 i;
    s16 j;
    s16 k;
    s16 n;
    s16 tmp;
    f32 ftmp;

    for (i = 0; i < hmf->unk10; i++) {
        obj = &hmf->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            face = &obj->unk54[j];
            n = face->unk00 & 0x7F;
            for (k = 0; k < n / 2; k++) {
                tmp = face->unk04[k];
                face->unk04[k] = face->unk04[n - k - 1];
                face->unk04[n - k - 1] = tmp;
                ftmp = face->unk0C[k];
                face->unk0C[k] = face->unk0C[n - k - 1];
                face->unk0C[n - k - 1] = ftmp;
                ftmp = face->unk1C[k];
                face->unk1C[k] = face->unk1C[n - k - 1];
                face->unk1C[n - k - 1] = ftmp;
            }
        }
    }
}
void Hu3DMotionShapeSet(s16 idx, s16 arg1, s16 arg2) {
    HmfModel *model = &Hu3DData[idx];
    f32 zero;

    model->motIdShape = arg1;
    zero = 0.0f;
    model->motShapeTime = zero;
    model->unk60 = zero;
    model->motShapeAttr = arg2;
    model->motShapeSpeed = 1.0f;
}

void Hu3DFogSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4) {
    Hu3DFogF = 1;
    Hu3DFogStart = arg0;
    Hu3DFogEnd = arg1;
    Hu3DFogColR = arg2;
    Hu3DFogColG = arg3;
    Hu3DFogColB = arg4;
}

void Hu3DFogClear(void) {
    Hu3DFogF = 0;
}

void Hu3DModelHookSet(s16 idx, s16 parentIdx, const char *name) {
    HmfData *hmf = Hu3DData[parentIdx].hmf;
    s16 node = SearchObjectIndex(hmf, name);

    Hu3DData[idx].unk68 = hmf;
    Hu3DData[idx].unk0A = node;
}

void Hu3DModelAnimNameSet(s16 idx, char *name) {
    HmfData *hmf = Hu3DData[idx].hmf;

    hmf->unk9C = Hu3DTexSearchName(hmf, name);
}

void Hu3DMotionNext(HmfModel *model, u16 speed) {
    model->motTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motId], model->motAttr,
                                        model->motTime, model->unk48, speed * model->motSpeed);
    if (model->motIdShift != 0xFF) {
        model->motShiftTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motIdShift],
                                                 model->motShiftAttr, model->motShiftTime, model->unk54, speed * model->motShiftSpeed);
    }
    if (model->motIdShape != 0xFF) {
        model->motShapeTime = Hu3DMotionTimeCalc(&Hu3DMotion[model->motIdShape],
                                                 model->motShapeAttr, model->motShapeTime, model->unk60, speed * model->motShapeSpeed);
    }
}
void Hu3DMotionExecAnim(HmfModel *model) {
    HmfData *hmf = model->hmf;
    s16 frame = model->motTime;
    s16 i;

    for (i = 0; i < hmf->unk2A; i++) {
        Hu3DAnimAttrSet(hmf->unkC8[i], 1, 1);
        Hu3DAnimTimeSet(hmf->unkC8[i], frame);
    }
}

s32 Hu3DMotionCreate(void *arg0, s32 arg1) {
    u8 *data = arg0;
    s16 ret;

    if (data[0] != 'M' || data[1] != 'T' || data[2] != 'N' || data[3] != 'X') {
        Hu3DModelDataTag = 0x2810;
        Hu3DModelTag = 0x2811;
        Hu3DMotionHmf.unk0E = 0x2810;
        LoadHMF(&Hu3DMotionHmf, data, (s16)arg1);
        ret = Hu3DMotionCreateSub((HmfMotionFile *)data, &Hu3DMotionHmf);
        HuMemFreeAllWithTag(Hu3DModelDataTag);
        HuMemFreeAllWithTag(Hu3DModelTag);
    } else {
        ret = Hu3DMotionCreateNoHmf((HmfMotionFile *)data);
    }
    if (arg1 & HU3D_ATTR_FILEFREE) {
        gFreeFunc(data);
    }
    return ret;
}

void Hu3DMotionSet(s16 arg0, s16 arg1) {
    HmfModel *temp_v0;

    temp_v0 = &Hu3DData[arg0];
    temp_v0->motId = arg1;
    temp_v0->motAttr = 0;
    temp_v0->unk48 =
        temp_v0->motTime = 0.0f;
    temp_v0->motSpeed = 1.0f;
    temp_v0->motIdShift = 0xFF;
}

f32 Hu3DMotionMotionMaxTimeGet(s16 arg0) {
    return Hu3DMotion[arg0].unk02;
}

void Hu3DBGColorSet(s32 r, s32 g, s32 b) {
    Hu3DBGColR = r;
    Hu3DBGColG = g;
    Hu3DBGColB = b;
}

void Hu3DMotionAttrSetEx(s16 idx, s16 flags, s16 clear, s16 set) {
    HmfModel *model = &Hu3DData[idx];

    if (flags & 1) {
        if (model->motId != 0xFF) {
            model->motAttr &= ~clear;
            model->motAttr |= set;
            if (flags & 2) {
                if (model->motIdShift != 0xFF) {
                    model->motShiftAttr &= ~clear;
                    model->motShiftAttr |= set;
                }
            }
            if (flags & 4) {
                if (model->motIdShape != 0xFF) {
                    model->motShapeAttr &= ~clear;
                    model->motShapeAttr |= set;
                }
            }
        }
    }
}

void Hu3DModelLODSet(s16 arg0, s16 arg1, f32 arg2) {
    HmfModel *model;

    model = &Hu3DData[arg0];
    model->unk09 = arg1;
    model->unk6C = model->hmf;
    model->unk14 = arg2;
    model = &Hu3DData[arg1];
    model->unk09 = arg0;
    model->unk6C = NULL;
    model->unk14 = 0.0f;
    model->attr |= HU3D_ATTR_DISPOFF;
}

void Hu3DModelLODExec(s16 idx) {
    HmfModel *model = &Hu3DData[idx];
    HmfData *hmf;
    f32 dx = Hu3DCurCamera->pos.x - model->pos.x;
    f32 dy = Hu3DCurCamera->pos.y - model->pos.y;
    f32 dz = Hu3DCurCamera->pos.z - model->pos.z;
    s16 i;

    if (model->unk14 < HuSqrtf(dx * dx + dy * dy + dz * dz)) {
        hmf = model->unk6C;
    } else {
        hmf = Hu3DData[model->unk09].hmf;
    }
    if (hmf != model->hmf) {
        model->hmf = hmf;
        for (i = 0; i < HU3D_MODEL_MAX; i++) {
            if (Hu3DData[i].hmf != NULL || (Hu3DData[i].attr & HU3D_ATTR_DISPOFF)) {
                continue;
            }
            if ((Hu3DData[i].attr & HU3D_ATTR_HOOK) &&
                (model->hmf == Hu3DData[i].unk68 || Hu3DData[model->unk09].hmf == Hu3DData[i].unk68)) {
                Hu3DData[i].unk68 = hmf;
            }
        }
    }
    Hu3DData[model->unk09].attr |= HU3D_ATTR_DISPOFF;
}
s32 Hu3DModelLODCheck(s16 arg0) {
    HmfModel *model = &Hu3DData[arg0];

    return model->hmf == Hu3DData[model->unk09].hmf;
}

void Hu3DDrawModeSet(s8 arg0) {
    Hu3DClipRatio = arg0;
}

void Hu3DModelPrimColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfData *hmf;

    hmf = Hu3DData[arg0].hmf;
    hmf->unk02[0] = arg1;
    hmf->unk02[1] = arg2;
    hmf->unk02[2] = arg3;
    hmf->unk02[3] = arg4;
}

void Hu3DModelEnvColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    HmfData *hmf;

    hmf = Hu3DData[arg0].hmf;
    hmf->unk02[4] = arg1;
    hmf->unk02[5] = arg2;
    hmf->unk02[6] = arg3;
    hmf->unk02[7] = arg4;
}

void Hu3DModelColorSet(s16 idx, u8 r, u8 g, u8 b, u8 a) {
    Hu3DModelPrimColorSet(idx, r, g, b, a);
    Hu3DModelEnvColorSet(idx, r * 0.5f, g * 0.5f, b * 0.5f, a * 0.5f);
}
void Hu3DLayerHookSet(s16 idx, void *func) {
    Hu3DLayerHook[idx] = func;
}

void Hu3DMotionModelSetEx(s16 arg0, s16 arg1) {
    Hu3DMotionModelSet(arg0, arg1);
    Hu3DData[arg0].unk08 = Hu3DData[arg1].unk08;
}

void Hu3DModelTPLvlSet(s16 arg0, u8 arg1) {
    HmfData *hmf = Hu3DData[arg0].hmf;
    s16 i;

    for (i = 0; i < hmf->unk10; i++) {
        hmf->unk60[i].unk20 = arg1;
    }
}

void Hu3DModelTPLvlInit(s16 idx) {
    HmfData *hmf = Hu3DData[idx].hmf;
    s16 i;

    Hu3DModelObjAttrSet(idx, 0x110000, 0x110000);
    for (i = 0; i < hmf->unk1E; i++) {
        hmf->unk88[i].unk0A = 0xFF;
        hmf->unk88[i].unk09 |= 5;
    }
    Hu3DModelRemakeStatic(idx);
}

void Hu3DLLightCreate(s16 arg0, s8 arg1) {
    HmfModel *model = &Hu3DData[arg0];
    HmfData_UnkD0 *light;

    if (model->unkB4 == NULL) {
        light = HuMemAllocTag(sizeof(HmfData_UnkD0), Hu3DModelTag);
        model->unkB4 = light;
        light->unk03 = arg1;
        light->unk02 = 0x40;
        light->unk01 = 0x40;
        light->unk00 = 0x40;
        light->unk06 = 0x64;
        light->unk05 = 0x64;
        light->unk04 = 0x64;
    }
}

void Hu3DLLightColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    HmfData_UnkD0 *light;

    light = Hu3DData[arg0].unkB4;
    if (light != NULL) {
        light->unk00 = arg1;
        light->unk01 = arg2;
        light->unk02 = arg3;
    }
}

void Hu3DLLightDirSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    HmfData_UnkD0 *light;
    f32 len;

    if (Hu3DData[arg0].unkB4 != NULL) {
        light = Hu3DData[arg0].unkB4;
        len = HuSqrtf(arg1 * arg1 + arg2 * arg2 + arg3 * arg3);
        if (len != 0.0f) {
            light->unk04 = (s8)((arg1 / len) * 120.0f);
            light->unk05 = (s8)((arg2 / len) * 120.0f);
            light->unk06 = (s8)((arg3 / len) * 120.0f);
        } else {
            light->unk04 = 0;
            light->unk05 = 120;
            light->unk06 = 0;
        }
    }
}

void Hu3DModelFaceFlagSet(s16 idx) {
    HmfData *hmf = Hu3DData[idx].hmf;
    HmfModelData_Unk64_Unk60_Struct *obj;
    s16 i;
    s16 j;

    for (i = 0; i < hmf->unk10; i++) {
        obj = &hmf->unk60[i];
        for (j = 0; j < obj->unk22; j++) {
            obj->unk54[j].unk00 |= 0x80;
        }
    }
}

void Hu3DMotionReset(s16 arg0) {
    Hu3DData[arg0].motId = 0xFF;
}
