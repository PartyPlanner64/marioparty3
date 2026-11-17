#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

// One entry of the 50 entry object table at m243_objWorkTbl.
// Layout derived from the table clear in m243_ObjWorkInit.
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
} ThreeDoorMontyObjWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} ThreeDoorMontyCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[3];
} ThreeDoorMontyDoorWork; // sizeof 0x8

extern u8 omAllPauseF;
extern s32 omCharModelNoTbl[][6];
extern const s16 m243_fontMesTbl[];
// obj of m243_objWorkTbl[8], accessed through a separate symbol.
extern omObjData *m243_signObj;
// unk_18 of m243_objWorkTbl[8], accessed through a separate symbol.
extern f32 m243_signScale;
// obj of m243_objWorkTbl[12], accessed through a separate symbol.
extern omObjData *m243_waterObj;
// unk_18 of m243_objWorkTbl[12], accessed through a separate symbol.
extern f32 m243_waterScroll;
extern u8 m243_teresaAlphaLo; // low byte of m243_teresaAlpha
extern s16 m243_hopF;    // m243_doorWork.unk_00
extern s16 m243_doorChrTbl[3]; // m243_doorWork.unk_02

// walking speeds, indexed by obj->work[0]
f32 m243_chrWalkSpeedTbl[3] = { 13.0f, 14.0f, 15.0f };
f32 m243_chrRunSpeedTbl[3] = { 20.0f, 21.0f, 22.0f };
s32 m243_chrMotTbl[3][2] = {
    { 1, 6 },
    { 143, 145 },
    { 199, 199 },
};
Vec2f m243_doorPosTbl[3] = {
    { -345.0f, -775.0f },
    { 0.0f, -775.0f },
    { 345.0f, -775.0f },
};
s32 m243_answerMdlTbl[3] = { 7, 8, 9 };
s32 m243_digitXTbl[4][4] = {
    { 44, 54, 64, 74 },
    { 108, 118, 128, 138 },
    { 172, 182, 192, 202 },
    { 236, 246, 256, 266 },
};
// per-character voice bank
s32 m243_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 m243_sidePosTbl[2][2] = { { 99, 51 }, { 212, 51 } };
s32 m243_cameraSetF = 0;
ThreeDoorMontyCamera m243_cameraViewTbl[3] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
};

s16 m243_doneCnt BSS;
s16 m243_resultWait BSS;
u16 m243_waterTexSize[2] BSS;
void *m243_signAnimDataTbl[3] BSS;
s16 m243_reactFTbl[4] BSS;
HuSprAnimData *m243_lowerBackSpr BSS;
s16 m243_targetChr BSS;
s16 m243_teresaFadeState BSS;
s16 m243_answerTime BSS;
s16 m243_digitSeNo BSS;
s16 m243_answerCnt BSS;
u8 m243_answerCntPad[4] BSS; /* Unreferenced. */
ThreeDoorMontyObjWork m243_objWorkTbl[50] BSS;
HuSprAnimData *m243_sideSprTbl[2] BSS;
u8 m243_phase BSS;
s16 m243_timer BSS;
HuSprAnimData *m243_upperBackSpr BSS;
u16 m243_rankNo BSS;
s16 m243_revealF BSS;
s16 m243_revealState BSS;
s16 m243_signAnim BSS;
s16 m243_digitSeState BSS;
u8 m243_phaseDoneNo BSS;
s16 m243_allAnsweredF BSS;
s16 m243_teresaAlpha BSS;
ThreeDoorMontyDoorWork m243_doorWork BSS;
s16 m243_signSeStep BSS;

void m243_VelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed);
void m243_BackObjMain(omObjData *obj);
void m243_BackObjInit(omObjData *);
void m243_ObjectSetup(void);
void m243_LowerBackDraw(Gfx **gfxP, s32 arg1, s32 arg2);
void m243_UpperBackDraw(Gfx **gfxP, s32 arg1, s32 arg2);
void m243_SideDraw(Gfx **gfxP, s32 arg1, s32 arg2);
void m243_WaterObjMain(omObjData *obj);
void m243_WaterObjInit(omObjData *);
void m243_SignObjInit(omObjData *);
void m243_ChrObjMain(omObjData *obj);
void m243_ChrObjInit(omObjData *obj);
void m243_SignObjMain(omObjData *obj);
void m243_DoorObjMain(omObjData *obj);
void m243_PlayerObjMain(omObjData *obj);
void m243_PlayerObjInit(omObjData *obj);
void m243_DigitObjMain(omObjData *obj);
void m243_DigitObjInit(omObjData *obj);
void m243_ExitCheckObjMain(omObjData *obj);
void m243_MainObjInit(omObjData *obj);
void m243_MainObjMain(omObjData *obj);
void m243_PlayerObjCreateAll(void);
void m243_DigitObjCreateAll(void);
void m243_CameraViewInit(void);
void m243_DoorObjInit(omObjData *obj);

void m243_Executor(void) {
    m243_ObjectSetup();
}

