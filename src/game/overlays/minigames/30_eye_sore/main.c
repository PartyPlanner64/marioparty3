#include "common.h"
#include "math.h"
#include "game/overlays/minigame.h"

// One entry of the 50 entry object table. Layout derived from the table clear
// in m248_ObjWorkInit, which walks 50 entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04[10];
    /* 0x18 */ f32 unk_18[10];
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} EyeSoreObjWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ s8 unk_05;
    /* 0x06 */ s8 unk_06;
    /* 0x07 */ char unk_07[1];
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ s8 unk_11;
    /* 0x12 */ char unk_12[2];
    /* 0x14 */ omObjData *unk_14;
} EyeSoreFire; // sizeof 0x18

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ char unk_03[1];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s8 unk_0C;
    /* 0x0D */ s8 unk_0D;
    /* 0x0E */ s8 unk_0E;
    /* 0x0F */ u8 unk_0F;
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ s8 unk_11;
    /* 0x12 */ s8 unk_12;
    /* 0x13 */ s8 unk_13;
    /* 0x14 */ s8 unk_14[16];
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ s8 unk_4C;
    /* 0x4D */ char unk_4D[3];
    /* 0x50 */ omObjData *unk_50;
} EyeSorePlayer; // sizeof 0x54

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ char unk_01[3];
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s8 unk_0C;
    /* 0x0D */ s8 unk_0D;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ omObjData *unk_10;
} EyeSoreEye; // sizeof 0x14

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} EyeSoreCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x02 */ s16 unk_02[7];
} EyeSorePhaseWork; // sizeof 0x10

extern s32 omCharModelNoTbl[][6];

f32 m248_AngleAdd(f32 arg0, f32 arg1);
void m248_StageObjMain(omObjData *obj);
void m248_StageObjInit(omObjData *obj);
void m248_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4);
void m248_ObjectSetup(void);
void m248_PlayerMotChange(omObjData *obj, s8 motion);
void m248_PlayerStepSeUpdate(omObjData *obj, s8 sound);
void m248_PlayerComInput(omObjData *obj);
void m248_FireObjInit(omObjData *obj);
void m248_PlayerObjCreateAll(void);

s32 m248_voiceChrTbl[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 m248_stepSeTbl[] = { 0, 0x1F, 0x28, 0 };
s8 m248_stunHopTbl[] = { 33, 30, 27, 24, 21, 18, 15, 12, 9, 6, 3, 0, -3, -6, -9, -12, -15, -18, -21, -24, -27, -30, -33 };
u8 m248_comRadiusTbl[] = { 150, 145, 140, 135 };
s8 m248_comCutInTbl[] = { 5, 4, 2, 1 };

u16 m248_faceAnimFileTbl[][2] = {
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0xA4, 0xA5 },
    { 0x1A, 0x1C },
};

EyeSorePhaseWork m248_phaseWork BSS;
f32 m248_eyeScaleTbl[15] BSS;
u8 m248_finishRank BSS;
EyeSoreObjWork m248_objWorkTbl[50] BSS;
EyeSoreFire m248_fireTbl[12] BSS;
s16 m248_musicTimer BSS;
s8 m248_finishAddCnt BSS;
u8 m248_finishAddCntPad[4] BSS; /* Unreferenced. */
EyeSorePlayer m248_playerWorkTbl[4] BSS;
s16 m248_timer BSS;
s16 m248_eyeMdl BSS;
s16 m248_linkMdlTbl[2] BSS;
s16 m248_fireShadowMdl BSS;
u8 m248_fireShadowMdlPad[4] BSS; /* Unreferenced. */
EyeSoreEye m248_eyeTbl[4] BSS;
s8 m248_drawF BSS;
s8 m248_finishCnt BSS;
u8 m248_finishCntPad[4] BSS; /* Unreferenced. */
void *m248_faceAnimDataTbl[4][2] BSS;

extern const char *m248_faceAnimNameTbl[];
extern const s16 m248_fontMesTbl[];

/* Aliases of m248_phaseWork fields (undefined_syms.txt). */
extern s8 m248_phase;
extern s16 m248_faceAnimTbl[];

/* Aliases of m248_objWorkTbl[0] fields (undefined_syms.txt). */
extern s16 m248_backSprAnim; // [0].unk_40[0]
extern s16 m248_backSprNo; // [0].unk_40[1]
extern f32 m248_backSprX; // [0].unk_44.x
extern f32 m248_backSprY; // [0].unk_44.y

void m248_Executor(void) {
    m248_ObjectSetup();
}

