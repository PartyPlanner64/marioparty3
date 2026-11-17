#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

// Per-chomp state at m245_playerWorkTbl, indexed by omObjData::work[0]
typedef struct MerryGoChompPlayerWork {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ s8 unk_1D;
    /* 0x1E */ s8 unk_1E;
    /* 0x1F */ s8 unk_1F;
    /* 0x20 */ s8 unk_20;
    /* 0x21 */ char unk_21[3];
} MerryGoChompPlayerWork; // Size 0x24

// One entry of the 50 entry object table at m245_objWorkTbl. Layout
// derived from the table clear in m245_ObjWorkInit, which walks 50
// entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} MerryGoChompObjWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} MerryGoChompCamera; // sizeof 0x2C

// Group of misaligned byte variables (see undefined_syms.txt for aliases).
typedef struct MerryGoChompSeqWork {
    /* 0x00 */ s8 unk00; // m245_seqNo
    /* 0x01 */ s8 unk01; // m245_queueNo
    /* 0x02 */ s8 unk02[5]; // m245_seatFreeTbl
} MerryGoChompSeqWork; // sizeof 0x08

extern s32 omCharModelNoTbl[][6];

s32 m245_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s8 m245_jumpYTbl[17] = { 60, 30, 20, 15, 10, 5, 0, 0, 0, 0, -15, -15, -20, -40, -50, -60, -65 };
f32 m245_jumpShadowScaleTbl[17] = { 1.0f, 0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.7f, 0.65f, 0.7f, 0.75f, 0.8f, 0.85f, 0.9f, 0.95f, 1.0f, 1.0f, 1.0f };
f32 m245_queuePosXTbl[4] = { 345.0f, 450.0f, 555.0f, 660.0f };
f32 m245_queuePosZTbl[4] = { -200.0f, -260.0f, -320.0f, -380.0f };
f32 m245_seatAngleTbl[3][5] = {
    { 0.0f, 72.0f, 144.0f, 216.0f, 288.0f },
    { 0.0f, 90.0f, 180.0f, 270.0f, 0.0f },
    { 0.0f, 120.0f, 240.0f, 0.0f, 0.0f },
};
Vec2f m245_chainAnchor = { -800.0f, 0.0f };
f32 m245_outPosXTbl[3] = { -500.0f, -600.0f, -400.0f };
f32 m245_outPosZTbl[3] = { -475.0f, -300.0f, -300.0f };
s16 m245_wanwanTargetXTbl[8] = { -700, -500, -700, -500, -600, -500, -600, -600 };
s16 m245_wanwanTargetZTbl[8] = { -50, -50, 150, 150, 350, 350, 25, 225 };
s32 m245_cameraSetF = 0;
MerryGoChompCamera m245_cameraViewTbl[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.5f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 34.5f },
};

s16 m245_spinSeNo BSS;
HuSprAnimData *m245_lowerBackSpr BSS;
s8 m245_carouselSeRound BSS;
u8 m245_carouselSeRoundPad[4] BSS; /* Unreferenced. */
MerryGoChompPlayerWork m245_playerWorkTbl[4] BSS;
s8 m245_phase BSS;
s16 m245_timer BSS;
f32 m245_stopAngleTbl[2] BSS;
MerryGoChompSeqWork m245_seqWork BSS;
s16 m245_carouselSeNo BSS;
omObjData *m245_winnerObj BSS;
s16 m245_spinSeSpeed BSS;
s8 m245_roundNo BSS;
Vec2f m245_chainPosTbl[6] BSS;
MerryGoChompObjWork m245_objWorkTbl[50] BSS;
s8 m245_outPlayerNo BSS;
s16 m245_musicTimer BSS;
u8 m245_seatPlayerTbl[8] BSS;
f32 m245_carouselSpeed BSS;
s8 m245_stopSeatNo BSS;
s16 m245_spinSePitch BSS;
s8 m245_doneBits BSS;
s8 m245_jumpTurnNo BSS;

// Aliases into m245_seqWork (see undefined_syms.txt).
extern s8 m245_seqNo;
extern s8 m245_queueNo;
extern s8 m245_seatFreeTbl[5];
// Entries and entry fields of m245_objWorkTbl, accessed through
// separate symbols (see undefined_syms.txt).
extern s16 m245_backSprAnim; // [0].unk_40[0]
extern s16 m245_backSprNo; // [0].unk_40[1]
extern f32 m245_backSprX; // [0].unk_44.x
extern f32 m245_backSprY; // [0].unk_44.y
extern MerryGoChompObjWork m245_playerObjWorkTbl[]; // &[5]
extern omObjData *m245_wanwanObj; // [10].obj
extern omObjData *m245_stageObj; // [15].obj
extern f32 m245_gateY; // [15].unk_44.y
extern f32 m245_gateZ; // [15].unk_44.z
extern omObjData *m245_carouselObj; // [25].obj
extern omObjData *m245_biteEffObj; // [30].obj
extern const s16 m245_fontMesTbl[];

void m245_BackObjInit(omObjData *);
void m245_StageObjMain(omObjData *obj);
void m245_BackObjMain(omObjData *obj);
void m245_StageObjInit(omObjData *);
void m245_CarouselObjMain(omObjData *obj);
void m245_CarouselObjInit(omObjData *);
void m245_WanwanChainUpdate(omObjData *obj);
void m245_WanwanObjMain(omObjData *obj);
void m245_WanwanObjInit(omObjData *);
void m245_BiteEffObjMain(omObjData *obj);
void m245_BiteEffObjInit(omObjData *);
void m245_PlayerPushUpdate(void);
void m245_RoundUpdate(void);
void m245_ExitWaitObjMain(omObjData *obj);
void m245_MainObjMain(omObjData *obj);
void m245_ObjectSetup(void);

void m245_Executor(void) {
    m245_ObjectSetup();
}

f32 m245_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m245_RandMulGet(u32 arg0) {
    return (rand8() * arg0) >> 8;
}

void m245_ObjWorkInit(void) {
    MerryGoChompObjWork *entry;
    u32 i;

    for (i = 0, entry = m245_objWorkTbl; i < 50; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04 = 0;
        entry->unk_06 = 0;
        entry->unk_08 = 0;
        entry->unk_0A = 0;
        entry->unk_0C = 0;
        entry->unk_0E = 0;
        entry->unk_10 = 0;
        entry->unk_12 = 0;
        entry->unk_14 = 0;
        entry->unk_16 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_28 = 0;
        entry->unk_2C = 0;
        entry->unk_30 = 0;
        entry->unk_34 = 0;
        entry->unk_38 = 0;
        entry->unk_3C = 0;
        entry->unk_40[0] = -1;
        entry->unk_40[1] = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68[0] = 0.0f;
        entry->unk_68[1] = 0.0f;
        entry->unk_68[2] = 0.0f;
        entry->unk_68[3] = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void m245_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m245_CameraDebugPrint(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = (x0 - x1) * 5.0f;
    f32 dz = (z0 - z1) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = m245_AngleAdd(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 m245_RandGet(s32 arg0) {
    return rand8() % arg0;
}

void m245_MotSet(omObjData *obj, u16 motion, s16 shift) {
    Hu3DMotionModelSet(obj->model[0], obj->motion[motion]);
    Hu3DMotionAttrSet(obj->model[0], shift, shift);
}

void m245_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

void m245_ChaseVelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 *angle, f32 speed) {
    f32 dx = x0 - x1;
    f32 dz = z0 - z1;
    f32 dist = sqrtf(dx * dx + dz * dz);
    f32 steps;

    if (dist == 0.0f) {
        *velX = 0.0f;
        *velZ = 0.0f;
        return;
    }
    if (dist <= speed) {
        *velX = dx;
        *velZ = dz;
    } else {
        steps = dist / speed;
        if (dx != 0.0f) {
            *velX = dx / steps;
        } else {
            *velX = 0.0f;
        }
        if (dz != 0.0f) {
            *velZ = dz / steps;
        } else {
            *velZ = 0.0f;
        }
    }
    *angle = atan2df(dx, dz);
}

s8 m245_RotYTurn(omObjData *obj, f32 target) {
    f32 rotY = obj->rot.y;
    f32 diff = target - rotY;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 15.0f) {
        obj->rot.y = target;
    } else if (rotY < target) {
        if (diff > 180.0f) {
            obj->rot.y = m245_AngleAdd(obj->rot.y, -15.0f);
        } else {
            obj->rot.y = m245_AngleAdd(obj->rot.y, 15.0f);
        }
        return 1;
    } else if (target < rotY) {
        if (diff > 180.0f) {
            obj->rot.y = m245_AngleAdd(obj->rot.y, 15.0f);
        } else {
            obj->rot.y = m245_AngleAdd(obj->rot.y, -15.0f);
        }
        return 1;
    }
    return 0;
}

void m245_BackDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, m245_lowerBackSpr->pal);
    x = 0;
    for (i = 0, y = 180; i < 60; i += 4) {
        gDPLoadTextureTile(gfx++, m245_lowerBackSpr->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void m245_BackObjMain(omObjData *obj) {
}

void m245_BackObjInit(omObjData *obj) {
    m245_backSprX = 160.0f;
    m245_backSprY = 107.0f;
    m245_backSprAnim = HuSprAnimDataRead(0x4E0000);
    m245_backSprNo = espEntry(m245_backSprAnim, 0, 0);
    espAttrSet(m245_backSprNo, 0x5000);
    espPosSet(m245_backSprNo, m245_backSprX,
              m245_backSprY);
    m245_lowerBackSpr = HuSprAnimDataGet(HuSprAnimDataRead(0x4E0001));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m245_BackDraw, 2), HU3D_CAM0);
    obj->model[0] = -1;
    obj->func = m245_BackObjMain;
}

void m245_BackObjCreate(void) {
    omObjData *obj = omAddObj(0x1F4, 1, 1, -1, m245_BackObjInit);
    obj->work[0] = 0;
    m245_objWorkTbl[0].obj = obj;
}

void m245_StageObjMain(omObjData *obj) {
}

void m245_StageObjInit(omObjData *obj) {
    f32 zero;

    obj->model[0] = Hu3DModelRead(0x4E0004, 0x2B9);
    obj->model[1] = Hu3DModelRead(0x4E0005, 0x2B9);
    obj->model[2] = Hu3DModelRead(0x4E0002, 0x2B9);
    obj->trans.x = -500.0f;
    obj->trans.y = zero = 0.0f;
    m245_gateY = zero;
    obj->trans.z = -400.0f;
    m245_gateZ = -225.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, m245_gateY, m245_gateZ);
    Hu3DModelPosSet(obj->model[2], zero, zero, zero);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM1);
    obj->func = m245_StageObjMain;
}