f32 m243_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m243_RandMulGet(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void m243_ObjWorkInit(void) {
    ThreeDoorMontyObjWork *entry;
    u32 i;

    for (i = 0, entry = m243_objWorkTbl; i < 50; i++, entry++) {
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

void m243_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m243_CameraDebugPrint(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = m243_AngleAdd(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void m243_CameraDebugPad(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)HuPadBtn[conNo] & D_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = m243_AngleAdd(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & U_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].x = m243_AngleAdd(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & L_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = m243_AngleAdd(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & R_JPAD) {
        for (i = 0; i < 3; i++) {
            CRotM[i].y = m243_AngleAdd(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & A_BUTTON) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & B_BUTTON) {
        for (i = 0; i < 3; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & L_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & R_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & U_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & D_CBUTTONS) {
        for (i = 0; i < 3; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 3; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

void m243_PhaseSet(u8 value) {
    m243_phase = value;
}

void m243_MotShiftSet(omObjData *obj, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

void m243_MotSet(omObjData *obj, s16 motion, s16 start, s16 end, s16 *current) {
    if (*current != motion) {
        Hu3DMotionModelSet(obj->model[0], obj->motion[motion]);
        Hu3DMotionAttrSet(obj->model[0], start, end);
        *current = motion;
    }
}

void m243_VelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1;
    f32 dz = z1;
    f32 absDx;
    f32 absDz;
    f32 delta;
    f32 dist;
    f32 step;

    dx -= x0;
    dz -= z0;
    absDx = fabsf(dx);
    absDz = fabsf(dz);

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        dist = absDx;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velZ = -(delta / step);
    } else {
        if (dz >= 0.0f) {
            *velZ = -speed;
        } else {
            *velZ = speed;
        }
        delta = dx;
        dist = absDz;
        step = speed;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velX = -(delta / step);
    }
}

void m243_RotVelCalc(omObjData *obj, f32 *outX, f32 *outZ, f32 scale) {
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

f32 m243_AngleTurnCalc(f32 current, f32 target, f32 step) {
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (current < target) {
        if (diff > 180.0f) {
            current = m243_AngleAdd(current, -step);
        } else {
            current = m243_AngleAdd(current, step);
        }
        return current;
    } else if (target < current) {
        if (diff > 180.0f) {
            current = m243_AngleAdd(current, step);
        } else {
            current = m243_AngleAdd(current, -step);
        }
        return current;
    }
    return 0.0f;
}

f32 m243_GravityCalc(f32 base, f32 *value, f32 step) {
    f32 prev = *value;

    *value = prev - step;
    return base + prev;
}

const char m243_signTexName[] = "243_kino_DEF";

void m243_SignAnimSet(omObjData *obj, u8 index) {
    Hu3DAnimKill(m243_signAnim);
    m243_signAnim = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m243_signAnimDataTbl[index], 0, m243_signTexName);
}

void m243_LowerBackDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

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
    gDPLoadTLUT_pal256(gfx++, m243_lowerBackSpr->pal);
    x = 0;
    // j is never incremented here, unlike in m243_UpperBackDraw.
    for (i = 0, y = 49, j = 0; i < 191; i += 4) {
        i -= (j >= 12);
        gDPLoadTextureTile(gfx++, m243_lowerBackSpr->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void m243_UpperBackDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;
    s32 j;

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
    gDPLoadTLUT_pal256(gfx++, m243_upperBackSpr->pal);
    x = 0;
    for (i = 0, y = 0, j = 0; i < 51; i += 4, j++) {
        i -= (j >= 12);
        gDPLoadTextureTile(gfx++, m243_upperBackSpr->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void m243_SideDraw(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
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
    for (i = 0; i < 2; i++) {
        gDPLoadTLUT_pal16(gfx++, 0, m243_sideSprTbl[i]->pal);
        gDPLoadTextureTile_4b(gfx++, m243_sideSprTbl[i]->data, G_IM_FMT_CI, 8, 32, 0, 0, 8, 32, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                              G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 8 << 2, 32 << 2);
        gSPTextureRectangle(gfx++, m243_sidePosTbl[i][0] << 2, m243_sidePosTbl[i][1] << 2,
                            (m243_sidePosTbl[i][0] + 8) << 2, (m243_sidePosTbl[i][1] + 32) << 2,
                            G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfxP = gfx;
}

void m243_BackObjMain(omObjData *obj) {
}

void m243_BackObjInit(omObjData *obj) {
    m243_upperBackSpr = HuSprAnimDataGet(HuSprAnimDataRead(0x4C0004));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m243_UpperBackDraw, 2), HU3D_CAM1);
    m243_lowerBackSpr = HuSprAnimDataGet(HuSprAnimDataRead(0x4C0003));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m243_LowerBackDraw, 2), HU3D_CAM0);
    m243_sideSprTbl[0] = HuSprAnimDataGet(HuSprAnimDataRead(0x4C0005));
    m243_sideSprTbl[1] = HuSprAnimDataGet(HuSprAnimDataRead(0x4C0006));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, m243_SideDraw, 2), HU3D_CAM1);
    obj->model[0] = Hu3DModelRead(0x4C000F, 0x289);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    obj->func = m243_BackObjMain;
}

void m243_BackObjCreate(void) {
    omObjData *obj = omAddObj(0x32, 5, 0xA, -1, m243_BackObjInit);
    obj->work[0] = 0;
    m243_objWorkTbl[0].obj = obj;
}

void m243_WaterObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[12];

    if (omPauseChk() + omAllPauseF == 0) {
        m243_waterScroll += 0.05f;
    }
    Hu3DModelObjTexScroll(obj->model[0], entry->unk_18, 0.0f, m243_waterTexSize[0], m243_waterTexSize[1],
                       "dammy-castle_ground1_2", 0);
}

void m243_WaterObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x4C000D, 0x2A9);
    Hu3DModelVtxBufMake(obj->model[0]);
    Hu3DTexSizeGet("243_water_DEF", m243_waterTexSize);
    m243_objWorkTbl[12].unk_18 = 0.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    obj->func = m243_WaterObjMain;
}

void m243_WaterObjCreate(void) {
    omObjData *obj = omAddObj(0x10E, 1, 0, -1, m243_WaterObjInit);
    obj->work[0] = 0;
    m243_waterObj = obj;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m243_ChrShuffleUpdate(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[5 + obj->work[0]];
    ThreeDoorMontyObjWork *entryA;
    ThreeDoorMontyObjWork *entryB;
    omObjData *objA;
    omObjData *objB;
    f32 velX;
    f32 velZ;
    f32 temp;
    s16 door;
    s16 i;
    s16 j;

    velX = velZ = 0.0f;
    switch (entry->unk_06) {
        case 0:
            if (entry->unk_08 == -1) {
                door = (u8)(rand8() % 3);
                while (TRUE) {
                    if (m243_timer < 60) {
                        if (door != entry->unk_0A) {
                            entry->unk_08 = door;
                            break;
                        }
                    } else if (m243_doorChrTbl[door] == -1) {
                        entry->unk_08 = door;
                        break;
                    }
                    door++;
                    if (door >= 3) {
                        door = 0;
                    }
                }
            } else {
                entry->unk_0A = entry->unk_08;
                if (m243_doorPosTbl[entry->unk_08].y + 300.0f < obj->trans.z) {
                    if (m243_timer < 60) {
                        m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                       m243_doorPosTbl[entry->unk_08].y + 300.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, m243_chrWalkSpeedTbl[obj->work[0]]);
                    } else {
                        m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                       m243_doorPosTbl[entry->unk_08].y + 300.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, m243_chrRunSpeedTbl[obj->work[0]]);
                    }
                    entry->unk_1C = atan2df(m243_doorPosTbl[entry->unk_08].x - obj->trans.x,
                                            m243_doorPosTbl[entry->unk_08].y + 300.0f - obj->trans.z);
                    entry->unk_1C = m243_AngleAdd(entry->unk_1C, 0.0f);
                    obj->rot.y = m243_AngleTurnCalc(obj->rot.y, entry->unk_1C, 15.0f);
                    obj->trans.x += velX;
                    obj->trans.z += velZ;
                } else if (m243_doorPosTbl[entry->unk_08].y - 500.0f < obj->trans.z) {
                    if (m243_timer < 60) {
                        m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                       m243_doorPosTbl[entry->unk_08].y - 500.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, m243_chrWalkSpeedTbl[obj->work[0]]);
                    } else {
                        m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                       m243_doorPosTbl[entry->unk_08].y - 500.0f, obj->trans.x,
                                                       obj->trans.z, &velX, &velZ, m243_chrRunSpeedTbl[obj->work[0]]);
                    }
                    entry->unk_1C = atan2df(m243_doorPosTbl[entry->unk_08].x - obj->trans.x,
                                            m243_doorPosTbl[entry->unk_08].y - 500.0f - obj->trans.z);
                    entry->unk_1C = m243_AngleAdd(entry->unk_1C, 0.0f);
                    obj->rot.y = m243_AngleTurnCalc(obj->rot.y, entry->unk_1C, 15.0f);
                    obj->trans.x += velX;
                    obj->trans.z += velZ;
                } else if (m243_timer < 60) {
                    if ((u8)(rand8() % 30) == 0) {
                        entry->unk_06 = 2;
                    }
                } else {
                    m243_doorChrTbl[entry->unk_08] = obj->work[0];
                    entry->unk_06 = 5;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (obj->trans.z < m243_doorPosTbl[entry->unk_08].y + 260.0f) {
                if (m243_timer < 60) {
                    m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                   m243_doorPosTbl[entry->unk_08].y + 280.0f, obj->trans.x,
                                                   obj->trans.z, &velX, &velZ, m243_chrWalkSpeedTbl[obj->work[0]]);
                } else {
                    m243_VelCalc(m243_doorPosTbl[entry->unk_08].x,
                                                   m243_doorPosTbl[entry->unk_08].y + 280.0f, obj->trans.x,
                                                   obj->trans.z, &velX, &velZ, m243_chrRunSpeedTbl[obj->work[0]]);
                }
                entry->unk_1C = atan2df(m243_doorPosTbl[entry->unk_08].x - obj->trans.x,
                                        m243_doorPosTbl[entry->unk_08].y + 280.0f - obj->trans.z);
                entry->unk_1C = m243_AngleAdd(entry->unk_1C, 0.0f);
                obj->rot.y = m243_AngleTurnCalc(obj->rot.y, entry->unk_1C, 15.0f);
                obj->trans.x += velX;
                obj->trans.z += velZ;
            } else {
                door = (u8)(rand8() % 3);
                while (TRUE) {
                    if (m243_timer < 60) {
                        if (door != entry->unk_0A) {
                            entry->unk_08 = door;
                            break;
                        }
                    } else if (m243_doorChrTbl[door] == -1) {
                        entry->unk_08 = door;
                        break;
                    }
                    door++;
                    if (door >= 3) {
                        door = 0;
                    }
                }
                switch (entry->unk_0A) {
                    case 0:
                        if (entry->unk_08 == 1) {
                            entry->unk_06 = 3;
                            entry->unk_3C = 4.0f;
                        }
                        if (entry->unk_08 == 2) {
                            entry->unk_06 = 6;
                            entry->unk_3C = 4.0f;
                        }
                        break;
                    case 1:
                        if (entry->unk_08 == 0) {
                            entry->unk_06 = 3;
                            entry->unk_3C = -4.0f;
                        }
                        if (entry->unk_08 == 2) {
                            entry->unk_06 = 3;
                            entry->unk_3C = 4.0f;
                        }
                        break;
                    case 2:
                        if (entry->unk_08 == 0) {
                            entry->unk_06 = 6;
                            entry->unk_3C = -4.0f;
                        }
                        if (entry->unk_08 == 1) {
                            entry->unk_06 = 3;
                            entry->unk_3C = -4.0f;
                        }
                        break;
                }
                entry->unk_16 = 0;
            }
            break;
        case 3:
            entry->unk_0A = entry->unk_08;
            m243_RotVelCalc(obj, &velX, &velZ, 0.17f);
            obj->trans.x += velX;
            obj->trans.z += velZ;
            obj->rot.y = m243_AngleAdd(obj->rot.y, entry->unk_3C);
            if (++entry->unk_16 >= 46) {
                entry->unk_06 = 0;
            }
            break;
        case 4:
            if (entry->unk_04 != 0) {
                obj->rot.y = m243_AngleTurnCalc(obj->rot.y, 0.0f, 15.0f);
            }
            if (obj->trans.z < -225.0f) {
                if (m243_timer < 60) {
                    velZ = m243_chrWalkSpeedTbl[obj->work[0]];
                } else {
                    velZ = m243_chrRunSpeedTbl[obj->work[0]];
                }
                obj->trans.z += velZ;
            } else {
                m243_MotShiftSet(obj, 0, 0, 3, 2, &entry->unk_04);
                if (entry->unk_0E >= 5) {
                    entry->unk_06 = 0;
                    entry->unk_0E = 0;
                    m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                } else {
                    entry->unk_0E++;
                }
            }
            break;
        case 5:
            break;
        case 6:
            m243_RotVelCalc(obj, &velX, &velZ, 0.25f);
            obj->trans.x += velX;
            obj->trans.z += velZ;
            obj->rot.y = m243_AngleAdd(obj->rot.y, entry->unk_3C);
            if (++entry->unk_16 >= 23) {
                entry->unk_06 = 0;
            }
            break;
    }
    if (obj->work[0] == 2) {
        for (i = 0; i < 3; i++) {
            entryA = &m243_objWorkTbl[5 + i];
            objA = entryA->obj;
            for (j = 0; j < 3; j++) {
                entryB = &m243_objWorkTbl[5 + j];
                objB = entryB->obj;
                if (objB->work[0] == objA->work[0]) {
                    continue;
                }
                if (objB->trans.x + 50.0f > objA->trans.x - 50.0f && objB->trans.x - 50.0f < objA->trans.x + 50.0f &&
                    objB->trans.z + 50.0f > objA->trans.z - 50.0f && objB->trans.z - 50.0f < objA->trans.z + 50.0f) {
                    if (objA->trans.z < m243_doorPosTbl[0].y - 350.0f &&
                        objB->trans.z < m243_doorPosTbl[0].y - 350.0f) {
                        if (rand8() & 1) {
                            temp = objB->trans.z;
                            objB->trans.z = objA->trans.z;
                            objA->trans.z = temp;
                        }
                        if (objA->trans.z < objB->trans.z) {
                            entryA->unk_06 = 0;
                            entryB->unk_06 = 2;
                        } else {
                            entryA->unk_06 = 2;
                            entryB->unk_06 = 0;
                        }
                    } else if (objB->trans.z < objA->trans.z) {
                        entryA->unk_06 = 4;
                        entryA->unk_08 = -1;
                    } else if (objB->trans.z == objA->trans.z) {
                        if (objB->work[0] > objA->work[0]) {
                            entryA->unk_06 = 4;
                            entryA->unk_08 = -1;
                        } else if (entryA->unk_06 != 3) {
                            entryA->unk_06 = 0;
                            entryA->unk_08 = entryA->unk_0A;
                        }
                    } else if (objB->trans.z > objA->trans.z) {
                        if (entryA->unk_06 != 3) {
                            entryA->unk_06 = 0;
                            entryA->unk_08 = entryA->unk_0A;
                        }
                    }
                }
            }
        }
    }
}

void m243_ChrObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[5 + obj->work[0]];
    ThreeDoorMontyObjWork *doors[3];
    ThreeDoorMontyObjWork *other;
    omObjData *otherObj;
    s16 i;
    s16 busy;

    for (i = 0; i < 3; i++) {
        doors[i] = &m243_objWorkTbl[9 + i];
    }
    switch (m243_phase) {
        case 1:
            busy = 0;
            if (m243_timer >= 15) {
                for (i = 0; i < 3; i++) {
                    if (doors[i]->unk_04 != 5 && doors[i]->unk_04 != 6) {
                        doors[i]->unk_04 = 5;
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_06 != 1) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                if (obj->trans.z < -450.0f) {
                    m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                    obj->trans.z += m243_chrWalkSpeedTbl[obj->work[0]];
                }
                for (i = 0; i < 3; i++) {
                    other = &m243_objWorkTbl[5 + i];
                    otherObj = other->obj;
                    if (otherObj->trans.z < -450.0f) {
                        busy = 1;
                    } else {
                        m243_MotShiftSet(otherObj, 0, 0, 3, 2, &other->unk_04);
                    }
                }
                if (busy == 0) {
                    m243_phaseDoneNo = 1;
                }
            }
            break;
        case 3:
            m243_ChrShuffleUpdate(obj);
            m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
            if (obj->work[0] == 2) {
                if (obj->trans.z < -350.0f) {
                    m243_teresaFadeState = 2;
                }
                switch (m243_teresaFadeState) {
                    case 0:
                        if ((u8)(rand8() % 10) == 0) {
                            m243_teresaFadeState = 1;
                        }
                        break;
                    case 1:
                        m243_teresaAlpha -= 10;
                        if (m243_teresaAlpha <= 0) {
                            m243_teresaAlpha = 0;
                            if ((u8)(rand8() % 50) == 0) {
                                m243_teresaFadeState = 2;
                            }
                        }
                        break;
                    case 2:
                        m243_teresaAlpha += 10;
                        if (m243_teresaAlpha >= 255) {
                            m243_teresaFadeState = 0;
                            m243_teresaAlpha = 255;
                        }
                        break;
                }
                Hu3DModelTPLvlSet(obj->model[0], m243_teresaAlpha);
                Hu3DModelTPLvlSet(obj->model[1], m243_teresaAlpha);
            }
            busy = 0;
            for (i = 0; i < 3; i++) {
                other = &m243_objWorkTbl[5 + i];
                if (other->unk_06 != 5) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                m243_teresaAlpha = 255;
                Hu3DModelTPLvlSet(obj->model[0], m243_teresaAlpha);
                Hu3DModelTPLvlSet(obj->model[1], m243_teresaAlpha);
                for (i = 0; i < 3; i++) {
                    if (doors[i]->unk_04 != 0 && doors[i]->unk_04 != 1) {
                        doors[i]->unk_04 = 0;
                    }
                    m243_phaseDoneNo = 3;
                }
            }
            break;
        case 4:
            entry->unk_06 = 0;
            break;
        case 7:
            m243_revealF = 0;
            break;
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
            for (i = 0; i < 3; i++) {
                m243_doorChrTbl[i] = -1;
            }
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_04 != 5 && doors[i]->unk_04 != 6) {
                    doors[i]->unk_04 = 5;
                }
            }
            obj->rot.y = 0.0f;
            if (obj->work[0] == m243_targetChr) {
                switch (entry->unk_06) {
                    case 0:
                        if (doors[entry->unk_08]->unk_06 == 1) {
                            if (obj->trans.z > -600.0f && m243_revealState == 0) {
                                m243_revealState = 1;
                            }
                            if (obj->trans.z < -450.0f) {
                                m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                                obj->trans.z += m243_chrWalkSpeedTbl[obj->work[0]];
                            } else {
                                Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                entry->unk_18 = 20.0f;
                                entry->unk_06 = 1;
                            }
                        }
                        break;
                    case 1:
                        obj->trans.y = m243_GravityCalc(obj->trans.y, &entry->unk_18, 2.0f);
                        if (obj->trans.y < entry->unk_24) {
                            obj->trans.y = entry->unk_24;
                        }
                        if (obj->trans.y <= entry->unk_24) {
                            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                            m243_MotShiftSet(obj, 0, 0, 3, 2, &entry->unk_04);
                            entry->unk_06 = 2;
                        }
                        break;
                    case 2:
                        m243_revealF = 1;
                        if ((m243_phase == 10 || m243_phase == 11 ||
                             m243_phase == 12 || m243_phase == 13) &&
                            m243_hopF == 1) {
                            if (obj->trans.y <= entry->unk_24) {
                                m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                                Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                entry->unk_18 = 20.0f;
                            }
                            obj->trans.y = m243_GravityCalc(obj->trans.y, &entry->unk_18, 2.0f);
                            if (obj->trans.y < entry->unk_24) {
                                obj->trans.y = entry->unk_24;
                            }
                        }
                        break;
                }
            } else {
                other = &m243_objWorkTbl[5 + m243_targetChr];
                if (other->unk_06 == 2) {
                    switch (entry->unk_06) {
                        case 0:
                            if (doors[entry->unk_08]->unk_06 == 1) {
                                if (obj->trans.z < -450.0f) {
                                    m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                                    obj->trans.z += m243_chrWalkSpeedTbl[obj->work[0]];
                                } else {
                                    m243_MotShiftSet(obj, 0, 0, 3, 2, &entry->unk_04);
                                    entry->unk_06 = 1;
                                }
                            }
                            break;
                        case 1:
                            entry->unk_06 = 2;
                            break;
                        case 2:
                            if (m243_phase == 10 || m243_phase == 11 ||
                                m243_phase == 12 || m243_phase == 13) {
                                if (obj->trans.y <= entry->unk_24) {
                                    m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                                    Hu3DMotionSpeedSet(obj->model[0], 0.5f);
                                    entry->unk_18 = 20.0f;
                                }
                                obj->trans.y = m243_GravityCalc(obj->trans.y, &entry->unk_18, 2.0f);
                                if (obj->trans.y < entry->unk_24) {
                                    obj->trans.y = entry->unk_24;
                                }
                                m243_hopF = 1;
                            }
                            break;
                    }
                }
            }
            if (m243_phase == 8 && obj->work[0] == 2) {
                busy = 0;
                for (i = 0; i < 3; i++) {
                    other = &m243_objWorkTbl[5 + i];
                    if (other->unk_06 != 2) {
                        busy = 1;
                    }
                }
                if (busy == 0) {
                    for (i = 0; i < 3; i++) {
                        other = &m243_objWorkTbl[5 + i];
                        other->unk_06 = 0;
                        other->unk_08 = -1;
                    }
                    m243_phaseDoneNo = 8;
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    if (entry->unk_18 > 0.0f) {
        entry->unk_20 -= 0.02f;
    } else if (entry->unk_18 < 0.0f) {
        entry->unk_20 += 0.02f;
    }
    if (entry->unk_20 < 0.1f) {
        entry->unk_20 = 0.1f;
    } else if (entry->unk_20 > 1.0f) {
        entry->unk_20 = 1.0f;
    }
    Hu3DModelScaleSet(obj->model[1], entry->unk_20, obj->scale.y, entry->unk_20);
}

void m243_ChrObjInit(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[5 + obj->work[0]];

    switch (obj->work[0]) {
        case 0:
            obj->model[0] = Hu3DModelRead(0xA0000, 0x2A9);
            omObjMotionRead(obj, 0, m243_chrMotTbl[obj->work[0]][0] | 0xA0000);
            omObjMotionRead(obj, 1, m243_chrMotTbl[obj->work[0]][1] | 0xA0000);
            obj->trans.x = m243_doorPosTbl[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 10.0f;
            obj->trans.z = m243_doorPosTbl[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 1.0f;
            obj->scale.y = 1.0f;
            obj->scale.z = 1.0f;
            break;
        case 1:
            obj->model[0] = Hu3DModelRead(0xA008E, 0x2A9);
            omObjMotionRead(obj, 0, m243_chrMotTbl[obj->work[0]][0] | 0xA0000);
            omObjMotionRead(obj, 1, m243_chrMotTbl[obj->work[0]][1] | 0xA0000);
            obj->trans.x = m243_doorPosTbl[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 30.0f;
            obj->trans.z = m243_doorPosTbl[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 1.0f;
            obj->scale.y = 1.0f;
            obj->scale.z = 1.0f;
            break;
        case 2:
            obj->model[0] = Hu3DModelRead(0xA00C4, 0x2A9);
            omObjMotionRead(obj, 0, m243_chrMotTbl[obj->work[0]][0] | 0xA0000);
            omObjMotionRead(obj, 1, m243_chrMotTbl[obj->work[0]][1] | 0xA0000);
            obj->trans.x = m243_doorPosTbl[obj->work[0]].x;
            entry->unk_24 = obj->trans.y = 0.0f;
            obj->trans.z = m243_doorPosTbl[obj->work[0]].y - 300.0f;
            obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
            obj->scale.x = 0.52f;
            obj->scale.y = 0.52f;
            obj->scale.z = 0.52f;
            m243_teresaAlpha = 0xFF;
            Hu3DModelTPLvlInit(obj->model[0]);
            Hu3DModelTPLvlSet(obj->model[0], m243_teresaAlphaLo);
            break;
    }
    obj->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 15.0f, 0.0f);
    if (obj->work[0] == 2) {
        Hu3DModelTPLvlInit(obj->model[1]);
        Hu3DModelTPLvlSet(obj->model[1], m243_teresaAlphaLo);
    } else {
        Hu3DModelRemakeStatic(obj->model[1]);
        Hu3DModelDynamicFree(obj->model[1]);
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    entry->unk_20 = 1.0f;
    Hu3DModelScaleSet(obj->model[1], entry->unk_20, obj->scale.y, entry->unk_20);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    entry->unk_08 = -1;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM1);
    obj->func = m243_ChrObjMain;
}

void m243_ChrObjCreateAll(void) {
    ThreeDoorMontyObjWork *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &m243_objWorkTbl[5 + i];
        obj = omAddObj(0x96, 5, 0xA, -1, m243_ChrObjInit);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m243_SignObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[8];
    ThreeDoorMontyObjWork *doors[3];
    s16 i;
    s16 busy;

    for (i = 0; i < 3; i++) {
        doors[i] = &m243_objWorkTbl[9 + i];
    }
    switch (m243_phase) {
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            busy = 0;
            for (i = 0; i < 3; i++) {
                if (doors[i]->unk_06 != 1) {
                    busy = 1;
                }
            }
            if (busy == 0) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                entry->unk_18 += 0.1f;
                if (entry->unk_18 > 1.0f) {
                    entry->unk_18 = 1.0f;
                    m243_targetChr = (u8)(rand8() % 3);
                    m243_SignAnimSet(obj, m243_targetChr);
                    m243_phaseDoneNo = 4;
                    HuAudFXPlay(0x453);
                    m243_signSeStep = 0;
                }
            }
            break;
        case 5:
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            if (Hu3DData[obj->model[0]].motTime >= 60.0f && m243_signSeStep == 0) {
                HuAudFXPlay(0x453);
                m243_signSeStep = 1;
            }
            if (Hu3DData[obj->model[0]].motTime >= 120.0f && m243_signSeStep == 1) {
                HuAudFXPlay(0x453);
                m243_signSeStep = 2;
            }
            if (Hu3DData[obj->model[0]].motTime >= 180.0f && m243_signSeStep == 2) {
                switch (m243_targetChr) {
                    case 0:
                        HuAudFXPlay(0x455);
                        break;
                    case 1:
                        HuAudFXPlay(0x457);
                        break;
                    case 2:
                        HuAudFXPlay(0x456);
                        break;
                }
                m243_signSeStep = 3;
            }
            if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                m243_phaseDoneNo = 5;
            }
            break;
        case 6:
        case 7:
        case 9:
        case 12:
            break;
        case 8:
        case 10:
        case 11:
        case 13:
            if (entry->unk_18 > 0.1f) {
                entry->unk_18 -= 0.1f;
            } else {
                entry->unk_18 = 0.1f;
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionSpeedSet(obj->model[0], 0.0f);
            }
            break;
    }
    obj->scale.x = obj->scale.y = entry->unk_18;
}

void m243_SignObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x4C000E, 0x2A9);
    m243_signAnimDataTbl[0] = DataRead(0x4C0000);
    m243_signAnimDataTbl[1] = DataRead(0x4C0001);
    m243_signAnimDataTbl[2] = DataRead(0x4C0002);
    m243_signAnim =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m243_signAnimDataTbl[0], 0, m243_signTexName);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 450.0f;
    obj->trans.z = 0.0f;
    obj->scale.x = m243_signScale = 0.1f;
    obj->scale.y = m243_objWorkTbl[8].unk_18;
    obj->scale.z = 1.0f;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    obj->func = m243_SignObjMain;
}

void m243_SignObjCreate(void) {
    omObjData *obj = omAddObj(0xC8, 5, 0xA, -1, m243_SignObjInit);
    obj->work[0] = 0;
    m243_signObj = obj;
}

void m243_DoorObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[9 + obj->work[0]];

    switch (entry->unk_04) {
        case 0:
            entry->unk_04 = 1;
            HuAudFXPlay(0x452);
            break;
        case 1:
            if (obj->trans.y > 0.0f) {
                obj->trans.y -= 15.0f;
            }
            if (obj->trans.y < 0.0f) {
                obj->trans.y = 0.0f;
                entry->unk_06 = 0;
            }
            break;
        case 5:
            entry->unk_04 = 6;
            HuAudFXPlay(0x451);
            break;
        case 6:
            if (obj->trans.y < 185.0f) {
                obj->trans.y += 10.0f;
            }
            if (obj->trans.y > 185.0f) {
                obj->trans.y = 185.0f;
                entry->unk_06 = 1;
            }
            break;
    }
}

void m243_DoorObjInit(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[9 + obj->work[0]];

    switch (obj->work[0]) {
        case 0:
            obj->model[0] = Hu3DModelRead(0x4C000C, 0x2B9);
            break;
        case 1:
            obj->model[0] = Hu3DModelRead(0x4C000B, 0x2B9);
            break;
        case 2:
            obj->model[0] = Hu3DModelRead(0x4C000A, 0x2B9);
            break;
    }
    obj->trans.x = m243_doorPosTbl[obj->work[0]].x;
    obj->trans.y = 0.0f;
    obj->trans.z = m243_doorPosTbl[obj->work[0]].y;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = 1.0f;
    obj->scale.y = 1.0f;
    obj->scale.z = 1.0f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM1);
    entry->unk_04 = 1;
    obj->func = m243_DoorObjMain;
}

void m243_DoorObjCreateAll(void) {
    ThreeDoorMontyObjWork *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 3; i++) {
        entry = &m243_objWorkTbl[9 + i];
        obj = omAddObj(0xFA, 5, 0xA, -1, m243_DoorObjInit);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

f32 m243_RandCalc(s16 mode, f32 value) {
    f32 result = 0.0f;

    switch (mode) {
        case 1:
            result = rand8() + value;
            break;
        case 2:
            result = rand8() - value;
            break;
        case 3:
            result = rand8() * value;
            break;
        case 4:
            result = rand8() / (s16)value;
            break;
        case 5:
            result = rand8() % (s16)value;
            break;
        case 6:
            if (rand8() % (s16)value == 0) {
                result = 1.0f;
            }
            break;
        case 0:
        default:
            result = rand8();
            break;
    }
    return result;
}

void m243_PlayerComInput(omObjData *obj) {
    s16 choice = 0;
    s16 act = 0;
    s16 door = 0;
    s16 i;

    for (i = 0; i < 3; i++) {
        if (m243_doorChrTbl[i] == m243_targetChr) {
            door = i;
        }
    }
    switch (GwPlayer[obj->work[0]].cpu_difficulty) {
        case 0:
            act = m243_RandCalc(6, 50.0f);
            choice = m243_RandCalc(5, 10.0f);
            break;
        case 1:
            act = m243_RandCalc(6, 30.0f);
            choice = m243_RandCalc(5, 15.0f);
            break;
        case 2:
            act = m243_RandCalc(6, 15.0f);
            choice = m243_RandCalc(5, 20.0f);
            break;
        case 3:
            act = m243_RandCalc(6, 10.0f);
            choice = m243_RandCalc(5, 25.0f);
            break;
    }
    if (m243_answerTime >= 4957) {
        act = 1;
    }
    if (act != 0) {
        switch (choice) {
            case 0:
                HuPadBtnDown[obj->work[3]] |= Z_TRIG;
                break;
            case 1:
                HuPadBtnDown[obj->work[3]] |= B_BUTTON;
                break;
            case 2:
                HuPadBtnDown[obj->work[3]] |= A_BUTTON;
                break;
            default:
                if (door == 0) {
                    HuPadBtnDown[obj->work[3]] |= Z_TRIG;
                } else if (door == 1) {
                    HuPadBtnDown[obj->work[3]] |= B_BUTTON;
                } else if (door == 2) {
                    HuPadBtnDown[obj->work[3]] |= A_BUTTON;
                }
                break;
        }
    }
}

void m243_PlayerAnswerInput(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[1 + obj->work[0]];

    if (entry->unk_14 == 0) {
        return;
    }
    if (GwPlayer[obj->work[0]].stat & 1) {
        m243_PadClear(obj->work[0]);
        if (m243_answerTime >= 165) {
            m243_PlayerComInput(obj);
        }
    }
    if (entry->unk_06 != -1) {
        return;
    }
    if (HuPadBtnDown[obj->work[3]] & A_BUTTON) {
        if (m243_answerTime >= 34) {
            entry->unk_12 = m243_answerTime - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = m243_answerTime;
        }
        m243_MotShiftSet(obj, 4, 0, 3, 0, &entry->unk_04);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        entry->unk_06 = 2;
    }
    if (HuPadBtnDown[obj->work[3]] & B_BUTTON) {
        if (m243_answerTime >= 34) {
            entry->unk_12 = m243_answerTime - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = m243_answerTime;
        }
        m243_MotShiftSet(obj, 4, 0, 3, 0, &entry->unk_04);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        entry->unk_06 = 1;
    }
    if (HuPadBtnDown[obj->work[3]] & Z_TRIG) {
        if (m243_answerTime >= 34) {
            entry->unk_12 = m243_answerTime - (u8)(rand8() % 3) * 10;
        } else {
            entry->unk_12 = m243_answerTime;
        }
        m243_MotShiftSet(obj, 4, 0, 3, 0, &entry->unk_04);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        entry->unk_06 = 0;
    }
}

void m243_RankCalc(void) {
    ThreeDoorMontyObjWork *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 j;
    s16 found;
    f32 best;

    for (i = 0; i < 4; i++) {
        entries[i] = &m243_objWorkTbl[1 + i];
        // objs is never read in this function; pointer form avoids a
        // set-but-unused warning without changing codegen.
        *(objs + i) = entries[i]->obj;
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_14 == 1 && entries[i]->unk_06 == -1) {
            entries[i]->unk_16 = m243_rankNo;
            entries[i]->unk_14 = 0;
            entries[i]->unk_08 = 1;
            m243_doneCnt++;
            found = 1;
        }
        if (entries[i]->unk_14 == 1 &&
            m243_doorChrTbl[entries[i]->unk_06] != m243_targetChr) {
            entries[i]->unk_16 = m243_rankNo;
            entries[i]->unk_14 = 0;
            entries[i]->unk_08 = 2;
            m243_doneCnt++;
            found = 1;
        }
    }
    if (found == 1) {
        m243_rankNo--;
    }
    if (m243_doneCnt < 3) {
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1) {
                    best = -100.0f;
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1 && best <= (s16)(entries[i]->unk_12 / 10)) {
                    best = (s16)(entries[i]->unk_12 / 10);
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_14 == 1 && (s16)(entries[i]->unk_12 / 10) == best) {
                    entries[i]->unk_16 = m243_rankNo;
                    entries[i]->unk_14 = 0;
                    entries[i]->unk_08 = 3;
                    m243_doneCnt++;
                }
            }
            m243_rankNo--;
        }
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_08 == 3 && (s16)(entries[i]->unk_12 / 10) == best) {
                entries[i]->unk_14 = 1;
                entries[i]->unk_08 = 0;
                m243_doneCnt--;
            }
        }
    }
}

