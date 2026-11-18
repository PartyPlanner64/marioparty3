#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

// One entry of the 50 entry object table at m246_objWorkTbl. Layout derived
// from the table clear in m246_ObjWorkInit, which walks 50 entries of 0x84
// bytes.
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
} SlapdownObjWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} SlapdownCamera; // sizeof 0x2C

// Sound handles; m246_knockSeTbl is misaligned for a standalone array.
typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06[5];
} SlapdownStateWork; // sizeof 0x10

extern s32 omCharModelNoTbl[][6];

s32 m246_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
f32 m246_playerPosXTbl[4] = { -380.0f, 380.0f, 380.0f, -380.0f };
f32 m246_playerPosZTbl[4] = { -380.0f, -380.0f, 380.0f, 380.0f };
f32 m246_playerPosXAltTbl[4] = { -390.0f, 390.0f, 390.0f, -390.0f };
f32 m246_playerPosZAltTbl[4] = { -390.0f, -390.0f, 390.0f, 390.0f };
f32 m246_buttonPosXTbl[4] = { -400.0f, 400.0f, 400.0f, -400.0f };
f32 m246_buttonPosZTbl[4] = { -400.0f, -400.0f, 400.0f, 400.0f };
f32 m246_playerRotTbl[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
f32 m246_paddleRotTbl[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
s32 m246_paddleAnimFileTbl[4][2] = { { 0, 0x4F0007 }, { 0, 0x4F0008 }, { 0, 0x4F0009 }, { 0, 0x4F000A } };
s16 m246_comSlapRateTbl[4][2] = { { 60, 450 }, { 45, 470 }, { 30, 480 }, { 25, 500 } };
Vec2f m246_knockVelBigTbl[4] = { { -6.5f, -6.5f }, { 6.5f, -6.5f }, { 3.5f, 3.5f }, { -3.5f, 3.5f } }; /* Unreferenced. */
Vec2f m246_knockVelBigAltTbl[4] = { { -4.5f, -4.5f }, { 4.5f, -4.5f }, { 1.5f, 1.5f }, { -1.5f, 1.5f } }; /* Unreferenced. */
Vec2f m246_knockVelTbl[4] = { { -1.08f, -1.08f }, { 1.08f, -1.08f }, { 1.75f, 1.75f }, { -1.75f, 1.75f } };
Vec2f m246_knockVelAltTbl[4] = { { -0.75f, -0.75f }, { 0.75f, -0.75f }, { 0.75f, 0.75f }, { -0.75f, 0.75f } };
f32 m246_cardPosXTbl[9] = { -65.0f, 65.0f, 190.0f, 190.0f, 130.0f, 0.0f, -130.0f, -190.0f, -190.0f };
f32 m246_cardPosZTbl[9] = { -190.0f, -190.0f, 65.0f, -65.0f, 190.0f, 190.0f, 190.0f, 65.0f, -65.0f };
Vec2f m246_rankFramePosTbl[4] = { { 50.0f, 92.0f }, { 271.0f, 92.0f }, { 239.0f, 155.0f }, { 81.0f, 155.0f } };
Vec2f m246_rankDigitPosTbl[4] = { { 49.0f, 92.0f }, { 272.0f, 92.0f }, { 238.0f, 155.0f }, { 82.0f, 155.0f } };
s32 m246_rankSprFileTbl[4] = { 0x4F000D, 0x4F000E, 0x4F000F, 0x4F0010 };
s32 m246_cameraSetF = 0;
SlapdownCamera m246_cameraViewTbl[1] = {
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 33.0f }
};

extern const s16 m246_fontMesTbl[];

SlapdownStateWork m246_stateWork BSS;
extern s16 m246_slapPendingF;    // m246_stateWork.unk_00
extern s16 m246_targetAnim;    // m246_stateWork.unk_02
extern s16 m246_spinSeNo;    // m246_stateWork.unk_04
extern s16 m246_knockSeTbl[5]; // m246_stateWork.unk_06
void *m246_paddleAnimDataTbl[4] BSS;
s16 m246_matchF BSS;
s16 m246_resultReadyF BSS;
u8 m246_resultReadyFPad[4] BSS; /* Unreferenced. */
s16 m246_cardAnimTbl[10] BSS;
f32 m246_cardSpinAngle BSS;
u8 m246_phaseDoneNo BSS;
s16 m246_spareAnim BSS;
u8 m246_spareAnimPad[4] BSS; /* Unreferenced. */
void *m246_targetAnimDataTbl[5] BSS;
s16 m246_unusedCntA BSS;
u8 m246_phase BSS;
s16 m246_unusedCntB BSS;
s16 m246_targetType BSS;
s16 m246_timer BSS;
s16 m246_spinSeState BSS;
void *m246_cardAnimDataTbl[6] BSS;
s16 m246_paddleAnimTbl[4] BSS;
s16 m246_slapOrderNo BSS;
s16 m246_firstFlipF BSS;
void *m246_spareAnimData BSS;
s16 m246_missCnt BSS;
u8 m246_missCntPad[0xC] BSS; /* Unreferenced. */
SlapdownObjWork m246_objWorkTbl[50] BSS;
// Fields of the first entry of m246_objWorkTbl are accessed through these
// separate symbols.
extern s16 m246_backSprAnim; // [0].unk_40[0]
extern s16 m246_backSprNo; // [0].unk_40[1]
extern f32 m246_backSprX; // [0].unk_44.x
extern f32 m246_backSprY; // [0].unk_44.y

void m246_BackObjMain(omObjData *obj);
void m246_RankObjInit(omObjData *obj);
void m246_BackObjInit(omObjData *);
void m246_PlayerObjMain(omObjData *obj);
void m246_TargetObjInit(omObjData *);
void m246_PlayerObjCreateAll(void);
void m246_CardObjInit(omObjData *obj);
void m246_PlayerObjInit(omObjData *obj);
void m246_CardObjMain(omObjData *obj);
void m246_CardObjCreateAll(void);
void m246_RankCalc(void);
void m246_ResultSet(void);
void m246_MainObjMain(omObjData *obj);
void m246_MainObjInit(omObjData *obj);
void m246_CameraInit(void);
void m246_ObjectSetup(void);

void m246_Executor(void) {
    m246_ObjectSetup();
}

f32 m246_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m246_RandMulGet(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void m246_ObjWorkInit(void) {
    SlapdownObjWork *entry;
    u32 i;

    for (i = 0, entry = m246_objWorkTbl; i < 50; i++, entry++) {
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

void m246_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m246_CameraDebugPrint(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = m246_AngleAdd(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void m246_CameraDebugPad(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)HuPadBtn[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m246_AngleAdd(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m246_AngleAdd(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m246_AngleAdd(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m246_AngleAdd(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & A_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & B_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & L_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & R_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & U_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & D_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)HuPadBtn[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

const char m246_cameraDebugStr[] = "";

void m246_PhaseSet(u8 value) {
    m246_phase = value;
}

void m246_MotShiftSet(omObjData *obj, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

void m246_MotSet(omObjData *obj, s16 motion, s16 start, s16 end, s16 *current) {
    if (*current != motion) {
        Hu3DMotionModelSet(obj->model[0], obj->motion[motion]);
        Hu3DMotionAttrSet(obj->model[0], start, end);
        *current = motion;
    }
}

void m246_VelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
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

f32 m246_AngleTurnCalc(f32 current, f32 target, f32 step) {
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = -diff;
    }
    if (diff < step) {
        return target;
    }
    if (current < target) {
        if (diff > 180.0f) {
            current = m246_AngleAdd(current, -step);
        } else {
            current = m246_AngleAdd(current, step);
        }
    } else if (target < current) {
        if (diff > 180.0f) {
            current = m246_AngleAdd(current, step);
        } else {
            current = m246_AngleAdd(current, -step);
        }
    }
    return current;
}

void m246_BackObjMain(omObjData *obj) {
}

void m246_BackObjInit(omObjData *obj) {
    m246_backSprAnim = HuSprAnimDataRead(0x4F0000);
    m246_backSprNo = espEntry(m246_backSprAnim, 0, 0);
    espAttrSet(m246_backSprNo, HUSPR_ATTR_BG);
    m246_backSprX = 160.0f;
    m246_backSprY = 120.0f;
    espPosSet(m246_backSprNo, 160, 120);
    obj->func = m246_BackObjMain;
}

void m246_BackObjCreate(void) {
    omObjData *obj = omAddObj(0x32, 1, 0, -1, m246_BackObjInit);
    obj->work[0] = 0;
    m246_objWorkTbl[0].obj = obj;
}

void m246_PaddleAnimClose(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        DataClose(m246_paddleAnimDataTbl[i]);
    }
    for (i = 0; i < 4; i++) {
        Hu3DAnimKill(m246_paddleAnimTbl[i]);
    }
}

void m246_PlayerComInput(omObjData *obj) {
    if (m246_matchF == 1 && m246_timer < 50) {
        if (((rand8() & 0xFF) + (rand8() & 0xFF)) % m246_comSlapRateTbl[GwPlayer[obj->work[0]].cpu_difficulty][0] == 0 || m246_timer < 2) {
            HuPadBtnDown[obj->work[3]] |= A_BUTTON;
        }
    } else {
        if (((rand8() & 0xFF) + (rand8() & 0xFF)) % m246_comSlapRateTbl[GwPlayer[obj->work[0]].cpu_difficulty][1] == 0) {
            HuPadBtnDown[obj->work[3]] |= A_BUTTON;
        }
    }
}

void m246_PlayerObjMain(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[11 + obj->work[0]];
    SlapdownObjWork *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 found;
    s16 moving;
    s16 max;
    s16 pick;

    for (i = 0; i < 4; i++) {
        entries[i] = &m246_objWorkTbl[11 + i];
        objs[i] = entries[i]->obj;
    }
    switch (m246_phase) {
        case 3:
        case 4:
        case 5:
            if (GwPlayer[obj->work[0]].stat & 1) {
                m246_PadClear(obj->work[0]);
                if (m246_phase == 5) {
                    m246_PlayerComInput(obj);
                }
            }
            if (obj->work[0] == 3) {
                if (m246_timer > 0) {
                    for (i = 0; i < 4; i++) {
                        if (entries[i]->unk_04 == 0 && entries[i]->unk_06 == 0 && (HuPadBtnDown[objs[i]->work[3]] & A_BUTTON)) {
                            entries[i]->unk_06 = 1;
                        }
                    }
                }
                found = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_06 != 0 && entries[i]->unk_06 < 99) {
                        found = 1;
                    }
                }
                if (found == 1) {
                    max = 1;
                    for (i = 0; i < 4; i++) {
                        if (max < entries[i]->unk_06 && entries[i]->unk_06 < 99) {
                            max = entries[i]->unk_06;
                        }
                    }
                    if (m246_timer % 3 == 0) {
                        pick = (u8)(rand8() % 4);
                        while (TRUE) {
                            if (entries[pick]->unk_06 == max) {
                                HuAudPlayerFXPlay(0x47B, objs[pick]->work[0]);
                                m246_MotSet(objs[pick], 2, 2, 0, &entries[pick]->unk_04);
                                Hu3DMotionSpeedSet(objs[pick]->model[4], 1.0f);
                                entries[pick]->unk_06 = 99;
                                entries[pick]->unk_08 = m246_slapOrderNo;
                                m246_slapOrderNo++;
                                if (m246_matchF == 1) {
                                    entries[pick]->unk_0A = m246_timer;
                                } else {
                                    entries[pick]->unk_0A = -1;
                                    m246_missCnt++;
                                }
                                break;
                            }
                            pick++;
                            if (pick >= 4) {
                                pick = 0;
                            }
                        }
                        for (i = 0; i < 4; i++) {
                            if (pick != i && entries[i]->unk_06 != 0 && entries[i]->unk_06 < 99) {
                                entries[i]->unk_06++;
                            }
                        }
                    }
                }
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_04 == 2 && Hu3DData[objs[i]->model[0]].motTime >= 10.0f) {
                        Hu3DMotionTimeSet(objs[i]->model[0], 9.0f);
                        Hu3DMotionSpeedSet(objs[i]->model[0], 0.0f);
                        if (entries[i]->unk_0E == 0) {
                            entries[i]->unk_0E = 1;
                        }
                    }
                }
                m246_slapPendingF = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_06 != 0 && entries[i]->unk_06 != 100) {
                        m246_slapPendingF = 1;
                    }
                }
            }
            switch (entry->unk_0E) {
                case 0:
                    entry->unk_18 = 0.0f;
                    break;
                case 1:
                    entry->unk_18 = m246_AngleAdd(entry->unk_18, 20.0f);
                    switch (entry->unk_08) {
                        case 0:
                            if (entry->unk_18 >= 93.0f) {
                                entry->unk_18 = 93.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                HuAudPlayerFXPlay(0x47C, obj->work[0]);
                            }
                            break;
                        case 1:
                            if (entry->unk_18 >= 91.0f) {
                                entry->unk_18 = 91.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                HuAudPlayerFXPlay(0x47C, obj->work[0]);
                            }
                            break;
                        case 2:
                            if (entry->unk_18 >= 89.0f) {
                                entry->unk_18 = 89.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                HuAudPlayerFXPlay(0x47C, obj->work[0]);
                            }
                            break;
                        case 3:
                            if (entry->unk_18 >= 87.0f) {
                                entry->unk_18 = 87.0f;
                                entry->unk_0E = 50;
                                Hu3DMotionTimeSet(obj->model[2], 8.0f);
                                Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                                HuAudPlayerFXPlay(0x47C, obj->work[0]);
                            }
                            break;
                    }
                    break;
                case 50:
                    if (m246_timer < -29) {
                        if (m246_matchF == 1) {
                            entry->unk_0E = 100;
                        } else {
                            entry->unk_0E = 99;
                        }
                    }
                    break;
                case 99:
                    if (entry->unk_18 <= 15.0f || entry->unk_18 >= 345.0f) {
                        entry->unk_18 = 0.0f;
                        entry->unk_0E = 100;
                    } else {
                        entry->unk_18 = m246_AngleAdd(entry->unk_18, -15.0f);
                    }
                    break;
                case 100:
                    entry->unk_06 = 100;
                    if (entry->unk_0A == -1) {
                        switch (entry->unk_0C) {
                            case 0:
                                if (m246_knockSeTbl[obj->work[0]] == -1) {
                                    m246_knockSeTbl[obj->work[0]] = HuAudPlayerFXPlay(0x47E, obj->work[0]);
                                    PlayerFXPlay(0x286, obj->work[0]);
                                }
                                obj->rot.y = m246_AngleAdd(obj->rot.y, 20.0f);
                                if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
                                    obj->trans.x += m246_knockVelTbl[obj->work[1]].x;
                                    obj->trans.z += m246_knockVelTbl[obj->work[1]].y;
                                } else {
                                    obj->trans.x += m246_knockVelAltTbl[obj->work[1]].x;
                                    obj->trans.z += m246_knockVelAltTbl[obj->work[1]].y;
                                }
                                m246_MotShiftSet(obj, 3, 0, 5, 2, &entry->unk_04);
                                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                                if ((s16)obj->rot.y == m246_playerRotTbl[obj->work[1]]) {
                                    entry->unk_0C = 1;
                                    obj->rot.y = m246_playerRotTbl[obj->work[1]];
                                }
                                break;
                            case 1:
                                m246_MotShiftSet(obj, 3, 0, 5, 1, &entry->unk_04);
                                break;
                        }
                    }
                    break;
            }
            break;
        case 6:
            if (entry->unk_0A == -1) {
                switch (entry->unk_0C) {
                    case 0:
                        if (m246_knockSeTbl[obj->work[0]] == -1) {
                            m246_knockSeTbl[obj->work[0]] = HuAudPlayerFXPlay(0x47E, obj->work[0]);
                            PlayerFXPlay(0x286, obj->work[0]);
                        }
                        obj->rot.y = m246_AngleAdd(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
                            obj->trans.x += m246_knockVelTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelTbl[obj->work[1]].y;
                        } else {
                            obj->trans.x += m246_knockVelAltTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelAltTbl[obj->work[1]].y;
                        }
                        m246_MotShiftSet(obj, 3, 0, 5, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == m246_playerRotTbl[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = m246_playerRotTbl[obj->work[1]];
                        }
                        break;
                    case 1:
                        m246_MotShiftSet(obj, 3, 0, 5, 1, &entry->unk_04);
                        break;
                }
            }
            break;
        case 7:
        case 8:
            if (entry->unk_16 == 0) {
                switch (entry->unk_0C) {
                    case 0:
                        obj->rot.y = m246_AngleAdd(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
                            obj->trans.x += m246_knockVelTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelTbl[obj->work[1]].y;
                        } else {
                            obj->trans.x += m246_knockVelAltTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelAltTbl[obj->work[1]].y;
                        }
                        m246_MotShiftSet(obj, 1, 0, 3, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == m246_playerRotTbl[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = m246_playerRotTbl[obj->work[1]];
                        }
                        break;
                    case 1:
                        if (m246_phase == 8 && m246_timer >= 0) {
                            m246_MotShiftSet(obj, 4, 0, 5, 0, &entry->unk_04);
                            HuAudCharVoicePlay((m246_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x30);
                            entry->unk_0C = 2;
                        } else {
                            m246_MotShiftSet(obj, 0, 0, 5, 1, &entry->unk_04);
                        }
                        break;
                    case 2:
                        break;
                }
            } else {
                switch (entry->unk_0C) {
                    case 0:
                        obj->rot.y = m246_AngleAdd(obj->rot.y, 20.0f);
                        if (GwPlayer[obj->work[0]].chr != CHAR_DK) {
                            obj->trans.x += m246_knockVelTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelTbl[obj->work[1]].y;
                        } else {
                            obj->trans.x += m246_knockVelAltTbl[obj->work[1]].x;
                            obj->trans.z += m246_knockVelAltTbl[obj->work[1]].y;
                        }
                        m246_MotShiftSet(obj, 3, 0, 3, 2, &entry->unk_04);
                        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                        if ((s16)obj->rot.y == m246_playerRotTbl[obj->work[1]]) {
                            entry->unk_0C = 1;
                            obj->rot.y = m246_playerRotTbl[obj->work[1]];
                        }
                        break;
                    case 1:
                        if (m246_phase == 8 && m246_resultReadyF != 0 && m246_timer >= 0) {
                            m246_MotShiftSet(obj, 5, 0, 5, 0, &entry->unk_04);
                            if (m246_knockSeTbl[obj->work[0]] != -1) {
                                HuAudFXStop(m246_knockSeTbl[obj->work[0]]);
                            }
                            entry->unk_0C = 2;
                        } else {
                            m246_MotShiftSet(obj, 3, 0, 5, 1, &entry->unk_04);
                        }
                        break;
                    case 2:
                        break;
                }
            }
            if (obj->work[0] == 3 && m246_resultReadyF == 0) {
                moving = 0;
                for (i = 0; i < 4; i++) {
                    if (entries[i]->unk_16 != 0 &&
                        (entries[i]->unk_04 != 3 ||
                         (s16)objs[i]->rot.y != m246_playerRotTbl[objs[i]->work[1]])) {
                        moving = 1;
                    }
                }
                if (moving == 0) {
                    m246_resultReadyF = 1;
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[2], entry->unk_18, m246_paddleRotTbl[obj->work[1]], 0.0f);
}

void m246_PlayerObjInit(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[11 + obj->work[0]];
    s8 chr = GwPlayer[obj->work[0]].chr;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][3], 0x2A9);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x14));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 8));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x30));
    if (chr != CHAR_YOSHI) {
        omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x38));
    } else {
        omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x3A));
    }
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    entry->unk_04 = 0;
    if (chr != CHAR_DK) {
        obj->trans.x = m246_playerPosXTbl[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = m246_playerPosZTbl[obj->work[1]];
    } else {
        obj->trans.x = m246_playerPosXAltTbl[obj->work[1]];
        obj->trans.y = 75.0f;
        obj->trans.z = m246_playerPosZAltTbl[obj->work[1]];
    }
    obj->rot.x = 0.0f;
    obj->rot.y = m246_playerRotTbl[obj->work[1]];
    obj->rot.z = 0.0f;
    obj->model[1] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    obj->model[2] = Hu3DModelRead(0x4F0018, 0x2A9);
    m246_paddleAnimDataTbl[obj->work[1]] = DataRead(m246_paddleAnimFileTbl[obj->work[1]][1]);
    m246_paddleAnimTbl[obj->work[1]] =
        Hu3DAnimCreate(Hu3DData[obj->model[2]].hmf, m246_paddleAnimDataTbl[obj->work[1]], 0, "s246_07_DEF");
    Hu3DModelRemakeStatic(obj->model[2]);
    Hu3DModelDynamicFree(obj->model[2]);
    Hu3DMotionTimeSet(obj->model[2], 0.0f);
    Hu3DMotionSpeedSet(obj->model[2], 0.0f);
    switch (obj->work[1]) {
        case 0:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, -285.0f);
            break;
        case 1:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, -285.0f);
            break;
        case 2:
            Hu3DModelPosSet(obj->model[2], 285.0f, 100.0f, 285.0f);
            break;
        case 3:
            Hu3DModelPosSet(obj->model[2], -285.0f, 100.0f, 285.0f);
            break;
    }
    Hu3DModelRotSet(obj->model[2], 0.0f, m246_paddleRotTbl[obj->work[1]], 0.0f);
    obj->model[3] = Hu3DModelRead(0x4F0017, 0x2A9);
    Hu3DModelPosSet(obj->model[3], m246_buttonPosXTbl[obj->work[1]], 0.0f, m246_buttonPosZTbl[obj->work[1]]);
    Hu3DModelRotSet(obj->model[3], 0.0f, m246_playerRotTbl[obj->work[1]], 0.0f);
    obj->model[4] = Hu3DModelRead(0x4F001A, 0x2A9);
    Hu3DModelPosSet(obj->model[4], m246_buttonPosXTbl[obj->work[1]], 0.0f, m246_buttonPosZTbl[obj->work[1]]);
    Hu3DModelRotSet(obj->model[4], 0.0f, m246_playerRotTbl[obj->work[1]], 0.0f);
    Hu3DMotionTimeSet(obj->model[4], 0.0f);
    Hu3DMotionSpeedSet(obj->model[4], 0.0f);
    entry->unk_0A = -2;
    obj->func = m246_PlayerObjMain;
}

