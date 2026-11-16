#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/hmfdraw.h"
#include "macros.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "variables.h"
#include "game/hmflight.h"
#include "game/hu3d.h"
#include "game/camera.h"
#include "game/mallocblock.h"
#include "gcc/string.h"
#include "game/graphics.h"
#include "game/hmfanim.h"
#include "game/hmfshape.h"
#include "game/hmfload.h"

#define HMF_HILITE_RENDER_MODE (Z_CMP | IM_RD | CVG_DST_SAVE | FORCE_BL |                \
                                GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA) | \
                                GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA))

#define HMF_TEXTURE_SIZE texture->unk1D
#define HMF_TEXTURE_SIZE_LOAD_BLOCK texLoadSiz
#define HMF_TEXTURE_SIZE_INCR texSizIncr
#define HMF_TEXTURE_SIZE_SHIFT texSizShift
#define HMF_TEXTURE_SIZE_BYTES texSizBytes
#define HMF_TEXTURE_SIZE_LINE_BYTES texSizLineBytes

static HmfModelData_Unk64_Unk60_Struct *drawObjP;
static s32 tlutModeBak;
static u8 tlutModeBakPad[8]; // unreferenced
static u16 motionKeyTimeCnt;
static u16 motionKeyValCnt;
extern s16 faceCnt;
extern s16 vtxCntBak;
extern HmfDrawFace faceBuf[];

typedef struct {
    f32 value;
    f32 inTangent;
    f32 outTangent;
} HmfHermiteKey;

extern u32 texLoadSiz;
extern u32 texSizIncr;
extern u32 texSizBytes;
extern u32 texSizLineBytes;
extern u32 texSizShift;
extern s16 Hu3DMotionTag;
extern HuCamera *Hu3DCurCamera;
extern HmfLookAtData Hu3DLookAtBuf[];
extern HmfLookAtData *Hu3DLookAtP;
extern Vtx *Hu3DVtxPos;
extern Mtx *MTXBuf;
extern s16 MTXBufNum;
extern Gfx *gMainGfxPos;
extern Gfx *Hu3DGfxStart;
extern u16 Hu3DDrawEnableF;
extern s16 vtxCnt;
extern s16 totalPolyCnt;
extern s16 totalMatCnt;
extern u8 Hu3DLayerNo;
extern HmfDrawEntry *Hu3DDrawList[8];
extern s16 Hu3DDrawListNum[8];
extern s16 DrawObjIdx;

extern Vtx *Hu3DVtxBuf[];
extern Mtx *Hu3DMtxBuf[];
extern Gfx *Hu3DGfxBuf[];
extern u8 Hu3DBufNo;
extern u16 Hu3DVtxMax;
extern u16 Hu3DMtxMax;
extern u16 Hu3DGfxMax;
extern HmfDrawObject *DrawObjData;
extern UnkLightData *Hu3DLightData;
extern u8 Hu3DObjExtF;
extern u8 Hu3DObjExtMode;
extern f32 Hu3DMatColScale;
extern f32 Hu3DMatAmbScale;
extern u8 Hu3DFogF;
extern u8 Hu3DFogColB;
extern u8 Hu3DFogColG;
extern u8 Hu3DFogColR;
extern s16 Hu3DFogStart;
extern s16 Hu3DFogEnd;
extern u8 Hu3DClipRatio;

extern s32 Hu3DCurAttr;
extern s16 faceNormCnt;
extern Gfx *extraGfxPos;
extern u8 matGfxSplitF;
extern s16 ambColBakB;
extern s16 ambColBakG;
extern s16 ambColBakR;
extern u64 renderModeBak;
extern s32 renderModeBakLo;
extern u64 combineModeBak;
extern s32 combineModeBakLo;
extern HmfData_Unk84_Entry *texAnimEntryBak;
extern HmfData_Unk84_Entry *texAnimGfxBak;
extern Light *Hu3DLightP;
extern s16 lightColBakR;
extern s16 lightColBakG;
extern s16 lightColBakB;

extern HuMtx4F Hu3DObjMtxStack[];
extern HuMtx4F Hu3DObjMtxStackPrev[];
extern HuMtx4F Hu3DSubMtxStackPrev[];
extern HuMtx4F Hu3DObjMtxStackNext;
extern HuMtx4F Hu3DSubMtxStack[];
extern s16 Hu3DObjMtxStackIdx;
extern s16 Hu3DSubMtxStackIdx;
extern u8 Hu3DCameraNo;
extern s16 Hu3DCameraNum;

extern u8 ditherBak;
extern u8 texFilterBak;
extern u8 shadingBak;
extern u8 Hu3DFlatShadeF;
extern s32 geomFlagsBak;

extern s16 Hu3DMotionSpeedMul;
extern s16 Hu3DModelTag;
extern f32 Hu3DMotionGlobalSpeed;
extern u16 Hu3DModelDataTag;
extern s16 Hu3DHiliteLightNo;

Gfx geomInitGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_PERSP),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPClearGeometryMode(G_CULL_BACK | G_FOG | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_ZBUFFER | G_LIGHTING),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

u8 drawListMaxTbl[8] = { 0xC0, 0xC0, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40 };
u8 vtxBatchMaxTbl[8] = { 0x1C, 0x1C, 0x3C, 0x3C, 0x1C, 0x1C, 0x1C, 0x3C };
s16 texFilterTbl[] = { G_TF_POINT, G_TF_AVERAGE, G_TF_BILERP, G_TF_POINT };
s32 clipRatioTbl[][2] = {
    { 1, 0xFFFF },
    { 2, 0xFFFE },
    { 3, 0xFFFD },
    { 4, 0xFFFC },
    { 5, 0xFFFB },
    { 6, 0xFFFA },
};

// 32x32 I4 hilite texture
u8 hiliteTex0[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x34, 0x43, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x9B, 0xB9, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xEF, 0xFE, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4B, 0xFF, 0xFF, 0xB4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xEF, 0xFE, 0x93, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0x9B, 0xB9, 0x51, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x34, 0x43, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// 32x32 I4 hilite texture
u8 hiliteTex1[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x33, 0x33, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x45, 0x67, 0x76, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x79, 0xAB, 0xBA, 0x97, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x47, 0xAC, 0xEE, 0xEE, 0xCA, 0x74, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x59, 0xCF, 0xFF, 0xFF, 0xFC, 0x95, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x6A, 0xEF, 0xFF, 0xFF, 0xFE, 0xA6, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x7B, 0xEF, 0xFF, 0xFF, 0xFE, 0xB7, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x7B, 0xEF, 0xFF, 0xFF, 0xFE, 0xB7, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x03, 0x6A, 0xEF, 0xFF, 0xFF, 0xFE, 0xA6, 0x30, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x59, 0xCF, 0xFF, 0xFF, 0xFC, 0x95, 0x20, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x47, 0xAC, 0xEE, 0xEE, 0xCA, 0x74, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x79, 0xAB, 0xBA, 0x97, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x45, 0x67, 0x76, 0x54, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x33, 0x33, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// 32x32 I4 hilite texture
u8 hiliteTex2[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x12, 0x22, 0x22, 0x21, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x44, 0x55, 0x55, 0x44, 0x32, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x12, 0x45, 0x67, 0x88, 0x88, 0x76, 0x54, 0x21, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x24, 0x67, 0x9A, 0xAB, 0xBA, 0xA9, 0x76, 0x42, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x46, 0x8A, 0xBC, 0xDD, 0xDD, 0xCB, 0xA8, 0x64, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x13, 0x58, 0xAC, 0xDE, 0xFF, 0xFF, 0xED, 0xCA, 0x85, 0x31, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x14, 0x69, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0x96, 0x41, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x25, 0x7A, 0xCE, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xA7, 0x52, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x25, 0x8A, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xA8, 0x52, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x35, 0x8B, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xB8, 0x53, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x01, 0x35, 0x8B, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xB8, 0x53, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x25, 0x8A, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xA8, 0x52, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x25, 0x7A, 0xCE, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xA7, 0x52, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x14, 0x69, 0xBD, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0x96, 0x41, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x13, 0x58, 0xAC, 0xDE, 0xFF, 0xFF, 0xED, 0xCA, 0x85, 0x31, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x02, 0x46, 0x8A, 0xBC, 0xDD, 0xDD, 0xCB, 0xA8, 0x64, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x01, 0x24, 0x67, 0x9A, 0xAB, 0xBA, 0xA9, 0x76, 0x42, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x12, 0x45, 0x67, 0x88, 0x88, 0x76, 0x54, 0x21, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x23, 0x44, 0x55, 0x55, 0x44, 0x32, 0x10, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x12, 0x22, 0x22, 0x21, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

Gfx hiliteGfx[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_LIGHTING | G_TEXTURE_GEN),
    gsDPSetCombineLERP(PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0,
                       PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0),
    gsSPTexture(0x0800, 0x0800, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPEndDisplayList(),
};

u8 *hiliteTexTbl[] = { hiliteTex0, hiliteTex1, hiliteTex2, NULL };
s16 Hu3DMotionLoopF = 0;

void Hu3DDrawInit(HuAllocFunc alloc, HuFreeFunc free, u16 vertexCount, u16 matrixCount, u16 gfxCount, u8 bufferCount) {
    s16 i;

    Hu3DBufNum = bufferCount;
    Hu3DBufNo = 0;
    HuMemInit(alloc, free);
    Hu3DVtxMax = vertexCount;
    Hu3DMtxMax = gfxCount;
    Hu3DGfxMax = matrixCount;
    for (i = 0; i < bufferCount; i++) {
        Hu3DVtxBuf[i] = HuMemAlloc(vertexCount * sizeof(Vtx));
        Hu3DMtxBuf[i] = HuMemAlloc(gfxCount * sizeof(Mtx));
        Hu3DGfxBuf[i] = HuMemAlloc(matrixCount * sizeof(Gfx));
    }
    for (i = 0; i < ARRAY_COUNT(Hu3DDrawList); i++) {
        Hu3DDrawList[i] = HuMemAlloc(drawListMaxTbl[i] * sizeof(HmfDrawEntry));
    }
    DrawObjData = HuMemAlloc(0x8400);
    Hu3DLightData = NULL;
    Hu3DLighInit();
    Hu3DTexInit();
    Hu3DShapeInit();
    Hu3DObjExtF = 1;
    Hu3DObjExtMode = 2;
    Hu3DMatColScale = 1.0f;
    Hu3DMatAmbScale = 1.0f;
    Hu3DFogF = 0;
    Hu3DFogColB = 0xFF;
    Hu3DFogColG = 0xFF;
    Hu3DFogColR = 0xFF;
    Hu3DFogStart = 950;
    Hu3DFogEnd = 1000;
    Hu3DClipRatio = 1;
}

void Hu3DPreProc(void) {
    HuMemCleanUp();
    if (Hu3DDrawEnableF != 0) {
        Hu3DVtxPos = Hu3DVtxBuf[Hu3DBufNo];
        MTXBuf = Hu3DMtxBuf[Hu3DBufNo];
        gMainGfxPos = Hu3DGfxBuf[Hu3DBufNo];
        Hu3DGfxStart = gMainGfxPos;
        Hu3DLookAtP = &Hu3DLookAtBuf[Hu3DBufNo];
        if (++Hu3DBufNo >= Hu3DBufNum) {
            Hu3DBufNo = 0;
        }
        Hu3DLightClose();
        vtxCnt = 0;
        MTXBufNum = 0;
        totalPolyCnt = 0;
        totalMatCnt = 0;
        Hu3DLayerNo = 0;
        Hu3DCamMtxBufSync();
        Hu3DFrameCnt++;
    }
}

void Hu3DDrawListInit(void) {
    s16 i;

    for (i = 0; i < ARRAY_COUNT(Hu3DDrawList); i++) {
        Hu3DDrawListNum[i] = 2;
        Hu3DDrawList[i][0].next = 1;
        Hu3DDrawList[i][1].prev = 0;
        Hu3DDrawList[i][1].next = 0;
        Hu3DDrawList[i][1].depth = 200000.0f;
    }
    DrawObjIdx = 0;
}

void MakeDisplayList(HmfData *arg0) {
    Vtx *vertices;
    HmfModelData_Unk64_Unk60_Struct *object;
    s16 i, j;
    Gfx *gfx;
    Gfx *extraGfx;
    s32 flags;
    s16 savedVertexCount;
    s16 startVertex;
    s16 maxGfx;
    Gfx *savedGfx;
    Vtx *savedVertices;
    u32 vertexCapacity;
    u32 gfxCapacity;
    s16 *indices;

    maxGfx = 0;
    if (arg0->unk10 == 0 || arg0->unk14 == 0) {
        return;
    }
    savedGfx = gMainGfxPos;
    savedVertices = Hu3DVtxPos;
    savedVertexCount = vtxCnt;
    arg0->unk3C = HuMemAllocTag(arg0->unk10 * sizeof(Gfx *), Hu3DModelTag);
    extraGfx = HuMemAlloc(200);
    flags = arg0->unk1C;
    flags = flags * 4 + arg0->unk10 * 8;
    Hu3DVtxPos = HuMemAlloc(flags * sizeof(Vtx));
    if (arg0->unkB4 != 0 || (Hu3DCurAttr & 0x400000)) {
        if (arg0->unk5C != NULL) {
            HuMemFree(arg0->unk5C);
        }
        arg0->unk5C = HuMemAlloc(arg0->unk14 * sizeof(s16));
        arg0->unk28 = 0;
    }
    if (Hu3DVtxPos == NULL) {
        arg0->unk40 = (Vtx *)(vtxCnt * sizeof(Vtx));
        Hu3DVtxPos = arg0->unk40;
    }
    for (i = 0, j = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unkC->unk1F & 1) {
            j++;
            break;
        }
    }
    vertexCapacity = arg0->unk1C;
    gfxCapacity = !j ? vertexCapacity * 32 : vertexCapacity * 128;
    gfx = HuMemAlloc(gfxCapacity + 4000);
    if (gfx == NULL) {
        gfx = gMainGfxPos;
    }
    if (arg0->unkCC != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unkCC->unk00[i] != NULL) {
                HuMemDelayFree(arg0->unkCC->unk00[i]);
            }
        }
        HuMemFree(arg0->unkCC->unk00);
        HuMemFree(arg0->unkCC);
        arg0->unkCC = NULL;
    }
    MakeVtxBuf(arg0);
    vtxCnt = 0;
    faceNormCnt = 0;
    Hu3DLightReset();
    MakeTexAnim(arg0);
    object = arg0->unk60;
    for (i = 0; i < arg0->unk10; i++, object++) {
        gMainGfxPos = gfx;
        extraGfxPos = extraGfx;
        matGfxSplitF = 0;
        startVertex = vtxCnt;
        ambColBakB = 0;
        ambColBakG = 0;
        ambColBakR = 0;
        renderModeBak = 0xFFFFFFFF;
        combineModeBak = 0xFFFFFFFF;
        texAnimEntryBak = NULL;
        SetLightColor(&gMainGfxPos, 1, 0);
        if (Hu3DCurAttr & 0x200) {
            gSPLight(gMainGfxPos++, Hu3DLightP, Hu3DLightData->unk00 + 1);
            lightColBakR = Hu3DLightP->l.col[0];
            lightColBakG = Hu3DLightP->l.col[1];
            lightColBakB = Hu3DLightP->l.col[2];
        }
        flags = object->unk50;
        object->unk28 = vtxCnt;
        object->unk2C = faceNormCnt;
        object->unk50 &= ~0x6000000;
        FaceDraw(arg0, i);
        flags &= 0x6000000;
        if (flags) {
            object->unk50 |= flags;
        }
        object->unk2A = vtxCnt - (u16)object->unk28;
        object->unk2E = faceNormCnt - (u16)object->unk2C;
        gSPEndDisplayList(gMainGfxPos++);
        object->unk60 = texAnimEntryBak;
        if (extraGfxPos == extraGfx) {
            flags = (gMainGfxPos - gfx) * sizeof(Gfx);
            ((Gfx **)arg0->unk3C)[i] = HuMemAllocTag(flags, Hu3DModelTag);
            bcopy(gfx, ((Gfx **)arg0->unk3C)[i], flags);
            object->unk5C = NULL;
            object->unk64 = NULL;
        } else {
            gSPEndDisplayList(extraGfxPos++);
            object->unk5C = texAnimGfxBak;
            ((Gfx **)arg0->unk3C)[i] = HuMemAllocTag((gMainGfxPos - gfx + extraGfxPos - extraGfx) * sizeof(Gfx), Hu3DModelTag);
            bcopy(gfx, ((Gfx **)arg0->unk3C)[i], (gMainGfxPos - gfx) * sizeof(Gfx));
            object->unk64 = ((Gfx **)arg0->unk3C)[i] + (gMainGfxPos - gfx);
            bcopy(extraGfx, object->unk64, (extraGfxPos - extraGfx) * sizeof(Gfx));
        }
        if (maxGfx < gMainGfxPos - gfx) {
            maxGfx = gMainGfxPos - gfx;
        }
        if (object->unk50 & 0x6000000) {
            if (arg0->unkCC == NULL) {
                arg0->unkCC = HuMemAllocTag(sizeof(*arg0->unkCC), Hu3DModelTag);
                arg0->unkCC->unk00 = HuMemAllocTag(arg0->unk10 * sizeof(Gfx *), Hu3DModelTag);
                for (j = 0; j < arg0->unk10; j++) {
                    arg0->unkCC->unk00[j] = NULL;
                }
            }
            gMainGfxPos = gfx;
            vtxCnt = startVertex;
            ambColBakB = 0;
            ambColBakG = 0;
            ambColBakR = 0;
            lightColBakB = 0;
            lightColBakG = 0;
            lightColBakR = 0;
            renderModeBak = 0xFFFFFFFF;
            combineModeBak = 0xFFFFFFFF;
            texAnimEntryBak = NULL;
            FaceDraw(arg0, i);
            gSPEndDisplayList(gMainGfxPos++);
            arg0->unkCC->unk00[i] = HuMemAllocTag((gMainGfxPos - gfx) * sizeof(Gfx), Hu3DModelTag);
            bcopy(gfx, arg0->unkCC->unk00[i], (gMainGfxPos - gfx) * sizeof(Gfx));
        }
    }
    arg0->unk18 = vtxCnt;
    arg0->unk1A = faceNormCnt;
    vertices = HuMemAllocTag(vtxCnt * sizeof(Vtx), Hu3DModelTag);
    bcopy(Hu3DVtxPos, vertices, vtxCnt * sizeof(Vtx));
    arg0->unk40 = vertices;
    MakeVtxGroup(arg0);
    for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
        arg0->unk44[i] = vertices;
    }
    if (arg0->unk5C != NULL) {
        indices = HuMemAllocTag(arg0->unk14 * sizeof(s16), Hu3DModelTag);
        bcopy(arg0->unk5C, indices, arg0->unk14 * sizeof(s16));
        HuMemFree(arg0->unk5C);
        arg0->unk5C = indices;
    }
    if (arg0->unkB4 != 0 || (Hu3DCurAttr & 0x400000)) {
        Hu3DShapeCacheMake(arg0);
    }
    if (arg0->unk1C * 4 + arg0->unk10 * 8 < vtxCnt) {
        osSyncPrintf("Vertex Over!\n");
    }
    HuMemFree(Hu3DVtxPos);
    HuMemFree(gfx);
    HuMemFree(extraGfx);
    vtxCnt = savedVertexCount;
    Hu3DVtxPos = savedVertices;
    gMainGfxPos = savedGfx;
}

