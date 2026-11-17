#include "common.h"
#include "game/vibrator.h"
#include "game/mallocblock.h"
#include "game/hmfmath.h"
#include "game/menuflag.h"
#include "game/overlays/minigame.h"
#include "math.h"

typedef struct UnkModeSel {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s32 unk_28;
} UnkModeSel;

typedef struct UnkModeSel2 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    u8 unk_18;
    u8 unk_19[3];
} UnkModeSel2; // sizeof 0x1C

typedef struct UnkModeSel3 {
    Vec pos;
    Vec at;
    Vec up;
} UnkModeSel3; // sizeof 0x24

// Parallel to UnkModeSel: two float triples indexed with the same 0x2C stride.
// The tail is unreferenced padding that brings each element up to 0x2C.
typedef struct UnkModeSel4 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s32 unk_18[5];
} UnkModeSel4; // sizeof 0x2C

// One entry per player slot; the object is the spinner for that player.
typedef struct UnkModeSel5 {
    s32 unk_00;
    s32 unk_04;
    omObjData *unk_08;
    Vec unk_0C;
} UnkModeSel5; // sizeof 0x18

typedef struct UnkModeSel6 {
    omObjData *unk_00;
    s32 unk_04;
    s32 unk_08;
    Vec pos;
    Vec at;
    Vec up;
} UnkModeSel6; // sizeof 0x30

typedef struct UnkModeSel7 {
    omObjData *obj;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    Vec unk_10;
    Vec unk_1C;
} UnkModeSel7; // sizeof 0x28

// Accumulated spin angle: added to as a float by modesel_StarNodeRotAdd, but reset
// and read as a raw word by modesel_StarNodeRotSet and modesel_StarNodeUpdate.
typedef union UnkModeSelAngle {
    s32 word;
    f32 angle;
} UnkModeSelAngle; // sizeof 0x4

// One entry per spinning star (model indices 7 to 9) and its shadow.
typedef struct UnkModeSelStar {
    HmfMotionNode *star;
    HmfMotionNode *shadow;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    UnkModeSelAngle rot;
} UnkModeSelStar; // sizeof 0x1C

// Summary of the saved party mode board, copied from the loaded save.
typedef struct UnkModeSelBoardSave {
    s32 chr[4];
    s32 cpu[4];
    s32 gameLength;
    s32 currentTurn;
    s32 totalTurns;
} UnkModeSelBoardSave; // sizeof 0x2C

// Summary of the saved story mode board, copied from the loaded save.
typedef struct UnkModeSelStorySave {
    s32 chr[2];
    s32 cpu[2];
    s32 gameLength;
    s32 currentTurn;
    s32 totalTurns;
} UnkModeSelStorySave; // sizeof 0x1C

extern s16 mgStoryStatPortNo;
extern const char modesel_emptyStr[];

s32 modesel_winPosX = 28; /* Unreferenced. */
s32 modesel_winPosY = 208;
s32 modesel_winUnusedParamA = 24; /* Unreferenced. */
s32 modesel_winUnusedParamB = 2;  /* Unreferenced. */
u8 modesel_boardNoTbl[16] = { 0, 6, 1, 7, 2, 8, 3, 9, 4, 10, 11, 5 };
u8 modesel_unusedOrderTbl[12] = { 0, 1, 2, 3, 4, 5, 7, 6 };
f32 modesel_cameraFov = 55.0f;
f32 modesel_cameraNear = 100.0f;
f32 modesel_cameraFar = 2080.0f;
s32 modesel_stickBtn = 0;
// Position tables, one entry per spinner position.
Vec modesel_starPosTbl[3] = {
    { 250.0f, 25.0f, 355.0f },
    { -250.0f, 25.0f, 355.0f },
    { 0.0f, 25.0f, 70.0f },
};
u32 modesel_rankMesTbl[5] = { 0x3121, 0x3120, 0x311D, 0x311C, 0x311B };
Vec modesel_spotPosTbl[14] = {
    { 250.0f, 45.0f, 355.0f },
    { -250.0f, 45.0f, 355.0f },
    { 0.0f, 45.0f, 70.0f },
    { 0.0f, 200.0f, 0.0f },
    { 325.0f, 102.5f, 45.0f },
    { 0.0f, 360.0f, -355.0f },
    { 50.0f, 25.0f, 300.0f },
    { -250.0f, 225.0f, 300.0f },
    { -500.0f, 440.0f, -355.0f },
    { -300.0f, 590.0f, -355.0f },
    { -100.0f, 590.0f, -355.0f },
    { 150.0f, 590.0f, -355.0f },
    { 425.0f, 590.0f, -355.0f },
    { 575.0f, 440.0f, -355.0f }
};

UnkModeSel2 modesel_sprTbl[0x40] BSS;
// the one-column second dimension keeps these indexed stores addressing the array base symbolically
s16 modesel_animTbl[0x40][1] BSS;
UnkModeSel modesel_modelTbl[0x40] BSS;
s16 modesel_bgAnim BSS;
u16 modesel_bgSpr BSS;
u8 modesel_bgSprPad[4] BSS; /* Unreferenced. */
s16 modesel_winTbl[0x20][6] BSS;
UnkModeSelStar modesel_starNodeTbl[3] BSS;
u8 modesel_starNodePad[4] BSS; /* Unreferenced. */
s32 modesel_boardStatUnusedTbl[6] BSS;
UnkModeSelBoardSave modesel_boardStatParty BSS;
UnkModeSelStorySave modesel_boardStatStory BSS;
omObjData *modesel_hostObj BSS;
HmfMotionNode *modesel_taihoNode BSS;
s32 modesel_storyChr BSS;
Process *modesel_mainProc BSS;
Process *modesel_cameraProc BSS;
u8 modesel_cameraProcPad[4] BSS; /* Unreferenced. */
UnkModeSel3 modesel_cameraWork BSS;
u8 modesel_cameraWorkPad[4] BSS; /* Unreferenced. */
UnkModeSel7 modesel_cameraMove BSS;
UnkModeSel6 modesel_cameraShake BSS;
UnkModeSel5 modesel_starBobTbl[3] BSS;
Vec modesel_hostPos BSS;
Vec modesel_hostEndPos BSS;
u8 modesel_hostPad[0xC] BSS; /* Unreferenced. */
f32 modesel_hostRotY BSS;
// Start and end positions for the model 10 hop animation.
Vec modesel_hostJumpPosTbl[2] BSS;
// Three interleaved parallel arrays covering the same 21 slots; each element is 0xC bytes apart.
s32 modesel_spotEffTime[21][3] BSS;
s32 modesel_rumbleCnt BSS;

/* Views into the BSS arrays above, aliased in undefined_syms.txt. */
extern s16 modesel_winPosYHalf;               // low half of modesel_winPosY
extern s16 modesel_storyChrHalf;               // low half of modesel_storyChr
extern UnkModeSel4 modesel_modelScaleTbl[0x40]; // modesel_modelTbl[i].unk_10
extern s32 modesel_winMesTbl[0x20][3];
extern s32 modesel_winTypeTbl[0x20][3];
extern s32 modesel_spotEffMaxTime[][3];
extern omObjData *modesel_spotEffObj[][3];

void modesel_SprInit(void);
void modesel_SprDispOn(s32);
void modesel_SprDispOff(s32);
void modesel_ModelInit(void);
void modesel_WinInit(void);
void modesel_MainCreate(void);
void modesel_WinKill(s32);
void modesel_CameraMotionApply(s32);
s32 modesel_CameraMotionPosGet(Vec *, Vec *, Vec *);
void modesel_HostFallObjMain(omObjData *);
f32 modesel_LookAtAngleCalc(f32, f32);

void modesel_SprPosSet(s32, s32, s32);
void modesel_ModelKill(s32);
void modesel_MainProc(void);
void modesel_StarNodePosSet(s32, f32, f32, f32, f32);
void modesel_StarNodeSet(s32, f32, f32, f32, f32);
void modesel_StarNodeUpdate(s32);
void modesel_CursorPosGet(s32, s32 *, s32 *);
void modesel_RumbleObjMain(omObjData *);
void modesel_MotionSet(s32, s32, s16);
void modesel_CameraViewSet(Vec *, Vec *, Vec *);
void modesel_CameraShakeObjMain(omObjData *);
void modesel_StarJumpObjMain(omObjData *);
void modesel_HostFloatObjMain(omObjData *);
void modesel_HostEnterObjMain(omObjData *);
void modesel_HostExitObjMain(omObjData *);
void modesel_HostJumpObjMain(omObjData *);
void modesel_SpotEffObjMain(omObjData *);
void modesel_StarBobObjMain(omObjData *);
void modesel_CameraTurnEaseObjMain(omObjData *);
void modesel_SpotPosGet(s32, f32 *, f32 *, f32 *);
void modesel_SpotEffUpdate(s32, f32);
s32 modesel_StickBtnGet(s32);
s32 modesel_BoardStatCreate(void);
s32 modesel_BoardStatChoice(void);
void modesel_FileInfoDispOn(void);
void modesel_HelpExec(void);
s32 modesel_BoardIdxGet(s32);
s32 modesel_BoardTypeGet(s32);
void modesel_BoardStatDispOn(void);
void modesel_BoardStatDispOff(void);
void modesel_BoardStatKill(void);
void modesel_CursorMove(s32, s32);
void modesel_MenuMesSet(s32);
void modesel_WinCreate(s32 index, u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
void modesel_SpotFocus(s32);
void modesel_CameraEaseObjMain(omObjData *);
void modesel_SprPosGet(s32, s32 *, s32 *);
void modesel_StarLandObjMain(omObjData *);
void modesel_StarFallObjMain(omObjData *);
void modesel_StarHoldObjMain(omObjData *);
void modesel_StarNodeRotSet(s32, s32);
void modesel_StarNodeRotAdd(s32, f32);
void modesel_SpotEffKill(s32);
void modesel_CameraDirLerp(Vec *, Vec *, f32, Vec *);
s32 modesel_WinType0Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 modesel_WinType1Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 modesel_WinType2Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 modesel_WinType3Create(u32 message, s16 x, s16 y, s16 style);
s32 modesel_WinType4Create(u32 message, s16 x, s16 y, s16 style);
s32 modesel_WinType5Create(u32 message, s16 x, s16 y, s16 style);
s32 modesel_BoardNoGet(s32);
s32 modesel_MenuDecide(s32, s32);
s32 modesel_MenuMove(s32, s32);
void modesel_CursorCreate(void);
void modesel_CursorKill(void);
void modesel_CursorPosUpdate(s32);
void modesel_SpotEffCreate(s32);
void modesel_FileInfoDispOff(void);
void modesel_RumbleStart(void);
void modesel_StarBobInit(void);
void modesel_BoardStatRead(void);
void modesel_StageCreate(void);
void modesel_SpotEffInit(void);
void modesel_CameraMoveInit(void);
void modesel_FileInfoCreate(void);
Process *modesel_CameraMotionStart(void);
Process *modesel_CameraManualStart(void);
omObjData *modesel_HostEnterCreate(s32);
omObjData *modesel_HostFloatCreate(s32);
s32 modesel_MenuExec(void);
void modesel_CameraMoveKill(void);
void modesel_CameraMotionStop(Process *);
void modesel_FileInfoKill(void);
void modesel_SpotEffKillAll(void);
void modesel_StageKill(void);

void modesel_UtilInit(void) {
    modesel_SprInit();
    modesel_ModelInit();
    modesel_WinInit();
}

void modesel_SprInit(void) {
    UnkModeSel2 *p;
    f32 zero;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(modesel_sprTbl); i++) {
        modesel_animTbl[i][0] = -1;
        modesel_sprTbl[i].unk_00 = -1;
        // only these two of the seven field stores go through the pointer, the rest stay symbolic
        p = &modesel_sprTbl[i];
        p->unk_08 = 0;
        modesel_sprTbl[i].unk_04 = 0;
        zero = 0.0f;
        p->unk_10 = zero;
        modesel_sprTbl[i].unk_0C = zero;
        modesel_sprTbl[i].unk_14 = zero;
        modesel_sprTbl[i].unk_18 = 0xFF;
    }
}

s16 modesel_AnimIdGet(s32 arg0) {
    return modesel_animTbl[arg0][0];
}

s16 modesel_EspIdGet(s32 arg0) {
    return modesel_sprTbl[arg0].unk_00;
}

void modesel_AnimCreate(s32 arg0, s32 arg1) {
    modesel_animTbl[arg0][0] = HuSprAnimDataRead(arg1);
}

void modesel_AnimKill(s32 arg0) {
    if (modesel_animTbl[arg0][0] != -1) {
        HuSprAnimKill(modesel_animTbl[arg0][0]);
    }
    modesel_animTbl[arg0][0] = -1;
}

void modesel_EspCreate(s32 arg0, s16 arg1) {
    modesel_sprTbl[arg0].unk_00 = espEntry(modesel_animTbl[arg1][0], 0, 0);
    modesel_SprPosSet(arg0, 0xA0, 0x78);
}

void modesel_EspKill(s32 arg0) {
    if (modesel_sprTbl[arg0].unk_00 != -1) {
        espKill(modesel_sprTbl[arg0].unk_00);
    }
    modesel_sprTbl[arg0].unk_00 = -1;
}

void modesel_SprCreate(s32 arg0, s32 arg1) {
    modesel_AnimCreate(arg0, arg1);
    modesel_EspCreate(arg0, arg0);
}

void modesel_SprBGCreate(s32 arg0, s32 arg1) {
    modesel_SprCreate(arg0, arg1);
    espAttrSet(modesel_sprTbl[arg0].unk_00, HUSPR_ATTR_BG);
}

void modesel_SprKill(s32 arg0) {
    modesel_EspKill(arg0);
    modesel_AnimKill(arg0);
}

void modesel_SprKillAll(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        modesel_SprKill(i);
    }
}

void modesel_SprDispOn(s32 arg0) {
    espDispOn(modesel_sprTbl[arg0].unk_00);
}

void modesel_SprDispOff(s32 arg0) {
    espDispOff(modesel_sprTbl[arg0].unk_00);
}

void modesel_SprBGDispOn(s32 arg0) {
    modesel_SprDispOn(arg0);
}

void modesel_SprBGDispOff(s32 arg0) {
    modesel_SprDispOff(arg0);
}