void m246_PlayerObjCreateAll(void) {
    s16 order[4];
    SlapdownObjWork *entry;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 pick;
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
        entry = &m246_objWorkTbl[11 + i];
        obj = omAddObj(0xFA, 10, 60, -1, m246_PlayerObjInit);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        entry->obj = obj;
        pick = rand8() % (4 - i);
        obj->work[1] = order[pick];
        order[pick] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void m246_TargetAnimSet(omObjData *obj, s16 anim) {
    Hu3DAnimKill(m246_targetAnim);
    m246_targetAnim = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m246_targetAnimDataTbl[anim], 0, "s246_01_DEF");
}

void m246_TargetAnimClose(void) {
    s16 i;

    for (i = 0; i < 5; i++) {
        DataClose(m246_targetAnimDataTbl[i]);
    }
    Hu3DAnimKill(m246_targetAnim);
}

void m246_SpareAnimClose(void) {
    DataClose(m246_spareAnimData);
    Hu3DAnimKill(m246_spareAnim);
}

void m246_TargetObjMain(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[1];

    switch (m246_phase) {
        case 0:
            break;
        case 1:
            if (entry->unk_04 < 60) {
                if (entry->unk_06 == 0) {
                    HuAudFXPlay(0x479);
                    entry->unk_06 = 1;
                }
                entry->unk_04++;
                m246_TargetAnimSet(obj, entry->unk_04 % 5);
            } else {
                if (entry->unk_06 == 1) {
                    HuAudFXPlay(0x47F);
                    entry->unk_06 = 2;
                }
                m246_TargetAnimSet(obj, m246_targetType);
                m246_phaseDoneNo = 1;
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
    }
}

void m246_TargetObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x4F0019, 0x2A9);
    m246_targetAnimDataTbl[0] = DataRead(0x4F0011);
    m246_targetAnimDataTbl[1] = DataRead(0x4F0012);
    m246_targetAnimDataTbl[2] = DataRead(0x4F0013);
    m246_targetAnimDataTbl[3] = DataRead(0x4F0014);
    m246_targetAnimDataTbl[4] = DataRead(0x4F0015);
    m246_targetAnim = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m246_targetAnimDataTbl[0], 0, "s246_19_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    m246_targetType = (u8)(rand8() % 5);
    obj->func = m246_TargetObjMain;
}

