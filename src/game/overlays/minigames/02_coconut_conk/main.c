#include "common.h"
#include "game/pause.h"
#include "game/overlays/minigame.h"
#include "game/mallocblock.h"
#include "humath.h"
#include "gcc/memory.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} CoconutConkData; // sizeof 0x84

typedef struct {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8 unk08[0xAC];
} CoconutConkCameraWork; // sizeof 0xB4

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} CoconutConkCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01[3];
} CoconutConkPhaseBss; // sizeof 0x4

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u16 unk02[2];
} CoconutConkTimerBss; // sizeof 0x6

extern char m202_faceTexDaisy[];
extern char m202_faceTexWaluigi[];
extern char m202_faceTexDonkey[];
extern char m202_faceTexWario[];
extern char m202_faceTexYoshi[];
extern char m202_faceTexPeach[];
extern char m202_faceTexLuigi[];
extern char m202_faceTexMario[];
extern char m202_seaObjName[];
extern char m202_seaTexName[];

s16 m202_dizzySe = 0xC1;
s16 m202_coconutLandSe = 0x310;
s16 m202_coconutHitSe = 0x312;
s16 m202_rollSe = 0x311;

u16 m202_faceFileTbl[][3] = {
    { 0xA4, 0xA5, 0xA8 },
    { 0xA4, 0xA5, 0xA9 },
    { 0xA4, 0xA5, 0xA9 },
    { 0xA4, 0xA5, 0xA8 },
    { 0xA4, 0xA5, 0xA8 },
    { 0xA4, 0xA5, 0xA8 },
    { 0xA4, 0xA5, 0xA9 },
    { 0x1A, 0x1C, 0x25 },
};

char *m202_faceTexTbl[] = {
    m202_faceTexMario,
    m202_faceTexLuigi,
    m202_faceTexPeach,
    m202_faceTexYoshi,
    m202_faceTexWario,
    m202_faceTexDonkey,
    m202_faceTexWaluigi,
    m202_faceTexDaisy,
};

f32 m202_treePosXTbl[] = { -425.0f, -255.0f, -85.0f, 85.0f, 255.0f, 425.0f };

s32 m202_voiceChrTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 };

// The intended delays (90, 900, 0, 30, 150) landed in gaugeValue/winners, likely
// from an initializer written without the inner braces. It doesn't matter in
// practice: this overlay never runs MgFlowMain, so only the
// setup in MgFlowInit reads this struct.
MinigameFlow m202_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 90.0f, 900.0f, 0.0f, 30.0f },
    { 150, 0, 0, 0 },
    0, 0, 0, 0, 0
};

CoconutConkCamera m202_cameraViewTbl[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 43.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 43.0f },
};

s16 m202_soloStillCnt BSS;
s16 m202_rollSeVol BSS;
HuSprAnimData *m202_backImgData BSS;
CoconutConkPhaseBss m202_phaseBss BSS;
u8 m202_soloHitF BSS;
void *m202_faceAnimDataTbl[3] BSS;
s16 m202_faceAnim BSS;
u8 m202_coconutFallNum BSS;
CoconutConkTimerBss m202_timerBss BSS;
s16 m202_rollSePitch BSS;
u8 m202_rollSePitchPad[8] BSS; /* Unreferenced. */
CoconutConkData m202_objWorkTbl[50] BSS;
s16 m202_rollSeTimer BSS;
u8 m202_readyState BSS;
u8 m202_teamComNum BSS;
s16 m202_teamComDelay BSS;
u8 m202_teamSlotNum BSS;
s16 m202_rollSeNo BSS;
u8 m202_rollSeNoPad[0xC] BSS; /* Unreferenced. */

extern const s16 m202_fontMesTbl[];
/* Aliases of m202_phaseBss and m202_timerBss fields (undefined_syms.txt). */
extern u8 m202_phase;
extern u8 m202_teamSlotTbl[3];
extern s16 m202_timer;
extern u16 m202_seaTexSize[2];
/* Aliases of m202_objWorkTbl element fields (undefined_syms.txt). */
extern omObjData *m202_backObj;
extern s16 m202_backSprAnim;
extern u16 m202_backSpr;
extern f32 m202_backSprX;
extern f32 m202_backSprY;
extern omObjData *m202_foreObj;
extern s16 m202_foreSprAnim;
extern u16 m202_foreSpr;
extern f32 m202_foreSprX;
extern f32 m202_foreSprY;
extern omObjData *m202_seaObj;
extern f32 m202_seaScroll;
extern omObjData *m202_cloudObj;
extern f32 m202_cloudScaleA;
extern f32 m202_cloudScaleB;
extern u8 omAllPauseF;
extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];

void m202_MapObjMain(omObjData *);
void m202_MapObjInit(omObjData *);
void m202_BackDraw(Gfx **, s32, s32);
void m202_BackObjMain(omObjData *);
void m202_BackObjInit(omObjData *);
void m202_SeaObjMain(omObjData *);
void m202_ForeObjInit(omObjData *);
void m202_SeaObjInit(omObjData *);
void m202_CloudObjMain(omObjData *);
void m202_CloudObjInit(omObjData *);
void m202_TreeObjInit(omObjData *);
void m202_CoconutUpdate(omObjData *);
void m202_CoconutObjInit(omObjData *);
void m202_SoloComInputCalc(omObjData *);
void m202_SoloObjMain(omObjData *);
void m202_SoloObjInit(omObjData *);
void m202_TeamComInputCalc(omObjData *);
void m202_TeamObjInit(omObjData *);
void m202_ExitObjMain(omObjData *);
void m202_MainObjMain(omObjData *);
void m202_ObjectSetup(void);

void m202_Executor(void) {
    m202_ObjectSetup();
}

f32 m202_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m202_ObjWorkInit(void) {
    CoconutConkData *data;
    u32 i;

    for (i = 0, data = m202_objWorkTbl; i < 50; i++, data++) {
        data->unk00 = NULL;
        data->unk04 = 0;
        data->unk06 = 0;
        data->unk08 = 0;
        data->unk0A = 0;
        data->unk0C = 0;
        data->unk0E = 0;
        data->unk10 = 0;
        data->unk12 = 0;
        data->unk14 = 0;
        data->unk16 = 0;
        data->unk18 = 0.0f;
        data->unk1C = 0.0f;
        data->unk20 = 0.0f;
        data->unk24 = 0.0f;
        data->unk28 = 0.0f;
        data->unk2C = 0.0f;
        data->unk30 = 0.0f;
        data->unk34 = 0.0f;
        data->unk38 = 0.0f;
        data->unk3C = 0.0f;
        data->unk40 = -1;
        data->unk42 = -1;
        data->unk44.x = data->unk44.y = data->unk44.z = 0.0f;
        data->unk50.x = data->unk50.y = data->unk50.z = 0.0f;
        data->unk5C.x = data->unk5C.y = data->unk5C.z = 0.0f;
        data->unk68 = 0.0f;
        data->unk6C = 0.0f;
        data->unk70 = 0.0f;
        data->unk74 = 0.0f;
        data->unk78.x = data->unk78.y = data->unk78.z = 0.0f;
    }
}