void modesel_SprPosSet(s32 arg0, s32 arg1, s32 arg2) {
    modesel_sprTbl[arg0].unk_04 = arg1;
    modesel_sprTbl[arg0].unk_08 = arg2;
    espPosSet(modesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void modesel_SprPosGet(s32 arg0, s32 *x, s32 *y) {
    *x = modesel_sprTbl[arg0].unk_04;
    *y = modesel_sprTbl[arg0].unk_08;
}

void modesel_SprScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    modesel_sprTbl[arg0].unk_0C = arg1;
    modesel_sprTbl[arg0].unk_10 = arg2;
    espScaleSet(modesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void modesel_SprAlphaSet(s32 arg0, u16 arg1) {
    espTPLvlSet(modesel_sprTbl[arg0].unk_00, arg1);
}

void modesel_SprAttrSet(s32 arg0, u16 arg1) {
    espAttrSet(modesel_sprTbl[arg0].unk_00, arg1);
}

void modesel_SprAttrReset(s32 arg0, u16 arg1) {
    espAttrReset(modesel_sprTbl[arg0].unk_00, arg1);
}

void modesel_SprPriSet(s32 arg0, u16 arg1) {
    espPriSet(modesel_sprTbl[arg0].unk_00, arg1);
}

void modesel_SprBankSet(s32 arg0, u16 arg1, u16 arg2) {
    espAnimModeSet(modesel_sprTbl[arg0].unk_00, 1);
    espBankSet(modesel_sprTbl[arg0].unk_00, arg1, arg2);
}

void modesel_ModelInit(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(modesel_modelTbl); i++) {
        modesel_modelTbl[i].unk_00 = -1;
        modesel_modelTbl[i].unk_02 = -1;
    }
}

void modesel_ModelCreate(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = Hu3DModelRead(arg1, arg2);

    modesel_modelTbl[arg0].unk_00 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void modesel_MotionCreate(s32 arg0, s32 arg1, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(arg1);
    modesel_modelTbl[arg0].unk_02 = Hu3DMotionCreate(data, (s16)arg2);
    DataClose(data);
}

void modesel_ModelKill(s32 arg0) {
    if (modesel_modelTbl[arg0].unk_00 != -1) {
        Hu3DModelKill(modesel_modelTbl[arg0].unk_00);
        modesel_modelTbl[arg0].unk_00 = -1;
    }
    if (modesel_modelTbl[arg0].unk_02 != -1) {
        Hu3DMotionKill(modesel_modelTbl[arg0].unk_02);
        modesel_modelTbl[arg0].unk_02 = -1;
    }
}

void modesel_ModelKillAll(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        modesel_ModelKill(i);
    }
}

s16 modesel_ModelIdGet(s32 arg0) {
    return modesel_modelTbl[arg0].unk_00;
}

s16 modesel_MotionIdGet(s32 arg0) {
    return modesel_modelTbl[arg0].unk_02;
}

void modesel_ModelRotSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    modesel_modelTbl[arg0].unk_1C = arg1;
    modesel_modelTbl[arg0].unk_20 = arg2;
    modesel_modelTbl[arg0].unk_24 = arg3;
    Hu3DModelRotSet(modesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void modesel_ModelPosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    modesel_modelTbl[arg0].unk_04 = arg1;
    modesel_modelTbl[arg0].unk_08 = arg2;
    modesel_modelTbl[arg0].unk_0C = arg3;
    Hu3DModelPosSet(modesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void modesel_ModelScaleSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    modesel_modelScaleTbl[arg0].unk_00 = arg1;
    modesel_modelScaleTbl[arg0].unk_04 = arg2;
    modesel_modelScaleTbl[arg0].unk_08 = arg3;
    Hu3DModelScaleSet(modesel_modelTbl[arg0].unk_00, arg1, arg2, arg3);
}

void modesel_ModelPosGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = modesel_modelTbl[arg0].unk_04;
    *arg2 = modesel_modelTbl[arg0].unk_08;
    *arg3 = modesel_modelTbl[arg0].unk_0C;
}

void modesel_ModelRotGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = modesel_modelTbl[arg0].unk_1C;
    *arg2 = modesel_modelTbl[arg0].unk_20;
    *arg3 = modesel_modelTbl[arg0].unk_24;
}

void modesel_ModelScaleGet(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = modesel_modelScaleTbl[arg0].unk_00;
    *arg2 = modesel_modelScaleTbl[arg0].unk_04;
    *arg3 = modesel_modelScaleTbl[arg0].unk_08;
}

void modesel_ModelDispOff(s32 arg0) {
    Hu3DModelAttrSet(modesel_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void modesel_ModelDispOn(s32 arg0) {
    Hu3DModelAttrSet(modesel_modelTbl[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void modesel_MotionFlagSet(s32 arg0, s32 arg1) {
    Hu3DMotionAttrSet(modesel_modelTbl[arg0].unk_00, -1, arg1);
}

void modesel_MotionShiftSet(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(modesel_modelTbl[arg0].unk_00, modesel_modelTbl[arg1].unk_02, arg2, arg3, arg4);
}

void modesel_MotionFlagReset(s32 arg0, s32 arg1) {
    Hu3DMotionAttrSet(modesel_modelTbl[arg0].unk_00, arg1, 0);
}

void modesel_MotionSpeedSet(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())Hu3DMotionSpeedSet;

    setModelScale(modesel_modelTbl[arg0].unk_00);
}

void modesel_MotionTimeSet(s32 arg0, u32 arg1) {
    Hu3DMotionTimeSet(modesel_modelTbl[arg0].unk_00, arg1);
}

void modesel_MotionEndWait(s32 arg0) {
    while (Hu3DData[modesel_modelTbl[arg0].unk_00].motTime !=
           Hu3DMotion[Hu3DData[modesel_modelTbl[arg0].unk_00].motId].unk02) {
        HuPrcVSleep();
    }
}

s32 modesel_MotionEndCheck(s32 arg0) {
    s16 modelId = modesel_modelTbl[arg0].unk_00;

    return Hu3DData[modelId].motTime == Hu3DMotion[Hu3DData[modelId].motId].unk02;
}

void modesel_MotionSet(s32 arg0, s32 arg1, s16 arg2) {
    s16 modelId = modesel_ModelIdGet(arg0);
    s16 parentModelId = modesel_MotionIdGet(arg1);

    Hu3DMotionSet(modelId, parentModelId);
    Hu3DMotionAttrSet(modelId, -1, arg2);
}

void modesel_BGSprCreate(void) {
    // The original call omits the resource id.
    modesel_bgAnim = ((s16 (*)())HuSprAnimDataRead)();
    modesel_bgSpr = espEntry(modesel_bgAnim, 0, 0);
    espAttrSet(modesel_bgSpr, HUSPR_ATTR_BG);
    espPosSet(modesel_bgSpr, 0xA0, 0x78);
}

void modesel_BGSprKill(void) {
    espKill(modesel_bgSpr);
    HuSprAnimKill(modesel_bgAnim);
}

u32 modesel_WinMesConv(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = GameMesStrConv2(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

void modesel_WinCreate(s32 index, u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s32 window;
    u32 text;

    switch (style) {
        case 1:
            text = modesel_WinMesConv(message);
            window = modesel_WinType1Create(text, x, y, width, height, style);
            break;
        case 2:
            text = modesel_WinMesConv(message);
            window = modesel_WinType2Create(text, x, y, width, height, style);
            break;
        case 3:
            text = modesel_WinMesConv(message);
            window = modesel_WinType3Create(text, x, y, style);
            break;
        case 4:
            text = modesel_WinMesConv(message);
            window = modesel_WinType4Create(text, x, y, style);
            break;
        case 5:
            text = modesel_WinMesConv(message);
            window = modesel_WinType5Create(text, x, y, style);
            break;
        case 0:
            text = modesel_WinMesConv(message);
            window = modesel_WinType0Create(text, x, y, width, height, style);
            break;
        default:
            text = modesel_WinMesConv(message);
            window = modesel_WinType0Create(text, x, y, width, height, style);
            break;
    }
    if (text > 0x80000000U) {
        modesel_winMesTbl[index][0] = text;
    }
    modesel_winTbl[index][0] = window;
}

s32 modesel_WinType0Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesDefColSet(window, 192, 192, 192);
    HuWinBGColSet(window, 0, 64, 64);
    HuWinMesColSet(window, 7);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 modesel_WinType1Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 4);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinMesDefColSet(window, 192, 192, 192);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 1);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 modesel_WinType2Create(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    HuWinAttrSet(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinDummy(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 7, 255, 255, 255);
    HuWinMesPalSet(window, 0, 0, 0, 0);
    HuWinMesPalSet(window, 3, 0, 0, 0);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinMesDefColSet(window, 192, 192, 0);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 6);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 modesel_WinType3Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinExOpen(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 modesel_WinType4Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 20);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinExOpen(window, 0);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 modesel_WinType5Create(u32 message, s16 x, s16 y, s16 style) {
    s16 window = HuWinExCreateStyled(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinExOpen(window, 0);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

void modesel_WinInit(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        modesel_winTbl[i][0] = -1;
        modesel_winMesTbl[i][0] = 0;
    }
}

void modesel_WinKill(s32 arg0) {
    if (modesel_winTypeTbl[arg0][0] == 3) {
        HuWinExClose(modesel_winTbl[arg0][0], 1);
        HuWinExCleanup(modesel_winTbl[arg0][0]);
    } else {
        HuWinDispOff(modesel_winTbl[arg0][0]);
        HuWinKill(modesel_winTbl[arg0][0]);
        modesel_winTbl[arg0][0] = -1;
    }
    if (modesel_winMesTbl[arg0][0] != 0) {
        HuMemDelayFree((void *)modesel_winMesTbl[arg0][0]);
        modesel_winMesTbl[arg0][0] = 0;
    }
}

void modesel_WinKillAll(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (modesel_winTbl[i][0] != -1) {
            modesel_WinKill(i);
        }
    }
}

void modesel_WinScaleSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinScaleSet(modesel_winTbl[arg0][0], arg1, arg2);
}

void modesel_WinPosSet(s32 arg0, f32 arg1, f32 arg2) {
    HuWinPosSet(modesel_winTbl[arg0][0], arg1, arg2);
}

void modesel_WinDispOn(s32 arg0) {
    HuWinDispOn(modesel_winTbl[arg0][0]);
}

void modesel_WinDispOff(s32 arg0) {
    HuWinDispOff(modesel_winTbl[arg0][0]);
}

void modesel_WinMesSet(s32 arg0, u32 message) {
    u32 text;

    HuWinHomeClear(modesel_winTbl[arg0][0]);
    if (modesel_winMesTbl[arg0][0] != 0) {
        HuMemDelayFree((void *)modesel_winMesTbl[arg0][0]);
        modesel_winMesTbl[arg0][0] = 0;
    }
    text = modesel_WinMesConv(message);
    if (text > 0x80000000U) {
        modesel_winMesTbl[arg0][0] = text;
    }
    HuWinMesSet(modesel_winTbl[arg0][0], text, -1, -1);
}

void modesel_WinInsertMesSet(s32 arg0, s8 arg1, u32 arg2) {
    HuWinInsertMesSetNoLF(modesel_winTbl[arg0][0], arg2, arg1);
}

s32 modesel_WinChoiceGet(s32 arg0, s16 arg1, s32 arg2) {
    return HuWinChoiceGet(modesel_winTbl[arg0][0], arg1, arg2);
}

s16 modesel_WinIdGet(s32 arg0) {
    return modesel_winTbl[arg0][0];
}

void modesel_WinMesWait(s32 arg0) {
    while (HuWinStatGet(modesel_winTbl[arg0][0]) != 0) {
        HuPrcVSleep();
    }
}

void modesel_PadBtnWait(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & HuPadBtnDown[0]));
}

void modesel_WinPriSet(s32 arg0, s16 arg1) {
    HuWinPriSet(modesel_winTbl[arg0][0], arg1);
}

u16 modesel_CameraDebugExec(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (HuPadBtnDown[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (HuPadBtnDown[0] & Z_TRIG) {
            camera = Hu3DData[gCameraList[0].unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", camera->unk08, camera->unk0C, camera->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", camera->unk14, camera->unk18, camera->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", camera->unk20, camera->unk24, camera->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return HuPadBtnDown[0];
}

void modesel_PlayerPadInit(void) {
    s16 i;
    s16 count;
    s16 pad;
    s16 player;

    for (i = 0; i < 4; i++) {
        GwPlayer[i].pad = 0xFF;
    }
    for (i = 0, count = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            GwPlayer[count].pad = i;
            count++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].pad == 0xFF) {
            for (pad = 0; pad < 4; pad++) {
                for (player = 0; player < 4; player++) {
                    if (GwPlayer[player].pad == pad) {
                        break;
                    }
                }
                if (player == 4) {
                    break;
                }
            }
            GwPlayer[i].pad = pad;
        }
    }
}

void modesel_MainCreate(void) {
    modesel_UtilInit();
    modesel_mainProc = omAddPrcObj(modesel_MainProc, 0x5000, 0x2000, 0);
}

const char modesel_emptyStr[] = "";

void modesel_MainProc(void) {
    s32 i;
    s32 j;
    s32 board;
    s32 complete;
    s32 result;
    s16 modelId;
    omOvlHisData *history;

    modesel_storyChr = 0;
    for (i = 0; i < 6; i++) {
        if (MgStoryRankGet(i) >= 0) {
            modesel_storyChr = i;
            break;
        }
    }
    if (_CheckFlag(0x21)) {
        modesel_storyChr = 0;
    } else if (_CheckFlag(0x22)) {
        modesel_storyChr = 1;
    } else if (_CheckFlag(0x23)) {
        modesel_storyChr = 2;
    } else if (_CheckFlag(0x24)) {
        modesel_storyChr = 3;
    } else if (_CheckFlag(0x25)) {
        modesel_storyChr = 4;
    } else if (_CheckFlag(0x26)) {
        modesel_storyChr = 5;
    }
    Hu3DBGColorSet(0, 0x40, 0x40);
    Hu3DScreenClearF = 0;
    modesel_StarBobInit();
    modesel_BoardStatRead();
    modesel_StageCreate();
    modesel_SpotEffInit();
    modesel_CameraMoveInit();
    modesel_FileInfoCreate();
    modesel_FileInfoDispOn();
    if (GwStory.unk0 == 12 && FileSelEnteredGet() == 0) {
        HuAudSeqPlay(0x29);
    } else {
        HuAudSeqPlay(4);
    }
    modesel_cameraProc = modesel_CameraMotionStart();
    if (omovlevtno != 1) {
        if (omovlevtno == 2) {
            WipeColorSet(0xFF, 0xFF, 0xFF);
        }
        WipeCreateIn(WIPE_FADE, 0x10);
        modelId = modesel_ModelIdGet(0xB);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DCameraMotionSet(modelId, 0);
        HuPrcSleep(0x10);
    } else {
        WipeColorSet(0xFF, 0xFF, 0xFF);
        WipeCreateIn(WIPE_FADE, 0x10);
        modesel_FileInfoDispOff();
        HuPrcSleep(1);
        modesel_MotionTimeSet(0xD, 0);
        modesel_MotionFlagReset(0xD, 1);
        HuPrcSleep(0xF);
        modesel_MotionEndWait(0xD);
        modelId = modesel_ModelIdGet(0xB);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DCameraMotionSet(modelId, 0);
        modesel_FileInfoDispOn();
    }
    if (FileSelEnteredGet() == 1) {
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            modesel_MotionTimeSet(5, 0);
            modesel_MotionFlagReset(5, 1);
            modesel_MotionEndWait(5);
        }
    } else if (_CheckFlag(0x28)) {
        modesel_MotionTimeSet(5, 0);
        modesel_MotionFlagReset(5, 1);
        modesel_MotionEndWait(5);
    }
    if (GwStory.unk0 == 12 && FileSelEnteredGet() == 0) {
        omDelPrcObj(modesel_cameraProc);
        modesel_cameraProc = modesel_CameraManualStart();
        modesel_hostObj = modesel_HostFloatCreate(10);
    } else {
        modesel_hostObj = modesel_HostEnterCreate(10);
    }
    modesel_ModelDispOn(10);
    HuPrcSleep(0x28);
    modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
    HuAudFXPlay(0x159);
    if (FileSelEnteredGet() == 1) {
        if (ModeSelIntroShownGet() == 0) {
            modesel_WinCreate(0, 0x3100, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
            HuPrcSleep(0x1E);
            modesel_WinMesWait(0);
            board = -1;
            if (_CheckFlag(0x21)) {
                board = 0;
            } else if (_CheckFlag(0x22)) {
                board = 1;
            } else if (_CheckFlag(0x23)) {
                board = 2;
            } else if (_CheckFlag(0x24)) {
                board = 3;
            } else if (_CheckFlag(0x25)) {
                board = 4;
            } else if (_CheckFlag(0x26)) {
                board = 5;
            }
            _ClearFlag(0x21);
            _ClearFlag(0x22);
            _ClearFlag(0x23);
            _ClearFlag(0x24);
            _ClearFlag(0x25);
            _ClearFlag(0x26);
            if (board != -1) {
                modesel_WinMesSet(0, 0x311A);
                modesel_WinInsertMesSet(0, 0, board + 0x1C00);
                modesel_WinMesWait(0);
                complete = 1;
                for (j = 0; j < 12; j++) {
                    if (GwStory.unk10[board][j] < 4) {
                        complete = 0;
                    }
                }
                if (GwStory.unk58[board] < 4) {
                    complete = 0;
                }
                if (complete) {
                    modesel_WinMesSet(0, 0x313B);
                    modesel_WinMesWait(0);
                    modesel_WinKill(0);
                    modesel_WinCreate(0, (u32)modesel_emptyStr, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
                }
            }
            ModeSelIntroShownSet(1);
            modesel_WinMesSet(0, 0x3101);
        } else {
            modesel_WinCreate(0, 0x3101, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
        }
        modesel_WinMesWait(0);
        HuPrcVSleep();
    } else if (GwStory.unk0 == 12) {
        modesel_WinCreate(0, 0x3136, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
        modesel_WinMesWait(0);
        modesel_WinMesSet(0, 0x3119);
        modesel_WinMesWait(0);
    } else {
        board = -1;
        if (_CheckFlag(0x21)) {
            board = 0;
        } else if (_CheckFlag(0x22)) {
            board = 1;
        } else if (_CheckFlag(0x23)) {
            board = 2;
        } else if (_CheckFlag(0x24)) {
            board = 3;
        } else if (_CheckFlag(0x25)) {
            board = 4;
        } else if (_CheckFlag(0x26)) {
            board = 5;
        }
        _ClearFlag(0x21);
        _ClearFlag(0x22);
        _ClearFlag(0x23);
        _ClearFlag(0x24);
        _ClearFlag(0x25);
        _ClearFlag(0x26);
        if (board != -1) {
            modesel_WinCreate(0, (u32)modesel_emptyStr, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
            modesel_WinMesSet(0, 0x311A);
            modesel_WinInsertMesSet(0, 0, board + 0x1C00);
            modesel_WinMesWait(0);
            complete = 1;
            for (j = 0; j < 12; j++) {
                if (GwStory.unk10[board][j] < 4) {
                    complete = 0;
                }
            }
            if (GwStory.unk58[board] < 4) {
                complete = 0;
            }
            if (complete) {
                modesel_WinMesSet(0, 0x313B);
                modesel_WinMesWait(0);
            }
            modesel_WinKill(0);
        }
        board = modesel_BoardNoGet(GwStory.unk0);
        modesel_WinCreate(0, (u32)modesel_emptyStr, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
        modesel_WinInsertMesSet(0, 0, board + 0x3127);
        modesel_WinMesSet(0, 0x3134);
        modesel_WinMesWait(0);
    }
    modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
    result = modesel_MenuExec();
    Hu3DScreenClearF = 1;
    if (result == 16) {
        WipeColorSet(0xFF, 0xFF, 0xFF);
    }
    WipeCreateOut(WIPE_FADE, 0x14);
    HuAudSeqFadeOut(0x14);
    HuPrcSleep(0x14);
    modesel_WinKill(0);
    modesel_CameraMoveKill();
    modesel_CameraMotionStop(modesel_cameraProc);
    modesel_FileInfoKill();
    modesel_SpotEffKillAll();
    modesel_StageKill();
    omDelPrcObj(modesel_mainProc);
    HuWinAllKill();
    omOvlKill();
    switch (result) {
        case 0:
            omOvlCallEx(staff, modesel_storyChrHalf, 0x4000);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 1:
            omOvlCallEx(option, 0, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 2:
            while (1) {
                HuPrcVSleep();
            }
        case 4:
            GwSystem.playMode = (GwSystem.playMode & 4) | 2;
            omOvlCallEx(msetup, 1, 0x4090);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 5:
            SLLoadBoardStory();
            _SetFlag(0);
            GwSystem.playMode = 2;
            omOvlCallEx(duelcall, 0, 0x4090);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 6:
            GwSystem.playMode = 2;
            omOvlCallEx(msetup, 8, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 7:
            GwSystem.playMode = 1;
            omOvlCallEx(msetup, 0, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 8:
            SLLoadBoard();
            GwSystem.playMode = 1;
            _SetFlag(0);
            omOvlCallEx(boardcall, 0, 0x92);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 9:
            GwSystem.playMode = (GwSystem.playMode & 4) | 1;
            omOvlCallEx(msetup, 7, 0x91);
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 10:
            if (GwStory.unk0 == 12) {
                omOvlCallEx(stardust_battle, 0, 0x94);
                omOvlHisChg(1, 0x77, 0, 0x91);
                MgStoryStageGoto();
                modesel_PlayerPadInit();
            } else if (GwSystem.playMode & 1) {
                omOvlCallEx(msetup, 2, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            } else {
                omOvlCallEx(msetup, 3, 0x91);
                omOvlHisChg(1, 0x77, 0, 0x91);
            }
            break;
        case 11:
            SLLoadStory();
            _SetFlag(0);
            if (GwStory.unk0 == 12) {
                while (1) {
                    HuPrcVSleep();
                }
            }
            if (GwSystem.playMode & 1) {
                omOvlCallEx(boardcall, 0, 0x92);
            } else {
                omOvlCallEx(duelcall, 0, 0x4090);
            }
            omOvlHisChg(1, 0x77, 0, 0x91);
            history = &omovlhis[omovlhisidx];
            history->overlayID = 0x7D;
            history->event = 0;
            history->stat = 0x4090;
            omovlhisidx++;
            break;
        case 12:
            break;
        case 13:
            if (FileSelEnteredGet() == 1) {
                omOvlCallEx(msetup, 5, 0x91);
            } else {
                omOvlCallEx(msetup, 6, 0x91);
            }
            omOvlHisChg(1, 0x77, 0, 0x91);
            break;
        case 14:
            omOvlCallEx(stardust_battle, 0, 0x94);
            omOvlHisChg(1, 0x77, 0, 0x91);
            MgStoryStageGoto();
            modesel_PlayerPadInit();
            break;
        case 3:
        case 15:
        case 16:
        default:
            omOvlHisChg(1, 0x7A, 0, 0x92);
            if ((u16)omOvlReturnEx(1) == 0) {
                osSyncPrintf("\n%d:omMapReturn ERROR!\n", 944);
            }
            break;
    }
    while (1) {
        HuPrcVSleep();
    }
}

void modesel_CameraMotionProc(void) {
    Hu3DCameraPerspectiveSet(0, modesel_cameraFov, modesel_cameraNear, modesel_cameraFar);
    while (1) {
        modesel_CameraMotionApply(0);
        HuPrcVSleep();
    }
}

void modesel_CameraProc(void) {
    do {
        modesel_CameraViewSet(&modesel_cameraWork.pos, &modesel_cameraWork.at, &modesel_cameraWork.up);
        HuPrcVSleep();
    } while (1);
}

void modesel_CameraProcKill(Process *arg0) {
    Vec pos;
    Vec at;
    Vec up;

    modesel_CameraMotionPosGet(&pos, &at, &up);
    modesel_CameraViewSet(&pos, &at, &up);
    omDelPrcObj(arg0);
}

Process *modesel_CameraManualStart(void) {
    modesel_CameraMotionPosGet(&modesel_cameraWork.pos, &modesel_cameraWork.at, &modesel_cameraWork.up);
    return omAddPrcObj(modesel_CameraProc, 0x5000, 0x1800, 0);
}

void modesel_CameraPosGet(Vec *pos, Vec *at, Vec *up) {
    HuVecCopy3F(pos, &modesel_cameraWork.pos);
    HuVecCopy3F(at, &modesel_cameraWork.at);
    HuVecCopy3F(up, &modesel_cameraWork.up);
}

void modesel_CameraPosSet(Vec *pos, Vec *at, Vec *up) {
    HuVecCopy3F(&modesel_cameraWork.pos, pos);
    HuVecCopy3F(&modesel_cameraWork.at, at);
    HuVecCopy3F(&modesel_cameraWork.up, up);
}

void modesel_CameraMotionApply(s32 arg0) {
    Vec pos;
    Vec at;
    Vec up;

    modesel_CameraMotionPosGet(&pos, &at, &up);
    modesel_CameraViewSet(&pos, &at, &up);
}

s32 modesel_CameraMotionPosGet(Vec *pos, Vec *at, Vec *up) {
    HmfData_UnkBC *cam;
    f32 angle;
    f32 dx, dy, dz;
    f32 upX, upY, upZ;
    f32 length;

    cam = Hu3DData[gCameraList->unk4].hmf->unkBC;
    pos->x = cam->unk08;
    pos->y = cam->unk0C;
    pos->z = cam->unk10;
    at->x = cam->unk14;
    at->y = cam->unk18;
    at->z = cam->unk1C;
    angle = -90.0f;
    dx = at->x - pos->x;
    dy = at->y - pos->y;
    dz = at->z - pos->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    upX = dy * dz - dz * (dy + 1.0f);
    upY = dz * dx - dz * dx;
    upZ = dx * (dy + 1.0f) - dy * dx;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(angle)) +
            upY * (dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle)) +
            upZ * (dx * dz * (1.0f - cosdf(angle)) + dy * sindf(angle));
    up->y = upX * (dx * dy * (1.0f - cosdf(angle)) + dz * sindf(angle)) +
            upY * (dy * dy + (1.0f - dy * dy) * cosdf(angle)) +
            upZ * (dy * dz * (1.0f - cosdf(angle)) - dx * sindf(angle));
    up->z = upX * (dx * dz * (1.0f - cosdf(angle)) - dy * sindf(angle)) +
            upY * (dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle)) +
            upZ * (dz * dz + (1.0f - dz * dz) * cosdf(angle));
    return 1;
}

void modesel_CameraViewSet(Vec *pos, Vec *at, Vec *up) {
    Hu3DCameraPosSetV(0, pos, at, up);
    Hu3DCamUpdateMtx(0);
}

void modesel_CameraMoveInit(void) {
    modesel_cameraMove.obj = NULL;
}

void modesel_CameraEaseObjMain(omObjData *obj) {
    Vec camPos;
    Vec at;
    Vec up;
    Vec start;
    Vec end;
    Vec pos;
    f32 t;
    f32 s;

    HuVecCopy3F(&start, &modesel_cameraMove.unk_10);
    HuVecCopy3F(&end, &modesel_cameraMove.unk_1C);
    t = (f32)modesel_cameraMove.unk_04 / (f32)modesel_cameraMove.unk_08;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        s = 1.0f;
    } else {
        s = sindf(t * 90.0f);
    }
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * s, start.y + (end.y - start.y) * s,
                 start.z + (end.z - start.z) * s);
    modesel_CameraPosGet(&camPos, &at, &up);
    if (modesel_cameraMove.unk_04 > modesel_cameraMove.unk_08) {
        omDelObj(obj);
        modesel_CameraPosSet(&camPos, &end, &up);
        modesel_cameraMove.obj = NULL;
    } else {
        modesel_cameraMove.unk_04++;
        modesel_CameraPosSet(&camPos, &pos, &up);
    }
}

void modesel_CameraMoveKill(void) {
    if (modesel_cameraMove.obj != NULL) {
        omDelObj(modesel_cameraMove.obj);
    }
    modesel_cameraMove.obj = NULL;
}

omObjData *modesel_CameraEaseMove(s32 arg0, s32 arg1) {
    omObjData *obj;
    Vec pos;
    Vec at;
    Vec up;
    Vec target;

    if (modesel_cameraMove.obj != NULL) {
        omDelObj(modesel_cameraMove.obj);
    }
    obj = omAddObj(6, 0, 0, -1, modesel_CameraEaseObjMain);
    obj->work[0] = 0;
    obj->work[1] = 0;
    modesel_cameraMove.obj = obj;
    modesel_cameraMove.unk_04 = 0;
    modesel_cameraMove.unk_08 = arg1;
    modesel_cameraMove.unk_0C = arg0;
    modesel_CameraPosGet(&pos, &at, &up);
    HuVecCopyXYZ(&modesel_cameraMove.unk_10, at.x, at.y, at.z);
    if (arg0 < 0) {
        target.x = 0.0f;
    } else {
        modesel_SpotPosGet(arg0, &target.x, &target.y, &target.z);
    }
    target.y = at.y;
    target.z = at.z;
    HuVecCopyXYZ(&modesel_cameraMove.unk_1C, target.x, target.y, target.z);
    return obj;
}

void modesel_CameraShakeObjMain(omObjData *obj) {
    Vec pos;
    Vec at;
    s32 timer = modesel_cameraShake.unk_04;
    f32 shake;

    HuVecCopy3F(&pos, &modesel_cameraShake.pos);
    HuVecCopy3F(&at, &modesel_cameraShake.at);
    if (timer > 32) {
        omDelObj(obj);
        modesel_cameraShake.unk_00 = NULL;
        timer = 0;
    } else {
        modesel_cameraShake.unk_08 = ~modesel_cameraShake.unk_08;
        if (modesel_cameraShake.unk_08 != 0) {
            shake = rand8();
        } else {
            shake = -(f32)rand8();
        }
        shake = shake * (1.0f / 255.0f) * ((1.0f - timer * (1.0f / 32.0f)) * 0.8f + 0.2f);
        pos.y += shake * 40.0f;
        at.y += shake * 40.0f;
    }
    modesel_CameraPosSet(&pos, &at, &modesel_cameraShake.up);
    modesel_cameraShake.unk_04 = timer + 1;
}

void modesel_CameraShakeKill(void) {
    if (modesel_cameraShake.unk_00 != NULL) {
        omDelObj(modesel_cameraShake.unk_00);
        modesel_cameraShake.unk_00 = NULL;
    }
}

void modesel_CameraShakeCreate(void) {
    modesel_cameraShake.unk_00 = omAddObj(6, 0, 0, -1, modesel_CameraShakeObjMain);
    modesel_cameraShake.unk_04 = 0;
    modesel_CameraPosGet(&modesel_cameraShake.pos, &modesel_cameraShake.at, &modesel_cameraShake.up);
    modesel_cameraShake.unk_08 = 1;
}

f32 modesel_CameraAngleCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return -(atan2df(arg3 - arg1, arg2 - arg0) - 90.0f);
}

void modesel_CameraDirLerp(Vec *from, Vec *to, f32 t, Vec *out) {
    f32 fromAngle;
    f32 toAngle;
    f32 endAngleCw;
    f32 endAngleCcw;
    f32 angle;

    fromAngle = modesel_CameraAngleCalc(0.0f, 0.0f, from->x, from->z);
    if (fromAngle < 0.0f) {
        fromAngle += 360.0f;
    }
    toAngle = modesel_CameraAngleCalc(0.0f, 0.0f, to->x, to->z);
    if (toAngle < 0.0f) {
        toAngle += 360.0f;
    }
    if (-from->z * to->x + from->x * to->z > 0.0f) {
        endAngleCw = toAngle;
        if (!(toAngle - fromAngle < 0.0f)) {
            endAngleCw = toAngle - 360.0f;
        }
        angle = (endAngleCw - fromAngle) * t + fromAngle;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        // The do-while ends the CSE block, so CSE keeps using toAngle (not endAngleCcw) below.
        do {
            endAngleCcw = toAngle;
        } while (0);
        if (!(0.0f < toAngle - fromAngle)) {
            endAngleCcw = toAngle + 360.0f;
        }
        angle = (endAngleCcw - fromAngle) * t + fromAngle;
        if (360.0f < angle) {
            angle -= 360.0f;
        }
    }
    out->x = sindf(angle);
    out->y = 0.0f;
    out->z = cosdf(angle);
}

void modesel_CameraTurnEaseObjMain(omObjData *obj) {
    Vec pos, at, up, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)modesel_cameraMove.unk_04 / modesel_cameraMove.unk_08;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    modesel_CameraPosGet(&pos, &at, &up);
    HuVecCopy3F(&startAt, &modesel_cameraMove.unk_10);
    HuVecCopy3F(&endAt, &modesel_cameraMove.unk_1C);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - pos.x, 0.0f, startAt.z - pos.z);
    HuVecCopyXYZ(&endDir, endAt.x - pos.x, 0.0f, endAt.z - pos.z);
    angleT = sindf(clamped * 90.0f);
    modesel_CameraDirLerp(&startDir, &endDir, angleT, &direction);
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * angleT + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x, (endAt.y - startAt.y) + startAt.y, t * direction.z + pos.z);
    if (modesel_cameraMove.unk_04 > modesel_cameraMove.unk_08) {
        omDelObj(obj);
        modesel_CameraPosSet(&pos, &modesel_cameraMove.unk_1C, &up);
        modesel_cameraMove.obj = NULL;
    } else {
        modesel_cameraMove.unk_04++;
        modesel_CameraPosSet(&pos, &at, &up);
    }
}

omObjData *modesel_CameraTurnEaseMove(s32 arg0, s32 arg1) {
    omObjData *obj;
    Vec pos;
    Vec at;
    Vec up;

    if (modesel_cameraMove.obj != NULL) {
        omDelObj(modesel_cameraMove.obj);
    }
    obj = omAddObj(6, 0, 0, -1, modesel_CameraTurnEaseObjMain);
    obj->work[0] = 0;
    obj->work[1] = 0;
    modesel_cameraMove.obj = obj;
    modesel_cameraMove.unk_04 = 0;
    modesel_cameraMove.unk_08 = arg1;
    modesel_cameraMove.unk_0C = arg0;
    modesel_CameraPosGet(&pos, &at, &up);
    HuVecCopy3F(&modesel_cameraMove.unk_10, &at);
    if (arg0 < 0) {
        at.x = 0.0f;
    } else {
        modesel_SpotPosGet(arg0, &at.x, &at.y, &at.z);
    }
    HuVecCopyXYZ(&modesel_cameraMove.unk_1C, at.x, at.y, at.z);
    return obj;
}

s32 modesel_StickBtnGet(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;

    stickX = HuPadStkX[arg0];
    stickY = HuPadStkY[arg0];
    if (modesel_stickBtn != 0) {
        if ((stickX == 0) & (stickY == 0)) {
            modesel_stickBtn = 0;
        }
        return 0;
    }
    if ((stickX != 0) | (stickY != 0)) {
        absX = __builtin_abs(stickX);
        absY = __builtin_abs(stickY);
        if (absY < absX) {
            if (absX > absY * 2) {
                if (stickX < 0) {
                    modesel_stickBtn = 0x200;
                } else {
                    modesel_stickBtn = 0x100;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    modesel_stickBtn = 0xA00;
                } else {
                    modesel_stickBtn = 0x900;
                }
            } else {
                if (stickX < 0) {
                    modesel_stickBtn = 0x600;
                } else {
                    modesel_stickBtn = 0x500;
                }
            }
        } else {
            if (absY > absX * 2) {
                if (stickY < 0) {
                    modesel_stickBtn = 0x400;
                } else {
                    modesel_stickBtn = 0x800;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    modesel_stickBtn = 0xA00;
                } else {
                    modesel_stickBtn = 0x900;
                }
            } else {
                if (stickX < 0) {
                    modesel_stickBtn = 0x600;
                } else {
                    modesel_stickBtn = 0x500;
                }
            }
        }
    }
    return modesel_stickBtn;
}

void modesel_StarBobInit(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        modesel_starBobTbl[i].unk_08 = NULL;
        modesel_starBobTbl[i].unk_04 = 0;
        modesel_starBobTbl[i].unk_00 = 0;
    }
}

void modesel_StarBobObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 angle = timer * (360.0f / 255.0f);
    f32 wave = sindf(angle);

    modesel_ModelIdGet(index);
    modesel_StarNodeSet(index, 0.0f, wave * 8.0f + 8.0f + 8.0f, 0.0f, wave * 16.0f + 20.0f);
    obj->work[1] = timer + 4;
}

void modesel_StarBobKill(s32 arg0) {
    s32 i = arg0 - 7;

    if (modesel_starBobTbl[i].unk_08 != NULL) {
        omDelObj(modesel_starBobTbl[i].unk_08);
    }
    modesel_starBobTbl[i].unk_08 = NULL;
}

omObjData *modesel_StarBobCreate(s32 arg0) {
    s32 i = arg0 - 7;
    omObjData *obj;

    if (modesel_starBobTbl[i].unk_08 != NULL) {
        modesel_StarBobKill(arg0);
    }
    obj = omAddObj(6, 0, 0, -1, modesel_StarBobObjMain);
    modesel_starBobTbl[i].unk_08 = obj;
    obj->work[0] = arg0;
    obj->work[1] = rand8();
    modesel_starBobTbl[i].unk_00 = 0;
    modesel_starBobTbl[i].unk_04 = 0;
    return obj;
}

void modesel_StarLandObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 i = index - 7;
    s32 timer = obj->work[1];
    f32 t = timer * 0.1f;
    f32 scale;

    t = 1.0f - t;
    scale = (t < 0.0f) ? 0.0f : t;

    modesel_StarNodeSet(index, 0.0f, (modesel_starBobTbl[i].unk_0C.y - 10.0f) * scale + 10.0f, 0.0f, 0.0f);
    if (timer < 10) {
        timer++;
    }
    obj->work[1] = timer;
}

omObjData *modesel_StarLandCreate(s32 arg0) {
    s32 i = arg0 - 7;
    omObjData *obj = modesel_starBobTbl[i].unk_08;
    f32 wave;

    if (obj != NULL) {
        wave = (s32)obj->work[1];
        wave = sindf(wave * (360.0f / 255.0f));
        HuVecCopyXYZ(&modesel_starBobTbl[i].unk_0C, 0.0f, wave * 8.0f + 8.0f + 8.0f, 0.0f);
        omDelObj(modesel_starBobTbl[i].unk_08);
    } else {
        HuVecCopyXYZ(&modesel_starBobTbl[i].unk_0C, 0.0f, 0.0f, 0.0f);
    }
    modesel_starBobTbl[i].unk_08 = omAddObj(6, 0, 0, -1, modesel_StarLandObjMain);
    modesel_starBobTbl[i].unk_04 = 0;
    // Writes to the previous (possibly deleted) object rather than the new one.
    obj->work[0] = arg0;
    return obj;
}

// Toggles the spinner's model when work[1] wraps over its 0..200 range: the
// second argument to modesel_MotionFlagSet is the model's visibility.
void modesel_StarBlinkObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];

    if (timer == 200) {
        modesel_MotionFlagSet(index, 0);
    } else if (timer == 0) {
        modesel_MotionFlagSet(index, 1);
    }
    timer += 4;
    obj->work[1] = timer;
}

