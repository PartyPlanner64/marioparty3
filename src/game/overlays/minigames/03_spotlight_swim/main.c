#include "common.h"
#include "game/overlays/minigame.h"
#include "game/mallocblock.h"
#include "humath.h"
#include "game/pause.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
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
} SpotlightSwimData; // sizeof 0x84

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ s8 unk04;
} SpotlightSwimUnk8; // sizeof 0x8

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
} SpotlightSwimAimCom; // sizeof 0x8

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} SpotlightSwimCamera; // sizeof 0x2C

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ u32 r;
    /* 0x0C */ u32 g;
    /* 0x10 */ u32 b;
} SpotlightSwimLight; // sizeof 0x14

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} SpotlightSwimPos2D; // sizeof 0x8

typedef struct {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
} SpotlightSwimState; // sizeof 0x18

typedef struct {
    /* 0x00 */ s8 state;
    /* 0x01 */ s8 timer;
    /* 0x02 */ u8 alpha[2];
    /* 0x04 */ f32 x[2];
    /* 0x0C */ f32 z[2];
} SpotlightSwimRipple; // sizeof 0x14

typedef struct {
    /* 0x00 */ s8 unk00[3];
    /* 0x03 */ s8 unk03[3];
} SpotlightSwimTeamBss; // sizeof 0x6

typedef struct {
    /* 0x00 */ s8 unk00[3];
    /* 0x03 */ s8 unk03[3];
} SpotlightSwimBubbleBss; // sizeof 0x6

extern s32 omCharModelNoTbl[][6];
extern s32 omCharMotTbl[][6];
extern s16 Hu3DCamMtxNo;