void m245_StageObjCreate(void) {
    m245_stageObj = omAddObj(0x2BC, 4, 1, -1, m245_StageObjInit);
}

void m245_CarouselObjMain(omObjData *obj) {
    MerryGoChompObjWork *entry = &m245_objWorkTbl[25];

    obj->rot.y = m245_AngleAdd(obj->rot.y, -m245_carouselSpeed);
    switch (m245_phase) {
        case 0:
            m245_carouselSpeed = 3.0f;
            entry->unk_06 = 0;
            entry->unk_08 = 0;
            break;
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            if (m245_timer < 50) {
                if (obj->trans.y > 0.0f) {
                    obj->trans.y -= 10.0f;
                } else {
                    obj->trans.y = 0.0f;
                }
            }
            break;
        case 9:
            if (m245_timer == 50) {
                if (entry->unk_06 == 0) {
                    if (entry->unk_08 == 0) {
                        HuAudFXPlay(0x473);
                        entry->unk_08++;
                    }
                    if (obj->trans.y > -650.0f) {
                        obj->trans.y -= 15.0f;
                    } else {
                        Hu3DModelAttrSet(obj->model[entry->unk_04], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        entry->unk_04++;
                        Hu3DModelAttrSet(obj->model[entry->unk_04], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        entry->unk_06 = 1;
                        if (m245_roundNo == 0) {
                            obj->rot.y = 0.0f;
                        }
                        if (m245_roundNo == 1) {
                            obj->rot.y = 30.0f;
                        }
                    }
                } else {
                    if (entry->unk_08 == 1) {
                        HuAudFXPlay(0x473);
                        entry->unk_08++;
                    }
                    if (obj->trans.y < 500.0f) {
                        obj->trans.y += 15.0f;
                    } else {
                        obj->trans.y = 500.0f;
                        m245_doneBits |= 8;
                        if (entry->unk_08 == 2) {
                            HuAudFXPlay(0x478);
                            entry->unk_08++;
                        }
                    }
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[entry->unk_04], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[entry->unk_04], obj->rot.x, obj->rot.y, obj->rot.z);
}

void m245_CarouselObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x4E0006, 0x2B9);
    obj->model[1] = Hu3DModelRead(0x4E0007, 0x2B9);
    obj->model[2] = Hu3DModelRead(0x4E0008, 0x2B9);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->model[3] = Hu3DModelRead(0x4E0009, 0x2B9);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m245_objWorkTbl[25].unk_04 = 1;
    obj->trans.x = 0.0f;
    obj->trans.y = 500.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    m245_seatFreeTbl[0] = 1;
    m245_seatFreeTbl[1] = 1;
    m245_seatFreeTbl[2] = 1;
    m245_seatFreeTbl[3] = 1;
    m245_seatFreeTbl[4] = 1;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM0);
    obj->func = m245_CarouselObjMain;
}

void m245_CarouselObjCreate(void) {
    m245_carouselObj = omAddObj(0x258, 5, 1, -1, m245_CarouselObjInit);
}

void m245_PlayerStepSeUpdate(omObjData *obj) {
    MerryGoChompObjWork *entry = &m245_objWorkTbl[obj->work[0] + 5];

    if (obj->work[2] == 0) {
        if (entry->unk_14 != 0) {
            HuAudFXStop(entry->unk_14);
        }
        entry->unk_14 = PlayerFXPlay(0x28, obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

void m245_PlayerMotChange(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    MerryGoChompObjWork *entry = &m245_objWorkTbl[obj->work[0] + 5];
    s16 shift;

    if (entry->unk_06 != motion) {
        switch (motion) {
            case 6:
            case 7:
            case 8:
                shift = 0;
                break;
            case 9:
            case 10:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        m245_MotShiftSet(obj, motion, 0, 5, shift);
        entry->unk_06 = motion;
        if (motion == 9) {
            HuAudCharVoicePlay((m245_voiceChrTbl[chr] << 16) | 0x30);
        }
    }
}

s8 m245_PlayerSeatCheck(omObjData *obj) {
    MerryGoChompObjWork *entry = &m245_objWorkTbl[obj->work[0] + 5];
    omObjData *chomp = m245_objWorkTbl[25].obj;
    s8 zone = 99;
    f32 angle = m245_AngleAdd(chomp->rot.y, -120.0f);

    if (!(GwPlayer[obj->work[0]].stat & 1)) {
        switch (m245_roundNo) {
            case 0:
                if (angle >= 324.0f || angle < 36.0f) {
                    zone = 0;
                }
                if (angle >= 36.0f && angle < 108.0f) {
                    zone = 1;
                }
                if (angle >= 108.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 180.0f && angle < 252.0f) {
                    zone = 3;
                }
                if (angle >= 252.0f && angle < 324.0f) {
                    zone = 4;
                }
                break;
            case 1:
                if (angle >= 315.0f || angle < 45.0f) {
                    zone = 0;
                }
                if (angle >= 45.0f && angle < 135.0f) {
                    zone = 1;
                }
                if (angle >= 135.0f && angle < 225.0f) {
                    zone = 2;
                }
                if (angle >= 225.0f && angle < 315.0f) {
                    zone = 3;
                }
                break;
            case 2:
                if (angle >= 300.0f || angle < 60.0f) {
                    zone = 0;
                }
                if (angle >= 60.0f && angle < 180.0f) {
                    zone = 1;
                }
                if (angle >= 180.0f && angle < 300.0f) {
                    zone = 2;
                }
                break;
        }
    } else {
        switch (m245_roundNo) {
            case 0:
                if (angle >= 324.0f || angle < 36.0f) {
                    zone = 0;
                }
                if (angle >= 36.0f && angle < 108.0f) {
                    zone = 1;
                }
                if (angle >= 108.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 180.0f && angle < 252.0f) {
                    zone = 3;
                }
                if (angle >= 252.0f && angle < 324.0f) {
                    zone = 4;
                }
                break;
            case 1:
                if (angle >= 315.0f) {
                    zone = 0;
                }
                if (angle >= 45.0f && angle < 90.0f) {
                    zone = 1;
                }
                if (angle >= 135.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 225.0f && angle < 270.0f) {
                    zone = 3;
                }
                break;
            case 2:
                if (angle >= 300.0f) {
                    zone = 0;
                }
                if (angle >= 60.0f && angle < 120.0f) {
                    zone = 1;
                }
                if (angle >= 180.0f && angle < 240.0f) {
                    zone = 2;
                }
                break;
        }
        if (zone == 99) {
            return 0;
        }
    }
    if (!(GwPlayer[obj->work[0]].stat & 1) || m245_timer <= 0) {
        if (m245_seatFreeTbl[zone] != 0) {
            entry->unk_0A = zone;
            m245_seatPlayerTbl[entry->unk_0A] = obj->work[0];
            m245_seatFreeTbl[zone] = 0;
            return 1;
        }
    } else if (entry->unk_0C == zone) {
        entry->unk_0A = zone;
        m245_seatPlayerTbl[entry->unk_0A] = obj->work[0];
        m245_seatFreeTbl[zone] = 0;
        return 1;
    }
    return 0;
}

void m245_PlayerSeatJumpStart(omObjData *obj) {
    MerryGoChompObjWork *entry = &m245_objWorkTbl[obj->work[0] + 5];
    omObjData *chomp = m245_objWorkTbl[25].obj;
    MerryGoChompPlayerWork *move = &m245_playerWorkTbl[obj->work[0]];
    f32 angle;

    angle = m245_AngleAdd(chomp->rot.y,
                                         -m245_seatAngleTbl[m245_roundNo][entry->unk_0A]);
    angle = m245_AngleAdd(angle, -(m245_carouselSpeed * 15.0f));
    move->unk_00.x = sindf(angle) * 180.0f;
    move->unk_00.y = cosdf(angle) * 180.0f;
    move->unk_00.x = (move->unk_00.x - obj->trans.x) / 15.0f;
    move->unk_00.y = (move->unk_00.y - obj->trans.z) / 15.0f;
    move->unk_00.z = atan2df(move->unk_00.x, move->unk_00.y);
    m245_MotSet(obj, 6, 0);
    Hu3DMotionSpeedSet(obj->model[0], 1.5f);
    entry->unk_06 = 6;
}

void m245_PlayerVelApply(omObjData *obj) {
    MerryGoChompPlayerWork *entry = &m245_playerWorkTbl[obj->work[0]];

    obj->trans.x += entry->unk_00.x;
    obj->trans.z += entry->unk_00.y;
    obj->rot.y = entry->unk_00.z;
}

void m245_RotVelCalc(omObjData *obj, f32 *outX, f32 *outZ, f32 scale) {
    f32 angle = obj->rot.y;
    s16 quadrant = 0;

    if (angle >= 90.0f) {
        quadrant++;
    }
    if (angle >= 180.0f) {
        quadrant++;
    }
    if (angle >= 270.0f) {
        quadrant++;
    }
    switch (quadrant) {
        case 0:
            *outX = angle * scale;
            *outZ = (90.0f - angle) * scale;
            break;
        case 1:
            angle -= 90.0f;
            *outX = (90.0f - angle) * scale;
            *outZ = -(angle * scale);
            break;
        case 2:
            angle -= 180.0f;
            *outX = -(angle * scale);
            *outZ = -(90.0f - angle) * scale;
            break;
        case 3:
            angle -= 270.0f;
            *outX = -(90.0f - angle) * scale;
            *outZ = angle * scale;
            break;
    }
}

s8 m245_OutPlayerGet(void) {
    MerryGoChompObjWork *entry;
    MerryGoChompPlayerWork *move;
    omObjData *obj;
    s8 found = -1;
    s8 zone;
    s8 i;
    f32 angle;

    for (i = 0; i < 4; i++) {
        entry = &m245_objWorkTbl[i + 5];
        obj = entry->obj;
        if (entry->unk_04 == 0) {
            move = &m245_playerWorkTbl[i];
            zone = -1;
            angle = m245_AngleAdd(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            switch (m245_roundNo) {
                case 0:
                    if (angle >= 306.0f || angle < 18.0f) {
                        zone = 0;
                    }
                    if (angle >= 18.0f && angle < 90.0f) {
                        zone = 1;
                    }
                    if (angle >= 90.0f && angle < 162.0f) {
                        zone = 2;
                    }
                    if (angle >= 162.0f && angle < 234.0f) {
                        zone = 3;
                    }
                    if (angle >= 234.0f && angle < 306.0f) {
                        found = i;
                    }
                    break;
                case 1:
                    if (angle >= 315.0f || angle < 45.0f) {
                        zone = 0;
                    }
                    if (angle >= 45.0f && angle < 135.0f) {
                        zone = 1;
                    }
                    if (angle >= 135.0f && angle < 225.0f) {
                        zone = 2;
                    }
                    if (angle >= 225.0f && angle < 315.0f) {
                        found = i;
                    }
                    break;
                case 2:
                    if (angle >= 330.0f || angle < 90.0f) {
                        zone = 0;
                    }
                    if (angle >= 90.0f && angle < 210.0f) {
                        zone = 1;
                    }
                    if (angle >= 210.0f && angle < 330.0f) {
                        found = i;
                    }
                    break;
            }
            move->unk_20 = zone;
        }
    }
    return found;
}

void m245_PlayerReturnUpdate(omObjData *obj) {
    s8 index = obj->work[0];
    MerryGoChompObjWork *entry = &m245_objWorkTbl[index + 5];
    MerryGoChompPlayerWork *move = &m245_playerWorkTbl[index];

    if (entry->unk_04 != 0) {
        return;
    }
    switch (move->unk_1C) {
        case 0:
            move->unk_1D = 0;
            move->unk_1E = 0;
            move->unk_14 = obj->trans.x;
            move->unk_18 = obj->trans.z;
            move->unk_10 = 18.0f;
            move->unk_0C = m245_AngleAdd(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            m245_PlayerMotChange(obj, 1);
            move->unk_1C++;
            m245_queueNo = 0;
            break;
        case 1:
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (sqrtf(move->unk_14 * move->unk_14 + move->unk_18 * move->unk_18) > 350.0f) {
                move->unk_1C++;
            }
            break;
        case 2:
            if (move->unk_1E != 0) {
                m245_PlayerMotChange(obj, 0);
                move->unk_1E++;
                if (move->unk_1E < 16) {
                    break;
                }
                m245_PlayerMotChange(obj, 1);
                move->unk_1E = 0;
            }
            move->unk_0C =
                m245_AngleAdd(atan2df(410.0f - move->unk_14, 100.0f - move->unk_18), 0.0f);
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (move->unk_10 == 0.0f) {
                m245_PlayerMotChange(obj, 0);
            } else {
                m245_PlayerMotChange(obj, 1);
            }
            if (move->unk_14 > 390.0f && move->unk_14 < 430.0f && move->unk_18 > 80.0f && move->unk_18 < 120.0f) {
                move->unk_1C++;
            }
            break;
        case 3:
            if (move->unk_1E != 0) {
                m245_PlayerMotChange(obj, 0);
                move->unk_1E++;
                if (move->unk_1E < 16) {
                    break;
                }
                m245_PlayerMotChange(obj, 1);
                move->unk_1E = 0;
            }
            move->unk_0C =
                m245_AngleAdd(atan2df(490.0f - move->unk_14, -20.0f - move->unk_18), 0.0f);
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (move->unk_10 == 0.0f) {
                m245_PlayerMotChange(obj, 0);
            } else {
                m245_PlayerMotChange(obj, 1);
            }
            if (move->unk_14 > 470.0f && move->unk_14 < 510.0f && move->unk_18 > -40.0f && move->unk_18 < 0.0f) {
                move->unk_1C++;
                obj->work[1] = m245_queueNo;
                m245_queueNo++;
            }
            break;
        case 4:
            m245_PlayerMotChange(obj, 2);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            obj->rot.y = 210.0f;
            if (obj->trans.y < 630.0f) {
                obj->trans.y += 10.0f;
            } else {
                obj->trans.y = 630.0f;
                m245_PlayerMotChange(obj, 6);
                move->unk_00.x = (m245_queuePosXTbl[obj->work[1]] - move->unk_14) / 17.0f;
                move->unk_00.y = (m245_queuePosZTbl[obj->work[1]] - move->unk_18) / 17.0f;
                move->unk_00.z = atan2df(move->unk_00.x, move->unk_00.y);
                move->unk_1D = 0;
                move->unk_1C++;
            }
            break;
        case 5:
            if (move->unk_1D == 0) {
                PlayerFXPlay(0x3A, obj->work[0]);
            }
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            m245_PlayerVelApply(obj);
            move->unk_1F = 1;
            obj->trans.y += m245_jumpYTbl[move->unk_1D];
            entry->unk_24 = m245_jumpShadowScaleTbl[move->unk_1D];
            move->unk_1D++;
            if (move->unk_1D >= 17) {
                move->unk_1F = 0;
                m245_PlayerMotChange(obj, 0);
                move->unk_1C++;
                PlayerFXPlay(0x31, obj->work[0]);
            }
            break;
        case 6:
            if (m245_RotYTurn(obj, 330.0f)) {
                m245_PlayerMotChange(obj, 1);
            } else {
                m245_PlayerMotChange(obj, 0);
                m245_doneBits |= 1 << obj->work[1];
                move->unk_1C++;
            }
            break;
        case 7:
            break;
    }
    if (entry->unk_06 == 1) {
        m245_PlayerStepSeUpdate(obj);
    }
}

void m245_PlayerPushUpdate(void) {
    MerryGoChompPlayerWork *move;
    MerryGoChompPlayerWork *other;
    MerryGoChompObjWork *entry;
    MerryGoChompObjWork *otherEntry;
    omObjData *obj;
    omObjData *otherObj;
    s8 push = 0;
    s8 collided;
    s8 i;
    s8 j;
    f32 angle;
    f32 dist;
    f32 dx;
    f32 dz;

    for (i = 0; i < 4; i++) {
        move = &m245_playerWorkTbl[i];
        entry = &m245_objWorkTbl[i + 5];
        obj = entry->obj;
        if (move->unk_1C >= 2 && entry->unk_04 == 0) {
            dist = sqrtf(move->unk_14 * move->unk_14 + move->unk_18 * move->unk_18);
            if (dist < 350.0f) {
                angle = m245_AngleAdd(atan2df(move->unk_14, move->unk_18), 0.0f);
                move->unk_14 = sindf(angle) * 350.0f;
                move->unk_18 = cosdf(angle) * 350.0f;
            }
        }
    }

    do {
        collided = 0;
        for (i = 0; i < 4; i++) {
            move = &m245_playerWorkTbl[i];
            entry = &m245_objWorkTbl[i + 5];
            obj = entry->obj;
            if (entry->unk_04 != 0 || obj->trans.y > 5.0f) {
                continue;
            }
            for (j = 0; j < 4; j++) {
                if (i == j) {
                    continue;
                }
                other = &m245_playerWorkTbl[j];
                otherEntry = &m245_objWorkTbl[j + 5];
                otherObj = otherEntry->obj;
                if (otherEntry->unk_04 != 0) {
                    continue;
                }
                dx = move->unk_14 - other->unk_14;
                dz = move->unk_18 - other->unk_18;
                if (sqrtf(dx * dx + dz * dz) < 120.0f) {
                    dx = move->unk_14 - 490.0f;
                    dz = move->unk_18 + 20.0f;
                    dist = sqrtf(dx * dx + dz * dz);
                    dx = other->unk_14 - 490.0f;
                    dz = other->unk_18 + 20.0f;
                    if (dist < sqrtf(dx * dx + dz * dz)) {
                        push = 2;
                    }
                    if (obj->trans.y > 5.0f && obj->trans.y < 160.0f) {
                        push = 2;
                    }
                    if (otherObj->trans.y > 5.0f && otherObj->trans.y < 160.0f) {
                        push = 1;
                    }
                    if (obj->trans.y > 160.0f) {
                        push = 0;
                    }
                    if (otherObj->trans.y > 160.0f) {
                        push = 0;
                    }
                    switch (push) {
                        case 0:
                            break;
                        case 1:
                            angle = m245_AngleAdd(
                                atan2df(move->unk_14 - other->unk_14, move->unk_18 - other->unk_18), 0.0f);
                            move->unk_14 = sindf(angle) * 121.0f + other->unk_14;
                            move->unk_18 = cosdf(angle) * 121.0f + other->unk_18;
                            move->unk_1E = collided = 1;
                            break;
                        case 2:
                            angle = m245_AngleAdd(
                                atan2df(other->unk_14 - move->unk_14, other->unk_18 - move->unk_18), 0.0f);
                            other->unk_14 = sindf(angle) * 121.0f + move->unk_14;
                            other->unk_18 = cosdf(angle) * 121.0f + move->unk_18;
                            collided = 1;
                            break;
                    }
                }
            }
        }
    } while (collided);

    for (i = 0; i < 4; i++) {
        move = &m245_playerWorkTbl[i];
        entry = &m245_objWorkTbl[i + 5];
        obj = entry->obj;
        if (entry->unk_04 == 0 && move->unk_1C < 5) {
            obj->trans.x = move->unk_14;
            obj->trans.z = move->unk_18;
            obj->rot.y = move->unk_0C;
        }
    }
}

void m245_PlayerObjMain(omObjData *obj) {
    s8 index = obj->work[0];
    MerryGoChompObjWork *entry = &m245_objWorkTbl[index + 5];
    MerryGoChompPlayerWork *move = &m245_playerWorkTbl[index];
    s8 choices[5];
    s8 count;
    s8 i;

    if (entry->unk_04 != 0) {
        if (entry->unk_04 == 2) {
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            entry->unk_04 = 3;
        }
        return;
    }
    switch (m245_phase) {
        case 0:
            move->unk_1C = 0;
            move->unk_1D = 0;
            entry->unk_0C = -1;
            m245_PlayerMotChange(obj, 0);
            break;
        case 1:
            if (m245_timer < 144 && obj->work[1] == m245_jumpTurnNo) {
                if (m245_timer > 0) {
                    if (GwPlayer[index].stat & 1) {
                        if (entry->unk_0C < 0) {
                            for (i = 0, count = 0; i < 5 - m245_roundNo; i++) {
                                if (m245_seatFreeTbl[i] != 0) {
                                    choices[count] = i;
                                    count++;
                                }
                            }
                            entry->unk_0C = choices[m245_RandGet(count)];
                        }
                    } else if (!(HuPadBtnDown[obj->work[3]] & A_BUTTON)) {
                        break;
                    }
                }
                if (m245_PlayerSeatCheck(obj)) {
                    m245_doneBits = 1;
                    m245_PlayerSeatJumpStart(obj);
                }
            }
            break;
        case 2:
            if (obj->work[1] == m245_jumpTurnNo) {
                if (m245_timer == 0) {
                    PlayerFXPlay(0x3A, obj->work[0]);
                }
                if (m245_timer < 15) {
                    move->unk_1F = 1;
                    obj->trans.x += move->unk_00.x;
                    obj->trans.z += move->unk_00.y;
                    obj->trans.y += m245_jumpYTbl[m245_timer];
                    obj->rot.y = move->unk_00.z;
                    entry->unk_24 = m245_jumpShadowScaleTbl[m245_timer];
                }
                if (m245_timer == 10) {
                    m245_PlayerMotChange(obj, 0);
                }
                if (m245_timer == 15) {
                    PlayerFXPlay(0x31, obj->work[0]);
                    move->unk_1F = 0;
                    entry->unk_18 = m245_AngleAdd(atan2df(obj->trans.x, obj->trans.z), 0.0f);
                    entry->unk_1C = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
                    entry->unk_08++;
                }
            } else if (entry->unk_08 == 0) {
                m245_PlayerMotChange(obj, 1);
                m245_PlayerStepSeUpdate(obj);
                obj->trans.x -= 7.0f;
                obj->trans.z += 4.0f;
            }
            break;
        case 3:
            m245_PlayerMotChange(obj, 0);
            break;
        case 4:
            if (m245_timer < 50) {
                m245_PlayerMotChange(obj, 5);
                if (obj->trans.y > 5.0f) {
                    obj->trans.y -= 10.0f;
                } else {
                    obj->trans.y = 5.0f;
                }
            }
            break;
        case 5:
            if (m245_timer < 30) {
                entry->unk_08 = 0;
                if (move->unk_20 == -1) {
                    entry->unk_0E = 3 - m245_roundNo;
                }
            } else if (move->unk_20 == -1) {
                if (!m245_RotYTurn(obj, 270.0f)) {
                    m245_PlayerMotChange(obj, 7);
                    PlayerFXPlay(0x286, obj->work[0]);
                    entry->unk_04 = 1;
                }
            } else if (!m245_RotYTurn(obj, 0.0f)) {
                if (m245_roundNo == 2) {
                    m245_winnerObj = obj;
                    m245_PlayerMotChange(obj, 0);
                } else {
                    m245_PlayerMotChange(obj, 8);
                }
            }
            break;
        case 9:
            m245_PlayerReturnUpdate(obj);
            break;
        case 6:
            if (!m245_RotYTurn(obj, 0.0f)) {
                m245_PlayerMotChange(obj, 8);
            }
            break;
        case 7:
            m245_PlayerMotChange(obj, 5);
            break;
        case 8:
            break;
    }
    if (entry->unk_08 != 0) {
        entry->unk_18 = m245_AngleAdd(entry->unk_18, -m245_carouselSpeed);
        obj->trans.x = sindf(entry->unk_18) * entry->unk_1C;
        obj->trans.z = cosdf(entry->unk_18) * entry->unk_1C;
        obj->rot.y = m245_AngleAdd(obj->rot.y, -m245_carouselSpeed);
    }
    if (move->unk_1F == 0) {
        entry->unk_20 = obj->trans.y;
    }
    if (obj->trans.y > 505.0f) {
        entry->unk_20 = 505.0f;
    }
    if (obj->trans.y <= 5.0f) {
        entry->unk_20 = 5.0f;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, entry->unk_20, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], entry->unk_24, 1.0f, entry->unk_24);
}

void m245_PlayerObjInit(omObjData *obj) {
    u16 player = obj->work[0];
    MerryGoChompObjWork *entry = &m245_objWorkTbl[player + 5];
    u16 chr = GwPlayer[player].chr;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][3], 0x2B9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 2));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x15));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 8));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x8B));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x29));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x7A));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 4));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 9, CharMotionDataNumGet(chr, 0x30));
    omObjMotionRead(obj, 10, CharMotionDataNumGet(chr, 0x37));
    obj->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    omSetTra(obj, m245_queuePosXTbl[obj->work[1]], 505.0f, m245_queuePosZTbl[obj->work[1]]);
    omSetRot(obj, 0.0f, 330.0f, 0.0f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    entry->unk_24 = 1.0f;
    m245_MotSet(obj, 0, 2);
    entry->unk_06 = 0;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    m245_playerWorkTbl[player].unk_00.x = 0.0f;
    m245_playerWorkTbl[player].unk_00.y = 0.0f;
    m245_playerWorkTbl[player].unk_00.z = 0.0f;
    m245_playerWorkTbl[player].unk_1C = 0;
    m245_playerWorkTbl[player].unk_1D = 0;
    m245_playerWorkTbl[player].unk_1F = 0;
    m245_jumpTurnNo = 0;
    obj->work[3] = GwPlayer[player].pad;
    obj->func = m245_PlayerObjMain;
}