void m243_PlayerObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[1 + obj->work[0]];
    ThreeDoorMontyObjWork *other;
    s16 i;
    s16 found;

    switch (m243_phase) {
        case 1:
        case 2:
            break;
        case 3:
            if (obj->rot.y >= 0.0f && obj->rot.y < 180.0f) {
                obj->rot.y = m243_AngleAdd(obj->rot.y, 9.0f);
                m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
            } else {
                obj->rot.y = 180.0f;
                m243_MotShiftSet(obj, 2, 0, 3, 2, &entry->unk_04);
            }
            break;
        case 4:
        case 5:
            if (obj->rot.y > 0.0f && obj->rot.y < 270.0f) {
                obj->rot.y = m243_AngleAdd(obj->rot.y, -9.0f);
                m243_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
            } else {
                obj->rot.y = 0.0f;
                m243_MotShiftSet(obj, 3, 0, 20, 2, &entry->unk_04);
            }
            entry->unk_06 = -1;
            break;
        case 6:
            if (m243_answerTime >= 33 && m243_answerTime <= 4957) {
                m243_PlayerAnswerInput(obj);
            }
            if (obj->work[0] == 3) {
                found = FALSE;
                for (i = 0; i < 4; i++) {
                    other = &m243_objWorkTbl[1 + i];
                    if (other->unk_14 == 1 && other->unk_06 == -1) {
                        found = TRUE;
                    }
                }
                if (!found) {
                    m243_allAnsweredF = 1;
                }
            }
            break;
        case 7:
            if (obj->work[0] == 3) {
                m243_RankCalc();
                m243_phaseDoneNo = 7;
                m243_answerCnt = 0;
                for (i = 0; i < 4; i++) {
                    other = &m243_objWorkTbl[1 + i];
                    if (other->unk_08 == 1 || other->unk_08 == 2 || other->unk_08 == 3) {
                        m243_answerCnt++;
                    }
                }
                if (m243_answerCnt >= 4) {
                    for (i = 0; i < 4; i++) {
                        other = &m243_objWorkTbl[1 + i];
                        other->unk_16 = 99;
                    }
                }
            }
            break;
        case 8:
        case 9:
            if (m243_doneCnt < 3) {
                if (entry->unk_14 == 0) {
                    switch (entry->unk_08) {
                        case 1:
                        case 2:
                            if (m243_revealState >= 2) {
                                for (i = 0; i < 3; i++) {
                                    Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                }
                                m243_MotSet(obj, 6, 2, 0, &entry->unk_04);
                                if (m243_reactFTbl[obj->work[0]] == 0) {
                                    PlayerFXPlay(0x286, obj->work[0]);
                                    m243_reactFTbl[obj->work[0]] = 1;
                                }
                                if (entry->unk_04 == 6) {
                                    if (Hu3DData[obj->model[0]].motTime >=
                                        Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                                        entry->unk_08 = 10;
                                    }
                                }
                            }
                            break;
                        case 3:
                            if (m243_revealState >= 2) {
                                for (i = 0; i < 3; i++) {
                                    Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                }
                                m243_MotSet(obj, 6, 2, 0, &entry->unk_04);
                                if (m243_reactFTbl[obj->work[0]] == 0) {
                                    PlayerFXPlay(0x286, obj->work[0]);
                                    m243_reactFTbl[obj->work[0]] = 1;
                                }
                                if (entry->unk_04 == 6) {
                                    if (Hu3DData[obj->model[0]].motTime >=
                                        Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                                        entry->unk_08 = 10;
                                    }
                                }
                            }
                            break;
                        case 10:
                            m243_MotShiftSet(obj, 1, 0, 30, 2, &entry->unk_04);
                            if (obj->trans.z < 500.0f) {
                                obj->trans.z += 10.0f;
                                obj->trans.y -= 3.0f;
                            } else {
                                obj->trans.z = 500.0f;
                                entry->unk_08 = 50;
                            }
                            break;
                        case 50:
                            break;
                    }
                }
                if (m243_phase == 9) {
                    if (obj->work[0] == 3) {
                        found = FALSE;
                        for (i = 0; i < 4; i++) {
                            other = &m243_objWorkTbl[1 + i];
                            if (other->unk_14 == 0 && other->unk_08 != 50) {
                                found = TRUE;
                            }
                        }
                        if (!found) {
                            m243_phaseDoneNo = 9;
                        }
                    }
                }
            }
            break;
        case 10:
        case 11:
            break;
        case 12:
            if (entry->unk_14 != 0) {
                if (m243_revealState >= 2) {
                    for (i = 0; i < 3; i++) {
                        Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    m243_MotShiftSet(obj, 5, 0, 30, 0, &entry->unk_04);
                    if (m243_reactFTbl[obj->work[0]] == 0) {
                        HuAudCharVoicePlay((m243_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
                        m243_reactFTbl[obj->work[0]] = 1;
                    }
                }
            }
            if (entry->unk_14 == 0) {
                switch (entry->unk_08) {
                    case 1:
                    case 2:
                        if (m243_revealState >= 2) {
                            for (i = 0; i < 3; i++) {
                                Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            }
                            m243_MotSet(obj, 6, 2, 0, &entry->unk_04);
                            if (m243_doneCnt >= 4) {
                                if (m243_reactFTbl[obj->work[0]] == 0) {
                                    m243_reactFTbl[obj->work[0]] = 1;
                                }
                            }
                            if (entry->unk_04 == 6) {
                                if (Hu3DData[obj->model[0]].motTime >=
                                    Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                                    entry->unk_08 = 10;
                                }
                            }
                        }
                        break;
                    case 3:
                        if (m243_revealState >= 2) {
                            for (i = 0; i < 3; i++) {
                                Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            }
                            m243_MotSet(obj, 6, 2, 0, &entry->unk_04);
                            if (m243_doneCnt >= 4) {
                                if (m243_reactFTbl[obj->work[0]] == 0) {
                                    HuAudCharVoicePlay(
                                        (m243_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x36);
                                    m243_reactFTbl[obj->work[0]] = 1;
                                }
                            }
                            if (entry->unk_04 == 6) {
                                if (Hu3DData[obj->model[0]].motTime >=
                                    Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                                    entry->unk_08 = 10;
                                }
                            }
                        }
                        break;
                    case 10:
                        break;
                    case 50:
                        break;
                }
            }
            break;
    }
    if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z - 20.0f);
    }
}

void m243_PlayerObjInit(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[1 + obj->work[0]];
    s8 chr = GwPlayer[obj->work[0]].chr;
    s16 i;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][3], 0x2A9);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x6C));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x66));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x8A));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x36));
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    entry->unk_04 = 0;
    obj->model[1] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    switch (obj->work[1]) {
        case 0:
            obj->trans.x = -325.0f;
            break;
        case 1:
            obj->trans.x = -110.0f;
            break;
        case 2:
            obj->trans.x = 110.0f;
            break;
        case 3:
            obj->trans.x = 325.0f;
            break;
    }
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    if (chr != 5) {
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z + 30.0f);
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    for (i = 0; i < 3; i++) {
        obj->model[2 + i] = Hu3DModelRead(m243_answerMdlTbl[i] | 0x4C0000, 0xA9);
        Hu3DModelHookSet(obj->model[2 + i], obj->model[0], "item_hook");
        Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_HOOK, HU3D_ATTR_HOOK);
        if (i == 0) {
            Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        } else {
            Hu3DModelAttrSet(obj->model[2 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM2);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM2);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM2);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM2);
    Hu3DModelCameraSet(obj->model[4], HU3D_CAM2);
    entry->unk_14 = 1;
    obj->func = m243_PlayerObjMain;
}