const char m246_emptyStr[] = "";

void m246_TargetObjCreate(void) {
    omObjData *obj = omAddObj(0x96, 1, 0, -1, m246_TargetObjInit);
    obj->work[0] = 0;
    m246_objWorkTbl[1].obj = obj;
}

void m246_CardAnimSet(omObjData *obj, s16 anim) {
    Hu3DAnimKill(m246_cardAnimTbl[obj->work[0]]);
    m246_cardAnimTbl[obj->work[0]] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m246_cardAnimDataTbl[anim], 0, "s246_01_DEF");
}

void m246_CardAnimClose(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(m246_cardAnimDataTbl[i]);
    }
    for (i = 0; i < 9; i++) {
        Hu3DAnimKill(m246_cardAnimTbl[i]);
    }
}

void m246_CardObjMain(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[2 + obj->work[0]];
    SlapdownObjWork *entries[9];
    omObjData *objs[9];
    s16 i;
    s16 pick;

    for (i = 0; i < 9; i++) {
        entries[i] = &m246_objWorkTbl[2 + i];
        objs[i] = entries[i]->obj;
    }
    (void)objs;
    if (obj->work[0] == 0) {
        m246_cardSpinAngle = m246_AngleAdd(m246_cardSpinAngle, 25.0f);
    }
    switch (m246_phase) {
        case 2:
            if (obj->work[0] == 8 && m246_firstFlipF == 0) {
                m246_firstFlipF = 1;
                pick = (u8)(rand8() % 9);
                if (entries[pick]->unk_06 == m246_targetType) {
                    pick = (u8)(rand8() % 9);
                    if (entries[pick]->unk_06 == m246_targetType) {
                        m246_matchF = 1;
                    } else {
                        m246_matchF = 0;
                    }
                } else {
                    m246_matchF = 0;
                }
                entries[pick]->unk_04 = 1;
            }
            break;
        case 3:
            obj->rot.z = m246_cardSpinAngle;
            m246_spinSeState = 1;
            if (m246_timer <= 60 && obj->work[0] == 8) {
                for (i = 0; i < 9; i++) {
                    if (entries[i]->unk_04 == 1) {
                        m246_phaseDoneNo = 3;
                    }
                }
            }
            break;
        case 4:
            if (entry->unk_04 == 1) {
                switch (entry->unk_08) {
                    case 0:
                        obj->rot.z = m246_cardSpinAngle;
                        if (m246_cardSpinAngle >= 150.0f && m246_cardSpinAngle <= 180.0f) {
                            entry->unk_08 = 1;
                        }
                        break;
                    case 1:
                        obj->rot.z = m246_cardSpinAngle;
                        if (m246_cardSpinAngle >= 0.0f && m246_cardSpinAngle <= 30.0f) {
                            HuAudFXPlay(0x480);
                            m246_CardAnimSet(obj, entry->unk_06);
                            obj->rot.z = 0.0f;
                            m246_phaseDoneNo = 4;
                            entry->unk_08 = 0;
                        }
                        break;
                }
            } else {
                if (m246_spinSeState == 3) {
                    m246_spinSeState = 1;
                }
                obj->rot.z = m246_cardSpinAngle;
            }
            break;
        case 5:
            if (entry->unk_04 == 1) {
                if (m246_timer <= 0) {
                    obj->rot.z = 0.0f;
                    if (m246_slapPendingF == 0) {
                        if (m246_matchF != 1) {
                            entry->unk_04 = 99;
                            if (m246_missCnt < 3) {
                                m246_CardAnimSet(obj, 5);
                            } else {
                                entry->unk_04 = 100;
                            }
                        } else {
                            entry->unk_04 = 100;
                        }
                        m246_phaseDoneNo = 5;
                    }
                }
            } else if (m246_timer <= 0) {
                switch (entry->unk_08) {
                    case 0:
                        obj->rot.z = m246_cardSpinAngle;
                        if (m246_cardSpinAngle >= 0.0f && m246_cardSpinAngle <= 30.0f) {
                            entry->unk_08 = 1;
                        }
                        break;
                    case 1:
                        if (m246_spinSeState == 1) {
                            m246_spinSeState = 0;
                        }
                        obj->rot.z = 0.0f;
                        break;
                }
            } else {
                obj->rot.z = m246_cardSpinAngle;
            }
            if (obj->work[0] == 8 && m246_phaseDoneNo == 5 && m246_matchF != 1) {
                pick = (u8)(rand8() % 9);
                while (TRUE) {
                    if (entries[pick]->unk_04 == 0) {
                        break;
                    }
                    pick++;
                    if (pick >= 9) {
                        pick = 0;
                    }
                }
                entries[pick]->unk_04 = 1;
                for (i = 0; i < 9; i++) {
                    entries[i]->unk_08 = 0;
                }
            }
            break;
        case 6:
        case 7:
            if (entry->unk_04 == 100) {
                obj->rot.z = 0.0f;
            } else {
                switch (entry->unk_08) {
                    case 0:
                        if (obj->rot.z >= 0.0f && obj->rot.z <= 30.0f) {
                            entry->unk_08 = 1;
                        } else {
                            obj->rot.z = m246_cardSpinAngle;
                        }
                        break;
                    case 1:
                        if (m246_spinSeState == 1) {
                            m246_spinSeState = 0;
                        }
                        obj->rot.z = 0.0f;
                        break;
                }
            }
            break;
    }
    if (obj->work[0] == 8) {
        switch (m246_spinSeState) {
            case 0:
                if (m246_spinSeNo != -1) {
                    HuAudFXStop(m246_spinSeNo);
                    m246_spinSeNo = -1;
                    m246_spinSeState = 2;
                }
                break;
            case 1:
                if (m246_spinSeNo == -1) {
                    m246_spinSeNo = HuAudFXPlay(0x47A);
                }
                break;
            case 2:
                HuAudFXPlay(0x480);
                m246_spinSeState = 3;
                break;
        }
    }
}