void MakeVtxBuf(HmfData *arg0) {
    s16 needed;
    s16 i;
    u16 count;

    needed = 0;
    for (i = 0, count = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk50 & 0x20000) {
            needed = 1;
        }
        count += (u16)arg0->unk60[i].unk22;
    }
    if (needed && arg0->unkB0 == NULL) {
        arg0->unkB0 = HuMemAllocTag(count * sizeof(*arg0->unkB0), Hu3DModelTag);
    }
}

void MakeVtxGroup(HmfData *arg0) {
    HmfVertexGroup *group;
    s16 *indices;
    s16 i, j;
    u16 count;
    f32 x, y, z;

    if (arg0->unkB0 == NULL) {
        return;
    }
    group = arg0->unkB0;
    for (i = 0; i < arg0->unk1A; i++, group++) {
        indices = group->indices;
        count = group->count;
        x = y = z = 0.0f;
        for (j = 0; j < count; j++, indices++) {
            x += arg0->unk40[*indices].v.ob[0];
            y += arg0->unk40[*indices].v.ob[1];
            z += arg0->unk40[*indices].v.ob[2];
        }
        group->center.x = x / count;
        group->center.y = y / count;
        group->center.z = z / count;
    }
}

void MakeTexAnim(HmfData *arg0) {
    s16 textureIndex;
    s16 i, j;

    textureIndex = 4; // TODO: why does this start at 4?

    for (i = 0; i < arg0->unk12; i++) {
        /* Skip entries marked as 0xFF */
        if (arg0->unk84[i].unk9 == 0xFF) {
            continue;
        }

        /* Find first entry with different unkC value */
        for (j = 0; j < i; j++) {
            if (arg0->unk84[i].unkC == arg0->unk84[j].unkC) {
                break;
            }
        }

        /* Copy or assign texture indices */
        if (j != i) {
            arg0->unk84[i].unk3 = arg0->unk84[j].unk3;
            arg0->unk84[i].unk4 = arg0->unk84[j].unk4;
        } else {
            arg0->unk84[i].unk3 = textureIndex++;
            if (arg0->unk84[i].unkC->unk_30 != NULL) {
                arg0->unk84[i].unk4 = textureIndex++;
            }

            if (textureIndex > 16) {
                osSyncPrintf("Texture Anime Over\n");
                return;
            }
        }
    }
}

s32 RemakeDisplayList(HmfData *arg0) {
    s32 var_s2;
    s16 i;

    var_s2 = 0;
    if (arg0->unk40 != NULL) {
        for (i = 0; i < ARRAY_COUNT(arg0->unk44); i++) {
            if (arg0->unk40 != arg0->unk44[i]) {
                if (arg0->unk0A != 0) {
                    HuMemDelayFree(arg0->unk44[i]);
                } else {
                    HuMemFree(arg0->unk44[i]);
                }
                arg0->unk44[i] = arg0->unk40;
                var_s2 = 1;
            }
        }

        if (arg0->unk0A != 0) {
            HuMemDelayFree(arg0->unk40);
        } else {
            HuMemFree(arg0->unk40);
        }
    }
    if (arg0->unk3C != NULL) {
        for (i = 0; i < arg0->unk10; i++) {
            if (arg0->unk0A != 0) {
                HuMemDelayFree(arg0->unk3C->unk00[i]);
            } else {
                HuMemFree(arg0->unk3C->unk00[i]);
            }
        }

        if (arg0->unk0A != 0) {
            HuMemDelayFree(arg0->unk3C);
        } else {
            HuMemFree(arg0->unk3C);
        }
    }
    Hu3DModelDataTag = arg0->unk0E;
    Hu3DModelTag = arg0->unk0E + 1;
    MakeDisplayList(arg0);
    return var_s2;
}

void Hu3DDraw(HmfData *arg0, HuMtx4F arg1, HuMtx4F arg2) {
    HuMtx4F mtx;

    if (arg0->unk14 == 0) {
        return;
    }
    mtxCopy(Hu3DObjMtxStack[0], arg1);
    Hu3DObjMtxStackIdx = 1;
    guMtxIdentF(Hu3DObjMtxStackNext);
    Hu3DSubMtxStackIdx = 0;
    mtxCopy(Hu3DSubMtxStack[0], arg2);
    if (arg0->unk01 & 4) {
        if (arg0->unk60[0].unk50 & 0x70000000) {
            objBillboardCheck(arg0, 0, arg1, mtx);
            mtxCat(arg2, mtx, arg1);
        }
        func_800898F0_main(arg1, &MTXBuf[MTXBufNum]);
        Hu3DDrawEntryAdd(arg0, 0, &MTXBuf[MTXBufNum++], arg1);
        return;
    }
    if (arg0->unk80 == (HmfMotionNode *)-1) {
        if (arg0->unk8C != NULL) {
            Hu3DMotionExec(arg0, arg0->unkA0, arg0->unk8C, 1);
            if (arg0->unk90 != NULL) {
                Hu3DSubMotionExec(arg0, arg0->unkA4, arg0->unkA8);
            }
            if (arg0->unk94 != NULL) {
                Hu3DMotionExec(arg0, arg0->unkAC, arg0->unk94, 0);
            }
        }
        if (arg0->unk64 == 0) {
            return;
        }
        objCallSkeleton(arg0, 0);
    } else {
        if (arg0->unk16 == 0) {
            return;
        }
        if (Hu3DCameraNo != 0 && arg0->unk0B == 1 && (u8)arg0->unk0C != 0) {
            objCallNoAnim(arg0, 0);
        } else {
            if (arg0->unk8C != NULL) {
                Hu3DMotionExec(arg0, arg0->unkA0, arg0->unk8C, 1);
                if (arg0->unk90 != NULL) {
                    Hu3DSubMotionExec(arg0, arg0->unkA4, arg0->unkA8);
                }
                if (arg0->unk94 != NULL) {
                    Hu3DMotionExec(arg0, arg0->unkAC, arg0->unk94, 0);
                }
            }
            if (arg0->unk16 == 1) {
                objCallLink(arg0, 0);
            } else {
                objCall(arg0, 0);
            }
        }
    }
    if (Hu3DMtxMax <= MTXBufNum) {
        osSyncPrintf("Mtx Over\n");
    }
}

void mtxCopy(HuMtx4F dst, HuMtx4F src) {
    dst[0][0] = src[0][0];
    dst[0][1] = src[0][1];
    dst[0][2] = src[0][2];
    dst[0][3] = src[0][3];
    dst[1][0] = src[1][0];
    dst[1][1] = src[1][1];
    dst[1][2] = src[1][2];
    dst[1][3] = src[1][3];
    dst[2][0] = src[2][0];
    dst[2][1] = src[2][1];
    dst[2][2] = src[2][2];
    dst[2][3] = src[2][3];
    dst[3][0] = src[3][0];
    dst[3][1] = src[3][1];
    dst[3][2] = src[3][2];
    dst[3][3] = src[3][3];
}

void objCallSkeleton(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfSkeletonNode *node;
    s32 objectIndex;
    s32 scaled;
    s32 transformed;

    node = &arg0->unk68[arg1];
    objectIndex = node->unk00;
    scaled = 0;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        mtxCat(node->unk4C, Hu3DObjMtxStack[0], mtx);
    } else {
        func_8008A070_main(mtx);
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            mtxTransCat(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            arg0->unkD4(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
            func_8008A070_main(temp);
            mtxScaleCat(temp, node->scale.x, node->scale.y, node->scale.z);
            Hu3DSubMtxStackIdx++;
            mtxCat(temp, Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx], Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx + 1]);
            scaled = 1;
            transformed = 1;
        }
        if (transformed) {
            Hu3DObjMtxStackIdx++;
            mtxCat(mtx, Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx], Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx + 1]);
        }
        mtxCat(Hu3DObjMtxStack[Hu3DObjMtxStackIdx], Hu3DObjMtxStack[0], mtx);
    }
    if (objectIndex >= 0) {
        if (node->unk48->unk60[objectIndex].unk50 & 0x70000000) {
            objBillboardCheck(node->unk48, objectIndex, mtx, temp);
            mtxCat(Hu3DSubMtxStack[Hu3DSubMtxStackIdx], temp, mtx);
        }
        func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
        Hu3DDrawEntryAdd(node->unk48, objectIndex, &MTXBuf[MTXBufNum], mtx);
        MTXBufNum++;
    }
    if (node->unk04 != 0) {
        objCallSkeleton(arg0, arg1 + node->unk04);
    }
    if (transformed) {
        Hu3DObjMtxStackIdx--;
    }
    if (scaled) {
        Hu3DSubMtxStackIdx--;
    }
    if (objectIndex >= 0 && node->unk48 == arg0 && arg0->unk60[objectIndex].unk58 != NULL) {
        objCallSkeleton(arg0->unk60[objectIndex].unk58, 0);
    }
    if (node->unk02 != 0) {
        objCallSkeleton(arg0, arg1 + node->unk02);
    }
}

void objCall(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s32 objectIndex;
    s32 matrixIndex;
    s16 *indices;
    s32 count;
    s32 i;
    s32 scaled;
    s32 transformed;
    void (*rotate)(HuMtx4F, f32, f32, f32);

    node = &arg0->unk80[arg1 & 0x7FFF];
    scaled = 0;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        mtxCat(node->unk58, Hu3DObjMtxStack[0], mtx);
        if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
            func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
            Hu3DSubMtxStackIdx++;
            mtxCat(temp, Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx], Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx + 1]);
            scaled = 1;
        }
    } else {
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            func_80088800_main(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            if (!transformed) {
                rotate = arg0->unkD8;
            } else {
                rotate = arg0->unkD4;
            }
            rotate(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            if (transformed) {
                mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
            } else {
                func_80088700_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            }
            func_80088700_main(temp, node->scale.x, node->scale.y, node->scale.z);
            matrixIndex = ++Hu3DSubMtxStackIdx;
            mtxCat(temp, Hu3DSubMtxStackPrev[matrixIndex], Hu3DSubMtxStackPrev[matrixIndex + 1]);
            scaled = 1;
            transformed = 1;
        }
        if (transformed) {
            Hu3DObjMtxStackIdx++;
            mtxCat(mtx, Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx], Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx + 1]);
        }
        if (Hu3DCameraNum != 1 && arg0->unk0B == 1) {
            mtxCopy(node->unk58, Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
        }
        mtxCat(Hu3DObjMtxStack[Hu3DObjMtxStackIdx], Hu3DObjMtxStack[0], mtx);
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    count = node->unk00;
    indices = node->unk50;
    for (i = 0; i < count; i++) {
        objectIndex = *indices;
        indices++;
        if (objectIndex & 0x8000) {
            if (objectIndex != -1) {
                objCall(arg0, objectIndex & 0x7FFF);
            }
        } else {
            object = &node->unk54->unk60[objectIndex];
            if (object->unk24 == 1) {
                break;
            }
            if (object->unk50 & 0x70000000) {
                objBillboardCheck(node->unk54, objectIndex, mtx, temp);
                mtxCat(Hu3DSubMtxStack[Hu3DSubMtxStackIdx], temp, mtx);
                func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
                matrixIndex = MTXBufNum++;
            }
            Hu3DDrawEntryAdd(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
            linked = arg0->unk60[objectIndex].unk58;
            if (linked != NULL && arg0 == node->unk54) {
                objCall(linked, 0);
            }
        }
    }
    if (transformed) {
        Hu3DObjMtxStackIdx--;
    }
    if (scaled) {
        Hu3DSubMtxStackIdx--;
    }
}

void objCallNoAnim(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s16 objectIndex;
    s16 matrixIndex;
    s16 *indices;
    s16 count;
    s16 i;
    s16 scaled;

    node = &arg0->unk80[arg1 & 0x7FFF];
    scaled = 0;
    mtxCat(node->unk58, Hu3DObjMtxStack[0], mtx);
    if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
        func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
        Hu3DSubMtxStackIdx++;
        mtxCat(temp, Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx], Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx + 1]);
        scaled = 1;
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    indices = node->unk50;
    i = 0;
    count = node->unk00;
    for (; i < count; i++) {
        objectIndex = *indices;
        indices++;
        if (objectIndex & 0x8000) {
            if (objectIndex != -1) {
                objCallNoAnim(arg0, objectIndex & 0x7FFF);
            }
        } else {
            object = &node->unk54->unk60[objectIndex];
            if (object->unk24 == 1) {
                break;
            }
            if (object->unk50 & 0x70000000) {
                objBillboardCheck(node->unk54, objectIndex, mtx, temp);
                mtxCat(Hu3DSubMtxStack[Hu3DSubMtxStackIdx], temp, mtx);
                func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
                matrixIndex = MTXBufNum++;
            }
            Hu3DDrawEntryAdd(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
            linked = arg0->unk60[objectIndex].unk58;
            if (linked != NULL && arg0 == node->unk54) {
                objCallNoAnim(linked, 0);
            }
        }
    }
    if (scaled) {
        Hu3DSubMtxStackIdx--;
    }
}