void m243_PlayerObjCreateAll(void) {
    ThreeDoorMontyObjWork *entry;
    omObjData *obj;
    s16 order[4];
    s16 i;
    s16 j;
    s16 idx;
    u16 player;

    for (i = 0; i < 4; i++) {
        order[i] = i;
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
            default:
                player = 0;
                break;
        }
        entry = &m243_objWorkTbl[1 + i];
        obj = omAddObj(100, 10, 60, -1, m243_PlayerObjInit);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        entry->obj = obj;
        idx = rand8() % (4 - i);
        obj->work[1] = order[idx];
        order[idx] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void m243_DigitObjMain(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[obj->work[0] * 4 + 13 + obj->work[1]];
    ThreeDoorMontyObjWork *entries[4];
    omObjData *objs[4];
    s16 count;
    u8 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &m243_objWorkTbl[1 + i];
        // objs is never read in this function; pointer form avoids a
        // set-but-unused warning without changing codegen.
        *(objs + i) = entries[i]->obj;
    }
    switch (m243_phase) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            espDispOff(entry->unk_40[1]);
            break;
        case 7:
            espDispOff(entry->unk_40[1]);
            if (obj->work[1] != 1) {
                entry->unk_04 = (u8)(rand8() % 10);
            }
            m243_digitSeState = 0;
            break;
        case 8:
        case 10:
        case 11:
        case 13:
            count = 0;
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_08 == 0 || entries[i]->unk_08 == 3) {
                    count++;
                }
            }
            if (count >= 2) {
                if ((entries[obj->work[0]]->unk_08 == 0 || entries[obj->work[0]]->unk_08 == 3) &&
                    m243_revealState > 0) {
                    espDispOn(entry->unk_40[1]);
                    if (m243_digitSeState == 0) {
                        m243_digitSeNo = HuAudFXPlay(0x454);
                        m243_digitSeState = 1;
                    }
                    if (obj->work[1] == 1) {
                        // The do-while(0) raises entry's loop-weighted ref count so it
                        // outranks obj in register allocation (entry in s0, obj in s1).
                        do {
                            entry->unk_04 = 11;
                        } while (0);
                        espPatNoSet(entry->unk_40[1], 11);
                    } else {
                        entry->unk_04++;
                        if (entry->unk_04 >= 10) {
                            entry->unk_04 = 0;
                        }
                        switch (obj->work[1]) {
                            case 0:
                                if (m243_timer < 50) {
                                    entry->unk_04 = entries[obj->work[0]]->unk_12 / 1000;
                                }
                                break;
                            case 2:
                                if (m243_timer < 40) {
                                    entry->unk_04 = (s16)(entries[obj->work[0]]->unk_12 / 100) % 10;
                                }
                                break;
                            case 3:
                                if (m243_timer < 30) {
                                    entry->unk_04 = (s16)(entries[obj->work[0]]->unk_12 / 10) % 10;
                                    if (m243_digitSeState == 1) {
                                        HuAudFXStop(m243_digitSeNo);
                                        m243_digitSeState = 2;
                                    }
                                    if (m243_revealState == 1) {
                                        m243_revealState = 2;
                                    }
                                }
                                break;
                        }
                        espPatNoSet(entry->unk_40[1], entry->unk_04);
                    }
                }
            } else if (m243_revealState == 1) {
                m243_revealState = 2;
            }
            break;
    }
}

