#include "common.h"
#include "game/overlays/minigame.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ s16 unk_42;
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ Vec unk_78;
} HideAndSneakWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ s8 unk_01; // movement step
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ s8 unk_05;
} HideAndSneakHiderMove; // sizeof 0x06

typedef struct {
    /* 0x00 */ s8 unk_00; // nonzero when the solo player is CPU controlled
    /* 0x01 */ s8 unk_01; // CPU state
    /* 0x02 */ s8 unk_02; // stick X
    /* 0x03 */ s8 unk_03; // timer
    /* 0x04 */ s8 unk_04; // duration
    /* 0x05 */ s8 unk_05; // direction change count
    /* 0x06 */ s8 unk_06; // direction change limit
    /* 0x07 */ s8 unk_07; // target column
} HideAndSneakSoloCpu;    // sizeof 0x08

typedef struct {
    /* 0x00 */ s8 count;
    /* 0x01 */ s8 slots[3];
} HideAndSneakSpot; // sizeof 0x04

typedef struct {
    /* 0x00 */ s16 sprite;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk_06;
} HideAndSneakSprite; // sizeof 0x08

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} HideAndSneakSpritePos; // sizeof 0x04

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} HideAndSneakCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s8 unk_00;    // D_8010E174
    /* 0x01 */ s8 unk_01[4]; // D_8010E175
    /* 0x06 */ s16 unk_06;   // D_8010E17A
    /* 0x08 */ s8 unk_08;    // D_8010E17C
    /* 0x09 */ s8 unk_09[3]; // D_8010E17D
    /* 0x0C */ s8 unk_0C;    // D_8010E180
    /* 0x0D */ s8 unk_0D;    // D_8010E181
    /* 0x0E */ s8 unk_0E[4]; // D_8010E182
    /* 0x12 */ s8 unk_12;    // D_8010E186
} HideAndSneakRoundBss;       // sizeof 0x14

typedef struct {
    /* 0x00 */ s8 unk_00;    // D_8010E1A8
    /* 0x01 */ s8 unk_01[3]; // D_8010E1A9
    /* 0x04 */ s8 unk_04;    // D_8010E1AC
    /* 0x05 */ s8 unk_05;    // D_8010E1AD
    /* 0x06 */ s8 unk_06[3]; // D_8010E1AE
    /* 0x09 */ s8 unk_09;    // D_8010E1B1
    /* 0x0A */ s8 unk_0A;    // D_8010E1B2
    /* 0x0B */ s8 unk_0B;    // D_8010E1B3
} HideAndSneakResultBss;       // sizeof 0xC

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
// Fields of m206_roundBss (aliased in undefined_syms.txt).
extern s8 m206_roundNo;
extern s8 m206_signSpotTbl[4];
extern s16 m206_timer;
extern s8 m206_seekerSpotNo;
extern s8 m206_teamPlayerNoTbl[3];
extern s8 m206_phase;
extern s8 m206_hiderLineupNum;
extern s8 m206_spotOpenTbl[4];
extern s8 m206_seekerChr;
// Fields of m206_resultBss (aliased in undefined_syms.txt).
extern s8 m206_seekerPlayerNo;
extern s8 m206_hiderFoundTbl[3];
extern s8 m206_spotSeF;
extern s8 m206_hiderFoundNum;
extern s8 m206_teamChrTbl[3];
extern s8 m206_hiderLineupNo;
extern s8 m206_timeUpF;
extern s8 m206_spotFadeMode;

void m206_StageObjMain(omObjData *object);
void m206_StageObjInit(omObjData *);
void m206_SeekerObjMain(omObjData *object);
void m206_SeekerObjInit(omObjData *);
void m206_HiderStepSeUpdate(omObjData *object);
void m206_HiderObjMain(omObjData *object);
void m206_HiderObjInit(omObjData *object);
void m206_SpotFadeSet(omObjData *object);
void m206_SpotObjMain(omObjData *);
void m206_SpotObjInit(omObjData *);
void m206_IconDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m206_IconObjMain(omObjData *object);
void m206_IconObjInit(omObjData *);
void m206_SignObjMain(omObjData *object);
void m206_SignObjInit(omObjData *);
void m206_MainObjMain(omObjData *object);
void m206_MainObjInit(omObjData *object);
void m206_ObjectSetup(void);
s8 m206_HiderPath0To1(omObjData *object);
s8 m206_HiderPath1To0(omObjData *object);
s8 m206_HiderPath0To2(omObjData *object);
s8 m206_HiderPath2To0(omObjData *object);
s8 m206_HiderPath0To3(omObjData *object);
s8 m206_HiderPath3To0(omObjData *object);
s8 m206_HiderPath1To2(omObjData *object);
s8 m206_HiderPath2To1(omObjData *object);
s8 m206_HiderPath1To3(omObjData *object);
s8 m206_HiderPath3To1(omObjData *object);
s8 m206_HiderPath2To3(omObjData *object);
s8 m206_HiderPath3To2(omObjData *object);
s8 m206_HiderPathNone(omObjData *object);

s16 m206_signXTbl[5][4] = {
    { 800, 800, 800, 800 },
    { 0, 800, 800, 800 },
    { -65, 65, 800, 800 },
    { -130, 0, 130, 800 },
    { -195, -65, 65, 195 },
};

s32 m206_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };

s8 m206_slotOrderTbl[6][3] = {
    { 0, 1, 2 },
    { 0, 2, 1 },
    { 1, 0, 2 },
    { 1, 2, 0 },
    { 2, 0, 1 },
    { 2, 1, 0 },
};

f32 m206_hiderOutXTbl[3] = { -400.0f, -140.0f, 520.0f };
f32 m206_hiderOutZTbl[3] = { -500.0f, -1200.0f, -810.0f };
f32 m206_spotXTbl[4] = { -400.0f, -250.0f, 150.0f, 475.0f };
f32 m206_spotZTbl[4] = { -850.0f, -1600.0f, -575.0f, -1350.0f };

s8 m206_spotOfsXTbl[3][3] = {
    { 0, 0, 0 },
    { -60, 60, 0 },
    { -120, 0, 120 },
};

f32 m206_lineupXTbl[3][3] = {
    { 0.0f, 0.0f, 0.0f },
    { 110.0f, -110.0f, 0.0f },
    { 220.0f, 0.0f, -220.0f },
};

s8 (*m206_hiderPath0Tbl[4])(omObjData *) = {
    m206_HiderPathNone,
    m206_HiderPath0To1,
    m206_HiderPath0To2,
    m206_HiderPath0To3,
};

s8 (*m206_hiderPath1Tbl[4])(omObjData *) = {
    m206_HiderPath1To0,
    m206_HiderPathNone,
    m206_HiderPath1To2,
    m206_HiderPath1To3,
};

s8 (*m206_hiderPath2Tbl[4])(omObjData *) = {
    m206_HiderPath2To0,
    m206_HiderPath2To1,
    m206_HiderPathNone,
    m206_HiderPath2To3,
};

s8 (*m206_hiderPath3Tbl[4])(omObjData *) = {
    m206_HiderPath3To0,
    m206_HiderPath3To1,
    m206_HiderPath3To2,
    m206_HiderPathNone,
};

s16 m206_spotMdlTbl[4] = { 4, 5, 6, 7 };

extern const char *m206_spotTexNameTbl[4];
extern const char *m206_spotTexNameBTbl[4];
extern s16 m206_iconSprTbl[4];
extern HideAndSneakSpritePos m206_iconPosTbl[4];
extern s16 m206_signAnimTbl[4];
extern s32 m206_cameraInitF;
extern HideAndSneakCamera m206_cameraViewTbl[2];
extern const s16 m206_fontMesTbl[];