void objCallLink(HmfData *arg0, s16 arg1) {
    HuMtx4F mtx;
    HuMtx4F temp;
    HmfMotionNode *node;
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfData *linked;
    s32 objectIndex;
    s32 matrixIndex;
    s32 flags;
    s32 transformed;
    void (*rotate)(HuMtx4F, f32, f32, f32);

    node = &arg0->unk80[arg1 & 0x7FFF];
    objectIndex = *node->unk50;
    object = &node->unk54->unk60[objectIndex];
    if (object->unk24 == 1) {
        return;
    }
    flags = object->unk50 & 0x70000000;
    transformed = 0;
    if (arg0->unk8C == NULL) {
        mtxCat(node->unk58, Hu3DObjMtxStack[0], mtx);
        if (flags && (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f)) {
            func_80088700_main(temp, node->baseScale.x, node->baseScale.y, node->baseScale.z);
            Hu3DSubMtxStackIdx++;
            mtxCat(temp, Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx], Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx + 1]);
        }
    } else {
        if (node->pos.x != 0.0f || node->pos.y != 0.0f || node->pos.z != 0.0f) {
            func_80088800_main(mtx, node->pos.x, node->pos.y, node->pos.z);
            transformed = 1;
        }
        if (node->rot.x != 0.0f || node->rot.y != 0.0f || node->rot.z != 0.0f) {
            if (!transformed) {
                rotate = arg0->unkD8;
            } else {
                rotate = arg0->unkD4;
            }
            rotate(mtx, node->rot.x, node->rot.y, node->rot.z);
            transformed = 1;
        }
        if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
            if (transformed) {
                mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
            } else {
                func_80088700_main(mtx, node->scale.x, node->scale.y, node->scale.z);
            }
            if (flags) {
                func_80088700_main(temp, node->scale.x, node->scale.y, node->scale.z);
                Hu3DSubMtxStackIdx++;
                mtxCat(temp, Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx], Hu3DSubMtxStackPrev[Hu3DSubMtxStackIdx + 1]);
            }
            transformed = 1;
        }
        if (transformed) {
            Hu3DObjMtxStackIdx++;
            mtxCat(mtx, Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx], Hu3DObjMtxStackPrev[Hu3DObjMtxStackIdx + 1]);
        }
        if (Hu3DCameraNum != 1 && arg0->unk0B == 1) {
            mtxCopy(node->unk58, Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
        }
        mtxCat(Hu3DObjMtxStack[Hu3DObjMtxStackIdx], Hu3DObjMtxStack[0], mtx);
    }
    func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
    matrixIndex = MTXBufNum++;
    if (object->unk50 & 0x70000000) {
        objBillboardCheck(node->unk54, objectIndex, mtx, temp);
        mtxCat(Hu3DSubMtxStack[Hu3DSubMtxStackIdx], temp, mtx);
        func_800898F0_main(mtx, &MTXBuf[MTXBufNum]);
        matrixIndex = MTXBufNum++;
    }
    Hu3DDrawEntryAdd(node->unk54, objectIndex, &MTXBuf[matrixIndex], mtx);
    linked = arg0->unk60[objectIndex].unk58;
    if (linked != NULL && arg0 == node->unk54) {
        objCall(linked, 0);
    }
}

void objMesh(HmfData *arg0, s16 arg1, HmfDrawObject *arg2) {
    HmfModelData_Unk64_Unk60_Struct *object;
    HmfMaterialData *material;
    s32 flags;

    flags = arg0->unk60[arg1].unk50;
    if (flags & 0x6000000) {
        if (Hu3DCurAttr == 0) {
            arg0->unk60[arg1].unk50 = flags & ~0x6000000;
            gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(Hu3DVtxPos));
            objMesh(arg0, arg1, arg2);
            arg0->unk60[arg1].unk50 = flags;
        } else {
            object = &arg0->unk60[arg1];
            SetupGeometry(arg0, object->unk50 & ~0x6000000, arg1);
            gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(arg0->unk44[Hu3DBufNo]));
            if (object->unk5C != NULL) {
                if (texAnimEntryBak != object->unk5C && object->unk5C != (HmfData_Unk84_Entry *)-1) {
                    gSPDisplayList(gMainGfxPos++, object->unk64);
                }
                texAnimEntryBak = object->unk60;
            } else {
                texAnimEntryBak = NULL;
            }
            gSPDisplayList(gMainGfxPos++, ((Gfx **)arg0->unk3C)[arg1]);
            SetupGeometry(arg0, object->unk50, arg1);
            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(arg2->fixedMtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(gMainGfxPos++, arg0->unkCC->unk00[arg1]);
            return;
        }
    }
    object = &arg0->unk60[arg1];
    SetupGeometry(arg0, object->unk50, arg1);
    if (object->unk50 & 0x40000) {
        Hu3DAnimSegmentSet(arg0);
    }
    if (object->unk20 != -1 || (arg0->unk98 != NULL && (arg0->unk88[object->unk1E].unk09 & 4))) {
        material = &arg0->unk88[object->unk1E];
        gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, (u8)object->unk20);
    }
    if (Hu3DCurAttr & 0x10000) {
        gDPSetEnvColor(gMainGfxPos++, (u8)arg0->unk02[4], (u8)arg0->unk02[5], (u8)arg0->unk02[6], (u8)arg0->unk02[7]);
        gDPSetPrimColor(gMainGfxPos++, 0, 0, (u8)arg0->unk02[0], (u8)arg0->unk02[1], (u8)arg0->unk02[2], (u8)arg0->unk02[3]);
    }
    if (Hu3DCurAttr & HU3D_ATTR_STATIC) {
        if (((Gfx **)arg0->unk3C)[arg1] == NULL) {
            return;
        }
        if (object->unk5C != NULL) {
            if (texAnimEntryBak != object->unk5C && object->unk5C != (HmfData_Unk84_Entry *)-1) {
                gSPDisplayList(gMainGfxPos++, object->unk64);
            }
            texAnimEntryBak = object->unk60;
        } else {
            texAnimEntryBak = NULL;
        }
        gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(arg0->unk44[Hu3DBufNo]));
        gSPDisplayList(gMainGfxPos++, ((Gfx **)arg0->unk3C)[arg1]);
    } else {
        gSPSegment(gMainGfxPos++, 1, osVirtualToPhysical(Hu3DVtxPos));
        FaceDraw(arg0, arg1);
    }
    if ((u32)gMainGfxPos >= (u32)Hu3DGfxStart + (Hu3DGfxMax << 6)) {
        osSyncPrintf("GfxMax Over\n");
    }
}

void Hu3DDrawEntryAddL(HmfData *arg0, s16 arg1, Mtx *arg2) {
    HuMtx4F mtx;

    func_80089980_main(mtx, arg2);
    Hu3DDrawEntryAdd(arg0, arg1, arg2, mtx);
}

void Hu3DDrawEntryAdd(HmfData *arg0, s16 arg1, Mtx *arg2, HuMtx4F arg3) {
    HmfDrawEntry *entries;
    HmfDrawObject *object;
    s16 entryIndex;
    s16 layer;
    s32 flags;
    f32 x, y, z;
    s16 insertion;
    HmfDrawEntry *entry;
    f32 depth;

    layer = arg0->unk00;
    entryIndex = Hu3DDrawListNum[layer];
    if (entryIndex >= drawListMaxTbl[layer]) {
        osSyncPrintf("Model Object Entry Over!! UCODE%d\n", layer);
        return;
    }
    entries = Hu3DDrawList[layer];
    if (arg0->unk60[arg1].unk50 & 0x81210000) {
        x = arg3[3][0];
        y = arg3[3][1];
        z = arg3[3][2];
        depth = x * x + y * y + z * z;
        if (depth != 0.0f) {
            depth = HuSqrtf(depth);
        } else {
            depth = 0.0f;
        }
        flags = arg0->unk60[arg1].unk50;
        if (flags & 0x80210000) {
            depth = 100000.0f - depth;
        } else if (flags & 0x1000000) {
            depth = -depth;
        }
        for (insertion = entries[0].next; entries[insertion].next != 0; insertion = entries[insertion].next) {
            if (depth < entries[insertion].depth) {
                break;
            }
        }
    } else {
        insertion = entries[0].next;
        depth = 0.0f;
    }
    arg0->unk60[arg1].unk1D = entryIndex;
    insertion = entries[insertion].prev;
    entry = entries + entryIndex;
    entry->prev = insertion;
    entry->next = entries[insertion].next;
    entries[insertion].next = entryIndex;
    entries[entry->next].prev = entryIndex;
    Hu3DDrawListNum[layer]++;
    entry->depth = depth;
    object = &DrawObjData[DrawObjIdx];
    entry->objectIndex = DrawObjIdx++;
    object->fixedMtx = arg2;
    object->hmf = arg0;
    object->objectIndex = arg1;
    object->modelFlags = Hu3DCurAttr;
    object->objectFlags = arg0->unk60[arg1].unk50;
    object->light = arg0->unkD0;
}