void m202_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m202_PhaseSet(u8 arg0) {
    m202_phase = arg0;
}

f32 m202_GravityCalc(f32 arg0, f32 *arg1, f32 arg2) {
    f32 value = *arg1;

    *arg1 = value - arg2;
    return arg0 + value;
}

void m202_SoloFaceSet(omObjData *arg0, u8 arg1) {
    s32 character = GwPlayer[arg0->work[0]].chr;

    Hu3DAnimKill(m202_faceAnim);
    m202_faceAnim = Hu3DAnimCreate(Hu3DData[arg0->model[0]].hmf, m202_faceAnimDataTbl[arg1], 0,
                                             m202_faceTexTbl[character]);
}

void m202_MapObjMain(omObjData *arg0) {
}

void m202_MapObjInit(omObjData *arg0) {
    CoconutConkCameraWork *work;

    mgMapObjTbl[mgMapObjNum++] = arg0;
    work = HuMemAllocTag(sizeof(CoconutConkCameraWork), TAG_OVERLAY);
    arg0->data = work;
    memset(work, 0, sizeof(CoconutConkCameraWork));
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk06 &= ~0x200;
    MgMapSlideSet(arg0, 20.0f);
    MgMapFrictionSet(arg0, 0.5f);
    MgMapAccelSet(arg0, mgPlayerAccel);
    MgMapBoxSet(mgMapObjTbl[0], 512.0f, -1000.0f, -285.0f, 1000.0f, -165.0f);
    arg0->func = m202_MapObjMain;
}

void m202_MapObjCreate(void) {
    omObjData *obj = omAddObj(0x3E8, 1, 0xA, -1, m202_MapObjInit);
    obj->work[0] = 0;
    m202_objWorkTbl[0].unk00 = obj;
}

void m202_BackDraw(Gfx **arg0, s32 arg1, s32 arg2) {
    Gfx *gfx = *arg0;
    s32 x;
    s32 top;
    s32 y;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_CULL_BOTH | G_FOG | G_LOD);
    gSPSetGeometryMode(gfx++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BACK);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, m202_backImgData->pal);
    x = 0;
    for (y = 0, top = 128; y < 112; y += 4) {
        gDPLoadTextureTile(gfx++, m202_backImgData->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, y, 320, y + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (top + y) << 2, (x + 320) << 2, (top + y + 4) << 2, G_TX_RENDERTILE, 0, 0,
                            1024, 1024);
    }
    *arg0 = gfx;
}

void m202_BackObjMain(omObjData *arg0) {
}

void m202_BackObjInit(omObjData *arg0) {
    m202_backSprAnim = HuSprAnimDataRead(0x23000D);
    m202_backSpr = espEntry(m202_backSprAnim, 0, 0);
    espAttrSet(m202_backSpr, HUSPR_ATTR_BG);
    m202_backSprX = 160.0f;
    m202_backSprY = 67.0f;
    espPosSet(m202_backSpr, 160, 67);
    m202_backImgData = HuSprAnimDataGet(HuSprAnimDataRead(0x23000E));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m202_BackDraw, 2), HU3D_CAM0);
    arg0->func = m202_BackObjMain;
}

void m202_BackObjCreate(void) {
    omObjData *obj = omAddObj(0x384, 1, 0xA, -1, m202_BackObjInit);
    obj->work[0] = 0;
    m202_backObj = obj;
}

void m202_ForeObjMain(omObjData *arg0) {
}

void m202_ForeObjInit(omObjData *arg0) {
    m202_foreSprAnim = HuSprAnimDataRead(0x23000F);
    m202_foreSpr = espEntry(m202_foreSprAnim, 0, 0);
    espAttrSet(m202_foreSpr, HUSPR_ATTR_NONE);
    m202_foreSprX = 160.0f;
    m202_foreSprY = 219.0f;
    espPosSet(m202_foreSpr, 160, 219);
    arg0->func = m202_ForeObjMain;
}

void m202_ForeObjCreate(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, m202_ForeObjInit);
    obj->work[0] = 0;
    m202_foreObj = obj;
}

void m202_SeaObjMain(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[4];

    if (omPauseChk() + omAllPauseF == 0) {
        data->unk18 += 0.2f;
    }
    Hu3DModelObjTexScroll(arg0->model[0], 0.0f, data->unk18, m202_seaTexSize[0], m202_seaTexSize[1],
                       m202_seaObjName, 0);
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

void m202_SeaObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead(0x230004, 0x289);
    Hu3DModelVtxBufMake(arg0->model[0]);
    Hu3DTexSizeGet(m202_seaTexName, m202_seaTexSize);
    m202_seaScroll = 0.0f;
    arg0->trans.x = 0.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = 0.0f;
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    arg0->func = m202_SeaObjMain;
}

void m202_SeaObjCreate(void) {
    omObjData *obj = omAddObj(0x35C, 1, 0, -1, m202_SeaObjInit);
    obj->work[0] = 0;
    m202_seaObj = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m202_CloudObjMain(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[5];

    switch (data->unk04) {
        case 0:
            data->unk1C += 0.005f;
            data->unk20 -= 0.005f;
            if (data->unk1C > 1.1f) {
                data->unk04 = 1;
            }
            break;
        case 1:
            data->unk1C -= 0.005f;
            data->unk20 += 0.005f;
            if (data->unk1C < 1.0f) {
                data->unk04 = 0;
            }
            break;
    }
    arg0->scale.x = arg0->scale.y = arg0->scale.z = data->unk1C;
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    Hu3DModelScaleSet(arg0->model[1], data->unk20, data->unk20, data->unk20);
}

void m202_CloudObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead(0x230005, 0x289);
    arg0->model[1] = Hu3DModelRead(0x230005, 0x289);
    arg0->trans.x = -400.0f;
    arg0->trans.y = 700.0f;
    arg0->trans.z = -1000.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -1000.0f);
    Hu3DModelPosSet(arg0->model[1], 450.0f, 750.0f, -1000.0f);
    m202_cloudScaleA = 1.0f;
    m202_cloudScaleB = 1.0f;
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM1);
    arg0->func = m202_CloudObjMain;
}

void m202_CloudObjCreate(void) {
    omObjData *obj = omAddObj(0x366, 5, 0xA, -1, m202_CloudObjInit);
    obj->work[0] = 0;
    m202_cloudObj = obj;
}

void m202_TreeObjMain(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[6 + arg0->work[0]];

    switch (data->unk04) {
        case 0:
            Hu3DMotionTimeSet(arg0->model[0], 0.0f);
            Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            break;
        case 1:
            Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
            if (Hu3DMotion[Hu3DData[arg0->model[0]].motId].unk02 == Hu3DData[arg0->model[0]].motTime) {
                data->unk04 = 0;
            }
            break;
    }
}