void modesel_StarBlinkCreate(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_StarBlinkObjMain);

    obj->work[0] = arg0;
    obj->work[1] = 0;
}

void modesel_StarFallObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * (1.0f / 255.0f);
    Vec pos;
    f32 shadowY;

    pos.x = modesel_starPosTbl[index - 7].x;
    pos.y = modesel_starPosTbl[index - 7].y;
    pos.z = modesel_starPosTbl[index - 7].z;
    pos.y -= t * 400.0f;
    modesel_ModelPosSet(index, 0.0f, 0.0f, 0.0f);
    shadowY = pos.y + 20.0f - 12.0f;
    if (shadowY < 0.0f) {
        shadowY = 0.0f;
    }
    modesel_StarNodePosSet(index, pos.x, pos.y, pos.z, shadowY);
    modesel_StarNodeRotSet(index, 0);
    modesel_StarNodeUpdate(index);
    timer += 20;
    if (timer == 100) {
        // Empty in the original; the comparison is still emitted.
    } else if (timer >= 256) {
        omDelObj(obj);
        modesel_ModelDispOff(index);
    }
    obj->work[1] = timer;
}

void modesel_StarHoldObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    Vec pos;
    f32 shadowY;

    pos.x = modesel_starPosTbl[index - 7].x;
    pos.y = modesel_starPosTbl[index - 7].y;
    pos.z = modesel_starPosTbl[index - 7].z;
    modesel_ModelPosSet(index, 0.0f, 0.0f, 0.0f);
    shadowY = pos.y + 20.0f - 12.0f;
    if (shadowY < 0.0f) {
        shadowY = 0.0f;
    }
    modesel_StarNodePosSet(index, pos.x, pos.y, pos.z, shadowY);
    modesel_StarNodeRotSet(index, 0);
    modesel_StarNodeUpdate(index);
    timer++;
    if (timer > 20) {
        HuAudFXPlay(0x2E2);
        obj->func = modesel_StarFallObjMain;
        obj->work[1] = 0;
    }
    obj->work[1] = timer;
}

