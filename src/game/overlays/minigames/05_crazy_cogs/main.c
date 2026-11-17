#include "common.h"
#include "game/overlays/minigame.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "gcc/memory.h"

typedef struct UnkCrazyCogsCog { // 0x84 bytes, one entry per cog slot
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ u16 timer;
    /* 0x06 */ u16 unk_06;
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
} UnkCrazyCogsCog;

typedef struct {
    /* 0x00 */ u8 unk_00[3];
    /* 0x03 */ u8 unk_03;
    /* 0x04 */ u8 unk_04;
    /* 0x05 */ u8 unk_05[0xAF];
} CrazyCogsSetupWork;

typedef struct {
    u8 xTimer;
    s8 xDuration;
    s8 xSpeed;
    s8 xDirection;
    u8 zTimer;
    s8 zDuration;
    s8 zSpeed;
    s8 zDirection;
} CrazyCogsMovement;

typedef struct {
    u8 xTimer;
    s8 xDuration;
    s8 xStick;
    u8 zTimer;
    s8 zDuration;
    s8 zStick;
} CrazyCogsCpuMovement;

typedef struct {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} CrazyCogsCamera;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01[3];
} CrazyCogsTeamChrBss;

typedef struct {
    /* 0x00 */ s8 unk00[50];
    /* 0x32 */ s8 unk32;
    /* 0x33 */ s8 unk33[13];
} CrazyCogsComQueueBss;

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ s8 unk02[4];
} CrazyCogsCrankBss;

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];

s32 m205_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
// The intended delays (90, 900, 0, 30, 150) landed in gaugeValue/winners, likely
// from an initializer written without the inner braces. It doesn't matter in
// practice: this overlay never runs MgFlowMain, so only the
// setup in MgFlowInit reads this struct.
MinigameFlow m205_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 90.0f, 900.0f, 0.0f, 30.0f },
    { 150, 0, 0, 0 },
    0, 0, 0, 0, 0
};
s16 m205_panelMdlTbl[4] = { 9, 11, 10, 12 };
u16 m205_crankComDelayTbl[5] = { 10, 20, 25, 30, 40 };
s16 m205_crankMotTbl[8][2] = { { 0, 55 }, { 0, 55 }, { 0, 55 }, { 0, 55 }, { 0, 55 }, { 0, 56 }, { 0, 54 }, { 0, 54 } };
f32 m205_teamDummyRotTbl[3] = { 90.0f, 225.0f, 315.0f };
CrazyCogsCamera m205_cameraViewTbl[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 45.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 45.0f },
};

CrazyCogsTeamChrBss m205_teamChrBss BSS;
s16 m205_killerSpawnInterval BSS;
s8 m205_blastNo BSS;
s8 m205_teamOutNum BSS;
f32 m205_introKillerY BSS;
s8 m205_phase BSS;
s16 m205_killerSpawnTimer BSS;
s8 m205_resultMot BSS;
s8 m205_crankComLevel BSS;
s8 m205_crankComTargetNo BSS;
u16 m205_introKillerTimer BSS;
s8 m205_crankComWait BSS;
f32 m205_cogASpeed BSS;
u8 m205_cogASpeedPad[4] BSS; /* Unreferenced. */
CrazyCogsComQueueBss m205_comQueueBss BSS;
UnkCrazyCogsCog m205_objWorkTbl[70] BSS;
s16 m205_teamBlownTimerTbl[3] BSS;
s16 m205_crankLeverPos BSS;
s8 m205_teamPlayerNoTbl[3] BSS;
f32 m205_cogBSpeed BSS;
s32 m205_killerMdlTbl[2] BSS;
s16 m205_mainTimer BSS;
s16 m205_comKillerCnt BSS;
u8 m205_comKillerCntPad[4] BSS; /* Unreferenced. */
CrazyCogsMovement m205_killerDriftTbl[7] BSS;
s8 m205_crankDir BSS;
s16 m205_introDoneF BSS;
u8 m205_crankPlayerNo BSS;
s16 m205_timer BSS;
CrazyCogsCrankBss m205_crankBss BSS;
CrazyCogsCpuMovement m205_teamComMoveTbl[4] BSS;
f32 m205_killerShadowScaleTbl[10] BSS;
UnkCrazyCogsCog *m205_introKillerWork BSS;
s8 m205_crankComDelay BSS;

/* Fields of the grouped BSS structs above, aliased in undefined_syms.txt. */
extern s8 m205_comQueueNo;
extern s8 m205_teamChrTbl[3];
extern s8 m205_comQueueTbl[50];
extern s8 m205_comQueueNum;
extern s8 m205_rumbleReqTbl[13];
extern s8 m205_crankComState;
extern u8 m205_crankChr;
extern s8 m205_panelShakeTbl[4];

/* Fields of m205_objWorkTbl[0], aliased in undefined_syms.txt. */
extern s16 m205_backSprAnim;
extern u16 m205_backSpr;
extern f32 m205_backSprX;
extern f32 m205_backSprY;

extern const s16 m205_fontMesTbl[];

void m205_CrankObjCreate(void);
void m205_TeamDummyObjCreate(void);
void m205_TeamObjCreate(void);
void m205_KillerObjCreateAll(void);
void m205_MainObjMain(omObjData *);
void m205_BlastObjInit(omObjData *);
void m205_IntroKillerObjMain(omObjData *);
void m205_KillerReset(omObjData *);
void m205_KillerObjInit(omObjData *);
void m205_ObjectSetup(void);
void m205_MapObjInit(omObjData *);
void m205_CogCenterObjInit(omObjData *);
void m205_CogAObjInit(omObjData *);
void m205_CogBObjInit(omObjData *);
void m205_KillerSpawnObjMain(omObjData *);
void m205_KillerSpawnObjInit(omObjData *);
void m205_IntroKillerObjInit(omObjData *);
void m205_TeamObjInit(omObjData *);

void m205_Executor(void) {
    m205_ObjectSetup();
}

f32 m205_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m205_ObjWorkInit(void) {
    u32 i = 0;
    UnkCrazyCogsCog *cog = m205_objWorkTbl;

    for (; i < 70; i++, cog++) {
        cog->obj = NULL;
        cog->timer = 0;
        cog->unk_06 = 0;
        cog->unk_08 = 0;
        cog->unk_0A = 0;
        cog->unk_0C = 0;
        cog->unk_0E = 0;
        cog->unk_10 = 0;
        cog->unk_12 = 0;
        cog->unk_14 = 0;
        cog->unk_16 = 0;
        cog->unk_18 = 0;
        cog->unk_1C = 0;
        cog->unk_20 = 0;
        cog->unk_24 = 0;
        cog->unk_28 = 0;
        cog->unk_2C = 0;
        cog->unk_30 = 0;
        cog->unk_34 = 0;
        cog->unk_38 = 0;
        cog->unk_3C = 0;
        cog->unk_40 = -1;
        cog->unk_42 = -1;
        cog->unk_44.x = cog->unk_44.y = cog->unk_44.z = 0.0f;
        cog->unk_50.x = cog->unk_50.y = cog->unk_50.z = 0.0f;
        cog->unk_5C.x = cog->unk_5C.y = cog->unk_5C.z = 0.0f;
        cog->unk_68 = 0.0f;
        cog->unk_6C = 0.0f;
        cog->unk_70 = 0.0f;
        cog->unk_74 = 0.0f;
        cog->unk_78.x = cog->unk_78.y = cog->unk_78.z = 0.0f;
    }
}

void m205_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

s32 m205_RandGet(s32 arg0) {
    return rand8() % arg0;
}

f32 m205_FloorYGet(omObjData *arg0) {
    f32 x;
    f32 z;
    f32 distance;
    f32 height;

    x = (s32)((arg0->trans.x < 0.0f) ? -arg0->trans.x : arg0->trans.x);
    z = (s32)((arg0->trans.z < 0.0f) ? -arg0->trans.z : arg0->trans.z);
    distance = sqrtf(x * x + z * z);
    if (distance > 480.0f) {
        height = 1.0f;
        x = (s32)(((arg0->trans.x - 580.0f) < 0.0f) ? -(arg0->trans.x - 580.0f) : (arg0->trans.x - 580.0f));
        z = (s32)(((arg0->trans.z + 450.0f) < 0.0f) ? -(arg0->trans.z + 450.0f) : (arg0->trans.z + 450.0f));
        distance = sqrtf(x * x + z * z);
        if (distance <= 380.0f) {
            height = 55.0f;
        }
    } else {
        if ((distance <= 480.0f) & (distance > 350.0f)) {
            height = 55.0f;
        } else {
            height = 28.0f;
        }
    }
    return height;
}