void m202_TreeObjInit(omObjData *arg0) {
    if (arg0->work[0] % 3 == 0) {
        arg0->model[0] = Hu3DModelRead(0x230001, 0x299);
    }
    if (arg0->work[0] % 3 == 1) {
        arg0->model[0] = Hu3DModelRead(0x230003, 0x299);
    }
    if (arg0->work[0] % 3 == 2) {
        arg0->model[0] = Hu3DModelRead(0x23000C, 0x299);
    }
    arg0->trans.x = m202_treePosXTbl[arg0->work[0]];
    arg0->trans.y = 0.0f;
    arg0->trans.z = -225.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -225.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM1);
    arg0->func = m202_TreeObjMain;
}

void m202_TreeObjCreateAll(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        CoconutConkData *data = &m202_objWorkTbl[6 + i];
        omObjData *obj = omAddObj(0x352, 1, 0xA, -1, m202_TreeObjInit);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

void m202_CoconutUpdate(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[12 + arg0->work[0]];
    s16 sound;
    s16 pan;

    switch (data->unk04) {
        case 0:
            Hu3DMotionTimeSet(arg0->model[0], 0.0f);
            Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 1:
            Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            arg0->trans.y = 422.0f - (++data->unk06 & 1) * 10.0f;
            if (data->unk06 > 0) {
                data->unk04 = 2;
                data->unk06 = 0;
                arg0->trans.y = 422.0f;
            }
            break;
        case 2:
            arg0->trans.y -= data->unk18;
            data->unk18 += 1.5f;
            arg0->trans.z += 4.0f;
            if (arg0->trans.y < 0.0f) {
                arg0->trans.y = 0.0f;
                data->unk04 = 3;
                data->unk18 = 0.0f;
                MgPlayerEffSet(arg0, 1, arg0->trans.x, arg0->trans.y, arg0->trans.z, 0.0f, 0.0f);
            }
            break;
        case 3:
            if (data->unk06 == 0) {
                Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
                sound = HuAudFXPlay(m202_coconutLandSe);
                pan = (arg0->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan > 127) {
                    pan = 127;
                }
                HuAudFXPanning(sound, pan);
            }
            if ((++data->unk06 & 3) < 3) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            if (data->unk06 >= 16) {
                m202_coconutFallNum--;
                data->unk04 = 0;
                data->unk06 = 0;
                arg0->trans.z = -200.0f;
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(arg0->model[0], 0.0f);
                Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            }
            break;
        case 4:
            if (data->unk06 == 0) {
                Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
                sound = HuAudFXPlay(m202_coconutHitSe);
                pan = (arg0->trans.x + 390.0f) * 0.165f;
                if (pan < 0) {
                    pan = 0;
                } else if (pan > 127) {
                    pan = 127;
                }
            }
            if ((++data->unk06 & 3) < 3) {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            if (data->unk06 >= 16) {
                m202_coconutFallNum--;
                data->unk04 = 0;
                data->unk06 = 0;
                arg0->trans.z = -200.0f;
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(arg0->model[0], 0.0f);
                Hu3DMotionSpeedSet(arg0->model[0], 0.0f);
            }
            break;
    }
}

void m202_CoconutObjMain(omObjData *arg0) {
    m202_CoconutUpdate(arg0);
}

void m202_CoconutObjInit(omObjData *arg0) {
    if (arg0->work[0] < 3) {
        arg0->model[0] = Hu3DModelRead(0x23000B, 0x289);
    }
    if (arg0->work[0] - 3 < 3) {
        arg0->model[0] = Hu3DModelRead(0x23000A, 0x289);
    }
    if (arg0->work[0] >= 6) {
        arg0->model[0] = Hu3DModelRead(0x230002, 0x289);
    }
    arg0->trans.x = arg0->trans.y = 0.0f;
    arg0->trans.z = -200.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -200.0f);
    arg0->model[1] = Hu3DModelRead(7, 0x2AD);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM1);
    arg0->func = m202_CoconutObjMain;
}

void m202_CoconutObjCreateAll(void) {
    u8 i;

    for (i = 0; i < 9; i++) {
        CoconutConkData *data = &m202_objWorkTbl[12 + i];
        omObjData *obj = omAddObj(0x320, 5, 0xA, -1, m202_CoconutObjInit);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

void m202_SoloComInputCalc(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];
    u16 player = arg0->work[0];
    f32 target = 0.0f;
    f32 gaps[4];
    f32 pos[3];
    u8 input;
    u8 middle;
    u8 mode;
    u8 left;
    u8 right;
    u8 widest;
    s16 i;
    s16 j;
    omObjData *obj;
    CoconutConkData *entry;

    input = rand8();
    // do-while (0) gives mode the loop weighting needed for its register.
    do {
        mode = 0;
    } while (0);
    if (((GwPlayer[player].cpu_difficulty == 0) & (input < 50)) ||
        ((GwPlayer[player].cpu_difficulty == 1) & (input < 150)) ||
        ((GwPlayer[player].cpu_difficulty == 2) & (input < 180)) ||
        ((GwPlayer[player].cpu_difficulty == 3) & (input < 255))) {
        for (i = 0; i < 3; i++) {
            CoconutConkData *e = &m202_objWorkTbl[22 + i];
            omObjData *o = e->unk00;

            pos[i] = o->trans.x;
            if (o->trans.x + 39.0f > arg0->trans.x - 40.0f && o->trans.x - 39.0f < arg0->trans.x + 40.0f) {
                mode = 1;
            }
        }
        for (i = 0; i < 3; i++) {
            entry = &m202_objWorkTbl[12 + i];
            obj = entry->unk00;
            if (entry->unk04 == 1 || entry->unk04 == 2) {
                if (obj->trans.x + 29.0f > arg0->trans.x - 40.0f && obj->trans.x - 29.0f < arg0->trans.x + 40.0f) {
                    mode = 2;
                }
            }
        }
        if (mode == 1) {
            left = 0;
            middle = 0;
            right = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    if (pos[left] > pos[j]) {
                        left = j;
                    }
                }
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    if (pos[right] < pos[j]) {
                        right = j;
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (i != left && i != right) {
                    middle = i;
                }
            }
            gaps[0] = fabsf(-450.0f - pos[left]);
            gaps[1] = fabsf(pos[left] - pos[middle]);
            gaps[2] = fabsf(pos[middle] - pos[right]);
            gaps[3] = fabsf(pos[right] - 450.0f);
            widest = 0;
            for (i = 0; i < 3; i++) {
                if (gaps[i] < gaps[i + 1]) {
                    widest = i + 1;
                }
            }
            switch (widest) {
                case 0:
                    target = (pos[left] + -450.0f) * 0.5f;
                    break;
                case 1:
                    target = (pos[left] + pos[middle]) * 0.5f;
                    break;
                case 2:
                    target = (pos[middle] + pos[right]) * 0.5f;
                    break;
                case 3:
                    target = (pos[right] + 450.0f) * 0.5f;
                    break;
            }
            if (target + 60.0f < arg0->trans.x) {
                input = 1;
            } else if (arg0->trans.x < target - 60.0f) {
                input = 2;
            }
        }
        if (mode == 2) {
            if (data->unk18 <= 0.0f) {
                input = 1;
            } else {
                input = 2;
            }
        }
        if (mode == 0) {
            if (0.0f < data->unk18) {
                input = 1;
            } else if (data->unk18 < 0.0f) {
                input = 2;
            }
        }
    }
    data->unk06--;
    if (data->unk06 <= 0) {
        data->unk06 = 0;
    }
    if (input == 0) {
        data->unk04 = 0;
    }
    if (input % 5 == 1 && data->unk06 == 0) {
        data->unk04 = 1;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                data->unk06 = 30;
                break;
            case 1:
                data->unk06 = 10;
                break;
            case 2:
                data->unk06 = 7;
                break;
            case 3:
                data->unk06 = 1;
                break;
        }
    }
    if (input % 5 == 2 && data->unk06 == 0) {
        data->unk04 = 2;
        switch (GwPlayer[player].cpu_difficulty) {
            case 0:
                data->unk06 = 30;
                break;
            case 1:
                data->unk06 = 10;
                break;
            case 2:
                data->unk06 = 7;
                break;
            case 3:
                data->unk06 = 1;
                break;
        }
    }
}