void m245_PlayerObjCreateAll(void) {
    MerryGoChompObjWork *entry;
    omObjData *obj;
    s8 slots[4];
    u16 player = 0;
    s8 pick;
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        slots[i] = i;
    }
    for (i = 0; i < 4; i++) {
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
        entry = &m245_objWorkTbl[i + 5];
        obj = omAddObj(0x320, 3, 12, -1, m245_PlayerObjInit);
        obj->work[0] = player;
        entry->obj = obj;
        pick = m245_RandGet(4 - i);
        obj->work[1] = slots[pick];
        slots[pick] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (slots[j - 1] == -1) {
                slots[j - 1] = slots[j];
                slots[j] = -1;
            }
        }
    }
}

void m245_ResultSet(void) {
    MerryGoChompObjWork *entry;
    s8 i;

    for (i = 0; i < 4; i++) {
        entry = &m245_playerObjWorkTbl[i];
        GwPlayer[entry->obj->work[0]].bonusCoin = entry->unk_0E;
    }
}

void m245_WanwanChainUpdate(omObjData *obj) {
    MerryGoChompObjWork *chomp = &m245_objWorkTbl[10];
    Vec2f *link;
    f32 angle;
    f32 divisor;
    f32 dx;
    f32 dz = 0.0f;
    f32 dist;
    s8 i;

    if (chomp->unk_18 != 0.0f || chomp->unk_1C != 0.0f || chomp->unk_30 != obj->rot.y) {
        obj->trans.x += chomp->unk_18;
        obj->trans.z += chomp->unk_1C;
        angle = m245_AngleAdd(obj->rot.y, 180.0f);
        link = m245_chainPosTbl;
        link->x = sindf(angle) * 70.0f + obj->trans.x;
        link->y = cosdf(angle) * 70.0f + obj->trans.z;
        if (chomp->unk_2C > 15.0f) {
            divisor = 2.0f;
        } else {
            divisor = 5.0f;
        }
        for (i = 1; i < 6; i++) {
            link = &m245_chainPosTbl[i];
            dx = m245_chainPosTbl[i - 1].x - link->x;
            dz = m245_chainPosTbl[i - 1].y - link->y;
            dist = dx * dx + dz * dz;
            if (dist > 5625.0f) {
                link->x = dx / divisor + link->x;
                link->y = dz / divisor + link->y;
            }
            Hu3DModelPosSet(obj->model[i], link->x, 30.0f, link->y);
            Hu3DModelPosSet(obj->model[i + 6], link->x, 5.0f, link->y);
        }
        link = &m245_chainPosTbl[5];
        if (link->x != m245_chainAnchor.x || link->y != m245_chainAnchor.y) {
            link->x = m245_chainAnchor.x;
            link->y = m245_chainAnchor.y;
            for (i = 4; i >= 0; i--) {
                link = &m245_chainPosTbl[i];
                dx = m245_chainPosTbl[i + 1].x - link->x;
                dz = m245_chainPosTbl[i + 1].y - link->y;
                dist = dx * dx + dz * dz;
                if (dist > 5625.0f) {
                    link->x = dx / divisor + link->x;
                    link->y = dz / divisor + link->y;
                }
                Hu3DModelPosSet(obj->model[i], link->x, 30.0f, link->y);
                Hu3DModelPosSet(obj->model[i + 6], link->x, 5.0f, link->y);
            }
        }
    }
    chomp->unk_30 = obj->rot.y;
}