void m246_CardObjInit(omObjData *obj) {
    SlapdownObjWork *entries[9];
    omObjData *objs[9];
    s16 i;
    s16 j;

    for (i = 0; i < 9; i++) {
        entries[i] = &m246_objWorkTbl[2 + i];
        objs[i] = entries[i]->obj;
    }
    obj->model[0] = Hu3DModelRead(0x4F0016, 0x2A9);
    obj->trans.x = m246_cardPosXTbl[obj->work[1]];
    obj->trans.y = 35.7455f;
    obj->trans.z = m246_cardPosZTbl[obj->work[1]];
    obj->rot.x = 0.0f;
    obj->rot.y = 0.0f;
    obj->rot.z = 0.0f;
    if (obj->work[0] == 8) {
        m246_cardAnimDataTbl[0] = DataRead(0x4F0001);
        m246_cardAnimDataTbl[1] = DataRead(0x4F0002);
        m246_cardAnimDataTbl[2] = DataRead(0x4F0003);
        m246_cardAnimDataTbl[3] = DataRead(0x4F0004);
        m246_cardAnimDataTbl[4] = DataRead(0x4F0005);
        m246_cardAnimDataTbl[5] = DataRead(0x4F0006);
        entries[0]->unk_06 = m246_targetType;
        for (j = 1, i = 0; i < 5; i++) {
            if (i != m246_targetType) {
                entries[j]->unk_06 = i;
                entries[j + 1]->unk_06 = i;
                j += 2;
            }
        }
        for (i = 0; i < 9; i++) {
            m246_cardAnimTbl[objs[i]->work[0]] =
                Hu3DAnimCreate(Hu3DData[objs[i]->model[0]].hmf, m246_cardAnimDataTbl[5], 0, "s246_01_DEF");
            Hu3DModelRemakeStatic(objs[i]->model[0]);
            Hu3DModelDynamicFree(objs[i]->model[0]);
        }
    }
    obj->func = m246_CardObjMain;
}