s8 m203_slotOrderTbl[][3] = {
    { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 }
};
s32 m203_voiceChrTbl[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 m203_seTbl[4] = { 0x70, 0x79, 0x82, 0x8B };
u8 m203_comCornerTbl[][2] = {
    { 1, 0 }, { 2, 1 }, { 1, 1 }, { 2, 0 }, { 0, 1 }, { 3, 0 }, { 0, 0 }, { 3, 1 }
};
s16 m203_comTargetXTbl[15] = {
    -450, 450, -450, 450, 0, 0, -450, 450, -150, 150, -150, 150, -225, 225, 0
};
s16 m203_comTargetZTbl[15] = {
    -450, -450, 260, 260, -450, 260, -95, -95, -278, -278, 88, 88, -95, -95, -95
};
u8 m203_comDiveRateTbl[4] = { 80, 100, 140, 170 };
s8 m203_swimmerOfsYTbl[8][9] = {
    { -45, -80, -80, -45, -40, -55, -60, -70, -65 },
    { -30, -30, -30, -45, -35, -55, -65, -45, -65 },
    { -70, -65, -65, -40, -20, -30, -65, -65, -85 },
    { -40, -35, -35, -40, -45, -50, -45, -55, -55 },
    { -50, -45, -45, -55, -45, -75, -60, -55, -65 },
    { -20, -35, -35, -35, -30, -95, -95, -128, -85 },
    { -30, -30, -30, -45, -35, -55, -100, -120, -100 },
    { -70, -65, -65, -45, -20, -30, -65, -65, -85 },
};
s8 m203_wakeOfsTbl[8][2] = {
    { 0, 60 }, { 20, 75 }, { 30, 90 }, { 20, 75 }, { 20, 75 }, { 70, 120 }, { 0, 0 }, { 0, 0 }
};
u8 m203_aimHitMaskTbl[4] = { 6, 5, 3, 0 };
u8 m203_aimComDelayTbl[4][2] = { { 60, 25 }, { 55, 20 }, { 50, 15 }, { 45, 10 } };
s8 m203_aimHitSeF = 0;
s16 m203_lampAnimTbl[4] = { 8, 9, 10, 0 };
s16 m203_lampBodyAnimTbl[4] = { 11, 12, 13, 0 };
u8 m203_lightShapeTbl[32][32] = {
    { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 13, 13, 13, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 15, 14, 14, 13, 12, 12, 11, 10, 10, 10, 10, 10, 10, 11, 12, 12, 13, 14, 14, 15, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 14, 13, 12, 11, 10, 9, 8, 7, 7, 6, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 14, 13, 12, 10, 9, 7, 6, 5, 4, 4, 3, 3, 4, 4, 5, 6, 7, 9, 10, 12, 13, 14, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 14, 13, 11, 10, 8, 6, 4, 3, 2, 2, 1, 1, 1, 1, 2, 2, 3, 4, 6, 8, 10, 11, 13, 14, 15, 15, 15, 15 },
    { 15, 15, 15, 14, 13, 11, 9, 7, 5, 3, 2, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 2, 3, 5, 7, 9, 11, 13, 14, 15, 15, 15 },
    { 15, 15, 14, 13, 12, 10, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 7, 10, 12, 13, 14, 15, 15 },
    { 15, 15, 14, 12, 10, 8, 5, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 5, 8, 10, 12, 14, 15, 15 },
    { 15, 14, 13, 11, 9, 6, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 6, 9, 11, 13, 14, 15 },
    { 15, 14, 12, 10, 7, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 7, 10, 12, 14, 15 },
    { 14, 14, 12, 9, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 9, 12, 14, 14 },
    { 14, 13, 11, 8, 5, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, 8, 11, 13, 14 },
    { 14, 13, 10, 7, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 7, 10, 13, 14 },
    { 14, 13, 10, 7, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 7, 10, 13, 14 },
    { 14, 12, 10, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 10, 12, 14 },
    { 14, 12, 10, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 10, 12, 14 },
    { 14, 13, 10, 7, 4, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 4, 7, 10, 13, 14 },
    { 14, 13, 10, 7, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 7, 10, 13, 14 },
    { 14, 13, 11, 8, 5, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 5, 8, 11, 13, 14 },
    { 14, 14, 12, 9, 6, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 6, 9, 12, 14, 14 },
    { 15, 14, 12, 10, 7, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 4, 7, 10, 12, 14, 15 },
    { 15, 14, 13, 11, 9, 6, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 6, 9, 11, 13, 14, 15 },
    { 15, 15, 14, 12, 10, 8, 5, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 3, 5, 8, 10, 12, 14, 15, 15 },
    { 15, 15, 14, 13, 12, 10, 7, 5, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 5, 7, 10, 12, 13, 14, 15, 15 },
    { 15, 15, 15, 14, 13, 11, 9, 7, 5, 3, 2, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 2, 3, 5, 7, 9, 11, 13, 14, 15, 15, 15 },
    { 15, 15, 15, 15, 14, 13, 11, 10, 8, 6, 4, 3, 2, 2, 1, 1, 1, 1, 2, 2, 3, 4, 6, 8, 10, 11, 13, 14, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 14, 13, 12, 10, 9, 7, 6, 5, 4, 4, 3, 3, 4, 4, 5, 6, 7, 9, 10, 12, 13, 14, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 14, 13, 12, 11, 10, 9, 8, 7, 7, 6, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 15, 14, 14, 13, 12, 12, 11, 10, 10, 10, 10, 10, 10, 11, 12, 12, 13, 14, 14, 15, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 13, 13, 13, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
    { 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 },
};
s32 m203_haloXTbl[3] = { 28, 128, 228 };
SpotlightSwimCamera m203_cameraViewTbl[1] = {
    { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 30.0f },
};

extern const s16 m203_fontMesTbl[];

u32 m203_darkBufNo BSS;
s8 m203_aimHitBits BSS;
u32 *m203_darkBufTbl[3] BSS;
s8 m203_swimmerUpTimer BSS;
s16 m203_swimmerTimer BSS;
SpotlightSwimAimCom m203_aimComTbl[3] BSS;
SpotlightSwimTeamBss m203_teamBss BSS;
SpotlightSwimState m203_swimmerState BSS;
s8 m203_teamChrTbl[3] BSS;
s8 m203_swimmerMotNo BSS;
f32 m203_swimmerSpeed BSS;
omObjData *m203_swimmerObj BSS;
s16 m203_mainTimer BSS;
s8 m203_comTargetNo BSS;
SpotlightSwimRipple m203_ripple BSS;
s16 m203_timer BSS;
s8 m203_aimPadNo BSS;
s8 m203_swimmerMotWait BSS;
s16 m203_aimDistTbl[4] BSS;
f32 m203_swimmerScreenPos[2] BSS;
s8 m203_comCornerF BSS;
s8 m203_swimmerDiveCnt BSS;
u8 m203_swimmerDiveCntPad[4] BSS; /* Unreferenced. */
f32 m203_bubbleXTbl[3] BSS;
f32 m203_bubbleZTbl[3] BSS;
SpotlightSwimBubbleBss m203_bubbleBss BSS;
f32 m203_operatorXTbl[3] BSS;
s8 m203_slotOrderNo BSS;
s16 m203_seNoTbl[8] BSS;
f32 m203_aimAngleTbl[3] BSS;
s8 m203_swimmerHumanF BSS;
s8 m203_swimmerPlayerNo BSS;
SpotlightSwimLight m203_lightTbl[6] BSS;
u32 m203_darkRgb BSS;
s8 m203_swimmerChr BSS;
SpotlightSwimPos2D m203_wakePosTbl[5] BSS;
s8 m203_rippleStartF BSS;
u32 m203_darkAlpha BSS;
SpotlightSwimData m203_objWorkTbl[50] BSS;
s8 m203_phase BSS;
u8 m203_phasePad[4] BSS; /* Unreferenced. */
SpotlightSwimUnk8 m203_lampStateTbl[4] BSS;

void m203_ScreenPosCalc(s16, f32, f32, f32, f32 *);
void m203_WakeUpdate(omObjData *);
void m203_StageObjInit(omObjData *);
void m203_WaterObjMain(omObjData *);
void m203_WaterObjInit(omObjData *);
void m203_BubbleObjMain(omObjData *);
void m203_BubbleObjInit(omObjData *);
void m203_SwimmerObjInit(omObjData *);
void m203_LampObjInit(omObjData *);
void m203_ResultObjInit(omObjData *);
void m203_OperatorObjInit(omObjData *);
void m203_DarkDraw(Gfx **gfx, s32 arg1, s32 arg2);
void m203_DarkObjInit(omObjData *);
void m203_AimObjInit(omObjData *);
void m203_AimObjMain(omObjData *);
void m203_AimComInput(omObjData *);
void m203_AimObjCreate(void);
void m203_OperatorObjCreate(void);
void m203_MainObjMain(omObjData *);
void m203_ResultObjMain(omObjData *);
void m203_SwimmerFinishMotUpdate(omObjData *);
void m203_ObjectSetup(void);
void m203_OperatorObjMain(omObjData *);
void m203_SwimmerComDirCalc(omObjData *);

void m203_Executor(void) {
    m203_ObjectSetup();
}

f32 m203_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void m203_ObjWorkInit(void) {
    SpotlightSwimData *data;
    u32 i;

    for (i = 0, data = m203_objWorkTbl; i < 50; i++, data++) {
        data->obj = NULL;
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

void m203_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

void m203_PlayerSeAudPlay(s16 arg0, s16 arg1) {
    s16 stopSeNo = m203_seNoTbl[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    m203_seNoTbl[arg1] = HuAudPlayerFXPlay(m203_seTbl[arg0], arg1);
}

void m203_PlayerSePlay(s16 arg0, s16 arg1) {
    s16 stopSeNo = m203_seNoTbl[arg1];

    if (stopSeNo != -1) {
        HuAudFXStop(stopSeNo);
    }

    m203_seNoTbl[arg1] = PlayerFXPlay(m203_seTbl[arg0], arg1);
}

s32 m203_RandGet(s32 arg0) {
    return rand8() % arg0;
}

void m203_MotSet(omObjData *arg0, u16 arg1, s16 arg2) {
    if (arg1 < 0xA) {
        Hu3DMotionModelSet(arg0->model[0], arg0->motion[arg1]);
        Hu3DMotionAttrSet(arg0->model[0], arg2, arg2);
    }
}

void m203_MotShiftSet(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if (arg1 < 0xA) {
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
    }
}

s8 m203_FrontTurn(omObjData *obj) {
    if (obj->rot.y != 0.0f) {
        if (obj->rot.y < 180.0f) {
            obj->rot.y = m203_AngleAdd(obj->rot.y, -7.0f);
            if (obj->rot.y > 350.0f) {
                obj->rot.y = 0.0f;
            }
        } else {
            obj->rot.y = m203_AngleAdd(obj->rot.y, 7.0f);
            if (obj->rot.y < 10.0f) {
                obj->rot.y = 0.0f;
            }
        }
        return 1;
    }

    return 0;
}

void m203_ScreenPosCalc(s16 camIndex, f32 x, f32 y, f32 z, f32 *screenPos) {
    HuCamera *camera = &gCameraList[camIndex];
    Mtx *lookAt = &camera->mtxs[Hu3DCamMtxNo].lookAtMtx;
    Mtx mtx;
    u16(*integer)[4] = (u16(*)[4])mtx.m;
    u16(*fraction)[4] = (u16(*)[4])mtx.m[2];
    f32 viewX, viewY, viewZ;
    f32 depth;
    s16 vpIndex;

    HuTranslate(&mtx, x, y, z);
    guMtxCatL(&mtx, lookAt, &mtx);
    viewX = (s32)(((u32)integer[3][0] << 16) | fraction[3][0]) >> 16;
    viewY = (s32)(((u32)integer[3][1] << 16) | fraction[3][1]) >> 16;
    viewZ = (s32)(((u32)integer[3][2] << 16) | fraction[3][2]) >> 16;
    depth = viewZ * sind(gCameraList[camIndex].fov / 2.0) / cosdf(gCameraList[camIndex].fov / 2.0);
    depth = (depth >= 0.0f) ? depth : 0.0f - depth;
    if (depth != 0.0) {
        vpIndex = Hu3DCamMtxNo;
        screenPos[0] = (s16)(camera->viewports[vpIndex].vp.vscale[0] / 4.0 * viewX / depth / (4.0f / 3.0f)) + camera->viewports[vpIndex].vp.vtrans[0] / 4.0;
        screenPos[1] = (s16)(camera->viewports[vpIndex].vp.vscale[1] / 4.0 * -viewY / depth) + camera->viewports[vpIndex].vp.vtrans[1] / 4.0;
    }
}

void m203_StageObjMain(omObjData *object) {
}

void m203_StageObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x240000, 0x299);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    obj->func = m203_StageObjMain;
}

void m203_StageObjCreate(void) {
    m203_objWorkTbl[0].obj = omAddObj(0x1F4, 1, 0, -1, m203_StageObjInit);
}

void m203_WaterObjMain(omObjData *obj) {
    SpotlightSwimData *data = &m203_objWorkTbl[1];

    if (++data->unk06 >= 30) {
        data->unk04++;
        data->unk06 = 0;
    }

    switch (data->unk04 & 1) {
        case 0:
            obj->trans.y += 0.5f;
            obj->trans.z -= 0.5f;
            if (m203_swimmerMotNo != 7) {
                m203_swimmerState.unk10 += 0.5f;
                m203_swimmerObj->trans.z -= 0.5f;
            }
            break;
        case 1:
            obj->trans.y -= 0.5f;
            obj->trans.z += 0.5f;
            if (m203_swimmerMotNo != 7) {
                m203_swimmerState.unk10 -= 0.5f;
                m203_swimmerObj->trans.z += 0.5f;
            }
            break;
    }

    obj->trans.x -= 4.0f;
    if (obj->trans.x == -254.0f) {
        obj->trans.x = 250.0f;
    }
}

void m203_WaterObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x240001, 0xA9);
    obj->trans.x = 250.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -50.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    obj->func = m203_WaterObjMain;
}

void m203_WaterObjCreate(void) {
    m203_objWorkTbl[1].obj = omAddObj(0x258, 1, 0, -1, m203_WaterObjInit);
}

void m203_BubbleObjMain(omObjData *obj) {
    s8 i;
    f32 *zs;

    for (i = 0; i < 3; i++) {
        switch (m203_bubbleBss.unk03[i]) {
            case 0:
                break;
            case 1:
                m203_bubbleBss.unk00[i]++;
                if (m203_bubbleBss.unk00[i] >= i * 7) {
                    m203_bubbleBss.unk03[i] = 2;
                    m203_bubbleBss.unk00[i] = 0;
                }
                break;
            case 2:
                m203_bubbleBss.unk00[i]++;
                if (m203_bubbleBss.unk00[i] >= 10) {
                    m203_bubbleBss.unk00[i] = 0;
                    m203_bubbleBss.unk03[i] = 0;
                    m203_bubbleXTbl[i] = 1000.0f;
                }
                zs = m203_bubbleZTbl;
                Hu3DModelPosSet(obj->model[i + 1], m203_bubbleXTbl[i], -200.0f, zs[i]);
                break;
        }
    }
}

void m203_BubbleObjInit(omObjData *obj) {
    void *data;
    s8 i;
    f32 *xs;
    f32 *zs;

    data = DataRead(0x24000F);
    for (i = 0, xs = m203_bubbleXTbl, zs = m203_bubbleZTbl; i < 3; i++) {
        obj->model[i + 1] = Hu3DModelRead(0x24000E, 0x289);
        Hu3DAnimCreate(Hu3DData[obj->model[i + 1]].hmf, data, 0, "s203_004_DEF");
        Hu3DModelRemakeStatic(obj->model[i + 1]);
        Hu3DModelDynamicFree(obj->model[i + 1]);
        Hu3DModelCameraSet(obj->model[i + 1], HU3D_CAM0);
        xs[i] = 1000.0f;
        zs[i] = 0.0f;
        Hu3DModelPosSet(obj->model[i + 1], xs[i], -200.0f, zs[i]);
        m203_bubbleBss.unk00[i] = 0;
        m203_bubbleBss.unk03[i] = 0;
    }
    DataClose(data);
    obj->func = m203_BubbleObjMain;
}

void m203_BubbleObjCreate(void) {
    m203_objWorkTbl[16].obj = omAddObj(0x4B0, 5, 3, -1, m203_BubbleObjInit);
}

void m203_SwimSeUpdate(omObjData *obj) {
    if (obj->work[2] == 0 && m203_swimmerMotNo == 1) {
        m203_PlayerSePlay(3, obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 10;
}

void m203_SwimmerSplashPosSet(omObjData *obj) {
    SpotlightSwimData *data;
    f32 angle;

    data = &m203_objWorkTbl[2];
    Hu3DMotionTimeSet(obj->model[5], 0.0f);
    if (obj->work[1] != 5) {
        data->unk44.x = obj->trans.x;
        data->unk44.z = obj->trans.z + 35.0f;
    } else {
        angle = m203_AngleAdd(obj->rot.y, -90.0f);
        data->unk44.x = obj->trans.x - cosdf(angle) * 50.0f;
        data->unk44.z = sindf(angle) * 50.0f + obj->trans.z + 60.0f;
    }
    data->unk44.y = obj->trans.y - m203_swimmerOfsYTbl[obj->work[1]][m203_swimmerMotNo] - 25.0f;
    if (m203_swimmerState.unk04 == 2 || m203_phase == 5) {
        Hu3DModelScaleSet(obj->model[5], 0.6f, 0.5f, 1.0f);
    } else {
        Hu3DModelScaleSet(obj->model[5], 0.8f, 0.6f, 1.0f);
    }
    Hu3DModelPosSet(obj->model[5], data->unk44.x, -200.0f, data->unk44.z);
}

void m203_SwimmerMotUpdate(omObjData *obj) {
    if (m203_swimmerState.unk04 == 2) {
        if (m203_swimmerMotNo != 2 && m203_swimmerMotNo != 3) {
            Hu3DMotionSpeedSet(obj->model[0], -1.0f);
            m203_swimmerMotNo = 2;
            m203_swimmerMotWait = 0;
        }
        if (m203_swimmerMotNo != 3) {
            if (++m203_swimmerMotWait >= 10) {
                m203_MotShiftSet(obj, 3, 0, 1, 2);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionSpeedSet(obj->model[0], 2.0f);
                m203_swimmerMotNo = 3;
            }
        }
    } else if (m203_swimmerState.unk04 == 1) {
        if (m203_swimmerMotNo != 1) {
            m203_MotShiftSet(obj, 1, 0, 5, 0);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            m203_swimmerMotNo = 1;
        }
    } else if (abs(HuPadStkX[obj->work[3]]) < 5 && abs(HuPadStkY[obj->work[3]]) < 5) {
        if (m203_swimmerMotNo != 4) {
            m203_MotShiftSet(obj, 4, 0, 10, 2);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            m203_swimmerMotNo = 4;
        }
    } else if (m203_swimmerMotNo != 0) {
        m203_MotShiftSet(obj, 0, 0, 10, 2);
        Hu3DMotionSpeedSet(obj->model[0], 2.0f);
        m203_swimmerMotNo = 0;
    }
}

void m203_SwimmerFinishMotUpdate(omObjData *obj) {
    if (m203_aimHitBits == 7) {
        if (m203_swimmerMotNo != 5) {
            m203_MotShiftSet(obj, 5, 0, 15, 2);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            m203_swimmerMotNo = 5;
            if (obj->trans.x <= -440.0f) {
                obj->trans.x += 25.0f;
            }
            if (obj->trans.x >= 440.0f) {
                obj->trans.x -= 20.0f;
            }
            if (obj->trans.z <= -440.0f) {
                obj->trans.z += 50.0f;
            }
        }
        m203_FrontTurn(obj);
    } else if (m203_phase >= 3) {
        if (m203_swimmerMotNo < 5) {
            m203_MotShiftSet(obj, 6, 0, 15, 1);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            m203_swimmerMotNo = 8;
            if (obj->trans.x <= -440.0f) {
                obj->trans.x += 25.0f;
            }
            if (obj->trans.x >= 440.0f) {
                obj->trans.x -= 20.0f;
            }
            if (obj->trans.z <= -440.0f) {
                obj->trans.z += 50.0f;
            }
            if (m203_swimmerState.unk04 == 1) {
                m203_rippleStartF = 1;
                m203_SwimmerSplashPosSet(obj);
            }
        }
        if (m203_swimmerMotNo == 8 && m203_FrontTurn(obj) != 0) {
            return;
        }
        if (m203_phase == 5 && m203_swimmerMotNo != 6) {
            m203_MotSet(obj, 6, 0);
            HuAudCharVoicePlay((m203_voiceChrTbl[GwPlayer[obj->work[0]].chr] << 16) | 0x2F);
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            m203_swimmerMotNo = 6;
        }
    }
}

void m203_RippleUpdate(omObjData *obj) {
    f32 y;

    switch (m203_ripple.state) {
        case 0:
            if (m203_rippleStartF != 0) {
                m203_ripple.timer = 0;
                m203_ripple.state = 1;
                m203_rippleStartF = 0;
            }
            break;
        case 1:
            if (m203_ripple.timer == 0) {
                Hu3DMotionTimeSet(obj->model[6], 0);
                Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (obj->work[1] != 5) {
                    m203_ripple.x[0] = obj->trans.x;
                    m203_ripple.z[0] = obj->trans.z;
                } else {
                    m203_ripple.x[0] = obj->trans.x - sindf(obj->rot.y) * 50.0f;
                    m203_ripple.z[0] = obj->trans.z - cosdf(obj->rot.y) * 50.0f;
                }
                m203_ripple.alpha[0] = 255;
                Hu3DModelTPLvlSet(obj->model[6], 255);
            } else if (m203_ripple.timer >= 5) {
                if (m203_ripple.alpha[0] >= 36) {
                    m203_ripple.alpha[0] -= 20;
                } else {
                    Hu3DModelAttrSet(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    m203_ripple.alpha[0] = 0;
                }
                Hu3DModelTPLvlSet(obj->model[6], m203_ripple.alpha[0]);
            }
            if (m203_ripple.timer == 8) {
                Hu3DMotionTimeSet(obj->model[7], 0);
                Hu3DModelAttrSet(obj->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (obj->work[1] != 5) {
                    m203_ripple.x[1] = obj->trans.x;
                    m203_ripple.z[1] = obj->trans.z;
                } else {
                    m203_ripple.x[0] = obj->trans.x - sindf(obj->rot.y) * 50.0f;
                    m203_ripple.z[0] = obj->trans.z - cosdf(obj->rot.y) * 50.0f;
                }
                m203_ripple.alpha[1] = 255;
                Hu3DModelTPLvlSet(obj->model[7], 255);
            } else if (m203_ripple.timer >= 10) {
                if (m203_ripple.alpha[1] >= 36) {
                    m203_ripple.alpha[1] -= 20;
                } else {
                    Hu3DModelAttrSet(obj->model[7], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    m203_ripple.alpha[1] = 0;
                    m203_ripple.state = 0;
                }
                Hu3DModelTPLvlSet(obj->model[7], m203_ripple.alpha[1]);
            }
            m203_ripple.timer++;
            break;
    }
    if (m203_phase == 3 && m203_swimmerState.unk04 != 1) {
        Hu3DModelScaleSet(obj->model[6], 2.5f, 2.5f, 2.5f);
        Hu3DModelScaleSet(obj->model[7], 2.5f, 2.5f, 2.5f);
    } else if (obj->work[1] != 5) {
        Hu3DModelScaleSet(obj->model[6], 1.5f, 1.5f, 1.5f);
        Hu3DModelScaleSet(obj->model[7], 1.5f, 1.5f, 1.5f);
    } else {
        Hu3DModelScaleSet(obj->model[6], 1.7f, 1.7f, 1.78f);
        Hu3DModelScaleSet(obj->model[7], 1.7f, 1.7f, 1.7f);
    }
    y = m203_swimmerState.unk10 + -200.0f + 3.0f;
    Hu3DModelPosSet(obj->model[6], m203_ripple.x[0], y, m203_ripple.z[0]);
    Hu3DModelPosSet(obj->model[7], m203_ripple.x[1], y, m203_ripple.z[1]);
}

void m203_WakeUpdate(omObjData *obj) {
    SpotlightSwimData *data = &m203_objWorkTbl[2];
    s8 playerIndex;
    s8 i;
    f32 angle;

    if (m203_swimmerState.unk04 <= 0) {
        playerIndex = obj->work[1];
        if (m203_swimmerMotNo == 0) {
            if (data->unk04 == 0) {
                data->unk06 = (data->unk06 + 1) & 3;
                i = m203_swimmerState.unk01 != 0;
                angle = m203_AngleAdd(obj->rot.y, -90.0f);
                m203_wakePosTbl[data->unk06 + 1].x =
                    obj->trans.x - m203_wakeOfsTbl[playerIndex][i] * cosdf(angle);
                m203_wakePosTbl[data->unk06 + 1].z =
                    m203_wakeOfsTbl[playerIndex][i] * sindf(angle) + obj->trans.z + 15.0f;
                Hu3DMotionTimeSet(obj->model[data->unk06 + 1], 0);
                m203_PlayerSePlay(1, obj->work[0]);
            }
            data->unk04 = (data->unk04 + 1) % 6;
        }

        for (i = 1; i < 5; i++) {
            Hu3DModelPosSet(obj->model[i], m203_wakePosTbl[i].x,
                            obj->trans.y - m203_swimmerOfsYTbl[playerIndex][m203_swimmerMotNo] - 25.0f,
                            m203_wakePosTbl[i].z);
            Hu3DModelScaleSet(obj->model[i], 0.3f, 0.5f, 0.5f);
        }
    }
}

void m203_BubbleStart(omObjData *obj) {
    f32 x;
    f32 z;
    s8 i;

    for (i = 0; i < 3; i++) {
        x = m203_RandGet(30) + 15;
        if (m203_RandGet(2) != 0) {
            x = 0.0f - x;
        }
        z = m203_RandGet(30) + 15;
        if (m203_RandGet(2) != 0) {
            z = 0.0f - z;
        }
        m203_bubbleXTbl[i] = x + obj->trans.x;
        m203_bubbleZTbl[i] = z + obj->trans.z;
        m203_bubbleBss.unk03[i] = 1;
    }
}

s8 m203_SwimmerEdgeXCheck(omObjData *obj) {
    if ((HuPadStkX[obj->work[3]] < 3 && obj->trans.x <= -450.0f) ||
        (HuPadStkX[obj->work[3]] >= 4 && obj->trans.x >= 450.0f)) {
        m203_swimmerState.unk01 |= 1;
        return 0;
    }
    return 1;
}

s8 m203_SwimmerEdgeZCheck(omObjData *obj) {
    if ((HuPadStkY[obj->work[3]] >= 4 && obj->trans.z <= -450.0f) ||
        (HuPadStkY[obj->work[3]] < 3 && obj->trans.z >= 260.0f)) {
        m203_swimmerState.unk01 |= 2;
        return 0;
    }
    return 1;
}

void m203_SwimmerComStickSet(omObjData *obj) {
    s16 idx = obj->work[3];
    f32 rot = obj->rot.y;
    s16 quadrant;

    quadrant = 0;
    if (rot >= 90.0f) {
        quadrant++;
    }
    if (rot >= 180.0f) {
        quadrant++;
    }
    if (rot >= 270.0f) {
        quadrant++;
    }

    switch (quadrant) {
        case 0:
            HuPadStkX[idx] = rot * m203_swimmerState.unk0C;
            HuPadStkY[idx] = 0.0f - (90.0f - rot) * m203_swimmerState.unk0C;
            break;
        case 1:
            rot -= 90.0f;
            HuPadStkX[idx] = (90.0f - rot) * m203_swimmerState.unk0C;
            HuPadStkY[idx] = rot * m203_swimmerState.unk0C;
            break;
        case 2:
            rot -= 180.0f;
            HuPadStkX[idx] = 0.0f - rot * m203_swimmerState.unk0C;
            HuPadStkY[idx] = (90.0f - rot) * m203_swimmerState.unk0C;
            break;
        case 3:
            rot -= 270.0f;
            HuPadStkX[idx] = 0.0f - (90.0f - rot) * m203_swimmerState.unk0C;
            HuPadStkY[idx] = 0.0f - rot * m203_swimmerState.unk0C;
            break;
    }
}

void m203_SwimmerMove(omObjData *obj) {
    s8 stickX;
    s8 stickY;

    stickX = HuPadStkX[obj->work[3]];
    if (stickX >= 64) {
        stickX = 63;
    } else if (stickX < -63) {
        stickX = -63;
    }
    stickY = -HuPadStkY[obj->work[3]];
    if (stickY >= 64) {
        stickY = 63;
    } else if (stickY < -63) {
        stickY = -63;
    }
    m203_swimmerState.unk01 = 0;
    if (m203_SwimmerEdgeXCheck(obj)) {
        obj->trans.x += stickX / m203_swimmerSpeed;
    }
    if (m203_SwimmerEdgeZCheck(obj)) {
        obj->trans.z += stickY / m203_swimmerSpeed;
    }
    if (m203_swimmerHumanF != 0) {
        if ((stickX < 0 ? -stickX : stickX) >= 5 || (stickY < 0 ? -stickY : stickY) >= 5) {
            obj->rot.y = m203_AngleAdd(atan2df(stickX, stickY), 0.0f);
        }
    }
    m203_ScreenPosCalc(0, obj->trans.x, obj->trans.y + 50.0f, obj->trans.z, m203_swimmerScreenPos);
    m203_WakeUpdate(obj);
    m203_SwimmerMotUpdate(obj);
}

void m203_SwimmerComDirCalc(omObjData *obj) {
    s8 flags;
    s8 farCount;
    s8 nearCount;
    s8 midCount;
    s16 maxAngle;
    s16 minAngle;
    s16 i;
    s16 r;
    f32 angle;

    flags = 0;
    farCount = 0;
    nearCount = 0;
    midCount = 0;
    maxAngle = 0;
    minAngle = 540;
    for (i = 0; i < 3; i++) {
        angle = m203_aimAngleTbl[i];
        if (angle < 180.0f) {
            angle += 360.0f;
        }
        if (angle < minAngle) {
            minAngle = angle;
        }
        if (maxAngle < angle) {
            maxAngle = angle;
        }
        if (m203_aimDistTbl[i] < 24) {
            nearCount++;
        }
        if (m203_aimDistTbl[i] < 39) {
            midCount++;
        }
        if (m203_aimDistTbl[i] >= 107) {
            farCount++;
        }
    }

    if (obj->trans.x <= -350.0f) {
        flags |= 1;
    } else if (obj->trans.x >= 350.0f) {
        flags |= 2;
    }
    if (obj->trans.z <= -350.0f) {
        flags |= 4;
    } else if (obj->trans.z >= 160.0f) {
        flags |= 8;
    }

    if (m203_comCornerF == 0) {
        if (flags == 5 || flags == 6 || flags == 9 || flags == 10) {
            m203_comCornerF = 1;
            r = m203_RandGet(2);
            switch (flags) {
                case 5:
                    break;
                case 6:
                    r += 4;
                    break;
                case 9:
                    r += 6;
                    break;
                case 10:
                    r += 2;
                    break;
            }
            m203_comTargetNo = m203_comCornerTbl[r][0];
            m203_swimmerState.unk03 = m203_comCornerTbl[r][1];
        }
    }

    if (obj->trans.x >= -150.0f && obj->trans.x <= 150.0f && obj->trans.z >= -200.0f && obj->trans.z <= 10.0f) {
        if (midCount >= 2 && m203_swimmerState.unk05 != 0) {
            m203_comCornerF = 0;
            m203_swimmerState.unk05 = 2;
        }
    }

    if (m203_swimmerState.unk04 == 0) {
        if ((midCount == 3 && nearCount == 2) || (midCount == 3 && m203_swimmerState.unk01 == 3)) {
            r = m203_RandGet(250) + m203_RandGet(250);
            if (m203_timer >= 451) {
                r >>= 1;
            }
            if (r < m203_comDiveRateTbl[m203_swimmerState.unk00]) {
                m203_swimmerState.unk04 = 1;
                m203_SwimmerSplashPosSet(obj);
                m203_PlayerSePlay(0, obj->work[0]);
            }
        }
    } else if (m203_swimmerState.unk04 == 1) {
        if (farCount > 0 && m203_swimmerState.unk00 >= 2) {
            m203_swimmerState.unk04 = 2;
            m203_SwimmerSplashPosSet(obj);
            m203_rippleStartF = 1;
            m203_PlayerSePlay(2, obj->work[0]);
        }
    }

    switch (m203_swimmerState.unk05) {
        case 0:
            r = m203_RandGet(100);
            if (r < 10 || m203_swimmerState.unk01 != 0) {
                m203_swimmerState.unk05 = 1;
            }
            break;
        case 1:
            if (m203_comCornerF != 0) {
                if (flags == 0) {
                    m203_comCornerF = 0;
                }
            } else {
                r = m203_RandGet(100);
                if (r < 5 || m203_swimmerState.unk01 == 1 || m203_swimmerState.unk01 == 2) {
                    m203_comTargetNo = m203_RandGet(15);
                    m203_swimmerState.unk03 = m203_RandGet(2);
                } else if (r >= 85) {
                    m203_swimmerState.unk05 = 0;
                }
                if (obj->trans.x <= -420.0f || obj->trans.x >= 420.0f) {
                    m203_swimmerState.unk08 = m203_RandGet(2) == 0 ? 180.0f : 0.0f;
                    m203_swimmerState.unk05 = 0;
                }
                if (obj->trans.z <= -420.0f || obj->trans.z >= 230.0f) {
                    m203_swimmerState.unk08 = m203_RandGet(2) ? 90.0f : 270.0f;
                    m203_swimmerState.unk05 = 0;
                }
            }
            angle = m203_AngleAdd(
                atan2df(m203_comTargetXTbl[m203_comTargetNo] - obj->trans.x,
                        m203_comTargetZTbl[m203_comTargetNo] - obj->trans.z),
                0.0f);
            if (m203_swimmerState.unk03 != 0) {
                m203_swimmerState.unk08 = m203_AngleAdd(angle, 90.0f);
            } else {
                m203_swimmerState.unk08 = m203_AngleAdd(angle, 270.0f);
            }
            break;
        case 2:
            m203_swimmerState.unk08 = ((minAngle + maxAngle + 360) >> 1) % 360;
            if (obj->trans.x <= -420.0f || obj->trans.x >= 420.0f) {
                m203_swimmerState.unk08 = m203_RandGet(2) == 0 ? 180.0f : 0.0f;
                m203_swimmerState.unk05 = 0;
            }
            if (obj->trans.z <= -420.0f || obj->trans.z >= 230.0f) {
                m203_swimmerState.unk08 = m203_RandGet(2) ? 90.0f : 270.0f;
                m203_swimmerState.unk05 = 0;
            }
            break;
    }
}

void m203_SwimmerComObjMain(omObjData *obj) {
    if (m203_phase != 2) {
        m203_SwimmerFinishMotUpdate(obj);
        return;
    }

    m203_swimmerState.unk0C = 1.2f;
    switch (m203_swimmerState.unk04) {
        case 0:
            m203_swimmerState.unk02 = 0;
            m203_SwimmerComDirCalc(obj);
            break;
        case 1:
            m203_swimmerDiveCnt++;
            if (m203_swimmerState.unk02 != 0) {
                m203_SwimmerComDirCalc(obj);
            } else {
                m203_swimmerState.unk08 = m203_AngleAdd(
                    atan2df(m203_comTargetXTbl[14] - obj->trans.x, m203_comTargetZTbl[14] - obj->trans.z), 0.0f);
                if (obj->trans.x >= m203_comTargetXTbl[14] - 10 && obj->trans.x <= m203_comTargetXTbl[14] + 10 &&
                    obj->trans.z >= m203_comTargetZTbl[14] - 10 && obj->trans.z <= m203_comTargetZTbl[14] + 10) {
                    m203_swimmerState.unk02 = 1;
                }
                if (m203_swimmerDiveCnt >= 30 || m203_swimmerState.unk00 < 2) {
                    m203_swimmerState.unk02 = 1;
                }
            }
            if (m203_swimmerDiveCnt < 11) {
                m203_PadClear(obj->work[0]);
                m203_SwimmerMove(obj);
                return;
            }
            if (m203_swimmerDiveCnt == 40) {
                m203_BubbleStart(obj);
            }
            if (m203_swimmerDiveCnt == 60) {
                m203_BubbleStart(obj);
            }
            if (m203_swimmerDiveCnt >= 90) {
                m203_swimmerState.unk04 = 2;
                m203_SwimmerSplashPosSet(obj);
                m203_rippleStartF = 1;
                m203_PlayerSePlay(2, obj->work[0]);
            }
            break;
        case 2:
            m203_swimmerState.unk0C = 0.0f;
            if (++m203_swimmerUpTimer >= 40) {
                m203_swimmerDiveCnt = 0;
                m203_swimmerUpTimer = 0;
                m203_swimmerState.unk04 = 0;
            }
            break;
    }

    obj->rot.y = m203_swimmerState.unk08;
    m203_SwimmerComStickSet(obj);
    if (abs(HuPadStkX[obj->work[3]]) >= 6 || abs(HuPadStkY[obj->work[3]]) >= 6) {
        m203_SwimSeUpdate(obj);
    } else if (abs(HuPadStkX[obj->work[3]]) < 6 && abs(HuPadStkY[obj->work[3]]) < 6) {
        obj->work[2] = 0;
    }
    m203_SwimmerMove(obj);
}

void m203_SwimmerObjMain(omObjData *obj) {
    if (m203_phase != 2) {
        m203_SwimmerFinishMotUpdate(obj);
        return;
    }

    switch (m203_swimmerState.unk04) {
        case 0:
            if (HuPadBtnDown[obj->work[3]] & A_BUTTON) {
                m203_SwimmerSplashPosSet(obj);
                m203_swimmerState.unk04 = 1;
                m203_PlayerSePlay(0, obj->work[0]);
            }
            break;
        case 1:
            if (++m203_swimmerDiveCnt < 11) {
                m203_PadClear(obj->work[0]);
            }
            if (m203_swimmerDiveCnt == 40) {
                m203_BubbleStart(obj);
            }
            if (m203_swimmerDiveCnt == 60) {
                m203_BubbleStart(obj);
            }
            if (!((u16)HuPadBtn[obj->work[3]] & A_BUTTON) && m203_swimmerDiveCnt >= 15) {
                m203_swimmerState.unk04 = 2;
                m203_SwimmerSplashPosSet(obj);
                m203_rippleStartF = 1;
                m203_PlayerSePlay(2, obj->work[0]);
            }
            if (m203_swimmerDiveCnt >= 90) {
                m203_swimmerState.unk04 = 2;
                m203_SwimmerSplashPosSet(obj);
                m203_rippleStartF = 1;
                m203_PlayerSePlay(2, obj->work[0]);
            }
            break;
        case 2:
            HuPadStkX[obj->work[3]] = 0;
            HuPadStkY[obj->work[3]] = 0;
            if (++m203_swimmerUpTimer >= 40) {
                m203_swimmerState.unk04 = 0;
                m203_swimmerDiveCnt = 0;
                m203_swimmerUpTimer = 0;
            }
            break;
    }

    if (abs(HuPadStkX[obj->work[3]]) >= 6 || abs(HuPadStkY[obj->work[3]]) >= 6) {
        m203_SwimSeUpdate(obj);
    } else if (abs(HuPadStkX[obj->work[3]]) < 6 && abs(HuPadStkY[obj->work[3]]) < 6) {
        obj->work[2] = 0;
    }
    m203_SwimmerMove(obj);
}

void m203_SwimmerObjInit(omObjData *obj) {
    SpotlightSwimData *data;
    u16 chr;

    chr = GwPlayer[obj->work[0]].chr;
    obj->work[1] = chr;
    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharMotTbl[chr][0], 0x2B9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 9));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x60));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x61));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0xD));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x59));
    omObjMotionRead(obj, 7, CharMotionDataNumGet(chr, 4));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x2F));
    obj->trans.x = 0.0f;
    obj->trans.y = -200.0f;
    obj->trans.z = -90.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    m203_MotSet(obj, 4, 2);
    m203_swimmerMotNo = 4;
    obj->model[1] = Hu3DModelRead(0x240006, 0x299);
    obj->model[2] = Hu3DModelRead(0x240006, 0x299);
    obj->model[3] = Hu3DModelRead(0x240006, 0x299);
    obj->model[4] = Hu3DModelRead(0x240006, 0x299);
    obj->model[5] = Hu3DModelRead(0x240006, 0x2B9);
    obj->model[6] = Hu3DModelRead(0x240007, 0x288);
    Hu3DModelTPLvlInit(obj->model[6]);
    Hu3DModelTPLvlSet(obj->model[6], 0xFF);
    obj->model[7] = Hu3DModelRead(0x240007, 0x288);
    Hu3DModelTPLvlInit(obj->model[7]);
    Hu3DModelTPLvlSet(obj->model[7], 0xFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[3], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[4], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[5], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[6], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[7], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[8], HU3D_CAM0);
    m203_wakePosTbl[1].x = 0.0f;
    m203_wakePosTbl[1].z = 0.0f;
    m203_wakePosTbl[2].x = 0.0f;
    m203_wakePosTbl[2].z = 0.0f;
    m203_wakePosTbl[3].x = 0.0f;
    m203_wakePosTbl[3].z = 0.0f;
    m203_wakePosTbl[4].x = 0.0f;
    m203_wakePosTbl[4].z = 0.0f;
    data = &m203_objWorkTbl[2];
    data->unk44.x = 0.0f;
    data->unk44.y = -500.0f;
    data->unk44.x = 0.0f;
    Hu3DModelPosSet(obj->model[1], m203_wakePosTbl[1].x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[2], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[3], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[4], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[5], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[6], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[7], data->unk44.x, data->unk44.y, data->unk44.z);
    Hu3DModelPosSet(obj->model[8], data->unk44.x, data->unk44.y, data->unk44.z);
    m203_swimmerDiveCnt = 0;
    m203_swimmerUpTimer = 0;
    m203_aimHitBits = 0;
    m203_swimmerTimer = 0;
    m203_swimmerSpeed = 7.0f;
    m203_comCornerF = 0;
    m203_comTargetNo = 0;
    m203_swimmerState.unk01 = 0;
    m203_swimmerState.unk02 = 0;
    m203_swimmerState.unk03 = 0;
    m203_swimmerState.unk04 = 0;
    m203_swimmerState.unk05 = 0;
    m203_swimmerState.unk08 = 0.0f;
    m203_swimmerState.unk0C = 0.0f;
    m203_swimmerState.unk10 = 0.0f;
    m203_swimmerState.unk00 = GwPlayer[obj->work[0]].cpu_difficulty;
    m203_rippleStartF = 0;
    m203_ripple.timer = 0;
    m203_ripple.state = 0;
    m203_ripple.alpha[0] = 0xFF;
    m203_ripple.alpha[1] = 0xFF;
    m203_ripple.x[0] = 1000.0f;
    m203_ripple.x[1] = 1000.0f;
    m203_ripple.z[0] = 0.0f;
    m203_ripple.z[1] = 0.0f;
    obj->work[3] = GwPlayer[obj->work[0]].pad;
    if (GwPlayer[obj->work[0]].stat & 1) {
        m203_swimmerHumanF = 0;
        obj->func = m203_SwimmerComObjMain;
    } else {
        m203_swimmerHumanF = 1;
        obj->func = m203_SwimmerObjMain;
    }
}