void m202_SoloComInput(omObjData *arg0) {
    m202_SoloComInputCalc(arg0);
}

void m202_SoloPadInput(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];

    data->unk04 = 0;
    if (HuPadStkX[arg0->work[3]] <= -30) {
        data->unk04 = 1;
    }
    if (HuPadStkX[arg0->work[3]] >= 30) {
        data->unk04 = 2;
    }
}

void m202_SoloIntroMove(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];

    switch (data->unk04) {
        case 0:
            if (data->unk18 < 0.0f) {
                data->unk18 += 0.05;
            }
            if (data->unk18 > 0.0f) {
                data->unk18 -= 0.05;
            }
            if ((s16)data->unk18 == 0) {
                data->unk18 = 0.0f;
                arg0->trans.x = (s16)arg0->trans.x;
            }
            break;
        case 1:
            if (data->unk18 > -10.0f) {
                data->unk18 -= 0.5f;
                if (data->unk18 < -10.0f) {
                    data->unk18 = -10.0f;
                }
            }
            break;
        case 2:
            if (data->unk18 < 10.0f) {
                data->unk18 += 0.5f;
                if (data->unk18 > 10.0f) {
                    data->unk18 = 10.0f;
                }
            }
            break;
    }
    arg0->rot.z = m202_AngleAdd(arg0->rot.z, -data->unk18);
    arg0->trans.x += data->unk18;
}

void m202_SoloMove(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];
    f32 nextX;

    switch (data->unk04) {
        case 0:
            if (data->unk18 < 0.0f) {
                data->unk18 += 0.05;
            }
            if (data->unk18 > 0.0f) {
                data->unk18 -= 0.05;
            }
            if ((s16)data->unk18 == 0) {
                data->unk18 = 0.0f;
                arg0->trans.x = (s16)arg0->trans.x;
            }
            break;
        case 1:
            if (data->unk18 > -7.0f) {
                data->unk18 -= 0.45f;
                if (data->unk18 < -7.0f) {
                    data->unk18 = -7.0f;
                }
            }
            break;
        case 2:
            if (data->unk18 < 7.0f) {
                data->unk18 += 0.45f;
                if (data->unk18 > 7.0f) {
                    data->unk18 = 7.0f;
                }
            }
            break;
    }
    if (data->unk18 >= -3.0f && data->unk18 <= 3.0f) {
        m202_soloStillCnt++;
        if (m202_soloStillCnt > 500) {
            m202_soloStillCnt = 500;
        }
    } else {
        m202_soloStillCnt = 0;
    }
    nextX = arg0->trans.x + data->unk18;
    if ((nextX >= 450.0f) | (nextX <= -450.0f)) {
        data->unk18 = -(data->unk18 * 0.5f);
    }
    arg0->rot.z = m202_AngleAdd(arg0->rot.z, -data->unk18);
    arg0->trans.x += data->unk18;
}

void m202_SoloHitCheck(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];
    s16 i;
    s16 sound;

    for (i = 0; i < 9; i++) {
        CoconutConkData *coconut = &m202_objWorkTbl[12 + i];
        omObjData *obj = coconut->unk00;

        if (coconut->unk04 == 2 && obj->trans.x + 29.0f >= arg0->trans.x - 40.0f &&
            obj->trans.x - 29.0f <= arg0->trans.x + 40.0f && obj->trans.y + 84.0f >= arg0->trans.y - 50.0f &&
            obj->trans.y <= arg0->trans.y + 50.0f) {
            if (m202_phase == 2 && m202_timer > 0) {
                m202_soloHitF = 1;
                m202_SoloFaceSet(arg0, 2);
                Hu3DMotionSpeedSet(arg0->model[6], 1.0f);
                Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelPosSet(arg0->model[6], arg0->trans.x, arg0->trans.y + 50.0f, arg0->trans.z);
                data->unk0A = 1;
                if (!(GwPlayer[arg0->work[0]].stat & 1)) {
                    omVibrate(arg0->work[0], 20, 0, 20);
                }
            }
            coconut->unk04 = 4;
        }
    }
    if (Hu3DMotion[Hu3DData[arg0->model[6]].motId].unk02 <= Hu3DData[arg0->model[6]].motTime) {
        Hu3DModelAttrSet(arg0->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(arg0->model[7], arg0->trans.x, arg0->trans.y + 50.0f, arg0->trans.z + 40.0f);
        if (data->unk0C == 0) {
            sound = PlayerFXPlay(m202_dizzySe, arg0->work[0]);
            data->unk0C++;
            HuAudFXPitchSet(sound, 0);
            HuAudFXVolSet(sound, 127);
        }
    }
    switch (data->unk0A) {
        case 0:
            data->unk28 = data->unk24 = 1.0f;
            break;
        case 1:
            Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
            data->unk24 = 0.5f;
            data->unk28 = 1.3f;
            data->unk0A = 2;
            break;
        case 2:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.5f) {
                data->unk0A = 3;
            }
            break;
        case 3:
            data->unk24 -= 0.1f;
            data->unk28 += 0.06f;
            if (data->unk24 <= 0.5f) {
                data->unk0A = 4;
            }
            break;
        case 4:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.5f) {
                data->unk0A = 5;
            }
            break;
        case 5:
            data->unk24 -= 0.1f;
            data->unk28 += 0.06f;
            if (data->unk24 <= 0.5f) {
                data->unk0A = 6;
            }
            break;
        case 6:
            data->unk24 += 0.1f;
            data->unk28 -= 0.06f;
            if (data->unk24 >= 1.0f) {
                data->unk0A = 7;
            }
            break;
    }
    Hu3DModelPosSet(arg0->model[3], arg0->trans.x, 40.0f, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[3], 90.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(arg0->model[3], data->unk28, 1.0f, data->unk24);
}