void modesel_StarSpinObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    Vec pos;

    pos.x = modesel_starPosTbl[index - 7].x;
    pos.y = modesel_starPosTbl[index - 7].y;
    pos.z = modesel_starPosTbl[index - 7].z;
    modesel_ModelPosSet(index, 0.0f, 0.0f, 0.0f);
    modesel_StarNodePosSet(index, pos.x, pos.y, pos.z, pos.y + 20.0f - 12.0f);
    modesel_StarNodeRotAdd(index, 35.5f);
    modesel_StarNodeUpdate(index);
    timer += 20;
    if (timer >= 256) {
        timer = 0;
        modesel_starPosTbl[index - 7].x = pos.x;
        modesel_starPosTbl[index - 7].y = pos.y;
        modesel_starPosTbl[index - 7].z = pos.z;
        obj->func = modesel_StarHoldObjMain;
    }
    obj->work[1] = timer;
}

void modesel_StarJumpObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * (1.0f / 255.0f);
    f32 s = (t < 1.0) ? t : 1.0f;
    f32 u = s * -5.0f * (s - 1.2f);
    Vec start;
    Vec end;
    Vec pos;

    start.x = modesel_starPosTbl[index - 7].x;
    start.y = modesel_starPosTbl[index - 7].y;
    start.z = modesel_starPosTbl[index - 7].z;
    HuVecCopyXYZ(&end, 0.0f, 200.0f, 300.0f);
    pos.x = start.x + (end.x - start.x) * t;
    pos.y = start.y + (end.y - start.y) * u;
    pos.z = start.z + (end.z - start.z) * t;
    modesel_ModelPosSet(index, 0.0f, 0.0f, 0.0f);
    modesel_StarNodePosSet(index, pos.x, pos.y, pos.z, pos.y + 20.0f - 12.0f);
    modesel_StarNodeRotAdd(index, 35.5f);
    modesel_StarNodeUpdate(index);
    timer += 12;
    if (timer >= 256) {
        obj->work[1] = 0;
        modesel_starPosTbl[index - 7].x = pos.x;
        modesel_starPosTbl[index - 7].y = pos.y;
        modesel_starPosTbl[index - 7].z = pos.z;
        obj->func = modesel_StarSpinObjMain;
    } else {
        obj->work[1] = timer;
    }
}

void modesel_StarJumpCreate(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_StarJumpObjMain);

    obj->work[0] = arg0;
    obj->work[1] = 0;
}

void modesel_HostFloatObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 bob;
    f32 angle;
    f32 diff;
    Vec pos;
    Vec base;
    Vec camPos;
    Vec camAt;
    Vec camUp;
    f32 x;
    f32 y;
    f32 z;

    // diff is reused to hold the float timer; a separate temporary changes register allocation.
    diff = timer;
    bob = sindf(diff * 1.4117647f);
    HuVecCopy3F(&base, &modesel_hostPos);
    HuVecCopyXYZ(&pos, base.x, base.y + bob * 5.0f * 5.0f, base.z);
    modesel_ModelPosSet(index, pos.x, pos.y, pos.z);
    timer++;
    modesel_CameraPosGet(&camPos, &camAt, &camUp);
    modesel_ModelPosGet(10, &x, &y, &z);
    angle = modesel_hostRotY;
    diff = modesel_LookAtAngleCalc(camPos.x - x, camPos.z - z);
    diff -= angle;
    if (diff < -2.0f) {
        angle -= 2.0f;
    }
    angle = (angle < 0.0f) ? angle + 360.0f : angle;
    angle = (diff > 2.0f) ? angle + 2.0f : angle;
    angle = (angle > 360.0f) ? angle - 360.0f : angle;
    modesel_hostRotY = angle;
    modesel_ModelRotSet(10, 0.0f, angle, 0.0f);
    obj->work[1] = timer;
}

void modesel_HostEnterObjMain(omObjData *obj) {
    Vec pos;
    Vec start;
    Vec end;
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * 0.05f;
    f32 s;
    f32 u;

    s = (1.0f < t) ? 1.0f : t * t;
    u = s * -3.0f * (s - 1.3333334f);
    HuVecCopy3F(&start, &modesel_hostPos);
    HuVecCopy3F(&end, &modesel_hostEndPos);
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * s, start.y + (end.y - start.y) * u,
                 start.z + (end.z - start.z) * s);
    modesel_ModelPosSet(index, pos.x, pos.y, pos.z);
    if (timer > 20) {
        obj->func = modesel_HostFloatObjMain;
        HuVecCopy3F(&modesel_hostPos, &pos);
        timer = 0;
    } else {
        timer++;
    }
    obj->work[1] = timer;
}

omObjData *modesel_HostEnterCreate(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_HostEnterObjMain);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    modesel_ModelPosGet(arg0, &modesel_hostPos.x, &modesel_hostPos.y, &modesel_hostPos.z);
    HuVecCopyXYZ(&modesel_hostEndPos, 0.0f, 25.0f, 300.0f);
    modesel_hostRotY = 0.0f;
    return obj;
}

omObjData *modesel_HostFloatCreate(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_HostFloatObjMain);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    modesel_ModelPosGet(arg0, &modesel_hostPos.x, &modesel_hostPos.y, &modesel_hostPos.z);
    modesel_hostRotY = 0.0f;
    return obj;
}

void modesel_HostExitObjMain(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * 0.05f;

    HuVecCopy3F(&start, &modesel_hostPos);
    HuVecCopy3F(&end, &modesel_hostEndPos);
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t,
                 start.z + (end.z - start.z) * t);
    modesel_ModelPosSet(index, pos.x, pos.y, pos.z);
    if (timer < 21) {
        timer++;
    }
    obj->work[1] = timer;
}

omObjData *modesel_HostExitCreate(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_HostExitObjMain);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    modesel_ModelPosGet(arg0, &modesel_hostPos.x, &modesel_hostPos.y, &modesel_hostPos.z);
    HuVecCopyXYZ(&modesel_hostEndPos, 0.0f, -400.0f, 300.0f);
    return obj;
}

void modesel_HostLookAtUpdate(void) {
    Vec modelPos;
    Vec pos;
    Vec at;
    Vec up;

    modesel_ModelPosGet(0xA, &modelPos.x, &modelPos.y, &modelPos.z);
    modesel_CameraPosGet(&pos, &at, &up);
    modesel_ModelRotSet(0xA, 0.0f, modesel_LookAtAngleCalc(pos.x - modelPos.x, pos.z - modelPos.z), 0.0f);
}

void modesel_HostFallObjMain(omObjData *obj) {
    Vec pos;
    s32 model = 10;
    s32 timer = obj->work[0];
    f32 t = timer * (1.0f / 255.0f);
    // Retain the unused jump interpolation clamp for matching register allocation.
    f32 s = (t < 1.0) ? t : 1.0f;

    pos.x = modesel_hostJumpPosTbl[1].x;
    pos.y = modesel_hostJumpPosTbl[1].y - t * 400.0f;
    pos.z = modesel_hostJumpPosTbl[1].z;
    modesel_ModelPosSet(model, pos.x, pos.y, pos.z);
    modesel_HostLookAtUpdate();
    timer += 20;
    if (timer >= 256) {
        omDelObj(obj);
        modesel_ModelDispOff(model);
    }
    obj->work[0] = timer;
}