void m203_SwimmerObjCreate(void) {
    u16 playerIndex;
    s16 i;

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

    m203_swimmerObj = omAddObj(0x2BC, 9, 10, -1, m203_SwimmerObjInit);
    m203_swimmerObj->work[0] = playerIndex;
    m203_objWorkTbl[2].obj = m203_swimmerObj;
    m203_swimmerPlayerNo = m203_swimmerObj->work[0];
    m203_swimmerChr = GwPlayer[m203_swimmerObj->work[0]].chr;
}

u8 m203_AimDirGet(omObjData *obj) {
    u8 flags = 0;

    if (HuPadStkX[obj->work[3]] < -5 && obj->trans.x < 65.0f) {
        HuPadStkX[obj->work[3]] = 0;
    } else if (HuPadStkX[obj->work[3]] < -4) {
        flags |= 4;
    }

    if (HuPadStkX[obj->work[3]] >= 6 && obj->trans.x > 255.0f) {
        HuPadStkX[obj->work[3]] = 0;
    } else if (HuPadStkX[obj->work[3]] >= 5) {
        flags |= 8;
    }

    if (HuPadStkY[obj->work[3]] >= 6 && obj->trans.y < 60.0f) {
        HuPadStkY[obj->work[3]] = 0;
    } else if (HuPadStkY[obj->work[3]] >= 5) {
        flags |= 1;
    }

    if (HuPadStkY[obj->work[3]] < -5 && obj->trans.y > 140.0f) {
        HuPadStkY[obj->work[3]] = 0;
    } else if (HuPadStkY[obj->work[3]] < -4) {
        flags |= 2;
    }

    return flags;
}