void m202_SoloObjMain(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[21];
    u16 player = arg0->work[0];
    s16 pan;

    switch (m202_phase) {
        case 0:
            switch (data->unk08) {
                case 0:
                    data->unk04 = 1;
                    if (arg0->trans.x < 30.0f) {
                        data->unk08 = 1;
                    }
                    break;
                case 1:
                    data->unk04 = 2;
                    if (data->unk18 > 2.5f) {
                        data->unk08 = 2;
                    }
                    break;
                case 2:
                    data->unk04 = 0;
                    if ((s16)arg0->rot.z >= 350.0f || (s16)arg0->rot.z <= 5.0f) {
                        if (arg0->trans.x >= -5.0f && arg0->trans.x <= 5.0f) {
                            arg0->rot.z = 0.0f;
                            data->unk04 = 0;
                            data->unk18 = 0.0f;
                            data->unk08 = 3;
                        }
                    }
                    break;
                case 3:
                    m202_readyState = 0;
                    data->unk08 = 0;
                    break;
            }
            m202_SoloIntroMove(arg0);
            break;
        case 2:
            if (m202_timer > 0 && m202_soloHitF == 0) {
                if (GwPlayer[player].stat & PLAYER_IS_CPU) {
                    m202_SoloComInput(arg0);
                } else {
                    m202_SoloPadInput(arg0);
                }
                m202_SoloMove(arg0);
            }
            m202_SoloHitCheck(arg0);
            break;
        case 3:
            m202_SoloHitCheck(arg0);
            data->unk18 = 0.0f;
            break;
        case 4:
            m202_SoloHitCheck(arg0);
            if (m202_soloHitF != 0) {
                break;
            }
            switch (data->unk08) {
                case 0:
                    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(arg0->model[3], HU3D_ATTR_HOOK, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(arg0->model[4], 1.0f);
                    Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(arg0->model[4], arg0->trans.x, arg0->trans.y + 20.0f, arg0->trans.z);
                    Hu3DMotionSpeedSet(arg0->model[5], 1.0f);
                    Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(arg0->model[5], arg0->trans.x, arg0->trans.y + 20.0f, arg0->trans.z);
                    m202_SoloFaceSet(arg0, 1);
                    arg0->rot.z = 0.0f;
                    Hu3DMotionModelSet(arg0->model[0], arg0->motion[1]);
                    data->unk1C = 30.0f;
                    data->unk08 = 1;
                    break;
                case 1:
                    arg0->trans.y = m202_GravityCalc(arg0->trans.y, &data->unk1C, 3.0f);
                    if (arg0->trans.y <= 0.0f) {
                        arg0->trans.y = 0.0f;
                        data->unk08 = 2;
                        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[2]].motId, 0, 5, 0);
                        HuAudCharVoicePlay((m202_voiceChrTbl[GwPlayer[arg0->work[0]].chr] << 16) | 0x2F);
                    }
                    data->unk20 -= 9.0f;
                    if (data->unk20 < 0.0f) {
                        data->unk20 = 0.0f;
                    }
                    Hu3DModelTPLvlSet(arg0->model[4], data->unk20);
                    if (Hu3DMotion[Hu3DData[arg0->model[4]].motId].unk02 <= Hu3DData[arg0->model[4]].motTime) {
                        Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    if (Hu3DMotion[Hu3DData[arg0->model[5]].motId].unk02 <= Hu3DData[arg0->model[5]].motTime) {
                        Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    break;
                case 2:
                    data->unk20 -= 9.0f;
                    if (data->unk20 < 0.0f) {
                        data->unk20 = 0.0f;
                    }
                    Hu3DModelTPLvlSet(arg0->model[4], data->unk20);
                    if (Hu3DMotion[Hu3DData[arg0->model[4]].motId].unk02 <= Hu3DData[arg0->model[4]].motTime) {
                        Hu3DModelAttrSet(arg0->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    if (Hu3DMotion[Hu3DData[arg0->model[5]].motId].unk02 <= Hu3DData[arg0->model[5]].motTime) {
                        Hu3DModelAttrSet(arg0->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    break;
            }
            break;
        case 1:
        case 5:
            break;
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    if (++m202_rollSeTimer >= 100) {
        m202_rollSeTimer = 0;
    }
    if (m202_rollSeNo == -1) {
        m202_rollSeNo = HuAudPlayerFXPlay(m202_rollSe, arg0->work[0]);
        if (m202_rollSeNo == -1) {
            return;
        }
        m202_rollSePitch = -400;
        HuAudFXPitchSet(m202_rollSeNo, -400);
        m202_rollSeVol = 0;
        HuAudFXVolSet(m202_rollSeNo, m202_rollSeVol);
        if (m202_rollSeNo == -1) {
            return;
        }
    }
    if (m202_phase < 3) {
        if (!(m202_rollSeTimer & 1)) {
            m202_rollSePitch = fabs(data->unk18 * 60.0f) + 0.0;
            if (m202_rollSePitch > 400) {
                m202_rollSePitch = 400;
            } else if (m202_rollSePitch < 0) {
                m202_rollSePitch = 0;
            }
            HuAudFXPitchSet(m202_rollSeNo, m202_rollSePitch);
        } else {
            m202_rollSeVol = fabs(data->unk18 * 20.0f) + 0.0;
            if (m202_rollSeVol > 125) {
                m202_rollSeVol = 125;
            } else if (m202_rollSeVol < 0) {
                m202_rollSeVol = 0;
            }
            HuAudFXVolSet(m202_rollSeNo, m202_rollSeVol);
        }
        pan = (arg0->trans.x + 450.0f) * 0.143f;
        if (pan < 0) {
            pan = 0;
        } else if (pan > 127) {
            pan = 127;
        }
        HuAudFXPanning(m202_rollSeNo, pan);
    }
}

void m202_SoloObjInit(omObjData *obj) {
    CoconutConkData *data = &m202_objWorkTbl[21];
    s8 chr = GwPlayer[obj->work[0]].chr;
    s32 model = omCharModelNoTbl[chr][0];
    s16 i;

    obj->model[0] = Hu3DModelRead(model | omCharModelNoTbl[chr][2], 0x2A9);
    for (i = 0; i < 3; i++) {
        m202_faceAnimDataTbl[i] = DataRead(model | m202_faceFileTbl[chr][i]);
    }
    m202_faceAnim = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m202_faceAnimDataTbl[0], 0,
                                             m202_faceTexTbl[chr]);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x62));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 4));
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    obj->trans.x = 400.0f;
    obj->trans.y = 40.0f;
    obj->trans.z = -100.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    data->unk18 = -10.0f;
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 325.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->model[1] = Hu3DModelRead2(0, 0x4A9);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    obj->model[2] = Hu3DModelRead(8, 0x2BD);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->model[3] = Hu3DModelRead(0x230000, 0x299);
    Hu3DModelPosSet(obj->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
    Hu3DModelHookSet(obj->model[3], obj->model[0], "item_hook");
    obj->model[4] = Hu3DModelRead(0x230006, 0x28D);
    Hu3DModelPosSet(obj->model[4], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[4], 0.0f);
    Hu3DMotionSpeedSet(obj->model[4], 0.0f);
    Hu3DModelTPLvlInit(obj->model[4]);
    data->unk20 = 255.0f;
    Hu3DModelTPLvlSet(obj->model[4], 0xFF);
    obj->model[5] = Hu3DModelRead(0x230007, 0x29D);
    Hu3DModelPosSet(obj->model[5], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[5], 0.0f);
    Hu3DMotionSpeedSet(obj->model[5], 0.0f);
    obj->model[6] = Hu3DModelRead(0x230008, 0x29D);
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    Hu3DMotionTimeSet(obj->model[6], 3.0f);
    Hu3DMotionSpeedSet(obj->model[6], 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.5f, 1.5f, 1.5f);
    obj->model[7] = Hu3DModelRead(0x230009, 0x29D);
    Hu3DModelPosSet(obj->model[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[7], 1.5f, 1.5f, 1.5f);
    Hu3DMotionAttrSet(obj->model[7], 2, 2);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[4], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[5], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[6], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[7], HU3D_CAM1);
    obj->func = m202_SoloObjMain;
}

void m202_SoloObjCreate(void) {
    u16 player = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            omObjData *obj;

            switch (i) {
                case 0:
                    player = 0;
                    break;
                case 1:
                    player = 1;
                    break;
                case 2:
                    player = 2;
                    break;
                case 3:
                    player = 3;
                    break;
            }
            obj = omAddObj(0x2BC, 9, 0x3C, -1, m202_SoloObjInit);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            m202_objWorkTbl[21].unk00 = obj;
        }
    }
}