void m246_CardObjCreateAll(void) {
    s16 order[9];
    SlapdownObjWork *entry;
    omObjData *obj;
    s16 i;
    s16 j;
    s16 pick;

    for (i = 0; i < 9; i++) {
        order[i] = i;
    }
    for (i = 0; i < 9; i++) {
        entry = &m246_objWorkTbl[2 + i];
        obj = omAddObj(0xC8, 1, 0, -1, m246_CardObjInit);
        obj->work[0] = i;
        entry->obj = obj;
        pick = rand8() % (9 - i);
        obj->work[1] = order[pick];
        order[pick] = -1;
        for (j = 1; j < 9 - i; j++) {
            if (order[j - 1] == -1) {
                order[j - 1] = order[j];
                order[j] = -1;
            }
        }
    }
}

void m246_RankObjMain(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[15 + obj->work[0]];
    SlapdownObjWork *entries[4];
    omObjData *objs[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        entries[i] = &m246_objWorkTbl[11 + i];
        objs[i] = entries[i]->obj;
    }
    switch (m246_phase) {
        case 7:
        case 8:
        case 9:
            switch (entry->unk_04) {
                case 0:
                    for (i = 0; i < 4; i++) {
                        if (objs[i]->work[1] == obj->work[0] && entries[i]->unk_0A != -2 && entries[i]->unk_0A != -1) {
                            espDispOn(entry->unk_40[1]);
                            switch (entries[i]->unk_16) {
                                case 0:
                                    espDispOn(entry->unk_06);
                                    break;
                                case 1:
                                    espDispOn(entry->unk_08);
                                    break;
                                case 2:
                                    espDispOn(entry->unk_0A);
                                    break;
                                case 3:
                                    espDispOn(entry->unk_0C);
                                    break;
                            }
                            entry->unk_04 = 1;
                        }
                    }
                    break;
                case 1:
                    if (entry->unk_18 < 1.0f) {
                        entry->unk_18 += 0.05f;
                    } else {
                        entry->unk_04 = 2;
                    }
                    break;
                case 2:
                    break;
            }
            break;
    }
    espScaleSet(entry->unk_40[1], entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_06, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_08, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_0A, entry->unk_18, entry->unk_18);
    espScaleSet(entry->unk_0C, entry->unk_18, entry->unk_18);
}