void m243_DigitObjInit(omObjData *obj) {
    ThreeDoorMontyObjWork *entry = &m243_objWorkTbl[obj->work[0] * 4 + 13 + obj->work[1]];
    ThreeDoorMontyObjWork *entries[4];
    omObjData *objs[4];
    u8 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &m243_objWorkTbl[1 + i];
        objs[i] = entries[i]->obj;
    }
    entry->unk_40[0] = HuSprAnimDataRead(0x31);
    entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
    if (obj->work[1] == 1) {
        entry->unk_04 = 11;
        espPatNoSet(entry->unk_40[1], 11);
    } else {
        entry->unk_04 = (u8)(rand8() % 10);
        espPatNoSet(entry->unk_40[1], entry->unk_04);
    }
    espPosSet(entry->unk_40[1], m243_digitXTbl[(s16)objs[obj->work[0]]->work[1]][obj->work[1]], 140);
    espDispOff(entry->unk_40[1]);
    obj->func = m243_DigitObjMain;
}

void m243_DigitObjCreateAll(void) {
    ThreeDoorMontyObjWork *entry;
    omObjData *obj;
    u8 i;
    u8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            entry = &m243_objWorkTbl[i * 4 + 13 + j];
            obj = omAddObj(0x12C, 1, 0xA, -1, m243_DigitObjInit);
            obj->work[0] = i;
            obj->work[1] = j;
            entry->obj = obj;
        }
    }
}