void m203_AimComRandMove(omObjData *obj) {
    SpotlightSwimAimCom *data = &m203_aimComTbl[obj->work[1]];

    if (++data->unk02 >= data->unk03) {
        data->unk02 = 0;
        data->unk03 = m203_RandGet(20) + 20;
        data->unk04 = m203_RandGet(2) == 0 ? -10 : 10;
        data->unk04 = m203_RandGet(data->unk00 + 4) != 0 ? data->unk04 : 0;
    }

    if (++data->unk05 >= data->unk06) {
        data->unk05 = 0;
        data->unk06 = m203_RandGet(20) + 20;
        data->unk07 = m203_RandGet(2) == 0 ? -10 : 10;
        data->unk07 = m203_RandGet(data->unk00 + 4) != 0 ? data->unk07 : 0;
    }

    HuPadStkX[obj->work[3]] = data->unk04;
    HuPadStkY[obj->work[3]] = data->unk07;
}

void m203_AimComChase(omObjData *obj, f32 targetX, f32 targetY) {
    if (targetX + 3.0f < obj->trans.x) {
        HuPadStkX[obj->work[3]] = -10;
    }
    if (obj->trans.x < targetX - 3.0f) {
        HuPadStkX[obj->work[3]] = 10;
    }
    if (targetY + 3.0f < obj->trans.y) {
        HuPadStkY[obj->work[3]] = 10;
    }
    if (obj->trans.y < targetY - 3.0f) {
        HuPadStkY[obj->work[3]] = -10;
    }
}