void modesel_HostWaitObjMain(omObjData *obj) {
    s32 timer = obj->work[0];

    modesel_HostLookAtUpdate();
    timer++;
    if (timer >= 31) {
        obj->func = modesel_HostFallObjMain;
        timer = 0;
    }
    obj->work[0] = timer;
}

void modesel_HostJumpObjMain(omObjData *obj) {
    Vec pos;
    s32 timer = obj->work[0];
    f32 t = timer * (1.0f / 255.0f);
    f32 s = (t < 1.0) ? t : 1.0f;

    pos.x = (modesel_hostJumpPosTbl[1].x - modesel_hostJumpPosTbl[0].x) * t + modesel_hostJumpPosTbl[0].x;
    pos.y = (modesel_hostJumpPosTbl[1].y - modesel_hostJumpPosTbl[0].y) * s + (1.0f - (s - 0.5f) * 4.0f * (s - 0.5f)) * 80.0f +
            modesel_hostJumpPosTbl[0].y;
    pos.z = (modesel_hostJumpPosTbl[1].z - modesel_hostJumpPosTbl[0].z) * t + modesel_hostJumpPosTbl[0].z;
    modesel_ModelPosSet(10, pos.x, pos.y, pos.z);
    modesel_HostLookAtUpdate();
    timer += 12;
    if (timer >= 256) {
        obj->func = modesel_HostWaitObjMain;
        timer = 0;
    }
    obj->work[0] = timer;
}

omObjData *modesel_HostJumpCreate(void) {
    omObjData *obj = omAddObj(6, 0, 0, -1, modesel_HostJumpObjMain);

    modesel_ModelPosGet(0xA, &modesel_hostJumpPosTbl[0].x, &modesel_hostJumpPosTbl[0].y, &modesel_hostJumpPosTbl[0].z);
    HuVecCopyXYZ(&modesel_hostJumpPosTbl[1], 0.0f, 200.0f, 300.0f);
    obj->work[0] = 0;
    return obj;
}