void m243_ResultSet(void) {
    ThreeDoorMontyObjWork *entries[4];
    omObjData *objs[4];
    s16 best[4];
    s16 rank[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        best[i] = 4;
        rank[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        entries[i] = &m243_objWorkTbl[1 + i];
        objs[i] = entries[i]->obj;
        if (best[0] > entries[i]->unk_16) {
            best[0] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[0] < entries[i]->unk_16 && entries[i]->unk_16 < best[1]) {
            best[1] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[1] < entries[i]->unk_16 && entries[i]->unk_16 < best[2]) {
            best[2] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[2] < entries[i]->unk_16 && entries[i]->unk_16 < best[3]) {
            best[3] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (best[0] == entries[i]->unk_16) {
            rank[i] = 0;
        }
        if (best[1] == entries[i]->unk_16) {
            rank[i] = 1;
        }
        if (best[2] == entries[i]->unk_16) {
            rank[i] = 2;
        }
        if (best[3] == entries[i]->unk_16) {
            rank[i] = 3;
        }
    }
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_16 == 99) {
            rank[i] = 3;
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[objs[i]->work[0]].bonusCoin = rank[i];
    }
}

void m243_CameraViewInit(void) {
    u32 i;

    if (m243_cameraSetF == 0) {
        m243_cameraSetF = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 1641.4171f;
            CRotM[i].x = 322.53763f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 150.0f;
            CenterM[i].z = -290.0f;
        }
        CZoomM[2] = 1641.4171f;
        CRotM[2].x = 342.44815f;
        CRotM[2].y = 0.0f;
        CRotM[2].z = 0.0f;
        CenterM[2].x = 0.0f;
        CenterM[2].y = 240.0f;
        CenterM[2].z = -220.0f;
    }
}