void m202_TeamComInputCalc(omObjData *arg0) {
    CoconutConkData *coconuts[3];
    omObjData *objs[3];
    CoconutConkData *data = &m202_objWorkTbl[22 + arg0->work[1]];
    u16 player = arg0->work[0];
    u8 dir = rand8();
    omObjData *target = m202_objWorkTbl[21].unk00;
    f32 minDist;
    s16 closest;
    s16 i;

    if (m202_phase == 2) {
        u8 difficulty = GwPlayer[player].cpu_difficulty;

        if ((difficulty == 0 && dir < 50) || (difficulty == 1 && dir < 80) || (difficulty == 2 && dir < 100) ||
            (difficulty == 3 && dir < 130)) {
            if (target->trans.x < arg0->trans.x) {
                dir = 1;
            } else {
                dir = 2;
            }
        }
    }
    if (m202_teamComNum == 3 && m202_soloStillCnt >= m202_teamComDelay) {
        closest = 0;
        minDist = 5000.0f;
        for (i = 0; i < 3; i++) {
            coconuts[i] = &m202_objWorkTbl[22 + i];
            objs[i] = coconuts[i]->unk00;
        }
        for (i = 0; i < 3; i++) {
            if (minDist >= fabs(objs[i]->trans.x - target->trans.x)) {
                closest = i;
                minDist = fabs(objs[i]->trans.x - target->trans.x);
            }
        }
        dir = 0;
        if (arg0->work[1] == closest) {
            if (arg0->trans.x > target->trans.x) {
                dir = 1;
            } else if (arg0->trans.x < target->trans.x) {
                dir = 2;
            }
            if (arg0->trans.x + 29.0f > target->trans.x - 40.0f && arg0->trans.x - 29.0f < target->trans.x + 40.0f) {
                HuPadBtnDown[arg0->work[3]] |= A_BUTTON;
                HuPadBtnDown[arg0->work[3]] |= Z_TRIG;
            }
        } else {
            HuPadBtnDown[arg0->work[3]] |= A_BUTTON;
        }
    }
    data->unk06--;
    if (data->unk06 <= 0) {
        data->unk06 = 0;
    }
    if (arg0->trans.y > 512.0f) {
        dir = 0;
    }
    if (dir == 0 && data->unk06 == 0) {
        data->unk08 = 0;
    }
    if (dir % 5 == 1 && data->unk06 == 0) {
        data->unk08 = -(rand8() & 0x1F) - 30;
        data->unk06 = 15;
    }
    if (dir % 5 == 2 && data->unk06 == 0) {
        data->unk08 = (rand8() & 0x1F) + 30;
        data->unk06 = 15;
    }
    HuPadStkX[arg0->work[3]] = data->unk08;
    if (rand8() % 70 == 0) {
        HuPadBtnDown[arg0->work[3]] |= A_BUTTON;
    }
    if (rand8() % 5 == 0) {
        HuPadBtnDown[arg0->work[3]] |= Z_TRIG;
    }
}

void m202_TeamPadInput(omObjData *);
void m202_TeamUpdate(omObjData *);

void m202_TeamComInput(omObjData *arg0) {
    m202_TeamComInputCalc(arg0);
}

void m202_TeamPadInput(omObjData *arg0) {
}