Gfx *Hu3DDrawLayer(s16 arg0, Gfx *arg1, Gfx *arg2) {
    HmfDrawEntry *entry;
    HmfDrawObject *object;
    HmfData *hmf;
    s16 lightCount;
    s16 visited;
    s16 layer;
    s16 i, j;
    s16 count;
    s16 flags;
    u8 r, g, b;
    Gfx *start;
    s32 active;

    start = gMainGfxPos;
    if (arg2 != NULL) {
        gSPDisplayList(gMainGfxPos++, arg2);
    }
    active = Hu3DLayerNo != 0;
    Hu3DLightExec(arg0);
    r = Hu3DLightP->l.col[0];
    g = Hu3DLightP->l.col[1];
    b = Hu3DLightP->l.col[2];
    lightCount = Hu3DLightData->unk00 + 1;
    for (layer = 0, visited = 0; layer < ARRAY_COUNT(Hu3DDrawList); layer++) {
        if (Hu3DDrawListNum[layer] == 2) {
            continue;
        }
        if (active) {
            gDPFullSync(gMainGfxPos++);
            gSPEndDisplayList(gMainGfxPos++);
            HuGfxTaskSend(start, Hu3DLayerNo, 0, NULL, 0);
            start = gMainGfxPos;
        }
        Hu3DCameraScissorDraw(arg0, &gMainGfxPos);
        visited++;
        active = 1;
        Hu3DLayerNo = layer;
        gSPDisplayList(gMainGfxPos++, arg1);
        renderModeBak = 0xFFFFFFFF;
        combineModeBak = 0xFFFFFFFF;
        geomFlagsBak = -1;
        texAnimEntryBak = NULL;
        gSPNumLights(gMainGfxPos++, lightCount - 1);
        for (j = 1; j < lightCount; j++) {
            gSPLight(gMainGfxPos++, &Hu3DLightP[j], j);
        }
        gSPLight(gMainGfxPos++, Hu3DLightP, lightCount);
        ditherBak = 0xFF;
        shadingBak = 0xFF;
        texFilterBak = 0xFF;
        flags = -1;
        SetClipRatio();
        entry = &Hu3DDrawList[layer][Hu3DDrawList[layer][0].next];
        count = Hu3DDrawListNum[layer];
        for (i = 2; i < count; i++) {
            object = &DrawObjData[entry->objectIndex];
            hmf = object->hmf;
            lightColBakR = r;
            lightColBakG = g;
            lightColBakB = b;
            ambColBakB = 0;
            ambColBakG = 0;
            ambColBakR = 0;
            SetLightColor(&gMainGfxPos, lightCount,
                               ((u16)lightColBakR << 24) + ((u16)lightColBakG << 16) + ((u16)lightColBakB << 8));
            SetLightColor(&gMainGfxPos, 1, 0);
            if (object->light != NULL) {
                gSPLight(gMainGfxPos++, &hmf->unkD0->unk08[Hu3DBufNo], 2);
            }
            if (flags != object->objectFlags) {
                flags = object->objectFlags;
                SetFogMode((u16)flags);
            }
            gSPMatrix(gMainGfxPos++, osVirtualToPhysical(object->fixedMtx), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
            Hu3DCurAttr = object->modelFlags;
            objMesh(hmf, object->objectIndex, object);
            if (object->light != NULL) {
                gSPLight(gMainGfxPos++, &Hu3DLightP[2], 2);
            }
            entry = &Hu3DDrawList[layer][entry->next];
            if (entry->next == 0) {
                break;
            }
        }
    }
    if (visited == 0) {
        gSPDisplayList(gMainGfxPos++, arg1);
        gSPNumLights(gMainGfxPos++, lightCount - 1);
        for (j = 1; j < lightCount; j++) {
            gSPLight(gMainGfxPos++, &Hu3DLightP[j], j);
        }
        gSPLight(gMainGfxPos++, Hu3DLightP, lightCount);
    }
    return start;
}

void FaceDraw(HmfData *hmf, s16 objectIndex) {
    s16 i;
    s16 j;
    s16 faceCount;
    s16 unlit;
    s16 textureWidth;
    s16 textureHeight;
    s16 vertexLimit;
    s16 previousUnlit;
    HmfModelData_Unk64_Unk60_Unk54_Struct *source;
    HmfMaterialData *previousMaterial;
    HmfMaterialData *material;
    HmfData_Unk84_Entry *previousTexture;
    HmfData_Unk84_Entry *texture;
    s32 flags;
    s16 groupVertices;
    s16 animated;
    HmfDrawFace *face;
    s16 *position;
    s8 *color;
    Vtx *vertex;
    s16 sourceIndex;
    s16 vertexIndex;
    s16 s;
    s16 t;
    s16 count;

    drawObjP = &hmf->unk60[objectIndex];
    faceCount = drawObjP->unk22;
    faceCnt = 0;
    tlutModeBak = -1;
    vtxCntBak = vtxCnt;
    source = drawObjP->unk54;
    previousMaterial = &hmf->unk88[source->unk30];
    flags = drawObjP->unk50 &= ~0x40000;
    groupVertices = (flags & 0x6020000) == 0x20000;
    if ((Hu3DCurAttr & 0x2001) == 0x2001) {
        ObjCullCheck(hmf, objectIndex);
    }
    unlit = source->unk00 & 0x80;
    previousUnlit = unlit;
    if (unlit) {
        gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
    } else {
        gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
    }
    if (source->unk32 >= 0) {
        previousTexture = &hmf->unk84[source->unk32];
    } else {
        previousTexture = (HmfData_Unk84_Entry *)-1;
    }
    vertexLimit = vtxBatchMaxTbl[(u32)(Hu3DCurAttr & HU3D_ATTR_LAYER_MASK) >> HU3D_ATTR_LAYER_SHIFT];
    for (i = 0, animated = 0; i < faceCount; i++) {
        source = &hmf->unk60[objectIndex].unk54[i];
        if (source->unk00 >= 3) {
            material = &hmf->unk88[source->unk30];
            if (source->unk32 >= 0) {
                texture = &hmf->unk84[source->unk32];
            } else {
                texture = (HmfData_Unk84_Entry *)-1;
            }
            unlit = source->unk00 & 0x80;
            /* The explicit mask keeps GCC from promoting the limit's halfword spill to a word. */
            if (((vertexLimit & 0xFFFF) < vtxCnt - vtxCntBak) | (previousMaterial != material) ||
                previousTexture != texture || (faceCnt >= 48) | (unlit != previousUnlit) || animated) {
                previousMaterial = material;
                previousTexture = texture;
                MaterialSet(hmf, &drawObjP->unk50);
                if (unlit != previousUnlit) {
                    if (unlit) {
                        gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
                    } else {
                        gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
                    }
                    previousUnlit = unlit;
                }
                faceCnt = 0;
                animated = 0;
            }
            face = &faceBuf[faceCnt];
            count = face->count = source->unk00 & 0x7F;
            if (count != 2) {
                face->material = material;
                face->texture = texture;
                if (texture != (HmfData_Unk84_Entry *)-1) {
                    textureWidth = texture->unkC->unk24 << 5;
                    textureHeight = texture->unkC->unk26 << 5;
                    if (texture->unkC->unk1F & 1) {
                        animated = 1;
                    }
                } else {
                    textureWidth = textureHeight = 0;
                }
                if (groupVertices) {
                    hmf->unkB0[faceNormCnt].count = count;
                    hmf->unkB0[faceNormCnt].normal[0] = source->unk01[0];
                    hmf->unkB0[faceNormCnt].normal[1] = source->unk01[1];
                    hmf->unkB0[faceNormCnt].normal[2] = source->unk01[2];
                }
                for (j = 0; j < count; j++) {
                    sourceIndex = source->unk04[j];
                    position = hmf->unk50[sourceIndex];
                    if (unlit) {
                        color = (s8 *)&hmf->unk88[source->unk2C[j]].unk05;
                    } else {
                        color = hmf->unk54[sourceIndex];
                    }
                    s = source->unk0C[j] * textureWidth;
                    t = source->unk1C[j] * textureHeight;
                    vertex = &Hu3DVtxPos[vtxCnt - 1];
                    if (flags & 0x20000) {
                        if (groupVertices) {
                            hmf->unkB0[faceNormCnt].indices[j] = vtxCnt;
                        }
                        vertexIndex = vtxCntBak;
                    } else {
                        for (vertexIndex = vtxCnt - 1; vertexIndex >= vtxCntBak; vertexIndex--, vertex--) {
                            if (vertex->v.ob[0] == position[0] && vertex->v.ob[1] == position[1] && vertex->v.ob[2] == position[2] &&
                                (s8)vertex->v.cn[0] == color[0] && (s8)vertex->v.cn[1] == color[1] && (s8)vertex->v.cn[2] == color[2] &&
                                vertex->v.tc[0] == s && vertex->v.tc[1] == t) {
                                break;
                            }
                        }
                    }
                    if (vertexIndex <= vtxCntBak) {
                        vertex = &Hu3DVtxPos[vtxCnt];
                        vertex->v.ob[0] = position[0];
                        vertex->v.ob[1] = position[1];
                        vertex->v.ob[2] = position[2];
                        vertex->v.cn[0] = color[0];
                        vertex->v.cn[1] = color[1];
                        vertex->v.cn[2] = color[2];
                        vertex->v.tc[0] = s;
                        vertex->v.tc[1] = t;
                        vertex->v.cn[3] = 0xFF;
                        face->indices[j] = vtxCnt - vtxCntBak;
                        face->flags = unlit;
                        if (hmf->unk5C != NULL) {
                            hmf->unk5C[sourceIndex] = vtxCnt;
                        }
                        vtxCnt++;
                    } else {
                        face->indices[j] = vertexIndex - vtxCntBak;
                        if (hmf->unk5C != NULL) {
                            hmf->unk5C[sourceIndex] = vertexIndex;
                        }
                    }
                }
                if (groupVertices) {
                    faceNormCnt++;
                }
                faceCnt++;
            }
        }
    }
    if (vtxCnt != vtxCntBak) {
        if (unlit != previousUnlit) {
            if (unlit) {
                gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
            } else {
                gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
            }
        }
        MaterialSet(hmf, &drawObjP->unk50);
        if (unlit) {
            gSPSetGeometryMode(gMainGfxPos++, G_LIGHTING);
        }
    }
}

void MaterialSet(HmfData *hmf, s32 *flags) {
    HmfData_Unk84_Entry2 *texture;
    HmfMaterialData *material;
    HmfData_Unk84_Entry *textureEntry;
    s16 changed;
    s16 minS, maxS, minT, maxT;
    u16 r, g, b;
    Vtx *vertex;
    s16 i;
    s16 t;
    s16 coordS;
    s8 segment;
    u8 *image;
    u8 *palette;
    Gfx **gfx;
    HmfDrawFace *face;

    if (faceCnt == 0) {
        return;
    }
    material = faceBuf[0].material;
    textureEntry = faceBuf[0].texture;
    if (!(*flags & 0x6000000)) {
        SetBlendMode(material, textureEntry, *flags);
        r = g = b = 0;
        if (textureEntry == (HmfData_Unk84_Entry *)-1) {
            changed = 0;
            if (Hu3DCurAttr & 0x200) {
                r = material->unk01 * Hu3DMatColScale;
                if (r > 255)
                    r = 255;
                g = material->unk02 * Hu3DMatColScale;
                if (g > 255)
                    g = 255;
                b = material->unk03 * Hu3DMatColScale;
                if (b > 255)
                    b = 255;
                if ((u16)lightColBakR != r || (u16)lightColBakG != g || (u16)lightColBakB != b) {
                    lightColBakR = r;
                    lightColBakG = g;
                    lightColBakB = b;
                    SetLightColor(&gMainGfxPos, Hu3DLightData->unk00 + 1,
                                       ((u16)lightColBakR << 24) + ((u16)lightColBakG << 16) + ((u16)lightColBakB << 8));
                    changed = 1;
                }
            }
            r = material->unk05 * Hu3DMatAmbScale;
            if (r > 255)
                r = 255;
            g = material->unk06 * Hu3DMatAmbScale;
            if (g > 255)
                g = 255;
            b = material->unk07 * Hu3DMatAmbScale;
            if (b > 255)
                b = 255;
            if ((u16)ambColBakR != r || (u16)ambColBakG != g || (u16)ambColBakB != b) {
                ambColBakR = r;
                ambColBakG = g;
                ambColBakB = b;
                SetLightColor(&gMainGfxPos, 1,
                                   ((u16)ambColBakR << 24) + ((u16)ambColBakG << 16) + ((u16)ambColBakB << 8));
                changed = 1;
            }
            if (changed) {
                gDPPipeSync(gMainGfxPos++);
            }
        } else {
            texture = textureEntry->unkC;
            minT = 32000;
            if (texture->unk1F & 1) {
                minS = 32000;
                maxS = maxT = -32000;
                vertex = &Hu3DVtxPos[vtxCntBak];
                for (i = 0; i < vtxCnt - vtxCntBak; i++, vertex++) {
                    t = vertex->v.tc[1];
                    coordS = vertex->v.tc[0];
                    if (minS > coordS)
                        minS = coordS;
                    if (maxS < coordS)
                        maxS = coordS;
                    if (minT > t)
                        minT = t;
                    if (maxT < t)
                        maxT = t;
                }
                minS >>= 5;
                minT >>= 5;
                maxS >>= 5;
                maxT >>= 5;
                changed = 1;
            } else {
                maxS = minS = maxT = minT = 0;
                changed = 0;
            }
            switch ((s8)textureEntry->unk0[0]) {
                case 0x2A:
                case 0x2B:
                    r = material->unk01 * Hu3DMatColScale;
                    if (r > 255)
                        r = 255;
                    g = material->unk02 * Hu3DMatColScale;
                    if (g > 255)
                        g = 255;
                    b = material->unk03 * Hu3DMatColScale;
                    if (b > 255)
                        b = 255;
                    break;
                case 0x29:
                    r = Hu3DMatColScale * 255;
                    if (r > 255)
                        r = 255;
                    g = b = r;
                    break;
            }
            if ((Hu3DCurAttr & 0x200) && ((u16)lightColBakR != r || (u16)lightColBakG != g || (u16)lightColBakB != b)) {
                lightColBakR = r;
                lightColBakG = g;
                lightColBakB = b;
                SetLightColor(&gMainGfxPos, Hu3DLightData->unk00 + 1,
                                   ((u16)lightColBakR << 24) + ((u16)lightColBakG << 16) + ((u16)lightColBakB << 8));
            }
            switch ((s8)textureEntry->unk0[0]) {
                case 0x2B:
                    r = textureEntry->unk5[0] * Hu3DMatAmbScale;
                    if (r > 255)
                        r = 255;
                    g = textureEntry->unk5[1] * Hu3DMatAmbScale;
                    if (g > 255)
                        g = 255;
                    b = textureEntry->unk5[2] * Hu3DMatAmbScale;
                    if (b > 255)
                        b = 255;
                    break;
                case 0x29:
                    r = Hu3DMatAmbScale * 255;
                    if (r > 255)
                        r = 255;
                    g = b = r;
                    break;
                default:
                    r = material->unk05 * Hu3DMatAmbScale;
                    if (r > 255)
                        r = 255;
                    g = material->unk06 * Hu3DMatAmbScale;
                    if (g > 255)
                        g = 255;
                    b = material->unk07 * Hu3DMatAmbScale;
                    if (b > 255)
                        b = 255;
                    break;
            }
            if ((u16)ambColBakR != r || (u16)ambColBakG != g || (u16)ambColBakB != b) {
                ambColBakR = r;
                ambColBakG = g;
                ambColBakB = b;
                SetLightColor(&gMainGfxPos, 1,
                                   ((u16)ambColBakR << 24) + ((u16)ambColBakG << 16) + ((u16)ambColBakB << 8));
            }
            if (changed || (textureEntry != texAnimEntryBak && !(*flags & 0x8000000))) {
                texAnimEntryBak = textureEntry;
                segment = textureEntry->unk3;
                if (segment != -1) {
                    image = (u8 *)(segment << 24);
                    *flags |= 0x40000;
                    gfx = &gMainGfxPos;
                    matGfxSplitF = 1;
                } else {
                    image = texture->unk28;
                    if (matGfxSplitF == 0 && (((((u32)Hu3DCurAttr >> 13) ^ 1) & 1) && (changed ^ 1))) {
                        gfx = &extraGfxPos;
                        texAnimGfxBak = texAnimEntryBak;
                    } else {
                        gfx = &gMainGfxPos;
                    }
                }
                if (texture->unk1C != G_IM_FMT_CI) {
                    if (tlutModeBak != 0) {
                        tlutModeBak = 0;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
                    }
                    if (texture->unk1D != G_IM_SIZ_4b) {
                        if (texture->unk1F & 1) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, texture->unk1D, texture->unk24, image);
                            switch (texture->unk1D) {
                                case G_IM_SIZ_16b:
                                    texSizIncr = 2;
                                    texSizBytes = 2;
                                    break;
                                case G_IM_SIZ_8b:
                                    texSizIncr = 1;
                                    texSizBytes = 1;
                                    break;
                                case G_IM_SIZ_4b:
                                    texSizIncr = 0;
                                    texSizBytes = 0;
                                    break;
                                default:
                                    texSizIncr = 2;
                                    texSizBytes = 2;
                                    break;
                            }
                            gDPSetTile((*gfx)++, texture->unk1C, texture->unk1D, (((maxS - minS + 1) * texSizIncr + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, minS << 2, minT << 2, maxS << 2, maxT << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, texture->unk1D, (((maxS - minS + 1) * texSizBytes + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, minS << 2, minT << 2, maxS << 2, maxT << 2);
                        } else {
                            switch (texture->unk1D) {
                                case G_IM_SIZ_16b:
                                    texLoadSiz = G_IM_SIZ_16b;
                                    texSizIncr = 0;
                                    texSizBytes = 2;
                                    texSizLineBytes = 2;
                                    texSizShift = 0;
                                    break;
                                case G_IM_SIZ_8b:
                                    texLoadSiz = G_IM_SIZ_16b;
                                    texSizIncr = 1;
                                    texSizBytes = 1;
                                    texSizLineBytes = 1;
                                    texSizShift = 1;
                                    break;
                                case G_IM_SIZ_4b:
                                    texLoadSiz = G_IM_SIZ_16b;
                                    texSizIncr = 3;
                                    texSizBytes = 0;
                                    texSizLineBytes = 0;
                                    texSizShift = 2;
                                    break;
                                default:
                                    texLoadSiz = G_IM_SIZ_32b;
                                    texSizIncr = 0;
                                    texSizBytes = 4;
                                    texSizLineBytes = 2;
                                    texSizShift = 0;
                                    break;
                            }
                            gDPLoadTextureBlock((*gfx)++, image, texture->unk1C, HMF_TEXTURE_SIZE,
                                                texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2],
                                                HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    } else {
                        if (texture->unk24 < 16) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24 >> 1, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 1, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_4b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, minS, minT, maxS + 1, maxT + 1, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    }
                } else {
                    segment = textureEntry->unk4;
                    if (segment != -1) {
                        palette = (u8 *)(segment << 24);
                        *flags |= 0x40000;
                        gfx = &gMainGfxPos;
                        matGfxSplitF = 1;
                    } else {
                        palette = texture->unk_30->data;
                        if (matGfxSplitF == 0 && (((((u32)Hu3DCurAttr >> 13) ^ 1) & 1) && (changed ^ 1))) {
                            gfx = &extraGfxPos;
                            texAnimGfxBak = texAnimEntryBak;
                        } else {
                            gfx = &gMainGfxPos;
                        }
                    }
                    if (tlutModeBak != G_TT_RGBA16) {
                        tlutModeBak = G_TT_RGBA16;
                        gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
                    }
                    if (texture->unk_30->colorCount <= 16) {
                        gDPLoadTLUT_pal16((*gfx)++, 0, palette);
                        if (texture->unk24 < 16) {
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24 >> 1, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 1, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_4b, ((((texture->unk24 + 1) >> 1) + 7) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, minS, minT, maxS + 1, maxT + 1, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock_4b((*gfx)++, image, texture->unk1C, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    } else {
                        gDPLoadTLUT_pal256((*gfx)++, palette);
                        if (texture->unk24 < 8) {
                            gfx = &gMainGfxPos;
                            gDPSetTextureImage((*gfx)++, texture->unk1C, G_IM_SIZ_8b, texture->unk24, image);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((texture->unk24 + 8) >> 3), 0, G_TX_LOADTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPLoadSync((*gfx)++);
                            gDPLoadTile((*gfx)++, G_TX_LOADTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                            gDPPipeSync((*gfx)++);
                            gDPSetTile((*gfx)++, texture->unk1C, G_IM_SIZ_8b, ((texture->unk24 + 8) >> 3), 0, G_TX_RENDERTILE, 0, textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk26), 0, textureEntry->unk0[1], HMF_TEXTURE_MASK(texture->unk24), 0);
                            gDPSetTileSize((*gfx)++, G_TX_RENDERTILE, 0, 0, texture->unk24 << 2, texture->unk26 << 2);
                        } else if (texture->unk1F & 1) {
                            gDPLoadTextureTile((*gfx)++, image, texture->unk1C, G_IM_SIZ_8b, texture->unk24, texture->unk26, minS, minT, maxS, maxT, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        } else {
                            gDPLoadTextureBlock((*gfx)++, image, texture->unk1C, G_IM_SIZ_8b, texture->unk24, texture->unk26, 0, textureEntry->unk0[1], textureEntry->unk0[2], HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
                        }
                    }
                }
                matGfxSplitF = 1;
            }
        }
    }
    if (vtxCnt - vtxCntBak > 32) {
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + vtxCntBak * sizeof(Vtx)), 32, 0);
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + (vtxCntBak + 32) * sizeof(Vtx)), vtxCnt - vtxCntBak - 32, 32);
    } else {
        gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + vtxCntBak * sizeof(Vtx)), vtxCnt - vtxCntBak, 0);
    }
    face = faceBuf;
    for (i = 0; i < faceCnt; i++) {
        if (face->count == 3) {
            if (i + 1 < faceCnt && face[1].count == 3) {
                gSP2Triangles(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], 0,
                              face[1].indices[0], face[1].indices[1], face[1].indices[2], 0);
                i++;
                face += 2;
            } else {
                gSP1Triangle(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], 0);
                face++;
            }
        } else {
            gSP1Quadrangle(gMainGfxPos++, face->indices[0], face->indices[1], face->indices[2], face->indices[3], 0);
            face++;
        }
    }
    vtxCntBak = vtxCnt;
}

void ObjCullCheck(HmfData *hmf, s16 objectIndex) {
    s16 *position;

    gSPClearGeometryMode(gMainGfxPos++, G_LIGHTING);
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMin[0];
    position[0] = hmf->unk60[objectIndex].boundsMin[1];
    position[1] = hmf->unk60[objectIndex].boundsMin[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMin[0];
    position[0] = hmf->unk60[objectIndex].boundsMax[1];
    position[1] = hmf->unk60[objectIndex].boundsMin[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMax[0];
    position[0] = hmf->unk60[objectIndex].boundsMax[1];
    position[1] = hmf->unk60[objectIndex].boundsMin[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMax[0];
    position[0] = hmf->unk60[objectIndex].boundsMin[1];
    position[1] = hmf->unk60[objectIndex].boundsMin[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMin[0];
    position[0] = hmf->unk60[objectIndex].boundsMin[1];
    position[1] = hmf->unk60[objectIndex].boundsMax[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMin[0];
    position[0] = hmf->unk60[objectIndex].boundsMax[1];
    position[1] = hmf->unk60[objectIndex].boundsMax[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMax[0];
    position[0] = hmf->unk60[objectIndex].boundsMax[1];
    position[1] = hmf->unk60[objectIndex].boundsMax[2];
    position = Hu3DVtxPos[vtxCnt++].v.ob;
    *position++ = hmf->unk60[objectIndex].boundsMax[0];
    position[0] = hmf->unk60[objectIndex].boundsMin[1];
    position[1] = hmf->unk60[objectIndex].boundsMax[2];
    gSPVertex(gMainGfxPos++, (Vtx *)(0x1000000 + vtxCntBak * sizeof(Vtx)), vtxCnt - vtxCntBak, 0);
    vtxCntBak = vtxCnt;
    gSPCullDisplayList(gMainGfxPos++, 0, 7);
}

void SetBlendMode(HmfMaterialData *material, HmfData_Unk84_Entry *texture, u32 flags) {
    u8 materialFlags;
    s32 antialias;
    u64 combine;
    u64 renderMode;
    s16 depthMode;
    s32 mask;
    s32 materialDepthFlags;
    u32 materialRenderMode;

    materialFlags = material->unk09;
    if ((Hu3DCurAttr & 0x180) == 0x100) {
        antialias = ((flags >> 24) ^ 1) & 1;
    } else {
        antialias = Hu3DCurAttr & 0x180;
    }
    if (flags & 0x80000) {
        return;
    }
    if (Hu3DCurAttr & 0x80000) {
        combine = 0xFCFFFFFF;
        combine <<= 32;
        combine |= 0xFFFFFFFF;
    } else if (Hu3DCurAttr & 0x10000) {
        combine = 0xFC127E24;
        combine <<= 32;
        combine |= 0x55FDF2F9;
    } else if (flags & 0x200000) {
        combine = 0xFCFFFFFF;
        combine <<= 32;
        combine |= 0xFFFE793C;
    } else if (texture == (HmfData_Unk84_Entry *)-1) {
        if (material->unk09 & 1) {
            combine = 0xFC327E64;
            combine <<= 32;
            combine |= 0xFFFFF7FB;
        } else {
            if (!(materialFlags & 4)) {
                gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, 1);
            }
            if (Hu3DFogF == 0) {
                combine = 0xFC327E64;
                combine <<= 32;
                combine |= 0xFFFFFDFE;
            } else {
                combine = 0xFC327FFF;
                combine <<= 32;
                combine |= 0xFFFFFC38;
            }
        }
    } else if (texture->unkC->unk1C == 3) {
        if (Hu3DFogF == 0) {
            combine = 0xFC119623;
            combine <<= 32;
            combine |= 0xFF2FFFFF;
        } else {
            combine = 0xFC1197FF;
            combine <<= 32;
            combine |= 0xFFFFFE38;
        }
        materialFlags |= 1;
    } else if (texture->unkC->unk1C == 4) {
        if (Hu3DFogF == 0) {
            combine = 0xFCFF97FF;
            combine <<= 32;
            combine |= 0xFF2DFEFF;
        } else {
            combine = 0xFCFF97FF;
            combine <<= 32;
            combine |= 0xFFFDFE38;
        }
        materialFlags |= 1;
    } else if (texture->unkC->unk1D == 3) {
        if (Hu3DFogF == 0) {
            combine = 0xFC121624;
            combine <<= 32;
            combine |= 0xFF2FFFFF;
        } else {
            combine = 0xFC1217FF;
            combine <<= 32;
            combine |= 0xFFFFFE38;
        }
        materialFlags |= 1;
    } else if (materialFlags & 1) {
        if (Hu3DFogF == 0) {
            combine = 0xFC121624;
            combine <<= 32;
            combine |= 0xFF2FFFFF;
        } else {
            combine = 0xFC1217FF;
            combine <<= 32;
            combine |= 0xFFFFFE38;
        }
    } else {
        if (Hu3DFogF == 0) {
            combine = 0xFC127E24;
            combine <<= 32;
            combine |= 0xFFFFF3F9;
        } else {
            combine = 0xFC127FFF;
            combine <<= 32;
            combine |= 0xFFFFF238;
        }
    }
    mask = Hu3DCurAttr & 0x60;
    if (mask == 0x20) {
        depthMode = 0x48;
    } else {
        depthMode = (mask == 0x40) * 8;
    }
    if (Hu3DCurAttr & 0x80000) {
        renderMode = 0x5553F0;
    } else if (flags & 0x8000) {
        gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
        if (!(materialFlags & 4)) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, material->unk0A);
        }
        {
            u64 texturedMask;
            renderMode = 0x50307B;
            texturedMask = -(u64)(texture != (HmfData_Unk84_Entry *)-1);
            texturedMask &= renderMode;
            renderMode = texturedMask | 0x50007B;
        }
        renderModeBak = 0;
    } else if (flags & 0x200000) {
        renderMode = 0x507858;
    } else if ((s32)flags < 0) {
        if (materialFlags & 1) {
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            if (!(materialFlags & 4)) {
                gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, material->unk0A);
            }
            renderMode = Hu3DFogF == 0 ? 0x504DD8ULL : 0xFFFFFFFFC8104DD8ULL;
        } else {
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            if (Hu3DFogF == 0) {
                {
                    materialDepthFlags = depthMode;
                    materialRenderMode = 0x553D18;
                    goto applyMaterialRenderMode;
                }
            } else {
                {
                    s32 renderFlags = depthMode;
                    renderFlags |= (s32)0xC8113D18;
                    renderMode = renderFlags;
                }
            }
        }
        drawObjP->unk1E = material->unk00;
    } else if (materialFlags & 1) {
        gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 1);
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
        if (!(materialFlags & 4)) {
            gDPSetPrimColor(gMainGfxPos++, 0, 0, material->unk05, material->unk06, material->unk07, material->unk0A);
        }
        if (depthMode != 0) {
            depthMode |= 0x180;
        } else {
            depthMode |= 0x200;
        }
        if (antialias) {
            if (Hu3DFogF == 0) {
                {
                    materialDepthFlags = depthMode;
                    materialRenderMode = 0x504850;
                    goto applyMaterialRenderMode;
                }
            } else {
                {
                    s32 renderFlags = depthMode;
                    renderFlags |= (s32)0xC8104850;
                    renderMode = renderFlags;
                }
            }
        } else {
            if (Hu3DFogF == 0) {
                {
                    materialDepthFlags = depthMode;
                    materialRenderMode = 0x504040;
                applyMaterialRenderMode:
                    materialRenderMode |= materialDepthFlags;
                    renderMode = (s32)materialRenderMode;
                }
            } else {
                {
                    s32 renderFlags = depthMode;
                    renderFlags |= (s32)0xC8104040;
                    renderMode = renderFlags;
                }
            }
        }
        drawObjP->unk1E = material->unk00;
    } else {
        gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
        if (texture == (HmfData_Unk84_Entry *)-1) {
            if (depthMode == 0) {
                depthMode |= 0x200;
            }
            if (antialias) {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0x552030;
                        mode = renderFlags | mode;
                        renderMode = (s32)mode;
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xC8112030;
                        renderMode = renderFlags;
                    }
                }
            } else {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0x552000;
                        mode = renderFlags | mode;
                        renderMode = (s32)mode;
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xC8112000;
                        renderMode = renderFlags;
                    }
                }
            }
        } else if (Hu3DCurAttr & 0x20000) {
            if (depthMode == 0) {
                depthMode |= 0x200;
            }
            if (antialias) {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0x552030;
                        mode = renderFlags | mode;
                        renderMode = (s32)mode;
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xC8112030;
                        renderMode = renderFlags;
                    }
                }
            } else {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0x552000;
                        mode = renderFlags | mode;
                        renderMode = (s32)mode;
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xC8112000;
                        renderMode = renderFlags;
                    }
                }
            }
        } else {
            if (antialias) {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0x553038;
                        mode = renderFlags | mode;
                        renderMode = (s32)mode;
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xC8113038;
                        renderMode = renderFlags;
                    }
                }
            } else {
                if (Hu3DFogF == 0) {
                    {
                        s32 renderFlags = depthMode;
                        u32 mode = 0xF0A7008;
                        /* De Morgan's form preserves the original OR operand order. */
                        renderMode = (s32) ~(~mode & ~renderFlags);
                    }
                } else {
                    {
                        s32 renderFlags = depthMode;
                        renderFlags |= (s32)0xCB027008;
                        renderMode = renderFlags;
                    }
                }
            }
        }
    }
    if (combineModeBak != combine || renderModeBak != renderMode) {
        gDPPipeSync(gMainGfxPos++);
        if (combineModeBak != combine) {
            Gfx *gfx;
            combineModeBak = combine;
            gfx = gMainGfxPos++;
            gfx->words.w0 = combine >> 32;
            gfx->words.w1 = combine;
        }
        if (renderModeBak != renderMode) {
            gDPSetRenderMode(gMainGfxPos++, renderMode, 0);
            renderModeBak = renderMode;
        }
    }
}