void m246_RankObjInit(omObjData *obj) {
    SlapdownObjWork *entry = &m246_objWorkTbl[15 + obj->work[0]];
    s16 i;

    if (obj->work[0] == 0 || obj->work[0] == 3) {
        entry->unk_40[0] = HuSprAnimDataRead(0x4F000C);
        entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
        if (obj->work[0] == 3) {
            espZRotSet(entry->unk_40[1], 180.0f);
        }
    } else {
        entry->unk_40[0] = HuSprAnimDataRead(0x4F000B);
        entry->unk_40[1] = espEntry(entry->unk_40[0], 0, 0);
        if (obj->work[0] == 2) {
            espZRotSet(entry->unk_40[1], 180.0f);
        }
    }
    espAttrSet(entry->unk_40[1], HUSPR_ATTR_NONE);
    espPosSet(entry->unk_40[1], m246_rankFramePosTbl[obj->work[0]].x, m246_rankFramePosTbl[obj->work[0]].y);
    espDispOff(entry->unk_40[1]);
    espPriSet(entry->unk_40[1], 0xEEEE);
    for (i = 0; i < 4; i++) {
        entry->unk_40[0] = HuSprAnimDataRead(m246_rankSprFileTbl[i]);
        switch (i) {
            case 0:
                entry->unk_06 = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_06, HUSPR_ATTR_NONE);
                espPosSet(entry->unk_06, m246_rankDigitPosTbl[obj->work[0]].x, m246_rankDigitPosTbl[obj->work[0]].y);
                espDispOff(entry->unk_06);
                espPriSet(entry->unk_06, 0xAAAA);
                break;
            case 1:
                entry->unk_08 = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_08, HUSPR_ATTR_NONE);
                espPosSet(entry->unk_08, m246_rankDigitPosTbl[obj->work[0]].x, m246_rankDigitPosTbl[obj->work[0]].y);
                espDispOff(entry->unk_08);
                espPriSet(entry->unk_08, 0xAAAA);
                break;
            case 2:
                entry->unk_0A = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_0A, HUSPR_ATTR_NONE);
                espPosSet(entry->unk_0A, m246_rankDigitPosTbl[obj->work[0]].x, m246_rankDigitPosTbl[obj->work[0]].y);
                espDispOff(entry->unk_0A);
                espPriSet(entry->unk_0A, 0xAAAA);
                break;
            case 3:
                entry->unk_0C = espEntry(entry->unk_40[0], 0, 0);
                espAttrSet(entry->unk_0C, HUSPR_ATTR_NONE);
                espPosSet(entry->unk_0C, m246_rankDigitPosTbl[obj->work[0]].x, m246_rankDigitPosTbl[obj->work[0]].y);
                espDispOff(entry->unk_0C);
                espPriSet(entry->unk_0C, 0xAAAA);
                break;
        }
    }
    entry->unk_18 = 0.1f;
    obj->func = m246_RankObjMain;
}