f32 m248_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m248_RandMulGet(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void m248_ObjWorkInit(void) {
    EyeSoreObjWork *entry;
    u32 i;

    for (i = 0, entry = m248_objWorkTbl; i < 50; i++, entry++) {
        entry->obj = NULL;
        entry->unk_04[0] = 0;
        entry->unk_04[1] = 0;
        entry->unk_04[2] = 0;
        entry->unk_04[3] = 0;
        entry->unk_04[4] = 0;
        entry->unk_04[5] = 0;
        entry->unk_04[6] = 0;
        entry->unk_04[7] = 0;
        entry->unk_04[8] = 0;
        entry->unk_04[9] = 0;
        entry->unk_18[0] = 0;
        entry->unk_18[1] = 0;
        entry->unk_18[2] = 0;
        entry->unk_18[3] = 0;
        entry->unk_18[4] = 0;
        entry->unk_18[5] = 0;
        entry->unk_18[6] = 0;
        entry->unk_18[7] = 0;
        entry->unk_18[8] = 0;
        entry->unk_18[9] = 0;
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

void m248_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m248_CameraDebugPrint(f32 x0, f32 z0, f32 x1, f32 z1) {
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
    rot = m248_AngleAdd(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 m248_RandGet(s32 arg0) {
    return rand8() % arg0;
}

void m248_MotSet(omObjData *obj, u16 motion, s16 shift) {
    Hu3DMotionModelSet(obj->model[0], obj->motion[motion]);
    Hu3DMotionAttrSet(obj->model[0], shift, shift);
}

void m248_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

void m248_ChaseVelCalc(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 *angle, f32 speed) {
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

s8 m248_RotYTurn(omObjData *obj, f32 target) {
    f32 rotY = obj->rot.y;
    f32 diff = target - rotY;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 10.0f) {
        obj->rot.y = target;
    } else if (rotY < target) {
        if (diff > 180.0f) {
            obj->rot.y = m248_AngleAdd(obj->rot.y, -10.0f);
        } else {
            obj->rot.y = m248_AngleAdd(obj->rot.y, 10.0f);
        }
        return 1;
    } else if (target < rotY) {
        if (diff > 180.0f) {
            obj->rot.y = m248_AngleAdd(obj->rot.y, 10.0f);
        } else {
            obj->rot.y = m248_AngleAdd(obj->rot.y, -10.0f);
        }
        return 1;
    }
    return 0;
}

void m248_StageObjMain(omObjData *obj) {
}

void m248_StageObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x510000, 0x2B9);
    obj->model[1] = Hu3DModelRead(0x510001, 0x2B9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    m248_backSprX = 160.0f;
    m248_backSprY = 120.0f;
    m248_backSprAnim = HuSprAnimDataRead(0x510004);
    m248_backSprNo = espEntry(m248_backSprAnim, 0, 0);
    espAttrSet(m248_backSprNo, 0x1000);
    espPosSet(m248_backSprNo, m248_backSprX, m248_backSprY);
    m248_backSprX = 160.0f;
    m248_backSprY = 120.0f;
    m248_backSprAnim = HuSprAnimDataRead(0x510005);
    m248_backSprNo = espEntry(m248_backSprAnim, 0, 0);
    espAttrSet(m248_backSprNo, 0x1000);
    espPosSet(m248_backSprNo, m248_backSprX, m248_backSprY);
    obj->func = m248_StageObjMain;
}

void m248_StageObjCreate(void) {
    omObjData *obj = omAddObj(0x1F4, 3, 3, -1, m248_StageObjInit);
    obj->work[0] = 0;
    m248_objWorkTbl[0].obj = obj;
}

void m248_PlayerFaceAnimSet(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    Hu3DAnimKill(m248_faceAnimTbl[player]);
    m248_faceAnimTbl[player] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m248_faceAnimDataTbl[player][anim], 0, m248_faceAnimNameTbl[chr]);
}

void m248_PlayerStepSeUpdate(omObjData *obj, s8 sound) {
    EyeSoreObjWork *entry = &m248_objWorkTbl[obj->work[0] + 5];

    if (obj->work[2] == 0) {
        if (entry->unk_04[8] != 0) {
            HuAudFXStop(entry->unk_04[8]);
        }
        entry->unk_04[8] = PlayerFXPlay(m248_stepSeTbl[sound], obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

const char *m248_faceAnimNameTbl[] = {
    "c000l_0_DEF",
    "c001l_0_DEF",
    "c002l_0_DEF",
    "c003l_0_DEF",
    "c004l_0_DEF",
    "c005l_0_DEF",
    "c300l_0_DEF",
    "c301l_0_DEF",
};

u8 m248_stunStarOfsTbl[] = { 70, 60, 70, 90, 70, 100, 90, 70 };

f32 m248_eyePopScaleTbl[] = {
    1.0f, 2.0f, 2.1f, 2.2f, 2.3f, 2.4f, 2.5f, 2.6f, 2.7f, 2.75f,
    2.8f, 2.85f, 2.9f, 2.95f, 3.0f, 3.05f, 3.1f, 3.15f, 3.2f, 3.25f
};

s8 m248_fireUnseenRateTbl[] = { 6, 8, 10, 15 };
s32 m248_cameraSetF = 0;

EyeSoreCamera m248_cameraViewTbl[4] = {
    { 0.0f, 0.0f, 160.0f, 120.0f, { 320.0f, 240.0f, 511.0f }, { 350.0f, 240.0f, 511.0f }, 25.0f },
    { 160.0f, 0.0f, 320.0f, 120.0f, { 320.0f, 240.0f, 511.0f }, { 930.0f, 240.0f, 511.0f }, 25.0f },
    { 0.0f, 120.0f, 160.0f, 240.0f, { 320.0f, 240.0f, 511.0f }, { 350.0f, 700.0f, 511.0f }, 25.0f },
    { 160.0f, 120.0f, 320.0f, 240.0f, { 320.0f, 240.0f, 511.0f }, { 930.0f, 700.0f, 511.0f }, 25.0f },
};

void m248_PlayerMotChange(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    EyeSoreObjWork *entry = &m248_objWorkTbl[obj->work[0] + 5];
    s16 shift;

    if (entry->unk_04[1] != motion) {
        switch (motion) {
            case 4:
            case 7:
            case 8:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 5:
            case 6:
            default:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        m248_MotShiftSet(obj, motion, 0, 10, shift);
        entry->unk_04[1] = motion;
        if (motion == 7) {
            HuAudCharVoicePlay((m248_voiceChrTbl[chr] << 16) | 0x2F);
        }
    }
}

void m248_PlayerPadInput(omObjData *obj) {
    u8 pad = obj->work[3];
    s16 stickX = HuPadStkX[pad];
    s16 stickY = -HuPadStkY[pad];
    f32 mag;
    f32 speed;

    if (stickX != 0 || stickY != 0) {
        mag = sqrtf(stickX * stickX + stickY * stickY);
        if (mag >= 70.0f) {
            speed = 25.0f;
        } else {
            speed = mag * 0.357;
        }
        obj->rot.y = m248_AngleAdd(atan2df(stickX, stickY), 0.0f);
        obj->trans.x += sindf(obj->rot.y) * speed;
        obj->trans.z += cosdf(obj->rot.y) * speed;
        if (mag > 40.0f) {
            m248_PlayerMotChange(obj, 2);
            m248_PlayerStepSeUpdate(obj, 2);
        } else {
            m248_PlayerMotChange(obj, 1);
            m248_PlayerStepSeUpdate(obj, 1);
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        m248_PlayerMotChange(obj, 0);
    }
}

void m248_FireSpawnUpdate(omObjData *obj) {
    s16 player = obj->work[0];
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    s16 i = player * 2;
    EyeSoreFire *first = &m248_fireTbl[i];
    EyeSoreFire *second = &m248_fireTbl[i + 1];

    if (state->unk_0D < 12) {
        switch (state->unk_0E) {
            case 0:
                first->unk_06 = 1;
                break;
            case 5:
                if (state->unk_0D < 7) {
                    second->unk_06 = 1;
                }
                break;
            case 60:
                first->unk_06 = 5;
                break;
            case 65:
                if (state->unk_0D < 7) {
                    second->unk_06 = 5;
                }
                break;
        }
        state->unk_0E = (state->unk_0E + 1) % 90;
    }
}

void m248_PlayerComInput(omObjData *obj) {
    s16 player = obj->work[0];
    s16 base = player * 2;
    f32 angleOfs = -20.0f;
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[player];
    EyeSoreFire *entry;
    s16 found = FALSE;
    f32 speed;
    f32 target;
    f32 angle;
    f32 tmp;
    f32 dist;
    f32 x;
    f32 z;
    s16 i;

    switch (state->unk_01) {
        case 0:
            speed = m248_RandGet(7) + 15.0f;
            break;
        case 2:
            speed = m248_RandGet(7) + 18.0f;
            break;
        case 3:
            speed = m248_RandGet(5) + 20.0f;
            break;
        case 1:
        default:
            speed = m248_RandGet(8) + 17.0f;
            break;
    }

    if (state->unk_02 < 5) {
        for (i = 0; i < 2; i++) {
            entry = &m248_fireTbl[base + i];
            if (entry->unk_10 != 0 && entry->unk_05 == 0) {
                angle = m248_AngleAdd(state->unk_48, -entry->unk_00);
                tmp = m248_AngleAdd(entry->unk_00, -state->unk_48);
                if ((angle < 90.0f) | (tmp < 45.0f)) {
                    if (entry->unk_08 < unkCBC0->unk_04 + (280.0f - unkCBC0->unk_04) * 0.5) {
                        state->unk_02 = 4;
                    } else {
                        state->unk_02 = 3;
                    }
                    found = TRUE;
                }
                tmp = (state->unk_24 < 120.0f) ? 50.0f : 25.0f;
                if (angle < tmp) {
                    tmp = state->unk_24 - entry->unk_08;
                    if (tmp < 0.0f) {
                        dist = 0.0f - tmp;
                    } else {
                        dist = tmp;
                    }
                    if (entry->unk_0C + 60.0f > dist) {
                        if (entry->unk_08 < unkCBC0->unk_04 + entry->unk_0C + (280.0f - unkCBC0->unk_04) * 0.5) {
                            state->unk_02 = 6;
                        } else {
                            state->unk_02 = 7;
                        }
                        state->unk_4C = base + i;
                        break;
                    }
                    found = TRUE;
                }
            }
        }
        if (!found && (state->unk_02 == 3 || state->unk_02 == 4)) {
            state->unk_02 = 0;
        }
    }

    if (m248_RandGet(30) == 0 && m248_RandGet(24) < m248_comCutInTbl[state->unk_01]) {
        state->unk_02 = 5;
    }

    switch (state->unk_02) {
        case 0:
            target = m248_comRadiusTbl[state->unk_01];
            if (state->unk_04 < target) {
                state->unk_04 += 15.0f;
            }
            if (target < state->unk_04) {
                state->unk_04 -= 15.0f;
            }
            tmp = (s16)(state->unk_04 - target);
            if (abs(tmp) < 15) {
                state->unk_04 = target;
            }
            if (m248_RandGet(16) < 4 - state->unk_01) {
                if (m248_RandGet(2) != 0) {
                    state->unk_02 = 1;
                    state->unk_08 = m248_RandGet(30) + 30;
                } else {
                    state->unk_02 = 2;
                    state->unk_08 = m248_RandGet(50) + 40;
                }
            }
            break;
        case 1:
            target = m248_comRadiusTbl[state->unk_01] - state->unk_08;
            if (target < state->unk_04) {
                state->unk_04 -= 15.0f;
            } else {
                state->unk_04 = target;
                if (m248_RandGet(10) == 0) {
                    state->unk_02 = 0;
                }
            }
            break;
        case 2:
            target = m248_comRadiusTbl[state->unk_01] + state->unk_08;
            if (state->unk_04 < target) {
                state->unk_04 += 15.0f;
            } else {
                state->unk_04 = target;
                if (m248_RandGet(10) == 0) {
                    state->unk_02 = 0;
                }
            }
            break;
        case 3:
            target = unkCBC0->unk_04 + 60.0f;
            if (target < state->unk_04) {
                state->unk_04 -= 20.0f;
            } else {
                state->unk_04 = target;
            }
            break;
        case 4:
            target = 270.0f;
            if (state->unk_04 < target) {
                state->unk_04 += 20.0f;
            } else {
                state->unk_04 = target;
            }
            break;
        case 5:
            if (55.0f < state->unk_04) {
                state->unk_04 -= 10.0f;
            } else {
                state->unk_04 = 55.0f;
            }
            break;
        case 6:
            state->unk_04 = 270.0f;
            goto case6_7_tail;
        case 7:
            state->unk_04 = unkCBC0->unk_04 + 60.0f;
        case6_7_tail:
            if (++state->unk_0F >= 5) {
                state->unk_02 = 8;
                state->unk_0F = 0;
            }
            angleOfs = 15.0f;
            break;
        case 8:
            speed = 0.0f;
            entry = &m248_fireTbl[state->unk_4C];
            if (280.0f - entry->unk_08 >= 120.0f || entry->unk_08 - unkCBC0->unk_04 >= 220.0f || entry->unk_10 == 0) {
                state->unk_02 = 0;
            }
            break;
    }

    target = unkCBC0->unk_04 + state->unk_04;
    angle = m248_AngleAdd(atan2df(obj->trans.x, obj->trans.z), angleOfs);
    x = sindf(angle) * target;
    z = cosdf(angle) * target;
    obj->rot.y = m248_AngleAdd(atan2df(x - obj->trans.x, z - obj->trans.z), 0.0f);
    obj->trans.x += sindf(obj->rot.y) * speed;
    obj->trans.z += cosdf(obj->rot.y) * speed;
    if (speed != 0.0f) {
        m248_PlayerMotChange(obj, 2);
        m248_PlayerStepSeUpdate(obj, 2);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    } else {
        m248_PlayerMotChange(obj, 0);
    }
}

void m248_PlayerKnockUpdate(omObjData *obj) {
    u8 pad = obj->work[3];
    EyeSorePlayer *state = &m248_playerWorkTbl[obj->work[0]];
    f32 velX;
    f32 velZ;
    f32 angle;

    m248_ChaseVelCalc(state->unk_28, state->unk_2C, obj->trans.x, obj->trans.z, &velX, &velZ, &angle, 40.0f);
    if (velX + velZ == 0.0f) {
        if (state->unk_0F < 40) {
            state->unk_0F++;
        }
        if (state->unk_0F == 15) {
            m248_PlayerMotChange(obj, 4);
        }
        if (state->unk_0F >= 31 && (m248_phase >= 3 ||
                                    HuPadStkX[(s8)pad] + HuPadStkY[(s8)pad] != 0 || state->unk_00 != 0)) {
            state->unk_11 = 0;
            state->unk_0F = 0;
            state->unk_02 = 0;
        }
    } else {
        obj->trans.x += velX;
        obj->trans.z += velZ;
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    }
}

void m248_PlayerStunUpdate(omObjData *obj) {
    u8 pad = obj->work[3];
    EyeSoreObjWork *entry = &m248_objWorkTbl[(s8)obj->work[0] + 5];
    EyeSorePlayer *state = &m248_playerWorkTbl[obj->work[0]];

    if (state->unk_0F < 46) {
        state->unk_34 = obj->trans.y + 30.0f;
        if ((state->unk_0F == 0) | (state->unk_0F == 23)) {
            HuAudPlayerFXPlay(0x48C, obj->work[0]);
        }
        if ((u8)(state->unk_0F % 23) < 11) {
            if (state->unk_38 < state->unk_34 + 44.0f) {
                state->unk_38 += 5.0f;
            }
            if (state->unk_3C < state->unk_38 + 46.0f) {
                state->unk_3C += 5.0f;
            }
            if (state->unk_40 < state->unk_3C + 60.0f) {
                state->unk_40 += 5.0f;
            }
        } else {
            if (state->unk_34 + 44.0f < state->unk_38) {
                state->unk_38 -= 5.0f;
            }
            if (state->unk_38 + 46.0f < state->unk_3C) {
                state->unk_3C -= 5.0f;
            }
            if (state->unk_3C + 60.0f < state->unk_40) {
                state->unk_40 -= 5.0f;
            }
        }
        entry->unk_18[0] = m248_AngleAdd(entry->unk_18[0], 30.0f);
        Hu3DModelPosSet(obj->model[2], state->unk_30, state->unk_34, state->unk_44);
        Hu3DModelPosSet(obj->model[3], state->unk_30, state->unk_38, state->unk_44);
        Hu3DModelPosSet(obj->model[4], state->unk_30, state->unk_3C, state->unk_44);
        Hu3DModelPosSet(obj->model[5], state->unk_30, state->unk_40, state->unk_44);
        Hu3DModelRotSet(obj->model[2], 0.0f, 0.0f, entry->unk_18[0]);
        Hu3DModelRotSet(obj->model[3], 0.0f, 0.0f, entry->unk_18[0]);
        Hu3DModelRotSet(obj->model[4], 0.0f, 0.0f, entry->unk_18[0]);
        Hu3DModelRotSet(obj->model[5], 0.0f, 0.0f, entry->unk_18[0]);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    if (state->unk_0F == 46) {
        HuAudPlayerFXPlay(0x48C, obj->work[0]);
    }
    if (state->unk_0F >= 16 && state->unk_0F < 51) {
        entry->unk_04[9] -= 7;
        if (entry->unk_04[9] < 0) {
            entry->unk_04[9] = 0;
        }
        Hu3DModelTPLvlSet(obj->model[2], entry->unk_04[9]);
    }
    if (state->unk_0F < 23) {
        obj->trans.y += m248_stunHopTbl[state->unk_0F];
    } else if (state->unk_0F < 46) {
        obj->trans.y += m248_stunHopTbl[state->unk_0F - 23];
    } else if (state->unk_0F == 50) {
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m248_PlayerMotChange(obj, 4);
    } else if (state->unk_0F >= 65 && (m248_phase >= 3 ||
                                       HuPadStkX[(s8)pad] + HuPadStkY[(s8)pad] != 0 || state->unk_00 != 0)) {
        state->unk_11 = 0;
        state->unk_0F = 0;
        state->unk_02 = 0;
        entry->unk_04[9] = 255;
        Hu3DModelTPLvlSet(obj->model[2], 255);
        state->unk_34 = obj->trans.y + 30.0f;
        state->unk_38 = obj->trans.y + 74.0f;
        state->unk_3C = obj->trans.y + 120.0f;
        state->unk_40 = obj->trans.y + 180.0f;
        return;
    }
    if (state->unk_0F < 65) {
        state->unk_0F++;
    }
}

void m248_PlayerHitCheck(omObjData *obj) {
    s8 player = obj->work[0];
    s8 base = player * 2;
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[player];
    EyeSoreFire *entry;
    f32 threshold;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 angle;
    s8 i;
    s8 end;

    state->unk_24 = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    threshold = unkCBC0->unk_04 + 60.0f;
    if (state->unk_24 > 280.0f) {
        obj->trans.x = sindf(state->unk_48) * 279.0f;
        obj->trans.z = cosdf(state->unk_48) * 279.0f;
    }
    if (state->unk_24 < threshold) {
        state->unk_28 = unkCBC0->unk_10->trans.x + sindf(state->unk_48) * (unkCBC0->unk_04 + 115.0f + state->unk_0D * 6);
        state->unk_2C = unkCBC0->unk_10->trans.z + cosdf(state->unk_48) * (unkCBC0->unk_04 + 115.0f + state->unk_0D * 6);
        state->unk_11 = 1;
        unkCBC0->unk_00 = 1;
        state->unk_0F = 0;
        m248_PlayerMotChange(obj, 5);
        Hu3DMotionSpeedSet(obj->model[0], 2.0f);
        if (!(GwPlayer[obj->work[0]].stat & 1)) {
            omVibrate(obj->work[0], 20, 0, 20);
        }
        HuAudPlayerFXPlay(0x488, obj->work[0]);
        Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    end = base + 2;
    for (i = base; i < end; i++) {
        entry = &m248_fireTbl[i];
        if (entry->unk_10 == 0 || !(entry->unk_14->trans.y < 120.0f)) {
            continue;
        }
        dx = obj->trans.x - entry->unk_14->trans.x;
        dz = obj->trans.z - entry->unk_14->trans.z;
        dist = dx * dx + dz * dz;
        threshold = (entry->unk_0C + 60.0f) * (entry->unk_0C + 60.0f);
        if (dist < threshold) {
            state->unk_11 = 2;
            state->unk_0F = 0;
            entry->unk_10 = 0;
            entry->unk_06 = 5;
            m248_PlayerMotChange(obj, 6);
            obj->rot.y = atan2df(dx, dz);
            if (!(GwPlayer[obj->work[0]].stat & 1)) {
                omVibrate(obj->work[0], 20, 0, 20);
            }
            HuAudPlayerFXPlay(0x48B, obj->work[0]);
            PlayerFXPlay(0x2AB, obj->work[0]);
            angle = m248_AngleAdd(obj->rot.y, 180.0f);
            state->unk_30 = sindf(angle) * m248_stunStarOfsTbl[GwPlayer[player].chr] + obj->trans.x;
            state->unk_44 = cosdf(angle) * m248_stunStarOfsTbl[GwPlayer[player].chr] + obj->trans.z;
        }
    }
}

void m248_PlayerObjMain(omObjData *obj) {
    s8 player = obj->work[0];
    EyeSoreObjWork *entry = &m248_objWorkTbl[player + 5];
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[player];
    f32 angle;

    if (m248_phase != 2) {
        if (m248_phase >= 3) {
            switch (state->unk_11) {
                case 0:
                    if (m248_RotYTurn(obj, 0.0f)) {
                        m248_PlayerMotChange(obj, 1);
                    } else if (entry->unk_04[1] != 7 && entry->unk_04[1] != 8) {
                        m248_PlayerMotChange(obj, 0);
                    }
                    if (state->unk_13 == 0) {
                        entry->unk_18[2] = 18.0f;
                        entry->unk_18[3] = 0.6f;
                        entry->unk_18[4] = 2.6f;
                        entry->unk_18[5] = (obj->trans.z + 85.0f) / 50.0f;
                        state->unk_11 = 99;
                    }
                    break;
                case 1:
                    m248_PlayerKnockUpdate(obj);
                    break;
                case 2:
                    m248_PlayerStunUpdate(obj);
                    break;
                case 99:
                    if (m248_RotYTurn(obj, 0.0f)) {
                        m248_PlayerMotChange(obj, 1);
                    } else if (entry->unk_04[1] != 7 && entry->unk_04[1] != 8) {
                        m248_PlayerMotChange(obj, 0);
                    }
                    if (entry->unk_04[5] < 50) {
                        entry->unk_04[5]++;
                        CZoomM[player] -= entry->unk_18[2];
                        CRotM[player].x = m248_AngleAdd(CRotM[player].x, entry->unk_18[3]);
                        CRotM[player].y = 0.0f;
                        CRotM[player].z = 0.0f;
                        CenterM[player].x = 0.0f;
                        CenterM[player].y += entry->unk_18[4];
                        CenterM[player].z += entry->unk_18[5];
                    }
                    break;
            }
        }
    } else {
        if (state->unk_0D < 0) {
            if (state->unk_0F < 60) {
                m248_PlayerMotChange(obj, 3);
                state->unk_0F++;
            } else if (m248_RotYTurn(obj, 0.0f)) {
                m248_PlayerMotChange(obj, 1);
            } else {
                m248_PlayerMotChange(obj, 0);
            }
            return;
        }
        switch (state->unk_11) {
            case 0:
                if (state->unk_00 == 0) {
                    m248_PlayerPadInput(obj);
                } else {
                    m248_PlayerComInput(obj);
                }
                break;
            case 1:
                m248_PlayerKnockUpdate(obj);
                break;
            case 2:
                m248_PlayerStunUpdate(obj);
                break;
        }
        angle = m248_AngleAdd(atan2df(obj->trans.x, obj->trans.z), 0.0f);
        if (state->unk_10 == 0 && angle > 300.0f && angle < 330.0f) {
            state->unk_10 = 1;
        }
        if (state->unk_10 != 0 && state->unk_0C == 0) {
            if (angle > 330.0f && state->unk_48 < 30.0f && state->unk_14[state->unk_0D] == 0) {
                state->unk_14[state->unk_0D] = 1;
                if (--state->unk_0D < 0) {
                    state->unk_13 = m248_finishRank;
                    m248_finishAddCnt++;
                    HuAudPlayerFXPlay(0x490, obj->work[0]);
                    return;
                }
                HuAudPlayerFXPlay(0x48F, obj->work[0]);
                unkCBC0->unk_04 = m248_eyeScaleTbl[state->unk_0D] * 75.0f;
            }
        }
        if ((state->unk_48 < angle && angle - state->unk_48 < 300.0f) ||
            (angle < 30.0f && state->unk_48 > 330.0f)) {
            state->unk_0C = 1;
        } else if ((angle <= unkCBC0->unk_08 && unkCBC0->unk_08 <= state->unk_48) ||
                   (angle > 330.0f && unkCBC0->unk_08 < 30.0f && state->unk_48 < 30.0f) ||
                   (angle > 330.0f && unkCBC0->unk_08 > 330.0f && angle <= unkCBC0->unk_08)) {
            state->unk_0C = 0;
        }
        state->unk_48 = angle;
        m248_FireSpawnUpdate(obj);
        m248_PlayerHitCheck(obj);
    }
}

void m248_PlayerObjInit(omObjData *obj) {
    u16 player = obj->work[0];
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    EyeSoreObjWork *entry = &m248_objWorkTbl[player + 5];
    u16 chr = GwPlayer[player].chr;
    s32 dir = omCharModelNoTbl[chr][0];
    u16 i;

    obj->model[0] = Hu3DModelRead(dir | omCharModelNoTbl[chr][2], 0x2A9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 2));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x13));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x23));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x15));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x1A));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x36));
    for (i = 0; i < 2; i++) {
        m248_faceAnimDataTbl[player][i] = DataRead(dir | m248_faceAnimFileTbl[chr][i]);
    }
    m248_faceAnimTbl[player] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m248_faceAnimDataTbl[player][0], 0, m248_faceAnimNameTbl[chr]);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    if (player == 0) {
        obj->model[1] = Hu3DModelRead2(0, 0xC9);
        Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[1]);
        Hu3DModelDynamicFree(obj->model[1]);
        HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        m248_linkMdlTbl[0] = obj->model[1];
    } else {
        obj->model[1] = Hu3DModelLink(m248_linkMdlTbl[0]);
    }
    obj->model[2] = Hu3DModelRead(0x10014, 0x8C);
    Hu3DModelTPLvlInit(obj->model[2]);
    Hu3DModelTPLvlSet(obj->model[2], 255);
    obj->model[3] = Hu3DModelLink(m248_linkMdlTbl[1] = obj->model[2]);
    obj->model[4] = Hu3DModelLink(m248_linkMdlTbl[1]);
    obj->model[5] = Hu3DModelLink(m248_linkMdlTbl[1]);
    obj->trans.y = 5.0f;
    obj->trans.z = 200.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 5.0f, 200.0f);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[4], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelPosSet(obj->model[5], obj->trans.x, 5.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelScaleSet(obj->model[3], 1.2f, 1.2f, 1.2f);
    Hu3DModelScaleSet(obj->model[4], 1.4f, 1.4f, 1.4f);
    Hu3DModelScaleSet(obj->model[5], 1.6f, 1.6f, 1.6f);
    m248_MotSet(obj, 0, 2);
    entry->unk_04[1] = 0;
    switch (player) {
        case 0:
            for (i = 0; i < 6; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM0);
            }
            break;
        case 1:
            for (i = 0; i < 6; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM1);
            }
            break;
        case 2:
            for (i = 0; i < 6; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM2);
            }
            break;
        case 3:
            for (i = 0; i < 6; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM3);
            }
            break;
    }
    entry->unk_04[9] = 255;
    state->unk_34 = obj->trans.y + 30.0f;
    state->unk_38 = obj->trans.y + 74.0f;
    state->unk_3C = obj->trans.y + 120.0f;
    state->unk_40 = obj->trans.y + 180.0f;
    state->unk_0C = 0;
    state->unk_0D = 14;
    state->unk_00 = GwPlayer[player].stat & 1;
    state->unk_01 = GwPlayer[player].cpu_difficulty;
    state->unk_02 = 0;
    state->unk_48 = 0.0f;
    state->unk_0E = 0;
    state->unk_11 = 0;
    state->unk_0F = 0;
    state->unk_12 = 0;
    state->unk_13 = -1;
    state->unk_10 = 0;
    state->unk_04 = m248_comRadiusTbl[state->unk_01];
    state->unk_50 = obj;
    for (i = 0; i < 15; i++) {
        state->unk_14[i] = 0;
    }
    obj->work[3] = GwPlayer[player].pad;
    obj->func = m248_PlayerObjMain;
}