f32 m205_DiamondAngleGet(f32 x, f32 z) {
    f32 angle = 0.0f;
    s32 quadrant = 0;
    f32 absX;
    f32 absZ;

    if (x >= 0.0f) {
        quadrant |= 1;
    } else {
        quadrant |= 2;
    }
    if (z < 0.0f) {
        quadrant |= 4;
    } else {
        quadrant |= 8;
    }
    absX = x;
    if (absX < 0.0f) {
        absX = -absX;
    }
    absZ = z;
    if (absZ < 0.0f) {
        absZ = -absZ;
    }
    switch (quadrant) {
        case 5:
            if (x == 0.0f) {
                return 0.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absX;
            break;
        case 9:
            if (x == 0.0f) {
                return 180.0f;
            }
            if (z == 0.0f) {
                return 90.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absZ;
            angle += 90.0f;
            break;
        case 10:
            if (x == 0.0f) {
                return 270.0f;
            }
            angle = 90.0f / (absX + absZ);
            angle *= absX;
            angle += 180.0f;
            break;
        case 6:
            angle = 90.0f / (absX + absZ);
            angle *= absZ;
            angle += 270.0f;
            break;
    }
    return angle;
}

void m205_MotSet(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        Hu3DMotionModelSet(arg0->model[0], arg0->motion[arg1]);
        Hu3DMotionAttrSet(arg0->model[0], arg2, arg2);
    }
}

void m205_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

f32 m205_AngleFrontStep(f32 angle) {
    if ((angle > 5.0f) & (angle < 355.0f)) {
        if (angle < 180.0f) {
            angle = m205_AngleAdd(angle, -6.0f);
        } else {
            angle = m205_AngleAdd(angle, 6.0f);
        }
    } else {
        angle = 0.0f;
    }
    return angle;
}

void m205_SeDebugPrint(s16 channel, s16 state) {
    switch (state) {
        case 0:
            osSyncPrintf("\x8E\x95\x8E\xD4\t"); // Cog (Shift-JIS)
            break;
        case 1:
            osSyncPrintf("\x83\x58\x83\x43\x83\x62\x83\x60\t"); // Switch (Shift-JIS)
            break;
        case 2:
            osSyncPrintf("\x91\xAB\x89\xB9\t"); // Footsteps (Shift-JIS)
            break;
        case 3:
            osSyncPrintf("\x83\x4C\x83\x89\x81\x5B\x97\x8E\x89\xBA\t"); // Bullet Bill falling (Shift-JIS)
            break;
        case 4:
            osSyncPrintf("\x94\x9A\x94\xAD\t"); // Explosion (Shift-JIS)
            break;
    }
    osSyncPrintf("ch=%d\n", channel);
}

void m205_MapObjMain(omObjData *arg0) {
}

void m205_MapObjInit(omObjData *arg0) {
    CrazyCogsSetupWork *work;

    m205_backSprX = 160.0f;
    m205_backSprY = 120.0f;
    m205_backSprAnim = HuSprAnimDataRead(0x260000);
    m205_backSpr = espEntry(m205_backSprAnim, 0, 0);
    espAttrSet(m205_backSpr, 0x5000);
    espPosSet(m205_backSpr, m205_backSprX, m205_backSprY);
    mgMapObjTbl[mgMapObjNum++] = arg0;
    work = HuMemAllocTag(sizeof(CrazyCogsSetupWork), TAG_OVERLAY);
    arg0->data = work;
    memset(work, 0, sizeof(CrazyCogsSetupWork));
    work->unk_03 = 1;
    work->unk_04 = 0;
    MgMapSlideSet(arg0, 20.0f);
    MgMapFrictionSet(arg0, 0.5f);
    MgMapAccelSet(arg0, 10.0f);
    MgMapCircleSet(mgMapObjTbl[0], 0.0f, 360.0f);
    arg0->model[0] = -1;
    arg0->func = m205_MapObjMain;
}

void m205_MapObjCreate(void) {
    m205_objWorkTbl[0].obj = omAddObj(0x1F4, 1, 0, -1, m205_MapObjInit);
}

void m205_PanelObjMain(omObjData *arg0) {
    s8 cogIdx = ((s8 *)arg0->work)[3];
    UnkCrazyCogsCog *cog = &m205_objWorkTbl[29 + cogIdx];

    if (m205_panelShakeTbl[cogIdx] != 0) {
        if (cog->timer & 1) {
            arg0->trans.y = 10.0f;
        } else {
            arg0->trans.y = 0.0f;
        }

        cog->timer++;

        if ((s16)cog->timer >= 0x14) {
            cog->timer = 0;
            m205_panelShakeTbl[cogIdx] = 0;
        }
    }
}

void m205_PanelObjInit(omObjData *arg0) {
    s8 cogIdx = ((s8 *)arg0->work)[3];

    arg0->model[0] = Hu3DModelRead(0x260000 | m205_panelMdlTbl[cogIdx], 0xB9);
    arg0->trans.x = 0.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = 0.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    m205_panelShakeTbl[cogIdx] = 0;
    arg0->func = m205_PanelObjMain;
}

void m205_PanelObjCreateAll(void) {
    s8 i;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 4; i++) {
        cog = &m205_objWorkTbl[29 + i];
        cog->obj = omAddObj(0x6A4, 1, 0, -1, m205_PanelObjInit);
        cog->obj->work[0] = i;
    }
}

void m205_CogCenterObjMain(omObjData *arg0) {
    switch (m205_crankDir) {
        case 0:
            break;
        case 1:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, -3.3f);
            break;
        case 2:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, 3.3f);
            break;
    }
    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void m205_CogCenterObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead(0x260002, 0xB9);
    arg0->model[1] = Hu3DModelRead(0x260005, 0xB9);
    arg0->trans.x = arg0->trans.y = arg0->trans.z = 0.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = m205_CogCenterObjMain;
    m205_cogASpeed = 4.4f;
    m205_cogBSpeed = 6.6000004f;
}

void m205_CogCenterObjCreate(void) {
    m205_objWorkTbl[1].obj = omAddObj(0x3E8, 2, 0, -1, m205_CogCenterObjInit);
}

void m205_CogAObjMain(omObjData *arg0) {
    switch (m205_crankDir) {
        case 0:
            break;
        case 1:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, m205_cogASpeed);
            break;
        case 2:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, -m205_cogASpeed);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void m205_CogAObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead(0x260003, 0xB9);
    arg0->model[1] = Hu3DModelRead(0x260006, 0xB9);
    arg0->trans.x = 580.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = -450.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = m205_CogAObjMain;
}

void m205_CogAObjCreate(void) {
    m205_objWorkTbl[2].obj = omAddObj(0x44C, 2, 0, -1, m205_CogAObjInit);
}

void m205_CogBObjMain(omObjData *arg0) {
    switch (m205_crankDir) {
        case 0:
            break;
        case 1:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, -m205_cogBSpeed);
            break;
        case 2:
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, m205_cogBSpeed);
            break;
    }

    Hu3DModelRotSet(arg0->model[1], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void m205_CogBObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead(0x260004, 0xB9);
    arg0->model[1] = Hu3DModelRead(0x260007, 0xB9);
    arg0->trans.x = 185.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = -800.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    arg0->func = m205_CogBObjMain;
}

void m205_CogBObjCreate(void) {
    m205_objWorkTbl[3].obj = omAddObj(0x4B0, 2, 0, -1, m205_CogBObjInit);
}

void m205_CrankDirSet(s8 direction) {
    m205_crankDir = direction;
    m205_crankComWait = 0;
    m205_crankComDelay = m205_RandGet(5) + 10;
}