void m202_TeamUpdate(omObjData *arg0) {
    CoconutConkData *data = &m202_objWorkTbl[22 + arg0->work[1]];
    MgPlayerWork *work = arg0->data;
    CoconutConkData *target;
    f32 minDist;
    s16 closest;
    s16 i;

    if (HuPadStkY[arg0->work[3]] >= 5) {
        HuPadStkY[arg0->work[3]] = 0;
    }
    if (HuPadStkY[arg0->work[3]] < -4) {
        HuPadStkY[arg0->work[3]] = 0;
    }
    MgPlayerObjMain(arg0);
    if (Hu3DData[arg0->model[7]].motTime == 0.0f) {
        Hu3DModelAttrSet(arg0->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    if (work->unk5C == 0x200 && work->unk50 == 0x80 && data->unk04 == 0) {
        data->unk04 = 1;
        if (m202_coconutFallNum < 3) {
            m202_coconutFallNum++;
            MgPlayerEffSet(arg0, 7, arg0->trans.x, arg0->trans.y, arg0->trans.z, 0.0f, 0.0f);
            minDist = 3000.0f;
            closest = 0;
            for (i = 0; i < 6; i++) {
                s32 idx = i;

                if (minDist > fabs(arg0->trans.x - m202_treePosXTbl[idx])) {
                    minDist = fabs(arg0->trans.x - m202_treePosXTbl[idx]);
                    closest = i;
                }
            }
            target = &m202_objWorkTbl[6 + closest];
            if (target->unk04 == 0) {
                target->unk04 = 1;
                data->unk16 = 1;
            }
            switch (closest) {
                case 0:
                case 3:
                    for (i = 0; i < 3; i++) {
                        CoconutConkData *coconut = &m202_objWorkTbl[12 + i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
                case 1:
                case 4:
                    for (i = 3; i < 6; i++) {
                        CoconutConkData *coconut = &m202_objWorkTbl[12 + i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
                case 2:
                case 5:
                    for (i = 6; i < 9; i++) {
                        CoconutConkData *coconut = &m202_objWorkTbl[12 + i];
                        omObjData *obj = coconut->unk00;

                        if (coconut->unk04 == 0) {
                            coconut->unk04 = 1;
                            obj->trans.x = arg0->trans.x;
                            break;
                        }
                    }
                    break;
            }
        }
    }
    if (work->unk5C != 0x200 && work->unk50 != 0x80 && arg0->trans.y <= 512.0f) {
        data->unk04 = 0;
    }
}

void m202_TeamObjMain(omObjData *arg0) {
    MgPlayerWork *works[3];
    CoconutConkData *datas[3];
    omObjData *objs[3];
    CoconutConkData *data = &m202_objWorkTbl[22 + arg0->work[1]];
    MgPlayerWork *work = arg0->data;
    s16 i;

    if (m202_phase != 2) {
        m202_PadClear(arg0->work[0]);
    }
    data->unk18 = arg0->trans.x;
    switch (m202_phase) {
        case 2:
            if (m202_timer > 0 && m202_soloHitF == 0) {
                if (!(GwPlayer[arg0->work[0]].stat & 1)) {
                    m202_TeamPadInput(arg0);
                } else {
                    m202_TeamComInput(arg0);
                }
            }
            m202_TeamUpdate(arg0);
            break;
        case 3:
            if (arg0->trans.y > 512.0f) {
                if (++data->unk0C > 30000) {
                    data->unk0C = 0;
                }
                if (data->unk0C < 70) {
                    HuPadStkX[arg0->work[3]] = -40;
                } else if (data->unk0C < 140) {
                    HuPadStkX[arg0->work[3]] = 40;
                }
                if (data->unk0C >= 140) {
                    m202_TeamComInput(arg0);
                }
                m202_TeamUpdate(arg0);
                break;
            }
            if (work->unk3C != 0.0f) {
                HuPadStkX[arg0->work[3]] = 0;
                HuPadStkY[arg0->work[3]] = -40;
            }
            for (i = 0; i < 3; i++) {
                datas[i] = &m202_objWorkTbl[22 + i];
                objs[i] = datas[i]->unk00;
                works[i] = objs[i]->data;
            }
            if (objs[0]->trans.y <= 512.0f && works[0]->unk3C == 0.0f &&
                (works[0]->unk50 == 0 || works[0]->unk50 == 0x80) && works[0]->unk5C == 2 &&
                objs[1]->trans.y <= 512.0f && works[1]->unk3C == 0.0f &&
                (works[1]->unk50 == 0 || works[1]->unk50 == 0x80) && works[1]->unk5C == works[0]->unk5C &&
                objs[2]->trans.y <= 512.0f && works[2]->unk3C == 0.0f &&
                (works[2]->unk50 == 0 || works[2]->unk50 == 0x80) && works[2]->unk5C == works[1]->unk5C) {
                m202_readyState = 3;
            }
            MgPlayerObjMain(arg0);
            break;
        case 4:
            if (data->unk0E == 0) {
                if (m202_soloHitF == 0) {
                    MgPlayerMotSet(arg0, 14);
                    data->unk0E = 1;
                } else {
                    MgPlayerMotSet(arg0, 13);
                    data->unk0E = 1;
                    HuAudCharVoicePlay((m202_voiceChrTbl[GwPlayer[arg0->work[0]].chr] << 16) | 0x2F);
                }
            }
            break;
        case 0:
        case 1:
        case 5:
            break;
    }
    if (m202_phase != 2 && m202_phase != 3) {
        MgPlayerObjMain(arg0);
    }
    if (arg0->trans.x < -450.0f) {
        arg0->trans.x = -450.0f;
    }
    if (arg0->trans.x > 450.0f) {
        arg0->trans.x = 450.0f;
    }
    if (work->unk53[1] != -1) {
        arg0->trans.x = data->unk18;
    }
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (data->unk16 > 0) {
        data->unk16++;
    }
    if (data->unk16 >= 4) {
        HuAudPlayerFXPlay(0x313, arg0->work[0]);
        data->unk16 = 0;
    }
}

void m202_TeamObjInit(omObjData *arg0) {
    u16 character = GwPlayer[arg0->work[0]].chr;
    s32 modelFile;
    s32 motionFile;
    MgPlayerWork *work;
    u8 slot;

    if (GwPlayer[arg0->work[0]].stat & 1) {
        m202_teamComNum++;
        switch (GwPlayer[arg0->work[0]].cpu_difficulty) {
            case 0:
                if (m202_teamComDelay > 60) {
                    m202_teamComDelay = 60;
                }
                break;
            case 1:
                if (m202_teamComDelay > 30) {
                    m202_teamComDelay = 30;
                }
                break;
            case 2:
                if (m202_teamComDelay > 15) {
                    m202_teamComDelay = 15;
                }
                break;
            case 3:
                if (m202_teamComDelay > 10) {
                    m202_teamComDelay = 10;
                }
                break;
        }
    }
    modelFile = omCharModelNoTbl[character][0];
    motionFile = omCharMotTbl[character][0];
    MgPlayerParamReset();
    MgPlayerCreate(arg0, modelFile, motionFile, ((u16 *)arg0->work)[1], 0x2B9, 0x2A9);
    work = arg0->data;
    work->unkEC = 0;
    Hu3DModelObjAttrSet(arg0->model[1], 0x80000000, 0);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_AA_MASK, HU3D_ATTR_AA);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_ON);
    Hu3DModelRemakeStatic(arg0->model[1]);
    Hu3DModelDynamicFree(arg0->model[1]);
    arg0->model[7] = Hu3DModelRead(8, 0x2BD);
    arg0->model[6] = Hu3DModelRead(5, 0x2BD);
    MgPlayerMotLoad(arg0, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(arg0, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(arg0, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(arg0, 6, CharMotionDataNumGet(character, 4), 1, 0x13);
    MgPlayerMotLoad(arg0, 8, CharMotionDataNumGet(character, 6), 1, 0x1B);
    MgPlayerMotLoad(arg0, 0x12, CharMotionDataNumGet(character, 0xF), 2, 0);
    MgPlayerMotRead(arg0, 0x15, CharMotionDataNumGet(character, 0x1F), 0, 0);
    MgPlayerMotLoad(arg0, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 0x78);
    MgPlayerMotLoad(arg0, 0xE, CharMotionDataNumGet(character, 0x36), 1, 0x3E7);
    MgPlayerMotSet(arg0, 0);
    mgFieldStat = 1;
    slot = rand8() % 3;
    while (TRUE) {
        if (slot != m202_teamSlotTbl[0] && slot != m202_teamSlotTbl[1]) {
            m202_teamSlotTbl[m202_teamSlotNum] = slot;
            m202_teamSlotNum++;
            switch (slot) {
                case 0:
                    arg0->trans.x = -300.0f;
                    break;
                case 1:
                    arg0->trans.x = 0.0f;
                    break;
                case 2:
                    arg0->trans.x = 300.0f;
                    break;
            }
            break;
        }
        slot++;
        if (slot >= 3) {
            slot = 0;
        }
    }
    arg0->trans.y = 512.0f;
    arg0->trans.z = -225.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[7], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[6], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM1);
    Hu3DModelCameraSet(arg0->model[7], HU3D_CAM1);
    Hu3DModelCameraSet(arg0->model[6], HU3D_CAM1);
    MgPlayerMapAttrSet(arg0, 0, 2);
    m202_PadClear(arg0->work[0]);
    arg0->func = m202_TeamObjMain;
}

void m202_TeamObjCreate(void) {
    u16 player = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            CoconutConkData *data;
            omObjData *obj;

            switch (i) {
                case 0:
                    player = 0;
                    break;
                case 1:
                    player = 1;
                    break;
                case 2:
                    player = 2;
                    break;
                case 3:
                    player = 3;
                    break;
            }
            data = &m202_objWorkTbl[22 + count];
            obj = omAddObj(0x28A, 9, 0x3C, -1, m202_TeamObjInit);
            obj->work[0] = player;
            obj->work[3] = GwPlayer[player].pad;
            data->unk00 = obj;
            obj->work[1] = count++;
            mgPlayerObjTbl[mgPlayerObjNum] = obj;
            mgPlayerObjNum++;
        }
    }
}

void m202_CameraViewInit(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1270.8f;
        CRotM[i].x = 350.94f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 415.0f;
        CenterM[i].z = -115.0f;
    }
}

void m202_ExitObjMain(omObjData *arg0) {
    u8 i;

    for (i = 0; i < 3; i++) {
        DataClose(m202_faceAnimDataTbl[i]);
    }
    Hu3DAnimKill(m202_faceAnim);
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void m202_ExitWaitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = m202_ExitObjMain;
    }
}

void m202_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        arg0->func = m202_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m202_MainObjMain(omObjData *arg0) {
    u8 chars[8];
    CoconutConkData *datas[3];
    omObjData *objs[3];
    omObjData *obj = m202_objWorkTbl[21].unk00;
    s16 i;
    s16 j;

    for (i = 0; i < 3; i++) {
        datas[i] = &m202_objWorkTbl[22 + i];
        objs[i] = datas[i]->unk00;
    }

    switch (m202_phase) {
        case 0:
            if (m202_timer == 13) {
                HuAudFXPlay(0x314);
                m202_timer = 14;
            } else if (m202_timer < 13) {
                m202_timer++;
            }
            if (m202_readyState == 0) {
                m202_PhaseSet(1);
                m202_timer = 1;
                HuAudSeqPlay(0x30);
            }
            break;
        case 1:
            if (--m202_timer == 0) {
                GMesCreate(GMES_MES_4);
            }
            if (GMesStatGet() == 0) {
                m202_PhaseSet(2);
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                m202_timer = 901;
            }
            break;
        case 2:
            if (m202_timer > 0) {
                m202_timer--;
                GMesTimerValueSet((m202_timer + 29) / 30);
            } else if (m202_soloHitF == 0) {
                GMesTimerEnd();
                m202_PhaseSet(3);
                GMesCreate(GMES_MES_15);
                m202_soloHitF = 0;
                m202_timer = -15;
                HuAudSeqFadeOut(120);
                HuAudFXStop(m202_rollSeNo);
            }
            if (m202_soloHitF == 1) {
                GMesTimerEnd();
                m202_PhaseSet(3);
                GMesCreate(GMES_MES_15);
                m202_soloHitF = 1;
                m202_timer = -15;
                HuAudSeqFadeOut(120);
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                if (m202_timer >= 0) {
                    if (m202_readyState == 3) {
                        m202_PhaseSet(4);
                        m202_timer = -1;
                        break;
                    }
                }
                if (m202_timer < 0) {
                    m202_timer++;
                }
            }
            break;
        case 4:
            if (m202_timer == -1) {
                m202_timer = 0;
                j = 0;
                if (m202_soloHitF == 0) {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group == 0) {
                            chars[0] = GwPlayer[i].chr;
                        }
                    }
                    GMesCreate(GMES_MES_MG_WINNER, chars[0]);
                    HuAudSeqPlay(0x65);
                    GwPlayer[obj->work[0]].bonusCoin = 10;
                } else {
                    for (i = 0; i < 4; i++) {
                        if (GwPlayer[i].group != 0) {
                            chars[j] = GwPlayer[i].chr;
                            j++;
                        }
                    }
                    GMesCreate(GMES_MES_MG_WINNERS_3, chars[0], chars[1], chars[2]);
                    HuAudSeqPlay(0x66);
                    for (i = 0; i < 3; i++) {
                        GwPlayer[objs[i]->work[0]].bonusCoin = 10;
                    }
                }
            }
            if (GMesStatGet() == 0) {
                if (m202_timer >= 15) {
                    m202_PhaseSet(5);
                    m202_timer = -1;
                }
                m202_timer++;
            }
            break;
        case 5:
            if (m202_timer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                arg0->func = m202_ExitWaitObjMain;
                m202_timer++;
            }
            break;
    }
}