void m248_PlayerObjCreateAll(void) {
    EyeSoreObjWork *entry;
    omObjData *obj;
    u32 player = 0;
    s8 i;
    s32 unused[2]; // Retain the original stack frame.

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
        entry = &m248_objWorkTbl[i + 5];
        obj = omAddObj(600, 7, 12, -1, m248_PlayerObjInit);
        obj->work[0] = player;
        entry->obj = obj;
    }
}

void m248_ResultSet(void) {
    EyeSorePlayer *state;
    s8 count = 0;
    s8 i;

    for (i = 0; i < 4; i++) {
        state = &m248_playerWorkTbl[i];
        if (state->unk_13 < 0) {
            count++;
        }
    }
    if (count == 4) {
        m248_playerWorkTbl[0].unk_13 = 3;
        m248_playerWorkTbl[1].unk_13 = 3;
        m248_playerWorkTbl[2].unk_13 = 3;
        m248_playerWorkTbl[3].unk_13 = 3;
        m248_drawF = 1;
    }
    for (i = 0; i < 4; i++) {
        state = &m248_playerWorkTbl[i];
        if (state->unk_13 < 0) {
            state->unk_13 = m248_finishRank;
        }
        GwPlayer[state->unk_50->work[0]].bonusCoin = state->unk_13;
        if (state->unk_13 == 0) {
            m248_PlayerMotChange(state->unk_50, 7);
            m248_PlayerFaceAnimSet(state->unk_50, 1);
        } else {
            m248_PlayerMotChange(state->unk_50, 8);
        }
    }
}