void m205_CrankComChase(omObjData *arg0) {
    UnkCrazyCogsCog *target;
    UnkCrazyCogsCog *player;
    f32 targetAngle;
    f32 playerAngle;
    f32 difference;
    u16 distance;

    target = &(&m205_objWorkTbl[8])[m205_comQueueTbl[m205_comQueueNo]];
    if ((s16)target->timer == 0) {
        m205_objWorkTbl[4].unk_06 = 0;
        m205_objWorkTbl[4].unk_08 = 0;
        m205_objWorkTbl[4].unk_0A = 0;
        m205_objWorkTbl[4].unk_0C = 0;
        m205_crankComState = 0;
        m205_comQueueNo++;
        return;
    }
    player = &m205_objWorkTbl[m205_crankComTargetNo];
    if (player->unk_0E != 0) {
        m205_crankComState = 1;
        return;
    }
    targetAngle = m205_DiamondAngleGet(target->obj->trans.x, target->obj->trans.z);
    playerAngle = m205_DiamondAngleGet(player->obj->trans.x, player->obj->trans.z);
    distance = (s32)((targetAngle - playerAngle < 0.0f) ? -(targetAngle - playerAngle) : targetAngle - playerAngle);
    if ((distance < 5) || (distance >= 356)) {
        m205_crankDir = 0;
        return;
    }
    if (m205_crankComWait > m205_crankComDelay) {
        difference = targetAngle - playerAngle;
        if (difference >= 0.0f) {
            if (((difference < 0.0f) ? -difference : difference) >= 180.0f) {
                m205_CrankDirSet(2);
            } else {
                m205_CrankDirSet(1);
            }
        } else {
            if (((difference < 0.0f) ? -difference : targetAngle - playerAngle) >= 180.0f) {
                m205_CrankDirSet(1);
            } else {
                m205_CrankDirSet(2);
            }
        }
    } else {
        m205_crankComWait++;
    }
}

void m205_CrankComSeek(omObjData *arg0) {
    UnkCrazyCogsCog *target;
    UnkCrazyCogsCog *controller;
    UnkCrazyCogsCog *player;
    s16 i;
    f32 targetAngle;
    f32 difference;
    u16 distance;

    target = &(&m205_objWorkTbl[8])[m205_comQueueTbl[m205_comQueueNo]];
    controller = &m205_objWorkTbl[4];
    if ((s16)target->timer == 0) {
        controller->unk_06 = 0;
        controller->unk_08 = 0;
        controller->unk_0A = 0;
        controller->unk_0C = 0;
        m205_crankComState = 0;
        m205_comQueueNo++;
        return;
    }
    targetAngle = m205_DiamondAngleGet(target->obj->trans.x, target->obj->trans.z);
    for (i = 0; i < 3; i++) {
        player = &(&m205_objWorkTbl[5])[i];
        if (player->unk_0E == 0) {
            difference = m205_DiamondAngleGet(player->obj->trans.x, player->obj->trans.z);
            distance = (s32)((targetAngle - difference < 0.0f) ? -(targetAngle - difference) : targetAngle - difference);
            if (distance < 20 || distance >= 341) {
                controller->unk_0C = 0;
                m205_crankComTargetNo = i + 5;
                m205_crankComState = 2;
                return;
            }
        }
    }
    if (m205_crankComWait > m205_crankComDelay) {
        switch (controller->unk_0C) {
            case 0:
                controller->unk_0C = m205_RandGet(2);
                break;
            case 1:
                m205_CrankDirSet(1);
                break;
            case 2:
                m205_CrankDirSet(2);
                break;
        }
    } else {
        m205_crankComWait++;
    }
}

void m205_CrankComRandom(omObjData *arg0) {
    UnkCrazyCogsCog *controller = &m205_objWorkTbl[4];

    switch (m205_comQueueTbl[m205_comQueueNo]) {
        case -1:
            break;
        case 4:
        case 5:
        case 6:
            m205_crankComState = 1;
            return;
    }
    controller->unk_06++;
    if ((s16)controller->unk_06 >= controller->unk_08) {
        controller->unk_06 = 0;
        controller->unk_08 = m205_crankComDelayTbl[m205_RandGet(5)];
        controller->unk_0A = m205_RandGet(2);
    }
    if (m205_crankComWait > m205_crankComDelay) {
        switch (controller->unk_0A) {
            case 0:
                m205_CrankDirSet(1);
                break;
            case 1:
                m205_CrankDirSet(2);
                break;
        }
    } else {
        m205_crankComWait++;
    }
}

void m205_CrankUpdate(omObjData *arg0) {
    UnkCrazyCogsCog *controller = &m205_objWorkTbl[4];
    s16 frame;

    switch (m205_crankDir) {
        case 0:
            if (m205_crankLeverPos < 0) {
                m205_crankLeverPos += 5;
            }
            if (m205_crankLeverPos > 0) {
                m205_crankLeverPos -= 5;
            }
            if (controller->unk_0E != 0 || controller->unk_10 != 0) {
                HuAudFXIdStop(0x323);
                controller->unk_10 = 0;
                controller->unk_0E = 0;
            }
            break;
        case 1:
            if (m205_crankLeverPos < 30) {
                m205_crankLeverPos += 5;
            }
            if (controller->unk_0E == 0) {
                HuAudFXPlay(0x322);
                HuAudPlayerFXPlay(0x323, ((s16 *)arg0->work)[1]);
                controller->unk_0E = 1;
                controller->unk_10 = 0;
            }
            break;
        case 2:
            if (m205_crankLeverPos > -30) {
                m205_crankLeverPos -= 5;
            }
            if (controller->unk_10 == 0) {
                HuAudFXPlay(0x322);
                HuAudPlayerFXPlay(0x323, ((s16 *)arg0->work)[1]);
                controller->unk_0E = 0;
                controller->unk_10 = 1;
            }
            break;
    }
    frame = m205_crankLeverPos + 30;
    m205_MotShiftSet(arg0, 0, frame, 1, 1);
    Hu3DMotionTimeSet(arg0->model[1], frame);
    Hu3DModelPosSet(arg0->model[2], m205_crankLeverPos * 2.5f + arg0->trans.x, arg0->trans.y, arg0->trans.z + 40.0f);
}

void m205_CrankObjMain(omObjData *arg0) {
    s8 character = GwPlayer[arg0->work[0]].chr;

    if (m205_phase != 2) {
        if (m205_phase == 6) {
            Hu3DModelPosSet(arg0->model[2], arg0->trans.x, arg0->trans.y, arg0->trans.z);
            if (m205_resultMot < 0) {
                m205_MotSet(arg0, 3, 0);
                HuAudCharVoicePlay((m205_voiceChrTbl[character] << 16) | 0x30);
            }
            if (m205_resultMot > 0) {
                m205_MotSet(arg0, 4, 0);
            }
        } else {
            m205_CrankUpdate(arg0);
        }
    } else {
        m205_CrankUpdate(arg0);
        if (GwPlayer[arg0->work[0]].stat & 1) {
            switch (m205_crankComState) {
                case 0:
                    m205_CrankComRandom(arg0);
                    break;
                case 1:
                    m205_CrankComSeek(arg0);
                    break;
                case 2:
                    m205_CrankComChase(arg0);
                    break;
            }
        } else {
            if (((HuPadStkX[arg0->work[3]] < 0) ? -HuPadStkX[arg0->work[3]] : HuPadStkX[arg0->work[3]]) < 15) {
                m205_crankDir = 0;
            } else if (HuPadStkX[arg0->work[3]] > 30) {
                m205_crankDir = 1;
            } else if (HuPadStkX[arg0->work[3]] < -30) {
                m205_crankDir = 2;
            }
        }
    }
}

void m205_CrankObjInit(omObjData *arg0) {
    u16 character = GwPlayer[arg0->work[0]].chr;

    arg0->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharMotTbl[character][0], 0x2B9);
    omObjMotionRead(arg0, 0, CharMotionDataNumGet(character, 0x3F));
    omObjMotionRead(arg0, 3, CharMotionDataNumGet(character, 0x30));
    omObjMotionRead(arg0, 4, CharMotionDataNumGet(character, m205_crankMotTbl[character][1]));
    m205_MotSet(arg0, 0, 1);
    Hu3DMotionTimeSet(arg0->model[0], 30.0f);
    Hu3DMotionSpeedSet(arg0->model[0], 1.0f);
    Hu3DMotionTimeSet(arg0->model[1], 30.0f);
    Hu3DMotionSpeedSet(arg0->model[1], 1.0f);
    arg0->model[1] = Hu3DModelRead(0x260001, 0xD9);
    arg0->model[2] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(arg0->model[2], 0x80000000, 0);
    Hu3DModelRemakeStatic(arg0->model[2]);
    Hu3DModelDynamicFree(arg0->model[2]);
    HuTranslateF(Hu3DData[arg0->model[2]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[2], HU3D_CAM0);
    arg0->trans.x = -600.0f;
    arg0->trans.y = 50.0f;
    arg0->trans.z = -600.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[2], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    m205_crankComWait = 20;
    m205_crankComDelay = 0;
    m205_crankComLevel = GwPlayer[arg0->work[0]].cpu_difficulty;
    m205_objWorkTbl[4].unk_0A = m205_RandGet(2);
    arg0->work[3] = GwPlayer[arg0->work[0]].pad;
    arg0->func = m205_CrankObjMain;
}