void modesel_StageCreate(void) {
    s16 modelId;

    modesel_ModelCreate(0, 0xD0000, 0x2002A9);
    modesel_ModelPosSet(0, 0.0f, 0.0f, 0.0f);
    modesel_ModelScaleSet(0, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(0, 0);
    modesel_MotionFlagSet(0, 1);

    modesel_ModelCreate(1, 0xD0001, 0x229);
    modesel_ModelPosSet(1, 0.0f, 0.0f, 0.0f);
    modesel_ModelScaleSet(1, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(1, 0);
    modesel_MotionFlagSet(1, 1);

    modesel_ModelCreate(2, 0xD0002, 0x6A9);
    modesel_ModelPosSet(2, 0.0f, 0.0f, -585.0f);
    modesel_ModelScaleSet(2, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(2, 0);
    modesel_MotionFlagSet(2, 1);
    {
        char *names[] = { "mario", "luigi", "peach", "yoshi", "wario", "donkey" };
        HmfMotionNode *node;
        s32 i;

        modelId = modesel_ModelIdGet(2);
        for (i = 0; i < 6; i++) {
            if (MgStoryRankGet(i) < 0) {
                node = Hu3DModelObjPtrGet(modelId, names[i]);
                HuTranslateF(node->unk58, 0.0f, -4000.0f, 0.0f);
            }
        }
    }

    {
        Vec pos;

        HuVecCopyXYZ(&pos, 0.0f, 0.0f, -200.0f);
        pos.z = pos.z - 8.0f - 2.5f;
        modesel_ModelCreate(3, 0xD0003, 0x7A9);
        modesel_ModelPosSet(3, pos.x, pos.y, pos.z);
    }
    modesel_ModelScaleSet(3, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(3, 0);
    modesel_MotionFlagSet(3, 1);

    modesel_ModelCreate(4, 0xD0004, 0xAA9);
    modesel_ModelPosSet(4, 0.0f, 0.0f, 0.0f);
    modesel_ModelScaleSet(4, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(4, 0);
    modesel_MotionFlagSet(4, 1);

    modesel_ModelCreate(5, 0xD0005, 0x6A9);
    modesel_ModelPosSet(5, 325.0f, 9.5f, 45.0f);
    modesel_ModelScaleSet(5, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(5, 0);
    modesel_MotionFlagSet(5, 1);
    modesel_taihoNode = Hu3DModelObjPtrGet(modesel_ModelIdGet(5), "taiho");

    modesel_MotionCreate(0x11, 0xD000B, -1);

    modesel_ModelCreate(0x12, 0xD000C, 0xAA9);
    modesel_ModelPosSet(0x12, 275.0f, 97.0f, 122.5f);
    modesel_ModelScaleSet(0x12, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(0x12, 0);
    modesel_MotionFlagSet(0x12, 2);
    modesel_ModelDispOff(0x12);

    modesel_ModelCreate(7, 0xD0007, 0xAA9);
    modesel_ModelPosSet(7, 250.0f, 25.0f, 355.0f);
    modesel_ModelScaleSet(7, 1.0f, 1.0f, 1.0f);
    modesel_MotionFlagSet(7, 1);
    modesel_StarBobCreate(7);
    modelId = modesel_ModelIdGet(7);
    modesel_starNodeTbl[0].star = Hu3DModelObjPtrGet(modelId, "star_red");
    modesel_starNodeTbl[0].shadow = Hu3DModelObjPtrGet(modelId, "red_kage");
    modesel_StarNodeRotSet(7, 0);
    modesel_StarNodeSet(7, 0.0f, 16.0f, 0.0f, 20.0f);

    modesel_ModelCreate(8, 0xD0008, 0xAA9);
    modesel_ModelPosSet(8, -250.0f, 25.0f, 355.0f);
    modesel_ModelScaleSet(8, 1.0f, 1.0f, 1.0f);
    modesel_MotionFlagSet(8, 1);
    modesel_StarBobCreate(8);
    modelId = modesel_ModelIdGet(8);
    modesel_starNodeTbl[1].star = Hu3DModelObjPtrGet(modelId, "star_blue");
    modesel_starNodeTbl[1].shadow = Hu3DModelObjPtrGet(modelId, "blue_kage");
    modesel_StarNodeRotSet(8, 0);
    modesel_StarNodeSet(8, 0.0f, 0.0f, 16.0f, 20.0f);

    modesel_ModelCreate(9, 0xD0009, 0x6A9);
    modesel_ModelPosSet(9, 0.0f, 25.0f, 70.0f);
    modesel_ModelScaleSet(9, 1.0f, 1.0f, 1.0f);
    modesel_MotionFlagSet(9, 1);
    modesel_StarBobCreate(9);
    modelId = modesel_ModelIdGet(9);
    modesel_starNodeTbl[2].star = Hu3DModelObjPtrGet(modelId, "star_yellow");
    modesel_starNodeTbl[2].shadow = Hu3DModelObjPtrGet(modelId, "yellow_kage");
    modesel_StarNodeSet(9, 0.0f, 0.0f, 16.0f, 20.0f);

    modesel_ModelCreate(10, 0xA0122, 0xAA9);
    if (GwStory.unk0 == 12 && FileSelEnteredGet() == 0) {
        modesel_ModelPosSet(10, -300.0f, 225.0f, 300.0f);
        modesel_ModelDispOn(10);
    } else {
        modesel_ModelPosSet(10, 0.0f, -75.0f, 300.0f);
        modesel_ModelDispOff(10);
    }
    modesel_ModelScaleSet(10, 1.0f, 1.0f, 1.0f);
    modesel_MotionTimeSet(10, 0);
    AuraCreate(modesel_ModelIdGet(10));

    modesel_MotionCreate(0x13, 0xA0125, 0);
    modesel_MotionCreate(0x14, 0xA0123, 0);

    modesel_ModelCreate(11, 0xD000D, 0x200009);
    modesel_MotionTimeSet(11, 0);
    modesel_MotionFlagSet(11, 1);

    modesel_ModelCreate(12, 0xD000E, 0x2002B9);
    modesel_MotionTimeSet(12, 0);
    modesel_MotionFlagSet(12, 1);

    modesel_ModelCreate(13, 0xD000F, 0x2002B9);
    modesel_MotionTimeSet(13, 0);
    modesel_MotionFlagSet(13, 1);
}

void modesel_StageKill(void) {
    modesel_ModelKill(0);
    modesel_ModelKill(1);
    modesel_ModelKill(2);
    modesel_ModelKill(3);
    modesel_ModelKill(4);
    modesel_ModelKill(0x11);
    modesel_ModelKill(0x12);
    modesel_ModelKill(5);
    modesel_ModelKill(7);
    modesel_ModelKill(8);
    modesel_ModelKill(9);
    AuraKill(modesel_ModelIdGet(0xA));
    modesel_ModelKill(0xA);
    omDelObj(modesel_hostObj);
    modesel_CameraMoveKill();
    modesel_ModelKill(0xB);
    modesel_ModelKill(0xC);
}

void modesel_StarNodeSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    modesel_StarNodePosSet(arg0, arg1, arg2, arg3, arg4);
    modesel_StarNodeUpdate(arg0);
}

void modesel_StarNodePosSet(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 index = arg0 - 7;

    modesel_starNodeTbl[index].x = arg1;
    modesel_starNodeTbl[index].y = arg2;
    modesel_starNodeTbl[index].z = arg3;
    modesel_starNodeTbl[index].scale = arg4 < 0.0f ? 0.0f : arg4;
}

void modesel_StarNodeRotSet(s32 arg0, s32 arg1) {
    modesel_starNodeTbl[arg0 - 7].rot.word = arg1;
}

void modesel_StarNodeUpdate(s32 arg0) {
    s32 index = arg0 - 7;
    f32 shadowY;

    HuTranslateF(modesel_starNodeTbl[index].star->unk58, modesel_starNodeTbl[index].x,
                       modesel_starNodeTbl[index].y, modesel_starNodeTbl[index].z);
    mtxRotYCat(modesel_starNodeTbl[index].star->unk58, modesel_starNodeTbl[index].rot.angle);
    shadowY = (8.0f < modesel_starNodeTbl[index].y) ? 4.0f : -200.0f;
    HuTranslateF(modesel_starNodeTbl[index].shadow->unk58, modesel_starNodeTbl[index].x, shadowY,
                       modesel_starNodeTbl[index].z);
    mtxRotYCat(modesel_starNodeTbl[index].shadow->unk58, modesel_starNodeTbl[index].rot.angle);
}

void modesel_StarNodeRotAdd(s32 arg0, f32 arg1) {
    s32 index = arg0 - 7;

    if (360.0f < arg1) {
        arg1 = 360.0f;
    }
    modesel_starNodeTbl[index].rot.angle += arg1;
    if (360.0f < modesel_starNodeTbl[index].rot.angle) {
        modesel_starNodeTbl[index].rot.angle -= 360.0f;
    }
}

Process *modesel_CameraMotionStart(void) {
    s16 modelId = modesel_ModelIdGet(omovlevtno != 1 ? 0xB : 0xD);

    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DCameraMotionSet(modelId, 0);
    Hu3DMotionTimeSet(modelId, 0.0f);
    Hu3DMotionAttrSet(modelId, 1, 1);
    modesel_CameraMotionPosGet(&modesel_cameraWork.pos, &modesel_cameraWork.at, &modesel_cameraWork.up);
    return omAddPrcObj(modesel_CameraMotionProc, 0x5000, 0x2000, 0);
}

s32 modesel_MenuExec(void) {
    s32 cur = 10;
    s32 buttons;
    s32 result;
    s32 confirm;
    s16 modelId;

    if (FileSelEnteredGet() == 1) {
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            cur = 5;
            modesel_WinMesSet(0, 0x3106);
        } else {
            modesel_WinMesSet(0, 0x3124);
        }
    } else if (_CheckFlag(0x28)) {
        cur = 5;
        modesel_WinMesSet(0, 0x3106);
    } else if (GwStory.unk0 != 12) {
        cur = 7;
        modesel_WinInsertMesSet(0, 0, modesel_BoardNoGet(GwStory.unk0) + 0x3127);
        modesel_WinMesSet(0, 0x3135);
        if (GwSystem.playMode & 1) {
            cur = 8;
        }
    }
    modesel_CursorCreate();
    modesel_CursorPosUpdate(cur);
    omDelPrcObj(modesel_cameraProc);
    modesel_cameraProc = modesel_CameraManualStart();
    Hu3DCameraMotionOff(0);
    modesel_CameraEaseMove(cur, 7);
    while (1) {
        buttons = HuPadBtnDown[0];
        buttons |= modesel_StickBtnGet(0);
        if (buttons & A_BUTTON) {
            result = modesel_MenuDecide(cur, buttons);
            if (result >= 0) {
                break;
            }
        } else if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
            result = modesel_MenuMove(cur, buttons);
            if (result >= 0) {
                cur = result;
            }
        } else if (buttons & B_BUTTON) {
            modesel_SprDispOff(1);
            modesel_CameraEaseMove(10, 8);
            HuPrcSleep(8);
            modesel_WinKill(0);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            modesel_WinCreate(0, 0x3115, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
            modesel_WinMesWait(0);
            confirm = modesel_WinChoiceGet(0, 1, 0);
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            if (confirm == 0) {
                HuPrcVSleep();
                result = 16;
                modesel_WinMesSet(0, 0x3116);
                modesel_WinMesWait(0);
                break;
            }
            if (FileSelEnteredGet() == 1) {
                HuWinComKeyWait(A_BUTTON, 0, 0, 0, 1);
                modesel_WinMesSet(0, 0x3101);
            } else if (GwStory.unk0 == 12) {
                modesel_WinMesSet(0, 0x3136);
            } else {
                modesel_WinInsertMesSet(0, 0, modesel_BoardNoGet(GwStory.unk0) + 0x3127);
                modesel_WinMesSet(0, 0x3134);
            }
            modesel_WinMesWait(0);
            modesel_MenuMesSet(cur);
            modesel_CameraEaseMove(cur, 8);
            HuPrcSleep(8);
            modesel_SprDispOn(1);
        }
        modesel_CursorPosUpdate(cur);
        modesel_SpotEffCreate(cur);
        HuPrcVSleep();
    }
    switch (result) {
        case 0:
            modesel_SprDispOff(1);
            break;
        case 1:
            modesel_SprDispOff(1);
            modesel_WinDispOff(0);
            modesel_FileInfoDispOff();
            modesel_CameraEaseMove(-1, 20);
            modesel_StarLandCreate(9);
            if (GwStory.unk0 != 12 || FileSelEnteredGet() != 0) {
                modesel_HostExitCreate(10);
            }
            HuPrcSleep(20);
            modelId = modesel_ModelIdGet(12);
            Hu3DCameraMotionSet(modelId, 0);
            Hu3DMotionTimeSet(modelId, 2.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            Hu3DMotionAttrSet(modelId, 3, 0);
            HuPrcSleep(20);
            HuAudFXPlay(0x2E1);
            modesel_MotionFlagReset(3, 3);
            HuPrcSleep(30);
            break;
        case 4:
        case 6:
        case 7:
        case 9:
        case 10:
        case 13:
            modesel_SprDispOff(1);
            modesel_WinDispOff(0);
            modesel_FileInfoDispOff();
            modesel_SpotEffKill(cur);
            HuAudFXPlay(0x2E0);
            modesel_StarJumpCreate(cur);
            modesel_CameraEaseMove(-1, 20);
            omDelObj(modesel_hostObj);
            if (GwStory.unk0 != 12 || FileSelEnteredGet() != 0) {
                modesel_hostObj = modesel_HostExitCreate(10);
            }
            HuPrcSleep(20);
            modelId = modesel_ModelIdGet(11);
            Hu3DCameraMotionSet(modelId, 0);
            Hu3DMotionTimeSet(modelId, 0.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            Hu3DMotionAttrSet(modelId, 3, 0);
            HuPrcSleep(50);
            modesel_RumbleStart();
            break;
        case 5:
        case 8:
        case 11:
            modesel_SpotEffKill(5);
            modesel_taihoNode->scale.x = modesel_taihoNode->baseScale.x = modesel_taihoNode->scale.y =
                modesel_taihoNode->baseScale.y = modesel_taihoNode->scale.z = modesel_taihoNode->baseScale.z =
                    1.0f;
            HuPrcSleep(8);
            modesel_MotionSet(5, 0x11, 0);
            modesel_MotionTimeSet(0x12, 0);
            modesel_MotionFlagSet(0x12, 0);
            modesel_ModelDispOn(0x12);
            modesel_CameraMoveKill();
            HuPrcSleep(4);
            HuAudFXPlay(0x2FA);
            modesel_CameraShakeCreate();
            modesel_MotionEndWait(0x12);
            HuPrcSleep(24);
            modesel_CameraShakeKill();
            break;
        case 14:
            modesel_SprDispOff(1);
            modesel_WinDispOff(0);
            modesel_FileInfoDispOff();
            modesel_SpotEffKill(cur);
            omDelObj(modesel_hostObj);
            modesel_HostJumpCreate();
            modesel_CameraEaseMove(-1, 20);
            HuPrcSleep(20);
            modelId = modesel_ModelIdGet(11);
            Hu3DCameraMotionSet(modelId, 0);
            Hu3DMotionTimeSet(modelId, 0.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            Hu3DMotionAttrSet(modelId, 3, 0);
            HuPrcSleep(50);
            modesel_RumbleStart();
            break;
        case 16:
            break;
        default:
            while (1) {
                HuPrcVSleep();
            }
    }
    modesel_CursorKill();
    return result;
}

s32 modesel_BoardStatCreate(void) {
    s32 x;
    s32 y;
    s32 i;
    s32 chr;
    s32 digit;

    SLLoadBoard();
    x = 0x50;
    y = 0x68;
    modesel_SprCreate(10, 0x1F0019);
    modesel_SprPosSet(10, x, y);
    modesel_SprDispOff(10);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            modesel_SprCreate(11, 0x1F0004);
        } else {
            modesel_EspCreate(i + 11, 11);
        }
        modesel_SprPriSet(i + 11, 5);
        modesel_SprPosSet(i + 11, x + (i - 2) * 16 + 8, y - 0x15);
        chr = modesel_boardStatParty.chr[i];
        modesel_SprBankSet(i + 11, chr, 0);
        modesel_SprDispOff(i + 11);
        if (i == 0) {
            modesel_SprCreate(15, 0x1F0008);
        } else {
            modesel_EspCreate(i + 15, 15);
        }
        modesel_SprPriSet(i + 15, 5);
        modesel_SprPosSet(i + 15, x + (i - 2) * 16 + 8, y - 9);
        modesel_SprDispOff(i + 15);
    }
    modesel_SprCreate(19, 0x1F000C);
    modesel_SprPriSet(19, 5);
    modesel_SprPosSet(19, x, y - 0x24);
    modesel_SprBankSet(19, 0, 0);
    modesel_SprDispOff(19);
    modesel_SprCreate(20, 0x1F000B);
    modesel_SprPriSet(20, 5);
    modesel_SprPosSet(20, x, y + 6);
    modesel_SprBankSet(20, GwSystem.current_board_index, 0);
    modesel_SprDispOff(20);
    modesel_SprCreate(21, 0x1F0006);
    modesel_SprPriSet(21, 5);
    modesel_SprPosSet(21, x - 0x18, y + 0x1E);
    modesel_SprDispOff(21);
    modesel_SprCreate(22, 0x1F0007);
    modesel_SprPriSet(22, 5);
    modesel_SprPosSet(22, x + 8, y + 0x1E);
    digit = modesel_boardStatParty.currentTurn % 10;
    modesel_SprBankSet(22, digit, 0);
    modesel_SprDispOff(22);
    modesel_EspCreate(23, 22);
    modesel_SprPriSet(23, 5);
    modesel_SprPosSet(23, x, y + 0x1E);
    digit = modesel_boardStatParty.currentTurn / 10;
    modesel_SprBankSet(23, digit, 0);
    modesel_SprDispOff(23);
    modesel_SprCreate(24, 0x1F0028);
    modesel_SprPosSet(24, x + 0x10, y + 0x1E);
    modesel_SprPriSet(24, 5);
    modesel_SprDispOff(24);
    modesel_EspCreate(25, 22);
    modesel_SprPriSet(25, 5);
    modesel_SprPosSet(25, x + 0x20, y + 0x1E);
    digit = modesel_boardStatParty.totalTurns % 10;
    modesel_SprBankSet(25, digit, 0);
    modesel_SprDispOff(25);
    modesel_EspCreate(26, 22);
    modesel_SprPriSet(26, 5);
    modesel_SprPosSet(26, x + 0x18, y + 0x1E);
    digit = modesel_boardStatParty.totalTurns / 10;
    modesel_SprBankSet(26, digit, 0);
    modesel_SprDispOff(26);

    SLLoadBoardStory();
    x = 0xF0;
    y = 0x68;
    modesel_EspCreate(27, 10);
    modesel_SprPosSet(27, x, y);
    modesel_SprDispOff(27);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            modesel_SprCreate(28, 0x1F0004);
        } else {
            modesel_EspCreate(i + 28, 28);
        }
        chr = modesel_boardStatStory.chr[i];
        modesel_SprPriSet(i + 28, 5);
        modesel_SprPosSet(i + 28, x + i * 32 - 0x10, y - 0x15);
        modesel_SprBankSet(i + 28, chr, 0);
        modesel_SprDispOff(i + 28);
        if (i == 0) {
            modesel_SprCreate(30, 0x1F0008);
        } else {
            modesel_EspCreate(i + 30, 30);
        }
        modesel_SprPriSet(i + 30, 5);
        modesel_SprPosSet(i + 30, x + i * 32 - 0x10, y - 9);
        modesel_SprDispOff(i + 30);
    }
    x = 0xF0;
    y = 0x68;
    modesel_EspCreate(32, 19);
    modesel_SprPriSet(32, 5);
    modesel_SprPosSet(32, x, y - 0x24);
    modesel_SprBankSet(32, 1, 0);
    modesel_SprDispOff(32);
    modesel_SprCreate(33, 0x1F000A);
    modesel_SprPriSet(33, 5);
    modesel_SprPosSet(33, x, y + 6);
    modesel_SprBankSet(33, GwSystem.current_board_index, 0);
    modesel_SprDispOff(33);
    modesel_EspCreate(34, 21);
    modesel_SprPriSet(34, 5);
    modesel_SprPosSet(34, x - 0x18, y + 0x1E);
    modesel_SprDispOff(34);
    modesel_EspCreate(35, 22);
    modesel_SprPriSet(35, 5);
    modesel_SprPosSet(35, x + 8, y + 0x1E);
    digit = modesel_boardStatStory.currentTurn % 10;
    modesel_SprBankSet(35, digit, 0);
    modesel_SprDispOff(35);
    modesel_EspCreate(36, 22);
    modesel_SprPriSet(36, 5);
    modesel_SprPosSet(36, x, y + 0x1E);
    digit = modesel_boardStatStory.currentTurn / 10;
    modesel_SprBankSet(36, digit, 0);
    modesel_SprDispOff(36);
    if (modesel_boardStatStory.totalTurns != 20) {
        modesel_SprCreate(37, 0x1F0027);
        modesel_SprPosSet(37, x, y + 0x1E);
    } else {
        modesel_SprCreate(37, 0x1F0028);
        modesel_SprPosSet(37, x + 0x10, y + 0x1E);
    }
    modesel_SprPriSet(37, 5);
    modesel_SprDispOff(37);
    modesel_EspCreate(38, 22);
    modesel_SprPriSet(38, 5);
    modesel_SprPosSet(38, x + 0x20, y + 0x1E);
    digit = modesel_boardStatStory.totalTurns % 10;
    modesel_SprBankSet(38, digit, 0);
    modesel_SprDispOff(38);
    modesel_EspCreate(39, 22);
    modesel_SprPriSet(39, 5);
    modesel_SprPosSet(39, x + 0x18, y + 0x1E);
    digit = modesel_boardStatStory.totalTurns / 10;
    modesel_SprBankSet(39, digit, 0);
    modesel_SprDispOff(39);
    return 0;
}

void modesel_BoardStatDispOn(void) {
    s32 i;

    modesel_SprBGDispOn(10);
    modesel_SprBGDispOn(11);
    modesel_SprBGDispOn(12);
    modesel_SprBGDispOn(13);
    modesel_SprBGDispOn(14);
    for (i = 0; i < 4; i++) {
        if (modesel_boardStatParty.cpu[i] != 0) {
            modesel_SprBGDispOn(i + 15);
        }
    }
    modesel_SprBGDispOn(19);
    modesel_SprBGDispOn(20);
    modesel_SprBGDispOn(21);
    modesel_SprBGDispOn(24);
    if (modesel_boardStatParty.currentTurn / 10 != 0) {
        modesel_SprBGDispOn(23);
    }
    modesel_SprBGDispOn(22);
    modesel_SprBGDispOn(26);
    modesel_SprBGDispOn(25);
    modesel_SprBGDispOn(27);
    modesel_SprBGDispOn(28);
    modesel_SprBGDispOn(29);
    for (i = 0; i < 2; i++) {
        if (modesel_boardStatStory.cpu[i] != 0) {
            modesel_SprBGDispOn(i + 30);
        }
    }
    modesel_SprBGDispOn(32);
    modesel_SprBGDispOn(33);
    modesel_SprBGDispOn(34);
    modesel_SprBGDispOn(37);
    if (modesel_boardStatStory.totalTurns == 20) {
        if (modesel_boardStatStory.currentTurn / 10 != 0) {
            modesel_SprBGDispOn(36);
        }
        modesel_SprBGDispOn(35);
        modesel_SprBGDispOn(39);
        modesel_SprBGDispOn(38);
    }
}

void modesel_BoardStatDispOff(void) {
    modesel_SprBGDispOff(0xA);
    modesel_SprBGDispOff(0xB);
    modesel_SprBGDispOff(0xC);
    modesel_SprBGDispOff(0xD);
    modesel_SprBGDispOff(0xE);
    modesel_SprBGDispOff(0xF);
    modesel_SprBGDispOff(0x10);
    modesel_SprBGDispOff(0x11);
    modesel_SprBGDispOff(0x12);
    modesel_SprBGDispOff(0x13);
    modesel_SprBGDispOff(0x14);
    modesel_SprBGDispOff(0x15);
    modesel_SprBGDispOff(0x16);
    modesel_SprBGDispOff(0x17);
    modesel_SprBGDispOff(0x18);
    modesel_SprBGDispOff(0x19);
    modesel_SprBGDispOff(0x1A);
    modesel_SprBGDispOff(0x1B);
    modesel_SprBGDispOff(0x1C);
    modesel_SprBGDispOff(0x1D);
    modesel_SprBGDispOff(0x1E);
    modesel_SprBGDispOff(0x1F);
    modesel_SprBGDispOff(0x20);
    modesel_SprBGDispOff(0x21);
    modesel_SprBGDispOff(0x22);
    modesel_SprBGDispOff(0x23);
    modesel_SprBGDispOff(0x24);
    modesel_SprBGDispOff(0x25);
    modesel_SprBGDispOff(0x26);
    modesel_SprBGDispOff(0x27);
}

void modesel_BoardStatKill(void) {
    modesel_SprKill(0x27);
    modesel_SprKill(0x26);
    modesel_SprKill(0x24);
    modesel_SprKill(0x23);
    modesel_SprKill(0x1A);
    modesel_SprKill(0x19);
    modesel_SprKill(0x17);
    modesel_SprKill(0x16);
    modesel_SprKill(0x25);
    modesel_SprKill(0x18);
    modesel_SprKill(0x22);
    modesel_SprKill(0x15);
    modesel_SprKill(0x21);
    modesel_SprKill(0x14);
    modesel_SprKill(0x20);
    modesel_SprKill(0x13);
    modesel_SprKill(0x1F);
    modesel_SprKill(0x1E);
    modesel_SprKill(0x12);
    modesel_SprKill(0x11);
    modesel_SprKill(0x10);
    modesel_SprKill(0xF);
    modesel_SprKill(0x1D);
    modesel_SprKill(0x1C);
    modesel_SprKill(0xE);
    modesel_SprKill(0xD);
    modesel_SprKill(0xC);
    modesel_SprKill(0xB);
    modesel_SprKill(0x1B);
    modesel_SprKill(0xA);
}

s32 modesel_BoardStatChoice(void) {
    s32 choice;
    s32 x;
    s32 y;
    s32 buttons;

    modesel_BoardStatCreate();
    modesel_BoardStatDispOn();
    choice = 14;
    modesel_CursorPosGet(choice, &x, &y);
    modesel_SprPosSet(1, x, y);
    while (1) {
        HuPrcVSleep();
        buttons = HuPadBtnDown[0];
        buttons |= modesel_StickBtnGet(0);
        if (buttons & A_BUTTON) {
            break;
        }
        if (buttons & B_BUTTON) {
            choice = -1;
            break;
        }
        if (buttons & (U_JPAD | D_JPAD | L_JPAD | R_JPAD)) {
            choice = (choice == 14) ? 15 : 14;
            modesel_CursorMove(1, choice);
        }
        modesel_CursorPosGet(choice, &x, &y);
        modesel_SprPosSet(1, x, y);
    }
    modesel_BoardStatDispOff();
    modesel_BoardStatKill();
    return choice;
}

s32 modesel_MenuDecide(s32 cur, s32 buttons) {
    s32 result = -1;
    s16 selection;
    Process *process;
    s32 pick;
    s32 choice;
    s32 i;
    s32 j;
    s32 index;
    s32 board;
    s32 boardNo;
    s32 best;
    s32 bestChr;
    s32 message;

    switch (cur) {
        case 0:
        case 1:
            break;
        case 2:
            modesel_WinDispOff(0);
            modesel_SprBGDispOff(1);
            modesel_FileInfoDispOff();
            mgStoryStatPortNo = 0;
            selection = modesel_storyChrHalf;
            HuPrcVSleep();
            if (MgStoryRankGet(selection) < 0) {
                while (1) {
                    HuPrcVSleep();
                }
            }
            process = omAddPrcObj(MgStoryStatViewProc, 0x4000, 0x800, 0);
            process->user_data = &selection;
            while (1) {
                if (selection == -3) {
                    break;
                }
                if (selection == -2) {
                    break;
                }
                if (selection == -1) {
                    result = 0;
                    break;
                }
                HuPrcVSleep();
            }
            modesel_WinDispOn(0);
            modesel_SprBGDispOn(1);
            modesel_FileInfoDispOn();
            return result;
        case 3:
            HuAudFXPlay(3);
            result = 1;
            break;
        case 5:
            HuAudFXPlay(3);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            if (FileSelEnteredGet() == 1) {
                if (_CheckFlag(0x16) && _CheckFlag(0x17)) {
                    modesel_WinMesSet(0, 0x3112);
                    pick = modesel_BoardStatChoice();
                    if (pick != -1) {
                        result = (pick == 14) ? 8 : 5;
                        modesel_WinDispOff(0);
                        modesel_SprBGDispOff(1);
                    } else {
                        modesel_WinMesSet(0, 0x3102);
                    }
                } else if (_CheckFlag(0x16) && !_CheckFlag(0x17)) {
                    result = 8;
                    modesel_WinDispOff(0);
                    modesel_SprBGDispOff(1);
                } else if (!_CheckFlag(0x16) && _CheckFlag(0x17)) {
                    result = 5;
                    modesel_WinDispOff(0);
                    modesel_SprBGDispOff(1);
                }
            } else {
                modesel_WinDispOff(0);
                modesel_SprBGDispOff(1);
                result = 11;
            }
            if (result != -1) {
                RepeatVibrator(0, 30, 0, 30);
            }
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            break;
        case 7:
            HuAudFXPlay(3);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            modesel_SprDispOff(1);
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                modesel_WinMesSet(0, 0x3118);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x3104);
            } else if (FileSelEnteredGet() == 0 && !(GwSystem.playMode & 2)) {
                modesel_WinMesSet(0, 0x3118);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x3104);
            } else {
                modesel_WinMesSet(0, 0x310A);
                modesel_WinMesWait(0);
                switch (modesel_WinChoiceGet(0, 1, 0)) {
                    case 0:
                        result = 6;
                        break;
                    case 1:
                        if (FileSelEnteredGet() == 1) {
                            if (_CheckFlag(0x17)) {
                                modesel_WinMesSet(0, 0x310B);
                                modesel_WinMesWait(0);
                                HuPrcVSleep();
                                modesel_WinMesSet(0, 0x310D);
                                modesel_WinMesWait(0);
                                if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                    modesel_WinMesSet(0, 0x310E);
                                    modesel_WinMesWait(0);
                                    result = 4;
                                } else {
                                    modesel_WinMesSet(0, 0x3110);
                                    modesel_WinMesWait(0);
                                    modesel_WinMesSet(0, 0x3104);
                                }
                            } else {
                                result = 4;
                            }
                        } else if (GwSystem.playMode & 2) {
                            if (_CheckFlag(0x28)) {
                                modesel_WinMesSet(0, 0x310B);
                                HuPrcSleep(8);
                                modesel_PadBtnWait(0xC000);
                                modesel_WinMesSet(0, 0x310C);
                                modesel_WinMesWait(0);
                                if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                    modesel_WinMesSet(0, 0x310F);
                                    modesel_WinMesWait(0);
                                    if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                        result = 10;
                                        break;
                                    }
                                }
                                modesel_WinMesSet(0, 0x3110);
                                modesel_WinMesWait(0);
                                modesel_MenuMesSet(cur);
                            } else {
                                result = 10;
                            }
                        } else {
                            modesel_WinMesSet(0, 0x3118);
                            modesel_WinMesWait(0);
                            modesel_WinMesSet(0, 0x3104);
                        }
                        break;
                    default:
                        modesel_MenuMesSet(cur);
                        break;
                }
            }
            if (result != -1) {
            confirmed:
                modesel_WinMesSet(0, 0x3117);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, (u32)modesel_emptyStr);
            } else {
                modesel_SprBGDispOn(1);
            }
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            break;
        case 8:
            HuAudFXPlay(3);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            modesel_SprDispOff(1);
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                modesel_WinMesSet(0, 0x3118);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x3103);
            } else if (FileSelEnteredGet() == 0 && (GwSystem.playMode & 2)) {
                modesel_WinMesSet(0, 0x3118);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x3103);
            } else {
                modesel_WinMesSet(0, 0x3109);
                modesel_WinMesWait(0);
                switch (modesel_WinChoiceGet(0, 1, 0)) {
                    case 0:
                        result = 9;
                        break;
                    case 1:
                        if (FileSelEnteredGet() == 1) {
                            if (_CheckFlag(0x16)) {
                                modesel_WinMesSet(0, 0x310B);
                                modesel_WinMesWait(0);
                                HuPrcVSleep();
                                modesel_WinMesSet(0, 0x310D);
                                modesel_WinMesWait(0);
                                if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                    modesel_WinMesSet(0, 0x310E);
                                    modesel_WinMesWait(0);
                                    result = 7;
                                } else {
                                    modesel_WinMesSet(0, 0x3110);
                                    modesel_WinMesWait(0);
                                    modesel_WinMesSet(0, 0x3103);
                                }
                            } else {
                                result = 7;
                            }
                        } else if (GwSystem.playMode & 2) {
                            modesel_WinMesSet(0, 0x3118);
                            modesel_WinMesWait(0);
                            modesel_WinMesSet(0, 0x3103);
                        } else if (_CheckFlag(0x28)) {
                            modesel_WinMesSet(0, 0x310B);
                            modesel_WinMesWait(0);
                            HuPrcVSleep();
                            modesel_WinMesSet(0, 0x310C);
                            modesel_WinMesWait(0);
                            if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                modesel_WinMesSet(0, 0x310F);
                                modesel_WinMesWait(0);
                                if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                                    result = 10;
                                    break;
                                }
                            }
                            modesel_WinMesSet(0, 0x3110);
                            modesel_WinMesWait(0);
                            modesel_MenuMesSet(cur);
                        } else {
                            result = 10;
                        }
                        break;
                    default:
                        modesel_MenuMesSet(cur);
                        break;
                }
            }
            if (result != -1) {
                goto confirmed;
            }
            modesel_SprBGDispOn(1);
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            break;
        case 9:
            HuAudFXPlay(3);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            modesel_SprDispOff(1);
            for (i = 0; i < 0x48; i++) {
                if (GWMgUnlockCheck(i)) {
                    break;
                }
            }
            if (FileSelEnteredGet() == 0) {
                modesel_WinMesSet(0, 0x3118);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x313E);
            } else if (i == 0x48) {
                modesel_WinMesSet(0, 0x3111);
                modesel_WinMesWait(0);
                modesel_WinMesSet(0, 0x3105);
            } else {
                modesel_WinMesSet(0, 0x3133);
                modesel_WinMesWait(0);
                if (modesel_WinChoiceGet(0, 1, 0) == 0) {
                    result = 13;
                    goto confirmed;
                }
                if (FileSelEnteredGet() == 0) {
                    modesel_WinMesSet(0, 0x313E);
                } else {
                    modesel_WinMesSet(0, 0x3105);
                }
            }
            modesel_SprDispOn(1);
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            break;
        case 10:
            HuAudFXPlay(3);
            modesel_MotionShiftSet(10, 0x13, 8, 8, 2);
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                modesel_SprBGDispOff(1);
                modesel_WinMesSet(0, 0x313C);
                modesel_WinMesWait(0);
                if (modesel_WinChoiceGet(0, 1, 1) == 0) {
                    modesel_WinMesSet(0, 0x313D);
                    modesel_WinMesWait(0);
                    modesel_WinMesSet(0, (u32)modesel_emptyStr);
                    result = 14;
                } else {
                    modesel_WinMesSet(0, 0x3119);
                    modesel_SprBGDispOn(1);
                }
            } else {
                modesel_SprBGDispOff(1);
                if (FileSelEnteredGet() == 0) {
                    modesel_WinMesSet(0, 0x3137);
                    modesel_WinMesWait(0);
                    choice = modesel_WinChoiceGet(0, 1, 0);
                    if (choice == 0) {
                        modesel_WinMesSet(0, 0x3138);
                        modesel_WinMesWait(0);
                        modesel_WinKill(0);
                        modesel_WinCreate(0, (u32)modesel_emptyStr, 0xA0, modesel_winPosYHalf + 4, 0, 0, 3);
                    }
                    if (choice == 1) {
                        modesel_WinMesSet(0, 0x3139);
                        modesel_WinMesWait(0);
                        choice = modesel_WinChoiceGet(0, 1, 0);
                        if (choice == 0) {
                            modesel_HelpExec();
                        }
                        if (choice == 1) {
                            modesel_WinMesSet(0, 0x313A);
                            modesel_WinMesWait(0);
                        }
                    }
                    modesel_WinMesSet(0, 0x3122);
                } else {
                    bestChr = -1;
                    index = rand8() * (10.0f / 255.0f);
                    boardNo = modesel_BoardNoGet(index);
                    board = modesel_BoardIdxGet(index);
                    best = 0;
                    if (modesel_BoardTypeGet(index) == 2) {
                        for (j = 0; j < 8; j++) {
                            if (best < GwCommon.boardRecord[1][board].chr[j]) {
                                best = GwCommon.boardRecord[1][board].chr[j];
                                bestChr = j;
                            }
                        }
                        for (j = 0; j < 8; j++) {
                            if (GwCommon.boardRecord[1][board].chr[j] == best) {
                                if (bestChr != j) {
                                    bestChr = -1;
                                    break;
                                }
                            }
                        }
                    } else {
                        for (j = 0; j < 8; j++) {
                            if (best < GwCommon.boardRecord[0][board].chr[j]) {
                                best = GwCommon.boardRecord[0][board].chr[j];
                                bestChr = j;
                            }
                        }
                        for (j = 0; j < 8; j++) {
                            if (GwCommon.boardRecord[0][board].chr[j] == best) {
                                if (bestChr != j) {
                                    bestChr = -1;
                                    break;
                                }
                            }
                        }
                    }
                    message = boardNo + 0x3127;
                    modesel_WinInsertMesSet(0, 0, message);
                    modesel_WinMesSet(0, 0x3125);
                    modesel_WinMesWait(0);
                    if (bestChr != -1) {
                        modesel_WinInsertMesSet(0, 0, message);
                        modesel_WinInsertMesSet(0, 1, bestChr + 0x1C00);
                        modesel_WinMesSet(0, 0x3126);
                        modesel_WinMesWait(0);
                    }
                    modesel_WinMesSet(0, 0x3124);
                    HuPrcSleep(3);
                }
                modesel_SprBGDispOn(1);
            }
            modesel_MotionShiftSet(10, 0x14, 8, 8, 2);
            break;
    }
    return result;
}