void m248_RankTieResolve(void) {
    EyeSorePlayer *a;
    EyeSorePlayer *b;
    s8 order = 3;
    s16 changed;
    s8 i;
    s8 j;

    do {
        changed = FALSE;
        for (i = 0; i < 4; i++) {
            a = &m248_playerWorkTbl[i];
            for (j = 0; j < 4; j++) {
                if (i == j) {
                    continue;
                }
                b = &m248_playerWorkTbl[j];
                if (a->unk_13 != -1 && a->unk_13 == b->unk_13) {
                    if (m248_RandGet(2) != 0) {
                        a->unk_13++;
                        a->unk_12 = order;
                    } else {
                        b->unk_13++;
                        b->unk_12 = order;
                    }
                    order += 3;
                    changed = TRUE;
                }
            }
        }
    } while (changed);
}

void m248_EyeObjMain(omObjData *obj) {
    u8 player = obj->work[0];
    EyeSoreObjWork *entry = &m248_objWorkTbl[player + 10];
    EyeSorePlayer *state = &m248_playerWorkTbl[player];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[player];
    omObjData *playerObj = state->unk_50;
    f32 angle;
    f32 scale;
    f32 size;

    switch (unkCBC0->unk_0C) {
        case 1:
            if (state->unk_12 == 0 || ++entry->unk_04[2] >= state->unk_12) {
                entry->unk_18[3] -= 2.0f;
                obj->rot.y = m248_AngleAdd(obj->rot.y, entry->unk_18[3]);
                entry->unk_18[4] -= 0.008;
                obj->scale.x = obj->scale.y = obj->scale.z = entry->unk_18[4] * 0.7f;
                scale = entry->unk_18[4] * 2.4f;
                Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
                if (entry->unk_18[4] < 0.06f) {
                    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DModelPosSet(obj->model[3], 0.0f, 90.0f, 70.0f);
                    unkCBC0->unk_0C++;
                }
            }
            break;
        case 2:
            size = m248_eyePopScaleTbl[entry->unk_04[9]];
            Hu3DModelScaleSet(obj->model[3], size, size, size);
            if (entry->unk_04[9] > 16) {
                entry->unk_04[0] = 0;
                Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                unkCBC0->unk_0C++;
            } else {
                entry->unk_04[0] -= 15;
                entry->unk_04[9]++;
                if (unkCBC0->unk_0D == 0) {
                    HuAudPlayerFXPlay(0x48A, playerObj->work[0]);
                    unkCBC0->unk_0D = 1;
                }
                Hu3DModelTPLvlSet(obj->model[3], entry->unk_04[0]);
            }
            break;
        case 3:
            break;
        case 0:
        default:
            if (state->unk_0C == 0) {
                obj->rot.y = m248_AngleAdd(atan2df(playerObj->trans.x, playerObj->trans.z), 0.0f);
            }
            unkCBC0->unk_08 = obj->rot.y;
            switch (unkCBC0->unk_00) {
                case 0:
                    break;
                case 1:
                    angle = m248_AngleAdd(state->unk_48, 180.0f);
                    obj->trans.x = sindf(angle) * 30.0f;
                    obj->trans.z = cosdf(angle) * 30.0f;
                    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    Hu3DMotionSpeedSet(obj->model[2], 1.0f);
                    Hu3DMotionTimeSet(obj->model[2], 5.0f);
                    Hu3DModelRotSet(obj->model[2], 0.0f, state->unk_48, 0.0f);
                    Hu3DModelPosSet(obj->model[2], sindf(state->unk_48) * unkCBC0->unk_04, obj->scale.y * 50.0f,
                                    cosdf(state->unk_48) * unkCBC0->unk_04);
                    scale = m248_eyeScaleTbl[state->unk_0D] * 1.4f;
                    Hu3DModelScaleSet(obj->model[2], scale, scale, scale);
                    entry->unk_04[1] = 1;
                    unkCBC0->unk_00++;
                    break;
                case 2:
                    m248_ChaseVelCalc(0.0f, 0.0f, obj->trans.x, obj->trans.z, &entry->unk_18[0], &entry->unk_18[1],
                                           &angle, 30.0f);
                    obj->trans.x += entry->unk_18[0];
                    obj->trans.z += entry->unk_18[1];
                    if (entry->unk_18[0] + entry->unk_18[1] == 0.0f) {
                        unkCBC0->unk_00 = 0;
                    }
                    break;
            }
            if (state->unk_0D < 0) {
                unkCBC0->unk_0C = 1;
                entry->unk_18[4] = m248_eyeScaleTbl[0];
            } else {
                scale = m248_eyeScaleTbl[state->unk_0D] * 0.7f;
                if (scale < obj->scale.z) {
                    obj->scale.z -= 0.03;
                } else {
                    obj->scale.z = scale;
                }
                obj->scale.x = obj->scale.y = obj->scale.z;
                scale = m248_eyeScaleTbl[state->unk_0D] * 2.4f;
                Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
            }
            if (entry->unk_04[1] != 0 && ++entry->unk_04[1] >= 15) {
                entry->unk_04[1] = 0;
                Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

void m248_EyeObjInit(omObjData *obj) {
    u16 player = obj->work[0];
    EyeSoreObjWork *entry = &m248_objWorkTbl[player + 10];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[player];
    f32 step;
    u16 i;

    if (player == 0) {
        obj->model[0] = Hu3DModelRead(0xA015D, 0x2B9);
        m248_eyeMdl = obj->model[0];
    } else {
        obj->model[0] = Hu3DModelLink(m248_eyeMdl);
    }
    obj->model[1] = Hu3DModelLink(m248_linkMdlTbl[0]);
    obj->model[2] = Hu3DModelRead(0x510002, 0x2B9);
    Hu3DMotionSpeedSet(obj->model[2], 0.0f);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[2], 0.0f, 0.0f, 0.0f);
    obj->model[3] = Hu3DModelRead(0x510003, 0x2A8);
    Hu3DModelTPLvlInit(obj->model[3]);
    Hu3DModelTPLvlSet(obj->model[3], 255);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[3], 0.0f, 60.0f, 20.0f);
    Hu3DModelRotSet(obj->model[3], 318.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[3], 0.3f, 0.3f, 0.3f);
    obj->trans.y = 5.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.7f;
    Hu3DModelScaleSet(obj->model[1], 2.4f, 1.0f, 2.4f);
    Hu3DModelPosSet(obj->model[1], 0.0f, 5.0f, 0.0f);
    switch (player) {
        case 0:
            for (i = 0; i < 4; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM0);
            }
            break;
        case 1:
            for (i = 0; i < 4; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM1);
            }
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM2);
            }
            break;
        case 3:
            for (i = 0; i < 4; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM3);
            }
            break;
    }
    unkCBC0->unk_04 = 75.0f;
    unkCBC0->unk_08 = 0.0f;
    unkCBC0->unk_0D = 0;
    unkCBC0->unk_10 = obj;
    entry->unk_04[0] = 255;
    entry->unk_18[2] = 0.3f;
    step = 0.7f / 15.0f;
    for (i = 0; i < 15; i++) {
        m248_eyeScaleTbl[i] = step * (i + 1) + 0.3f;
    }
    obj->func = m248_EyeObjMain;
}