void m243_ExitObjMain(omObjData *obj) {
    s16 i;

    for (i = 0; i < 3; i++) {
        DataClose(m243_signAnimDataTbl[i]);
    }
    Hu3DAnimKill(m243_signAnim);
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m243_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m243_ExitObjMain;
    }
}

void m243_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m243_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m243_MainObjMain(omObjData *obj) {
    switch (m243_phase) {
        case 0:
            m243_PhaseSet(1);
            break;
        case 1:
            if (m243_phaseDoneNo == 1) {
                m243_PhaseSet(2);
                m243_timer = 0;
            } else if (++m243_timer > 50) {
                m243_timer = 50;
            }
            break;
        case 2:
            if (m243_timer == 0) {
                GMesCreate(GMES_MES_7);
                m243_timer++;
            } else if (m243_timer >= 63) {
                HuAudSeqPlay(0x31);
            } else {
                m243_timer++;
            }
            if (GMesStatGet() == 0) {
                m243_PhaseSet(3);
                m243_timer = 0;
            }
            break;
        case 3:
            if (m243_phaseDoneNo == 3) {
                m243_PhaseSet(4);
                m243_revealState = 0;
                omSysPauseDisableF = 1;
            } else {
                m243_timer++;
            }
            break;
        case 4:
            if (m243_phaseDoneNo == 4) {
                m243_PhaseSet(5);
                m243_timer = 0;
            }
            break;
        case 5:
            if (m243_phaseDoneNo == 5) {
                m243_PhaseSet(6);
                m243_timer = 151;
                GMesCreate(GMES_MES_TIMER, 5, 160, 28);
            }
            break;
        case 6:
            if (m243_timer <= 0 || m243_allAnsweredF == 1) {
                m243_answerTime = 0;
                m243_allAnsweredF = 0;
                GMesTimerEnd();
                m243_PhaseSet(7);
                omSysPauseDisableF = 0;
            } else {
                m243_timer--;
                m243_answerTime += 33;
                if (m243_answerTime % 1000 == 990) {
                    m243_answerTime += 10;
                }
            }
            GMesTimerValueSet((m243_timer + 29) / 30);
            break;
        case 7:
            if (m243_phaseDoneNo == 7) {
                m243_PhaseSet(10);
                m243_timer = 150;
                if (m243_doneCnt == 4) {
                    m243_PhaseSet(11);
                }
            }
            break;
        case 8:
        case 9:
            break;
        case 10:
            if (m243_revealState == 2) {
                GMesCreate(GMES_MES_18);
                HuAudSeqFadeOut(120);
                m243_revealState = 3;
            }
            if (m243_revealState == 3 && GMesStatGet() == 0) {
                if (m243_resultWait >= 0) {
                    m243_timer = 99;
                    m243_PhaseSet(12);
                }
                m243_resultWait++;
            }
            if (m243_timer > 0) {
                m243_timer--;
            } else {
                m243_timer = 0;
            }
            break;
        case 11:
            if (m243_revealState == 2) {
                GMesCreate(GMES_MES_18);
                HuAudSeqFadeOut(120);
                m243_revealState = 3;
            }
            if (m243_revealState == 3 && GMesStatGet() == 0) {
                if (m243_resultWait >= 0) {
                    m243_timer = 144;
                    m243_PhaseSet(12);
                }
                m243_resultWait++;
            }
            break;
        case 12:
            if (m243_doneCnt == 4) {
                if (m243_timer == 144) {
                    HuAudSeqPlay(0x6C);
                }
            } else {
                if (m243_timer == 98) {
                    HuAudSeqPlay(0x65);
                }
            }
            if (m243_timer > 0) {
                m243_timer--;
            } else {
                m243_timer = 0;
                m243_PhaseSet(13);
            }
            break;
        case 13:
            if (m243_timer == 0) {
                m243_ResultSet();
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                obj->func = m243_ExitWaitObjMain;
                m243_timer++;
            }
            break;
    }
}