s32 modesel_MenuMove(s32 cur, s32 buttons) {
    s32 next = cur;
    s32 unlocked;
    s32 i;

    if (FileSelEnteredGet() == 1) {
        unlocked = 0;
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            unlocked = 1;
        }
    } else {
        unlocked = _CheckFlag(0x28);
    }
    switch (cur) {
        case 0:
        case 1:
        case 2:
            if (buttons & L_JPAD) {
                do {
                    modesel_storyChr = (modesel_storyChr - 1 < 0) ? 5 : modesel_storyChr - 1;
                } while (MgStoryRankGet(modesel_storyChrHalf) < 0);
            } else if (buttons & R_JPAD) {
                do {
                    modesel_storyChr = (modesel_storyChr + 1 < 6) ? modesel_storyChr + 1 : 0;
                } while (MgStoryRankGet(modesel_storyChrHalf) < 0);
            } else if (buttons & D_JPAD) {
                next = 3;
            }
            break;
        case 3:
            if (buttons & U_JPAD) {
                for (i = 0; i < 6; i++) {
                    if (MgStoryRankGet(i) >= 0) {
                        next = 2;
                    }
                }
            } else if (buttons & L_JPAD) {
                next = 8;
                if (FileSelEnteredGet() == 0) {
                    next = (GwStory.unk0 == 12) ? 10 : 8;
                }
            } else if (buttons & R_JPAD) {
                next = (unlocked == 0) ? 7 : 5;
            } else if (buttons & D_JPAD) {
                next = 9;
            }
            break;
        case 4:
        case 5:
            if (buttons & U_JPAD) {
                next = 3;
            } else if (buttons & L_JPAD) {
                next = 9;
            } else if (buttons & D_JPAD) {
                next = 7;
            }
            break;
        case 6:
        case 7:
            if (buttons & U_JPAD) {
                next = unlocked ? 5 : 9;
            } else if (buttons & L_JPAD) {
                next = 10;
                if (FileSelEnteredGet() == 0) {
                    next = (GwStory.unk0 != 12) ? 10 : 8;
                }
            }
            break;
        case 8:
            if (buttons & U_JPAD) {
                next = 9;
                if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                    next = 10;
                }
            } else if (buttons & R_JPAD) {
                next = 10;
                if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                    next = 7;
                }
            }
            break;
        case 9:
            if (buttons & U_JPAD) {
                next = 3;
            } else if (buttons & L_JPAD) {
                next = 8;
                if (FileSelEnteredGet() == 0) {
                    next = (GwStory.unk0 == 12) ? 10 : 8;
                }
            } else if (buttons & D_JPAD) {
                next = 10;
                if (FileSelEnteredGet() == 0) {
                    next = (GwStory.unk0 != 12) ? 10 : 8;
                }
            } else if (buttons & R_JPAD) {
                next = (unlocked == 0) ? 7 : 5;
            }
            break;
        case 10:
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                if (buttons & U_JPAD) {
                    next = 9;
                } else if (buttons & L_JPAD) {
                } else if (buttons & D_JPAD) {
                    next = 8;
                } else if (buttons & R_JPAD) {
                    next = 9;
                }
            } else {
                if (buttons & U_JPAD) {
                    next = 9;
                } else if (buttons & L_JPAD) {
                    next = 8;
                } else if (buttons & D_JPAD) {
                } else if (buttons & R_JPAD) {
                    next = 7;
                }
            }
            break;
    }
    modesel_SpotFocus(next);
    modesel_MenuMesSet(next);
    return next;
}

void modesel_MenuMesSet(s32 arg0) {
    s32 rank;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            rank = MgStoryRankGet(modesel_storyChrHalf);
            rank = (rank < 0) ? 0 : (rank >= 5) ? 4
                                                : rank;
            modesel_WinMesSet(0, 0x3114);
            modesel_WinInsertMesSet(0, 0, modesel_rankMesTbl[rank]);
            modesel_WinInsertMesSet(0, 1, modesel_storyChr + 0x1C00);
            break;
        case 3:
            modesel_WinMesSet(0, 0x3107);
            break;
        case 4:
        case 5:
            modesel_WinMesSet(0, 0x3106);
            break;
        case 7:
            if (FileSelEnteredGet() == 1) {
                modesel_WinMesSet(0, 0x3104);
            } else if ((GwSystem.playMode & 2) && GwStory.unk0 != 12) {
                modesel_WinInsertMesSet(0, 0, modesel_BoardNoGet(GwStory.unk0) + 0x3127);
                modesel_WinMesSet(0, 0x3135);
            } else {
                modesel_WinMesSet(0, 0x3104);
            }
            break;
        case 8:
            if (FileSelEnteredGet() == 1) {
                modesel_WinMesSet(0, 0x3103);
            } else if ((GwSystem.playMode & 1) && GwStory.unk0 != 12) {
                modesel_WinInsertMesSet(0, 0, modesel_BoardNoGet(GwStory.unk0) + 0x3127);
                modesel_WinMesSet(0, 0x3135);
            } else {
                modesel_WinMesSet(0, 0x3103);
            }
            break;
        case 9:
            if (FileSelEnteredGet() == 0) {
                modesel_WinMesSet(0, 0x313E);
            } else {
                modesel_WinMesSet(0, 0x3105);
            }
            break;
        case 10:
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                modesel_WinMesSet(0, 0x3119);
            } else if (FileSelEnteredGet() == 0) {
                modesel_WinMesSet(0, 0x3122);
            } else {
                modesel_WinMesSet(0, 0x3124);
            }
            break;
    }
}