void m248_EyeObjCreateAll(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        EyeSoreObjWork *entry = &m248_objWorkTbl[i + 10];
        omObjData *obj = omAddObj(700, 4, 1, -1, m248_EyeObjInit);

        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m248_FireObjMain(omObjData *obj) {
    u8 index = obj->work[0];
    u8 odd = index % 2;
    u8 mult = odd * 2 + 1;
    f32 dist = 0.0f;
    EyeSoreObjWork *entry = &m248_objWorkTbl[index + 15];
    EyeSorePlayer *state = &m248_playerWorkTbl[obj->work[1]];
    EyeSoreEye *unkCBC0 = &m248_eyeTbl[obj->work[1]];
    EyeSoreFire *eye = &m248_fireTbl[index];
    s16 range;
    f32 scale;

    if (state->unk_0D < 0 || m248_phase >= 3) {
        if (eye->unk_06 == 0) {
            return;
        }
        eye->unk_06 = 5;
    }

    switch (eye->unk_06) {
        case 0:
            return;
        case 1:
            entry->unk_18[0] = 0.0f;
            entry->unk_18[1] = 1.0f;
            eye->unk_06++;
            eye->unk_00 = mult * 60 + m248_RandGet(60);
            eye->unk_00 = m248_AngleAdd(state->unk_48, -eye->unk_00);
            if (!odd) {
                range = m248_RandGet(2);
            } else {
                range = (m248_fireTbl[index - 1].unk_04 + 1) % 2;
            }
            if (range == 0) {
                dist = unkCBC0->unk_04 + eye->unk_0C +
                       m248_RandGet((s16)(180.0f - (unkCBC0->unk_04 + eye->unk_0C + eye->unk_0C))) + 20.0f;
                eye->unk_04 = 0;
            } else {
                range = 280.0f - (unkCBC0->unk_04 + 200.0f + eye->unk_0C);
                if (range == 0) {
                    dist = 280.0f;
                }
                if (range > 0) {
                    dist = 280 - m248_RandGet(range);
                }
                if (range < 0) {
                    dist = 280 - m248_RandGet(-range);
                }
                eye->unk_04 = 1;
            }
            obj->trans.x = sindf(eye->unk_00) * dist;
            obj->trans.z = cosdf(eye->unk_00) * dist;
            if (m248_RandGet(m248_fireUnseenRateTbl[state->unk_01]) == 0) {
                eye->unk_05 = 1;
            } else {
                eye->unk_05 = 0;
            }
            break;
        case 2:
            entry->unk_18[0] += 2.0f;
            obj->trans.y -= entry->unk_18[0];
            if (obj->trans.y < 5.0f) {
                obj->trans.y = 5.0f;
                eye->unk_06++;
            }
            break;
        case 3:
            entry->unk_18[0] -= 7.0f;
            obj->trans.y += entry->unk_18[0];
            if (obj->trans.y < 5.0f) {
                obj->trans.y = 5.0f;
                eye->unk_06++;
            }
            break;
        case 4:
            if (--entry->unk_04[0] < 0) {
                entry->unk_04[0] = m248_RandGet(25) + 20;
                entry->unk_18[3] = m248_RandMulGet(360);
            }
            obj->trans.x += sindf(entry->unk_18[3]) * 1.5f;
            obj->trans.z += cosdf(entry->unk_18[3]) * 1.5f;
            break;
        case 5:
            entry->unk_18[1] -= 0.05;
            if (entry->unk_18[1] < 0.4) {
                eye->unk_10 = 0;
                eye->unk_11 = 0;
            }
            if (entry->unk_18[1] < 0.05) {
                obj->trans.y = 600.0f;
                eye->unk_06 = 0;
                eye->unk_0C = 30.0f;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
                Hu3DModelScaleSet(obj->model[1], 0.1f, 1.0f, 0.1f);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            } else {
                eye->unk_0C = entry->unk_18[1] * 30.0f;
                obj->scale.x = obj->scale.y = obj->scale.z = entry->unk_18[1];
                Hu3DModelScaleSet(obj->model[1], entry->unk_18[1], 1.0f, entry->unk_18[1]);
            }
            break;
    }

    if (eye->unk_06 != 5) {
        if (obj->trans.y == 5.0f) {
            Hu3DModelScaleSet(obj->model[1], 1.0f, 1.0f, 1.0f);
        } else if (obj->trans.y < 450.0f) {
            scale = 1.0f - (2.0f * obj->trans.y) / 1000.0f;
            Hu3DModelScaleSet(obj->model[1], scale, 1.0f, scale);
            eye->unk_10 = 1;
        } else if (obj->trans.y < 580.0f) {
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (eye->unk_11 == 0) {
                HuAudFXPlay(0x489);
                eye->unk_11 = 1;
            }
        }
    }
    eye->unk_00 = m248_AngleAdd(atan2df(obj->trans.x, obj->trans.z), 0.0f);
    if (obj->trans.x < -260.0f) {
        obj->trans.x = -260.0f;
    }
    if (obj->trans.x > 260.0f) {
        obj->trans.x = 260.0f;
    }
    if (obj->trans.z < -260.0f) {
        obj->trans.z = -260.0f;
    }
    if (obj->trans.z > 260.0f) {
        obj->trans.z = 260.0f;
    }
    eye->unk_08 = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
    if (eye->unk_08 < unkCBC0->unk_04 + eye->unk_0C) {
        obj->trans.x = sindf(eye->unk_00) * (eye->unk_08 + 1.0f);
        obj->trans.z = cosdf(eye->unk_00) * (eye->unk_08 + 1.0f);
    }
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 5.0f, obj->trans.z);
}

