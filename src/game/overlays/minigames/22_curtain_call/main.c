#include "common.h"
#include "game/overlays/minigame.h"

// One entry of the 50 entry object table at m234_objWorkTbl. Layout
// derived from the table clear in m234_ObjWorkInit, which walks 50
// entries of 0x84 bytes.
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
} CurtainCallWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} CurtainCallCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ s16 unk_00;   // m234_timer
    /* 0x02 */ s8 unk_02[2]; // m234_questionTbl
} CurtainCallTimerWork;        // sizeof 0x4

// Fields of entries of m234_objWorkTbl accessed through separate
// symbols (aliased in undefined_syms.txt).
extern s16 m234_backSprAnim;        // [0].unk_40[0]
extern s16 m234_backSpr;        // [0].unk_40[1]
extern f32 m234_backSprX;        // [0].unk_44.x
extern f32 m234_backSprY;        // [0].unk_44.y
extern f32 m234_backSprZ;        // [0].unk_44.z
extern omObjData *m234_hostObj; // [11].obj
extern omObjData *m234_spotlightObj; // [13].obj
// Fields of m234_timerWork (aliased in undefined_syms.txt).
extern s16 m234_timer;
extern s8 m234_questionTbl[2];
// Fields at offsets 1 and 4 of the 8 byte per-entry table at
// m234_actorTbl (aliased in undefined_syms.txt).
extern s8 m234_actorSlotTbl[][8];
extern omObjData *m234_actorObjTbl[][2];
extern char *m234_chrAnimNameTbl[8];
extern const s16 m234_fontMesTbl[];
extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;

void m234_QuestionWinProc(void);
void m234_ObjectSetup(void);
void m234_StageObjInit(omObjData *);
void m234_HostObjInit(omObjData *);
void m234_MainObjMain(omObjData *);
void m234_RoundUpdate(void);
void m234_ActorMarchUpdate(void);
void m234_SpotlightObjInit(omObjData *);

s32 m234_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 m234_questionMesTbl[2] = { 0x6300, 0x6301 };
s16 m234_ordinalMesTbl[6] = { 0x6302, 0x6303, 0x6304, 0x6305, 0x6306, 0x6307 };
u16 m234_chrAnimFileTbl[8][3] = {
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0xA4, 0xA5, 0xA6 },
    { 0x1A, 0x1C, 0x1D },
};

CurtainCallWork m234_objWorkTbl[50] BSS;
s16 m234_playerAnimTbl[4] BSS;
s8 m234_survivorChrTbl[4] BSS;
s16 m234_marchFrame BSS;
s8 m234_speedPatternNo BSS;
CurtainCallTimerWork m234_timerWork BSS;
u8 m234_timerWorkPad[4] BSS; /* Unreferenced. */
void *m234_playerAnimDataTbl[4][3] BSS;
s8 m234_answerSlot BSS;
s8 m234_roundPhase BSS;
u8 m234_roundPhasePad[4] BSS; /* Unreferenced. */
s8 m234_actorTbl[6][8] BSS;
s8 m234_comLevelTbl[4] BSS;
s16 m234_startTimer BSS;
s8 m234_roundNo BSS;
s8 m234_answerType BSS;
s8 m234_musicFadeF BSS;
s8 m234_outNum BSS;
u8 m234_outNumPad[4] BSS; /* Unreferenced. */
s16 m234_comTimeTbl[4][2] BSS;
s8 m234_choiceTbl[4] BSS;
s16 m234_actorStopFrameTbl[2] BSS;
s8 m234_firstOutTbl[2] BSS;
s8 m234_correctCnt BSS;
omObjData *m234_actorLinkObj BSS;
s8 m234_survivorTbl[4] BSS;
s16 m234_linkMdlTbl[3] BSS;
s8 m234_phase BSS;
s8 m234_lastActorNo BSS;
Process *m234_questionProc BSS;
s8 m234_actorStopTimer BSS;

void m234_Executor(void) {
    m234_ObjectSetup();
}