void m245_WanwanObjMain(omObjData *obj) {
    f32 angle = 0.0f;
    MerryGoChompObjWork *chomp = &m245_objWorkTbl[10];
    MerryGoChompObjWork *entry = &m245_objWorkTbl[m245_outPlayerNo + 5];
    omObjData *player = entry->obj;
    MerryGoChompPlayerWork *move = &m245_playerWorkTbl[player->work[0]];
    MerryGoChompObjWork *fence = &m245_objWorkTbl[15];
    omObjData *fenceObj = fence->obj;
    omObjData *star = m245_objWorkTbl[30].obj;
    f32 dx;
    f32 dz;
    f32 limit;
    s8 frame;
    s8 pick;

    switch (m245_phase) {
        case 9:
            if (chomp->unk_08 != 0) {
                chomp->unk_10 = 0;
                chomp->unk_04 = 0;
                break;
            }
        case 0:
        case 1:
        case 2:
        case 3:
            if ((s16)chomp->unk_0E > 0) {
                chomp->unk_0E--;
                break;
            }
            if (chomp->unk_04 == 0) {
                chomp->unk_04 = 1;
                pick = m245_RandGet(8);
                if (chomp->unk_0C != pick) {
                    chomp->unk_0C = pick;
                } else {
                    chomp->unk_0C = (pick + 1) % 8;
                }
                chomp->unk_20 = m245_wanwanTargetXTbl[chomp->unk_0C];
                chomp->unk_24 = m245_wanwanTargetZTbl[chomp->unk_0C];
            }
            chomp->unk_28 = atan2df(chomp->unk_20 - obj->trans.x, chomp->unk_24 - obj->trans.z);
            chomp->unk_28 = m245_AngleAdd(chomp->unk_28, 0.0f);
            m245_RotYTurn(obj, chomp->unk_28);
            m245_RotVelCalc(obj, &chomp->unk_18, &chomp->unk_1C, 0.1f);
            dx = chomp->unk_20 - obj->trans.x;
            dz = chomp->unk_24 - obj->trans.z;
            if (dx * dx + dz * dz < 900.0f) {
                chomp->unk_04 = 0;
            }
            if (m245_RandGet(65) == 0) {
                chomp->unk_0E = m245_RandGet(15) + 15;
                chomp->unk_04 = 0;
                chomp->unk_18 = 0.0f;
                chomp->unk_1C = 0.0f;
            }
            break;
        case 4:
            switch (chomp->unk_10) {
                case 0:
                    m245_ChaseVelCalc(-450.0f, 0.0f, obj->trans.x, obj->trans.z, &chomp->unk_18,
                                                 &chomp->unk_1C, &obj->rot.y, 13.0f);
                    if (chomp->unk_18 + chomp->unk_1C == 0.0f) {
                        m245_RotYTurn(obj, 90.0f);
                        if (m245_timer >= 110) {
                            chomp->unk_10 = 1;
                        }
                    }
                    break;
                case 1:
                    if (obj->rot.z < 40.0f) {
                        obj->rot.z += 4.0f;
                    }
                    if (obj->trans.y < 70.0f) {
                        obj->trans.y += 7.0f;
                    }
                    if (obj->trans.x < -350.0f) {
                        obj->trans.x += 10.0f;
                    }
                    if (chomp->unk_06 != 2) {
                        m245_MotShiftSet(obj, 2, 0, 10, 2);
                        Hu3DMotionSpeedSet(obj->model[0], 2.0f);
                        chomp->unk_06 = 2;
                        chomp->unk_34 = 5.0f;
                        chomp->unk_38 = 90.0f;
                    }
                    if (obj->trans.x <= -350.0f) {
                        chomp->unk_10 = 3;
                    }
                    break;
                case 2:
                    if (obj->rot.y > 120.0f) {
                        chomp->unk_34 = -5.0f;
                    }
                    if (obj->rot.y < 60.0f) {
                        chomp->unk_34 = 5.0f;
                    }
                    obj->rot.y += chomp->unk_34;
                    obj->trans.x = sindf(obj->rot.y) * 100.0f + -700.0f;
                    obj->trans.z = cosdf(obj->rot.y) * 60.0f;
                    break;
            }
            break;
        case 5:
            if (chomp->unk_10 == 2) {
                if (obj->rot.y > 120.0f) {
                    chomp->unk_34 = -5.0f;
                }
                if (obj->rot.y < 60.0f) {
                    chomp->unk_34 = 5.0f;
                }
                obj->rot.y += chomp->unk_34;
                obj->trans.x = sindf(obj->rot.y) * 100.0f + -450.0f;
                obj->trans.z = cosdf(obj->rot.y) * 60.0f;
            }
            goto chomp_hit;
        case 6:
            if (chomp->unk_06 != 1) {
                m245_MotSet(obj, 1, 2);
                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                chomp->unk_06 = 1;
            }
            obj->rot.z = 0.0f;
            obj->trans.y = 0.0f;
            obj->trans.x = -450.0f;
            break;
        case 7:
            if (obj->rot.z < 40.0f) {
                obj->rot.z += 4.0f;
            }
            if (obj->trans.y < 70.0f) {
                obj->trans.y += 7.0f;
            }
            if (obj->trans.x < -350.0f) {
                obj->trans.x += 10.0f;
            }
            if (chomp->unk_06 != 2) {
                m245_MotShiftSet(obj, 2, 0, 10, 2);
                Hu3DMotionSpeedSet(obj->model[0], 2.0f);
                chomp->unk_06 = 2;
                chomp->unk_34 = 5.0f;
                chomp->unk_38 = 90.0f;
            }
            break;
        case 8:
        chomp_hit:
            if (chomp->unk_08 == 0 && entry->unk_04 != 0) {
                chomp->unk_10 = 3;
                if (m245_RotYTurn(
                        obj, atan2df(player->trans.x - obj->trans.x, player->trans.z - obj->trans.z))) {
                    obj->trans.x = sindf(obj->rot.y) * 100.0f + -450.0f;
                    obj->trans.z = cosdf(obj->rot.y) * 60.0f;
                }
                frame = Hu3DData[obj->model[0]].motTime;
                if (frame >= 25 && frame < 30) {
                    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
                }
                if (chomp->unk_04 == 10) {
                    Hu3DModelAttrSet(star->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(star->model[0], 1.0f);
                    Hu3DMotionTimeSet(star->model[0], 0.0f);
                    star->scale.x = star->scale.y = star->scale.z = 2.5f;
                    star->trans.x = player->trans.x;
                    star->trans.y = 250.0f;
                    star->trans.z = player->trans.z;
                }
                if (chomp->unk_04 >= 15) {
                    obj->trans.x -= 30.0f;
                }
                if (++chomp->unk_04 >= 20) {
                    chomp->unk_08 = 1;
                    obj->rot.z = 0.0f;
                    obj->trans.y = 0.0f;
                    obj->trans.x = -700.0f;
                    chomp->unk_2C = 100.0f;
                    Hu3DMotionSpeedSet(obj->model[0], 2.0f);
                    chomp->unk_20 = player->trans.x;
                    chomp->unk_24 = player->trans.z;
                }
            }
            break;
    }
    switch (chomp->unk_08) {
        case 0:
            break;
        case 1:
            if (++chomp->unk_0A == 2) {
                player->rot.y = 0.0f;
                move->unk_00.z = 0.0f;
                player->trans.y = 110.0f;
                player->trans.z += 50.0f;
                m245_PlayerMotChange(player, 3);
                Hu3DMotionSpeedSet(obj->model[0], 0.0f);
                HuAudFXPlay(0x476);
                if (!(GwPlayer[player->work[0]].stat & 1)) {
                    omVibrate(player->work[0], 10, 0, 10);
                }
            } else if (chomp->unk_0A >= 3) {
                if (player->rot.x < 90.0f) {
                    player->rot.x += 18.0f;
                }
                star->scale.z = star->scale.y = star->scale.x -= 0.49;
                if (star->scale.x < 0.1) {
                    Hu3DModelAttrSet(star->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
            }
            m245_ChaseVelCalc(chomp->unk_20, chomp->unk_24, obj->trans.x, obj->trans.z, &chomp->unk_18,
                                         &chomp->unk_1C, &obj->rot.y, chomp->unk_2C);
            if (chomp->unk_18 + chomp->unk_1C == 0.0f) {
                chomp->unk_0A = 0;
                chomp->unk_2C = 13.0f;
                chomp->unk_08++;
            }
            break;
        case 2:
            if (chomp->unk_06 != 0) {
                m245_MotSet(obj, 0, 2);
                chomp->unk_06 = 0;
            }
            m245_ChaseVelCalc(-500.0f, 0.0f, obj->trans.x, obj->trans.z, &chomp->unk_18, &chomp->unk_1C,
                                         &angle, chomp->unk_2C);
            m245_ChaseVelCalc(-420.0f, 0.0f, player->trans.x, player->trans.z, &move->unk_00.x,
                                         &move->unk_00.y, &angle, chomp->unk_2C);
            m245_PlayerVelApply(player);
            Hu3DModelPosSet(player->model[1], player->trans.x, 5.0f, player->trans.z);
            if (chomp->unk_18 + chomp->unk_1C == 0.0f) {
                chomp->unk_08++;
                player->rot.x = 0.0f;
                player->trans.x = obj->trans.x + 100.0f;
                player->trans.z = obj->trans.z - 90.0f;
                HuAudFXPlay(0x474);
            }
            break;
        case 3:
            if (fence->unk_44.y < 280.0f) {
                fence->unk_44.y += 40.0f;
            }
            player->rot.z = 270.0f;
            m245_ChaseVelCalc(-400.0f, -280.0f, player->trans.x, player->trans.z, &move->unk_00.x,
                                         &move->unk_00.y, &angle, chomp->unk_2C);
            m245_PlayerVelApply(player);
            Hu3DModelPosSet(player->model[1], player->trans.x, 5.0f, player->trans.z);
            m245_ChaseVelCalc(-500.0f, -200.0f, obj->trans.x, obj->trans.z, &chomp->unk_18,
                                         &chomp->unk_1C, &obj->rot.y, chomp->unk_2C);
            if (chomp->unk_18 + chomp->unk_1C == 0.0f) {
                chomp->unk_08++;
                player->rot.z = 0.0f;
                player->trans.y = 65.0f;
                player->trans.x = obj->trans.x;
                move->unk_00.x = (m245_outPosXTbl[m245_roundNo] - player->trans.x) / 16.0f;
                move->unk_00.y = (m245_outPosZTbl[m245_roundNo] - player->trans.z) / 16.0f;
                move->unk_00.z = atan2df(move->unk_00.x, move->unk_00.y);
            }
            goto fence_pos;
        case 4:
            if (chomp->unk_0A < 16) {
                if (chomp->unk_0A == 0) {
                    PlayerFXPlay(0x3A, player->work[0]);
                }
                player->trans.y += m245_jumpYTbl[chomp->unk_0A];
                m245_PlayerVelApply(player);
                player->rot.y = 0.0f;
                m245_MotSet(player, 4, 2);
                entry->unk_06 = 0;
                Hu3DMotionSpeedSet(player->model[0], 0.0f);
                Hu3DModelPosSet(player->model[1], player->trans.x, 5.0f, player->trans.z);
            }
            if (chomp->unk_0A == 16) {
                PlayerFXPlay(0x31, player->work[0]);
                entry->unk_04 = 2;
            }
            if (++chomp->unk_0A >= 11) {
                m245_ChaseVelCalc(-500.0f, 100.0f, obj->trans.x, obj->trans.z, &chomp->unk_18,
                                             &chomp->unk_1C, &obj->rot.y, chomp->unk_2C);
            }
            if (chomp->unk_0A == 20) {
                HuAudFXPlay(0x475);
            }
            if (chomp->unk_0A >= 21) {
                if (fence->unk_44.y > 0.0f) {
                    fence->unk_44.y -= 40.0f;
                } else if (chomp->unk_18 + chomp->unk_1C == 0.0f) {
                    chomp->unk_0A = 0;
                    chomp->unk_08 = 0;
                }
            }
        fence_pos:
            Hu3DModelPosSet(fenceObj->model[1], fenceObj->trans.x, fence->unk_44.y, fence->unk_44.z);
            break;
    }
    m245_WanwanChainUpdate(obj);
    if (chomp->unk_08 == 1 || chomp->unk_08 == 2) {
        limit = obj->trans.x + 80.0f;
        if (player->trans.x < limit) {
            player->trans.x = limit;
        }
    }
    if (chomp->unk_10 == 0) {
        Hu3DModelPosSet(obj->model[6], obj->trans.x, 5.0f, obj->trans.z);
    }
}

void m245_WanwanObjInit(omObjData *obj) {
    MerryGoChompObjWork *chomp = &m245_objWorkTbl[10];
    void *anim = DataRead(0xA00E5);
    s32 chain;
    s32 shadow;
    s16 i;

    obj->model[0] = Hu3DModelRead(0xA00D9, 0x2A9);
    Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, anim, 0, "c165n_4_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    DataClose(anim);
    omObjMotionRead(obj, 0, 0xA00DD);
    omObjMotionRead(obj, 1, 0xA00E3);
    omObjMotionRead(obj, 2, 0xA00DB);
    obj->model[1] = Hu3DModelRead(0xA00E4, 0x2B9);
    chain = obj->model[1];
    for (i = 2; i < 6; i++) {
        obj->model[i] = Hu3DModelLink(chain);
    }
    shadow = obj->model[6] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[6], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[6]);
    Hu3DModelDynamicFree(obj->model[6]);
    HuTranslateF(Hu3DData[obj->model[6]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 2.5f, 1.0f, 2.5f);
    for (i = 7; i < 12; i++) {
        obj->model[i] = Hu3DModelLink(shadow);
    }
    m245_MotSet(obj, 0, 2);
    chomp->unk_06 = 0;
    omSetTra(obj, -500.0f, 0.0f, 60.0f);
    omSetRot(obj, 0.0f, 60.0f, 0.0f);
    Hu3DModelPosSet(obj->model[6], obj->trans.x, obj->trans.y, obj->trans.z);
    for (i = 0; i < 7; i++) {
        Hu3DModelCameraSet(obj->model[i], HU3D_CAM1);
    }
    for (i = 1; i < 6; i++) {
        m245_chainPosTbl[i].x = (5 - i) * 45 + m245_chainAnchor.x + 20.0f;
        m245_chainPosTbl[i].y = (5 - i) * 10 + m245_chainAnchor.y;
        Hu3DModelPosSet(obj->model[i], m245_chainPosTbl[i].x, 30.0f, m245_chainPosTbl[i].y);
        Hu3DModelPosSet(obj->model[i + 6], m245_chainPosTbl[i].x, 5.0f, m245_chainPosTbl[i].y);
        Hu3DModelScaleSet(obj->model[i + 6], 0.8f, 1.0f, 0.8f);
    }
    Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[11], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->func = m245_WanwanObjMain;
}

const char m245_emptyStr[] = "";

void m245_WanwanObjCreate(void) {
    m245_wanwanObj = omAddObj(0x384, 0xF, 4, -1, m245_WanwanObjInit);
}

void m245_BiteEffObjMain(omObjData *obj) {
}

void m245_BiteEffObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x4E0003, 0x2B9);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    obj->scale.x = obj->scale.y = obj->scale.z = 2.5f;
    obj->rot.y = 270.0f;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    obj->func = m245_BiteEffObjMain;
}

void m245_BiteEffObjCreate(void) {
    m245_biteEffObj = omAddObj(0x3E8, 1, 1, -1, m245_BiteEffObjInit);
}

void m245_RoundUpdate(void) {
    omObjData *obj = m245_carouselObj;
    s8 result;

    switch (m245_phase) {
        case 0:
            GMesCreate(GMES_MES_TIMER, 10, 0xA0, 0x1C);
            m245_timer = 151;
            if (m245_carouselSeRound == m245_roundNo) {
                m245_carouselSeNo = HuAudFXPlay(0x471);
                m245_spinSeNo = -1;
                m245_carouselSeRound++;
            }
            m245_carouselSpeed = 3.0f;
            m245_phase = 1;
            break;
        case 1:
            if (m245_timer > 0) {
                m245_timer--;
                GMesTimerValueSet((m245_timer + 29) / 30);
            } else {
                GMesTimerEnd();
            }
            if (m245_doneBits != 0) {
                m245_doneBits = 0;
                GMesTimerEnd();
                m245_timer = 0;
                m245_phase = 2;
            }
            break;
        case 2:
            if (m245_timer < 15) {
                m245_timer++;
            } else if (++m245_jumpTurnNo == 4 - m245_roundNo) {
                m245_phase = 3;
                m245_timer = 0;
                switch (m245_roundNo) {
                    case 0:
                        m245_stopSeatNo = m245_RandGet(5);
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(270.0f, -m245_stopSeatNo * 72);
                        break;
                    case 1:
                        m245_stopSeatNo = m245_RandGet(4);
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(270.0f, -m245_stopSeatNo * 90);
                        break;
                    case 2:
                        m245_stopSeatNo = m245_RandGet(3);
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(270.0f, -m245_stopSeatNo * 120);
                        break;
                }
                m245_stopAngleTbl[0] = m245_AngleAdd(m245_stopAngleTbl[0], -3.0f);
                m245_stopAngleTbl[1] = m245_AngleAdd(m245_stopAngleTbl[0], 6.0f);
                m245_spinSeNo = HuAudFXPlay(0x472);
            } else {
                m245_phase = 0;
            }
            break;
        case 3:
            m245_spinSePitch = m245_carouselSpeed * 40.0f;
            if (m245_spinSePitch > 1200) {
                m245_spinSePitch = 1200;
            }
            HuAudFXPitchSet(m245_carouselSeNo, m245_spinSePitch);
            if (m245_spinSeNo > 0) {
                m245_spinSeSpeed = m245_carouselSpeed * 26.0f;
                HuAudFXPitchSet(m245_spinSeNo, m245_spinSePitch);
            }
            if (m245_timer < 54) {
                m245_timer++;
                m245_carouselSpeed += 0.5;
                if (m245_timer == 53) {
                    obj->rot.y -= 0.5;
                }
            } else {
                m245_timer = 0;
                m245_carouselSpeed = 30.0f;
                m245_phase = 4;
            }
            break;
        case 4:
            m245_spinSePitch = m245_carouselSpeed * 40.0f;
            if (m245_spinSePitch > 1200) {
                m245_spinSePitch = 1200;
            }
            HuAudFXPitchSet(m245_carouselSeNo, m245_spinSePitch);
            HuAudFXPitchSet(m245_spinSeNo, m245_spinSePitch);
            m245_timer++;
            if (m245_carouselSpeed > 3.0f) {
                m245_carouselSpeed -= 0.2f;
            } else {
                m245_carouselSpeed = 3.0f;
                if ((obj->rot.y >= m245_stopAngleTbl[0] && obj->rot.y <= m245_stopAngleTbl[1]) ||
                    (obj->rot.y >= m245_stopAngleTbl[0] && obj->rot.y > 355.0f &&
                     m245_stopAngleTbl[1] < 5.0f) ||
                    (obj->rot.y < 5.0f && obj->rot.y <= m245_stopAngleTbl[1] &&
                     m245_stopAngleTbl[0] > 355.0f)) {
                    m245_carouselSpeed = 0.0f;
                    m245_timer = 0;
                    HuAudFXStop(m245_carouselSeNo);
                    HuAudFXStop(m245_spinSeNo);
                    HuAudFXPlay(0x477);
                    result = m245_OutPlayerGet();
                    if (result == -1) {
                        m245_timer = 0;
                        m245_phase = 6;
                    } else {
                        m245_outPlayerNo = result;
                        m245_phase = 5;
                    }
                }
            }
            break;
        case 6:
            if (++m245_timer > 60) {
                switch (m245_roundNo) {
                    case 0:
                        m245_stopSeatNo = m245_RandGet(4) + 1;
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(obj->rot.y, -m245_stopSeatNo * 72);
                        break;
                    case 1:
                        m245_stopSeatNo = m245_RandGet(3) + 1;
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(obj->rot.y, -m245_stopSeatNo * 90);
                        break;
                    case 2:
                        m245_stopSeatNo = m245_RandGet(2) + 1;
                        m245_stopAngleTbl[0] =
                            m245_AngleAdd(obj->rot.y, -m245_stopSeatNo * 120);
                        break;
                }
                m245_stopAngleTbl[0] = m245_AngleAdd(m245_stopAngleTbl[0], -3.0f);
                m245_stopAngleTbl[1] = m245_AngleAdd(m245_stopAngleTbl[0], 6.0f);
                m245_phase = 7;
                m245_carouselSpeed = 3.0f;
                m245_timer = 0;
                m245_carouselSeNo = HuAudFXPlay(0x471);
                m245_spinSeNo = HuAudFXPlay(0x472);
            }
            break;
        case 7:
            m245_spinSePitch = m245_carouselSpeed * 40.0f;
            if (m245_spinSePitch > 1200) {
                m245_spinSePitch = 1200;
            }
            HuAudFXPitchSet(m245_carouselSeNo, m245_spinSePitch);
            if (m245_spinSeNo > 0) {
                m245_spinSeSpeed = m245_carouselSpeed * 26.0f;
                HuAudFXPitchSet(m245_spinSeNo, m245_spinSePitch);
            }
            if (m245_timer < 54) {
                m245_timer++;
                m245_carouselSpeed += 0.5;
                if (m245_timer == 53) {
                    obj->rot.y -= 0.5;
                }
            } else {
                m245_timer = 0;
                m245_carouselSpeed = 30.0f;
                m245_phase = 4;
            }
            break;
        case 8:
            m245_spinSePitch = m245_carouselSpeed * 40.0f;
            if (m245_spinSePitch > 1200) {
                m245_spinSePitch = 1200;
            }
            HuAudFXPitchSet(m245_carouselSeNo, m245_spinSePitch);
            HuAudFXPitchSet(m245_spinSeNo, m245_spinSePitch);
            m245_timer++;
            if (m245_carouselSpeed > 3.0f) {
                m245_carouselSpeed -= 0.2f;
            } else {
                m245_carouselSpeed = 3.0f;
                if ((obj->rot.y >= m245_stopAngleTbl[0] && obj->rot.y <= m245_stopAngleTbl[1]) ||
                    (obj->rot.y >= m245_stopAngleTbl[0] && obj->rot.y > 355.0f &&
                     m245_stopAngleTbl[1] < 5.0f) ||
                    (obj->rot.y < 5.0f && obj->rot.y <= m245_stopAngleTbl[1] &&
                     m245_stopAngleTbl[0] > 355.0f)) {
                    m245_carouselSpeed = 0.0f;
                    m245_timer = 0;
                    HuAudFXStop(m245_carouselSeNo);
                    HuAudFXStop(m245_spinSeNo);
                    HuAudFXPlay(0x477);
                    result = m245_OutPlayerGet();
                    if (result == -1) {
                        m245_timer = 0;
                        m245_phase = 6;
                    } else {
                        m245_outPlayerNo = result;
                        m245_phase = 5;
                    }
                }
            }
            break;
        case 5:
            if (m245_timer < 80) {
                m245_timer++;
            } else {
                m245_timer = 0;
                if (m245_roundNo == 2) {
                    m245_phase = 10;
                } else {
                    m245_phase = 9;
                }
            }
            break;
        case 9:
            if (m245_timer < 50) {
                m245_timer++;
            }
            if ((m245_roundNo == 0 && m245_doneBits == 15) ||
                (m245_roundNo == 1 && m245_doneBits == 11)) {
                m245_doneBits = 0;
                m245_timer = 0;
                m245_jumpTurnNo = 0;
                m245_seatFreeTbl[0] = 1;
                m245_seatFreeTbl[1] = 1;
                m245_seatFreeTbl[2] = 1;
                m245_seatFreeTbl[3] = 1;
                m245_roundNo++;
                m245_phase = 0;
            }
            break;
        case 10:
            break;
    }
}

void m245_CameraViewInit(void) {
    u32 i;

    if (m245_cameraSetF == 0) {
        m245_cameraSetF = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 2023.0191f;
            CRotM[i].x = 330.45712f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 500.0f;
            CenterM[i].z = 140.0f;
        }
    }
}