void m203_AimComChaseAxis(omObjData *obj, f32 targetX, f32 targetY) {
    if (abs(targetX - obj->trans.x) > abs(targetY - obj->trans.y)) {
        if (targetX + 3.0f < obj->trans.x) {
            HuPadStkX[obj->work[3]] = -10;
        }
        if (obj->trans.x < targetX - 3.0f) {
            HuPadStkX[obj->work[3]] = 10;
        }
    } else {
        if (targetY + 3.0f < obj->trans.y) {
            HuPadStkY[obj->work[3]] = 10;
        }
        if (obj->trans.y < targetY - 3.0f) {
            HuPadStkY[obj->work[3]] = -10;
        }
    }
}

void m203_AimComInput(omObjData *obj) {
    u32 index = obj->work[1];
    SpotlightSwimData *data = &m203_objWorkTbl[index + 3];
    SpotlightSwimAimCom *unk;
    u16 row;
    s8 flags;
    s32 mask;
    u8 *limits;

    if (data->unk16 == 0) {
        return;
    }

    unk = &m203_aimComTbl[index];
    row = 1;

    if (m203_aimPadNo != 0) {
        flags = m203_aimHitBits;
        mask = flags | (1 << (m203_aimPadNo - 1));
        if (flags == mask && m203_swimmerState.unk04 <= 0) {
            goto target;
        }
    } else if (m203_aimHitBits != 0 && m203_swimmerState.unk04 <= 0) {
        if (unk->unk00 == 3) {
        target:
            if (obj->work[0] & 1) {
                goto chase;
            }
            goto wander;
        }
        row = 1;
    }

    if (m203_swimmerState.unk04 == 1) {
        row = 0;
    } else {
        s8 curFlags = m203_aimHitBits;

        mask = curFlags | (1 << index);
        if (curFlags == mask) {
            goto chase;
        }
    }

    if (m203_swimmerState.unk04 == 2) {
        goto chase;
    }

    if (++unk->unk01 >= (limits = m203_aimComDelayTbl[unk->unk00])[row]) {
        if (unk->unk01 == limits[row]) {
            data->unk06 = m203_RandGet(2);
        }

        if (unk->unk01 >= 60) {
            unk->unk01 = m203_RandGet(5);
            return;
        }

        if (data->unk06 != 0) {
            goto chase;
        }
        goto wander;
    } else {
        m203_AimComRandMove(obj);
        return;
    }

chase:
    m203_AimComChase(obj, m203_swimmerScreenPos[0], m203_swimmerScreenPos[1]);
    return;

wander:
    m203_AimComChaseAxis(obj, m203_swimmerScreenPos[0], m203_swimmerScreenPos[1]);
}