void m243_MainObjInit(omObjData *obj) {
    s16 i;

    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m243_BackObjCreate();
    m243_ChrObjCreateAll();
    m243_SignObjCreate();
    m243_DoorObjCreateAll();
    m243_PlayerObjCreateAll();
    m243_WaterObjCreate();
    m243_DigitObjCreateAll();
    m243_CameraViewInit();
    m243_timer = 0;
    m243_phase = 0;
    m243_phaseDoneNo = 0;
    m243_answerTime = 0;
    m243_revealF = 0;
    m243_targetChr = -1;
    m243_rankNo = 3;
    m243_revealState = 0;
    m243_doneCnt = 0;
    m243_teresaFadeState = 0;
    m243_teresaAlpha = 0;
    for (i = 0; i < 3; i++) {
        m243_doorChrTbl[i] = -1;
    }
    m243_hopF = 0;
    m243_allAnsweredF = 0;
    for (i = 0; i < 4; i++) {
        m243_reactFTbl[i] = 0;
    }
    m243_answerCnt = 0;
    m243_digitSeState = 0;
    m243_signSeStep = 0;
    m243_resultWait = -15;
    obj->func = m243_MainObjMain;
}

void m243_Dummy(void) {
}

void m243_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 3;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(3);
    CamSetupMapCullAddMulti(3);
    for (i = 0; i < 3; i++) {
        ScissorSet(i, m243_cameraViewTbl[i].scissorX, m243_cameraViewTbl[i].scissorY,
                   m243_cameraViewTbl[i].scissorWidth, m243_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m243_cameraViewTbl[i].viewportScale.x, m243_cameraViewTbl[i].viewportScale.y,
                    m243_cameraViewTbl[i].viewportScale.z, m243_cameraViewTbl[i].viewportTranslate.x,
                    m243_cameraViewTbl[i].viewportTranslate.y,
                    m243_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m243_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m243_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(60, 0);
    omGameSysInit();
    m243_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m243_fontMesTbl, 0);
    GMesFontMesCreate(m243_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m243_MainObjInit);
    omAddObj(1000, 0, 0, -1, m243_ExitCheckObjMain);
    m243_ObjWorkInit();
}

const s16 m243_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