void m202_MainObjInit(omObjData *arg0) {
    s16 i;

    MgFlowStatSet(MG_STATE_PLAY);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m202_timer = 0;
    m202_phase = 0;
    m202_readyState = 100;
    for (i = 0; i < 3; i++) {
        m202_teamSlotTbl[i] = 5;
    }
    m202_teamSlotNum = 0;
    m202_soloStillCnt = 0;
    m202_teamComNum = 0;
    m202_teamComDelay = 500;
    m202_soloHitF = 0;
    m202_coconutFallNum = 0;
    m202_rollSeNo = -1;
    m202_rollSePitch = -400;
    m202_rollSeVol = 0;
    m202_rollSeTimer = 0;
    m202_MapObjCreate();
    m202_BackObjCreate();
    m202_ForeObjCreate();
    m202_SeaObjCreate();
    m202_CloudObjCreate();
    m202_SoloObjCreate();
    m202_TeamObjCreate();
    m202_CoconutObjCreateAll();
    m202_TreeObjCreateAll();
    m202_CameraViewInit();
    arg0->func = m202_MainObjMain;
}

void m202_Dummy(void) {
}

void m202_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, m202_cameraViewTbl[i].scissorX, m202_cameraViewTbl[i].scissorY,
                   m202_cameraViewTbl[i].scissorWidth, m202_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m202_cameraViewTbl[i].viewportScale.x, m202_cameraViewTbl[i].viewportScale.y,
                    m202_cameraViewTbl[i].viewportScale.z, m202_cameraViewTbl[i].viewportTranslate.x,
                    m202_cameraViewTbl[i].viewportTranslate.y, m202_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m202_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m202_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    m202_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(0, -84.0f, 49.0f, 69.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -84.0f, 49.0f, 69.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -84.0f, 49.0f, 69.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m202_fontMesTbl, 0);
    GMesFontMesCreate(m202_fontMesTbl, 1);
    omAddObj(0x5DC, 0, 0, -1, m202_MainObjInit);
    omAddObj(0x5DC, 0, 0, -1, m202_ExitCheckObjMain);
    m202_ObjWorkInit();
    MgFlowInit(&m202_mgFlow);
}

// Keep this table after the functions to preserve the original rodata order.
const s16 m202_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