void SetFogMode(u16 flags) {
    u8 mode;

    mode = (flags >> 7) & 3;
    if (mode != texFilterBak) {
        texFilterBak = mode;
        gDPSetTextureFilter(gMainGfxPos++, texFilterTbl[mode]);
    }
    if (Hu3DFlatShadeF != shadingBak) {
        shadingBak = Hu3DFlatShadeF;
        if (!Hu3DFlatShadeF) {
            gSPSetGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        } else {
            gSPClearGeometryMode(gMainGfxPos++, G_SHADING_SMOOTH);
        }
    }
    mode = (flags >> 9) & 3;
    if (mode != ditherBak) {
        ditherBak = mode;
        switch (mode) {
            case 0:
                gDPSetColorDither(gMainGfxPos++, G_CD_DISABLE);
                break;
            case 1:
                gDPSetColorDither(gMainGfxPos++, G_CD_NOISE);
                break;
            case 2:
                gDPSetColorDither(gMainGfxPos++, G_CD_BAYER);
                break;
            case 3:
                gDPSetColorDither(gMainGfxPos++, G_CD_MAGICSQ);
                break;
        }
    }
    if (Hu3DFogF) {
        gSPFogPosition(gMainGfxPos++, Hu3DFogStart, Hu3DFogEnd);
        gDPSetFogColor(gMainGfxPos++, Hu3DFogColR, Hu3DFogColG, Hu3DFogColB, 255);
    }
}

void SetClipRatio(void) {
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RNX, *clipRatioTbl[Hu3DClipRatio]);
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RNY, *clipRatioTbl[Hu3DClipRatio]);
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RPX, *(clipRatioTbl[Hu3DClipRatio] + 1));
    gMoveWd(gMainGfxPos++, G_MW_CLIP, G_MWO_CLIP_RPY, *(clipRatioTbl[Hu3DClipRatio] + 1));
}

void SetupGeometry(HmfData *hmf, s32 flags, s16 objectIndex) {
    if (geomFlagsBak != flags || (flags & 0xE000000)) {
        geomFlagsBak = flags;
        gSPDisplayList(gMainGfxPos++, geomInitGfx);
        if (flags & 0x2000) {
            gSPSetGeometryMode(gMainGfxPos++, G_CULL_BACK);
        }
        if (Hu3DFogF) {
            gDPSetCycleType(gMainGfxPos++, G_CYC_2CYCLE);
            gSPSetGeometryMode(gMainGfxPos++, G_FOG);
        }
        if (flags & 0x6000000) {
            SetHilite(hmf, objectIndex);
        } else if (flags & 0x8000000) {
            SetReflect(hmf, objectIndex);
        }
    }
}

void SetReflect(HmfData *hmf, s16 objectIndex) {
    HuMtx4F mtx;
    HmfData_Unk84_Entry2 *texture;

    if (hmf->unk60[objectIndex].unk1C == 255) {
        return;
    }
    gDPPipeSync(gMainGfxPos++);
    guLookAtReflect((Mtx *)mtx, &Hu3DLookAtP->lookAt,
                    Hu3DCurCamera->pos.x, Hu3DCurCamera->pos.y, Hu3DCurCamera->pos.z,
                    Hu3DCurCamera->at.x, Hu3DCurCamera->at.y, Hu3DCurCamera->at.z,
                    Hu3DCurCamera->up.x, Hu3DCurCamera->up.y, Hu3DCurCamera->up.z);
    gSPLookAt(gMainGfxPos++, &Hu3DLookAtP->lookAt);
    gSPTexture(gMainGfxPos++, 1984, 1984, 0, G_TX_RENDERTILE, G_ON);
    if (hmf->unk9C == NULL) {
        texture = hmf->unk84[hmf->unk60[objectIndex].unk1C].unkC;
    } else {
        texture = hmf->unk9C;
    }
    LoadTexture(texture, 0, 0);
    gSPSetGeometryMode(gMainGfxPos++, G_TEXTURE_GEN | G_LIGHTING);
}