void modesel_SpotFocus(s32 arg0) {
    switch (arg0) {
        case 0:
        case 1:
        case 2:
            MgStoryRankGet(modesel_storyChrHalf);
            modesel_CursorMove(1, 2);
            break;
        case 3:
            modesel_CameraEaseMove(3, 8);
            modesel_CursorMove(1, 3);
            break;
        case 4:
        case 5:
            modesel_CameraEaseMove(5, 8);
            modesel_CursorMove(1, 5);
            break;
        case 7:
            modesel_CameraEaseMove(7, 8);
            modesel_CursorMove(1, 7);
            break;
        case 8:
            modesel_CameraEaseMove(8, 8);
            modesel_CursorMove(1, 8);
            break;
        case 9:
            modesel_CameraEaseMove(9, 8);
            modesel_CursorMove(1, 9);
            break;
        case 10:
            FileSelEnteredGet();
            modesel_CameraEaseMove(10, 8);
            modesel_CursorMove(1, 10);
            break;
    }
}

void modesel_CursorCreate(void) {
    modesel_SprCreate(1, 0x88);
    modesel_SprPriSet(1, 5);
    modesel_SprPosSet(1, 0xA0, 0x71);
    modesel_SprDispOn(1);
}

void modesel_CursorKill(void) {
    modesel_SprKill(1);
}

void modesel_CursorPosUpdate(s32 arg0) {
    s32 x;
    s32 y;

    modesel_CursorPosGet(arg0, &x, &y);
    modesel_SprPosSet(1, x, y);
}

void modesel_CursorPosGet(s32 arg0, s32 *x, s32 *y) {
    Vec pos;
    Vec2f screenPos;
    s32 index = 0;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            index = modesel_storyChr + 8;
            break;
        case 3:
            index = 3;
            break;
        case 4:
        case 5:
        case 6:
            index = 4;
            break;
        case 7:
            index = 0;
            break;
        case 8:
            index = 1;
            break;
        case 9:
            index = 2;
            break;
        case 10:
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                index = 7;
            } else {
                index = 6;
            }
            break;
        case 14:
            *x = 0x70;
            *y = 0x3C;
            return;
        case 15:
            *x = 0x110;
            *y = 0x3C;
            return;
    }
    pos.x = modesel_spotPosTbl[index].x;
    pos.y = modesel_spotPosTbl[index].y;
    pos.z = modesel_spotPosTbl[index].z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    *x = screenPos.x;
    *y = screenPos.y;
}

void modesel_SpotPosGet(s32 arg0, f32 *x, f32 *y, f32 *z) {
    s32 index = 0;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            index = 5;
            break;
        case 3:
            index = 3;
            break;
        case 4:
        case 5:
        case 6:
            index = 4;
            break;
        case 7:
            index = 0;
            break;
        case 8:
            index = 1;
            break;
        case 9:
            index = 2;
            break;
        case 10:
            if (FileSelEnteredGet() == 0 && GwStory.unk0 == 12) {
                index = 7;
            } else {
                index = 2;
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
    }
    *x = modesel_spotPosTbl[index].x;
    *y = modesel_spotPosTbl[index].y;
    *z = modesel_spotPosTbl[index].z;
}

void modesel_SprPosYAdd(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;

    modesel_SprPosGet(arg0, &x, &y);
    y += arg1;
    modesel_SprPosSet(arg0, x, y);
}

void modesel_CursorMove(s32 arg0, s32 arg1) {
    s32 endX;
    s32 endY;
    s32 startX;
    s32 startY;
    s32 i;
    f32 t;

    modesel_CursorPosGet(arg1, &endX, &endY);
    modesel_SprPosGet(arg0, &startX, &startY);
    for (i = 0; i < 8; i++) {
        t = i * (1.0f / 7.0f);
        modesel_CursorPosGet(arg1, &endX, &endY);
        modesel_SprPosSet(arg0, startX + t * (endX - startX), startY + t * (endY - startY));
        HuPrcVSleep();
    }
    modesel_SprPosSet(arg0, endX, endY);
}

void modesel_SpotEffUpdate(s32 index, f32 t) {
    s32 slot = index;
    f32 angle;
    f32 sine;
    f32 amplitude;
    f32 base;
    f32 scale;

    if (t > 1.0f) {
        t = 1.0f;
    }
    if (t < 0.0f) {
        return;
    }
    angle = t * 360.0f;
    sine = sindf(angle);
    cosdf(angle);
    amplitude = 0.1f;
    base = 1.0f;
    scale = sine * amplitude + base;
    switch (slot) {
        case 2:
            modesel_ModelScaleSet(index, 1.0f, 1.0f, 1.0f);
            break;
        case 3:
            modesel_ModelScaleSet(index, scale, scale, 1.0f);
            break;
        case 5:
            scale = sine * 0.3f + 1.0f;
            modesel_taihoNode->scale.x = modesel_taihoNode->baseScale.x = modesel_taihoNode->scale.y =
                modesel_taihoNode->baseScale.y = modesel_taihoNode->scale.z = modesel_taihoNode->baseScale.z =
                    scale;
            break;
        case 7:
        case 8:
        case 9:
            modesel_StarNodeRotAdd(index, 180.0f / 23.0f);
            modesel_StarNodeUpdate(index);
            break;
    }
}

void modesel_SpotEffInit(void) {
    s32 i;

    for (i = 0; i < 21; i++) {
        modesel_spotEffObj[i][0] = 0;
        modesel_spotEffTime[i][0] = 0;
        modesel_spotEffMaxTime[i][0] = 0;
    }
}

void modesel_SpotEffKill(s32 arg0) {
    if (modesel_spotEffObj[arg0][0] != NULL) {
        omDelObj(modesel_spotEffObj[arg0][0]);
    }
    modesel_spotEffObj[arg0][0] = NULL;
}

void modesel_SpotEffKillAll(void) {
    s32 i;

    for (i = 0; i < 21; i++) {
        modesel_SpotEffKill(i);
    }
}

void modesel_SpotEffObjMain(omObjData *obj) {
    s32 index = obj->work[0];
    s32 slot = index;
    f32 t = (f32)modesel_spotEffTime[index][0] / modesel_spotEffMaxTime[index][0];

    if (modesel_spotEffTime[index][0] <= modesel_spotEffMaxTime[index][0] - 1) {
        modesel_SpotEffUpdate(index, t);
        modesel_spotEffTime[index][0]++;
    } else {
        modesel_SpotEffUpdate(index, t);
        modesel_SpotEffKill(slot);
        modesel_spotEffTime[index][0] = 0;
    }
}

void modesel_SpotEffCreate(s32 arg0) {
    omObjData *obj;

    if (modesel_spotEffObj[arg0][0] == NULL) {
        obj = omAddObj(6, 0, 0, -1, modesel_SpotEffObjMain);
        obj->work[0] = arg0;
        modesel_spotEffObj[arg0][0] = obj;
        if (arg0 < 10) {
            if (arg0 >= 7) {
                modesel_spotEffMaxTime[arg0][0] = 45;
            } else {
                modesel_spotEffMaxTime[arg0][0] = 20;
            }
        } else {
            modesel_spotEffMaxTime[arg0][0] = 20;
        }
    }
}

void modesel_CameraMotionStop(Process *arg0) {
    omDelPrcObj(arg0);
    Hu3DCameraMotionOff(0);
}

void modesel_BoardStatRead(void) {
    s32 i;
    s8 value;

    modesel_boardStatUnusedTbl[0] = modesel_boardStatUnusedTbl[1] = modesel_boardStatUnusedTbl[2] = modesel_boardStatUnusedTbl[3] =
        modesel_boardStatUnusedTbl[4] = modesel_boardStatUnusedTbl[5] = 0;
    if (FileSelEnteredGet() == 1) {
        SLLoadBoard();
        for (i = 0; i < 4; i++) {
            modesel_boardStatParty.chr[i] = GwPlayer[i].chr;
            modesel_boardStatParty.cpu[i] = GwPlayer[i].stat & 1;
        }
        modesel_boardStatParty.gameLength = (value = GwSystem.current_game_length) >= 3 ? 3 : value;
        modesel_boardStatParty.currentTurn = (value = GwSystem.current_turn) >= 99 ? 99 : value;
        modesel_boardStatParty.totalTurns = (value = GwSystem.total_turns) >= 99 ? 99 : value;
        SLLoadBoardStory();
        for (i = 0; i < 2; i++) {
            modesel_boardStatStory.chr[i] = GwPlayer[i].chr;
            modesel_boardStatStory.cpu[i] = GwPlayer[i].stat & 1;
        }
        modesel_boardStatStory.gameLength = (value = GwSystem.current_game_length) >= 3 ? 3 : value;
        modesel_boardStatStory.currentTurn = (value = GwSystem.current_turn) >= 99 ? 99 : value;
        modesel_boardStatStory.totalTurns = (value = GwSystem.total_turns) >= 99 ? 99 : value;
    }
}

void modesel_FileInfoCreate(void) {
    s32 x;
    s32 y;

    if (FileSelEnteredGet() == 1) {
        modesel_SprCreate(6, 0xD0011);
        modesel_SprPosSet(6, 0x40, 0x1C);
        modesel_SprDispOff(6);
        HuSprColorSet(modesel_EspIdGet(6), 0, 0xFF, 0xFF, 0);
        modesel_SprCreate(7, 0xD0013);
        modesel_SprPosSet(7, 0x40, 0x1C);
        modesel_SprDispOff(7);
        modesel_SprCreate(8, 0xD0014);
        modesel_SprPosSet(8, 0x40, 0x1C);
        modesel_SprDispOff(8);
        modesel_SprCreate(9, 0x1F0004);
        modesel_SprPosSet(9, 0x26, 0x24);
    } else {
        x = 0x40;
        modesel_SprCreate(6, 0xD0010);
        modesel_SprPosSet(6, x, 0x26);
        modesel_SprDispOff(6);
        HuSprColorSet(modesel_EspIdGet(6), 0, 0xFF, 0xFF, 0);
        modesel_SprCreate(7, 0xD0012);
        modesel_SprPosSet(7, x, 0x1C);
        modesel_SprDispOff(7);
        switch (GwStory.unk2) {
            case 0:
                modesel_SprCreate(8, 0xD0014);
                y = 0x2E;
                break;
            case 1:
                modesel_SprCreate(8, 0xD0015);
                y = 0x2E;
                break;
            case 2:
                modesel_SprCreate(8, 0xD0016);
                y = 0x2E;
                break;
            case 3:
                modesel_SprCreate(8, 0xD0017);
                y = 0x2E;
                break;
            default:
                modesel_SprCreate(8, 0xD0015);
                y = 0x2E;
                break;
        }
        modesel_SprPosSet(8, x + 10, y);
        modesel_SprDispOff(8);
        modesel_SprCreate(9, 0x1F0004);
        modesel_SprPosSet(9, x - 26, y);
        modesel_SprBankSet(9, GwStory.unk1, 0);
    }
    modesel_SprDispOff(9);
}

void modesel_FileInfoKill(void) {
    modesel_SprKill(6);
    modesel_SprKill(7);
    modesel_SprKill(8);
    modesel_SprKill(9);
}

void modesel_FileInfoDispOn(void) {
    modesel_SprBGDispOn(6);
    modesel_SprBGDispOn(7);
    if (FileSelEnteredGet() != 1) {
        modesel_SprBGDispOn(8);
        modesel_SprBGDispOn(9);
    }
}

void modesel_FileInfoDispOff(void) {
    modesel_SprBGDispOff(6);
    modesel_SprBGDispOff(7);
    modesel_SprBGDispOff(8);
    modesel_SprBGDispOff(9);
}

f32 modesel_LookAtAngleCalc(f32 arg0, f32 arg1) {
    return -(atan2df(arg1, arg0) - 90.0f);
}

void modesel_RumbleObjMain(omObjData *obj) {
    s32 *counter;

    if (modesel_rumbleCnt == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &modesel_rumbleCnt;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

void modesel_RumbleStart(void) {
    modesel_rumbleCnt = 0;
    omAddObj(6, 0, 0, -1, modesel_RumbleObjMain);
}

void modesel_HelpExec(void) {
    u16 spriteId;
    s32 i;

    modesel_SprCreate(3, 0x140064);
    modesel_SprPosSet(3, 160, 120);
    modesel_SprScaleSet(3, 10.0f, 8.0f);
    modesel_SprAlphaSet(3, 0);
    modesel_SprDispOff(3);
    spriteId = modesel_EspIdGet(3);
    espColorSet(spriteId, 0, 0, 0);
    espPriSet(spriteId, 0x4BA);
    modesel_SprCreate(2, 0xD0018);
    modesel_SprPosSet(2, 160, 120);
    modesel_SprScaleSet(2, 1.0f, 1.0f);
    modesel_SprDispOff(2);
    spriteId = modesel_EspIdGet(2);
    espColorSet(spriteId, 0, 0, 0);
    espPriSet(spriteId, 11);
    modesel_SprCreate(4, 0x150003);
    modesel_SprPosSet(4, 28, 120);
    modesel_SprDispOff(4);
    modesel_SprCreate(5, 0x150003);
    modesel_SprPosSet(5, 292, 120);
    modesel_SprDispOff(5);
    espAttrSet(modesel_EspIdGet(5), HUSPR_ATTR_FLIPX);
    modesel_SprBGDispOff(1);
    modesel_WinDispOff(0);
    modesel_FileInfoDispOff();
    modesel_SprDispOn(3);
    modesel_SprDispOn(2);
    modesel_SprDispOff(4);
    modesel_SprDispOn(5);
    for (i = 0; i < 8; i++) {
        modesel_SprAlphaSet(2, i * (256.0f / 7));
        if (i * (256.0f / 7) < 128.0f) {
            modesel_SprAlphaSet(3, i * (256.0f / 7));
        } else {
            modesel_SprAlphaSet(3, 128);
        }
        HuPrcVSleep();
    }
    modesel_SprAlphaSet(2, 256);
    modesel_SprAlphaSet(3, 128);
    modesel_WinCreate(1, 0x5F01, 0, 16, 304, 208, 0);
    HuWinMesDefColSet(modesel_winTbl[1][0], 64, 64, 64);
    HuWinMesPalSet(modesel_winTbl[1][0], 4, 0, 255, 0);
    HuWinMesPalSet(modesel_winTbl[1][0], 6, 255, 255, 128);
    while (1) {
        if (HuPadBtnDown[0] & B_BUTTON) {
            break;
        }
        if (ContBtnDown[0] & L_JPAD) {
            modesel_SprDispOff(4);
            modesel_SprDispOn(5);
            modesel_WinMesSet(1, 0x5F01);
        } else if (ContBtn[0] & R_JPAD) {
            modesel_SprDispOn(4);
            modesel_SprDispOff(5);
            modesel_WinMesSet(1, 0x5F02);
        }
        HuPrcVSleep();
    }
    modesel_WinKill(1);
    for (i = 0; i < 7; i++) {
        modesel_SprAlphaSet(2, (7 - i) * (255.0f * (1.0f / 7)));
        HuPrcVSleep();
    }
    modesel_SprDispOff(2);
    modesel_SprDispOff(3);
    modesel_SprDispOff(4);
    modesel_SprDispOff(5);
    modesel_SprKill(3);
    modesel_SprKill(2);
    modesel_SprKill(4);
    modesel_SprKill(5);
    modesel_SprBGDispOn(1);
    modesel_WinDispOn(0);
    modesel_FileInfoDispOn();
}

void modesel_SysClose(void) {
}

s32 modesel_SysCheck(void) {
    return 1;
}

s32 modesel_BoardNoGet(s32 arg0) {
    return modesel_boardNoTbl[arg0];
}

s32 modesel_BoardIdxGet(s32 arg0) {
    s32 value = modesel_boardNoTbl[arg0];

    if (value >= 6) {
        value -= 6;
    }
    return value;
}

s32 modesel_BoardTypeGet(s32 arg0) {
    s32 value = modesel_boardNoTbl[arg0];

    return value < 6 ? 1 : 2;
}

u8 modesel_UnusedOrderGet(s32 arg0) {
    return modesel_unusedOrderTbl[arg0];
}