void m246_RankObjCreateAll(void) {
    SlapdownObjWork *entry;
    omObjData *obj;
    s16 i;

    for (i = 0; i < 4; i++) {
        entry = &m246_objWorkTbl[15 + i];
        obj = omAddObj(0x12C, 1, 0, -1, m246_RankObjInit);
        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m246_RankCalc(void) {
    SlapdownObjWork *entries[4];
    omObjData *objs[4];
    s16 i;
    s16 j;
    s16 active;
    s16 out;
    s16 rank;
    s16 min;
    s16 found;

    active = 0;
    out = 0;
    for (i = 0; i < 4; i++) {
        entries[i] = &m246_objWorkTbl[11 + i];
        objs[i] = entries[i]->obj;
        // do-while(0) needed to match register allocation.
        do {
            entries[i]->unk_16 = -1;
        } while (0);
        if (entries[i]->unk_0A == -2) {
            out++;
        }
        if (entries[i]->unk_0A >= 0) {
            active++;
        }
    }
    // Copied but never read in the original.
    (void)objs;
    if (active == 0) {
        if (out == 1) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_0A == -1) {
                    entries[i]->unk_16 = 1;
                } else {
                    entries[i]->unk_16 = 0;
                }
            }
        } else {
            for (i = 0; i < 4; i++) {
                entries[i]->unk_16 = 3;
            }
        }
    } else {
        rank = 3;
        found = 0;
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_0A == -1) {
                entries[i]->unk_16 = rank;
                found = 1;
            }
        }
        min = 9999;
        for (i = 0; i < 4; i++) {
            if (entries[i]->unk_0A == -2) {
                entries[i]->unk_16 = rank;
                found = 1;
            }
        }
        if (found) {
            rank--;
        }
        for (j = 0; j < 4; j++) {
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_16 == -1 && entries[i]->unk_0A < min) {
                    min = entries[i]->unk_0A;
                }
            }
            for (i = 0; i < 4; i++) {
                if (entries[i]->unk_16 == -1 && entries[i]->unk_0A == min) {
                    entries[i]->unk_16 = rank;
                    rank--;
                }
            }
            min = 9999;
        }
    }
}

void m246_ResultSet(void) {
    SlapdownObjWork *entries[4];
    omObjData *objs[4];
    s16 ranks[4];
    s16 places[4];
    s16 i;
    s16 found;

    for (i = 0; i < 4; i++) {
        ranks[i] = 4;
        places[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        entries[i] = &m246_objWorkTbl[11 + i];
        objs[i] = entries[i]->obj;
        if (ranks[0] > entries[i]->unk_16) {
            ranks[0] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[0] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[1]) {
            ranks[1] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[1] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[2]) {
            ranks[2] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[2] < entries[i]->unk_16 && entries[i]->unk_16 < ranks[3]) {
            ranks[3] = entries[i]->unk_16;
        }
    }
    for (i = 0; i < 4; i++) {
        if (ranks[0] == entries[i]->unk_16) {
            places[i] = 0;
        }
        if (ranks[1] == entries[i]->unk_16) {
            places[i] = 1;
        }
        if (ranks[2] == entries[i]->unk_16) {
            places[i] = 2;
        }
        if (ranks[3] == entries[i]->unk_16) {
            places[i] = 3;
        }
    }
    found = 0;
    for (i = 0; i < 4; i++) {
        if (entries[i]->unk_16 != 3) {
            found = 1;
        }
    }
    if (found == FALSE) {
        for (i = 0; i < 4; i++) {
            places[i] = 3;
        }
        m246_missCnt = 4;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[objs[i]->work[0]].bonusCoin = places[i];
        entries[i]->unk_16 = places[i];
    }
}

void m246_CameraViewInit(void) {
    u32 i;

    if (m246_cameraSetF == 0) {
        m246_cameraSetF = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2037.5552f;
            CRotM[i].x = 311.9663f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -42.5f;
            CenterM[i].z = -160.0f;
        }
    }
}