void m203_AimHitCheck(omObjData *obj) {
    s8 index = obj->work[1];
    s32 dx = obj->trans.x - m203_swimmerScreenPos[0];
    s32 dy = obj->trans.y - m203_swimmerScreenPos[1];
    s32 dist = sqrtf(dx * dx + dy * dy);

    m203_aimDistTbl[index] = dist;
    m203_aimAngleTbl[index] = m203_AngleAdd(
        atan2df(obj->trans.x - m203_swimmerScreenPos[0], obj->trans.y - m203_swimmerScreenPos[1]), 0.0f);

    if (m203_swimmerState.unk04 == 1) {
        return;
    }

    if (dist < 24) {
        m203_aimHitBits |= 1 << index;
    } else {
        m203_aimHitBits &= m203_aimHitMaskTbl[index];
    }

    if (m203_aimHitBits == 3 || m203_aimHitBits == 5 || m203_aimHitBits == 6) {
        if (m203_aimHitSeF == 0) {
            HuAudFXPlay(0x316);
            m203_aimHitSeF = 1;
        }
    } else {
        m203_aimHitSeF = 0;
    }

    if (m203_aimHitBits == 7) {
        HuAudFXPlay(0x317);
    }
}

void m203_AimObjMain(omObjData *obj) {
    SpotlightSwimData *data = &m203_objWorkTbl[obj->work[1] + 3];

    if (m203_phase != 2) {
        return;
    }

    m203_AimComInput(obj);
    data->unk14 = m203_AimDirGet(obj);

    switch (data->unk14) {
        case 1:
            obj->trans.y -= 1.0f;
            break;
        case 2:
            obj->trans.y += 1.0f;
            break;
        case 4:
            obj->trans.x -= 1.5f;
            break;
        case 8:
            obj->trans.x += 1.5f;
            break;
        case 5:
            obj->trans.x -= 1.0f;
            obj->trans.y -= 1.0f;
            break;
        case 9:
            obj->trans.x += 1.0f;
            obj->trans.y -= 1.0f;
            break;
        case 6:
            obj->trans.x -= 1.0f;
            obj->trans.y += 1.0f;
            break;
        case 10:
            obj->trans.x += 1.0f;
            obj->trans.y += 1.0f;
            break;
    }

    m203_AimHitCheck(obj);
}

void m203_AimObjInit(omObjData *obj) {
    SpotlightSwimData *data = &m203_objWorkTbl[obj->work[1] + 3];
    s8 index = obj->work[1];

    if (GwPlayer[obj->work[0]].stat & 1) {
        data->unk16 = 1;
    } else {
        data->unk16 = 0;
        m203_aimPadNo = index + 1;
    }

    switch (m203_slotOrderTbl[m203_slotOrderNo][index]) {
        case 0:
            obj->trans.x = 70.0f;
            break;
        case 1:
            obj->trans.x = 160.0f;
            break;
        case 2:
            obj->trans.x = 250.0f;
            break;
    }

    obj->trans.y = 140.0f;
    obj->trans.z = 0.0f;
    m203_aimComTbl[index].unk02 = 0;
    m203_aimComTbl[index].unk03 = 0;
    m203_aimComTbl[index].unk04 = 0;
    m203_aimComTbl[index].unk05 = 0;
    m203_aimComTbl[index].unk06 = 0;
    m203_aimComTbl[index].unk07 = 0;
    m203_aimComTbl[index].unk01 = m203_RandGet(60);
    m203_aimComTbl[index].unk00 = GwPlayer[obj->work[0]].cpu_difficulty;
    obj->work[3] = GwPlayer[obj->work[0]].pad;
    obj->func = m203_AimObjMain;
}

void m203_AimObjCreate(void) {
    u16 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            SpotlightSwimData *data;
            omObjData *obj;

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
            data = &m203_objWorkTbl[3 + count];
            obj = omAddObj(0x320, 4, 1, -1, m203_AimObjInit);
            obj->work[0] = playerIndex;
            data->obj = obj;
            obj->work[1] = data->unk04 = count;
            m203_teamBss.unk00[count] = obj->work[0];
            m203_teamChrTbl[count] = GwPlayer[obj->work[0]].chr;
            count++;
        }
    }
}

void m203_OperatorObjMain(omObjData *obj) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    SpotlightSwimData *data = &m203_objWorkTbl[obj->work[1] + 6];
    f32 angle;

    switch (m203_phase) {
        case 0:
        case 1:
        case 2:
            angle = m203_AngleAdd(obj->rot.y, 180.0f);
            data->unk44.x = sindf(angle) * 80.0f + obj->trans.x;
            data->unk44.z = cosdf(angle) * 80.0f + obj->trans.z;
            Hu3DModelPosSet(obj->model[1], data->unk44.x, obj->trans.y, data->unk44.z);
            break;
        case 3:
        case 4:
            if (m203_teamBss.unk03[obj->work[1]] == 0) {
                m203_MotSet(obj, 5, 2);
                Hu3DMotionSpeedSet(obj->model[0], 1.0f);
                angle = m203_AngleAdd(obj->rot.y, 180.0f);
                obj->trans.x = sindf(angle) * 80.0f + obj->trans.x;
                obj->trans.z = cosdf(angle) * 80.0f + obj->trans.z;
                Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
                if (m203_aimHitBits == 7) {
                    m203_teamBss.unk03[obj->work[1]] = 1;
                } else {
                    m203_teamBss.unk03[obj->work[1]] = 2;
                }
            }
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
            if (obj->trans.x > m203_operatorXTbl[obj->work[1]] + 3.0f) {
                obj->trans.x -= 4.0f;
            } else if (obj->trans.x < m203_operatorXTbl[obj->work[1]] - 3.0f) {
                obj->trans.x += 4.0f;
            }
            if (obj->trans.z < 690.0f) {
                obj->trans.z += 4.0f;
            }
            if (m203_FrontTurn(obj) == 0 && data->unk16 == 0) {
                m203_MotSet(obj, 6, 2);
                data->unk16 = 1;
            }
            break;
        case 6:
            if (m203_phase == 6 && m203_teamBss.unk03[obj->work[1]] == 1) {
                m203_MotSet(obj, 3, 0);
                HuAudCharVoicePlay((m203_voiceChrTbl[chr] << 16) | 0x2F);
                m203_teamBss.unk03[obj->work[1]] = 10;
            }
            break;
        case 5:
            if (m203_teamBss.unk03[obj->work[1]] == 2) {
                m203_MotSet(obj, 4, 0);
                m203_teamBss.unk03[obj->work[1]] = 10;
            }
            break;
        case 7:
            break;
    }
}

void m203_OperatorObjInit(omObjData *obj) {
    s32 temp = (s8)obj->work[1];
    s8 index = temp;
    u16 chr = GwPlayer[obj->work[0]].chr;
    f32 unused[2]; // Unused stack space retained from the original function.

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharMotTbl[chr][0], 0x2B9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0x5C));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x5B));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x5A));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x2F));
    m203_MotSet(obj, 0, 2);
    Hu3DMotionSpeedSet(obj->model[0], 0);
    obj->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0, 0, 0);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);

    switch (m203_slotOrderTbl[m203_slotOrderNo][temp]) {
        case 0:
            obj->trans.x = -360.0f;
            break;
        case 1:
            obj->trans.x = 0.0f;
            break;
        case 2:
            obj->trans.x = 360.0f;
            break;
    }

    m203_operatorXTbl[index] = obj->trans.x;
    obj->trans.y = 0.0f;
    obj->trans.z = 580.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->rot.x = obj->rot.z = 0.0f;
    obj->rot.y = 180.0f;
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    m203_teamBss.unk03[index] = 0;
    obj->func = m203_OperatorObjMain;
}

void m203_OperatorObjCreate(void) {
    u16 playerIndex = 0;
    s32 count = 0;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            SpotlightSwimData *data;
            omObjData *obj;

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
            data = &m203_objWorkTbl[6 + count];
            obj = omAddObj(0x384, 8, 7, -1, m203_OperatorObjInit);
            obj->work[0] = playerIndex;
            data->obj = obj;
            obj->work[1] = data->unk04 = count;
            count++;
        }
    }
}

void m203_LampObjMain(omObjData *obj) {
    s8 idx = obj->work[0];
    SpotlightSwimData *data = &m203_objWorkTbl[obj->work[0] + 9];
    SpotlightSwimData *data3 = &m203_objWorkTbl[obj->work[0] + 3];
    omObjData *obj3 = data3->obj;
    SpotlightSwimData *data6 = &m203_objWorkTbl[obj->work[0] + 6];
    omObjData *obj6 = data6->obj;
    s16 dx, dz, dist;
    s8 motion;

    if (m203_phase < 3) {
        dx = data->unk44.x - obj3->trans.x;
        dz = 200.0f - obj3->trans.y;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 100) {
            motion = 0;
        } else if (dist < 150) {
            motion = 1;
        } else {
            motion = 2;
        }

        obj->rot.y = m203_AngleAdd(
            atan2df(data3->obj->trans.x - data->unk44.x, data3->obj->trans.y - 200.0f), 0.0f);
        obj6->rot.y = obj->rot.y;
        data->unk50.x = m203_AngleAdd(atan2df(dist, 60.0f), 0.0f);
        data->unk50.x = m203_AngleAdd(80.0f, -data->unk50.x);

        if (m203_lampStateTbl[idx].unk04 != motion) {
            m203_lampStateTbl[idx].unk04 = motion;
            m203_MotShiftSet(obj6, motion, 0, 5, 2);
            Hu3DMotionSpeedSet(obj6->model[0], 0.5f);
        }

        if (m203_lampStateTbl[idx].unk00 != obj->rot.y) {
            m203_lampStateTbl[idx].unk00 = obj->rot.y;
            Hu3DMotionSpeedSet(obj6->model[0], 0.5f);
        } else {
            Hu3DMotionSpeedSet(obj6->model[0], 0.0f);
            m203_MotShiftSet(obj6, m203_lampStateTbl[idx].unk04, 0, 10, 2);
        }

        Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
        Hu3DModelRotSet(obj->model[1], data->unk50.x, obj->rot.y, obj->rot.z);
        Hu3DModelRotSet(obj6->model[0], obj6->rot.x, obj6->rot.y, obj6->rot.z);
    }
}