void LoadTexture(HmfData_Unk84_Entry2 *texture, s16 wrapS, s16 wrapT) {
    if (texture->unk1C != G_IM_FMT_CI) {
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
        switch (texture->unk1D) {
            case G_IM_SIZ_16b:
                texLoadSiz = G_IM_SIZ_16b;
                texSizIncr = 0;
                texSizBytes = 2;
                texSizLineBytes = 2;
                texSizShift = 0;
                break;
            case G_IM_SIZ_8b:
                texLoadSiz = G_IM_SIZ_16b;
                texSizIncr = 1;
                texSizBytes = 1;
                texSizLineBytes = 1;
                texSizShift = 1;
                break;
            case G_IM_SIZ_4b:
                texLoadSiz = G_IM_SIZ_16b;
                texSizIncr = 3;
                texSizBytes = 0;
                texSizLineBytes = 0;
                texSizShift = 2;
                break;
            default:
                texLoadSiz = G_IM_SIZ_32b;
                texSizIncr = 0;
                texSizBytes = 4;
                texSizLineBytes = 2;
                texSizShift = 0;
                break;
        }
        gDPLoadTextureBlock(gMainGfxPos++, texture->unk28, texture->unk1C, HMF_TEXTURE_SIZE,
                            texture->unk24, texture->unk26, 0, wrapS, wrapT,
                            HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
    } else {
        gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
        if (texture->unk_30->colorCount <= 16) {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, texture->unk_30->data);
            gDPLoadTextureBlock_4b(gMainGfxPos++, texture->unk28, texture->unk1C,
                                   texture->unk24, texture->unk26, 0, wrapS, wrapT,
                                   HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
        } else {
            gDPLoadTLUT_pal256(gMainGfxPos++, texture->unk_30->data);
            gDPLoadTextureBlock(gMainGfxPos++, texture->unk28, texture->unk1C, G_IM_SIZ_8b,
                                texture->unk24, texture->unk26, 0, wrapS, wrapT,
                                HMF_TEXTURE_MASK(texture->unk24), HMF_TEXTURE_MASK(texture->unk26), 0, 0);
        }
    }
}

void SetHilite(HmfData *hmf, s16 objectIndex) {
    Mtx mtx;
    Light *light;
    u8 *texture;
    s32 objectOffset;

    gSPDisplayList(gMainGfxPos++, hiliteGfx);
    light = &Hu3DLightP[Hu3DHiliteLightNo];
    guLookAtHilite(&mtx, &Hu3DLookAtP->lookAt, &Hu3DLookAtP->data.hilite,
                   Hu3DCurCamera->pos.x, Hu3DCurCamera->pos.y, Hu3DCurCamera->pos.z,
                   Hu3DCurCamera->at.x, Hu3DCurCamera->at.y, Hu3DCurCamera->at.z,
                   Hu3DCurCamera->up.x, Hu3DCurCamera->up.y, Hu3DCurCamera->up.z,
                   light->l.dir[0], light->l.dir[1], light->l.dir[2],
                   0.0f, 0.0f, 115.0f, 32, 32);
    gSPLookAt(gMainGfxPos++, &Hu3DLookAtP->lookAt);
    objectOffset = objectIndex * sizeof(*hmf->unk60);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, light->l.col[0], light->l.col[1], light->l.col[2], 255);
    gDPSetEnvColor(gMainGfxPos++, 64, 64, 64, 128);
    texture = hiliteTexTbl[(((u32)((HmfModelData_Unk64_Unk60_Struct *)(objectOffset + (u32)hmf->unk60))->unk50 >> 25) & 3) - 1];
    gDPLoadTextureBlock_4b(gMainGfxPos++, texture,
                           G_IM_FMT_I, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetHilite1Tile(gMainGfxPos++, G_TX_RENDERTILE, &Hu3DLookAtP->data.hilite, 32, 32);
    if (((HmfModelData_Unk64_Unk60_Struct *)(objectOffset + (u32)hmf->unk60))->unk50 & 0x10000) {
        gDPSetRenderMode(gMainGfxPos++, HMF_HILITE_RENDER_MODE, ZMODE_XLU);
    } else {
        gDPSetRenderMode(gMainGfxPos++, HMF_HILITE_RENDER_MODE, ZMODE_DEC);
    }
    texAnimEntryBak = NULL;
    renderModeBak = 0xFFFFFFFF;
    combineModeBak = 0xFFFFFFFF;
}

s32 objBillboardCheck(HmfData *arg0, s16 arg1, HuMtx4F arg2, HuMtx4F arg3) {
    if (!(arg0->unk60[arg1].unk50 & 0x70000000)) {
        return 0;
    }
    HmfInverseMtxF3X3Cat(arg2, arg3);
    return 1;
}

void Hu3DModelObjMtxGet(HmfData *hmf, s16 nodeIndex, HuMtx4F mtx) {
    Hu3DObjMtxStackIdx = 0;
    guMtxIdentF(Hu3DObjMtxStack[0]);
    if (hmf->unk80 == (HmfMotionNode *)-1 && hmf->unk64 != 0) {
        objMtxCalc(hmf, 0, nodeIndex);
        mtxCopy(mtx, Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
    }
}

s32 objMtxCalc(HmfData *hmf, s16 nodeIndex, s16 targetIndex) {
    HuMtx4F mtx;
    HmfSkeletonNode *node;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk68[nodeIndex];
    changed = 0;
    guMtxIdentF(mtx);
    if (node->unk08.x != 0.0f || node->unk08.y != 0.0f || node->unk08.z != 0.0f) {
        mtxTransCat(mtx, node->unk08.x, node->unk08.y, node->unk08.z);
        changed = 1;
    }
    if (node->unk14.x != 0.0f || node->unk14.y != 0.0f || node->unk14.z != 0.0f) {
        hmf->unkD4(mtx, node->unk14.x, node->unk14.y, node->unk14.z);
        changed = 1;
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++Hu3DObjMtxStackIdx;
        mtxCat(mtx, Hu3DObjMtxStackPrev[matrixIndex], Hu3DObjMtxStackPrev[matrixIndex + 1]);
    }
    if (targetIndex == nodeIndex) {
        return 0;
    }
    if (node->unk04 != 0 && objMtxCalc(hmf, nodeIndex + node->unk04, targetIndex) == 0) {
        return 0;
    }
    if (changed) {
        Hu3DObjMtxStackIdx--;
    }
    if (node->unk02 != 0) {
        if (objMtxCalc(hmf, nodeIndex + node->unk02, targetIndex) == 0) {
            return 0;
        }
    }
    return 1;
}

s16 SearchObjectIndex(HmfData *arg0, const char *name) {
    s16 hash;
    s16 i;

    hash = HmfNameHash((const u8 *)name);
    for (i = 0; i < arg0->unk10; i++) {
        if (arg0->unk60[i].unk26 == hash && strcmp(arg0->unk60[i].unk00, name) == 0) {
            break;
        }
    }
    if (i == arg0->unk10) {
        osSyncPrintf("Can't find ObjName %s\n", name);
        return -1;
    }
    return i;
}

void Hu3DObjReplace(HmfData *hmf, char *name, HmfData *replacement) {
    s16 objectIndex;

    objectIndex = SearchObjectIndex(hmf, name);
    if (objectIndex != -1) {
        Hu3DObjReplaceIdx(hmf, objectIndex, replacement);
    }
}

void Hu3DObjReplaceIdx(HmfData *hmf, s16 objectIndex, HmfData *replacement) {
    s16 i;
    s16 hash;
    s16 j;
    HmfSkeletonNode *node;

    hash = hmf->unk60[objectIndex].unk26;
    for (i = 0; i < replacement->unk10; i++) {
        if (replacement->unk60[i].unk26 == hash &&
            strcmp(replacement->unk60[i].unk00, hmf->unk60[objectIndex].unk00) == 0) {
            break;
        }
    }
    if (i != replacement->unk10) {
        for (j = 0; j < hmf->unk64; j++) {
            node = &hmf->unk68[j];
            if (node->unk00 == objectIndex) {
                node->unk48 = replacement;
                node->unk00 = i;
            }
        }
    }
}

void Hu3DMtxCalc(HmfData *hmf) {
    if (hmf->unk14 != 0) {
        Hu3DSubMtxStackIdx = 0;
        Hu3DObjMtxStackIdx = 0;
        func_8008A070_main(Hu3DObjMtxStack[0]);
        if (hmf->unk80 == (HmfMotionNode *)-1) {
            if (hmf->unk64 != 0) {
                objMtxCalcSkeleton(hmf, 0);
            }
        } else if (hmf->unk16 != 0) {
            objMtxCalcMotion(hmf, 0);
        }
    }
}

void objMtxCalcSkeleton(HmfData *hmf, s16 nodeIndex) {
    HuMtx4F mtx;
    HmfSkeletonNode *node;
    s8 scaled;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk68[nodeIndex];
    scaled = 0;
    changed = 0;
    func_8008A070_main(mtx);
    if (hmf->unk8C == NULL) {
        if (node->unk08.x != 0.0f || node->unk08.y != 0.0f || node->unk08.z != 0.0f) {
            mtxTransCat(mtx, node->unk08.x, node->unk08.y, node->unk08.z);
            changed = 1;
        }
        if (node->unk14.x != 0.0f || node->unk14.y != 0.0f || node->unk14.z != 0.0f) {
            hmf->unkD4(mtx, node->unk14.x, node->unk14.y, node->unk14.z);
            changed = 1;
        }
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        mtxScaleCat(mtx, node->scale.x, node->scale.y, node->scale.z);
        scaled = 1;
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++Hu3DObjMtxStackIdx;
        mtxCat(mtx, Hu3DObjMtxStackPrev[matrixIndex], Hu3DObjMtxStackPrev[matrixIndex + 1]);
    }
    mtxCopy(node->unk4C, Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
    if (node->unk04 != 0) {
        objMtxCalcSkeleton(hmf, nodeIndex + node->unk04);
    }
    if (changed) {
        Hu3DObjMtxStackIdx--;
    }
    if (scaled) {
        Hu3DSubMtxStackIdx--;
    }
    if (node->unk02 != 0) {
        objMtxCalcSkeleton(hmf, nodeIndex + node->unk02);
    }
}

void objMtxCalcMotion(HmfData *hmf, s16 nodeIndex) {
    HuMtx4F mtx;
    HmfMotionNode *node;
    s16 i;
    s16 child;
    s8 scaled;
    s8 changed;
    s16 matrixIndex;

    node = &hmf->unk80[nodeIndex];
    scaled = 0;
    changed = 0;
    func_8008A070_main(mtx);
    if (node->basePos.x != 0.0f || node->basePos.y != 0.0f || node->basePos.z != 0.0f) {
        mtxTransCat(mtx, node->basePos.x, node->basePos.y, node->basePos.z);
        changed = 1;
    }
    if (node->baseRot.x != 0.0f || node->baseRot.y != 0.0f || node->baseRot.z != 0.0f) {
        hmf->unkD4(mtx, node->baseRot.x, node->baseRot.y, node->baseRot.z);
        changed = 1;
    }
    if (node->baseScale.x != 1.0f || node->baseScale.y != 1.0f || node->baseScale.z != 1.0f) {
        mtxScaleCat(mtx, node->baseScale.x, node->baseScale.y, node->baseScale.z);
        scaled = 1;
        changed = 1;
    }
    if (changed) {
        matrixIndex = ++Hu3DObjMtxStackIdx;
        mtxCat(mtx, Hu3DObjMtxStackPrev[matrixIndex], Hu3DObjMtxStackPrev[matrixIndex + 1]);
    }
    mtxCopy(node->unk58, Hu3DObjMtxStack[Hu3DObjMtxStackIdx]);
    for (i = 0; i < node->unk00; i++) {
        child = node->unk50[i];
        if (child & 0x8000) {
            if (child != -1) {
                objMtxCalcMotion(hmf, child & 0x7FFF);
            }
        }
    }
    if (changed) {
        Hu3DObjMtxStackIdx--;
    }
    if (scaled) {
        Hu3DSubMtxStackIdx--;
    }
}

void SetLightColor(Gfx **arg0, s16 arg1, s32 color) {
    switch (arg1) {
        case 0:
        case 1:
            gSPLightColor((*arg0)++, LIGHT_1, color);
            break;
        case 2:
            gSPLightColor((*arg0)++, LIGHT_2, color);
            break;
        case 3:
            gSPLightColor((*arg0)++, LIGHT_3, color);
            break;
        case 4:
            gSPLightColor((*arg0)++, LIGHT_4, color);
            break;
        case 5:
            gSPLightColor((*arg0)++, LIGHT_5, color);
            break;
        case 6:
            gSPLightColor((*arg0)++, LIGHT_6, color);
            break;
        case 7:
            gSPLightColor((*arg0)++, LIGHT_7, color);
            break;
        default:
            gSPLightColor((*arg0)++, LIGHT_8, color);
            break;
    }
}

// Possible file boundary: ROM 0x2DE60 (motion code starts here, like MP4 hsfmotion.c; would be
// hmfmotion.c). Only the code below uses the motion work Hu3DMotion. Weak evidence: no nop
// padding before this function.
void Hu3DMotionInit(void) {
    s16 i;

    Hu3DMotionGlobalSpeedSet(1.0f);
    Hu3DMotion = HuMemAlloc(HU3D_MODEL_MAX * sizeof(*Hu3DMotion));
    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        Hu3DMotion[i].unk02 = -1;
    }
}

s16 Hu3DMotionCreateSub(HmfMotionFile *file, HmfData *hmf) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (Hu3DMotion[i].unk02 == -1) {
            break;
        }
    }
    if (i == HU3D_MODEL_MAX) {
        return -1;
    }
    if ((s16)MotionLoad(hmf, file, i) != 0) {
        if (hmf == NULL) {
            return i;
        }
        hmf->unkA0 = 0;
        return i;
    }
    return -1;
}

s32 Hu3DMotionCreateNoHmf(HmfMotionFile *file) {
    return Hu3DMotionCreateSub(file, NULL);
}

s32 MotionLoad(HmfData *hmf, HmfMotionFile *file, s32 arg2) {
    s16 modelIndex = arg2;
    u32 size;
    HmfMotionFile *copy;
    s32 result;

    Hu3DMotionTag = arg2 + TAG_MOTION;
    Hu3DMotion[modelIndex].unk00 = 0;
    if (hmf == NULL) {
        size = file->size + 8;
        copy = HuMemAllocTag(size, Hu3DMotionTag);
        bcopy(file, copy, size);
        MotionLoadFixup(&Hu3DMotion[modelIndex], copy);
        result = 1;
    } else {
        result = MotionLoadTransform(&Hu3DMotion[modelIndex], hmf) != 0;
    }
    return result;
}

void Hu3DMotionKill(s32 arg0) {
    s16 modelIndex = arg0;

    if (modelIndex != 0xFF) {
        HuMemFreeAllWithTag(modelIndex + TAG_MOTION);
        Hu3DMotion[modelIndex].unk02 = -1;
    }
}

void Hu3DMotionAllKill(void) {
    s16 i;

    for (i = 0; i < HU3D_MODEL_MAX; i++) {
        if (Hu3DMotion[i].unk02 != -1) {
            HuMemFreeAllWithTag(i + TAG_MOTION);
            Hu3DMotion[i].unk02 = -1;
        }
    }
}