void m205_CrankObjCreate(void) {
    omObjData *obj;
    UnkCrazyCogsCog *cog = &m205_objWorkTbl[4];
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
    obj = omAddObj(0x2BC, 3, 4, -1, m205_CrankObjInit);
    obj->work[0] = playerIndex;
    cog->obj = obj;
    m205_crankPlayerNo = obj->work[0];
    m205_crankChr = GwPlayer[obj->work[0]].chr;
}

void m205_TeamDummyObjMain(omObjData *arg0) {
}

void m205_TeamDummyObjInit(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[25])[arg0->work[1]];
    u16 character = GwPlayer[arg0->work[0]].chr;
    f32 angle;

    arg0->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharMotTbl[character][0], 0x2B9);
    omObjMotionRead(arg0, 1, CharMotionDataNumGet(character, 0));
    omObjMotionRead(arg0, 2, CharMotionDataNumGet(character, 2));
    m205_MotSet(arg0, 1, 2);
    arg0->model[1] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(arg0->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(arg0->model[1]);
    Hu3DModelDynamicFree(arg0->model[1]);
    HuTranslateF(Hu3DData[arg0->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    angle = m205_AngleAdd(0.0f, (s16)cog->timer * 120);
    arg0->trans.x = sindf(angle) * 90.0f;
    arg0->trans.y = 28.0f;
    arg0->trans.z = cosdf(angle) * 90.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    arg0->func = m205_TeamDummyObjMain;
}

void m205_TeamDummyObjCreate(void) {
    omObjData *obj;
    s8 positions[3];
    s8 available[3];
    s8 i;
    s8 j;
    s8 count;
    s8 position;
    s32 cogIndex;
    u16 playerIndex;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 3; i++) {
        positions[i] = i;
        available[i] = 1;
    }
    playerIndex = 0;
    cogIndex = 0;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
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
            cog = &(&m205_objWorkTbl[25])[cogIndex];
            obj = omAddObj(0x320, 3, 3, -1, m205_TeamDummyObjInit);
            obj->work[0] = playerIndex;
            cog->obj = obj;
            obj->work[1] = cogIndex;
            position = m205_RandGet(3 - cogIndex);
            cog->timer = positions[position];
            available[positions[position]] = 0;
            j = 0;
            count = 0;
            for (; j < 3; j++) {
                if (available[j] != 0) {
                    positions[count] = j;
                    count++;
                }
            }
            cogIndex++;
        }
    }
}

void m205_PosRotate(f32 *x, f32 *z, f32 angle) {
    f32 radius = sqrtf(*x * *x + *z * *z);
    f32 direction = m205_AngleAdd(atan2df(*x, *z), angle);

    *x = radius * sindf(direction);
    *z = radius * cosdf(direction);
}

void m205_TeamStepSeUpdate(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[25])[arg0->work[1]];

    if (arg0->work[2] == 0) {
        if (cog->unk_16 != 0) {
            HuAudFXStop(cog->unk_16);
        }
        cog->unk_16 = PlayerFXPlay(0x28, ((s16 *)arg0->work)[1]);
    }
    arg0->work[2] = (arg0->work[2] + 1) % 11;
}

void m205_TeamIntroUpdate(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[5])[arg0->work[1]];
    UnkCrazyCogsCog *introCog = &(&m205_objWorkTbl[25])[arg0->work[1]];

    switch (cog->unk_12) {
        case 0:
            cog->unk_16++;
            if (cog->unk_16 == 20) {
                cog->unk_12 = 1;
                cog->unk_16 = 0;
                m205_crankDir = 1;
                m205_MotSet(introCog->obj, 2, 2);
            }
            break;
        case 1:
            introCog->obj->rot.y = m205_teamDummyRotTbl[(s16)introCog->timer];
            m205_TeamStepSeUpdate(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 40) {
                cog->unk_12 = 4;
                cog->unk_16 = 0;
                m205_crankDir = 2;
            }
            break;
        case 2:
            introCog->obj->rot.y = m205_AngleAdd(m205_teamDummyRotTbl[(s16)introCog->timer], -180.0f);
            m205_TeamStepSeUpdate(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 40) {
                cog->unk_12++;
                cog->unk_16 = 0;
                m205_crankDir = 1;
            }
            break;
        case 3:
            introCog->obj->rot.y = m205_teamDummyRotTbl[(s16)introCog->timer];
            m205_TeamStepSeUpdate(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12++;
                cog->unk_16 = 0;
                m205_crankDir = 2;
            }
            break;
        case 4:
            introCog->obj->rot.y = m205_AngleAdd(m205_teamDummyRotTbl[(s16)introCog->timer], -180.0f);
            m205_TeamStepSeUpdate(arg0);
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12++;
                cog->unk_16 = 0;
                m205_crankDir = 0;
                arg0->trans.x = introCog->obj->trans.x;
                arg0->trans.y = introCog->obj->trans.y;
                arg0->trans.z = introCog->obj->trans.z;
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(introCog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(introCog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 5:
            switch ((s16)introCog->timer) {
                case 0:
                    HuPadStkY[arg0->work[3]] = -67;
                    break;
                case 1:
                    HuPadStkX[arg0->work[3]] = 60;
                    HuPadStkY[arg0->work[3]] = 30;
                    break;
                case 2:
                    HuPadStkX[arg0->work[3]] = -60;
                    HuPadStkY[arg0->work[3]] = 30;
                    break;
            }
            cog->unk_16++;
            if (cog->unk_16 == 18) {
                cog->unk_12 = 0;
                m205_introDoneF = 1;
            }
            break;
        case 6:
            cog->unk_16++;
            if (cog->unk_16 == 30) {
                cog->unk_12 = 0;
                m205_introDoneF = 1;
            }
            break;
    }
}

void m205_TeamBlownUpdate(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[5])[arg0->work[1]];

    switch (cog->unk_12) {
        case 0:
            if (cog->unk_10 != 0) {
                cog->unk_44.x = arg0->trans.x + 650.0f;
                cog->unk_1C = -5.0f;
                cog->unk_20 = 180.0f;
            } else {
                cog->unk_44.x = arg0->trans.x - 650.0f;
                cog->unk_1C = 5.0f;
                cog->unk_20 = 0;
            }
            cog->unk_44.y = arg0->trans.y;
            cog->unk_12++;
            MgPlayerMotSet(arg0, 0x12);
            Hu3DData[arg0->model[0]].motTime = 0;
            Hu3DData[arg0->model[0]].motSpeed = 0;
            m205_PadClear(arg0->work[1]);
            MgPlayerObjMain(arg0);
            HuAudFXStop((s16)(arg0->work[3] * 2 + 2));
            HuAudPlayerFXPlay(0x325, ((s16 *)arg0->work)[1]);
            PlayerFXPlay(0x286, ((s16 *)arg0->work)[1]);
            m205_teamBlownTimerTbl[arg0->work[1]] = 0;
        case 1:
            cog->unk_20 = m205_AngleAdd(cog->unk_20, cog->unk_1C);
            arg0->trans.x = cosdf(cog->unk_20) * 650.0f + cog->unk_44.x;
            arg0->trans.y = sindf(cog->unk_20) * 590.0f + cog->unk_44.y;
            arg0->rot.y = m205_AngleAdd(arg0->rot.y, 33.0f);
            arg0->rot.x = m205_AngleAdd(arg0->rot.x, 33.0f);
            m205_teamBlownTimerTbl[arg0->work[1]]++;
            if (arg0->trans.y < 0.0f) {
                cog->unk_12++;
            }
            break;
        case 2:
            return;
    }
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, m205_FloorYGet(arg0), arg0->trans.z);
}