void m248_FireObjInit(omObjData *obj) {
    u16 index = obj->work[0];
    s32 idx = index;
    EyeSoreFire *eye = &m248_fireTbl[obj->work[0]];
    void *anim = DataRead(0xA008C);
    u16 i;

    obj->model[0] = Hu3DModelRead(0xA008A, 0x2A9);
    Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, anim, 0, "c201n_00_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    DataClose(anim);
    if (idx == 0) {
        obj->model[1] = Hu3DModelRead(0x510006, 0x2B9);
        m248_fireShadowMdl = obj->model[1];
        obj->trans.x = 0.0f;
    } else {
        obj->model[1] = Hu3DModelLink(m248_fireShadowMdl);
        obj->trans.x = 0.0f;
    }
    obj->trans.y = 600.0f;
    obj->trans.z = 250.0f;
    obj->rot.x = 340.0f;
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], 0.1f, 1.0f, 0.1f);
    switch (index) {
        case 0:
        case 1:
            for (i = 0; i < 2; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM0);
            }
            obj->work[1] = 0;
            break;
        case 2:
        case 3:
            for (i = 0; i < 2; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM1);
            }
            obj->work[1] = 1;
            break;
        case 4:
        case 5:
            for (i = 0; i < 2; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM2);
            }
            obj->work[1] = 2;
            break;
        case 6:
        case 7:
            for (i = 0; i < 2; i++) {
                Hu3DModelCameraSet(obj->model[i], HU3D_CAM3);
            }
            obj->work[1] = 3;
            break;
    }
    eye->unk_00 = 0.0f;
    eye->unk_06 = 0;
    eye->unk_05 = 0;
    eye->unk_04 = 0;
    eye->unk_10 = 0;
    eye->unk_0C = 30.0f;
    eye->unk_14 = obj;
    eye->unk_11 = 0;
    obj->func = m248_FireObjMain;
}