s32 MotionLoadTransform(HmfModelData_Unk64_Unk8C_Struct *motion, HmfData *hmf) {
    u8 *data;
    u8 *record;
    HmfMotionChannel *channels;
    s16 channelCapacity;
    s16 blockIndex;
    s16 objectIndex;
    s16 blockCount;
    s16 duration;
    s16 channelIndex;
    s16 materialIndex;
    s16 i;
    s16 channelCount;
    s16 type;
    f32 *values;
    s16 *times;

    data = hmf->unk34;
    channelCapacity = 0;
    blockCount = 0;
    while (1) {
        data = HmfChunkSearch(0x4D544E31, data, hmf->unk30);
        if (data == NULL) {
            break;
        }
        type = data[2];
        if (type == 0x4E || type == 0x0D || type == 8) {
            channelCapacity += data[10];
        }
        blockCount++;
        data = HmfChunkNext(data + 4);
    }
    if (channelCapacity == 0) {
        return 0;
    }
    motion->unk08 = HuMemAllocTag(channelCapacity * sizeof(HmfMotionChannel *), Hu3DMotionTag);
    motion->unk0C = HuMemAllocTag(channelCapacity, Hu3DMotionTag);
    times = motion->unk10 = HuMemAllocTag(0x2000, Hu3DMotionTag);
    values = motion->unk14 = HuMemAllocTag(0x4000, Hu3DMotionTag);
    motionKeyValCnt = 0;
    motionKeyTimeCnt = 0;
    duration = 0;
    data = hmf->unk34;
    blockIndex = 0;
    channelIndex = 0;
    materialIndex = 0;
    for (; blockIndex < blockCount; blockIndex++) {
        data = HmfChunkSearch(0x4D544E31, data, hmf->unk30);
        record = data;
        objectIndex = HmfRecordCount(hmf, (data[8] << 8) + data[9]);
        channelCount = data[10];
        if (channelCount != 0) {
            if ((data[11] << 8) + data[12] > duration) {
                duration = (data[11] << 8) + data[12];
            }
            record += 13;
            channels = HuMemAllocTag(channelCount * sizeof(HmfMotionChannel), Hu3DMotionTag);
            for (i = 0; i < channelCount; i++) {
                type = record[2];
                motion->unk0C[channelIndex] = type;
                motion->unk08[channelIndex] = &channels[i];
                switch (type) {
                    case 0x4E:
                        if (MotionLoadChannel(motion, channelIndex, record + 2)) {
                            channelIndex++;
                        }
                        break;
                    case 0x0D:
                        if (MotionLoadChannel(motion, channelIndex, record + 2)) {
                            motion->unk08[channelIndex]->targetIndex = objectIndex;
                            if (objectIndex == -1) {
                                motion->unk0C[channelIndex] = 0x4E;
                            }
                            channelIndex++;
                        }
                        break;
                    case 8:
                        if (materialIndex == 0) {
                            hmf->unk98 = HuMemAllocTag(sizeof(*hmf->unk98), (s16)(hmf->unk0E + 1));
                        }
                        if (MotionLoadMaterial(hmf, materialIndex, record + 4)) {
                            materialIndex++;
                        }
                        break;
                }
                record += (record[0] << 8) + record[1] + 2;
            }
            data = HmfChunkNext(data + 4);
        }
    }
    if (materialIndex != 0) {
        hmf->unk98->unk00 = materialIndex;
        hmf->unk98->unk08 = 0;
        for (i = 0, blockIndex = 0; i < materialIndex; i++) {
            if ((hmf->unk98->tracks + i)->duration > blockIndex) {
                blockIndex = (hmf->unk98->tracks + i)->duration;
            }
        }
        hmf->unk98->unk04 = blockIndex;
        hmf->unk98->unk02 = 0;
    }
    motion->unk10 = HuMemAllocTag(motionKeyTimeCnt * sizeof(s16), Hu3DMotionTag);
    bcopy(times, motion->unk10, motionKeyTimeCnt * sizeof(s16));
    HuMemFree(times);
    motion->unk14 = HuMemAllocTag(motionKeyValCnt * sizeof(f32), Hu3DMotionTag);
    bcopy(values, motion->unk14, motionKeyValCnt * sizeof(f32));
    HuMemFree(values);
    motion->unk02 = duration;
    motion->unk00 = channelIndex;
    return 1;
}

s32 MotionLoadChannel(HmfModelData_Unk64_Unk8C_Struct *motion, s16 channelIndex, u8 *data) {
    HmfMotionChannel *channel;
    s16 i;
    u16 type;
    union {
        u32 bits;
        f32 value;
    } decoded;
    HmfHermiteKey *key;
    u8 *bytes;
    f32 scale;

    channel = motion->unk08[channelIndex];
    type = *data;
    data++;
    channel->target = data[0];
    scale = 1.0f;
    channel->objectIndex = (data[1] << 8) + data[2];
    channel->nodeIndex = (data[3] << 8) + data[4];
    channel->component = data[5];
    switch ((s16)type) {
        case 0x4E:
            channel->targetIndex = data[6];
            data++;
            break;
    }
    channel->interpolation = data[6];
    data += 7;
    if (channel->interpolation == 'I') {
        channel->flags = data[0];
        channel->keyCount = data[1];
        data += 2;
        channel->timeIndex = motionKeyTimeCnt;
        channel->valueIndex = motionKeyValCnt;
        for (i = 0; i < channel->keyCount; i++, data += 6) {
            type = motionKeyTimeCnt++;
            motion->unk10[type] = (data[0] << 8) + data[1];
            decoded.bits = (data[2] << 24) + (data[3] << 16) + (data[4] << 8) + data[5];
            motion->unk14[motionKeyValCnt++] = scale * decoded.value;
        }
    } else if (channel->interpolation == '#') {
        data++;
        channel->keyCount = *data++;
        channel->timeIndex = motionKeyTimeCnt;
        channel->valueIndex = motionKeyValCnt;
        key = (HmfHermiteKey *)&motion->unk14[motionKeyValCnt];
        for (i = 0; i < channel->keyCount; i++, data += 14) {
            type = motionKeyTimeCnt++;
            motion->unk10[type] = (data[0] << 8) + data[1];
            bytes = (u8 *)key;
            bytes[0] = data[2];
            bytes[1] = data[3];
            bytes[2] = data[4];
            bytes[3] = data[5];
            bytes[4] = data[6];
            bytes[5] = data[7];
            bytes[6] = data[8];
            bytes[7] = data[9];
            bytes[8] = data[10];
            bytes[9] = data[11];
            bytes[10] = data[12];
            bytes[11] = data[13];
            key->value = scale * key->value;
            key++;
            motionKeyValCnt += 3;
        }
    }
    return 1;
}

s32 MotionLoadMaterial(HmfData *hmf, s16 trackIndex, u8 *data) {
    HmfMaterialAnimTrack *track;
    s16 count;
    s16 i;
    s16 duration;

    track = &hmf->unk98->tracks[trackIndex];
    track->flags = (data[0] << 8) + data[1];
    track->materialIndex = (data[2] << 8) + data[3];
    hmf->unk88[track->materialIndex].unk09 |= 5;
    count = track->keyCount = (data[6] << 8) + data[7];
    track->times = HuMemAllocTag(count * sizeof(u16), (s16)(hmf->unk0E + 1));
    track->colors = HuMemAllocTag(count * sizeof(HmfAnimColor), (s16)(hmf->unk0E + 1));
    data += 8;
    for (i = 0, duration = 0; i < count; i++, data += 6) {
        track->colors[i].components[0] = data[0];
        track->colors[i].components[1] = data[1];
        track->colors[i].components[2] = data[2];
        track->colors[i].components[3] = data[3];
        track->times[i] = (data[4] << 8) + data[5];
        duration = track->times[i] + duration;
    }
    track->times[i - 1]++;
    track->duration = duration + 1;
    return 1;
}

s32 MotionLoadFixup(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionFile *file) {
    s16 count;
    s16 i;
    u32 *offsets;
    HmfMotionChannel **channels;

    count = motion->unk00 = file->objectCount;
    motion->unk02 = file->duration;
    motion->unk0C = ((u8 *)file + file->channelOffset);
    motion->unk10 = (s16 *)((u8 *)file + file->timeOffset);
    motion->unk14 = (f32 *)((u8 *)file + file->valueOffset);
    motion->unk08 = HuMemAllocTag(count * sizeof(HmfMotionChannel *), Hu3DMotionTag);
    offsets = file->objectOffsets;
    channels = motion->unk08;
    for (i = 0; i < count; i++) {
        *channels++ = (HmfMotionChannel *)((u8 *)file + *offsets);
        offsets++;
    }
    return 1;
}