void m245_ExitObjMain(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m245_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m245_ExitObjMain;
    }
}

void m245_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m245_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m245_MainObjMain(omObjData *obj) {
    switch (m245_seqNo) {
        case 0:
            GMesCreate(GMES_MES_7);
            m245_seqNo = 1;
            m245_musicTimer = 0;
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m245_seqNo = 2;
                m245_phase = 0;
            }
            if (++m245_musicTimer == 4) {
                HuAudSeqPlay(0x34);
            }
            break;
        case 2:
            if (m245_phase == 9) {
                m245_PlayerPushUpdate();
            }
            m245_RoundUpdate();
            if (m245_phase == 10) {
                GMesCreate(GMES_MES_18);
                m245_ResultSet();
                HuAudSeqFadeOut(120);
                m245_timer = 0;
                m245_seqNo = 3;
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                if (++m245_timer == 15) {
                    HuAudSeqPlay(0x65);
                    m245_PlayerMotChange(m245_winnerObj, 9);
                }
                if (m245_timer == 113) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    obj->func = m245_ExitWaitObjMain;
                }
            }
            break;
    }
}

void m245_MainObjInit(omObjData *obj) {
    m245_seqNo = 0;
    m245_phase = 20;
    m245_doneBits = 0;
    m245_timer = 0;
    m245_roundNo = 0;
    m245_carouselSpeed = 0;
    m245_carouselSeNo = m245_spinSeNo = -1;
    m245_stopSeatNo = 0;
    m245_outPlayerNo = 0;
    m245_carouselSeRound = 0;
    m245_CameraViewInit();
    m245_BackObjCreate();
    m245_PlayerObjCreateAll();
    m245_WanwanObjCreate();
    m245_CarouselObjCreate();
    m245_StageObjCreate();
    m245_BiteEffObjCreate();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    obj->func = m245_MainObjMain;
}

void m245_Dummy(void) {
}

void m245_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, m245_cameraViewTbl[i].scissorX, m245_cameraViewTbl[i].scissorY,
                   m245_cameraViewTbl[i].scissorWidth, m245_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m245_cameraViewTbl[i].viewportScale.x, m245_cameraViewTbl[i].viewportScale.y,
                    m245_cameraViewTbl[i].viewportScale.z, m245_cameraViewTbl[i].viewportTranslate.x,
                    m245_cameraViewTbl[i].viewportTranslate.y, m245_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m245_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m245_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(60, 0);
    omGameSysInit();
    m245_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, -33.0f, 0.0f, 115.0f);
    Hu3DGLightDirSet(1, -33.0f, 0.0f, 115.0f);
    Hu3DGLightDirSet(2, -33.0f, 0.0f, 115.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m245_fontMesTbl, 0);
    GMesFontMesCreate(m245_fontMesTbl, 1);
    omAddObj(1500, 0, 0, -1, m245_MainObjInit);
    omAddObj(1500, 0, 0, -1, m245_ExitCheckObjMain);
    m245_ObjWorkInit();
}

const s16 m245_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