HideAndSneakSprite m206_iconTbl[4] BSS;
s8 m206_roundState BSS;
s8 m206_slotOrderNo BSS;
s8 m206_signNum BSS;
u8 m206_signNumPad[4] BSS; /* Unreferenced. */
HideAndSneakHiderMove m206_hiderMoveTbl[4] BSS;
// Work slots: [0] obj 0x1F4, [1] solo player, [2..4] team players (by work[1]), [5..8] and [9..12] per-player objects,
// [13] screen fade (unk_04 is its alpha)
HideAndSneakWork m206_objWorkTbl[50] BSS;
HideAndSneakSoloCpu m206_seekerCom BSS;
s8 m206_roundDoneBits BSS;
s16 m206_mainTimer BSS;
HideAndSneakRoundBss m206_roundBss BSS;
HideAndSneakSpot m206_spotHiderTbl[4] BSS;
HuSprAnimData *m206_iconSprDataTbl[4] BSS;
HideAndSneakResultBss m206_resultBss BSS;

void m206_Executor(void) {
    m206_ObjectSetup();
}

f32 m206_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m206_RandMulGet(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void m206_ObjWorkInit(void) {
    HideAndSneakWork *work;
    u32 i;

    for (i = 0, work = m206_objWorkTbl; i < 50; i++, work++) {
        work->obj = NULL;
        work->unk_04 = 0;
        work->unk_06 = 0;
        work->unk_08 = 0;
        work->unk_0A = 0;
        work->unk_0C = 0;
        work->unk_0E = 0;
        work->unk_10 = 0;
        work->unk_12 = 0;
        work->unk_14 = 0;
        work->unk_16 = 0;
        work->unk_18 = 0;
        work->unk_1C = 0;
        work->unk_20 = 0;
        work->unk_24 = 0;
        work->unk_28 = 0;
        work->unk_2C = 0;
        work->unk_30 = 0;
        work->unk_34 = 0;
        work->unk_38 = 0;
        work->unk_3C = 0;
        work->unk_40 = -1;
        work->unk_42 = -1;
        work->unk_44.x = work->unk_44.y = work->unk_44.z = 0.0f;
        work->unk_50.x = work->unk_50.y = work->unk_50.z = 0.0f;
        work->unk_5C.x = work->unk_5C.y = work->unk_5C.z = 0.0f;
        work->unk_68 = 0.0f;
        work->unk_6C = 0.0f;
        work->unk_70 = 0.0f;
        work->unk_74 = 0.0f;
        work->unk_78.x = work->unk_78.y = work->unk_78.z = 0.0f;
    }
}

void m206_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

Gfx **m206_GfxRectTexInit(Gfx **gfxPos) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gfx = *gfxPos;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, geometryMode);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    *gfxPos = gfx;
    return gfxPos;
}

Gfx **m206_GfxRectXluInit(Gfx **gfxPos) {
    u32 geometryMode = G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH;
    Gfx *gfx = *gfxPos;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, geometryMode);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    *gfxPos = gfx;
    return gfxPos;
}