void m203_LampObjInit(omObjData *obj) {
    void *file1;
    void *file2;
    s8 idx = obj->work[0];
    SpotlightSwimData *data = &m203_objWorkTbl[idx + 9];

    switch (m203_slotOrderTbl[m203_slotOrderNo][idx]) {
        case 0:
            obj->trans.x = -360.0f;
            data->unk44.x = 80.0f;
            break;
        case 1:
            obj->trans.x = 0.0f;
            data->unk44.x = 160.0f;
            break;
        case 2:
            obj->trans.x = 360.0f;
            data->unk44.x = 240.0f;
            break;
    }

    obj->trans.y = 0.0f;
    data->unk44.y = 87.5f;
    obj->trans.z = 580.0f;
    data->unk50.x = 35.0f;
    obj->rot.x = obj->rot.z = 0.0f;
    data->unk50.y = obj->rot.y = 180.0f;

    obj->model[0] = Hu3DModelRead(0x240002, 0xA9);
    file1 = DataRead(m203_lampAnimTbl[idx] | 0x240000);
    Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, file1, 0, "m203_001_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    DataClose(file1);

    obj->model[1] = Hu3DModelRead(0x240003, 0x89);
    file2 = DataRead(m203_lampBodyAnimTbl[idx] | 0x240000);
    Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, file2, 0, "light_boddy_DEF");
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    DataClose(file2);

    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[0], obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, data->unk44.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, data->unk50.z);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    m203_lampStateTbl[idx].unk00 = 0.0f;
    m203_lampStateTbl[idx].unk04 = 0;
    obj->func = m203_LampObjMain;
}

void m203_LampObjCreate(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        SpotlightSwimData *data = &m203_objWorkTbl[9 + i];

        data->obj = omAddObj(0x3E8, 5, 5, -1, m203_LampObjInit);
        data->obj->work[0] = i;
    }
}

void m203_ResultObjMain(omObjData *obj) {
    s16 idx = 13;
    SpotlightSwimData *data = &m203_objWorkTbl[idx];

    if (m203_phase == 5) {
        m203_objWorkTbl[idx].unk04 = 1;
    } else if (m203_aimHitBits == 7) {
        data->unk04 = 2;
    }

    if (data->unk04 == 1) {
        if (obj->trans.y == 920.0f) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj->trans.x = m203_swimmerObj->trans.x;
            obj->trans.z = m203_swimmerObj->trans.z;
            data->unk06 = (obj->trans.x > 0.0f) ? 0 : 1;
            data->unk18 = 20.0f;
        }
        switch (data->unk08) {
            case 0:
                if (++data->unk0A >= 30) {
                    data->unk08 = 1;
                    data->unk0A = 0;
                    HuAudFXPlay(0x319);
                }
                break;
            case 1:
                data->unk0A++;
                if (obj->trans.y >= 340.0f) {
                    obj->trans.y -= data->unk18;
                } else if (obj->trans.y >= 140.0f) {
                    data->unk18 -= 1.0f;
                    obj->trans.y -= data->unk18;
                } else {
                    obj->trans.y = 140.0f;
                    data->unk0A = 0;
                    data->unk08 = 2;
                    data->unk18 = 0.0f;
                    if (m203_swimmerObj->work[1] == 4 || m203_swimmerObj->work[1] == 5) {
                        m203_MotShiftSet(m203_swimmerObj, 7, 15, 15, 1);
                    } else {
                        m203_MotShiftSet(m203_swimmerObj, 7, 0, 15, 0);
                    }
                    m203_swimmerMotNo = 7;
                }
                break;
            case 2:
                if (++data->unk0A >= 10) {
                    data->unk08 = 3;
                }
                break;
            case 3:
                obj->trans.y += data->unk18;
                m203_swimmerState.unk10 += data->unk18;
                if (data->unk06 != 0) {
                    obj->rot.y = m203_AngleAdd(obj->rot.y, 1.0f);
                    m203_swimmerObj->rot.y = m203_AngleAdd(m203_swimmerObj->rot.y, 1.0f);
                } else {
                    obj->rot.y = m203_AngleAdd(obj->rot.y, -1.0f);
                    m203_swimmerObj->rot.y = m203_AngleAdd(m203_swimmerObj->rot.y, -1.0f);
                }
                if (obj->trans.y <= 245.0f) {
                    data->unk18 += 2.0f;
                } else if (obj->trans.y >= 355.0f) {
                    data->unk18 -= 2.0f;
                }
                if (obj->trans.y >= 460.0f) {
                    data->unk08 = 4;
                    data->unk18 = 0.0f;
                    data->unk0A = 0;
                }
                break;
            case 4:
                if (data->unk06 != 0) {
                    obj->trans.x += data->unk1C;
                    m203_swimmerObj->trans.x += data->unk1C;
                } else {
                    obj->trans.x -= data->unk1C;
                    m203_swimmerObj->trans.x -= data->unk1C;
                }
                obj->trans.z += data->unk20;
                m203_swimmerObj->trans.z += data->unk20;
                obj->trans.y += data->unk18;
                m203_swimmerState.unk10 += data->unk18;
                data->unk18 += 0.2;
                if (++data->unk0A < 31) {
                    data->unk1C += 0.5f;
                    data->unk20 += 1.8f;
                }
                if (obj->trans.z > 1400.0f) {
                    data->unk08 = 5;
                }
                break;
        }
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    }

    if (data->unk04 == 2) {
        switch (data->unk08) {
            case 0:
                Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                data->unk44.x = m203_swimmerObj->trans.x;
                data->unk44.z = m203_swimmerObj->trans.z;
                m203_wakePosTbl[0].x = data->unk44.x;
                m203_wakePosTbl[0].z = data->unk44.z + 95.0f;
                m203_wakePosTbl[1].x = data->unk44.x + 85.0f;
                m203_wakePosTbl[1].z = data->unk44.z + 55.0f;
                m203_wakePosTbl[2].x = data->unk44.x - 85.0f;
                m203_wakePosTbl[2].z = data->unk44.z + 55.0f;
                data->unk08 = 1;
                break;
            case 1:
                CRotM[0].x += 0.6f;
                if (++data->unk0A >= 20) {
                    data->unk08 = 2;
                    data->unk0A = 0;
                }
                break;
            case 2:
                data->unk44.y -= data->unk18;
                data->unk18 += 3.5f;
                if (data->unk44.y < -260.0f) {
                    data->unk44.y = -260.0f;
                    data->unk08 = 3;
                    Hu3DMotionTimeSet(m203_swimmerObj->model[1], 0);
                    Hu3DModelScaleSet(m203_swimmerObj->model[1], 0.8f, 1.2f, 1.0f);
                    Hu3DModelRotSet(m203_swimmerObj->model[1], 0.0f, 0.0f, 0.0f);
                    Hu3DMotionTimeSet(m203_swimmerObj->model[2], 0);
                    Hu3DModelScaleSet(m203_swimmerObj->model[2], 0.8f, 1.2f, 1.0f);
                    Hu3DModelRotSet(m203_swimmerObj->model[2], 0.0f, 50.0f, 0.0f);
                    Hu3DMotionTimeSet(m203_swimmerObj->model[3], 0);
                    Hu3DModelScaleSet(m203_swimmerObj->model[3], 0.8f, 1.2f, 1.0f);
                    Hu3DModelRotSet(m203_swimmerObj->model[3], 0.0f, 310.0f, 0.0f);
                    HuAudFXPlay(0x315);
                    m203_rippleStartF = 1;
                    if (!(GwPlayer[m203_swimmerObj->work[0]].stat & 1)) {
                        omVibrate(m203_swimmerObj->work[0], 2, 2, 20);
                    }
                }
                break;
            case 3:
                data->unk44.y += 1.0f;
                if (data->unk44.y >= -220.0f) {
                    data->unk44.y = -220.0f;
                    data->unk08 = 5;
                }
                break;
        }
        Hu3DModelPosSet(m203_swimmerObj->model[1], m203_wakePosTbl[0].x, -230.0f, m203_wakePosTbl[0].z);
        Hu3DModelPosSet(m203_swimmerObj->model[2], m203_wakePosTbl[1].x, -230.0f, m203_wakePosTbl[1].z);
        Hu3DModelPosSet(m203_swimmerObj->model[3], m203_wakePosTbl[2].x, -230.0f, m203_wakePosTbl[2].z);
        Hu3DModelPosSet(obj->model[2], data->unk44.x, data->unk44.y, data->unk44.z);
    }

    m203_swimmerObj->trans.y = m203_swimmerState.unk10 + -200.0f +
                                         m203_swimmerOfsYTbl[m203_swimmerObj->work[1]][m203_swimmerMotNo];
    m203_RippleUpdate(m203_swimmerObj);
}

void m203_ResultObjInit(omObjData *obj) {
    SpotlightSwimData *data;
    HmfData *hmf;
    s16 node;
    s16 i;

    data = &m203_objWorkTbl[13];
    obj->model[0] = Hu3DModelRead(0xA0089, 0x2B9);
    hmf = Hu3DData[obj->model[0]].hmf;
    node = SearchObjectIndex(hmf, "c205_000-sao");
    for (i = 0; i < hmf->unk10; i++) {
        if (i == node) {
            hmf->unk60[i].unk24 |= 1;
        }
    }
    obj->model[1] = Hu3DModelRead(0x240005, 0x299);
    obj->model[2] = Hu3DModelRead(0x240004, 0x299);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[2], HU3D_CAM0);
    obj->trans.x = 0.0f;
    obj->trans.y = 920.0f;
    obj->trans.z = 0.0f;
    data->unk44.x = 0.0f;
    data->unk44.y = 920.0f;
    data->unk44.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], data->unk44.x, data->unk44.y, data->unk44.z);
    obj->func = m203_ResultObjMain;
}

void m203_ResultObjCreate(void) {
    m203_objWorkTbl[13].obj = omAddObj(0x514, 5, 5, -1, m203_ResultObjInit);
}