f32 m234_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m234_ObjWorkInit(void) {
    CurtainCallWork *entry;
    u32 i;

    for (i = 0, entry = m234_objWorkTbl; i < 50; i++, entry++) {
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

void m234_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

s32 m234_RandGet(s32 arg0) {
    return rand8() % arg0;
}

void m234_MotSet(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        Hu3DMotionModelSet(arg0->model[0], arg0->motion[arg1]);
        Hu3DMotionAttrSet(arg0->model[0], arg2, arg2);
    }
}

void m234_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s32 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

s8 m234_RotYTurn(omObjData *obj, f32 target) {
    if (obj->rot.y != target) {
        obj->rot.y = m234_AngleAdd(obj->rot.y, 10.0f);
        return 1;
    }
    return 0;
}

void m234_CameraDebugPad(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)HuPadBtn[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m234_AngleAdd(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)HuPadBtn[GwPlayer[0].pad] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = m234_AngleAdd(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m234_AngleAdd(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)HuPadBtn[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = m234_AngleAdd(CRotM[i].y, -1.0f);
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
    if (HuPadBtnDown[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

void m234_QuestionWinProc(void) {
    s16 window = HuWinExCreateStyled(175, 92, 10);

    HuWinExOpen(window, 1);
    HuWinInsertMesSet(window, m234_ordinalMesTbl[m234_questionTbl[1]], 0);
    HuWinMesSet(window, m234_questionMesTbl[m234_questionTbl[0]], -1, -1);
    while (HuWinStatGet(window) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if (m234_roundPhase == 4) {
            break;
        }
        HuPrcVSleep();
    }
    HuWinExClose(window, 1);
    HuWinExCleanup(window);
    HuWinAllKill();
    while (TRUE) {
        HuPrcVSleep();
    }
}

void m234_QuestionStart(void) {
    omSysPauseDisableF = 1;
    HuWinInit();
    m234_questionProc = omAddPrcObj(m234_QuestionWinProc, 0x3F00, 0x800, 0);
}

void m234_QuestionKill(void) {
    if (m234_questionProc != NULL) {
        HuWinAllKill();
        while (omDelPrcObj(m234_questionProc) != 0) {
        }
        m234_questionProc = NULL;
    }
}

void m234_PauseEnable(void) {
    omSysPauseDisableF = 0;
}

void m234_StageObjMain(omObjData *arg0) {
    switch (m234_roundPhase) {
        case 3:
            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 5:
            Hu3DModelAttrSet(arg0->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
}

void m234_StageObjInit(omObjData *obj) {
    m234_backSprX = 160.0f;
    m234_backSprY = 120.0f;
    m234_backSprZ = 45.0f;
    m234_backSprAnim = HuSprAnimDataRead(0x430000);
    m234_backSpr = espEntry(m234_backSprAnim, 0, 0);
    espAttrSet(m234_backSpr, 0x5000);
    espPosSet(m234_backSpr, m234_backSprX, m234_backSprY);
    obj->model[0] = Hu3DModelRead(0x430001, 0x299);
    obj->model[1] = Hu3DModelRead(0x430002, 0x299);
    obj->model[2] = Hu3DModelRead(0x430003, 0x299);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    Hu3DMotionTimeSet(obj->model[0], 60.0f);
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM0);
    obj->func = m234_StageObjMain;
}

void m234_StageObjCreate(void) {
    m234_objWorkTbl[0].obj = omAddObj(0x1F4, 4, 2, -1, m234_StageObjInit);
}

void m234_PlayerAnimSet(omObjData *obj, u8 anim) {
    u8 player = obj->work[0];
    u8 chr = GwPlayer[player].chr;

    Hu3DAnimKill(m234_playerAnimTbl[player]);
    m234_playerAnimTbl[player] = Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m234_playerAnimDataTbl[player][anim], 0, m234_chrAnimNameTbl[chr]);
}

char *m234_chrAnimNameTbl[8] = {
    "c000l_0_DEF",
    "c001l_0_DEF",
    "c002l_0_DEF",
    "c003l_0_DEF",
    "c004l_0_DEF",
    "c005l_0_DEF",
    "c300l_0_DEF",
    "c301l_0_DEF",
};

u8 m234_comEasyRateTbl[3][5] = {
    { 13, 20, 33, 40, 74 },
    { 10, 20, 30, 40, 70 },
    { 7, 20, 27, 40, 66 },
};
u8 m234_comNormalRateTbl[3][5] = {
    { 18, 25, 43, 50, 84 },
    { 15, 25, 40, 50, 80 },
    { 12, 25, 37, 50, 76 },
};
u8 m234_comHardRateTbl[3][5] = {
    { 44, 50, 73, 80, 93 },
    { 40, 50, 70, 80, 90 },
    { 36, 50, 67, 80, 87 },
};
u8 m234_comExpertRateTbl[3][5] = {
    { 74, 80, 88, 90, 98 },
    { 70, 80, 85, 90, 95 },
    { 66, 80, 82, 90, 92 },
};

s8 m234_hopYTbl[25] = {
    0,
    0,
    0,
    0,
    16,
    14,
    12,
    10,
    8,
    6,
    4,
    2,
    0,
    -2,
    -4,
    -6,
    -8,
    -10,
    -12,
    -14,
    -16,
    0,
    0,
    0,
    0,
};

f32 m234_hopScaleTbl[25] = {
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    0.95f,
    0.9f,
    0.85f,
    0.8f,
    0.75f,
    0.7f,
    0.65f,
    0.6f,
    0.65f,
    0.7f,
    0.75f,
    0.8f,
    0.85f,
    0.9f,
    0.95f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
    1.0f,
};

s16 m234_actorSeTbl[3] = { 601, 603, 599 };
s16 m234_slotX3Tbl[3] = { 150, 0, -150 };
s16 m234_slotX5Tbl[5] = { 300, 150, 0, -150, -300 };
s16 m234_slotX6Tbl[6] = { 310, 185, 60, -60, -185, -310 };
s8 m234_spotOfs3Tbl[3] = { -8, 0, 8 };
s8 m234_spotOfs5Tbl[5] = { -16, -8, 0, 8, 16 };
s8 m234_spotOfs6Tbl[6] = { -18, -10, -3, 3, 10, 18 };
s16 m234_marchStartXTbl[6] = { -525, -655, -785, -915, -1045, -1175 };

u8 m234_orderPermTbl[6][3] = {
    { 0, 1, 2 },
    { 0, 2, 1 },
    { 1, 0, 2 },
    { 1, 2, 0 },
    { 2, 0, 1 },
    { 2, 1, 0 },
};

u8 m234_speedPattern5Tbl[3][3] = {
    { 4, 4, 8 },
    { 4, 8, 4 },
    { 8, 4, 4 },
};

u8 m234_speedPattern6Tbl[6][4] = {
    { 8, 8, 252, 4 },
    { 8, 252, 8, 4 },
    { 4, 252, 8, 8 },
    { 4, 8, 252, 8 },
    { 8, 252, 4, 8 },
    { 8, 4, 252, 8 },
};

CurtainCallCamera m234_cameraViewTbl[1] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 21.0f },
};

const char m234_emptyStr[] = ""; /* Unreferenced. */

s8 m234_SignScaleUpdate(omObjData *obj, s8 mode) {
    CurtainCallWork *entry = &m234_objWorkTbl[1 + obj->work[0]];

    switch (mode) {
        case 0:
            if (entry->unk_5C.y == 0.05f) {
                Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (entry->unk_5C.y < 1.0f) {
                entry->unk_5C.y += 0.19f;
                break;
            }
            entry->unk_5C.y = 1.0f;
            Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            return 1;
        case 1:
            if (entry->unk_5C.y > 0.05f) {
                entry->unk_5C.y -= 0.19;
                break;
            }
            Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            entry->unk_5C.y = 0.05f;
            Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
            return 1;
    }
    Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    return 0;
}

void m234_PlayerMotChange(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    CurtainCallWork *entry = &m234_objWorkTbl[1 + obj->work[0]];
    s8 shift = 0;

    if (entry->unk_06 != motion) {
        switch (motion) {
            case 4:
            case 5:
            case 6:
            case 8:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        m234_MotShiftSet(obj, motion, 0, 10, shift);
        entry->unk_06 = motion;
        if (motion == 4) {
            HuAudCharVoicePlay((m234_voiceChrTbl[chr] << 16) | 0x2F);
        }
    }
}

void m234_PlayerEndObjMain(omObjData *obj) {
    CurtainCallWork *entry;

    if (m234_phase < 5) {
        m234_PlayerMotChange(obj, 3);
        return;
    }
    entry = &m234_objWorkTbl[1 + obj->work[0]];
    if (entry->unk_04 != 0) {
        m234_PlayerMotChange(obj, 5);
        if (entry->unk_16 == 0) {
            entry->unk_16++;
            m234_PlayerAnimSet(obj, 2);
        }
    } else {
        m234_PlayerMotChange(obj, 4);
        if (entry->unk_16 == 0) {
            entry->unk_16++;
            m234_PlayerAnimSet(obj, 1);
        }
    }
}

void m234_ComWander(omObjData *obj) {
    if ((m234_timer & 0xF) == 0) {
        switch (m234_RandGet(3)) {
            case 0:
                HuPadStkX[obj->work[3]] = 0;
                break;
            case 1:
                HuPadStkX[obj->work[3]] = 10;
                break;
            case 2:
                HuPadStkX[obj->work[3]] = -10;
                break;
        }
    }
}

void m234_PlayerComInput(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CurtainCallWork *entry = &m234_objWorkTbl[1 + player];
    s8 roll;
    s8 level;

    if (obj->work[1] == 0) {
        return;
    }
    m234_PadClear(player);
    switch (m234_roundPhase) {
        case 0:
            roll = m234_RandGet(100);
            level = m234_roundNo;
            switch (m234_comLevelTbl[player]) {
                case 0:
                    if (roll < m234_comEasyRateTbl[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < m234_comEasyRateTbl[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < m234_comEasyRateTbl[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < m234_comEasyRateTbl[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < m234_comEasyRateTbl[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 1:
                    if (roll < m234_comNormalRateTbl[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < m234_comNormalRateTbl[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < m234_comNormalRateTbl[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < m234_comNormalRateTbl[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < m234_comNormalRateTbl[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 2:
                    if (roll < m234_comHardRateTbl[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < m234_comHardRateTbl[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < m234_comHardRateTbl[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < m234_comHardRateTbl[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < m234_comHardRateTbl[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
                case 3:
                    if (roll < m234_comExpertRateTbl[level][0]) {
                        entry->unk_0E = 1;
                    } else if (roll < m234_comExpertRateTbl[level][1]) {
                        entry->unk_0E = 2;
                    } else if (roll < m234_comExpertRateTbl[level][2]) {
                        entry->unk_0E = 3;
                    } else if (roll < m234_comExpertRateTbl[level][3]) {
                        entry->unk_0E = 4;
                    } else if (roll < m234_comExpertRateTbl[level][4]) {
                        entry->unk_0E = 5;
                    } else if (roll < 100) {
                        entry->unk_0E = 6;
                    }
                    break;
            }
            switch (entry->unk_0E) {
                case 1:
                case 2:
                    m234_comTimeTbl[player][0] = 230 - m234_RandGet(70);
                    m234_comTimeTbl[player][1] = m234_RandGet(20) + 20;
                    break;
                case 3:
                case 4:
                    m234_comTimeTbl[player][0] = m234_RandGet(20) + 20;
                    break;
                case 5:
                case 6:
                    m234_comTimeTbl[player][0] = 120 - m234_RandGet(60);
                    break;
            }
            entry->unk_10 = m234_RandGet(2);
            entry->unk_0C = m234_RandGet(3);
            break;
        case 3:
            switch (entry->unk_0E) {
                case 1:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_timer == m234_comTimeTbl[player][0]) {
                        entry->unk_0A = 2;
                        HuAudPlayerFXPlay(0x417, obj->work[0]);
                    } else if (m234_timer == m234_comTimeTbl[player][1]) {
                        if (m234_choiceTbl[player] != m234_answerType) {
                            entry->unk_0A = 4;
                            HuAudPlayerFXPlay(0x418, obj->work[0]);
                        }
                    } else if (m234_timer < m234_comTimeTbl[player][1]) {
                        if (m234_choiceTbl[player] != m234_answerType) {
                            if (entry->unk_10 != 0) {
                                HuPadStkX[pad] = 10;
                            } else {
                                HuPadStkX[pad] = -10;
                            }
                        }
                    }
                    break;
                case 2:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_timer == m234_comTimeTbl[player][0]) {
                        entry->unk_0A = 2;
                        HuAudPlayerFXPlay(0x417, obj->work[0]);
                    } else if (m234_timer == m234_comTimeTbl[player][1]) {
                        entry->unk_0A = 4;
                        HuAudPlayerFXPlay(0x418, obj->work[0]);
                    } else if (m234_timer < m234_comTimeTbl[player][1]) {
                        if (m234_choiceTbl[player] == m234_answerType) {
                            if (entry->unk_10 != 0) {
                                HuPadStkX[pad] = 10;
                            } else {
                                HuPadStkX[pad] = -10;
                            }
                        }
                    }
                    break;
                case 3:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_choiceTbl[player] != m234_answerType) {
                        if (entry->unk_10 != 0) {
                            HuPadStkX[pad] = 10;
                        } else {
                            HuPadStkX[pad] = -10;
                        }
                    }
                    break;
                case 4:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_choiceTbl[player] == m234_answerType) {
                        if (entry->unk_10 != 0) {
                            HuPadStkX[pad] = 10;
                        } else {
                            HuPadStkX[pad] = -10;
                        }
                    }
                    break;
                case 5:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_choiceTbl[player] == m234_answerType) {
                        if (entry->unk_0C == 0) {
                            entry->unk_0A = 2;
                            HuAudPlayerFXPlay(0x417, obj->work[0]);
                            entry->unk_0C = 1;
                        }
                    } else {
                        if (entry->unk_10 != 0) {
                            HuPadStkX[pad] = 10;
                        } else {
                            HuPadStkX[pad] = -10;
                        }
                    }
                    break;
                case 6:
                    if (m234_timer > m234_comTimeTbl[player][0]) {
                        m234_ComWander(obj);
                    } else if (m234_choiceTbl[player] == m234_answerType) {
                        if (entry->unk_10 != 0) {
                            HuPadStkX[pad] = 10;
                        } else {
                            HuPadStkX[pad] = -10;
                        }
                    } else {
                        if (entry->unk_0C == 0) {
                            entry->unk_0A = 2;
                            HuAudPlayerFXPlay(0x417, obj->work[0]);
                            entry->unk_0C = 1;
                        }
                    }
                    break;
            }
            break;
    }
}

void m234_PlayerOutUpdate(omObjData *obj) {
    CurtainCallWork *entry = &m234_objWorkTbl[1 + obj->work[0]];
    CurtainCallWork *other = &m234_objWorkTbl[1 + m234_firstOutTbl[0]];

    if (entry->unk_14 != 1000 && m234_correctCnt >= 2 && m234_roundNo < 2) {
        if (m234_firstOutTbl[0] == obj->work[0] || m234_firstOutTbl[1] == m234_roundNo) {
            m234_PlayerMotChange(obj, 7);
            entry->unk_14 = 1000;
        } else if (Hu3DData[other->obj->model[0]].motTime == 0.0f && entry->unk_06 != 7) {
            m234_MotSet(obj, 7, 2);
            entry->unk_06 = 7;
            entry->unk_14 = 1000;
        }
    }
}

void m234_PlayerObjMain(omObjData *obj) {
    s8 pad = obj->work[3];
    s8 player = obj->work[0];
    CurtainCallWork *entry = &m234_objWorkTbl[1 + player];

    if (m234_phase != 2) {
        if (m234_phase > 2) {
            obj->func = m234_PlayerEndObjMain;
        }
        return;
    }
    if (entry->unk_04 != 0) {
        m234_PlayerOutUpdate(obj);
        return;
    }
    m234_PlayerComInput(obj);
    switch (m234_roundPhase) {
        case 0:
            m234_PlayerMotChange(obj, 0);
            break;
        case 1:
            break;
        case 3:
            if (entry->unk_0A == 1) {
                if (entry->unk_08 <= 0) {
                    if (HuPadStkX[pad] < -5) {
                        if ((s32)entry->unk_44.x == -180) {
                            entry->unk_44.x = 0.0f;
                        }
                        entry->unk_08 = 1;
                        m234_choiceTbl[player] = (m234_choiceTbl[player] + 1) % 3;
                    }
                }
                if (entry->unk_08 >= 0) {
                    if (HuPadStkX[pad] > 5) {
                        if ((s32)entry->unk_44.x == 0) {
                            entry->unk_44.x = -180.0f;
                        }
                        entry->unk_08 = -1;
                        m234_choiceTbl[player] = m234_choiceTbl[player] != 0 ? m234_choiceTbl[player] - 1 : 2;
                    }
                }
            }
        case 2:
            if (m234_RotYTurn(obj, 0.0f)) {
                m234_PlayerMotChange(obj, 2);
            } else if (entry->unk_06 != 3) {
                m234_PlayerMotChange(obj, 1);
            }
            break;
        case 4:
        case 5:
            if (m234_RotYTurn(obj, 180.0f)) {
                m234_PlayerMotChange(obj, 2);
            } else {
                m234_PlayerMotChange(obj, 3);
            }
            m234_correctCnt = 0;
            entry->unk_12 = 0;
            break;
        case 6:
            if (entry->unk_12 < 30) {
                m234_RotYTurn(obj, 0.0f);
                m234_PlayerMotChange(obj, 2);
            } else if (entry->unk_12 == 30) {
                if (m234_choiceTbl[player] == m234_answerType) {
                    m234_PlayerMotChange(obj, 6);
                    m234_correctCnt++;
                } else {
                    m234_PlayerMotChange(obj, 8);
                    if (entry->unk_16 == 0) {
                        entry->unk_16++;
                        PlayerFXPlay(0x286, obj->work[0]);
                    }
                }
            } else if (entry->unk_12 > 70) {
                if (m234_choiceTbl[player] == m234_answerType) {
                    if (m234_correctCnt == 1) {
                        m234_PlayerMotChange(obj, 3);
                    } else if (m234_roundNo == 2) {
                        m234_PlayerMotChange(obj, 3);
                    } else if (m234_RotYTurn(obj, 180.0f)) {
                        m234_PlayerMotChange(obj, 2);
                    } else {
                        m234_PlayerMotChange(obj, 3);
                    }
                } else {
                    entry->unk_04 = 1;
                    if (m234_firstOutTbl[0] < 0) {
                        m234_firstOutTbl[0] = player;
                        m234_firstOutTbl[1] = m234_roundNo;
                    } else {
                        m234_PlayerMotChange(obj, 3);
                    }
                }
            }
            entry->unk_12++;
            break;
    }
    if (entry->unk_08 > 0) {
        entry->unk_44.x -= 4.0f;
        if ((s32)entry->unk_44.x % 60 == 0) {
            entry->unk_08 = 0;
        }
    }
    if (entry->unk_08 < 0) {
        entry->unk_44.x += 4.0f;
        if ((s32)entry->unk_44.x % 60 == 0) {
            entry->unk_08 = 0;
        }
    }
    Hu3DModelPosSet(obj->model[3], obj->trans.x + entry->unk_44.x, entry->unk_44.y, obj->trans.z);
    switch (m234_roundPhase) {
        case 0:
            entry->unk_44.x = 0.0f;
            m234_choiceTbl[player] = 0;
            entry->unk_0A = 0;
            entry->unk_14 = 0;
            break;
        case 3:
            switch (entry->unk_0A) {
                case 0:
                    if (m234_SignScaleUpdate(obj, 0)) {
                        entry->unk_0A = 1;
                    }
                    break;
                case 1:
                    if ((s32)entry->unk_44.x % 60 == 0 && (HuPadBtnDown[pad] & A_BUTTON)) {
                        HuAudPlayerFXPlay(0x417, obj->work[0]);
                        entry->unk_0A = 2;
                    }
                    break;
                case 2:
                    if (m234_SignScaleUpdate(obj, 1)) {
                        entry->unk_0A = 3;
                        m234_PlayerMotChange(obj, 3);
                    }
                    break;
                case 3:
                    if (HuPadBtnDown[pad] & B_BUTTON) {
                        HuAudPlayerFXPlay(0x418, obj->work[0]);
                        entry->unk_0A = 4;
                    }
                    break;
                case 4:
                    if (m234_SignScaleUpdate(obj, 0)) {
                        entry->unk_0A = 1;
                        m234_PlayerMotChange(obj, 1);
                    }
                    break;
            }
            break;
        case 4:
            if (m234_SignScaleUpdate(obj, 0)) {
                entry->unk_0A = 1;
            }
            break;
        case 6:
            if (m234_SignScaleUpdate(obj, 1)) {
                entry->unk_0A = 0;
            }
            break;
    }
}

void m234_PlayerObjInit(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallWork *entry = &m234_objWorkTbl[1 + player];
    u16 chr = GwPlayer[player].chr;
    s32 dir = omCharModelNoTbl[chr][0];
    s8 i;

    obj->model[0] = Hu3DModelRead(dir | omCharModelNoTbl[chr][3], 0x2A9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x6C));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x2C));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x33));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 0x63));
    omObjMotionRead(obj, 8, CharMotionDataNumGet(chr, 0x3A));
    for (i = 0; i < 3; i++) {
        m234_playerAnimDataTbl[player][i] = DataRead(dir | m234_chrAnimFileTbl[chr][i]);
    }
    m234_playerAnimTbl[player] =
        Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, m234_playerAnimDataTbl[player][0], 0, m234_chrAnimNameTbl[chr]);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    if (obj->work[0] == 0) {
        obj->model[1] = Hu3DModelRead2(0, 0xC9);
        Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[1]);
        Hu3DModelDynamicFree(obj->model[1]);
        HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        obj->model[2] = Hu3DModelRead(0x430004, 0x288);
        Hu3DModelRemakeStatic(obj->model[2]);
        Hu3DModelDynamicFree(obj->model[2]);
        obj->model[3] = Hu3DModelRead(0x430005, 0x288);
        Hu3DModelObjAttrSet(obj->model[3], 0x80000000, 0x80000000);
        Hu3DModelRemakeStatic(obj->model[3]);
        Hu3DModelDynamicFree(obj->model[3]);
        m234_linkMdlTbl[0] = obj->model[1];
        m234_linkMdlTbl[1] = obj->model[2];
        m234_linkMdlTbl[2] = obj->model[3];
    } else {
        obj->model[1] = Hu3DModelLink(m234_linkMdlTbl[0]);
        obj->model[2] = Hu3DModelLink(m234_linkMdlTbl[1]);
        obj->model[3] = Hu3DModelLink(m234_linkMdlTbl[2]);
    }
    Hu3DMotionAttrSet(obj->model[2], 2, 2);
    Hu3DMotionTimeSet(obj->model[2], m234_RandGet(50));
    switch (obj->work[1]) {
        case 0:
            obj->trans.x = -225.0f;
            obj->trans.z = 0.0f;
            obj->trans.y = 3.0f;
            break;
        case 1:
            obj->trans.x = -75.0f;
            obj->trans.z = 10.0f;
            obj->trans.y = 5.0f;
            break;
        case 2:
            obj->trans.x = 75.0f;
            obj->trans.z = 0.0f;
            obj->trans.y = 3.0f;
            break;
        case 3:
            obj->trans.x = 225.0f;
            obj->trans.z = 10.0f;
            obj->trans.y = 5.0f;
            break;
    }
    entry->unk_44.y = obj->trans.y + 160.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, entry->unk_44.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, entry->unk_44.y, obj->trans.z);
    obj->rot.x = 0.0f;
    obj->rot.y = 180.0f;
    obj->rot.z = 0.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    entry->unk_5C.x = 1.0f;
    entry->unk_5C.y = 0.05f;
    entry->unk_5C.z = 1.0f;
    Hu3DModelScaleSet(obj->model[2], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    Hu3DModelScaleSet(obj->model[3], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m234_MotSet(obj, 3, 2);
    entry->unk_06 = 3;
    m234_choiceTbl[player] = 0;
    m234_firstOutTbl[0] = -1;
    m234_firstOutTbl[1] = -1;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM0);
    obj->work[1] = GwPlayer[player].stat & 1;
    m234_comLevelTbl[player] = GwPlayer[player].cpu_difficulty;
    obj->work[3] = GwPlayer[player].pad;
    obj->func = m234_PlayerObjMain;
}

void m234_PlayerObjCreateAll(void) {
    CurtainCallWork *entry;
    omObjData *obj;
    s8 slots[4];
    s8 avail[4];
    u16 player = 0;
    s8 pick;
    s8 i;
    s8 j;
    s8 k;

    for (i = 0; i < 4; i++) {
        slots[i] = i;
        avail[i] = 1;
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
        entry = &m234_objWorkTbl[1 + i];
        obj = omAddObj(0x2BC, 5, 10, -1, m234_PlayerObjInit);
        obj->work[0] = player;
        entry->obj = obj;
        pick = m234_RandGet(4 - i);
        obj->work[1] = slots[pick];
        avail[slots[pick]] = 0;
        for (j = 0, k = 0; j < 4; j++) {
            if (avail[j]) {
                slots[k] = j;
                k++;
            }
        }
    }
}

void m234_ActorObjMain(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallWork *entry = &m234_objWorkTbl[5 + player];

    if (m234_phase < 2) {
        return;
    }
    switch (m234_roundPhase) {
        case 0:
            entry->unk_04 = 0;
            entry->unk_16 = 0;
            if (player >= 4) {
                obj->trans.y = 190.0f;
            } else {
                obj->trans.y = 125.0f;
            }
            entry->unk_5C.x = entry->unk_5C.z = 1.0f;
            break;
        case 1:
            if (omPauseChk() + omAllPauseF != 0) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            break;
        case 2:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 6:
            if (m234_answerSlot == m234_actorSlotTbl[player][0]) {
                if (m234_phase < 3 || (m234_phase == 3 && entry->unk_04 != 0)) {
                    obj->trans.y += m234_hopYTbl[entry->unk_04];
                    entry->unk_5C.x = entry->unk_5C.z = m234_hopScaleTbl[entry->unk_04];
                    entry->unk_04 = (entry->unk_04 + 1) % 25;
                    if (entry->unk_16 == 0) {
                        entry->unk_16++;
                        HuAudFXPlay(m234_actorSeTbl[m234_answerType]);
                    }
                }
            }
            /* fallthrough */
        case 4:
        case 5:
            if (omPauseChk() + omAllPauseF != 0) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            break;
    }
    if (m234_phase >= 4) {
        if (entry->unk_06 > 0) {
            entry->unk_06--;
        } else {
            obj->trans.y += m234_hopYTbl[entry->unk_04];
            entry->unk_5C.x = entry->unk_5C.z = m234_hopScaleTbl[entry->unk_04];
            entry->unk_04 = (entry->unk_04 + 1) % 25;
        }
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], entry->unk_5C.x, entry->unk_5C.y, entry->unk_5C.z);
}

void m234_ActorObjInit(omObjData *obj) {
    s8 player = obj->work[0];
    CurtainCallWork *entry = &m234_objWorkTbl[5 + player];

    switch (player) {
        case 0:
            obj->model[0] = Hu3DModelRead(0xA008E, 0x2B9);
            omObjMotionRead(obj, 0, 0xA0097);
            omObjMotionRead(obj, 1, 0xA0098);
            omObjMotionRead(obj, 2, 0xA0099);
            obj->work[1] = 0;
            m234_linkMdlTbl[0] = obj->model[0];
            m234_actorLinkObj = obj;
            break;
        case 1:
            obj->model[0] = Hu3DModelLink(m234_linkMdlTbl[0]);
            obj->work[1] = 0;
            obj->motion[0] = m234_actorLinkObj->motion[0];
            obj->motion[1] = m234_actorLinkObj->motion[1];
            obj->motion[2] = m234_actorLinkObj->motion[2];
            break;
        case 2:
            obj->model[0] = Hu3DModelRead(0xA00A5, 0x2B9);
            omObjMotionRead(obj, 0, 0xA00A8);
            omObjMotionRead(obj, 1, 0xA00A9);
            omObjMotionRead(obj, 2, 0xA00AA);
            obj->work[1] = 1;
            m234_linkMdlTbl[0] = obj->model[0];
            m234_actorLinkObj = obj;
            break;
        case 3:
            obj->model[0] = Hu3DModelLink(m234_linkMdlTbl[0]);
            obj->work[1] = 1;
            obj->motion[0] = m234_actorLinkObj->motion[0];
            obj->motion[1] = m234_actorLinkObj->motion[1];
            obj->motion[2] = m234_actorLinkObj->motion[2];
            break;
        case 4:
            obj->model[0] = Hu3DModelRead(0xA00C5, 0x2B9);
            omObjMotionRead(obj, 0, 0xA00CB);
            omObjMotionRead(obj, 1, 0xA00CC);
            omObjMotionRead(obj, 2, 0xA00CD);
            obj->work[1] = 2;
            m234_linkMdlTbl[0] = obj->model[0];
            m234_actorLinkObj = obj;
            break;
        case 5:
            obj->model[0] = Hu3DModelLink(m234_linkMdlTbl[0]);
            obj->work[1] = 2;
            obj->motion[0] = m234_actorLinkObj->motion[0];
            obj->motion[1] = m234_actorLinkObj->motion[1];
            obj->motion[2] = m234_actorLinkObj->motion[2];
            break;
    }
    m234_MotSet(obj, 0, 2);
    if (obj->work[0] == 0) {
        obj->model[1] = Hu3DModelRead2(0, 0xC9);
        Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[1]);
        Hu3DModelDynamicFree(obj->model[1]);
        HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
        m234_linkMdlTbl[1] = obj->model[1];
    } else {
        obj->model[1] = Hu3DModelLink(m234_linkMdlTbl[1]);
    }
    obj->trans.x = -1500.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 125.0f, obj->trans.z);
    if (player >= 0 && player < 2) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (player >= 2 && player < 4) {
        obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    if (player >= 4 && player < 6) {
        obj->scale.x = obj->scale.y = obj->scale.z = 0.52f;
        Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    }
    entry->unk_5C.x = entry->unk_5C.z = 1.0f;
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    obj->func = m234_ActorObjMain;
}

void m234_ActorObjCreateAll(void) {
    omObjData *obj;
    s16 i;

    for (i = 0; i < 6; i++) {
        obj = omAddObj(0x320, 3, 4, -1, m234_ActorObjInit);
        m234_actorObjTbl[i][0] = obj;
        obj->work[0] = i;
        m234_objWorkTbl[5].obj = obj;
        omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void m234_HostObjMain(omObjData *obj) {
    Hu3DModelPosSet(obj->model[1], obj->trans.x, 127.0f, obj->trans.z);
}

void m234_HostObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0xA0000, 0x2B9);
    omObjMotionRead(obj, 0, 0xA000C);
    m234_MotSet(obj, 0, 2);
    obj->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    obj->trans.x = -450.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -350.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->scale.x = 0.8f;
    obj->scale.y = 0.8f;
    obj->scale.z = 0.8f;
    Hu3DModelScaleSet(obj->model[0], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelScaleSet(obj->model[1], obj->scale.x, obj->scale.y, obj->scale.z);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    obj->func = m234_HostObjMain;
}

void m234_HostObjCreate(void) {
    m234_hostObj = omAddObj(0x258, 3, 2, -1, m234_HostObjInit);
}

void m234_SpotlightObjMain(omObjData *obj) {
    CurtainCallWork *entry = &m234_objWorkTbl[13];

    switch (m234_roundPhase) {
        case 0:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 5:
            switch (m234_roundNo) {
                case 0:
                    obj->trans.x = (f32)m234_slotX3Tbl[m234_answerSlot] +
                                   m234_spotOfs3Tbl[m234_answerSlot];
                    break;
                case 1:
                    obj->trans.x = (f32)m234_slotX5Tbl[m234_answerSlot] +
                                   m234_spotOfs5Tbl[m234_answerSlot];
                    break;
                case 2:
                    obj->trans.x = (f32)m234_slotX6Tbl[m234_answerSlot] +
                                   m234_spotOfs6Tbl[m234_answerSlot];
                    break;
            }
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
    if (m234_phase >= 3) {
        if (entry->unk_04 <= 0) {
            entry->unk_04 = 0;
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else {
            entry->unk_04 -= 5;
            Hu3DModelTPLvlSet(obj->model[0], entry->unk_04);
        }
    }
}

void m234_SpotlightObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x430006, 0x2A8);
    Hu3DModelTPLvlInit(obj->model[0]);
    Hu3DModelTPLvlSet(obj->model[0], 0xD2);
    obj->trans.x = 0.0f;
    obj->trans.y = 125.0f;
    obj->trans.z = -725.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    m234_objWorkTbl[13].unk_04 = 0xFF;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    obj->func = m234_SpotlightObjMain;
}

void m234_SpotlightObjCreate(void) {
    m234_spotlightObj = omAddObj(0x384, 1, 1, -1, m234_SpotlightObjInit);
}

void m234_ActorStopUpdate(void) {
    s8 i;
    s8 frame = m234_actorStopTimer;

    for (i = 0; i < 6; i++) {
        switch (frame) {
            case 0:
                m234_MotShiftSet(m234_actorObjTbl[i][0], 1, 0, 5, 2);
                break;
            case 25:
                m234_MotShiftSet(m234_actorObjTbl[i][0], 2, 0, 5, 2);
                break;
            case 50:
                m234_MotShiftSet(m234_actorObjTbl[i][0], 0, 0, 5, 2);
                break;
        }
    }
    if (frame == 50) {
        m234_marchFrame++;
        m234_actorStopTimer = 0;
    } else {
        m234_actorStopTimer++;
    }
}

void m234_ActorMarchUpdate(void) {
    s16 frame;
    s8 speed = 0;
    s8 i;

    if (m234_marchFrame == m234_actorStopFrameTbl[0] || m234_marchFrame == m234_actorStopFrameTbl[1]) {
        m234_ActorStopUpdate();
        return;
    }
    m234_marchFrame++;
    frame = m234_marchFrame;
    switch (m234_roundNo) {
        case 0:
            speed = 6;
            break;
        case 1:
            if (frame < 60) {
                speed = 6;
            } else if (frame < 105) {
                speed = m234_speedPattern5Tbl[m234_speedPatternNo][0];
            } else if (frame < 150) {
                speed = 6;
            } else if (frame < 195) {
                speed = m234_speedPattern5Tbl[m234_speedPatternNo][1];
            } else if (frame < 240) {
                speed = 6;
            } else if (frame < 285) {
                speed = m234_speedPattern5Tbl[m234_speedPatternNo][2];
            } else {
                speed = 6;
            }
            break;
        case 2:
            if (frame < 60) {
                speed = 6;
            } else if (frame < 105) {
                speed = m234_speedPattern6Tbl[m234_speedPatternNo][0];
            } else if (frame < 150) {
                speed = 6;
            } else if (frame < 195) {
                speed = m234_speedPattern6Tbl[m234_speedPatternNo][1];
            } else if (frame < 240) {
                speed = m234_speedPattern6Tbl[m234_speedPatternNo][2];
            } else if (frame < 285) {
                speed = 6;
            } else if (frame < 330) {
                speed = m234_speedPattern6Tbl[m234_speedPatternNo][3];
            } else {
                speed = 6;
            }
            break;
    }
    for (i = 0; i < 6; i++) {
        if (m234_actorTbl[i][0] != 0) {
            m234_actorObjTbl[i][0]->trans.x += speed;
        }
    }
}

void m234_SurvivorCount(void) {
    CurtainCallWork *entry;
    s8 i;
    s8 count;

    m234_outNum = 0;
    for (i = 0; i < 4; i++) {
        m234_survivorChrTbl[i] = 0;
    }
    for (i = 0, count = 0; i < 4; i++) {
        entry = &m234_objWorkTbl[1 + i];
        if (entry->unk_04 == 0) {
            m234_survivorChrTbl[count] = GwPlayer[entry->obj->work[0]].chr;
            m234_survivorTbl[count] = entry->obj->work[0];
            count++;
        } else {
            m234_outNum++;
        }
    }
}

void m234_QuestionSet(void) {
    s8 slots[6];
    s8 pick;
    s8 i;

    for (i = 0; i < 6; i++) {
        slots[m234_actorSlotTbl[i][0]] = m234_actorObjTbl[i][0]->work[1];
    }
    switch (m234_roundNo) {
        case 0:
            pick = m234_RandGet(3);
            m234_answerType = slots[pick];
            m234_answerSlot = pick;
            m234_questionTbl[0] = m234_RandGet(2);
            if (m234_questionTbl[0] != 0) {
                m234_questionTbl[1] = pick;
            } else {
                m234_questionTbl[1] = 2 - pick;
            }
            break;
        case 1:
            pick = m234_RandGet(5);
            m234_answerType = slots[pick];
            m234_answerSlot = pick;
            m234_questionTbl[0] = m234_RandGet(2);
            if (m234_questionTbl[0] != 0) {
                m234_questionTbl[1] = pick;
            } else {
                m234_questionTbl[1] = 4 - pick;
            }
            break;
        case 2:
            pick = m234_RandGet(6);
            m234_answerType = slots[pick];
            m234_answerSlot = pick;
            m234_questionTbl[0] = m234_RandGet(2);
            if (m234_questionTbl[0] != 0) {
                m234_questionTbl[1] = pick;
            } else {
                m234_questionTbl[1] = 5 - pick;
            }
            break;
    }
}

void m234_RoundUpdate(void) {
    CurtainCallWork *entry = m234_objWorkTbl;
    omObjData *stage = entry->obj;
    omObjData *host = m234_objWorkTbl[11].obj;
    s8 order[6];
    s8 avail[6];
    s8 pick;
    s8 count;
    s8 i;
    s8 j;

    switch (m234_roundPhase) {
        case 0:
            switch (m234_roundNo) {
                case 0:
                    m234_actorTbl[0][0] = m234_actorTbl[2][0] = m234_actorTbl[4][0] = 1;
                    m234_actorTbl[1][0] = m234_actorTbl[3][0] = m234_actorTbl[5][0] = 0;
                    pick = m234_RandGet(6);
                    m234_actorTbl[0][1] = m234_orderPermTbl[pick][0];
                    m234_actorTbl[2][1] = m234_orderPermTbl[pick][1];
                    m234_actorTbl[4][1] = m234_orderPermTbl[pick][2];
                    m234_actorTbl[1][1] = 3;
                    m234_actorTbl[3][1] = 4;
                    m234_actorTbl[5][1] = 5;
                    break;
                case 1:
                case 2:
                    for (i = 0; i < 6; i++) {
                        order[i] = i;
                        avail[i] = TRUE;
                    }
                    for (i = 0; i < 6; i++) {
                        pick = m234_RandGet(6 - i);
                        m234_actorSlotTbl[i][0] = order[pick];
                        avail[order[pick]] = FALSE;
                        for (j = 0, count = 0; j < 6; j++) {
                            if (avail[j] != 0) {
                                order[count] = j;
                                count++;
                            }
                        }
                    }
                    for (i = 0; i < 6; i++) {
                        m234_actorTbl[i][0] = 1;
                        if (m234_roundNo == 1 && m234_actorSlotTbl[i][0] == 5) {
                            m234_actorTbl[i][0] = 0;
                        }
                    }
                    break;
            }
            switch (m234_roundNo) {
                case 0:
                    m234_actorStopFrameTbl[0] = 108;
                    m234_actorStopFrameTbl[1] = 1000;
                    break;
                case 1:
                    m234_actorStopFrameTbl[0] = m234_RandGet(75) + 60;
                    m234_actorStopFrameTbl[1] = m234_RandGet(105) + 135;
                    m234_speedPatternNo = m234_RandGet(3);
                    break;
                case 2:
                    m234_actorStopFrameTbl[0] = m234_RandGet(105) + 60;
                    m234_actorStopFrameTbl[1] = m234_RandGet(135) + 165;
                    m234_speedPatternNo = m234_RandGet(6);
                    break;
            }
            for (i = 0; i < 6; i++) {
                if (m234_actorTbl[i][0] != 0) {
                    m234_actorObjTbl[i][0]->trans.x = m234_marchStartXTbl[m234_actorSlotTbl[i][0]];
                } else {
                    m234_actorObjTbl[i][0]->trans.x = -1500.0f;
                }
            }
            m234_actorStopTimer = 0;
            m234_marchFrame = 0;
            Hu3DMotionSpeedSet(stage->model[0], -1.0f);
            for (i = 0; i < 6; i++) {
                switch (m234_roundNo) {
                    case 0:
                        if (m234_actorSlotTbl[i][0] == 2) {
                            m234_lastActorNo = i;
                        }
                        break;
                    case 1:
                        if (m234_actorSlotTbl[i][0] == 4) {
                            m234_lastActorNo = i;
                        }
                        break;
                    case 2:
                        if (m234_actorSlotTbl[i][0] == 5) {
                            m234_lastActorNo = i;
                        }
                        break;
                }
            }
            m234_QuestionSet();
            m234_roundPhase = 1;
            break;
        case 1:
            if ((s32)Hu3DData[stage->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(stage->model[0], 0.0f);
                Hu3DMotionSpeedSet(stage->model[0], 0.0f);
                Hu3DModelAttrSet(stage->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            m234_ActorMarchUpdate();
            if (m234_actorObjTbl[m234_lastActorNo][0]->trans.x >= 500.0f) {
                m234_roundPhase = 2;
                Hu3DModelAttrSet(stage->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(host->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DModelAttrSet(host->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            break;
        case 2:
            Hu3DMotionSpeedSet(stage->model[0], 1.0f);
            if (host->trans.x < 0.0f) {
                host->trans.x += 7.0f;
            } else {
                host->trans.x = 0.0f;
                HuAudFXPlay(0x298);
                GMesCreate(GMES_MES_TIMER, 10, 160, 28);
                m234_timer = 301;
                m234_QuestionStart();
                HuAudFXPlay(0x414);
                m234_roundPhase = 3;
            }
            break;
        case 3:
            if (m234_timer > 0) {
                m234_timer--;
                GMesTimerValueSet((m234_timer + 29) / 30);
            } else {
                GMesTimerEnd();
                HuAudFXIdStop(0x414);
                m234_roundPhase = 4;
            }
            break;
        case 4:
            if (host->trans.x > -450.0f) {
                host->trans.x -= 7.0f;
                if (host->trans.x < -300.0f && m234_musicFadeF == 0) {
                    HuAudSeqVolFadeOut(30);
                    m234_musicFadeF = 1;
                }
            } else {
                host->trans.x = -450.0f;
                Hu3DModelAttrSet(host->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(host->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                m234_musicFadeF = 0;
                for (i = 0; i < 6; i++) {
                    if (m234_actorTbl[i][0] != 0) {
                        switch (m234_roundNo) {
                            case 0:
                                m234_actorObjTbl[i][0]->trans.x =
                                    m234_slotX3Tbl[m234_actorSlotTbl[i][0]];
                                break;
                            case 1:
                                m234_actorObjTbl[i][0]->trans.x =
                                    m234_slotX5Tbl[m234_actorSlotTbl[i][0]];
                                break;
                            case 2:
                                m234_actorObjTbl[i][0]->trans.x =
                                    m234_slotX6Tbl[m234_actorSlotTbl[i][0]];
                                break;
                        }
                    } else {
                        m234_actorObjTbl[i][0]->trans.x = -1500.0f;
                    }
                }
                m234_roundPhase = 5;
                HuAudFXPlay(0x419);
                m234_QuestionKill();
            }
            break;
        case 5:
            m234_PauseEnable();
            Hu3DMotionSpeedSet(stage->model[0], -1.0f);
            if ((s32)Hu3DData[stage->model[0]].motTime <= 0) {
                Hu3DMotionTimeSet(stage->model[0], 0.0f);
                Hu3DMotionSpeedSet(stage->model[0], 0.0f);
                Hu3DModelAttrSet(stage->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                HuAudFXPlay(0x522);
                m234_timer = 100;
                m234_roundPhase = 6;
            }
            break;
        case 6:
            if (m234_timer > 0) {
                m234_timer--;
                break;
            }
            switch (m234_roundNo) {
                case 0:
                case 1:
                    m234_SurvivorCount();
                    if (m234_outNum < 3) {
                        break;
                    }
                    m234_roundNo = 3;
                    pick = m234_RandGet(2);
                    for (i = 0; i < 6; i++) {
                        for (j = 0; j < 6; j++) {
                            if (m234_actorSlotTbl[i][0] == j) {
                                entry = &m234_objWorkTbl[i + 5];
                                if (pick != 0) {
                                    entry->unk_06 = m234_actorSlotTbl[i][0] * 5;
                                } else {
                                    entry->unk_06 = (5 - j) * 5;
                                }
                                break;
                            }
                        }
                    }
                    return;
                case 2:
                    m234_SurvivorCount();
                    m234_roundNo++;
                    pick = m234_RandGet(2);
                    for (i = 0; i < 6; i++) {
                        for (j = 0; j < 6; j++) {
                            if (m234_actorSlotTbl[i][0] == j) {
                                entry = &m234_objWorkTbl[i + 5];
                                if (pick != 0) {
                                    entry->unk_06 = m234_actorSlotTbl[i][0] * 5;
                                } else {
                                    entry->unk_06 = (5 - j) * 5;
                                }
                                break;
                            }
                        }
                    }
                    return;
            }
            if (m234_musicFadeF == 0) {
                m234_musicFadeF = 1;
                HuAudFXAllFadeOut(30);
                HuAudSeqVolFadeIn(30);
            }
            Hu3DMotionSpeedSet(stage->model[0], 1.0f);
            Hu3DModelAttrSet(stage->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if ((s32)Hu3DData[stage->model[0]].motTime >= 60) {
                Hu3DMotionTimeSet(stage->model[0], 60.0f);
                Hu3DMotionSpeedSet(stage->model[0], 0.0f);
                m234_musicFadeF = 0;
                m234_roundNo++;
                m234_roundPhase = 0;
            }
            break;
    }
}

void m234_CameraViewInit(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 1520.0f;
        CRotM[i].x = 347.14f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 225.0f;
        CenterM[i].z = -25.0f;
    }
}

void m234_ExitObjMain(omObjData *obj) {
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

void m234_ExitWaitObjMain(omObjData *obj) {
    s8 i;
    s8 j;

    if (WipeStatGet() == 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 3; j++) {
                DataClose(m234_playerAnimDataTbl[i][j]);
            }
            Hu3DAnimKill(m234_playerAnimTbl[i]);
        }
        obj->func = m234_ExitObjMain;
    }
}

void m234_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        m234_QuestionKill();
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m234_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m234_MainObjMain(omObjData *obj) {
    switch (m234_phase) {
        case 0:
            GMesCreate(GMES_MES_3);
            m234_phase = 1;
            m234_startTimer = 0;
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m234_phase = 2;
                m234_roundPhase = 0;
            }
            if (++m234_startTimer == 62) {
                HuAudSeqPlay(0x31);
            }
            break;
        case 2:
            m234_RoundUpdate();
            if (m234_roundNo == 3) {
                GMesCreate(GMES_MES_14);
                HuAudSeqFadeOut(120);
                m234_phase = 3;
            }
            break;
        case 3:
            if (GMesStatGet() == 0) {
                m234_phase = 4;
                m234_timer = 0;
            }
            break;
        case 4:
            if (m234_outNum == 4) {
                if (++m234_timer >= 16) {
                    m234_phase = 5;
                }
            } else {
                if (++m234_timer >= 16) {
                    m234_phase = 6;
                }
            }
            break;
        case 6:
            switch (m234_outNum) {
                case 0:
                    GMesCreate(GMES_MES_MG_WINNERS_4, m234_survivorChrTbl[0], m234_survivorChrTbl[1], m234_survivorChrTbl[2],
                               m234_survivorChrTbl[3]);
                    GwPlayer[m234_survivorTbl[0]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[1]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[2]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[3]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 1:
                    GMesCreate(GMES_MES_MG_WINNERS_3, m234_survivorChrTbl[0], m234_survivorChrTbl[1], m234_survivorChrTbl[2]);
                    GwPlayer[m234_survivorTbl[0]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[1]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[2]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 2:
                    GMesCreate(GMES_MES_MG_WINNERS_2, m234_survivorChrTbl[0], m234_survivorChrTbl[1]);
                    GwPlayer[m234_survivorTbl[0]].bonusCoin = 10;
                    GwPlayer[m234_survivorTbl[1]].bonusCoin = 10;
                    HuAudSeqPlay(0x66);
                    break;
                case 3:
                    GMesCreate(GMES_MES_MG_WINNER, m234_survivorChrTbl[0]);
                    GwPlayer[m234_survivorTbl[0]].bonusCoin = 10;
                    HuAudSeqPlay(0x65);
                    break;
            }
            m234_timer = 15;
            m234_phase = 7;
            break;
        case 5:
            GMesCreate(GMES_MES_MG_DRAW);
            HuAudSeqPlay(0x6C);
            m234_timer = 15;
            m234_phase = 7;
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (--m234_timer <= 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    obj->func = m234_ExitWaitObjMain;
                }
            }
            break;
    }
}

void m234_MainObjInit(omObjData *obj) {
    m234_phase = 0;
    m234_roundPhase = 20;
    m234_timer = 0;
    m234_roundNo = 0;
    m234_questionProc = NULL;
    m234_musicFadeF = 0;
    m234_CameraViewInit();
    m234_StageObjCreate();
    m234_SpotlightObjCreate();
    m234_HostObjCreate();
    m234_PlayerObjCreateAll();
    m234_ActorObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    obj->func = m234_MainObjMain;
}

void m234_Dummy(void) {
}

void m234_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m234_cameraViewTbl[i].scissorX, m234_cameraViewTbl[i].scissorY,
                   m234_cameraViewTbl[i].scissorWidth, m234_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m234_cameraViewTbl[i].viewportScale.x, m234_cameraViewTbl[i].viewportScale.y,
                    m234_cameraViewTbl[i].viewportScale.z, m234_cameraViewTbl[i].viewportTranslate.x,
                    m234_cameraViewTbl[i].viewportTranslate.y, m234_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m234_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m234_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(50, 3);
    omGameSysInit();
    m234_CameraInit();
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
    GMesFontMesCreate(m234_fontMesTbl, 0);
    GMesFontMesCreate(m234_fontMesTbl, 1);
    omAddObj(1500, 0, 0, -1, m234_MainObjInit);
    omAddObj(1500, 0, 0, -1, m234_ExitCheckObjMain);
    m234_ObjWorkInit();
}

const s16 m234_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