void m246_ExitObjMain(omObjData *obj) {
    m246_TargetAnimClose();
    m246_CardAnimClose();
    m246_PaddleAnimClose();
    HuAudFXStop(-1);
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m246_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m246_ExitObjMain;
    }
}

void m246_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m246_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m246_MainObjMain(omObjData *obj) {
    SlapdownObjWork *entry;
    s16 i;

    switch (m246_phase) {
        case 0:
            m246_PhaseSet(1);
            m246_timer = 0;
            HuAudFXPlay(0x47D);
            break;
        case 1:
            if (m246_phaseDoneNo == 1) {
                m246_PhaseSet(2);
                GMesCreate(GMES_MES_7);
                m246_timer = 0;
            }
            break;
        case 2:
            if (m246_timer >= 63) {
                HuAudSeqPlay(0x38);
            } else {
                m246_timer++;
            }
            if (GMesStatGet() == 0) {
                m246_PhaseSet(3);
                m246_timer = 90;
            }
            break;
        case 3:
            m246_timer--;
            if (m246_phaseDoneNo == 3) {
                m246_PhaseSet(4);
            }
            break;
        case 4:
            if (m246_timer >= -29) {
                m246_timer--;
            }
            if (m246_phaseDoneNo == 4) {
                m246_PhaseSet(5);
            }
            break;
        case 5:
            if (m246_timer >= -29) {
                m246_timer--;
            }
            if (m246_phaseDoneNo == 5) {
                if (m246_matchF != 1) {
                    if (m246_missCnt < 3) {
                        m246_PhaseSet(4);
                        m246_timer = 60;
                        for (i = 0; i < 9; i++) {
                            entry = &m246_objWorkTbl[2 + i];
                            if (entry->unk_04 == 1) {
                                if (entry->unk_06 == m246_targetType) {
                                    m246_matchF = 1;
                                } else {
                                    m246_matchF = 0;
                                }
                                break;
                            }
                        }
                    } else {
                        m246_PhaseSet(6);
                        m246_timer = 15;
                    }
                } else {
                    m246_PhaseSet(6);
                    m246_timer = 15;
                }
            }
            break;
        case 6:
            if (m246_spinSeState == 3) {
                if (m246_timer < 0) {
                    m246_PhaseSet(7);
                    GMesCreate(GMES_MES_18);
                    HuAudSeqFadeOut(120);
                    m246_RankCalc();
                    m246_ResultSet();
                    m246_timer = -15;
                } else {
                    m246_timer--;
                }
            }
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (m246_timer >= 0) {
                    m246_PhaseSet(8);
                    if (m246_missCnt < 4) {
                        m246_timer = 98;
                    } else {
                        m246_timer = 132;
                    }
                } else {
                    m246_timer++;
                }
            }
            break;
        case 8:
            if (m246_missCnt >= 4) {
                if (m246_timer == 132) {
                    HuAudSeqPlay(0x6B);
                }
            } else {
                if (m246_timer == 98) {
                    HuAudSeqPlay(0x65);
                }
            }
            if (m246_timer > 0) {
                m246_timer--;
            } else {
                m246_timer = 0;
                m246_PhaseSet(9);
            }
            break;
        case 9:
            if (m246_timer == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                obj->func = m246_ExitWaitObjMain;
                m246_timer++;
            }
            break;
    }
}

void m246_MainObjInit(omObjData *obj) {
    s16 i;

    WipeCreateIn(WIPE_TYPE_PREV, 16);
    m246_CameraViewInit();
    m246_BackObjCreate();
    m246_TargetObjCreate();
    m246_CardObjCreateAll();
    m246_PlayerObjCreateAll();
    m246_RankObjCreateAll();
    m246_timer = 0;
    m246_phase = 0;
    m246_phaseDoneNo = 0;
    m246_unusedCntB = 0;
    m246_slapPendingF = 0;
    m246_matchF = 0;
    m246_targetType = 0;
    m246_missCnt = 0;
    m246_firstFlipF = 0;
    m246_resultReadyF = 0;
    m246_slapOrderNo = 0;
    m246_cardSpinAngle = 0;
    m246_unusedCntA = 0;
    m246_spinSeNo = -1;
    for (i = 0; i < 4; i++) {
        m246_knockSeTbl[i] = -1;
    }
    m246_spinSeState = 0;
    obj->func = m246_MainObjMain;
}

void m246_Dummy(void) {
}

void m246_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m246_cameraViewTbl[i].scissorX, m246_cameraViewTbl[i].scissorY,
                   m246_cameraViewTbl[i].scissorWidth, m246_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m246_cameraViewTbl[i].viewportScale.x, m246_cameraViewTbl[i].viewportScale.y,
                    m246_cameraViewTbl[i].viewportScale.z, m246_cameraViewTbl[i].viewportTranslate.x,
                    m246_cameraViewTbl[i].viewportTranslate.y, m246_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m246_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m246_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(60, 0);
    omGameSysInit();
    m246_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, -41.0f, 70.0f, 87.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -41.0f, 70.0f, 87.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -41.0f, 70.0f, 87.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m246_fontMesTbl, 0);
    GMesFontMesCreate(m246_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m246_MainObjInit);
    omAddObj(1000, 0, 0, -1, m246_ExitCheckObjMain);
    m246_ObjWorkInit();
}

const s16 m246_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