void m203_DarkDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *gdl = *gfx;
    s32 y;
    s32 stripHeight;

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, G_SHADE | G_SHADING_SMOOTH | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN |
                                    G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPSetGeometryMode(gdl++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(gdl++, G_TP_NONE);
    gDPSetTextureFilter(gdl++, G_TF_BILERP);
    gDPSetRenderMode(gdl++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode(gdl++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTextureLUT(gdl++, G_TT_NONE);

    for (y = 0, stripHeight = 4; y < 240; y += stripHeight) {
        gDPLoadTextureTile(gdl++, m203_darkBufTbl[m203_darkBufNo], G_IM_FMT_RGBA, G_IM_SIZ_32b, 160,
                           120, 0, y / 2, 159, (y + stripHeight) / 2 - 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gdl++, G_TX_RENDERTILE, 0, 0, 159 << 2, (stripHeight / 2 - 1) << 2);
        gSPTextureRectangle(gdl++, 0, y << 2, 320 << 2, (y + stripHeight) << 2, G_TX_RENDERTILE, 0, 0, 0x200, 0x200);
    }
    *gfx = gdl;
}

void m203_DarkBufClear(void) {
    u32 i;
    u32 *ptr = m203_darkBufTbl[m203_darkBufNo];

    for (i = 0; i < 0x35C0; i++) {
        *ptr = m203_darkAlpha | m203_darkRgb;
        ptr++;
    }
}

s8 m203_DarkBufFade(void) {
    u32 i;
    u32 *ptr = m203_darkBufTbl[m203_darkBufNo];

    for (i = 0; i < 0x4B00; i++) {
        *ptr = m203_darkAlpha | m203_darkRgb;
        ptr++;
    }

    if (m203_darkAlpha >= 8) {
        m203_darkAlpha -= 8;
        return 0;
    }

    m203_darkAlpha = 0;
    return 1;
}

void m203_DarkLightAdd(s32 x, s32 y, u32 r, u32 g, u32 b) {
    u32 *buf = m203_darkBufTbl[m203_darkBufNo];
    s32 col;
    s32 row;
    s32 i;
    s32 j;
    s32 offset;
    u8 value;
    u32 pixel;
    u32 scale;
    u32 red;
    u32 green;
    u32 blue;
    u32 addRed;
    u32 addGreen;
    u32 addBlue;
    u32 alpha;
    s32 xEnd;
    s32 yEnd;

    x /= 2;
    y /= 2;
    xEnd = x + 32;
    yEnd = y + 32;
    for (row = y, i = 0; row < yEnd; row++, i++) {
        offset = row * 160;
        for (col = x, j = 0; col < xEnd; col++, j++) {
            value = m203_lightShapeTbl[i][j];
            if (value == 15) {
                continue;
            }
            pixel = *(buf + col + offset);
            red = pixel >> 24;
            green = (pixel >> 16) & 0xFF;
            scale = 256 - (value << 4);
            addRed = (r * scale) >> 8;
            addGreen = (g * scale) >> 8;
            addBlue = (b * scale) >> 8;
            red = (red + addRed) & 0xFF;
            green = (green + addGreen) & 0xFF;
            blue = addBlue & 0xFF;
            if (red + green + blue == 765) {
                *(buf + col + offset) = 0;
                continue;
            }
            alpha = (765 - (red + green + blue)) * m203_darkAlpha / 765;
            *(buf + col + offset) = (red << 24) + (green << 16) + (blue << 8) + alpha;
        }
    }
}

void m203_DarkHaloSet(u32 *buf, s32 x, s32 y) {
    s32 col;
    s32 row;
    s32 i;
    s32 j;
    s32 offset;
    u32 value;

    x /= 2;
    y /= 2;
    for (row = y, i = 0; row < y + 32; row++, i++) {
        offset = row * 160;
        for (col = x, j = 0; col < x + 32; col++, j++) {
            value = m203_lightShapeTbl[i][j] << 4;
            if (value > m203_darkAlpha) {
                value = m203_darkAlpha;
            }
            *(buf + col + offset) = value + m203_darkRgb;
        }
    }
}

void m203_DarkObjMain(omObjData *obj) {
    SpotlightSwimData *data;
    SpotlightSwimLight *light;
    s32 i;

    m203_darkBufNo = (m203_darkBufNo + 1) % 3;
    if (m203_phase >= 3) {
        if (m203_DarkBufFade() == 0) {
            for (i = 0; i < 3; i++) {
                m203_DarkHaloSet(m203_darkBufTbl[m203_darkBufNo],
                                             m203_haloXTbl[i], 0xAA);
                light = &m203_lightTbl[i];
                m203_DarkLightAdd(light->x, light->y, light->r, light->g, light->b);
            }
        }
    } else {
        m203_DarkBufClear();
        for (i = 0; i < 3; i++) {
            data = &m203_objWorkTbl[3 + i];
            light = &m203_lightTbl[i];
            light->x = data->obj->trans.x - 32.0f;
            light->y = data->obj->trans.y - 32.0f;
            m203_DarkLightAdd(light->x, light->y, light->r, light->g, light->b);
        }
    }
}

void m203_DarkObjInit(omObjData *obj) {
    s32 i;
    s32 j;

    m203_darkBufNo = 0;
    obj->model[0] = Hu3DHookFuncCreate(0, m203_DarkDraw, 2);
    Hu3DModelCameraSet(obj->model[0], HU3D_CAM0);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    for (i = 0; i < 3; i++) {
        m203_darkBufTbl[i] = HuMemAllocTag(0x12C00, TAG_OVERLAY);
        for (j = 0; j < 0x4B00; j++) {
            m203_darkBufTbl[i][j] = m203_darkRgb | 0x98;
        }
        for (j = 0; j < 3; j++) {
            m203_DarkHaloSet(m203_darkBufTbl[i], m203_haloXTbl[j], 0xAA);
        }
    }
    for (i = 0; i < 3; i++) {
        m203_lightTbl[i].r = 0;
        m203_lightTbl[i].g = 0;
        m203_lightTbl[i].b = 0;
    }
    for (i = 3; i < 6; i++) {
        m203_lightTbl[i].r = 0xFF;
        m203_lightTbl[i].g = 0xFF;
        m203_lightTbl[i].b = 0xFF;
    }
    m203_lightTbl[0].r = 0xFF;
    m203_lightTbl[1].g = 0xFF;
    m203_lightTbl[2].b = 0xFF;
    obj->func = m203_DarkObjMain;
}

void m203_DarkObjCreate(void) {
    omObjData *obj = omAddObj(0x44C, 1, 0, -1, m203_DarkObjInit);
    obj->work[0] = 0;
    m203_objWorkTbl[12].obj = obj;
}

void m203_CameraViewInit(void) {
    u32 i;

    for (i = 0; i < 1; i++) {
        CZoomM[i] = 2241.8f;
        CRotM[i].x = 314.3f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = -195.0f;
        CenterM[i].z = 40.0f;
    }
}

void m203_ExitObjMain(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m203_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m203_ExitObjMain;
    }
}

void m203_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        obj->func = m203_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m203_MainObjMain(omObjData *obj) {
    switch (m203_phase) {
        case 0:
            GMesCreate(GMES_MES_4);
            m203_phase = 1;
            m203_mainTimer = 0;
            break;
        case 1:
            if (GMesStatGet() == 0) {
                m203_phase = 2;
                GMesCreate(GMES_MES_TIMER, 30, 160, 28);
                m203_timer = 901;
            }
            if (++m203_mainTimer == 33) {
                HuAudSeqPlay(0x35);
            }
            break;
        case 2:
            if (m203_timer > 0) {
                m203_timer--;
                GMesTimerValueSet((m203_timer + 29) / 30);
                if (m203_aimHitBits != 7) {
                    break;
                }
                m203_phase = 3;
                m203_timer = 0;
            } else {
                m203_phase = 3;
            }
            GMesTimerEnd();
            GMesCreate(GMES_MES_15);
            HuAudSeqFadeOut(120);
            break;
        case 3:
            if (GMesStatGet() == 0) {
                m203_phase = 4;
                m203_timer = 0;
            }
            break;
        case 4:
            if (++m203_timer >= 15) {
                if (m203_aimHitBits == 7) {
                    m203_phase = 6;
                } else {
                    m203_phase = 5;
                }
            }
            break;
        case 6:
            GMesCreate(GMES_MES_MG_WINNERS_3, m203_teamChrTbl[0], m203_teamChrTbl[1], m203_teamChrTbl[2]);
            GwPlayer[m203_teamBss.unk00[0]].bonusCoin = 10;
            GwPlayer[m203_teamBss.unk00[1]].bonusCoin = 10;
            GwPlayer[m203_teamBss.unk00[2]].bonusCoin = 10;
            HuAudSeqPlay(0x66);
            m203_timer = 15;
            m203_phase = 7;
            break;
        case 5:
            GMesCreate(GMES_MES_MG_WINNER, m203_swimmerChr);
            GwPlayer[m203_swimmerPlayerNo].bonusCoin = 10;
            HuAudSeqPlay(0x65);
            m203_timer = 35;
            m203_phase = 7;
            break;
        case 7:
            if (GMesStatGet() == 0) {
                if (--m203_timer <= 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    obj->func = m203_ExitWaitObjMain;
                }
            }
            break;
    }
}

void m203_MainObjInit(omObjData *obj) {
    s8 i;

    m203_phase = 0;
    m203_timer = 0;
    for (i = 0; i < 8; i++) {
        m203_seNoTbl[i] = -1;
    }
    m203_aimPadNo = 0;
    m203_slotOrderNo = m203_RandGet(6);
    m203_darkAlpha = 0x98;
    m203_darkRgb = 0x2000;
    m203_CameraViewInit();
    m203_StageObjCreate();
    m203_WaterObjCreate();
    m203_SwimmerObjCreate();
    m203_AimObjCreate();
    m203_OperatorObjCreate();
    m203_LampObjCreate();
    m203_DarkObjCreate();
    m203_ResultObjCreate();
    m203_BubbleObjCreate();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    obj->func = m203_MainObjMain;
}

void m203_Dummy(void) {
}

void m203_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m203_cameraViewTbl[i].scissorX, m203_cameraViewTbl[i].scissorY,
                   m203_cameraViewTbl[i].scissorWidth, m203_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m203_cameraViewTbl[i].viewportScale.x, m203_cameraViewTbl[i].viewportScale.y,
                    m203_cameraViewTbl[i].viewportScale.z, m203_cameraViewTbl[i].viewportTranslate.x,
                    m203_cameraViewTbl[i].viewportTranslate.y, m203_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m203_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m203_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    m203_CameraInit();
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
    GMesFontMesCreate(m203_fontMesTbl, 0);
    GMesFontMesCreate(m203_fontMesTbl, 1);
    omAddObj(0x5DC, 0, 0, -1, m203_MainObjInit);
    omAddObj(0x5DC, 0, 0, -1, m203_ExitCheckObjMain);
    m203_ObjWorkInit();
}

// Keep this table after the functions to preserve the original rodata order.
const s16 m203_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