void m248_FireObjCreateAll(void) {
    s8 i;

    for (i = 0; i < 8; i++) {
        EyeSoreObjWork *entry = &m248_objWorkTbl[i + 15];
        omObjData *obj = omAddObj(0x320, 3, 2, -1, m248_FireObjInit);

        obj->work[0] = i;
        entry->obj = obj;
    }
}

void m248_CameraViewInit(void) {
    u32 i;

    if (m248_cameraSetF == 0) {
        m248_cameraSetF = 1;
        for (i = 0; i < 4; i++) {
            CZoomM[i] = 1627.4962f;
            CRotM[i].x = 317.99966f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -45.0f;
            CenterM[i].z = -85.0f;
        }
    }
}

void m248_ExitObjMain(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m248_ExitWaitObjMain(omObjData *obj) {
    s8 i;
    s8 j;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                DataClose(m248_faceAnimDataTbl[i][j]);
            }
            Hu3DAnimKill(m248_faceAnimTbl[i]);
        }
        obj->func = m248_ExitObjMain;
    }
}

void m248_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m248_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m248_MainObjMain(omObjData *obj) {
    switch (m248_phase) {
        case 0:
            GMesCreate(GMES_MES_7);
            m248_phase = 1;
            m248_musicTimer = 0;
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m248_phase = 2;
                GMesCreate(GMES_MES_TIMER, 60, 0xA0, 0x1C);
            }
            if (++m248_musicTimer == 43) {
                HuAudSeqPlay(0x35);
            }
            break;
        case 2:
            m248_timer--;
            GMesTimerValueSet((m248_timer + 29) / 30);
            if (m248_finishAddCnt != 0) {
                m248_finishRank += m248_finishAddCnt;
                m248_finishCnt += m248_finishAddCnt;
                m248_finishAddCnt = 0;
                m248_RankTieResolve();
            }
            if (m248_timer == 0 || m248_finishCnt >= 3) {
                GMesTimerEnd();
                GMesCreate(GMES_MES_18);
                HuAudSeqFadeOut(120);
                m248_timer = 0;
                m248_phase = 3;
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                if (++m248_timer >= 15) {
                    m248_ResultSet();
                    if (m248_drawF != 0) {
                        HuAudSeqPlay(0x6C);
                        m248_timer = 144;
                    } else {
                        HuAudSeqPlay(0x65);
                        m248_timer = 98;
                    }
                    m248_phase = 4;
                }
            }
            break;
        case 4:
            if (--m248_timer <= 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                obj->func = m248_ExitWaitObjMain;
            }
            break;
    }
}