void m205_TeamComInput(omObjData *arg0) {
    CrazyCogsCpuMovement *movement = &m205_teamComMoveTbl[arg0->work[1]];
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[5])[arg0->work[1]];
    UnkCrazyCogsCog *obstacle;
    omObjData *obj;
    s16 i;

    movement->xTimer++;
    if ((s8)movement->xTimer >= movement->xDuration) {
        movement->xTimer = 0;
        movement->xDuration = m205_RandGet(30) + 10;
        movement->xStick = m205_RandGet(20) + 30;
        movement->xStick = m205_RandGet(2) == 1 ? movement->xStick : -movement->xStick;
        cog->unk_0C = 0;
    }
    movement->zTimer++;
    if ((s8)movement->zTimer >= movement->zDuration) {
        movement->zTimer = 0;
        movement->zDuration = m205_RandGet(30) + 10;
        movement->zStick = m205_RandGet(20) + 30;
        movement->zStick = m205_RandGet(2) == 1 ? movement->zStick : -movement->zStick;
        cog->unk_0C = 0;
    }
    if (cog->unk_0C == 0 && cog->unk_14 != 0) {
        for (i = 0; i < 7; i++) {
            obstacle = &(&m205_objWorkTbl[8])[i];
            if ((s16)obstacle->timer != 0) {
                obj = obstacle->obj;
                if (arg0->trans.x < cog->unk_14 + obj->trans.x &&
                    arg0->trans.x > obj->trans.x - cog->unk_14 &&
                    arg0->trans.z < cog->unk_14 + obj->trans.z &&
                    arg0->trans.z > obj->trans.z - cog->unk_14) {
                    if (arg0->trans.x >= 0.0f && arg0->trans.z < 0.0f) {
                        movement->xStick = -40;
                        movement->zStick = -40;
                    } else if (arg0->trans.x >= 0.0f && arg0->trans.z >= 0.0f) {
                        movement->xStick = -40;
                        movement->zStick = 40;
                    } else if (arg0->trans.x < 0.0f && arg0->trans.z >= 0.0f) {
                        movement->xStick = 40;
                        movement->zStick = 40;
                    } else if (arg0->trans.x < 0.0f && arg0->trans.z < 0.0f) {
                        movement->xStick = 40;
                        movement->zStick = -40;
                    }
                    movement->zTimer = 0;
                    movement->xTimer = 0;
                    movement->zDuration = 17;
                    movement->xDuration = 17;
                    cog->unk_0C = 1;
                }
            }
        }
    }
    HuPadStkX[arg0->work[3]] = movement->xStick;
    HuPadStkY[arg0->work[3]] = movement->zStick;
}

void m205_TeamObjMain(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[5])[arg0->work[1]];
    MgPlayerWork *work = arg0->data;

    if (cog->unk_0E != 0) {
        m205_TeamBlownUpdate(arg0);
        return;
    }
    if (m205_rumbleReqTbl[arg0->work[0]] != 0) {
        if (!(GwPlayer[arg0->work[0]].stat & 1)) {
            omVibrate(((s16 *)arg0->work)[1], 10, 0, 10);
        }
        m205_rumbleReqTbl[arg0->work[0]] = 0;
    }
    if (m205_phase != 2) {
        m205_PadClear(arg0->work[0]);
        if (m205_phase == 0) {
            m205_TeamIntroUpdate(arg0);
        }
        if (m205_phase == 3) {
            work->unk3C = 0;
            work->unk40 = 0;
        }
        if (m205_resultMot > 0) {
            MgPlayerMotSet(arg0, 0xD);
            HuAudCharVoicePlay((m205_voiceChrTbl[GwPlayer[arg0->work[0]].chr] << 16) | 0x30);
        }
    } else {
        if (GwPlayer[arg0->work[0]].stat & 1) {
            m205_TeamComInput(arg0);
        }
        switch (m205_crankDir) {
            case 0:
                break;
            case 1:
                m205_PosRotate(&arg0->trans.x, &arg0->trans.z, -3.3f);
                if (((HuPadStkX[arg0->work[3]] < 0) ? -HuPadStkX[arg0->work[3]] : HuPadStkX[arg0->work[3]]) < 20 &&
                    ((HuPadStkY[arg0->work[3]] < 0) ? -HuPadStkY[arg0->work[3]] : HuPadStkY[arg0->work[3]]) < 20) {
                    work->unk3C = m205_AngleAdd(work->unk3C, -3.3f);
                }
                break;
            case 2:
                m205_PosRotate(&arg0->trans.x, &arg0->trans.z, 3.3f);
                if (((HuPadStkX[arg0->work[3]] < 0) ? -HuPadStkX[arg0->work[3]] : HuPadStkX[arg0->work[3]]) < 20 &&
                    ((HuPadStkY[arg0->work[3]] < 0) ? -HuPadStkY[arg0->work[3]] : HuPadStkY[arg0->work[3]]) < 20) {
                    work->unk3C = m205_AngleAdd(work->unk3C, 3.3f);
                }
                break;
        }
    }
    MgPlayerObjMain(arg0);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

void m205_TeamObjInit(omObjData *arg0) {
    CrazyCogsCpuMovement *movement = &m205_teamComMoveTbl[arg0->work[1]];
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[5])[arg0->work[1]];
    u16 character = GwPlayer[arg0->work[0]].chr;
    s32 modelFile = omCharModelNoTbl[character][0];
    s32 motionFile = omCharMotTbl[character][0];
    MgPlayerWork *work;

    MgPlayerParamReset();
    MgPlayerCreate(arg0, modelFile, motionFile, ((u16 *)arg0->work)[1], 0x299, 0x289);
    work = arg0->data;
    work->unkEC = 0;
    Hu3DModelObjAttrSet(arg0->model[1], 0x80000000, 0);
    Hu3DModelAttrSet(arg0->model[1], 0x60, 0x20);
    Hu3DModelRemakeStatic(arg0->model[1]);
    Hu3DModelDynamicFree(arg0->model[1]);
    arg0->model[3] = Hu3DModelRead(3, 0x2BD);
    arg0->model[4] = Hu3DModelRead(4, 0x2BD);
    MgPlayerMotLoad(arg0, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(arg0, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(arg0, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(arg0, 0x12, CharMotionDataNumGet(character, 0xF), 2, 0);
    MgPlayerMotRead(arg0, 3, CharMotionDataNumGet(character, 0x1D), 1, 0);
    MgPlayerMotRead(arg0, 4, CharMotionDataNumGet(character, 0x1E), 1, 0);
    MgPlayerMotLoad(arg0, 0xD, CharMotionDataNumGet(character, 0x30), 1, 120);
    MgPlayerMotSet(arg0, 0);
    mgFieldStat = 1;
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[3], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[4], HU3D_CAM0);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    arg0->trans.x = 700.0f;
    arg0->trans.y = 28.0f;
    arg0->trans.z = 700.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    movement->xTimer = movement->xDuration = movement->xStick = 0;
    movement->zTimer = movement->zDuration = movement->zStick = 0;
    switch (GwPlayer[arg0->work[0]].cpu_difficulty) {
        case 0:
            cog->unk_14 = 0;
            break;
        case 1:
            cog->unk_14 = 33;
            break;
        case 2:
            cog->unk_14 = 66;
            break;
        case 3:
            cog->unk_14 = 100;
            break;
    }
    arg0->work[3] = GwPlayer[arg0->work[0]].pad;
    arg0->work[2] = 0;
    arg0->func = m205_TeamObjMain;
}

void m205_TeamObjCreate(void) {
    omObjData *obj;
    s16 count;
    u16 playerIndex;
    s32 cogIndex;
    s16 i;
    UnkCrazyCogsCog *cog;

    count = 0;
    playerIndex = 0;
    cogIndex = 0;
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
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
            cog = &(&m205_objWorkTbl[5])[cogIndex];
            obj = omAddObj(0x384, 9, 60, -1, m205_TeamObjInit);
            obj->work[0] = playerIndex;
            cog->obj = obj;
            obj->work[1] = cogIndex;
            cogIndex++;
            mgPlayerObjTbl[mgPlayerObjNum] = obj;
            mgPlayerObjNum++;
            m205_teamChrTbl[count] = GwPlayer[obj->work[0]].chr;
            m205_teamPlayerNoTbl[count] = obj->work[0];
            count++;
        }
    }
}

void m205_BlastObjMain(omObjData *arg0) {
}

void m205_BlastObjInit(omObjData *arg0) {
    arg0->model[0] = Hu3DModelRead2(0x260008, 0x89);
    Hu3DModelObjAttrSet(arg0->model[0], 0x80000000, 0);
    Hu3DModelRemakeStatic(arg0->model[0]);
    Hu3DModelDynamicFree(arg0->model[0]);
    HuTranslateF(Hu3DData[arg0->model[0]].mtx, 0.0f, 0.0f, 0.0f);
    arg0->trans.x = arg0->trans.z = arg0->trans.y = 1000.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 2.0f;
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    arg0->rot.x = 290.0f;
    arg0->rot.y = arg0->rot.z = 0.0f;
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DMotionSpeedSet(arg0->model[0], 2.0f);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    arg0->func = m205_BlastObjMain;
}

void m205_BlastObjCreateAll(void) {
    s8 i;
    UnkCrazyCogsCog *cog;

    for (i = 0; i < 5; i++) {
        cog = &(&m205_objWorkTbl[18])[i];
        cog->obj = omAddObj(0x5DC, 1, 1, -1, m205_BlastObjInit);
        cog->obj->work[0] = i;
    }
}