Gfx **m206_GfxPrimAlphaSet(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

void m206_CameraDebugPrint(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 dx = (arg0 - arg2) * 5.0f;
    f32 dz = (arg1 - arg3) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = m206_AngleAdd(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void m206_CameraDebugPad(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)HuPadBtn[conNo] & D_JPAD) {
        for (i = 0; i < 2; i++) {
            CRotM[i].x = m206_AngleAdd(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)HuPadBtn[GwPlayer[0].pad] & U_JPAD) {
        for (i = 0; i < 2; i++) {
            CRotM[i].x = m206_AngleAdd(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & L_JPAD) {
        for (i = 0; i < 2; i++) {
            CRotM[i].y = m206_AngleAdd(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & R_JPAD) {
        for (i = 0; i < 2; i++) {
            CRotM[i].y = m206_AngleAdd(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & A_BUTTON) {
        for (i = 0; i < 2; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & B_BUTTON) {
        for (i = 0; i < 2; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & L_CBUTTONS) {
        for (i = 0; i < 2; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & R_CBUTTONS) {
        for (i = 0; i < 2; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & U_CBUTTONS) {
        for (i = 0; i < 2; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & D_CBUTTONS) {
        for (i = 0; i < 2; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if (HuPadBtnDown[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 2; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

const char m206_emptyStr[] = "";

s32 m206_RandGet(s32 arg0) {
    return rand8() % arg0;
}

void m206_MotSet(omObjData *object, u16 motionIndex, s16 arg2) {
    Hu3DMotionModelSet(object->model[0], object->motion[motionIndex]);
    Hu3DMotionAttrSet(object->model[0], arg2, arg2);
}

void m206_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

s8 m206_RotYTurn(omObjData *object, f32 target) {
    f32 current = object->rot.y;
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 10.0f) {
        object->rot.y = target;
    } else {
        if (current < target) {
            if (diff > 180.0f) {
                object->rot.y = m206_AngleAdd(object->rot.y, -10.0f);
            } else {
                object->rot.y = m206_AngleAdd(object->rot.y, 10.0f);
            }
        } else if (target < current) {
            if (diff > 180.0f) {
                object->rot.y = m206_AngleAdd(object->rot.y, 10.0f);
            } else {
                object->rot.y = m206_AngleAdd(object->rot.y, -10.0f);
            }
        } else {
            return 0;
        }
        return 1;
    }
    return 0;
}

void m206_StageObjMain(omObjData *object) {
}

void m206_StageObjInit(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[0];

    work->unk_44.x = 160.0f;
    work->unk_44.y = 120.0f;
    work->unk_40 = HuSprAnimDataRead(0x270000);
    work->unk_42 = espEntry(work->unk_40, 0, 0);
    espAttrSet(work->unk_42, 0x5000);
    espPosSet(work->unk_42, work->unk_44.x, work->unk_44.y);
    work->unk_44.x = 160.0f;
    work->unk_44.y = 231.0f;
    work->unk_40 = HuSprAnimDataRead(0x270001);
    work->unk_42 = espEntry(work->unk_40, 0, 0);
    espAttrSet(work->unk_42, 0x1000);
    espPosSet(work->unk_42, work->unk_44.x, work->unk_44.y);
    object->model[0] = Hu3DModelRead(0x270003, 0x299);
    object->model[1] = Hu3DModelRead(0x270002, 0x299);
    object->model[2] = Hu3DModelRead(0x27000C, 0x299);
    Hu3DMotionSpeedSet(object->model[0], 0.0f);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 4.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
    object->func = m206_StageObjMain;
}

void m206_StageObjCreate(void) {
    m206_objWorkTbl[0].obj = omAddObj(0x1F4, 4, 2, -1, m206_StageObjInit);
}

void m206_SeekerMotSet(omObjData *object, s8 motion) {
    HideAndSneakWork *work = &m206_objWorkTbl[1];
    s16 mode = 0;

    if (work->unk_06 != motion) {
        switch (motion) {
            case 0:
            case 1:
            case 3:
                mode = 2;
                break;
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
                mode = 0;
                break;
        }
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        m206_MotShiftSet(object, motion, 0, 10, mode);
        if (motion == 6) {
            HuAudCharVoicePlay((m206_voiceChrTbl[GwPlayer[object->work[0]].chr] << 16) | 0x30);
        }
        work->unk_06 = motion;
    }
}

s8 m206_SeekerComInput(omObjData *object) {
    HideAndSneakSoloCpu *cpu = &m206_seekerCom;

    if (cpu->unk_00 != 0) {
        m206_PadClear(object->work[0]);
        // Reading the state through the global rather than `cpu` is required to match.
        switch (m206_seekerCom.unk_01) {
            case 0:
                cpu->unk_05 = 0;
                cpu->unk_06 = m206_RandGet(9 - m206_signNum);
                cpu->unk_02 = m206_RandGet(2) * 40 - 20;
                cpu->unk_03 = 0;
                cpu->unk_04 = (m206_signNum - 1) * 9;
                cpu->unk_07 = m206_RandGet(m206_signNum);
                cpu->unk_01++;
                break;
            case 1:
                HuPadStkX[object->work[3]] = cpu->unk_02;
                cpu->unk_03++;
                if (cpu->unk_03 >= cpu->unk_04) {
                    cpu->unk_05++;
                    if (cpu->unk_05 >= cpu->unk_06) {
                        cpu->unk_01 = 2;
                    } else {
                        cpu->unk_02 = -cpu->unk_02;
                        cpu->unk_03 = 0;
                        cpu->unk_04 = (m206_signNum - 1) * 18;
                    }
                }
                break;
            case 2:
                if (m206_signXTbl[m206_signNum][cpu->unk_07] < object->trans.x) {
                    HuPadStkX[object->work[3]] = -20;
                } else if (object->trans.x < m206_signXTbl[m206_signNum][cpu->unk_07]) {
                    HuPadStkX[object->work[3]] = 20;
                } else if (object->trans.x == m206_signXTbl[m206_signNum][cpu->unk_07]) {
                    cpu->unk_01 = 0;
                    return 1;
                }
                break;
        }
    }
    return 0;
}

void m206_SeekerObjMain(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[1];
    s16 pad = object->work[3];
    s16 x;
    s16 i;

    if (m206_phase != 2) {
        if (m206_phase >= 3) {
            if (m206_phase >= 5) {
                if (m206_hiderFoundNum == 3) {
                    m206_SeekerMotSet(object, 6);
                } else {
                    m206_SeekerMotSet(object, 7);
                }
            } else {
                m206_SeekerMotSet(object, 0);
            }
        }
        return;
    }
    switch (m206_roundState) {
        case 0:
            work->unk_0A = 0;
            m206_seekerCom.unk_01 = 0;
            m206_seekerSpotNo = -1;
            m206_SeekerMotSet(object, 3);
            break;
        case 1:
            break;
        case 2:
            if (m206_RotYTurn(object, 0.0f)) {
                m206_SeekerMotSet(object, 1);
            } else {
                m206_SeekerMotSet(object, 0);
            }
            break;
        case 3:
            if (m206_hiderFoundNum == 3) {
                m206_roundState = 6;
                m206_roundNo = 2;
                m206_timer = 0;
                break;
            }
            work->unk_0C = m206_SeekerComInput(object);
            if (work->unk_08 <= 0) {
                if (HuPadStkX[pad] < -10 && -((m206_signNum - 1) * 65) < object->trans.x) {
                    work->unk_08 = 1;
                    object->rot.y = 270.0f;
                    m206_SeekerMotSet(object, 1);
                }
            }
            if (work->unk_08 >= 0) {
                if (HuPadStkX[pad] > 10 && object->trans.x < (m206_signNum - 1) * 65) {
                    work->unk_08 = -1;
                    object->rot.y = 90.0f;
                    m206_SeekerMotSet(object, 1);
                }
            }
            x = object->trans.x;
            if (work->unk_08 == 0) {
                if ((m206_signNum == 4 && abs(x) == 195) || (m206_signNum == 3 && abs(x) == 130) || (m206_signNum == 2 && abs(x) == 65) || abs(HuPadStkX[pad]) <= 10) {
                    if (m206_RotYTurn(object, 0.0f)) {
                        m206_SeekerMotSet(object, 1);
                    } else {
                        m206_SeekerMotSet(object, 0);
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                if (x == m206_signXTbl[m206_signNum][i]) {
                    if ((HuPadBtnDown[pad] & 0x8000) || work->unk_0C != 0) {
                        m206_seekerSpotNo = m206_signSpotTbl[i];
                        m206_roundDoneBits = 1;
                        work->unk_08 = 0;
                        break;
                    }
                }
            }
            break;
        case 4:
            if (m206_timeUpF != 0) {
                m206_roundState = 5;
                break;
            }
            work->unk_08 = 0;
            if (m206_seekerSpotNo != -1) {
                if (work->unk_0A < 15) {
                    if (object->rot.y == 0.0f) {
                        work->unk_0A = 15;
                        break;
                    }
                    m206_RotYTurn(object, 0.0f);
                    m206_SeekerMotSet(object, 1);
                } else if (work->unk_0A == 15) {
                    HideAndSneakWork *works = &m206_objWorkTbl[9];

                    m206_MotSet(object, 2, 0);
                    work->unk_06 = 2;
                    Hu3DMotionSpeedSet(object->model[0], 0.5f);
                    Hu3DMotionSpeedSet(works[m206_seekerSpotNo].obj->model[0], 1.0f);
                } else if (work->unk_0A == 20) {
                    HuAudFXPlay(0x329);
                } else if (work->unk_0A == 24) {
                    Hu3DMotionSpeedSet(object->model[0], -0.5f);
                } else if (work->unk_0A >= 32) {
                    if (work->unk_0A < 50) {
                        if (m206_RotYTurn(object, 180.0f)) {
                            m206_SeekerMotSet(object, 1);
                        }
                    } else if (work->unk_0A == 50) {
                        m206_spotFadeMode = 1;
                    } else if (work->unk_0A == 65) {
                        if (m206_spotHiderTbl[m206_seekerSpotNo].count != 0) {
                            m206_SeekerMotSet(object, 4);
                        } else {
                            m206_SeekerMotSet(object, 5);
                        }
                    }
                }
                if (work->unk_0A == 95) {
                    m206_roundDoneBits = 1;
                }
            } else {
                if (m206_RotYTurn(object, 180.0f)) {
                    m206_spotFadeMode = 2;
                    m206_SeekerMotSet(object, 1);
                } else {
                    m206_SeekerMotSet(object, 5);
                }
                if (work->unk_0A == 70) {
                    m206_roundDoneBits = 1;
                }
            }
            work->unk_0A++;
            break;
        case 5:
            if (object->trans.x > 0.0f) {
                if (m206_RotYTurn(object, 270.0f)) {
                    m206_SeekerMotSet(object, 1);
                } else {
                    object->trans.x -= 6.5;
                }
            }
            if (object->trans.x < 0.0f) {
                if (m206_RotYTurn(object, 90.0f)) {
                    m206_SeekerMotSet(object, 1);
                } else {
                    object->trans.x += 6.5;
                }
            }
            if (object->trans.x == 0.0f) {
                if (m206_hiderFoundNum == 3 || m206_timeUpF != 0 || m206_roundNo == 2) {
                    if (m206_RotYTurn(object, 0.0f)) {
                        m206_SeekerMotSet(object, 1);
                    } else {
                        m206_SeekerMotSet(object, 0);
                        m206_roundDoneBits |= 1;
                    }
                } else {
                    if (m206_RotYTurn(object, 180.0f)) {
                        m206_SeekerMotSet(object, 1);
                    } else {
                        m206_SeekerMotSet(object, 0);
                        m206_roundDoneBits |= 1;
                    }
                }
            }
            break;
        case 6:
            break;
        case 7:
            break;
    }
    if (work->unk_08 > 0) {
        object->trans.x -= 6.5;
        x = object->trans.x;
        for (i = 0; i < m206_signNum; i++) {
            if (x == m206_signXTbl[m206_signNum][i]) {
                work->unk_08 = 0;
                break;
            }
        }
    }
    if (work->unk_08 < 0) {
        object->trans.x += 6.5;
        x = object->trans.x;
        for (i = 0; i < m206_signNum; i++) {
            if (x == m206_signXTbl[m206_signNum][i]) {
                work->unk_08 = 0;
                break;
            }
        }
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
}

void m206_SeekerObjInit(omObjData *object) {
    HideAndSneakSoloCpu *cpu = &m206_seekerCom;
    u16 character = GwPlayer[object->work[0]].chr;

    object->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharModelNoTbl[character][3], 0x2B9);
    omObjMotionRead(object, 0, CharMotionDataNumGet(character, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(character, 1));
    omObjMotionRead(object, 2, CharMotionDataNumGet(character, 0x14));
    omObjMotionRead(object, 3, CharMotionDataNumGet(character, 0x6C));
    omObjMotionRead(object, 4, CharMotionDataNumGet(character, 0x33));
    omObjMotionRead(object, 5, CharMotionDataNumGet(character, 0x3A));
    omObjMotionRead(object, 6, CharMotionDataNumGet(character, 0x30));
    omObjMotionRead(object, 7, CharMotionDataNumGet(character, 0x36));
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    object->rot.y = 180.0f;
    m206_MotSet(object, 0, 2);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    cpu->unk_00 = GwPlayer[object->work[0]].stat & 1;
    cpu->unk_01 = 0;
    object->work[3] = GwPlayer[object->work[0]].pad;
    object->func = m206_SeekerObjMain;
}

void m206_SeekerObjCreate(void) {
    omObjData *obj;
    s16 i;
    u16 playerIndex;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    switch (i) {
        case 0:
            playerIndex = 0;
            break;
        case 1:
            playerIndex = 1;
            break;
        case 2:
            playerIndex = 2;
            break;
        case 3:
            playerIndex = 3;
            break;
        default:
            playerIndex = 0;
            break;
    }
    obj = omAddObj(0x2BC, 3, 0xA, -1, m206_SeekerObjInit);
    obj->work[0] = playerIndex;
    m206_objWorkTbl[1].obj = obj;
    m206_seekerPlayerNo = obj->work[0];
    m206_seekerChr = GwPlayer[obj->work[0]].chr;
}

void m206_HiderHideCheck(omObjData *object) {
    s8 i;

    for (i = 0; i < 4; i++) {
        if (m206_spotOpenTbl[i] != 0) {
            if (m206_spotXTbl[i] - 150.0f < object->trans.x && object->trans.x < m206_spotXTbl[i] + 150.0f && m206_spotZTbl[i] - 20.0f < object->trans.z &&
                object->trans.z < m206_spotZTbl[i] + 100.0f) {
                Hu3DModelAttrSet(object->model[0], 4, 4);
                break;
            }
            Hu3DModelAttrSet(object->model[0], 4, 0);
        }
    }
}

void m206_HiderStepSeUpdate(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[2 + object->work[1]];

    if (object->work[2] == 0) {
        if (work->unk_14 != 0) {
            HuAudFXStop(work->unk_14);
        }
        work->unk_14 = PlayerFXPlay(0x28, object->work[0]);
    }
    object->work[2] = (object->work[2] + 1) % 11;
}

void m206_HiderMotSet(omObjData *object, s8 motion) {
    HideAndSneakWork *work = &m206_objWorkTbl[2 + object->work[0]];
    s8 mode = 0;

    if (work->unk_06 != motion) {
        switch (motion) {
            case 0:
                mode = 2;
                break;
            case 1:
                mode = 2;
                break;
            case 2:
                mode = 2;
                break;
            case 3:
                mode = 0;
                break;
            case 4:
                mode = 0;
                break;
        }
        m206_MotShiftSet(object, motion, 0, 15, mode);
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        work->unk_06 = motion;
        if (motion == 4) {
            HuAudCharVoicePlay((m206_voiceChrTbl[GwPlayer[object->work[0]].chr] << 16) | 0x30);
        }
    }
}

s8 m206_HiderComSpotGet(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];
    s8 candidates[4];
    s8 i;
    s8 count;

    for (i = 0, count = 0; i < 4; i++) {
        if (m206_spotOpenTbl[i] != 0 && entry->unk_04 != i) {
            candidates[count] = i;
            count++;
        }
    }
    return candidates[m206_RandGet(count)];
}

s8 m206_HiderPath0To1(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -700.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -700.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < -250.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath1To0(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -600.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -600.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -850.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -850.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < -400.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath0To2(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 0.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath2To0(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -50.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -50.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -850.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -850.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -400.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath0To3(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.z > -1100.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1100.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.x < 60.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.z > -1350.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1350.0f;
                entry->unk_01++;
            }
            break;
        case 3:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath3To0(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 150.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -1200.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -1200.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -400.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -400.0f;
                entry->unk_01++;
            }
            break;
        case 3:
            if (object->trans.z < -850.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -850.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath1To2(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 150.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath2To1(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 60.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -250.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath1To3(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -1350.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -1350.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath3To1(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.x > -250.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath2To3(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 60.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1350.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1350.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPath3To2(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 150.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s8 m206_HiderPathNone(omObjData *object) {
    return 0;
}

void m206_HiderMoveUpdate(omObjData *object) {
    s8 index = object->work[1];
    HideAndSneakWork *work = &m206_objWorkTbl[2 + index];
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[index];

    m206_HiderStepSeUpdate(object);
    switch (entry->unk_00) {
        case 0:
            if (m206_roundNo != 0) {
                entry->unk_00 = 5;
                break;
            }
            switch (m206_HiderComSpotGet(object)) {
                case 0:
                    entry->unk_00 = 1;
                    entry->unk_04 = 0;
                    break;
                case 1:
                    entry->unk_00 = 2;
                    entry->unk_04 = 1;
                    break;
                case 2:
                    entry->unk_00 = 3;
                    entry->unk_04 = 2;
                    break;
                case 3:
                    entry->unk_00 = 4;
                    entry->unk_04 = 3;
                    break;
            }
            break;
        case 1:
            if (object->trans.z > -575.0f) {
                if (object->trans.x > -220.0f) {
                    object->trans.x -= 24.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -220.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z > -850.0f) {
                if (object->trans.x < -30.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -575.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = -30.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z <= -850.0f) {
                if (object->trans.x > -400.0f) {
                    object->trans.x -= 24.0f;
                    object->trans.z = -850.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -400.0f;
                    entry->unk_00 = m206_RandGet(2) ? 5 : 7;
                }
            }
            break;
        case 2:
            if (object->trans.z > -575.0f) {
                if (object->trans.x > -220.0f) {
                    object->trans.x -= 24.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -220.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z > -1150.0f) {
                if (object->trans.x < -30.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -575.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = -30.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z > -1600.0f) {
                if (object->trans.x < 90.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -1150.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = 90.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z <= -1600.0f) {
                if (object->trans.x > -250.0f) {
                    object->trans.x -= 24.0f;
                    object->trans.z = -1600.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -250.0f;
                    entry->unk_00 = m206_RandGet(2) ? 5 : 7;
                }
            }
            break;
        case 3:
            if (object->trans.z > -575.0f) {
                if (object->trans.x > -220.0f) {
                    object->trans.x -= 24.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -220.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z <= -575.0f) {
                if (object->trans.x < 150.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -575.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = 150.0f;
                    entry->unk_00 = m206_RandGet(2) ? 5 : 7;
                }
            }
            break;
        case 4:
            if (object->trans.z > -575.0f) {
                if (object->trans.x > -220.0f) {
                    object->trans.x -= 24.0f;
                    object->rot.y = 270.0f;
                } else {
                    object->trans.x = -220.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z > -1150.0f) {
                if (object->trans.x < -30.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -575.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = -30.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z > -1350.0f) {
                if (object->trans.x < 90.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -1150.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = 90.0f;
                    object->trans.z -= 24.0f;
                    object->rot.y = 180.0f;
                }
            } else if (object->trans.z <= -1350.0f) {
                if (object->trans.x < 475.0f) {
                    object->trans.x += 24.0f;
                    object->trans.z = -1350.0f;
                    object->rot.y = 90.0f;
                } else {
                    object->trans.x = 475.0f;
                    entry->unk_00 = m206_RandGet(2) ? 5 : 7;
                }
            }
            break;
        case 5:
            entry->unk_05 = m206_HiderComSpotGet(object);
            entry->unk_02 = m206_RandGet(2);
            entry->unk_03 = 0;
            entry->unk_00 = 6;
            entry->unk_01 = 0;
            work->unk_12 = 0;
            break;
        case 6:
            switch (entry->unk_04) {
                case 0:
                    if (m206_hiderPath0Tbl[entry->unk_05](object)) {
                        entry->unk_04 = entry->unk_05;
                        entry->unk_00 = 7;
                    }
                    break;
                case 1:
                    if (m206_hiderPath1Tbl[entry->unk_05](object)) {
                        entry->unk_04 = entry->unk_05;
                        entry->unk_00 = 7;
                    }
                    break;
                case 2:
                    if (m206_hiderPath2Tbl[entry->unk_05](object)) {
                        entry->unk_04 = entry->unk_05;
                        entry->unk_00 = 7;
                    }
                    break;
                case 3:
                    if (m206_hiderPath3Tbl[entry->unk_05](object)) {
                        entry->unk_04 = entry->unk_05;
                        entry->unk_00 = 7;
                    }
                    break;
            }
            break;
        case 7:
            if (entry->unk_02 != 0) {
                switch (entry->unk_03) {
                    case 0:
                        object->trans.x += 24.0f;
                        object->rot.y = 90.0f;
                        work->unk_12++;
                        if (work->unk_12 > 16) {
                            entry->unk_03 = 1;
                        }
                        break;
                    case 1:
                        object->trans.x -= 24.0f;
                        object->rot.y = 270.0f;
                        work->unk_12--;
                        if (work->unk_12 <= 0) {
                            if (m206_RandGet(4) <= 0) {
                                entry->unk_03 = 0;
                                entry->unk_02 = 0;
                            } else {
                                entry->unk_00 = 5;
                            }
                        }
                        break;
                }
            } else {
                switch (entry->unk_03) {
                    case 0:
                        object->trans.x -= 24.0f;
                        object->rot.y = 270.0f;
                        work->unk_12++;
                        if (work->unk_12 > 16) {
                            entry->unk_03 = 1;
                        }
                        break;
                    case 1:
                        object->trans.x += 24.0f;
                        object->rot.y = 90.0f;
                        work->unk_12--;
                        if (work->unk_12 <= 0) {
                            if (m206_RandGet(4) <= 0) {
                                entry->unk_03 = 0;
                                entry->unk_02 = 1;
                            } else {
                                entry->unk_00 = 5;
                            }
                        }
                        break;
                }
            }
            break;
    }
    m206_HiderHideCheck(object);
}

void m206_SpotClear(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        m206_spotHiderTbl[i].slots[0] = -1;
        m206_spotHiderTbl[i].slots[1] = -1;
        m206_spotHiderTbl[i].slots[2] = -1;
        m206_spotHiderTbl[i].count = 0;
    }
}

void m206_SpotCount(void) {
    s8 i;

    for (i = 0; i < 3; i++) {
        HideAndSneakWork *work = &m206_objWorkTbl[2 + i];

        if (work->unk_04 == 0 && work->unk_08 != -1) {
            s8 spot = work->unk_08;

            m206_spotHiderTbl[spot].slots[i] = m206_spotHiderTbl[spot].count;
            m206_spotHiderTbl[spot].count++;
        }
    }
}

void m206_HiderSpotSelect(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[2 + object->work[1]];
    s8 pad = object->work[3];
    s8 candidates[4];
    s8 i;
    s8 count;
    s16 stickX;
    s16 stickY;

    if (GwPlayer[object->work[0]].stat & 1) {
        if (work->unk_08 == -1) {
            for (i = 0, count = 0; i < 4; i++) {
                if (m206_spotOpenTbl[i] != 0) {
                    candidates[count] = i;
                    count++;
                }
            }
            work->unk_08 = candidates[m206_RandGet(count)];
        }
    } else {
        stickX = HuPadStkX[pad];
        stickY = HuPadStkY[pad];
        if (abs(stickX) > 10 || abs(stickY) > 10) {
            if (abs(stickX) > abs(stickY)) {
                if (stickX < 0 && m206_spotOpenTbl[0] != 0) {
                    work->unk_08 = 0;
                }
                if (stickX > 0 && m206_spotOpenTbl[3] != 0) {
                    work->unk_08 = 3;
                }
            } else {
                if (stickY > 0 && m206_spotOpenTbl[1] != 0) {
                    work->unk_08 = 1;
                }
                if (stickY < 0 && m206_spotOpenTbl[2] != 0) {
                    work->unk_08 = 2;
                }
            }
        }
    }
}

void m206_HiderReturnMove(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[2 + object->work[1]];

    if (work->unk_08 == -1) {
        return;
    }
    m206_HiderStepSeUpdate(object);
    if (object->trans.z < -1350.0f) {
        if (object->trans.x < 90.0f) {
            object->trans.x += 24.0f;
            object->rot.y = 90.0f;
        } else {
            object->trans.x = 90.0f;
            object->trans.z += 24.0f;
            object->rot.y = 0.0f;
        }
    } else if (object->trans.z < -1150.0f) {
        if (object->trans.x > 90.0f) {
            object->trans.x -= 24.0f;
            object->rot.y = 270.0f;
        } else {
            object->trans.x = 90.0f;
            object->trans.z += 24.0f;
            object->rot.y = 0.0f;
        }
    } else if (object->trans.z < -850.0f) {
        if (object->trans.x > -30.0f) {
            object->trans.x -= 24.0f;
            object->rot.y = 270.0f;
        } else {
            object->trans.x = -30.0f;
            object->trans.z += 24.0f;
            object->rot.y = 0.0f;
        }
    } else if (object->trans.z < -575.0f) {
        if (object->trans.x < -30.0f) {
            object->trans.x += 24.0f;
            object->rot.y = 90.0f;
        } else {
            object->trans.x = -30.0f;
            object->trans.z += 24.0f;
            object->rot.y = 0.0f;
        }
    } else if (object->trans.z < -300.0f) {
        if (object->trans.x > -220.0f) {
            object->trans.x -= 24.0f;
            object->rot.y = 270.0f;
        } else {
            object->trans.x = -220.0f;
            object->trans.z += 24.0f;
            object->rot.y = 0.0f;
        }
    } else {
        if (work->unk_0E < 0 && object->trans.z >= -300.0f) {
            work->unk_0E = m206_hiderLineupNo;
            m206_hiderLineupNo++;
            object->trans.z = -300.0f;
        }
        if (object->trans.z == -300.0f) {
            if (object->trans.x < m206_lineupXTbl[2 - m206_hiderFoundNum][work->unk_0E]) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = m206_lineupXTbl[2 - m206_hiderFoundNum][work->unk_0E];
                object->rot.y = 0.0f;
                m206_HiderMotSet(object, 0);
                work->unk_08 = -1;
                m206_hiderLineupNum++;
            }
        }
    }
}

s8 m206_HiderOutUpdate(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[2 + object->work[1]];

    if (work->unk_04 == 0) {
        return 0;
    }
    if (work->unk_04 == 2) {
        return 1;
    }
    m206_HiderStepSeUpdate(object);
    if (work->unk_0C != 0) {
        work->unk_0C--;
    } else {
        if (work->unk_16 == 0) {
            work->unk_16++;
            PlayerFXPlay(0x286, object->work[0]);
        }
        if (abs(object->trans.x) > 1000) {
            work->unk_04 = 2;
            Hu3DModelAttrSet(object->model[0], 4, 4);
            Hu3DModelAttrSet(object->model[1], 4, 4);
            m206_hiderFoundTbl[object->work[1]] = 0;
            return 1;
        }
        if (object->trans.x < 0.0f) {
            object->rot.y = 270.0f;
            object->trans.x -= 24.0f;
        } else {
            object->rot.y = 90.0f;
            object->trans.x += 24.0f;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    }
    return 1;
}

void m206_HiderObjMain(omObjData *object) {
    s8 index = object->work[1];
    HideAndSneakWork *work = &m206_objWorkTbl[2 + index];
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[index];
    s8 spot;

    if (m206_HiderOutUpdate(object)) {
        return;
    }
    if (m206_phase != 2) {
        if (m206_phase >= 5 && m206_hiderFoundNum != 3) {
            m206_HiderMotSet(object, 4);
        }
        return;
    }
    switch (m206_roundState) {
        case 0:
            work->unk_08 = -1;
            work->unk_0A = 0;
            work->unk_0C = 0;
            work->unk_0E = -1;
            work->unk_10 = 0;
            work->unk_12 = 0;
            m206_slotOrderNo = m206_RandGet(6);
            m206_hiderLineupNo = 0;
            m206_hiderLineupNum = 0;
            entry->unk_00 = 0;
            entry->unk_02 = m206_RandGet(2);
            entry->unk_03 = 0;
            m206_hiderFoundTbl[index] = 0;
            break;
        case 1:
            m206_HiderMotSet(object, 1);
            m206_HiderMoveUpdate(object);
            m206_HiderSpotSelect(object);
            break;
        case 2:
            m206_HiderMoveUpdate(object);
            break;
        case 3:
            if (work->unk_08 == -1) {
                Hu3DModelAttrSet(object->model[0], 4, 0);
                m206_HiderMotSet(object, 2);
                object->trans.x = m206_hiderOutXTbl[m206_slotOrderTbl[m206_slotOrderNo][index]];
                object->trans.z = m206_hiderOutZTbl[m206_slotOrderTbl[m206_slotOrderNo][index]];
                object->rot.y = 0.0f;
                work->unk_0C = 45;
                work->unk_04 = 1;
                m206_hiderFoundTbl[index] = 1;
                m206_hiderFoundNum++;
            } else {
                spot = work->unk_08;
                entry->unk_04 = spot;
                object->trans.x = m206_spotOfsXTbl[m206_spotHiderTbl[spot].count - 1][m206_spotHiderTbl[spot].slots[index]] + m206_spotXTbl[spot];
                object->trans.z = m206_spotZTbl[spot];
                m206_HiderMotSet(object, 3);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DModelAttrSet(object->model[0], 4, 4);
                object->rot.y = 0.0f;
            }
            break;
        case 4:
            Hu3DModelAttrSet(object->model[0], 4, 0);
            if (work->unk_08 == m206_seekerSpotNo) {
                if (work->unk_0C == 40) {
                    Hu3DMotionSpeedSet(object->model[0], 1.0f);
                }
                if (work->unk_0C == 60) {
                    PlayerFXPlay(0x286, object->work[0]);
                    work->unk_16++;
                    if (!(GwPlayer[object->work[0]].stat & 1)) {
                        omVibrate(object->work[0], 10, 0, 10);
                    }
                }
                if (work->unk_0C == 80) {
                    m206_HiderMotSet(object, 2);
                    work->unk_0C = 0;
                    work->unk_04 = 1;
                    m206_hiderFoundTbl[index] = 1;
                    m206_hiderFoundNum++;
                } else {
                    work->unk_0C++;
                }
            } else {
                m206_HiderMotSet(object, 0);
            }
            break;
        case 5:
            m206_roundDoneBits |= 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    if (work->unk_10 != 0) {
        m206_HiderReturnMove(object);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
}

void m206_HiderObjInit(omObjData *object) {
    HideAndSneakHiderMove *entry = &m206_hiderMoveTbl[object->work[1]];
    u16 character = GwPlayer[object->work[0]].chr;

    object->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharModelNoTbl[character][3], 0x2B9);
    omObjMotionRead(object, 0, CharMotionDataNumGet(character, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(character, 2));
    omObjMotionRead(object, 3, CharMotionDataNumGet(character, 0x79));
    omObjMotionRead(object, 4, CharMotionDataNumGet(character, 0x30));
    omObjMotionRead(object, 2, CharMotionDataNumGet(character, 0x70));
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    switch (object->work[1]) {
        case 0:
            object->trans.x = -220.0f;
            break;
        case 1:
            object->trans.x = 0.0f;
            break;
        case 2:
            object->trans.x = 220.0f;
            break;
    }
    object->trans.y = 125.0f;
    object->trans.z = -300.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    m206_MotSet(object, 0, 2);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    entry->unk_00 = 0;
    entry->unk_01 = 0;
    entry->unk_02 = m206_RandGet(2);
    entry->unk_03 = 0;
    entry->unk_04 = 0;
    entry->unk_05 = 0;
    object->work[3] = GwPlayer[object->work[0]].pad;
    object->func = m206_HiderObjMain;
}

void m206_HiderObjCreate(void) {
    s8 slots[3];
    u16 playerIndex = 0;
    s32 count = 0;
    s8 i;
    s8 j;
    s8 choice;

    for (i = 0; i < 3; i++) {
        slots[i] = i;
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            HideAndSneakWork *work;
            omObjData *object;

            switch (i) {
                case 0:
                    playerIndex = 0;
                    break;
                case 1:
                    playerIndex = 1;
                    break;
                case 2:
                    playerIndex = 2;
                    break;
                case 3:
                    playerIndex = 3;
                    break;
            }
            work = &m206_objWorkTbl[2 + count];
            object = omAddObj(0x258, 3, 6, -1, m206_HiderObjInit);
            object->work[0] = playerIndex;
            work->obj = object;
            m206_teamPlayerNoTbl[count] = object->work[0];
            m206_teamChrTbl[count] = GwPlayer[object->work[0]].chr;
            choice = m206_RandGet(3 - count);
            object->work[1] = slots[choice];
            slots[choice] = -1;
            for (j = 1; j < 3 - count; j++) {
                if (slots[j - 1] == -1) {
                    slots[j - 1] = slots[j];
                    slots[j] = -1;
                }
            }
            count++;
        }
    }
}

void m206_SpotFadeSet(omObjData *object) {
    HideAndSneakWork *work = &m206_objWorkTbl[5 + object->work[0]];

    Hu3DModelObjTexScroll(object->model[0], 0.0f, work->unk_04, 0x60, 0x40, m206_spotTexNameTbl[object->work[0]], 0);
    Hu3DModelObjTexScroll(object->model[0], 0.0f, work->unk_04, 0x60, 0x40, m206_spotTexNameBTbl[object->work[0]], 0);
}

s8 m206_SpotShowCheck(void) {
    s8 i = 0;
    s8 count1 = 0;
    s8 count2 = 0;
    HideAndSneakWork *players = &m206_objWorkTbl[5];

    while (i < 4) {
        if (players[i].unk_04 == 0) {
            count1++;
        }
        if (m206_spotOpenTbl[i] != 0) {
            count2++;
        }
        i++;
    }

    return count1 == count2;
}

s8 m206_SpotHiddenCheck(void) {
    s8 i = 0;
    s8 count = 0;
    HideAndSneakWork *players = &m206_objWorkTbl[5];

    while (i < 4) {
        if (players[i].unk_04 == -0x40) {
            count++;
        }
        i++;
    }
    return count == 4;
}

void m206_SpotObjMain(omObjData *object) {
    s8 index = object->work[0];
    HideAndSneakWork *work = &m206_objWorkTbl[5 + index];

    switch (m206_spotFadeMode) {
        case 1:
            if (index == m206_seekerSpotNo) {
                if (work->unk_16 == 0) {
                    HuAudFXPlay(0x32C);
                    work->unk_16++;
                }
                if (work->unk_04 < -0x3F) {
                    work->unk_04 = -0x40;
                    m206_spotOpenTbl[index] = 0;
                    m206_iconTbl[index].unk_06 = 1;
                    work->unk_08++;
                    if (work->unk_08 > 20) {
                        m206_spotFadeMode = 2;
                    }
                } else if (omPauseChk() + omAllPauseF == 0) {
                    work->unk_04 -= 4;
                }
            }
            break;
        case 2:
            if (m206_spotSeF == 0) {
                HuAudFXPlay(0x327);
                m206_spotSeF = 1;
            }
            if (work->unk_04 >= -0x3F) {
                if (omPauseChk() + omAllPauseF == 0) {
                    work->unk_04 -= 4;
                }
            } else {
                work->unk_04 = -0x40;
            }
            break;
        case 3:
            if (m206_spotSeF != 0) {
                HuAudFXPlay(0x327);
                m206_spotSeF = 0;
            }
            if (m206_spotOpenTbl[index] != 0) {
                if (work->unk_04 < 0) {
                    if (omPauseChk() + omAllPauseF == 0) {
                        work->unk_04 += 4;
                    }
                } else {
                    work->unk_04 = 0;
                }
            }
            break;
    }
    switch (m206_roundState) {
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
        case 7:
            m206_SpotFadeSet(object);
            break;
    }
}

void m206_SpotObjInit(omObjData *object) {
    s8 index = object->work[0];
    HideAndSneakWork *work = &m206_objWorkTbl[5 + index];

    object->model[0] = Hu3DModelRead(m206_spotMdlTbl[index] | 0x270000, 0x1689);
    object->trans.z = -10.0f;
    if (index == 1) {
        object->trans.x = -10.0f;
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelVtxBufMake(object->model[0]);
    work->unk_04 = -0x40;
    m206_SpotFadeSet(object);
    m206_spotOpenTbl[index] = 1;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->func = m206_SpotObjMain;
}

void m206_SpotObjCreateAll(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        HideAndSneakWork *work = &m206_objWorkTbl[5 + i];
        omObjData *object = omAddObj(0x320, 2, 1, -1, m206_SpotObjInit);

        object->work[0] = i;
        work->obj = object;
        omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void m206_IconFadeIn(void) {
    HideAndSneakWork *work = &m206_objWorkTbl[13];

    if (work->unk_04 < 0xFF) {
        work->unk_04 += 0x1A;
    } else {
        work->unk_04 = 0xFF;
    }
}

void m206_IconFadeReset(void) {
    m206_objWorkTbl[13].unk_04 = 0;
}

void m206_IconDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HideAndSneakWork *work = &m206_objWorkTbl[13];
    s8 i;
    Gfx *gfx;

    if (work->unk_04 < 0xFF) {
        gfxPos = m206_GfxRectXluInit(gfxPos);
        gfxPos = m206_GfxPrimAlphaSet(gfxPos, (u8)work->unk_04);
        if (work->unk_04 == 0) {
            return;
        }
    } else {
        gfxPos = m206_GfxRectTexInit(gfxPos);
    }
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    for (i = 0; i < 4; i++) {
        if (m206_iconTbl[i].unk_06 == 0) {
            gDPLoadTLUT_pal16(gfx++, 0, m206_iconSprDataTbl[i]->pal);
            gDPLoadTextureTile_4b(gfx++, m206_iconSprDataTbl[i]->data, G_IM_FMT_CI, 32, 32, 0, 0, 32, 32, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 32 << 2, 32 << 2);
            gSPTextureRectangle(gfx++, m206_iconTbl[i].x << 2, m206_iconTbl[i].y << 2, (m206_iconTbl[i].x + 32) << 2, (m206_iconTbl[i].y + 32) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
        }
    }
    *gfxPos = gfx;
}

void m206_IconObjMain(omObjData *object) {
}

void m206_IconObjInit(omObjData *object) {
    s8 i;

    for (i = 0; i < 4; i++) {
        m206_iconTbl[i].sprite = HuSprAnimDataRead(m206_iconSprTbl[i] | 0x270000);
        m206_iconTbl[i].x = m206_iconPosTbl[i].x;
        m206_iconTbl[i].y = m206_iconPosTbl[i].y;
        m206_iconTbl[i].unk_06 = 0;
        m206_iconSprDataTbl[i] = HuSprAnimDataGet(m206_iconTbl[i].sprite);
    }
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m206_IconDraw, 2), HU3D_CAM0);
    object->func = m206_IconObjMain;
}

void m206_IconObjCreate(void) {
    m206_objWorkTbl[13].obj = omAddObj(0x3E8, 2, 1, -1, m206_IconObjInit);
    omSetStatBit(m206_objWorkTbl[13].obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m206_SignShuffle(void) {
    HideAndSneakWork *works;
    s8 candidates[4];
    s8 i;
    s8 j;
    s8 count;
    s8 emptyCount;
    s8 choice;

    for (i = 0, count = 0, emptyCount = 0; i < 4; i++) {
        if (m206_spotOpenTbl[i] != 0) {
            candidates[count] = i;
            count++;
        } else {
            m206_signSpotTbl[3 - emptyCount] = i;
            emptyCount++;
        }
    }
    for (i = 0; i < count; i++) {
        choice = m206_RandGet(count - i);
        m206_signSpotTbl[i] = candidates[choice];
        candidates[choice] = -1;
        for (j = 1; j < count - i; j++) {
            if (candidates[j - 1] == -1) {
                candidates[j - 1] = candidates[j];
                candidates[j] = -1;
            }
        }
    }
    for (i = 0, works = &m206_objWorkTbl[9]; i < 4; i++) {
        works[m206_signSpotTbl[i]].obj->trans.x = m206_signXTbl[m206_signNum][i];
    }
}

void m206_SignObjMain(omObjData *object) {
    if (m206_phase >= 3) {
        if (object->trans.y > -160.0f) {
            object->trans.y -= 4.0f;
        }
    } else {
        switch (m206_roundState) {
            case 1:
                if (object->trans.y > -160.0f) {
                    object->trans.y -= 4.0f;
                }
                break;
            case 2:
                if (object->trans.y < 0.0f) {
                    object->trans.y += 4.0f;
                }
                break;
        }
    }
}

const char *m206_spotTexNameTbl[4] = { "m206_09-kirikabu", "m206_09-ishi", "m206_09-kinokoie", "m206_09-kusa" };
const char *m206_spotTexNameBTbl[4] = { "m206_09-kirikabu1", "m206_09-ishi1", "m206_09-kinokoie1", "m206_09-kusa1" };
s16 m206_iconSprTbl[4] = { 8, 9, 10, 11 };
HideAndSneakSpritePos m206_iconPosTbl[4] = {
    { 70, 76 },
    { 105, 41 },
    { 173, 87 },
    { 226, 60 },
};
s16 m206_signAnimTbl[4] = { 14, 15, 16, 17 };
s32 m206_cameraInitF = 0;
HideAndSneakCamera m206_cameraViewTbl[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 23.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 23.0f },
};

void m206_SignObjInit(omObjData *object) {
    s32 index = (s8)object->work[0];
    void *data;

    object->model[0] = Hu3DModelRead(0x27000D, 0x2A9);
    data = DataRead(m206_signAnimTbl[index] | 0x270000);
    Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "s206_004_DEF");
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    DataClose(data);
    object->trans.x = index * 130 - 195;
    object->trans.y = -160.0f;
    object->trans.z = 100.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DMotionSpeedSet(object->model[0], 0.0f);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = m206_SignObjMain;
}

void m206_SignObjCreateAll(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        HideAndSneakWork *work = &m206_objWorkTbl[9 + i];
        omObjData *object = omAddObj(0x384, 1, 1, -1, m206_SignObjInit);

        object->work[0] = i;
        work->obj = object;
    }
}

void m206_RoundUpdate(void) {
    omObjData *object = m206_objWorkTbl[0].obj;

    switch (m206_roundState) {
        case 0:
            if (m206_SpotShowCheck()) {
                GMesCreate(GMES_MES_TIMER, 10, 160, 28);
                m206_timer = 151;
                if (m206_roundNo != 0) {
                    HuAudFXPlay(0x328);
                }
                m206_spotSeF = 0;
                m206_roundState = 1;
            }
            break;
        case 1:
            if (m206_timer > 0) {
                m206_timer--;
                GMesTimerValueSet((m206_timer + 29) / 30);
                m206_IconFadeIn();
            } else {
                GMesTimerEnd();
                m206_timer = 30;
                Hu3DModelAttrSet(object->model[0], 4, 0);
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
                m206_SpotClear();
                m206_SpotCount();
                m206_SignShuffle();
                m206_spotFadeMode = 0;
                m206_roundState = 2;
                HuAudFXPlay(0x328);
            }
            break;
        case 2:
            if ((s32)Hu3DData[object->model[0]].motTime >= 60) {
                Hu3DMotionTimeSet(object->model[0], 60.0f);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                if (m206_timer > 0) {
                    m206_timer--;
                } else {
                    GMesCreate(GMES_MES_TIMER, 10, 160, 28);
                    m206_timer = 301;
                    m206_IconFadeReset();
                    Hu3DMotionSpeedSet(object->model[0], -1.0f);
                    m206_roundState = 3;
                }
            }
            break;
        case 3:
            if ((s32)Hu3DData[object->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DModelAttrSet(object->model[0], 4, 4);
            }
            if (m206_timer > 0) {
                m206_timer--;
                GMesTimerValueSet((m206_timer + 29) / 30);
            } else {
                GMesTimerEnd();
                if (m206_roundNo == 2) {
                    GMesCreate(GMES_MES_15);
                    HuAudSeqFadeOut(100);
                    m206_timeUpF = 1;
                }
                m206_roundState = 4;
            }
            if (m206_roundDoneBits != 0) {
                m206_roundDoneBits = 0;
                GMesTimerEnd();
                m206_roundState = 4;
            }
            break;
        case 4:
            if ((s32)Hu3DData[object->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DModelAttrSet(object->model[0], 4, 4);
            }
            if (m206_roundDoneBits != 0 && m206_SpotHiddenCheck() && m206_spotFadeMode == 2) {
                m206_spotFadeMode = 0;
                m206_roundDoneBits = 0;
                m206_roundState = 5;
            }
            break;
        case 5:
            if (m206_hiderFoundNum == 3) {
                m206_roundNo = 2;
                m206_roundDoneBits |= 2;
            }
            if (m206_roundDoneBits == 3) {
                m206_roundDoneBits = 0;
                if (m206_roundNo < 2) {
                    m206_timer = 20;
                } else {
                    m206_timer = 0;
                }
                if (m206_seekerSpotNo != -1) {
                    m206_signNum--;
                }
                m206_roundState = 6;
            }
            break;
        case 6:
            if ((s32)Hu3DData[object->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DModelAttrSet(object->model[0], 4, 4);
            }
            if (m206_timer > 0) {
                m206_timer--;
            } else {
                GMesTimerEnd();
                if (m206_hiderFoundTbl[0] == 0 && m206_hiderFoundTbl[1] == 0 && m206_hiderFoundTbl[2] == 0) {
                    m206_roundNo++;
                    if (m206_roundNo == 3) {
                        m206_roundState = 7;
                        m206_spotFadeMode = 2;
                    } else {
                        m206_roundState = 0;
                        m206_spotFadeMode = 3;
                    }
                }
            }
            break;
        case 7:
            break;
    }
}

void m206_CameraViewInit(void) {
    u32 i;

    if (m206_cameraInitF == 0) {
        m206_cameraInitF = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 2695.0789f;
            CRotM[i].x = 340.1531f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = -0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 385.0f;
            CenterM[i].z = -100.0f;
        }
    }
}

void m206_ExitObjMain(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m206_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m206_ExitObjMain;
    }
}

void m206_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m206_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m206_MainObjMain(omObjData *object) {
    switch (m206_phase) {
        case 0:
            GMesCreate(GMES_MES_4);
            m206_phase = 1;
            m206_mainTimer = 0;
            HuAudFXPlay(0x327);
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m206_phase = 2;
                m206_roundState = 0;
            }
            m206_mainTimer++;
            if (m206_mainTimer == 64) {
                HuAudSeqPlay(0x31);
            }
            break;
        case 2:
            m206_RoundUpdate();
            if (m206_roundState == 7) {
                if (m206_timeUpF == 0) {
                    GMesCreate(GMES_MES_15);
                    HuAudSeqFadeOut(120);
                }
                m206_phase = 3;
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                m206_phase = 4;
                m206_timer = 0;
            }
            break;
        case 4:
            m206_timer++;
            if (m206_timer >= 16) {
                m206_phase = 5;
            }
            break;
        case 5:
            if (m206_hiderFoundNum == 3) {
                GMesCreate(GMES_MES_MG_WINNER, m206_seekerChr);
                GwPlayer[m206_seekerPlayerNo].bonusCoin = 10;
                HuAudSeqPlay(0x65);
                m206_timer = 15;
                m206_phase = 6;
            } else {
                GMesCreate(GMES_MES_MG_WINNERS_3, m206_teamChrTbl[0], m206_teamChrTbl[1], m206_teamChrTbl[2]);
                GwPlayer[m206_teamPlayerNoTbl[0]].bonusCoin = 10;
                GwPlayer[m206_teamPlayerNoTbl[1]].bonusCoin = 10;
                GwPlayer[m206_teamPlayerNoTbl[2]].bonusCoin = 10;
                HuAudSeqPlay(0x66);
                m206_timer = 15;
                m206_phase = 6;
            }
            break;
        case 6:
            if (GMesStatGet() == 0) {
                m206_timer--;
                if (m206_timer <= 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    object->func = m206_ExitWaitObjMain;
                }
            }
            break;
    }
}

void m206_MainObjInit(omObjData *object) {
    m206_phase = 0;
    m206_roundDoneBits = 0;
    m206_timer = 0;
    m206_roundNo = 0;
    m206_spotFadeMode = 3;
    m206_hiderFoundNum = 0;
    m206_timeUpF = 0;
    m206_signNum = 4;
    m206_spotSeF = 0;
    m206_CameraViewInit();
    m206_StageObjCreate();
    m206_SeekerObjCreate();
    m206_HiderObjCreate();
    m206_SpotObjCreateAll();
    m206_SignObjCreateAll();
    m206_IconObjCreate();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = m206_MainObjMain;
}

void m206_Dummy(void) {
}

void m206_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, m206_cameraViewTbl[i].scissorX, m206_cameraViewTbl[i].scissorY, m206_cameraViewTbl[i].scissorWidth, m206_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m206_cameraViewTbl[i].viewportScale.x, m206_cameraViewTbl[i].viewportScale.y, m206_cameraViewTbl[i].viewportScale.z, m206_cameraViewTbl[i].viewportTranslate.x,
                    m206_cameraViewTbl[i].viewportTranslate.y, m206_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m206_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m206_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    m206_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(2, 255, 255, 255);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m206_fontMesTbl, 0);
    GMesFontMesCreate(m206_fontMesTbl, 1);
    omAddObj(1500, 0, 0, -1, m206_MainObjInit);
    omAddObj(1500, 0, 0, -1, m206_ExitCheckObjMain);
    m206_ObjWorkInit();
}

const s16 m206_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