void Hu3DMotionExec(HmfData *hmf, f32 frame, HmfModelData_Unk64_Unk8C_Struct *motion, s32 reset) {
    HmfData_UnkBC *environment;
    HmfSkeletonNode *skeleton;
    HmfSkeletonNode *object;
    HmfMotionNode *node;
    HmfMotionChannel *channel;
    f32 *value;
    s32 count;
    s32 i;
    s32 index;
    s32 environmentPresent;
    u32 cameraChannel;

    environment = NULL;
    if (reset != 0) {
        if (hmf->unk80 == (HmfMotionNode *)-1) {
            index = hmf->unk64;
            skeleton = hmf->unk68;
            for (i = 0; i < index; i++, skeleton++) {
                if (skeleton->unk44 != 0) {
                    skeleton->pos = skeleton->unk08;
                }
                if (skeleton->unk45 != 0) {
                    skeleton->rot = skeleton->unk14;
                }
                skeleton->unk44 = 0;
                skeleton->unk45 = 0;
            }
        } else {
            node = hmf->unk80;
            count = hmf->unk16;
            for (i = 0; i < count; i++, node++) {
                if (node->unk4C != 0) {
                    node->pos = node->basePos;
                }
                if (node->unk4D != 0) {
                    node->rot = node->baseRot;
                }
                if (node->unk4E != 0) {
                    node->scale = node->baseScale;
                }
                node->unk4E = 0;
                node->unk4D = 0;
                node->unk4C = 0;
            }
        }
        if (hmf->unkC4 != NULL) {
            environment = hmf->unkBC;
            environment->unk08 = *(f32 *)&hmf->unkC4[environment->unk00].unk20;
            environment->unk0C = *(f32 *)&hmf->unkC4[environment->unk00].unk24;
            environment->unk10 = *(f32 *)&hmf->unkC4[environment->unk00].unk28;
            environment->unk14 = *(f32 *)&hmf->unkC4[environment->unk02].unk20;
            environment->unk18 = *(f32 *)&hmf->unkC4[environment->unk02].unk24;
            environment->unk1C = *(f32 *)&hmf->unkC4[environment->unk02].unk28;
            environment->unk20 = *(f32 *)&hmf->unkC4[environment->unk04].unk20;
            environment->unk24 = *(f32 *)&hmf->unkC4[environment->unk04].unk24;
            environment->unk28 = *(f32 *)&hmf->unkC4[environment->unk04].unk28;
        }
    }
    if (motion != (HmfModelData_Unk64_Unk8C_Struct *)-1) {
        count = motion->unk00;
        for (i = 0; i < count; i++) {
            channel = motion->unk08[i];
            if (channel->objectIndex & 0x8000) {
                continue;
            }
            index = channel->targetIndex & 0x7FFF;
            index = -(index != 0x7FFF) & index;
            cameraChannel = (u32)index >> 14;
            environmentPresent = environment != NULL;
            if (cameraChannel & environmentPresent) {
                index &= 0x3FFF;
                value = &environment->unk08;
                if (environment->unk00 != index) {
                    if (environment->unk02 == index) {
                        value = &environment->unk14;
                    } else {
                        value = &environment->unk20;
                    }
                }
                if (channel->component == 'E') {
                } else if (channel->component == 'F') {
                    value++;
                } else {
                    value += 2;
                }
                if (channel->interpolation == 'I') {
                    *value = GetLinear(motion, channel, frame);
                } else {
                    *value = GetCurve(motion, channel, frame);
                }
                continue;
            }
            if (frame < motion->unk10[channel->timeIndex]) {
                continue;
            }
            switch (motion->unk0C[i]) {
                case 0x4E:
                    switch (channel->target) {
                        case 0x4C:
                            object = &hmf->unk68[index];
                            value = &object->rot.x;
                            switch (channel->component) {
                                case 'E':
                                    break;
                                case 'F':
                                    value = &object->rot.y;
                                    break;
                                default:
                                    value += 2;
                                    break;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            hmf->unk68[index].unk45 = 0x80;
                            break;
                        case 0x4F:
                            value = &hmf->unk68[index].pos.x;
                            if (channel->component == 'E') {
                            } else if (channel->component == 'F') {
                                value++;
                            } else {
                                value += 2;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            hmf->unk68[index].unk44 = 0x80;
                            break;
                        case 0x17:
                            value = &hmf->unk68[index].pos.x;
                            if (channel->component == 'E') {
                            } else if (channel->component == 'F') {
                                value++;
                            } else {
                                value += 2;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            hmf->unk68[index].unk44 = 0x80;
                            break;
                    }
                    break;
                case 0x0D:
                    node = &hmf->unk80[index];
                    switch (channel->target) {
                        case 0x17:
                            value = &node->pos.x;
                            if (channel->component == 'F') {
                                value = &node->pos.y;
                            } else if (channel->component == 'G') {
                                value += 2;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            node->unk4C = 0x80;
                            break;
                        case 0x4C:
                            value = &node->rot.x;
                            if (channel->component == 'F') {
                                value = &node->rot.y;
                            } else if (channel->component == 'G') {
                                value += 2;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            node->unk4D = 0x80;
                            break;
                        case 0x1B:
                            value = &node->scale.x;
                            if (channel->component == 'F') {
                                value = &node->scale.y;
                            } else if (channel->component == 'G') {
                                value += 2;
                            }
                            if (channel->interpolation == 'I') {
                                *value = GetLinear(motion, channel, frame);
                            } else {
                                *value = GetCurve(motion, channel, frame);
                            }
                            node->unk4E = 0x80;
                            break;
                    }
                    break;
            }
        }
    }
}

f32 GetLinear(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame) {
    f32 *values;
    s16 *times;
    s16 i;
    s16 interval;
    s16 previousTime;
    s32 next;

    values = &motion->unk14[channel->valueIndex];
    if (frame == 0.0f || channel->keyCount == 1) {
        return values[0];
    }
    times = &motion->unk10[channel->timeIndex];
    for (i = 0; i < channel->keyCount; i++) {
        if (frame < times[i]) {
            break;
        }
    }
    if (i == channel->keyCount) {
        return values[channel->keyCount - 1];
    } else {
        next = i;
        i--;
        interval = times[next] - times[i];
        previousTime = times[i];
        return (values[next] - values[i]) / interval * (frame - previousTime) + values[i];
    }
}

const u32 curveConstPad[2] = { 0, 0 };
const f64 curveConstOne = 1.0;
const f64 curveConstThree = 3.0;

f32 GetCurve(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame) {
    HmfHermiteKey *values;
    HmfHermiteKey *previous;
    HmfHermiteKey *next;
    s16 *times;
    s32 i;
    s32 count;
    s32 nextTime;
    s16 *cursor;
    f32 elapsed;
    f32 inverse;
    f32 inverseSquared;
    f32 elapsedSquared;
    f32 quadratic;
    f32 cubic;
    f32 twiceCubic;
    f32 thriceQuadratic;

    values = (HmfHermiteKey *)&motion->unk14[channel->valueIndex];
    if (frame == 0.0f || channel->keyCount == 1) {
        return values[0].value;
    }
    times = &motion->unk10[channel->timeIndex];
    count = channel->keyCount;
    for (i = 0, cursor = times; i < count; i++) {
        if (frame < *cursor++) {
            break;
        }
    }
    if (i == count) {
        return values[channel->keyCount - 1].value;
    } else {
        next = &values[i];
        nextTime = times[i];
        i--;
        previous = &values[i];
        elapsed = frame - times[i];
        inverse = curveConstOne / (nextTime - times[i]);
        inverseSquared = inverse * inverse;
        elapsedSquared = elapsed * elapsed;
        quadratic = elapsedSquared * inverse;
        cubic = elapsedSquared * elapsed * inverseSquared;
        twiceCubic = 2.0 * cubic * inverse;
        thriceQuadratic = curveConstThree * elapsedSquared * inverseSquared;
        return (twiceCubic - thriceQuadratic + 1.0f) * previous->value +
               (-twiceCubic + thriceQuadratic) * next->value +
               (cubic - quadratic - quadratic + elapsed) * previous->inTangent +
               (cubic - quadratic) * previous->outTangent;
    }
}

void Hu3DSubMotionExec(HmfData *hmf, f32 frame, f32 weight) {
    HmfModelData_Unk64_Unk8C_Struct *motion;
    HmfMotionChannel *channel;
    HmfSkeletonNode *skeleton;
    HmfMotionNode *node;
    f32 *value;
    f32 result;
    f32 threshold;
    f32 inverseWeight;
    s16 i;
    s16 index;
    s32 component;
    u8 flags;

    motion = hmf->unk90;
    inverseWeight = 1.0f - weight;
    for (i = 0; i < motion->unk00; i++) {
        channel = motion->unk08[i];
        if (channel->objectIndex & 0x8000) {
            continue;
        }
        index = channel->targetIndex & 0x7FFF;
        if (index == 0x7FFF) {
            index = 0;
        }
        if (index & 0x4000) {
            continue;
        }
        if (frame < motion->unk10[channel->timeIndex]) {
            continue;
        }
        if (channel->component != 'E') {
            component = 2;
            if (channel->component == 'F') {
                component = 1;
            }
        } else {
            component = 0;
        }
        switch (motion->unk0C[i]) {
            case 0x4E:
                switch (channel->target) {
                    case 0x4C:
                        value = &hmf->unk68[index].rot.x + component;
                        if (channel->interpolation == 'I') {
                            result = GetLinear(motion, channel, frame);
                        } else {
                            result = GetCurve(motion, channel, frame);
                        }
                        if (result < -180.0f) {
                            result += 360.0f;
                        }
                        threshold = -180.0f;
                        if (*value < threshold) {
                            *value += 360.0f;
                        }
                        if (result > 180.0f) {
                            result -= 360.0f;
                        }
                        if (*value > 180.0f) {
                            *value -= 360.0f;
                        }
                        *value = inverseWeight * *value + result * weight;
                        hmf->unk68[index].unk45 |= (1 << component) | 0x40;
                        break;
                    case 0x4F:
                        value = &hmf->unk68[index].pos.x + component;
                        if (channel->interpolation == 'I') {
                            result = GetLinear(motion, channel, frame);
                        } else {
                            result = GetCurve(motion, channel, frame);
                        }
                        *value = inverseWeight * *value + result * weight;
                        hmf->unk68[index].unk44 |= (1 << component) | 0x40;
                        break;
                }
                break;
            case 0x0D:
                switch (channel->target) {
                    case 0x17:
                        value = &hmf->unk80[index].pos.x + component;
                        if (channel->interpolation == 'I') {
                            result = GetLinear(motion, channel, frame);
                        } else {
                            result = GetCurve(motion, channel, frame);
                        }
                        *value = inverseWeight * *value + result * weight;
                        hmf->unk80[index].unk4C |= (1 << component) | 0x40;
                        break;
                    case 0x4C:
                        value = &hmf->unk80[index].rot.x + component;
                        if (channel->interpolation == 'I') {
                            result = GetLinear(motion, channel, frame);
                        } else {
                            result = GetCurve(motion, channel, frame);
                        }
                        if (result < 0.0f) {
                            result += 360.0f;
                        }
                        if (*value < 0.0f) {
                            *value += 360.0f;
                        }
                        if (result < 180.0f) {
                            if (result + 180.0f < *value) {
                                *value -= 360.0f;
                            }
                        } else {
                            if (*value < result - 180.0f) {
                                result -= 360.0f;
                            }
                        }
                        *value = inverseWeight * *value + result * weight;
                        hmf->unk80[index].unk4D |= (1 << component) | 0x40;
                        break;
                    case 0x1B:
                        value = &hmf->unk80[index].scale.x + component;
                        if (channel->interpolation == 'I') {
                            result = GetLinear(motion, channel, frame);
                        } else {
                            result = GetCurve(motion, channel, frame);
                        }
                        *value = inverseWeight * *value + result * weight;
                        hmf->unk80[index].unk4E |= (1 << component) | 0x40;
                        break;
                }
                break;
        }
    }
    if (hmf->unk80 == (HmfMotionNode *)-1) {
        skeleton = hmf->unk68;
        index = hmf->unk64;
        for (i = 0; i < index; i++, skeleton++) {
            if (skeleton->unk44 != 0) {
                flags = skeleton->unk44;
                value = &skeleton->pos.x;
                if (!(flags & 0x40)) {
                    skeleton->pos.x = inverseWeight * skeleton->pos.x + weight * skeleton->unk08.x;
                    skeleton->pos.y = inverseWeight * skeleton->pos.y + weight * skeleton->unk08.y;
                    skeleton->pos.z = inverseWeight * skeleton->pos.z + weight * skeleton->unk08.z;
                } else {
                    if (!(flags & 1)) {
                        value[0] = inverseWeight * value[0] + weight * skeleton->unk08.x;
                    }
                    if (!(flags & 2)) {
                        value[1] = inverseWeight * value[1] + weight * skeleton->unk08.y;
                    }
                    if (!(flags & 4)) {
                        value[2] = inverseWeight * value[2] + weight * skeleton->unk08.z;
                    }
                }
            }
            if (skeleton->unk45 != 0) {
                flags = skeleton->unk45;
                value = &skeleton->rot.x;
                if (!(flags & 0x40)) {
                    skeleton->rot.x = inverseWeight * skeleton->rot.x + weight * skeleton->unk14.x;
                    skeleton->rot.y = inverseWeight * skeleton->rot.y + weight * skeleton->unk14.y;
                    skeleton->rot.z = inverseWeight * skeleton->rot.z + weight * skeleton->unk14.z;
                } else {
                    if (!(flags & 1)) {
                        value[0] = inverseWeight * value[0] + weight * skeleton->unk14.x;
                    }
                    if (!(flags & 2)) {
                        value[1] = inverseWeight * value[1] + weight * skeleton->unk14.y;
                    }
                    if (!(flags & 4)) {
                        value[2] = inverseWeight * value[2] + weight * skeleton->unk14.z;
                    }
                }
            }
        }
    } else {
        for (i = 0; i < hmf->unk16; i++) {
            node = &hmf->unk80[i];
            if (node->unk4C != 0) {
                flags = node->unk4C;
                value = &node->pos.x;
                if (!(flags & 0x40)) {
                    node->pos.x = inverseWeight * node->pos.x + weight * node->basePos.x;
                    node->pos.y = inverseWeight * node->pos.y + weight * node->basePos.y;
                    node->pos.z = inverseWeight * node->pos.z + weight * node->basePos.z;
                } else {
                    if (!(flags & 1)) {
                        value[0] = inverseWeight * value[0] + weight * node->basePos.x;
                    }
                    if (!(flags & 2)) {
                        value[1] = inverseWeight * value[1] + weight * node->basePos.y;
                    }
                    if (!(flags & 4)) {
                        value[2] = inverseWeight * value[2] + weight * node->basePos.z;
                    }
                }
            }
            if (node->unk4D != 0) {
                flags = node->unk4D;
                value = &node->rot.x;
                if (!(flags & 0x40)) {
                    node->rot.x = inverseWeight * node->rot.x + weight * node->baseRot.x;
                    node->rot.y = inverseWeight * node->rot.y + weight * node->baseRot.y;
                    node->rot.z = inverseWeight * node->rot.z + weight * node->baseRot.z;
                } else {
                    if (!(flags & 1)) {
                        value[0] = inverseWeight * value[0] + weight * node->baseRot.x;
                    }
                    if (!(flags & 2)) {
                        value[1] = inverseWeight * value[1] + weight * node->baseRot.y;
                    }
                    if (!(flags & 4)) {
                        value[2] = inverseWeight * value[2] + weight * node->baseRot.z;
                    }
                }
            }
            if (node->unk4E != 0) {
                flags = node->unk4E;
                value = &node->scale.x;
                if (!(flags & 0x40)) {
                    node->scale.x = inverseWeight * node->scale.x + weight * node->baseScale.x;
                    node->scale.y = inverseWeight * node->scale.y + weight * node->baseScale.y;
                    node->scale.z = inverseWeight * node->scale.z + weight * node->baseScale.z;
                } else {
                    if (!(flags & 1)) {
                        value[0] = inverseWeight * value[0] + weight * node->baseScale.x;
                    }
                    if (!(flags & 2)) {
                        value[1] = inverseWeight * value[1] + weight * node->baseScale.y;
                    }
                    if (!(flags & 4)) {
                        value[2] = inverseWeight * value[2] + weight * node->baseScale.z;
                    }
                }
            }
        }
    }
}

s32 SetObjMatMotion(HmfData *hmf) {
    HmfMaterialAnimTrack *track;
    s16 i;
    s16 j;
    s16 k;
    s16 frame;
    s16 elapsed;
    s16 duration;
    f32 alpha;

    for (i = 0; i < hmf->unk98->unk00; i++) {
        track = &hmf->unk98->tracks[i];
        frame = hmf->unk98->unk08;
        duration = 0;
        for (j = 0; j < track->keyCount; j++) {
            duration += track->times[j];
            if (duration >= frame) {
                break;
            }
        }
        if (j < track->keyCount - 1) {
            elapsed = frame - (duration - track->times[j]);
            alpha = track->colors[j + 1].components[0] - track->colors[j].components[0];
            hmf->unk88[track->materialIndex].unk05 = track->colors[j].components[0] + alpha / (s16)track->times[j] * elapsed;
            alpha = track->colors[j + 1].components[1] - track->colors[j].components[1];
            hmf->unk88[track->materialIndex].unk06 = track->colors[j].components[1] + alpha / (s16)track->times[j] * elapsed;
            alpha = track->colors[j + 1].components[2] - track->colors[j].components[2];
            hmf->unk88[track->materialIndex].unk07 = track->colors[j].components[2] + alpha / (s16)track->times[j] * elapsed;
            alpha = track->colors[j + 1].components[3] - track->colors[j].components[3];
            alpha = track->colors[j].components[3] + alpha / (s16)track->times[j] * elapsed;
        } else {
            hmf->unk88[track->materialIndex].unk05 = track->colors[j].components[0];
            hmf->unk88[track->materialIndex].unk06 = track->colors[j].components[1];
            hmf->unk88[track->materialIndex].unk07 = track->colors[j].components[2];
            alpha = track->colors[j].components[3];
        }
        for (k = 0; k < hmf->unk10; k++) {
            if (hmf->unk60[k].unk1E == track->materialIndex) {
                hmf->unk60[k].unk20 = alpha;
            }
        }
    }
    return 1;
}

void Hu3DAnimTimeStep(HmfData *arg0, f32 arg1) {
    if (arg0->unk98->unk02 & 1) {
        return;
    }

    arg0->unk98->unk08 = arg1 * Hu3DMotionGlobalSpeed + arg0->unk98->unk08;

    if (!(arg0->unk98->unk08 >= arg0->unk98->unk04)) {
        return;
    }

    if (arg0->unk98->unk02 & 2) {
        arg0->unk98->unk08 = 0;
    } else {
        arg0->unk98->unk08 = arg0->unk98->unk04;
    }
}

void Hu3DMotionTimeStepFwd(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg1 * Hu3DMotionGlobalSpeed + arg0->unkA0;

    if (arg0->unkA0 >= arg0->unk8C->unk02) {
        if (Hu3DMotionLoopF != 0) {
            arg0->unkA0 = 0;
        } else {
            arg0->unkA0 = arg0->unk8C->unk02;
        }
    }
}

void Hu3DMotionTimeStepBwd(HmfData *arg0, f32 arg1) {
    arg0->unkA0 = arg0->unkA0 - arg1 * Hu3DMotionGlobalSpeed;

    if (arg0->unkA0 < 0) {
        if (Hu3DMotionLoopF != 0) {
            arg0->unkA0 = arg0->unk8C->unk02;
        } else {
            arg0->unkA0 = 0;
        }
    }
}

f32 Hu3DMotionTimeCalc(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed) {
    speed *= Hu3DMotionSpeedMul * Hu3DMotionGlobalSpeed;
    if (!(flags & 9)) {
        if (!(flags & 4)) {
            frame += speed;
            if (frame >= arg0->unk02) {
                if (flags & 2) {
                    return start;
                } else {
                    return arg0->unk02;
                }
            }
        } else {
            frame -= speed;
            if (frame < start) {
                if (flags & 2) {
                    return arg0->unk02 - speed;
                } else {
                    return start;
                }
            }
        }
    }
    return frame;
}

void Hu3DMotionTimeReset(HmfData *arg0) {
    arg0->unkA0 = 0;
}

void Hu3DMotionTimeEnd(HmfData *arg0) {
    arg0->unkA0 = arg0->unk8C->unk02 - 1;
}

s16 Hu3DMotionTimeGet(HmfData *arg0) {
    return arg0->unkA0;
}

void Hu3DMotionNoMotSet(s16 arg0, s16 arg1, const char *arg2, s16 arg3, s16 arg4) {
    Hu3DMotionNoMotSetEx(arg0, arg1, arg2, arg3, arg4, 0x8000);
}

void Hu3DMotionNoMotReset(s16 arg0, s16 arg1, const char *arg2, s16 arg3, s16 arg4) {
    Hu3DMotionNoMotSetEx(arg0, arg1, arg2, arg3, arg4, 0);
}

void Hu3DMotionNoMotSetEx(s16 modelIndex, s16 motionIndex, const char *name, s16 target, s16 component, s16 flags) {
    HmfModelData_Unk64_Unk8C_Struct *motion;
    HmfData *hmf;
    s16 objectIndex;
    s16 i;
    s16 j;
    HmfMotionChannel *channel;

    motion = &Hu3DMotion[motionIndex];
    hmf = Hu3DData[modelIndex].hmf;
    objectIndex = SearchObjectIndex(hmf, name);
    for (i = 0; i < hmf->unk16; i++) {
        for (j = 0; j < hmf->unk80[i].unk00; j++) {
            if (hmf->unk80[i].unk50[j] == objectIndex) {
                break;
            }
        }
        if (j != hmf->unk80[i].unk00) {
            break;
        }
    }
    for (j = 0; j < motion->unk00; j++) {
        channel = motion->unk08[j];
        if ((channel->targetIndex & 0x7FFF) == i && channel->target == target && channel->component == component) {
            channel->objectIndex = (channel->objectIndex & 0x7FFF) | flags;
            break;
        }
    }
}

void Hu3DMotionGlobalSpeedSet(f32 arg0) {
    Hu3DMotionGlobalSpeed = arg0;
}