void m205_BlastStart(omObjData *arg0) {
    omObjData *obj = (&m205_objWorkTbl[18])[m205_blastNo].obj;

    HuAudFXPlay(0x321);
    obj->trans.x = arg0->trans.x;
    obj->trans.y = m205_FloorYGet(arg0) + arg0->trans.y + 70.0f;
    obj->trans.z = arg0->trans.z + 70.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    m205_blastNo = (m205_blastNo + 1) % 5;
}

void m205_KillerReset(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[8])[arg0->work[0]];
    s32 offset;

    if (arg0->work[0] < 7) {
        if (arg0->trans.x > 0.0f) {
            if (arg0->trans.z > -50.0f) {
                m205_panelShakeTbl[3] = 1;
            } else {
                m205_panelShakeTbl[1] = 1;
            }
        } else {
            if (arg0->trans.z > -50.0f) {
                m205_panelShakeTbl[2] = 1;
            } else {
                m205_panelShakeTbl[0] = 1;
            }
        }
    }
    arg0->trans.x = cog->unk_44.x;
    arg0->trans.y = cog->unk_44.y;
    if (arg0->work[0] == 9) {
        cog->unk_18 = m205_RandGet(5);
        if (m205_RandGet(2) != 0) {
            cog->unk_18 = 0.0f - cog->unk_18;
        }
        arg0->trans.z = -1300.0f;
    } else {
        arg0->trans.x = cog->unk_44.x;
        arg0->trans.z = 0;
    }
    m205_killerShadowScaleTbl[arg0->work[0]] = 0.1f;
    cog->timer = 0;
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (arg0->work[0] < 4) {
        offset = m205_RandGet(54);
        offset = offset * 10 + m205_RandGet(100);
        if (m205_RandGet(2) != 0) {
            arg0->trans.x = offset + arg0->trans.x;
        } else {
            arg0->trans.x -= offset;
        }
    } else if ((arg0->work[0] < 3) & (arg0->work[0] < 7)) {
        offset = m205_RandGet(20);
        offset = offset * 10 + m205_RandGet(100);
        if (m205_RandGet(2) != 0) {
            arg0->trans.x = offset + arg0->trans.x;
        } else {
            arg0->trans.x -= offset;
        }
        offset = m205_RandGet(20);
        offset = offset * 10 + m205_RandGet(100);
        if (m205_RandGet(2) != 0) {
            arg0->trans.z = offset + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    } else if ((arg0->work[0] == 7) & (arg0->work[0] == 8)) {
        offset = m205_RandGet(20);
        offset = offset * 10 + m205_RandGet(100);
        if (arg0->work[0] == 7) {
            arg0->trans.x -= offset;
        } else {
            arg0->trans.x = offset + arg0->trans.x;
        }
        offset = m205_RandGet(30) * 10;
        if (m205_RandGet(3) != 0) {
            arg0->trans.z = offset + (f32)m205_RandGet(200) + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    } else if (arg0->work[0] == 9) {
        offset = m205_RandGet(150);
        if (m205_RandGet(2) != 0) {
            arg0->trans.x -= offset;
        } else {
            arg0->trans.x = offset + arg0->trans.x;
        }
        offset = m205_RandGet(150);
        if (m205_RandGet(2) != 0) {
            arg0->trans.z = offset + arg0->trans.z;
        } else {
            arg0->trans.z -= offset;
        }
    }
}

void m205_KillerHitCheck(omObjData *arg0) {
    s16 candidates[3];
    UnkCrazyCogsCog *cog;
    MgPlayerWork *work;
    s16 count;
    s16 i;
    f32 x;
    f32 z;
    f32 distance;
    u32 obstacleIndex;

    if (m205_phase != 2) {
        return;
    }
    count = 0;
    for (i = 0; i < 3; i++) {
        cog = &(&m205_objWorkTbl[5])[i];
        work = cog->obj->data;
        if (cog->unk_0E == 0 && arg0->trans.y <= work->unk34) {
            x = arg0->trans.x - cog->obj->trans.x;
            z = arg0->trans.z - cog->obj->trans.z;
            distance = sqrtf(x * x + z * z);
            if (distance < work->unk48 + 40.0f) {
                candidates[count] = ((s16 *)cog->obj->work)[3];
                count++;
            }
        }
    }
    if (count != 0) {
        cog = &(&m205_objWorkTbl[5])[candidates[(s16)m205_RandGet(count)]];
        m205_BlastStart(arg0);
        if (!(GwPlayer[cog->obj->work[0]].stat & 1)) {
            omVibrate(((s16 *)cog->obj->work)[1], 20, 0, 20);
        }
        m205_KillerReset(arg0);
        cog->unk_0E = 1;
        m205_teamOutNum++;
        obstacleIndex = arg0->work[0];
        if (obstacleIndex < 2) {
            cog->unk_10 = 1;
        } else if (obstacleIndex < 4) {
            cog->unk_10 = 0;
        } else {
            if (arg0->trans.x > cog->obj->trans.x) {
                cog->unk_10 = 0;
            } else {
                cog->unk_10 = 1;
            }
        }
    }
}

s8 m205_KillerOutCheck(omObjData *arg0) {
    s8 result;

    switch (arg0->work[0]) {
        case 4:
        case 5:
        case 6:
            if (arg0->trans.x > -600.0f && arg0->trans.x < 600.0f && arg0->trans.z > -350.0f && arg0->trans.z < 600.0f) {
                result = 0;
            } else {
                result = 1;
                if (arg0->trans.x > -350.0f && arg0->trans.x < 600.0f && arg0->trans.z > -600.0f && arg0->trans.z < -350.0f) {
                    result = 0;
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
            result = 1;
            if (arg0->trans.z > -350.0f) {
                if (arg0->trans.z < 500.0f) {
                    result = 0;
                }
            }
            break;
        default:
            result = 1;
            break;
    }
    return result;
}

void m205_KillerDrift(omObjData *arg0, s32 arg1) {
    CrazyCogsMovement *movement;

    if (arg0->work[0] < 7) {
        movement = &m205_killerDriftTbl[arg0->work[0]];
        if (m205_KillerOutCheck(arg0) != 0) {
            movement->xTimer = 0;
            movement->xDirection *= -1;
            movement->zTimer = 0;
            movement->zDirection *= -1;
        } else {
            movement->xTimer++;
            if ((s8)movement->xTimer >= movement->xDuration) {
                movement->xTimer = 0;
                movement->xDuration = m205_RandGet(20) + 5;
                movement->xSpeed = m205_RandGet(8);
                movement->xDirection = m205_RandGet(2) == 1 ? 1 : -1;
            }
            movement->zTimer++;
            if ((s8)movement->zTimer >= movement->zDuration) {
                movement->zTimer = 0;
                movement->zDuration = m205_RandGet(20) + 5;
                movement->zSpeed = m205_RandGet(8);
                movement->zDirection = m205_RandGet(2) == 1 ? 1 : -1;
            }
        }
        switch (arg0->work[0]) {
            case 4:
            case 5:
            case 6:
                arg0->trans.x = movement->xSpeed * movement->xDirection + arg0->trans.x;
            case 0:
            case 1:
            case 2:
            case 3:
                arg0->trans.z = movement->zSpeed * movement->zDirection + arg0->trans.z;
                break;
        }
    }
}

void m205_RumbleReqSetAll(void) {
    m205_rumbleReqTbl[0] = 1;
    m205_rumbleReqTbl[1] = 1;
    m205_rumbleReqTbl[2] = 1;
    m205_rumbleReqTbl[3] = 1;
}

void m205_KillerObjMain(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[8])[arg0->work[0]];

    m205_KillerHitCheck(arg0);
    if ((s16)cog->timer == 0) {
        return;
    }
    switch (m205_phase) {
        case 0:
        case 1:
            break;
        case 2:
            if (arg0->trans.y > 25.0f) {
                arg0->trans.x -= cog->unk_18;
                arg0->trans.y -= cog->unk_1C;
                m205_killerShadowScaleTbl[arg0->work[0]] += cog->unk_20;
            } else {
                m205_BlastStart(arg0);
                m205_KillerReset(arg0);
                m205_RumbleReqSetAll();
            }
            if (arg0->work[0] == 9) {
                if (arg0->trans.z < 600.0f) {
                    arg0->trans.z += 35.0f;
                } else {
                    m205_KillerReset(arg0);
                    m205_RumbleReqSetAll();
                }
            }
            m205_KillerDrift(arg0, 0);
            break;
        default:
            if ((s16)cog->timer != 0) {
                m205_BlastStart(arg0);
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                cog->timer = 0;
            }
            break;
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, m205_FloorYGet(arg0), arg0->trans.z);
    if (m205_killerShadowScaleTbl[arg0->work[0]] > 1.0f) {
        m205_killerShadowScaleTbl[arg0->work[0]] = 1.0f;
    }
    Hu3DModelScaleSet(arg0->model[1], m205_killerShadowScaleTbl[arg0->work[0]], 1.0f,
                      m205_killerShadowScaleTbl[arg0->work[0]]);
}

void m205_KillerObjInit(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &(&m205_objWorkTbl[8])[arg0->work[0]];
    f32 xSpeed;
    f32 angle;
    u32 cogIndex;

    if (arg0->work[0] == 0) {
        arg0->model[0] = Hu3DModelRead2(0xA0062, 0x89);
        Hu3DModelRemakeStatic(arg0->model[0]);
        Hu3DModelDynamicFree(arg0->model[0]);
        arg0->model[1] = Hu3DModelRead2(0, 0x14C9);
        Hu3DModelObjAttrSet(arg0->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(arg0->model[1]);
        Hu3DModelDynamicFree(arg0->model[1]);
        HuTranslateF(Hu3DData[arg0->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        m205_killerMdlTbl[0] = arg0->model[0];
        m205_killerMdlTbl[1] = arg0->model[1];
    } else {
        arg0->model[0] = Hu3DModelLink((s16)m205_killerMdlTbl[0]);
        arg0->model[1] = Hu3DModelLink((s16)m205_killerMdlTbl[1]);
    }
    if (arg0->work[0] < 4) {
        angle = 60.0f;
        xSpeed = cosdf(0.0f) * cosdf(angle) * 36.0f;
        cog->unk_1C = sindf(angle) * 36.0f;
        cogIndex = arg0->work[0];
        if (cogIndex < 2) {
            cog->unk_18 = 0.0f - xSpeed;
            cog->unk_44.x = 0.0f - cosdf(0.0f) * cosdf(angle) * 2900.0f;
            cog->unk_50.y = 90.0f;
            cog->unk_50.z = 300.0f;
        } else if (cogIndex < 4) {
            cog->unk_18 = xSpeed;
            cog->unk_44.x = cosdf(0.0f) * cosdf(angle) * 2900.0f;
            cog->unk_50.y = 270.0f;
            cog->unk_50.z = angle;
        }
        cog->unk_44.y = sindf(angle) * 2900.0f;
    } else if (arg0->work[0] < 7) {
        cog->unk_18 = 0;
        cog->unk_1C = 36.0f;
        cog->unk_44.x = 0;
        cog->unk_44.y = 2900.0f;
        cog->unk_50.x = 90.0f;
    }
    if (arg0->work[0] == 7) {
        cog->unk_18 = 45.0f;
        cog->unk_1C = 45.0f;
        cog->unk_44.x = 1400.0f;
        cog->unk_44.y = 2000.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 270.0f;
        cog->unk_50.z = 45.0f;
    }
    if (arg0->work[0] == 8) {
        cog->unk_18 = -45.0f;
        cog->unk_1C = 45.0f;
        cog->unk_44.x = -1400.0f;
        cog->unk_44.y = 2000.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 90.0f;
        cog->unk_50.z = 315.0f;
    }
    if (arg0->work[0] == 9) {
        cog->unk_18 = 5.0f;
        cog->unk_1C = 30.0f;
        cog->unk_44.x = 0;
        cog->unk_44.y = 1800.0f;
        cog->unk_44.z = 0;
        cog->unk_50.y = 0;
        cog->unk_50.x = 30.0f;
    }
    arg0->trans.x = cog->unk_44.x;
    arg0->trans.y = cog->unk_44.y;
    arg0->trans.z = cog->unk_44.z;
    arg0->rot.x = cog->unk_50.x;
    arg0->rot.y = cog->unk_50.y;
    arg0->rot.z = cog->unk_50.z;
    arg0->scale.x = arg0->scale.y = arg0->scale.z = 1.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(arg0->model[0], arg0->rot.x, arg0->rot.y, arg0->rot.z);
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    cog->unk_20 = 0.9f / 80.0f;
    Hu3DModelScaleSet(arg0->model[1], 0.1f, 1.0f, 0.1f);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(arg0->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(arg0->model[1], HU3D_CAM0);
    m205_KillerReset(arg0);
    arg0->func = m205_KillerObjMain;
}

void m205_KillerObjCreateAll(void) {
    s16 i;
    UnkCrazyCogsCog *cog;
    omObjData *obj;

    for (i = 0; i < 10; i++) {
        cog = &(&m205_objWorkTbl[8])[i];
        obj = omAddObj(0x578, 20, 0, -1, m205_KillerObjInit);
        obj->work[0] = i;
        cog->obj = obj;
    }
}

void m205_KillerComQueueAdd(UnkCrazyCogsCog *cog) {
    if (cog->obj->work[0] < 4) {
        return;
    }
    m205_comKillerCnt++;
    switch (m205_crankComLevel) {
        case 0:
            return;
        case 1:
            if ((s16)(m205_comKillerCnt % 3) != 1) {
                return;
            }
            break;
        case 2:
            if ((s16)(m205_comKillerCnt % 3) == 1) {
                return;
            }
            break;
    }
    m205_comQueueTbl[m205_comQueueNum] = ((s8 *)cog->obj->work)[3];
    m205_comQueueNum++;
}

void m205_KillerSpawnObjMain(omObjData *arg0) {
    UnkCrazyCogsCog *cog;
    s16 cogIndex;
    s16 i;

    if (m205_phase != 2) {
        return;
    }
    if (m205_killerSpawnTimer >= m205_killerSpawnInterval) {
        m205_killerSpawnTimer = 0;
        m205_killerSpawnInterval = m205_RandGet(2) == 0 ? 30 : m205_RandGet(10) + 30;
        cogIndex = m205_RandGet(7);
        cog = &(&m205_objWorkTbl[8])[cogIndex];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            m205_KillerComQueueAdd(cog);
            Hu3DModelAttrSet(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        } else {
            cogIndex++;
            for (i = 0; i < 6; cogIndex = (cogIndex + 1) % 7, i++) {
                if (cogIndex == 7) {
                    cogIndex--;
                    i--;
                } else {
                    cog = &(&m205_objWorkTbl[8])[cogIndex];
                    if ((s16)cog->timer == 0) {
                        cog->timer = 1;
                        m205_KillerComQueueAdd(cog);
                        Hu3DModelAttrSet(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        break;
                    }
                }
            }
        }
    }
    if ((s16)(m205_killerSpawnTimer % 27) == 0 && m205_RandGet(5) == 0) {
        cog = &m205_objWorkTbl[15];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            Hu3DModelAttrSet(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    if ((m205_killerSpawnTimer + 15) % 27 == 0 && m205_RandGet(5) == 0) {
        cog = &m205_objWorkTbl[16];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            Hu3DModelAttrSet(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    if ((s16)(m205_killerSpawnTimer % 15) == 0 && m205_RandGet(5) == 0) {
        cog = &m205_objWorkTbl[17];
        if ((s16)cog->timer == 0) {
            cog->timer = 1;
            Hu3DModelAttrSet(cog->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(cog->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
    m205_killerSpawnTimer++;
}

void m205_KillerSpawnObjInit(omObjData *arg0) {
    s16 i;

    m205_killerSpawnTimer = 0;
    m205_killerSpawnInterval = 5;

    for (i = 0; i < 0x32; i++) {
        m205_comQueueTbl[i] = -1;
    }

    m205_comQueueTbl[i] = -1;
    m205_comQueueNum = 0;
    m205_comQueueNo = 0;
    m205_comKillerCnt = 0;

    arg0->model[0] = -1;
    arg0->func = m205_KillerSpawnObjMain;
}

void m205_KillerSpawnObjCreate(void) {
    m205_objWorkTbl[23].obj = omAddObj(0x514, 1, 1, -1, m205_KillerSpawnObjInit);
}

void m205_IntroKillerIdle(omObjData *arg0) {
}

void m205_IntroKillerRiseIdle(omObjData *arg0) {
}

void m205_IntroKillerRiseObjMain(omObjData *arg0) {
    if (m205_introKillerWork->obj->trans.y >= 1500.0f) {
        m205_introKillerWork->obj->trans.x = 0.0f;
        m205_introKillerWork->obj->trans.y = 2400.0f;
        m205_introKillerWork->obj->trans.z = 560.0f;
        m205_introKillerWork->obj->rot.x = m205_introKillerWork->unk_50.x;
        m205_introKillerWork->obj->rot.y = m205_introKillerWork->unk_50.y;
        m205_introKillerWork->obj->rot.z = m205_introKillerWork->unk_50.z;
        m205_killerShadowScaleTbl[m205_introKillerWork->obj->work[0]] = 0.2f;
        arg0->func = m205_IntroKillerRiseIdle;
    } else {
        m205_introKillerWork->obj->trans.y += 42.0f;
        m205_introKillerWork->obj->trans.z += 14.0f;
    }
}

void m205_IntroKillerObjMain(omObjData *arg0) {
    omObjData *obj = m205_introKillerWork->obj;

    m205_introKillerTimer++;
    if ((s16)m205_introKillerTimer == 15) {
        HuAudFXPlay(0x326);
    }
    if (m205_introKillerTimer >= 25 && m205_introKillerTimer < 100) {
        obj->trans.x -= 30.0f;
        obj->trans.y -= 8.0f;
        obj->trans.z += 30.0f;
        if (obj->trans.z >= 900.0f) {
            obj->trans.x = 0.0f;
            obj->trans.y = m205_introKillerWork->unk_44.y;
            obj->trans.z = 0.0f;
            obj->rot.x = 90.0f;
            obj->rot.y = 0.0f;
            obj->rot.z = 0.0f;
            m205_introKillerTimer = 100;
        }
    }
    if ((s16)m205_introKillerTimer >= 100) {
        if (obj->trans.y > 25.0f) {
            obj->trans.x -= m205_introKillerWork->unk_18;
            obj->trans.y -= m205_introKillerWork->unk_1C + 10.0f;
            m205_killerShadowScaleTbl[obj->work[0]] += m205_introKillerWork->unk_20;
        } else {
            m205_BlastStart(obj);
            m205_KillerReset(obj);
            m205_RumbleReqSetAll();
            m205_panelShakeTbl[0] = m205_panelShakeTbl[1] = m205_panelShakeTbl[2] = m205_panelShakeTbl[3] = 1;
            arg0->func = m205_IntroKillerIdle;
        }
        Hu3DModelPosSet(obj->model[1], obj->trans.x, m205_FloorYGet(obj), obj->trans.z);
        Hu3DModelScaleSet(obj->model[1], m205_killerShadowScaleTbl[obj->work[0]], 1.0f, m205_killerShadowScaleTbl[obj->work[0]]);
    }
}

void m205_IntroKillerObjInit(omObjData *arg0) {
    UnkCrazyCogsCog *cog = &m205_objWorkTbl[12];

    m205_introKillerWork = cog;
    m205_introKillerTimer = 0;
    m205_introKillerY = 820.0f;
    cog->obj->trans.x = 400.0f;
    cog->obj->trans.y = 900.0f;
    cog->obj->trans.z = 300.0f;
    cog->obj->rot.x = 15.0f;
    cog->obj->rot.y = 315.0f;
    cog->obj->rot.z = 0.0f;
    Hu3DModelPosSet(cog->obj->model[0], cog->obj->trans.x,
                    cog->obj->trans.y, cog->obj->trans.z);
    Hu3DModelRotSet(m205_introKillerWork->obj->model[0], m205_introKillerWork->obj->rot.x,
                    m205_introKillerWork->obj->rot.y, m205_introKillerWork->obj->rot.z);
    Hu3DModelAttrSet(m205_introKillerWork->obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet(m205_introKillerWork->obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    arg0->model[0] = -1;
    arg0->func = m205_IntroKillerObjMain;
}

void m205_IntroKillerObjCreate(void) {
    m205_objWorkTbl[24].obj = omAddObj(0x640, 1, 1, -1, m205_IntroKillerObjInit);
}

void m205_CameraViewInit(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1648.63f;
        CRotM[i].x = 314.034f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -20.0f;
        CenterM[i].z = -50.0f;
    }
}

void m205_ExitObjMain(omObjData *arg0) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m205_ExitWaitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = m205_ExitObjMain;
    }
}

void m205_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        arg0->func = m205_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m205_MainObjMain(omObjData *arg0) {
    switch (m205_phase) {
        case 0:
            if (m205_introDoneF == 1) {
                GMesCreate(GMES_MES_4);
                m205_phase = 1;
                m205_mainTimer = 0;
            }
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m205_phase = 2;
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                m205_timer = 901;
            }
            m205_mainTimer++;
            if (m205_mainTimer == 57) {
                HuAudSeqPlay(0x2F);
            }
            break;
        case 2:
            if (m205_timer <= 0) {
                m205_phase = 3;
                GMesTimerEnd();
                m205_timer = 0;
            } else {
                m205_timer--;
                GMesTimerValueSet((m205_timer + 29) / 30);
                if (m205_teamOutNum == 3) {
                    GMesTimerEnd();
                    m205_phase = 3;
                } else {
                    break;
                }
            }
            m205_crankDir = 0;
            GMesCreate(GMES_MES_15);
            HuAudSeqFadeOut(120);
            break;
        case 3:
            if (GMesStatGet() == 0) {
                m205_timer = 0;
                if (m205_teamOutNum == 3) {
                    m205_phase = 4;
                } else {
                    m205_phase = 5;
                }
            }
            break;
        case 4:
            m205_timer++;
            if (m205_timer >= 15) {
                m205_resultMot = -1;
                HuAudSeqPlay(0x65);
                GMesCreate(GMES_MES_MG_WINNER, (s8)m205_crankChr);
                GwPlayer[(s8)m205_crankPlayerNo].bonusCoin = 10;
                m205_timer = 15;
                m205_phase = 6;
            }
            break;
        case 5:
            m205_timer++;
            if (m205_timer >= 15) {
                m205_resultMot = 1;
                HuAudSeqPlay(0x66);
                GMesCreate(GMES_MES_MG_WINNERS_3, m205_teamChrTbl[0], m205_teamChrTbl[1], m205_teamChrTbl[2]);
                GwPlayer[m205_teamPlayerNoTbl[0]].bonusCoin = 10;
                GwPlayer[m205_teamPlayerNoTbl[1]].bonusCoin = 10;
                GwPlayer[m205_teamPlayerNoTbl[2]].bonusCoin = 10;
                m205_timer = 15;
                m205_phase = 6;
            }
            break;
        case 6:
            m205_resultMot = 0;
            if (GMesStatGet() == 0) {
                m205_timer--;
                if (m205_timer <= 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    arg0->func = m205_ExitWaitObjMain;
                }
            }
            break;
    }
}

void m205_MainObjInit(omObjData *arg0) {
    MgFlowStatSet(MG_STATE_PLAY);
    m205_phase = 0;
    m205_teamOutNum = 0;
    m205_timer = 0;
    m205_introDoneF = 0;
    m205_crankLeverPos = 0;
    m205_resultMot = 0;
    m205_crankDir = 0;
    m205_rumbleReqTbl[0] = m205_rumbleReqTbl[1] = m205_rumbleReqTbl[2] = m205_rumbleReqTbl[3] = 0;
    m205_blastNo = 0;
    m205_CameraViewInit();
    m205_MapObjCreate();
    m205_CogCenterObjCreate();
    m205_CogAObjCreate();
    m205_CogBObjCreate();
    m205_CrankObjCreate();
    m205_TeamDummyObjCreate();
    m205_TeamObjCreate();
    m205_KillerSpawnObjCreate();
    m205_KillerObjCreateAll();
    m205_BlastObjCreateAll();
    m205_IntroKillerObjCreate();
    m205_PanelObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    arg0->func = m205_MainObjMain;
}

void m205_Dummy(void) {
}

void m205_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m205_cameraViewTbl[i].scissorX, m205_cameraViewTbl[i].scissorY,
                   m205_cameraViewTbl[i].scissorWidth, m205_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m205_cameraViewTbl[i].viewportScale.x, m205_cameraViewTbl[i].viewportScale.y,
                    m205_cameraViewTbl[i].viewportScale.z, m205_cameraViewTbl[i].viewportTranslate.x,
                    m205_cameraViewTbl[i].viewportTranslate.y, m205_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m205_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m205_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(32);
    omInitObjMan(50, 0);
    omGameSysInit();
    m205_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m205_fontMesTbl, 0);
    GMesFontMesCreate(m205_fontMesTbl, 1);
    omAddObj(0x7D0, 0, 0, -1, m205_MainObjInit);
    omAddObj(0x7D0, 0, 0, -1, m205_ExitCheckObjMain);
    m205_ObjWorkInit();
    MgFlowInit(&m205_mgFlow);
}

// Keep this table after the functions to preserve the original rodata order.
const s16 m205_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