void m248_MainObjInit(omObjData *obj) {
    m248_phase = 0;
    m248_timer = 1800;
    m248_finishAddCnt = 0;
    m248_finishCnt = 0;
    m248_finishRank = 0;
    m248_drawF = 0;
    m248_CameraViewInit();
    m248_StageObjCreate();
    m248_PlayerObjCreateAll();
    m248_EyeObjCreateAll();
    m248_FireObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    obj->func = m248_MainObjMain;
}

void m248_Dummy(void) {
}

void m248_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(4);
    CamSetupMapCullAddMulti(4);
    for (i = 0; i < 4; i++) {
        ScissorSet(i, m248_cameraViewTbl[i].scissorX, m248_cameraViewTbl[i].scissorY,
                   m248_cameraViewTbl[i].scissorWidth, m248_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m248_cameraViewTbl[i].viewportScale.x, m248_cameraViewTbl[i].viewportScale.y,
                    m248_cameraViewTbl[i].viewportScale.z, m248_cameraViewTbl[i].viewportTranslate.x,
                    m248_cameraViewTbl[i].viewportTranslate.y, m248_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m248_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m248_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(60, 0);
    omGameSysInit();
    m248_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, -33.0f, 0.0f, 115.0f);
    Hu3DGLightDirSet(1, -33.0f, 0.0f, 115.0f);
    Hu3DGLightDirSet(2, -33.0f, 0.0f, 115.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m248_fontMesTbl, 0);
    GMesFontMesCreate(m248_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m248_MainObjInit);
    omAddObj(1000, 0, 0, -1, m248_ExitCheckObjMain);
    m248_ObjWorkInit();
}

const s16 m248_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
