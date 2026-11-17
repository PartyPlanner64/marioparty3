#include "common.h"
#include "game/overlays/minigame.h"

typedef struct PumpPumpAwayObjWork {
    /* 0x00 */ s32 unk_00;
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
} PumpPumpAwayObjWork; // sizeof 0x84

typedef struct PumpPumpAwayPump {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C; // 0x0A is also read as an s16 elsewhere
} PumpPumpAwayPump;         // sizeof 0x10

typedef struct PumpPumpAwayLakitu {
    s32 unk_00;
    s32 unk_04;
    f32 unk_08;
    s32 unk_0C;
} PumpPumpAwayLakitu; // sizeof 0x10

typedef struct PumpPumpAwayLaunchEff {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04; // 0x07 is also read as a u8 elsewhere
} PumpPumpAwayLaunchEff;    // sizeof 0x8

typedef struct PumpPumpAwayHose {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} PumpPumpAwayHose; // sizeof 0x10

typedef struct PumpPumpAwayMidFlyer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 hidden;
    /* 0x08 */ s32 direction;
    /* 0x0C */ f32 speed;
} PumpPumpAwayMidFlyer; // sizeof 0x10

typedef struct PumpPumpAwaySmoke {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ omObjData *unk_0C;
} PumpPumpAwaySmoke; // sizeof 0x10

typedef struct PumpPumpAwayLowFlyer {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} PumpPumpAwayLowFlyer; // sizeof 0x14

typedef struct PumpPumpAwaySway {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
} PumpPumpAwaySway; // sizeof 0xC

typedef struct PumpPumpAwayPumper {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ omObjData *unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
} PumpPumpAwayPumper; // sizeof 0x38

typedef struct PumpPumpAwayHud {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04; // 0x06 is also read as an s16 elsewhere
    /* 0x08 */ s32 unk_08; // 0x0A is also read as an s16 elsewhere
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10[8];
    /* 0x30 */ s32 unk_30;
} PumpPumpAwayHud; // sizeof 0x34

typedef struct PumpPumpAwayRocket {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
} PumpPumpAwayRocket; // sizeof 0x34

typedef struct PumpPumpAwayParachute {
    s32 state;
    s32 player;
    f32 angle;
} PumpPumpAwayParachute; // sizeof 0xC

typedef struct PumpPumpAwayCover {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 spriteId; // 0x06 is also read as an s16
    /* 0x08 */ s32 modelId;  // 0x0A is also read as an s16
    /* 0x0C */ HuSprAnimData *sprite;
    /* 0x10 */ s32 alpha;
    /* 0x14 */ s32 timer;
} PumpPumpAwayCover; // sizeof 0x18

typedef struct PumpPumpAwayRecord {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 spriteData;
    /* 0x06 */ s16 espriteData;
    /* 0x08 */ s16 group;
    /* 0x0A */ s16 esprite;
    /* 0x0C */ s32 digits[4];
    /* 0x1C */ u16 record;
    /* 0x1E */ s16 unk_1E;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s32 unk_24;
} PumpPumpAwayRecord; // sizeof 0x28

typedef struct PumpPumpAwayCamera {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} PumpPumpAwayCamera; // sizeof 0x2C

typedef struct PumpPumpAwayRecordMarker {
    /* 0x00 */ s32 state;
    /* 0x04 */ u16 record;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s32 hidden;
} PumpPumpAwayRecordMarker; // sizeof 0xC

typedef struct PumpPumpAwaySkyColor {
    s32 red;
    s32 green;
    s32 blue;
} PumpPumpAwaySkyColor;

extern u8 Hu3DBufNo;
extern u8 omAllPauseF;
extern s32 omCharModelNoTbl[][6];
extern const s16 m213_fontMesTbl[];

Vec m213_playerPosTbl[] = {
    { -295.0f, 10.0f, 600.0f },
    { -135.0f, 10.0f, 600.0f },
    { 135.0f, 10.0f, 600.0f },
    { 295.0f, 10.0f, 600.0f }
};

Vec m213_rocketPosTbl[] = {
    { -215.0f, 200.0f, 0.0f },
    { 215.0f, 200.0f, 0.0f }
};

PumpPumpAwaySkyColor m213_skyColorTbl[15] = {
    { 200, 230, 255 },
    { 20, 150, 255 },
    { 135, 225, 255 },
    { 65, 170, 250 },
    { 20, 100, 220 },
    { 10, 60, 170 },
    { 10, 40, 130 },
    { 10, 30, 110 },
    { 15, 25, 100 },
    { 15, 25, 90 },
    { 15, 25, 90 },
    { 15, 25, 90 },
    { 15, 25, 90 },
    { 15, 25, 90 },
    { 15, 25, 90 }
};

Vec m213_pumpPosTbl[] = {
    { -295.0f, 10.0f, 600.0f },
    { -135.0f, 10.0f, 600.0f },
    { 135.0f, 10.0f, 600.0f },
    { 295.0f, 10.0f, 600.0f }
};

f32 m213_pumpMotSpeedTbl[] = {
    0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f,
    1.3f, 1.4f
};

Vec m213_hosePosTbl[] = {
    { -215.0f, 0.0f, 0.0f },
    { 215.0f, 0.0f, 0.0f }
};

u16 m213_hudLabelPosTbl[][2] = {
    { 23, 208 },
    { 238, 208 }
};

u16 m213_hudDigitPosTbl[][2] = {
    { 29, 211 },
    { 29, 211 },
    { 38, 211 },
    { 47, 211 },
    { 244, 211 },
    { 244, 211 },
    { 253, 211 },
    { 262, 211 }
};

Vec m213_launchEffPosTbl[] = {
    { -215.0f, 0.0f, 0.0f },
    { 215.0f, 0.0f, 0.0f }
};

f32 m213_lowFlyerYTbl[] = { 1500.0f, 1750.0f, 2250.0f, 2500.0f };

f32 m213_midFlyerYTbl[] = { 2750.0f, 3250.0f, 3500.0f, 3750.0f };

f32 m213_highFlyerYTbl[] = {
    4200.0f, 4400.0f, 4600.0f, 4800.0f, 5200.0f, 5400.0f, 5600.0f, 5800.0f,
    6200.0f, 6400.0f, 6600.0f, 6800.0f, 7200.0f, 7400.0f, 7600.0f, 7800.0f,
    8200.0f, 8400.0f, 8600.0f, 8800.0f, 9200.0f, 9400.0f, 9600.0f, 9800.0f
};

f32 m213_cloudYTbl[] = {
    1250.0f, 1500.0f, 1750.0f, 2250.0f, 2500.0f, 2750.0f, 3250.0f, 3500.0f,
    3750.0f, 4250.0f, 4500.0f, 4750.0f, 5250.0f, 5500.0f, 5750.0f, 6250.0f,
    6500.0f, 6750.0f, 7250.0f, 7500.0f, 7750.0f, 8250.0f, 8500.0f, 8750.0f,
    9250.0f, 9500.0f, 9750.0f
};
s16 m213_parachuteSwingDir = 0;
s16 m213_parachuteSeF = 0;
s16 m213_fallDelay = 18;
s16 m213_parachuteOpenF = 0;
s32 m213_fallSeF = 0;
u16 m213_cameraSetF = 0;
s32 m213_musicTimer = 0;

PumpPumpAwayCamera m213_cameraViewTbl[1] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 20.0f },
};

f32 m213_skyScrollRate BSS;
f32 m213_skyScroll BSS;
u8 m213_lakituAnimNo BSS;
s16 m213_lakituMdl BSS;
s16 m213_lowFlyerMdl BSS;
s16 m213_midFlyerMdl BSS;
s16 m213_highFlyerMdl BSS;
s16 m213_cloudMdl BSS;
s32 m213_phase BSS;
s32 m213_phaseStep BSS;
s32 m213_phaseTimer BSS;
s32 m213_team0SlotCnt BSS;
s32 m213_team1SlotCnt BSS;
s32 m213_turnDelay BSS;
u8 m213_turnDelayPad[4] BSS; /* Unreferenced. */
PumpPumpAwaySway m213_highFlyerTbl[6] BSS;
PumpPumpAwayHud m213_hudTbl[2] BSS;
PumpPumpAwayHose m213_hoseTbl[2] BSS;
PumpPumpAwaySmoke m213_smokeTbl[20] BSS;
PumpPumpAwayLowFlyer m213_lowFlyerTbl[4] BSS;
s32 m213_highFlyerCnt BSS;
u8 m213_highFlyerCntPad[4] BSS; /* Unreferenced. */
PumpPumpAwayRocket m213_rocketTbl[2] BSS;
u8 m213_rocketTblPad[4] BSS; /* Unreferenced. */
s32 m213_launchVibF BSS;
PumpPumpAwaySway m213_cloudTbl[6] BSS;
PumpPumpAwayObjWork m213_objWorkTbl[50] BSS;
s32 m213_cloudCnt BSS;
u8 m213_cloudCntPad[4] BSS; /* Unreferenced. */
PumpPumpAwayLaunchEff m213_launchEffTbl[3] BSS;
PumpPumpAwayLakitu m213_lakituTbl[2] BSS;
PumpPumpAwayPumper m213_pumperTbl[4] BSS;
PumpPumpAwayParachute m213_parachute BSS;
omObjData *m213_parachuteObj BSS;
s32 m213_pumpAnimB BSS;
s32 m213_pumpAnimA BSS;
PumpPumpAwayCover m213_cover BSS;
u16 m213_skyTexSize[2] BSS;
u8 m213_skyTexSizePad[0x24] BSS; /* Unreferenced. */
PumpPumpAwayPump m213_pumpTbl[2] BSS;
u8 m213_pumpTblPad[0x20] BSS; /* Unreferenced. */
PumpPumpAwayRecord m213_record BSS;
PumpPumpAwayRecordMarker m213_recordMarker BSS;
s32 m213_skyColorNo BSS;
PumpPumpAwayMidFlyer m213_midFlyerTbl[4] BSS;

// Fields of the structs above, accessed through separate symbols
// (see undefined_syms.txt).
extern s32 m213_hudLabelAnimNo; // m213_hudTbl[0].unk_04
extern s16 m213_hudLabelAnimNoLo; // m213_hudTbl[0].unk_04 (low half)
extern s32 m213_hudLabelMdl; // m213_hudTbl[0].unk_08
extern s16 m213_hudLabelMdlLo; // m213_hudTbl[0].unk_08 (low half)
extern HuSprAnimData *m213_hudLabelAnim; // m213_hudTbl[0].unk_0C
extern s32 m213_hudLabelAlpha; // m213_hudTbl[0].unk_30
extern s32 m213_hudDigitAnimNo; // m213_hudTbl[1].unk_04
extern s16 m213_hudDigitAnimNoLo; // m213_hudTbl[1].unk_04 (low half)
extern s32 m213_hudDigitMdl; // m213_hudTbl[1].unk_08
extern s16 m213_hudDigitMdlLo; // m213_hudTbl[1].unk_08 (low half)
extern HuSprAnimData *m213_hudDigitAnim; // m213_hudTbl[1].unk_0C
extern s32 m213_hudDigitAlpha; // m213_hudTbl[1].unk_30
extern f32 m213_rocket0Height; // m213_rocketTbl[0].unk_18
extern s32 m213_parachuteRocketNo; // m213_parachute.player
extern f32 m213_parachuteAngle; // m213_parachute.angle
extern s32 m213_coverAnimNo; // m213_cover.spriteId
extern s16 m213_coverAnimNoLo; // m213_cover.spriteId (low half)
extern s32 m213_coverMdl; // m213_cover.modelId
extern s16 m213_coverMdlLo; // m213_cover.modelId (low half)
extern HuSprAnimData *m213_coverAnim; // m213_cover.sprite
extern s32 m213_coverAlpha; // m213_cover.alpha
extern s32 m213_coverTimer; // m213_cover.timer
extern s16 m213_recordDigitAnim; // m213_record.spriteData
extern s16 m213_recordSprGrp; // m213_record.group
extern s16 m213_recordDigit0Lo; // m213_record.digits[0] (low half)
extern u16 m213_recordValue; // m213_record.record
extern u16 m213_recordMarkerValue; // m213_recordMarker.record
extern s32 m213_recordMarkerHiddenF; // m213_recordMarker.hidden

void m213_SkyObjMain(omObjData *obj);
void m213_PolarCalc(Vec *position, Vec *target, Vec *result);
void m213_GroundObjMain(omObjData *obj);
void m213_GroundObjInit(omObjData *obj);
void m213_NearBackObjMain(omObjData *obj);
void m213_NearBackObjInit(omObjData *obj);
void m213_FarBackObjMain(omObjData *obj);
void m213_FarBackObjInit(omObjData *obj);
void m213_SkyObjInit(omObjData *obj);
void m213_CoverDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m213_CoverObjInit(omObjData *obj);
void m213_PumpAnimUpdate(omObjData *obj);
void m213_PumpObjInit(omObjData *obj);
void m213_HosePumpUpdate(omObjData *obj);
void m213_HoseObjInit(omObjData *obj);
void m213_HudLabelDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m213_HudDigitDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m213_HudObjMain(omObjData *obj);
void m213_HudObjInit(omObjData *obj);
void m213_LaunchEffObjInit(omObjData *obj);
void m213_ParachuteUpdate(omObjData *obj);
void m213_ParachuteObjMain(omObjData *obj);
void m213_ParachuteObjInit(omObjData *obj);
void m213_SmokeObjInit(omObjData *obj);
void m213_RocketFlyUpdate(omObjData *obj);
void m213_RocketLandUpdate(omObjData *obj);
void m213_RocketObjInit(omObjData *obj);
void m213_PlayerObjInit(omObjData *obj);
void m213_RecordObjMain(omObjData *obj);
void m213_RecordObjInit(omObjData *obj);
void m213_RecordMarkerObjMain(omObjData *obj);
void m213_RecordMarkerObjInit(omObjData *obj);
void m213_Lakitu0Update(omObjData *obj);
void m213_Lakitu1Update(omObjData *obj);
void m213_LakituObjInit(omObjData *obj);
void m213_LowFlyerObjMain(omObjData *obj);
void m213_LowFlyerObjInit(omObjData *obj);
void m213_MidFlyerObjMain(omObjData *obj);
void m213_MidFlyerObjInit(omObjData *obj);
void m213_CloudObjMain(omObjData *obj);
void m213_CloudObjInit(omObjData *obj);
void m213_CameraViewObjMain(omObjData *obj);
void m213_SeqResultObjMain(omObjData *obj);
void m213_SeqRecordObjMain(omObjData *obj);
void m213_SeqFinishObjMain(omObjData *obj);
void m213_SeqCoverWaitObjMain(omObjData *obj);
void m213_HighFlyerObjMain(omObjData *obj);
void m213_HighFlyerObjInit(omObjData *obj);
void m213_SeqLaunchObjMain(omObjData *obj);
void m213_RocketPowerCalc(void);
void m213_SeqTimerObjMain(omObjData *obj);
void m213_SeqStartWaitObjMain(omObjData *obj);
void m213_ExitWaitObjMain(omObjData *obj);
void m213_ObjectSetup(void);

void m213_Executor(void) {
    m213_ObjectSetup();
}

Gfx **m213_GfxRectTexInit(Gfx **gfxPos) {
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

Gfx **m213_GfxRectXluInit(Gfx **gfxPos) {
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

Gfx **m213_GfxPrimAlphaSet(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

f32 m213_AngleAdd(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 m213_RandMulGet(u32 arg0) {
    return (rand8() * arg0) >> 8;
}

void m213_ObjWorkInit(void) {
    u32 i;
    PumpPumpAwayObjWork *entry;

    for (i = 0, entry = m213_objWorkTbl; i < 50; i++, entry++) {
        entry->unk_00 = 0;
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
        entry->unk_40 = -1;
        entry->unk_42 = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68 = 0.0f;
        entry->unk_6C = 0.0f;
        entry->unk_70 = 0.0f;
        entry->unk_74 = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void m213_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

f32 m213_ArcTanCalc(f32 value) {
    s32 range;
    s32 i;
    f32 fraction;

    if (value > 1.0f) {
        range = 1;
        value = 1.0f / value;
    } else if (value < -1.0f) {
        range = -1;
        value = 1.0f / value;
    } else {
        range = 0;
    }

    fraction = 0.0f;
    for (i = 6; i > 0; i--) {
        fraction = (i * i * value * value) / (2 * i + 1 + fraction);
    }

    if (fraction != -1.0f) {
        if (range > 0) {
            return 1.5707963267948966 - value / (fraction + 1.0f);
        } else if (range < 0) {
            return -1.5707963267948966 - value / (fraction + 1.0f);
        } else {
            return value / (fraction + 1.0f);
        }
    }
    return 0.0f;
}

void m213_PolarCalc(Vec *position, Vec *target, Vec *result) {
    Vec difference;
    Vec positionCopy;
    Vec targetCopy;
    f32 yaw;
    f32 horizontalDistance;
    f32 pitch;
    f32 distance;

    positionCopy.x = position->x;
    positionCopy.y = position->y;
    positionCopy.z = position->z;
    targetCopy.x = target->x;
    targetCopy.y = target->y;
    targetCopy.z = target->z;
    difference.x = targetCopy.x - positionCopy.x;
    difference.y = targetCopy.y - positionCopy.y;
    difference.z = targetCopy.z - positionCopy.z;
    horizontalDistance = HuSqrtf(difference.x * difference.x + difference.z * difference.z);

    if ((horizontalDistance <= 0.002f) & (horizontalDistance >= -0.002f)) {
        horizontalDistance = 0.0f;
        pitch = (difference.y > 0.0001f || !(difference.y < 0.0001f)) ? 180.0f : horizontalDistance;
        yaw = horizontalDistance;
    } else {
        if (difference.x != 0.0f && difference.z != 0.0f) {
            yaw = m213_ArcTanCalc(difference.x / difference.z) * 57.2957795130823229;
        } else if (difference.z == 0.0f) {
            yaw = difference.x >= 0.0f ? 90.0f : 270.0f;
        } else {
            yaw = 0.0f;
        }
        if (difference.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontalDistance != 0.0f && difference.y != 0.0f) {
            pitch = m213_ArcTanCalc(difference.y / horizontalDistance) * 57.2957795130823229;
        } else {
            pitch = 0.0f;
        }
        yaw = yaw >= 360.0f ? yaw - 360.0f : yaw < 0.0f ? yaw + 360.0f
                                                        : yaw;
        pitch = pitch + 90.0f >= 360.0f ? pitch + 90.0f - 360.0f
                : pitch + 90.0f < 0.0f  ? pitch + 90.0f + 360.0f
                                        : pitch + 90.0f;
    }
    if ((pitch <= 0.002f) & (pitch >= -0.002f)) {
        pitch = 0.0f;
    }
    distance = HuSqrtf(difference.y * difference.y + horizontalDistance * horizontalDistance);
    result->z = yaw;
    result->x = distance;
}

void m213_TextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void m213_GroundObjMain(omObjData *obj) {
    PumpPumpAwayRocket *players;
    PumpPumpAwayRocket *other;
    s32 i;
    f32 scale;

    switch (m213_phase) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 5:
            break;
        case 4:
            players = m213_rocketTbl;
            other = players + 1;
            if (players->unk_18 - other->unk_18 > 0.0f) {
                obj->trans.y -= players->unk_20;
            } else {
                obj->trans.y -= other->unk_20;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 6:
            if (m213_cover.state < 2) {
                break;
            }
        case 7:
            obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
            break;
    }

    for (i = 1; i < 3; i++) {
        players = &m213_rocketTbl[i];
        scale = players[-1].unk_28->trans.y - obj->trans.y - 200.0f;
        if ((scale > 1000.0f) | (scale < -100.0f)) {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(obj->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            scale = 3.0 - scale * 0.003;
            if (scale >= 3.0) {
                scale = 3.0f;
            }
        }
        Hu3DModelPosSet(obj->model[i], m213_rocketPosTbl[i - 1].x,
                        obj->trans.y + 1.0, m213_rocketPosTbl[i - 1].z + 0.0f);
        Hu3DModelScaleSet(obj->model[i], scale, scale, scale);
    }
}

void m213_GroundObjInit(omObjData *obj) {
    s32 i;

    obj->model[0] = Hu3DModelRead(0x2E0000, 0x289);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    for (i = 1; i < 3; i++) {
        obj->model[i] = Hu3DModelRead2(0, 0xC9);
        Hu3DModelObjAttrSet(obj->model[i], 0x80000000, 0);
        Hu3DModelRemakeStatic(obj->model[i]);
        Hu3DModelDynamicFree(obj->model[i]);
        HuTranslateF(Hu3DData[obj->model[i]].mtx, 0.0f, 1.0f, 0.0f);
        Hu3DModelScaleSet(obj->model[i], 3.0f, 3.0f, 3.0f);
        Hu3DModelPosSet(obj->model[i], m213_rocketPosTbl[i - 1].x,
                        obj->trans.y + 1.0, m213_rocketPosTbl[i - 1].z + 0.0f);
    }
    obj->func = m213_GroundObjMain;
}

void m213_GroundObjCreate(void) {
    omAddObj(0xC8, 3, 0, -1, m213_GroundObjInit);
}

void m213_NearBackObjMain(omObjData *obj) {
    PumpPumpAwayRocket *first;
    PumpPumpAwayRocket *player;
    PumpPumpAwayRocket *other;

    switch (m213_phase) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            first = &m213_rocketTbl[0];
            player = m213_rocketTbl;
            other = &player[1];
            if (first->unk_18 - other->unk_18 > 0.0f) {
                obj->trans.y -= first->unk_20 * 0.9;
            } else {
                obj->trans.y -= other->unk_20 * 0.9;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 5:
            break;
        case 6:
            if (m213_cover.state < 2) {
                break;
            }
        case 7:
            obj->trans.x = obj->trans.y = 0.0f;
            obj->trans.z = -1100.0f;
            break;
    }
}

void m213_NearBackObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2E0003, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1100.0f;
    obj->func = m213_NearBackObjMain;
}

void m213_NearBackObjCreate(void) {
    omAddObj(0xFA, 1, 0, -1, m213_NearBackObjInit);
}

void m213_FarBackObjMain(omObjData *obj) {
    PumpPumpAwayRocket *first;
    PumpPumpAwayRocket *player;
    PumpPumpAwayRocket *other;

    switch (m213_phase) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            first = &m213_rocketTbl[0];
            player = m213_rocketTbl;
            other = &player[1];
            if (first->unk_18 - other->unk_18 > 0.0f) {
                obj->trans.y -= first->unk_20 * 0.8;
            } else {
                obj->trans.y -= other->unk_20 * 0.8;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            break;
        case 5:
            break;
        case 6:
            if (m213_cover.state < 2) {
                break;
            }
        case 7:
            obj->trans.x = obj->trans.y = 0.0f;
            obj->trans.z = -1290.0f;
            break;
    }
}

void m213_FarBackObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2E0004, 0x289);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1290.0f;
    obj->func = m213_FarBackObjMain;
}

void m213_FarBackObjCreate(void) {
    omAddObj(0x104, 1, 0, -1, m213_FarBackObjInit);
}

void m213_SkyObjMain(omObjData *obj) {
    HmfData *model = Hu3DData[obj->model[0]].hmf;
    Vtx *vertex = model->unk44[Hu3DBufNo];
    PumpPumpAwayRocket *players;
    PumpPumpAwayRocket *other;
    f32 distance;
    f32 difference;
    f32 fraction;
    s32 meters;
    u32 i;

    switch (m213_phase) {
        case 0:
        case 1:
        case 2:
        case 3:
            i = 0;
            if (i < model->unk18) {
                // A structured loop swaps the object and model pointer registers.
            colorVertex:
                if (i == 1 || i == 2) {
                    vertex->v.cn[0] = m213_skyColorTbl[m213_skyColorNo + 1].red;
                    vertex->v.cn[1] = m213_skyColorTbl[m213_skyColorNo + 1].green;
                    vertex->v.cn[2] = m213_skyColorTbl[m213_skyColorNo + 1].blue;
                } else {
                    vertex->v.cn[0] = m213_skyColorTbl[m213_skyColorNo].red;
                    vertex->v.cn[1] = m213_skyColorTbl[m213_skyColorNo].green;
                    vertex->v.cn[2] = m213_skyColorTbl[m213_skyColorNo].blue;
                }
                vertex++;
                if (++i < model->unk18) {
                    goto colorVertex;
                }
            }
            break;
        case 4:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            players = m213_rocketTbl;
            other = &players[1];
            if (m213_rocket0Height > other->unk_18) {
                distance = m213_rocket0Height;
            } else {
                distance = other->unk_18;
            }
            meters = distance * 0.01;
            m213_skyColorNo = meters * 0.01;
            if (omPauseChk() + omAllPauseF == 0) {
                if (players->unk_18 - other->unk_18 > 0.0f) {
                    m213_skyScrollRate = players->unk_18 * 0.0000125;
                    m213_skyScroll -= players->unk_20 * 0.08;
                } else {
                    m213_skyScrollRate = other->unk_18 * 0.0000125;
                    m213_skyScroll -= other->unk_20 * 0.08;
                }
            }
            for (i = 0; i < model->unk18; i++, vertex++) {
                if (i == 1 || i == 2) {
                    difference = m213_skyColorTbl[m213_skyColorNo + 1].red - m213_skyColorTbl[m213_skyColorNo].red;
                    fraction = (m213_skyColorNo + 1) * 100 - meters;
                    difference *= fraction * 0.01;
                    vertex->v.cn[0] = (u32)(m213_skyColorTbl[m213_skyColorNo + 1].red - difference);
                    difference = m213_skyColorTbl[m213_skyColorNo + 1].green - m213_skyColorTbl[m213_skyColorNo].green;
                    fraction = (m213_skyColorNo + 1) * 100 - meters;
                    difference *= fraction * 0.01;
                    vertex->v.cn[1] = (u32)(m213_skyColorTbl[m213_skyColorNo + 1].green - difference);
                    difference = m213_skyColorTbl[m213_skyColorNo + 1].blue - m213_skyColorTbl[m213_skyColorNo].blue;
                    fraction = (m213_skyColorNo + 1) * 100 - meters;
                    difference *= fraction * 0.01;
                    vertex->v.cn[2] = (u32)(m213_skyColorTbl[m213_skyColorNo + 1].blue - difference);
                } else {
                    difference = m213_skyColorTbl[m213_skyColorNo + 2].red - m213_skyColorTbl[m213_skyColorNo + 1].red;
                    fraction = (m213_skyColorNo + 2) * 100 - (distance + 10000.0f) * 0.01;
                    difference *= fraction * 0.01;
                    vertex->v.cn[0] = (u32)(m213_skyColorTbl[m213_skyColorNo + 2].red - difference);
                    difference = m213_skyColorTbl[m213_skyColorNo + 2].green - m213_skyColorTbl[m213_skyColorNo + 1].green;
                    fraction = (m213_skyColorNo + 2) * 100 - (distance + 10000.0f) * 0.01;
                    difference *= fraction * 0.01;
                    vertex->v.cn[1] = (u32)(m213_skyColorTbl[m213_skyColorNo + 2].green - difference);
                    difference = m213_skyColorTbl[m213_skyColorNo + 2].blue - m213_skyColorTbl[m213_skyColorNo + 1].blue;
                    fraction = (m213_skyColorNo + 2) * 100 - (distance + 10000.0f) * 0.01;
                    difference *= fraction * 0.01;
                    vertex->v.cn[2] = (u32)(m213_skyColorTbl[m213_skyColorNo + 2].blue - difference);
                }
            }
        case 5:
            Hu3DModelObjTexScroll(obj->model[0], m213_skyScroll, m213_skyScroll,
                               m213_skyTexSize[0], m213_skyTexSize[1], "dammy_0-sky_b_2", 0);
            break;
        case 6:
            if (m213_cover.state < 2) {
                break;
            }
        case 7:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
}

void m213_SkyObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2E0001, 0x289);
    obj->model[1] = Hu3DModelRead(0x2E0002, 0x289);
    Hu3DModelObjAttrSet(obj->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelVtxBufMake(obj->model[0]);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DTexSizeGet("m213_back_DEF", m213_skyTexSize);
    obj->trans.x = obj->trans.y = 0.0f;
    obj->trans.z = -1300.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    m213_skyScrollRate = 0.0f;
    m213_skyScroll = 0.0f;
    m213_skyColorNo = 0;
    obj->func = m213_SkyObjMain;
}

void m213_SkyObjCreate(void) {
    omObjData *obj = omAddObj(0x64, 2, 0, -1, m213_SkyObjInit);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m213_CoverDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    PumpPumpAwayCover *fade = &m213_cover;
    Gfx *gfx;
    Gfx *command;
    u32 word;
    s32 x;
    s32 y;

    if (fade->state == -1) {
        return;
    }
    if (m213_coverAlpha < 255) {
        gfxPos = m213_GfxRectXluInit(gfxPos);
        gfxPos = m213_GfxPrimAlphaSet(gfxPos, (u8)m213_coverAlpha);
    } else {
        gfxPos = m213_GfxRectTexInit(gfxPos);
    }
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, fade->sprite->pal);
    for (x = 0; x < 5; x++) {
        for (y = 0; y < 5; y++) {
            gDPLoadTextureTile_4b(gfx++, fade->sprite->data, G_IM_FMT_CI, 64, 16,
                                  0, 0, 64, 48, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 64 << 2, 48 << 2);
            {
                Gfx *rectangle = gfx++;
                rectangle->words.w0 = _SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(((x + 1) * 64 * 4) & 0xFFF, 12, 12) | _SHIFTL(((y + 1) * 48 * 4) & 0xFFF, 0, 12);
                rectangle->words.w1 = _SHIFTL((x * 64 * 4) & 0xFFF, 12, 12) | _SHIFTL((y * 48 * 4) & 0xFFF, 0, 12);
            }
            command = gfx++;
            word = _SHIFTL(G_RDPHALF_1, 24, 8);
            command->words.w0 = word;
            command->words.w1 = 0;
            command = gfx++;
            word = _SHIFTL(G_RDPHALF_2, 24, 8);
            command->words.w0 = word;
            word = _SHIFTL(1024, 16, 16) | _SHIFTL(1024, 0, 16);
            command->words.w1 = word;
        }
    }
    *gfxPos = gfx;
}

void m213_CoverObjMain(omObjData *obj) {
    PumpPumpAwayCover *fade = &m213_cover;

    if (fade->state == -1) {
        return;
    }
    switch (fade->state) {
        case 0:
            fade->alpha = 0;
            break;
        case 1:
            fade->alpha += 26;
            if (fade->alpha >= 256) {
                fade->alpha = 255;
                fade->state = 2;
            }
            break;
        case 2:
            if (fade->timer != 0) {
                fade->timer--;
            } else {
                fade->state = 3;
            }
            break;
        case 3:
            fade->alpha -= 25;
            if (fade->alpha < 30) {
                fade->alpha = 0;
                fade->state = 4;
            }
            break;
        case 4:
            fade->alpha = 0;
            fade->state = -1;
            break;
    }
}

void m213_CoverObjInit(omObjData *obj) {
    m213_coverAnimNo = HuSprAnimDataRead(0x2E001E);
    m213_coverAnim = HuSprAnimDataGet(m213_coverAnimNoLo);
    m213_coverMdl = Hu3DHookFuncCreate(0, m213_CoverDraw, 6);
    Hu3DModelCameraSet(m213_coverMdlLo, HU3D_CAM0);
    m213_coverAlpha = 0;
    m213_cover.state = -1;
    m213_coverTimer = 30;
    obj->func = m213_CoverObjMain;
}

void m213_CoverObjCreate(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0, -1, m213_CoverObjInit);
    obj->work[0] = 0;
}

void m213_PumpSmokeEmit(omObjData *obj) {
    s32 i;
    PumpPumpAwaySmoke *entry;

    for (i = 0; i < 20; i++) {
        entry = &m213_smokeTbl[i];
        if (entry->unk_00 == 0) {
            entry->unk_00 = 1;
            entry->unk_0C->trans.x = obj->trans.x;
            entry->unk_0C->trans.y = obj->trans.y + 50.0f;
            entry->unk_0C->trans.z = obj->trans.z + 50.0f;
            entry->unk_08 = 0;
            break;
        }
    }
}

void m213_PumpAnimUpdate(omObjData *obj) {
    PumpPumpAwayPump *entry = &m213_pumpTbl[obj->work[0]];
    PumpPumpAwayPumper *jet = &m213_pumperTbl[entry->unk_0C];

    Hu3DMotionTimeSet(obj->model[0], Hu3DData[jet->unk_04->model[0]].motTime);
    if (jet->unk_18 != 0 && Hu3DData[obj->model[0]].motTime <= 6.0f) {
        if (entry->unk_04 != 0) {
            entry->unk_04--;
        } else {
            entry->unk_08 ^= 1;
            entry->unk_04 = 1;
            Hu3DAnimTimeSet(obj->work[1], (s16)entry->unk_08);
        }
    } else {
        entry->unk_04 = 0;
        Hu3DAnimTimeSet(obj->work[1], 0);
    }
}

void m213_PumpObjMain(omObjData *obj) {
    PumpPumpAwayPump *entry = &m213_pumpTbl[obj->work[0]];

    if (entry->unk_00 == -1) {
        return;
    }
    switch (m213_phase) {
        case 0:
        case 1:
            break;
        case 2:
            m213_PumpAnimUpdate(obj);
            break;
        case 3:
            if (entry->unk_00 == 0) {
                m213_PumpSmokeEmit(obj);
                entry->unk_00 = 1;
            }
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            break;
        case 4:
            break;
    }
}

void m213_PumpObjInit(omObjData *obj) {
    void *data;
    PumpPumpAwayPump *entry;
    s32 i;
    PumpPumpAwayPumper *jets;

    obj->model[0] = Hu3DModelRead(0x2E0005, 0x2A9);
    omObjMotionRead(obj, 0, 0x2E0006);
    switch (obj->work[0]) {
        case 0:
        case 1:
            if (obj->work[0] == 0) {
                data = DataRead(0x2E0007);
                m213_pumpAnimA = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                obj->work[1] = m213_pumpAnimA;
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = Hu3DAnimLink(Hu3DData[obj->model[0]].hmf, (u16)m213_pumpAnimA, 0, "m213_p1_DEF");
            }
        case 2:
        case 3:
            if (obj->work[0] == 2) {
                data = DataRead(0x2E0008);
                m213_pumpAnimB = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "m213_p1_DEF");
                obj->work[1] = m213_pumpAnimB;
                HuMemMemoryFreePerm(data);
            } else {
                obj->work[1] = Hu3DAnimLink(Hu3DData[obj->model[0]].hmf, (u16)m213_pumpAnimB, 0, "m213_p1_DEF");
            }
            break;
    }
    Hu3DAnimTimeSet((s16)obj->work[1], 0);
    Hu3DAnimAttrSet((s16)obj->work[1], 1, 1);
    Hu3DModelRemakeStatic(obj->model[0]);
    Hu3DModelDynamicFree(obj->model[0]);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    obj->trans.x = m213_pumpPosTbl[obj->work[0]].x;
    obj->trans.y = m213_pumpPosTbl[obj->work[0]].y;
    obj->trans.z = m213_pumpPosTbl[obj->work[0]].z;
    obj->func = m213_PumpObjMain;
    entry = &m213_pumpTbl[obj->work[0]];
    entry->unk_00 = 0;
    entry->unk_04 = 0;
    entry->unk_08 = 0;
    for (i = 0, jets = m213_pumperTbl; i < 4; i++) {
        if (jets[i].unk_04->work[3] == obj->work[0]) {
            break;
        }
    }
    entry->unk_0C = i;
}

void m213_PumpObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1F4, 1, 1, -1, m213_PumpObjInit)->work[0] = i;
    }
}

void m213_HosePumpUpdate(omObjData *obj) {
    PumpPumpAwayHose *hose = &m213_hoseTbl[obj->work[0]];
    PumpPumpAwayPumper *jets[2];
    s32 i;
    s32 count;
    s32 speed;
    PumpPumpAwayRocket *player;

    for (i = 0, count = 0; (i < 4) & (count < 2); i++) {
        jets[count] = &m213_pumperTbl[i];
        count += GwPlayer[jets[count]->unk_04->work[0]].group == obj->work[0];
    }

    switch (hose->unk_04) {
        case 0:
            if (hose->unk_0C < jets[0]->unk_10 + jets[1]->unk_10) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                speed = (jets[0]->unk_10 + jets[1]->unk_10 - hose->unk_0C) / 3;
                hose->unk_0C = jets[0]->unk_10 + jets[1]->unk_10;
                hose->unk_08 = speed < 10 ? speed : 9;
                Hu3DMotionSpeedSet(obj->model[0], m213_pumpMotSpeedTbl[hose->unk_08]);
                Hu3DMotionAttrSet(obj->model[0], 1, 0);
                hose->unk_04 = 1;
            } else {
                Hu3DMotionTimeSet(obj->model[0], 0);
            }
            break;
        case 1:
            if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                Hu3DMotionTimeSet(obj->model[0], 0);
                hose->unk_04 = 0;
                player = &m213_rocketTbl[obj->work[0]];
                player->unk_0C = 1;
                player->unk_10 = hose->unk_08;
            }
            break;
    }
}

void m213_HoseLaunchUpdate(omObjData *obj) {
    PumpPumpAwayHose *hose = &m213_hoseTbl[obj->work[0]];
    f32 frame;

    if (hose->unk_04 == 2) {
        if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            hose->unk_04 = 3;
        }
    } else if (hose->unk_04 != 3) {
        frame = Hu3DData[obj->model[0]].motTime;
        if (frame != 0.0f) {
            if (frame >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
            } else {
                return;
            }
        } else {
            Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
        }
        Hu3DMotionAttrSet(obj->model[0], 2, 0);
        hose->unk_04 = 2;
    }
}

void m213_HoseObjMain(omObjData *obj) {
    if (m213_hoseTbl[obj->work[0]].unk_00 == -1) {
        return;
    }

    switch (m213_phase) {
        case 0:
        case 1:
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 1);
            break;
        case 2:
            m213_HosePumpUpdate(obj);
            break;
        case 3:
            m213_HoseLaunchUpdate(obj);
            break;
        case 4:
            break;
    }
}

void m213_HoseObjInit(omObjData *obj) {
    void *data;
    PumpPumpAwayHose *hose;

    obj->model[0] = Hu3DModelRead(0x2E0009, 0x289);
    omObjMotionRead(obj, 0, 0x2E000A);
    omObjMotionRead(obj, 1, 0x2E000B);
    if (obj->work[0] != 0) {
        data = DataRead(0x2E000C);
        obj->work[1] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "m213_hose_r_DEF");
        Hu3DAnimAttrSet(obj->work[1], 1, 1);
        HuMemMemoryFreePerm(data);
        Hu3DModelRemakeStatic(obj->model[0]);
        Hu3DModelDynamicFree(obj->model[0]);
    }
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    obj->trans.x = m213_hosePosTbl[obj->work[0]].x;
    obj->trans.y = m213_hosePosTbl[obj->work[0]].y;
    obj->trans.z = m213_hosePosTbl[obj->work[0]].z;
    obj->func = m213_HoseObjMain;
    hose = &m213_hoseTbl[obj->work[0]];
    hose->unk_00 = 0;
    hose->unk_04 = 0;
    hose->unk_08 = 0;
    hose->unk_0C = 0;
}

void m213_HoseObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x258, 1, 2, -1, m213_HoseObjInit)->work[0] = i;
    }
}

void m213_HudLabelDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    PumpPumpAwayHud *node = &m213_hudTbl[0];
    Gfx *gfx;
    Gfx *command;
    u32 word;
    s32 i;
    s32 x;
    s32 y;
    s32 right;
    s32 bottom;

    if (node->unk_00 == -1) {
        return;
    }
    if (m213_hudLabelAlpha < 255) {
        gfxPos = m213_GfxRectXluInit(gfxPos);
        gfxPos = m213_GfxPrimAlphaSet(gfxPos, (u8)m213_hudLabelAlpha);
    } else {
        gfxPos = m213_GfxRectTexInit(gfxPos);
    }
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, ((HuSprAnimData *)node->unk_0C)->pal);
    for (i = 0; i < 2; i++) {
        gDPLoadTextureTile_4b(gfx++, ((HuSprAnimData *)node->unk_0C)->data, G_IM_FMT_CI, 64, 16,
                              0, 0, 64, 16, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 64 << 2, 16 << 2);
        x = m213_hudLabelPosTbl[i][0];
        y = m213_hudLabelPosTbl[i][1];
        right = x + 64;
        bottom = y + 16;
        {
            Gfx *rectangle = gfx++;
            rectangle->words.w0 = _SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL((right * 4) & 0xFFC, 12, 12) | _SHIFTL((bottom * 4) & 0xFFC, 0, 12);
            rectangle->words.w1 = _SHIFTL((x * 4) & 0xFFC, 12, 12) | _SHIFTL((y * 4) & 0xFFC, 0, 12);
        }
        command = gfx++;
        word = _SHIFTL(G_RDPHALF_1, 24, 8);
        command->words.w0 = word;
        command->words.w1 = 0;
        command = gfx++;
        word = _SHIFTL(G_RDPHALF_2, 24, 8);
        command->words.w0 = word;
        word = _SHIFTL(1024, 16, 16) | _SHIFTL(1024, 0, 16);
        command->words.w1 = word;
    }
    *gfxPos = gfx;
}

void m213_HudDigitDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    PumpPumpAwayHud *node = &m213_hudTbl[1];
    Gfx *gfx;
    Gfx *command;
    u32 word;
    s32 i;
    s32 x;
    s32 y;
    s32 right;
    s32 bottom;

    if (node->unk_00 == -1) {
        return;
    }
    if (m213_hudDigitAlpha < 255) {
        gfxPos = m213_GfxRectXluInit(gfxPos);
        gfxPos = m213_GfxPrimAlphaSet(gfxPos, (u8)m213_hudDigitAlpha);
    } else {
        gfxPos = m213_GfxRectTexInit(gfxPos);
    }
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal16(gfx++, 0, ((HuSprAnimData *)node->unk_0C)->pal);
    for (i = 0; i < 8; i++) {
        if ((i != 0) & (i != 4)) {
            // Explicit command words and staged coordinate packing preserve GCC 2.7.2's loop hoisting.
            gDPSetTextureImage(gfx++, G_IM_FMT_CI, G_IM_SIZ_8b, 4, ((HuSprAnimData *)node->unk_0C)->data);
            gDPSetTile(gfx++, G_IM_FMT_CI, G_IM_SIZ_8b, 1, 0, G_TX_LOADTILE, 0, G_TX_WRAP, 0, G_TX_NOLOD, G_TX_WRAP, 0, G_TX_NOLOD);
            gDPLoadSync(gfx++);
            gDPLoadTile(gfx++, G_TX_LOADTILE, 0, node->unk_10[i] << 2, 8 << 1, (node->unk_10[i] + 10) << 2);
            command = gfx++;
            word = _SHIFTL(G_RDPPIPESYNC, 24, 8);
            command->words.w0 = word;
            word = 0;
            command->words.w1 = word;
            command = gfx++;
            word = _SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(G_IM_FMT_CI, 21, 3) | _SHIFTL(1, 9, 9);
            command->words.w0 = word;
            word = 0;
            command->words.w1 = word;
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, node->unk_10[i] << 2, 8 << 2, (node->unk_10[i] + 10) << 2);
            gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 8 << 2, 10 << 2);
            x = m213_hudDigitPosTbl[i][0];
            y = m213_hudDigitPosTbl[i][1];
            right = x;
            right += 8;
            bottom = y;
            bottom += 10;
            {
                Gfx *rectangle = gfx++;
                u32 packedRight;
                u32 packedX;

                right *= 4;
                packedRight = _SHIFTL(right & 0xFFC, 12, 12);
                bottom *= 4;
                rectangle->words.w0 = _SHIFTL(G_TEXRECT, 24, 8) | packedRight | _SHIFTL(bottom & 0xFFC, 0, 12);
                x *= 4;
                packedX = _SHIFTL(x & 0xFFC, 12, 12);
                y *= 4;
                rectangle->words.w1 = packedX | _SHIFTL(y & 0xFFC, 0, 12);
            }
            command = gfx++;
            word = _SHIFTL(G_RDPHALF_1, 24, 8);
            command->words.w0 = word;
            command->words.w1 = 0;
            command = gfx++;
            word = _SHIFTL(G_RDPHALF_2, 24, 8);
            command->words.w0 = word;
            word = _SHIFTL(1024, 16, 16) | _SHIFTL(1024, 0, 16);
            command->words.w1 = word;
        }
    }
    *gfxPos = gfx;
}

void m213_HudDigitCalc(omObjData *obj) {
    s32 digits[4];
    s32 i = 0;
    s32 j;
    s32 distance;
    PumpPumpAwayHud *node = &m213_hudTbl[1];
    PumpPumpAwayRocket *players = m213_rocketTbl;

    for (; i < 2; i++) {
        distance = players[i].unk_18 / 10.0f;
        digits[0] = distance / 10000;
        distance -= digits[0] * 10000;
        digits[1] = distance / 1000;
        distance -= digits[1] * 1000;
        digits[2] = distance / 100;
        distance -= digits[2] * 100;
        digits[3] = distance / 10;
        distance -= digits[3] * 10;
        for (j = 0; j < 4; j++) {
            node->unk_10[i * 4 + j] = 100 - digits[j] * 10;
            if (j == 3) {
                node->unk_10[i * 4 + j] -= distance;
            }
        }
        for (j = 3; j > 0; j--) {
            if (node->unk_10[i * 4 + j] < 11) {
                node->unk_10[i * 4 + j - 1] -= 10 - node->unk_10[i * 4 + j];
            }
        }
    }
}

void m213_HudObjMain(omObjData *obj) {
    s32 i;
    PumpPumpAwayHud *node;

    for (i = 0; i < 2; i++) {
        node = &m213_hudTbl[i];
        if (node->unk_00 == -1) {
            return;
        }
    }
    m213_HudDigitCalc(obj);
    switch (obj->work[0]) {
        case 0:
            if (m213_phase < 4) {
                for (i = 0; i < 2; i++) {
                    node = &m213_hudTbl[i];
                    node->unk_30 = 0;
                }
            } else {
                obj->work[0] = 1;
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                node = &m213_hudTbl[i];
                node->unk_30 += 25;
                if (node->unk_30 >= 255) {
                    node->unk_30 = 255;
                    obj->work[0] = 2;
                }
            }
            break;
        case 2:
            for (i = 0; i < 2; i++) {
                node = &m213_hudTbl[i];
                node->unk_30 = 255;
            }
            break;
    }
}

void m213_HudObjInit(omObjData *obj) {
    PumpPumpAwayHud *entry = m213_hudTbl;
    s32 i;

    m213_hudLabelAnimNo = HuSprAnimDataRead(0x2E0015);
    m213_hudLabelAnim = HuSprAnimDataGet(m213_hudLabelAnimNoLo);
    m213_hudLabelMdl = Hu3DHookFuncCreate(0, m213_HudLabelDraw, 2);
    Hu3DModelCameraSet(m213_hudLabelMdlLo, HU3D_CAM0);
    m213_hudLabelAlpha = 0;
    entry->unk_00 = 0;
    entry++;
    m213_hudDigitAnimNo = HuSprAnimDataRead(0x2E0016);
    m213_hudDigitAnim = HuSprAnimDataGet(m213_hudDigitAnimNoLo);
    m213_hudDigitMdl = Hu3DHookFuncCreate(0, m213_HudDigitDraw, 2);
    Hu3DModelCameraSet(m213_hudDigitMdlLo, HU3D_CAM0);
    m213_hudDigitAlpha = 0;
    entry->unk_00 = 0;
    obj->func = m213_HudObjMain;
    for (i = 0; i < 8; i++) {
        entry->unk_10[i] = 100;
    }
}

void m213_HudObjCreate(void) {
    omObjData *obj = omAddObj(0x384, 2, 0, -1, m213_HudObjInit);
    obj->work[0] = 0;
}

void m213_LaunchEffUpdate(omObjData *obj) {
    PumpPumpAwayLaunchEff *state = &m213_launchEffTbl[obj->work[0]];

    PumpPumpAwayRocket *players;
    PumpPumpAwayRocket *secondPlayer;

    switch (state->unk_00) {
        case 0:
            break;
        case 1:
            Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            state->unk_00 = 3;
            break;
        case 2:
            Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
            Hu3DMotionTimeSet(obj->model[1], 0);
            Hu3DMotionSpeedSet(obj->model[1], 0.5f);
            Hu3DMotionAttrSet(obj->model[1], 1, 0);
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            state->unk_00 = 4;
            break;
        case 3:
            players = m213_rocketTbl;
            secondPlayer = players + 1;
            if (players->unk_18 - secondPlayer->unk_18 > 0.0f) {
                obj->trans.y -= players->unk_20;
            } else {
                obj->trans.y -= secondPlayer->unk_20;
            }
            if (obj->trans.y < -3000.0f) {
                obj->trans.y = -3000.0f;
            }
            state->unk_04 -= 8;
            if (state->unk_04 > 0) {
                Hu3DModelTPLvlSet(obj->model[0], (u8)state->unk_04);
            } else {
                Hu3DMotionAttrSet(obj->model[0], 1, 1);
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                state->unk_04 = 255;
                state->unk_00 = 0;
            }
            break;
        case 4:
            state->unk_04 -= 5;
            if (state->unk_04 > 0) {
                Hu3DModelTPLvlSet(obj->model[1], (u8)state->unk_04);
            } else {
                Hu3DMotionAttrSet(obj->model[1], 1, 1);
                Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                state->unk_04 = 255;
                state->unk_00 = 0;
            }
            break;
    }
}

void m213_LaunchEffObjMain(omObjData *obj) {
    if (m213_launchEffTbl[obj->work[0]].unk_00 != -1) {
        switch (m213_phase) {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
            case 7:
                m213_LaunchEffUpdate(obj);
                break;
            case 5:
            case 6:
                break;
        }
    }
}

void m213_LaunchEffObjInit(omObjData *obj) {
    PumpPumpAwayLaunchEff *state;

    obj->model[0] = Hu3DModelRead(0x2E0017, 0x289);
    obj->model[1] = Hu3DModelRead(0x2E0019, 0x289);
    omObjMotionRead(obj, 0, 0x2E0018);
    omObjMotionRead(obj, 1, 0x2E001A);
    Hu3DModelTPLvlInit(obj->model[0]);
    Hu3DModelTPLvlSet(obj->model[0], 255);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0);
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlInit(obj->model[1]);
    Hu3DModelTPLvlSet(obj->model[1], 255);
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionTimeSet(obj->model[1], 0);
    Hu3DMotionAttrSet(obj->model[1], 1, 1);
    Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = m213_launchEffPosTbl[obj->work[0]].x;
    obj->trans.y = m213_launchEffPosTbl[obj->work[0]].y;
    obj->trans.z = m213_launchEffPosTbl[obj->work[0]].z;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    obj->func = m213_LaunchEffObjMain;
    state = &m213_launchEffTbl[obj->work[0]];
    state->unk_00 = 0;
    state->unk_04 = 255;
}

void m213_LaunchEffObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x2EE, 1, 2, -1, m213_LaunchEffObjInit)->work[0] = i;
    }
}

void m213_ParachuteUpdate(omObjData *obj) {
    PumpPumpAwayParachute *state = &m213_parachute;
    PumpPumpAwayRocket *player = &m213_rocketTbl[m213_parachuteRocketNo];
    s16 sound;

    switch (state->state) {
        case 0:
            break;
        case 1:
            Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj->trans.x = player->unk_28->trans.x;
            obj->trans.y = player->unk_28->trans.y + 200.0f;
            obj->trans.z = player->unk_28->trans.z;
            state->state = 3;
            break;
        case 2:
            Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj->trans.x = player->unk_28->trans.x;
            obj->trans.y = player->unk_28->trans.y + 200.0f;
            obj->trans.z = player->unk_28->trans.z;
            state->state = 3;
            break;
        case 3:
            if (Hu3DData[obj->model[0]].motTime >= 16.0f && m213_parachuteSeF == 0) {
                sound = HuAudFXPlay(0x363);
                if (player->unk_28->work[0] != 0) {
                    HuAudFXPanning(sound, 0x60);
                } else {
                    HuAudFXPanning(sound, 0x20);
                }
                m213_parachuteSeF = 1;
            }
            obj->trans.y = player->unk_28->trans.y + 200.0f;
            if (player->unk_24 == 2) {
                state->state = 4;
                break;
            }
            if (m213_parachuteSwingDir != 0) {
                if (state->angle <= 175.0f) {
                    state->angle = 175.0f;
                    m213_parachuteSwingDir ^= 1;
                } else {
                    state->angle = state->angle - 0.5 >= 360.0 ? state->angle - 0.5 - 360.0
                                   : state->angle - 0.5 < 0.0  ? state->angle - 0.5 + 360.0
                                                               : state->angle - 0.5;
                }
            } else {
                if (state->angle >= 185.0f) {
                    state->angle = 185.0f;
                    m213_parachuteSwingDir ^= 1;
                } else {
                    state->angle = state->angle + 0.5 >= 360.0 ? state->angle + 0.5 - 360.0
                                   : state->angle + 0.5 < 0.0  ? state->angle + 0.5 + 360.0
                                                               : state->angle + 0.5;
                }
            }
            obj->rot.z = state->angle + 180.0f >= 360.0f ? state->angle + 180.0f - 360.0f
                         : state->angle + 180.0f < 0.0f  ? state->angle + 180.0f + 360.0f
                                                         : state->angle + 180.0f;
            player->unk_28->trans.x = obj->trans.x - sindf(state->angle) * 200.0f;
            player->unk_28->trans.y = obj->trans.y + cosdf(state->angle) * 200.0f;
            break;
    }
}

void m213_ParachuteLandUpdate(omObjData *obj) {
    s32 *state = &m213_parachute.state;
    PumpPumpAwayRocket *player = &m213_rocketTbl[m213_parachuteRocketNo];

    if (*state == 4) {
        Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
        Hu3DMotionTimeSet(obj->model[0], 0);
        Hu3DMotionAttrSet(obj->model[0], 1, 0);
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        obj->trans.x = player->unk_28->trans.x;
        obj->trans.y = player->unk_28->trans.y + 200.0f;
        obj->trans.z = player->unk_28->trans.z;
        *state = 5;
    }
}

void m213_ParachuteObjMain(omObjData *obj) {
    s32 *state = &m213_parachute.state;

    if (*state == -1) {
        return;
    }
    switch (m213_phase) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            if (*state < 4) {
                m213_ParachuteUpdate(obj);
                break;
            }
        case 8:
            m213_ParachuteLandUpdate(obj);
            break;
    }
}

void m213_ParachuteObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2E001B, 0x1689);
    omObjMotionRead(obj, 0, 0x2E001C);
    omObjMotionRead(obj, 1, 0x2E001D);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionTimeSet(obj->model[0], 0);
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = m213_ParachuteObjMain;
    m213_parachute.state = 0;
    m213_parachuteRocketNo = -1;
    m213_parachuteAngle = 180.0f;
    m213_parachuteObj = obj;
}

void m213_ParachuteObjCreate(void) {
    omObjData *obj = omAddObj(0x2E4, 1, 2, -1, m213_ParachuteObjInit);
    obj->work[0] = 0;
}

void m213_RocketSmokeEmit(omObjData *obj) {
    s32 i;
    PumpPumpAwaySmoke *entry;
    PumpPumpAwayRocket *player;

    for (i = 0; i < 20; i++) {
        entry = &m213_smokeTbl[i];
        if (entry->unk_00 == 0) {
            player = &m213_rocketTbl[obj->work[0]];
            entry->unk_00 = 1;
            entry->unk_0C->trans.x = obj->trans.x;
            entry->unk_0C->trans.y = obj->trans.y - 200.0f;
            entry->unk_0C->trans.z = obj->trans.z;
            entry->unk_08 = player->unk_20 * 0.6;
            break;
        }
    }
}

void m213_SmokeObjMain(omObjData *obj) {
    PumpPumpAwaySmoke *entry = &m213_smokeTbl[obj->work[0]];

    if (entry->unk_00 == -1) {
        return;
    }
    switch (entry->unk_00) {
        case 0:
            break;
        case 1:
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            entry->unk_00 = 2;
            break;
        case 2:
            entry->unk_04 -= 25;
            if (entry->unk_04 > 0) {
                Hu3DModelTPLvlSet(obj->model[0], (u8)entry->unk_04);
                obj->trans.y -= entry->unk_08 * entry->unk_08;
                obj->scale.x += 0.1;
                obj->scale.y += 0.1;
                obj->scale.z += 0.1;
            } else {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                entry->unk_04 = 255;
                entry->unk_08 = 0;
                entry->unk_00 = 0;
                obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
            }
            break;
    }
}

void m213_SmokeObjInit(omObjData *obj) {
    PumpPumpAwaySmoke *entry;

    obj->model[0] = Hu3DModelRead(0x2E0013, 0x289);
    Hu3DModelTPLvlInit(obj->model[0]);
    Hu3DModelTPLvlSet(obj->model[0], 255);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->func = m213_SmokeObjMain;
    entry = &m213_smokeTbl[obj->work[0]];
    entry->unk_00 = 0;
    entry->unk_04 = 255;
    entry->unk_08 = 0;
    entry->unk_0C = obj;
}

void m213_SmokeObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 14; i++) {
        omAddObj(0x2F8, 1, 0, -1, m213_SmokeObjInit)->work[0] = i;
    }
}

void m213_RocketPumpUpdate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];
    s16 sound;

    switch (player->unk_0C) {
        case 0:
            Hu3DMotionTimeSet(obj->model[0], 0);
            break;
        case 1:
            Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
            Hu3DMotionSpeedSet(obj->model[0], m213_pumpMotSpeedTbl[player->unk_10]);
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DMotionAttrSet(obj->model[0], 4, 0);
            player->unk_0C = 2;
            sound = HuAudFXPlay(0x362);
            if (obj->work[0] != 0) {
                HuAudFXPanning(sound, 0x60);
            } else {
                HuAudFXPanning(sound, 0x20);
            }
            break;
        case 2:
            if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                Hu3DMotionTimeSet(obj->model[0], Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2);
                Hu3DMotionSpeedSet(obj->model[0], m213_pumpMotSpeedTbl[player->unk_10]);
                Hu3DMotionAttrSet(obj->model[0], 4, 4);
                player->unk_0C = 3;
            }
            break;
        case 3:
            if (Hu3DData[obj->model[0]].motTime <= 2.0f) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                Hu3DMotionTimeSet(obj->model[0], 0);
                player->unk_0C = 0;
            }
            break;
    }
}

void m213_RocketPumpEndUpdate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    switch (player->unk_0C) {
        case 2:
            if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                Hu3DMotionTimeSet(obj->model[0], Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2);
                Hu3DMotionSpeedSet(obj->model[0], m213_pumpMotSpeedTbl[player->unk_10]);
                Hu3DMotionAttrSet(obj->model[0], 4, 4);
                player->unk_0C = 3;
            }
            break;
        case 3:
            if (Hu3DData[obj->model[0]].motTime <= 2.0f) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
                Hu3DMotionTimeSet(obj->model[0], 0);
                Hu3DMotionAttrSet(obj->model[0], 4, 0);
                Hu3DMotionAttrSet(obj->model[0], 1, 1);
                player->unk_0C = 0;
            }
            break;
        default:
            Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 1);
            player->unk_0C = 3;
            break;
    }
}

void m213_RocketLaunchStart(omObjData *obj) {
    s32 i = obj->work[0];
    PumpPumpAwayRocket *player = &m213_rocketTbl[i];
    PumpPumpAwayLaunchEff *state = &m213_launchEffTbl[i];

    player->unk_00 = 1;
    state->unk_00 = 1;
    if (obj->work[0] == 0) {
        HuAudFXPlay(0x35F);
    }
}

void m213_RocketSmokeUpdate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    if (player->unk_18 - player->unk_1C > 300.0f) {
        m213_RocketSmokeEmit(obj);
        player->unk_1C = player->unk_18;
    }
}

void m213_SkyDecoHideAll(void) {
    s32 i;
    PumpPumpAwayLakitu *entry;
    PumpPumpAwayLowFlyer *nozzle;
    PumpPumpAwayMidFlyer *hose;
    PumpPumpAwaySway *spray;
    PumpPumpAwaySway *otherSpray;

    for (i = 0, entry = m213_lakituTbl; i < 2; i++) {
        entry[i].unk_0C = 1;
    }
    m213_recordMarkerHiddenF = 1;
    for (i = 0, nozzle = m213_lowFlyerTbl; i < 4; i++) {
        nozzle[i].unk_04 = 1;
    }
    for (i = 0, hose = m213_midFlyerTbl; i < 4; i++) {
        hose[i].hidden = 1;
    }
    for (i = 0, spray = m213_highFlyerTbl; i < 6; i++) {
        spray[i].unk_04 = 1;
    }
    for (i = 0, otherSpray = m213_cloudTbl; i < 6; i++) {
        otherSpray[i].unk_04 = 1;
    }
}

void m213_RocketFlyUpdate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];
    s16 sound;
    PumpPumpAwayParachute *state;

    switch (player->unk_04) {
        case 0:
            if (player->unk_18 < 2000.0f) {
                player->unk_20 += 0.2;
                player->unk_18 += player->unk_20 * player->unk_20;
            } else {
                player->unk_18 += player->unk_20 * player->unk_20;
                player->unk_04 = 1;
                player->unk_2C = (u8)(rand8() % 7) * 15;
            }
            m213_RocketSmokeUpdate(obj);
            break;
        case 1:
            player->unk_20 = 10.6f;
            player->unk_18 += player->unk_20 * player->unk_20;
            if (--player->unk_14 <= 0) {
                player->unk_14 = 0;
                if (m213_rocketTbl[obj->work[0] ^ 1].unk_14 == 0) {
                    player->unk_04 = 3;
                } else {
                    player->unk_04 = 2;
                }
            } else if (player->unk_14 < 20) {
                obj->trans.y -= player->unk_30;
            } else {
                player->unk_2C = player->unk_2C + (u8)(rand8() % 10) >= 360.0f ? player->unk_2C + (u8)(rand8() % 10) - 360.0f
                                 : player->unk_2C + (u8)(rand8() % 10) < 0.0f  ? player->unk_2C + (u8)(rand8() % 10) + 360.0f
                                                                               : player->unk_2C + (u8)(rand8() % 10);
                obj->trans.y += sindf(player->unk_2C) * 3.0;
                player->unk_30 = (obj->trans.y - 200.0f) * 0.05;
            }
            m213_RocketSmokeUpdate(obj);
            break;
        case 2:
            if (player->unk_20 > 0.0f) {
                player->unk_20 -= 0.4;
                player->unk_18 += player->unk_20 * player->unk_20;
                if (player->unk_20 <= 0.0f) {
                    player->unk_18 += 101 - (s32)player->unk_18 % 100;
                }
                m213_RocketSmokeUpdate(obj);
            } else {
                if (m213_fallSeF == 0 && player->unk_20 < -1.2) {
                    sound = HuAudFXPlay(0x360);
                    if (obj->work[0] != 0) {
                        HuAudFXPanning(sound, 0x60);
                    } else {
                        HuAudFXPanning(sound, 0x20);
                    }
                    m213_fallSeF = 1;
                }
                if (obj->trans.y < -200.0f) {
                    player->unk_24 = 1;
                }
                if (obj->trans.y <= -3000.0f) {
                    obj->trans.y = -3000.0f;
                } else {
                    obj->trans.y -= player->unk_20 * player->unk_20;
                    player->unk_20 -= 0.2;
                }
            }
            break;
        case 3:
            if (player->unk_20 > 0.0f) {
                player->unk_20 -= 0.3;
                player->unk_18 += player->unk_20 * player->unk_20;
                if (player->unk_20 <= 0.0f) {
                    player->unk_18 += 101 - (s32)player->unk_18 % 100;
                    m213_SkyDecoHideAll();
                }
                m213_RocketSmokeUpdate(obj);
            } else {
                player->unk_04 = 10;
            }
            break;
        case 10:
            if (obj->trans.y < 0.0f) {
                player->unk_24 = 1;
            }
            if (m213_fallDelay <= 0) {
                if (m213_parachuteOpenF == 0) {
                    m213_parachute.state = 1;
                    m213_parachuteRocketNo = obj->work[0];
                    obj->trans.y -= player->unk_20 * player->unk_20;
                    player->unk_20 = -2.0f;
                    m213_parachuteOpenF = 1;
                } else {
                    obj->trans.y -= player->unk_20 * player->unk_20;
                    state = &m213_parachute;
                    obj->rot.z = m213_parachuteAngle + 180.0f >= 360.0f ? m213_parachuteAngle + 180.0f - 360.0f
                                 : state->angle + 180.0f < 0.0f               ? state->angle + 180.0f + 360.0f
                                                                              : state->angle + 180.0f;
                }
            } else {
                m213_fallDelay--;
                obj->trans.y -= player->unk_20 * player->unk_20;
                player->unk_20 -= 0.2;
            }
            break;
    }
    if (m213_cover.state >= 2) {
        obj->trans.y = 2000.0f;
    }
}

void m213_RocketFlyCheck(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    if (player->unk_14 == 0 && player->unk_18 == 0.0f) {
        player->unk_00 = 99;
        player->unk_24 = 2;
    } else {
        m213_RocketFlyUpdate(obj);
    }
}

void m213_RocketStayUpdate(omObjData *obj) {
    u32 playerIndex = obj->work[0];
    PumpPumpAwayRocket *players = m213_rocketTbl;
    PumpPumpAwayRocket *player = &players[playerIndex ^ 1];

    if (m213_phase < 6) {
        obj->trans.y -= player->unk_20;
        if (obj->trans.y < -2800.0f) {
            obj->trans.y = -2800.0f;
        }
    } else if (m213_cover.state >= 2) {
        obj->trans.y = 200.0f;
    }
}

void m213_RocketFlyExec(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    switch (player->unk_00) {
        case 0:
            m213_RocketLaunchStart(obj);
            break;
        case 1:
            m213_RocketFlyCheck(obj);
            break;
        case 99:
            m213_RocketStayUpdate(obj);
            break;
    }
}

void m213_RocketLandStart(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    if (player->unk_00 == 99) {
        obj->trans.y = 200.0f;
    } else if (player->unk_04 == 2) {
        obj->trans.y = 950.0f;
        player->unk_08 = 20;
    } else if (player->unk_04 == 10) {
        obj->trans.y = 1000.0f;
        obj->rot.z = 0.0f;
        player->unk_08 = 10;
    }
}

void m213_RocketLandUpdate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];
    PumpPumpAwayParachute *angleState;
    f32 angle;
    s16 sound;
    s32 i;
    PumpPumpAwayPumper *jet;

    switch (player->unk_08) {
        case 10:
            obj->trans.y = 1010.0f;
            player->unk_08 = 11;
            break;
        case 11:
            angleState = &m213_parachute;
            if (m213_parachuteAngle + 180.0f >= 360.0f) {
                angle = m213_parachuteAngle + 180.0f - 360.0f;
            } else {
                angle = angleState->angle + 180.0f;
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
            }
            obj->rot.z = angle;
            obj->trans.y -= 10.0f;
            if (obj->trans.y <= 200.0f) {
                obj->trans.y = 200.0f;
                player->unk_24 = 2;
                player->unk_08 = 12;
            }
            break;
        case 20:
            obj->trans.y = 1000.0f;
            obj->rot.z = 180.0f;
            player->unk_08 = 21;
            break;
        case 21:
            obj->trans.y -= 50.0f;
            if (obj->trans.y <= 250.0f) {
                m213_launchEffTbl[obj->work[0]].unk_00 = 2;
                player->unk_08 = 22;
                sound = HuAudFXPlay(0x361);
                if (obj->work[0] != 0) {
                    HuAudFXPanning(sound, 96);
                } else {
                    HuAudFXPanning(sound, 32);
                }
                for (i = 0; i < 4; i++) {
                    jet = &m213_pumperTbl[i];
                    if (jet->unk_00 != -1) {
                        if (jet->unk_04->work[1] == obj->work[0]) {
                            if (jet->unk_20 == 0) {
                                omVibrate((s16)jet->unk_04->work[0], 2, 2, 20);
                            }
                        } else if (jet->unk_20 == 0) {
                            omVibrate((s16)jet->unk_04->work[0], 10, 0, 10);
                        }
                    }
                }
            }
            break;
        case 22:
            obj->trans.y -= 50.0f;
            if (obj->trans.y <= 100.0f) {
                obj->trans.y = 100.0f;
                player->unk_24 = 2;
                player->unk_08 = 23;
            }
            break;
    }
}

void m213_RocketObjMain(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[obj->work[0]];

    if (player->unk_00 == -1) {
        return;
    }
    switch (m213_phase) {
        case 0:
        case 1:
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 1);
            break;
        case 2:
            m213_RocketPumpUpdate(obj);
            break;
        case 3:
            m213_RocketPumpEndUpdate(obj);
            break;
        case 4:
        case 5:
        case 6:
            m213_RocketFlyExec(obj);
            break;
        case 7:
            if (player->unk_08 == 0) {
                m213_RocketLandStart(obj);
            } else {
                m213_RocketLandUpdate(obj);
            }
            break;
    }
}

void m213_RocketObjInit(omObjData *obj) {
    void *data;
    PumpPumpAwayRocket *player;

    obj->model[0] = Hu3DModelRead(0x2E000D, 0x4022A9);
    obj->motion[0] = Hu3DModelReadNum(0x2E000E);
    Hu3DModelVtxBufMake(obj->model[0]);
    Hu3DMotionModelSetEx(obj->model[0], obj->motion[0]);
    Hu3DModelDynamicFree(obj->motion[0]);
    if (obj->work[0] != 0) {
        data = DataRead(0x2E000F);
        obj->work[1] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "m213_roket_r00_DEF");
        Hu3DAnimAttrSet(obj->work[1], 1, 1);
        HuMemMemoryFreePerm(data);
        data = DataRead(0x2E0010);
        obj->work[2] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, data, 0, "m213_roket_r01_DEF");
        Hu3DAnimAttrSet(obj->work[2], 1, 1);
        HuMemMemoryFreePerm(data);
        Hu3DModelRemakeStatic(obj->model[0]);
        Hu3DModelDynamicFree(obj->model[0]);
    }
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 0);
    obj->trans.x = m213_rocketPosTbl[obj->work[0]].x;
    obj->trans.y = m213_rocketPosTbl[obj->work[0]].y;
    obj->trans.z = m213_rocketPosTbl[obj->work[0]].z;
    obj->func = m213_RocketObjMain;
    player = &m213_rocketTbl[obj->work[0]];
    player->unk_00 = 0;
    player->unk_04 = 0;
    player->unk_08 = 0;
    player->unk_0C = 0;
    player->unk_10 = 0;
    player->unk_14 = 0;
    player->unk_18 = 0;
    player->unk_1C = 0;
    player->unk_20 = 0;
    player->unk_24 = 0;
    player->unk_2C = 0;
    player->unk_28 = obj;
}

void m213_RocketObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x2BC, 1, 1, -1, m213_RocketObjInit)->work[0] = i;
    }
}

void m213_PlayerComInput(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    s32 press = 0;
    s32 interval;

    if (jet->unk_34 > 0) {
        jet->unk_34--;
    } else {
        press = 1;
        jet->unk_34 = rand8() % jet->unk_30 + 5;
    }
    if (press) {
        if (jet->unk_18 != 0) {
            HuPadBtnDown[GwPlayer[obj->work[0]].pad] |= 0x8000;
        } else {
            HuPadBtnDown[GwPlayer[obj->work[0]].pad] |= 0x4000;
        }
    } else {
        interval = jet->unk_30 * 0.5;
        if (rand8() % interval == 0 && jet->unk_14 == 0.0f) {
            if (jet->unk_18 != 0) {
                HuPadBtnDown[GwPlayer[obj->work[0]].pad] |= 0x8000;
            } else {
                HuPadBtnDown[GwPlayer[obj->work[0]].pad] |= 0x4000;
            }
            jet->unk_34 = rand8() % jet->unk_30 + 5;
        }
    }
}

void m213_PlayerPumpUpdate(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    f32 frame = Hu3DData[obj->model[0]].motTime;
    s16 sound;

    if (jet->unk_18 != 0) {
        if (frame <= 2.0f) {
            if (jet->unk_10 >= 6) {
                jet->unk_10 *= 0.97;
            }
            jet->unk_14 = 0.0f;
        }
        jet->unk_10 += (s32)jet->unk_14;
        if (HuPadBtnDown[GwPlayer[obj->work[0]].pad] & 0x8000) {
            sound = HuAudPlayerFXPlay(0x35D, obj->work[0]);
            if (obj->work[1] != 0) {
                HuAudFXPanning(sound, 0x60);
            } else {
                HuAudFXPanning(sound, 0x20);
            }
            if (frame < 2.0f) {
                jet->unk_14 = (jet->unk_2C - frame) * 0.17;
            } else {
                jet->unk_14 = (jet->unk_2C - frame) * 0.01;
            }
            jet->unk_18 = 0;
            jet->unk_28 = 1;
            jet->unk_2C = frame;
        }
    } else {
        if (frame >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
            if (jet->unk_10 >= 6) {
                jet->unk_10 *= 0.97;
            }
            jet->unk_14 = 0.0f;
        }
        jet->unk_10 += (s32)jet->unk_14;
        if ((HuPadBtnDown[GwPlayer[obj->work[0]].pad] & 0x4000) ||
            (HuPadBtnDown[GwPlayer[obj->work[0]].pad] & 0x2000)) {
            sound = HuAudPlayerFXPlay(0x35E, obj->work[0]);
            if (obj->work[1] != 0) {
                HuAudFXPanning(sound, 0x60);
            } else {
                HuAudFXPanning(sound, 0x20);
            }
            if (frame >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02) {
                jet->unk_14 = (frame - jet->unk_2C) * 0.17;
            } else {
                jet->unk_14 = (frame - jet->unk_2C) * 0.01;
            }
            jet->unk_18 = 1;
            jet->unk_28 = 1;
            jet->unk_2C = frame;
        }
    }
}

void m213_PlayerPumpMotUpdate(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];

    if (jet->unk_28 != 0) {
        if (jet->unk_18 != 0) {
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DMotionAttrSet(obj->model[0], 4, 4);
        } else {
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            Hu3DMotionAttrSet(obj->model[0], 4, 0);
        }
    } else if (jet->unk_18 != 0) {
        if (Hu3DData[obj->model[0]].motTime <= 2.0f) {
            Hu3DMotionAttrSet(obj->model[0], 1, 1);
        }
    } else if (Hu3DData[obj->model[0]].motTime >= Hu3DMotion[Hu3DData[obj->model[0]].motId].unk02 - 2) {
        Hu3DMotionAttrSet(obj->model[0], 1, 1);
    }
}

void m213_PlayerTurnUpdate(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];

    switch (jet->unk_08) {
        case 0:
            if (obj->rot.y >= 180.0f) {
                break;
            }
            if (obj->work[0] == 0 && m213_turnDelay != 0) {
                m213_turnDelay--;
            }
            if (m213_turnDelay == 0) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[3]);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionAttrSet(obj->model[0], 2, 2);
                jet->unk_08 = 3;
            }
            break;
        case 3:
            obj->rot.y += 10.0f;
            if (!(obj->rot.y >= 180.0f)) {
                break;
            }
            obj->rot.y = 180.0f;
        case 1:
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 20, 2);
            jet->unk_08 = 0;
            jet->unk_0C = 0;
            break;
    }
}

void m213_PlayerWatchUpdate(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    PumpPumpAwayRocket *player;
    PumpPumpAwayRocket *other;

    if (m213_rocketTbl[obj->work[1]].unk_00 == 99 && jet->unk_0C == 0) {
        Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[4]].motId, 0, 30, 2);
        jet->unk_08 = 4;
        jet->unk_0C = 1;
    }
    player = m213_rocketTbl;
    other = &player[1];
    if (player->unk_18 - other->unk_18 > 0.0f) {
        obj->trans.y -= player->unk_20;
    } else {
        obj->trans.y -= other->unk_20;
    }
    if (obj->trans.y < -3000.0f) {
        obj->trans.y = -3000.0f;
    }
}

void m213_PlayerResultUpdate(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    s16 sound;

    switch (jet->unk_08) {
        case 0:
            obj->trans.y = m213_playerPosTbl[0].y;
            if (m213_rocketTbl[obj->work[1]].unk_24 == 2) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[6]);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionAttrSet(obj->model[0], 2, 0);
                Hu3DMotionAttrSet(obj->model[0], 1, 0);
                jet->unk_08 = 6;
                sound = PlayerFXPlay(0x286, obj->work[0]);
                if (obj->work[1] != 0) {
                    HuAudFXPanning(sound, 0x60);
                } else {
                    HuAudFXPanning(sound, 0x20);
                }
            }
            break;
        case 4:
            if (obj->work[1] == 0) {
                obj->trans.y = m213_playerPosTbl[0].y;
            } else {
                obj->trans.y = m213_playerPosTbl[obj->work[1]].y;
            }
            break;
    }
}

void m213_PlayerFrontTurn(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    f32 angle;

    obj->trans.y = m213_playerPosTbl[0].y;
    switch (jet->unk_08) {
        case 0:
            if (jet->unk_0C == 9) {
                break;
            }
            Hu3DMotionModelSet(obj->model[0], obj->motion[3]);
            Hu3DMotionTimeSet(obj->model[0], 0);
            Hu3DMotionAttrSet(obj->model[0], 2, 2);
            jet->unk_08 = 3;
            break;
        case 3:
            obj->rot.y = obj->rot.y + 10.0f >= 360.0f ? obj->rot.y + 10.0f - 360.0f : obj->rot.y + 10.0f < 0.0f ? obj->rot.y + 10.0f + 360.0f
                                                                                                                : obj->rot.y + 10.0f;
            angle = obj->rot.y + 180.0f >= 360.0f ? obj->rot.y + 180.0f - 360.0f : obj->rot.y + 180.0f < 0.0f ? obj->rot.y + 180.0f + 360.0f
                                                                                                              : obj->rot.y + 180.0f;
            if (angle >= 180.0f) {
                obj->rot.y = 0;
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 20, 2);
                jet->unk_08 = 0;
                jet->unk_0C = 9;
            }
            break;
    }
}

void m213_PlayerWinStart(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];
    s32 modelFile = omCharModelNoTbl[GwPlayer[obj->work[0]].chr][0];

    if (jet->unk_08 == 0) {
        Hu3DMotionModelSet(obj->model[0], obj->motion[5]);
        Hu3DMotionTimeSet(obj->model[0], 0.0f);
        Hu3DMotionAttrSet(obj->model[0], 1, 0);
        Hu3DMotionAttrSet(obj->model[0], 2, 0);
        jet->unk_08 = 5;
        if (obj->work[0] != 0) {
            HuAudCharVoicePlayPan(modelFile | 0x2F, 0x60);
        } else {
            HuAudCharVoicePlayPan(modelFile | 0x2F, 0x20);
        }
    }
}

void m213_PlayerObjMain(omObjData *obj) {
    PumpPumpAwayPumper *jet = &m213_pumperTbl[obj->work[0]];

    if (jet->unk_00 == -1) {
        return;
    }
    switch (m213_phase) {
        case 0:
        case 1:
            m213_PadClear(obj->work[0]);
            if (jet->unk_0C == 0) {
                Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
                Hu3DMotionTimeSet(obj->model[0], 0.0f);
                Hu3DMotionAttrSet(obj->model[0], 1, 1);
                jet->unk_08 = 1;
                jet->unk_0C = 0;
            }
            break;
        case 2:
            if (jet->unk_20 != 0) {
                m213_PadClear(obj->work[0]);
                m213_PlayerComInput(obj);
            }
            m213_PlayerPumpUpdate(obj);
            m213_PlayerPumpMotUpdate(obj);
            break;
        case 3:
            m213_PadClear(obj->work[0]);
            m213_PlayerTurnUpdate(obj);
            if (GwPlayer[obj->work[0]].chr == 4) {
                obj->rot.x = 0;
            }
            break;
        case 4:
        case 5:
            m213_PadClear(obj->work[0]);
            m213_PlayerWatchUpdate(obj);
            break;
        case 6:
            if (m213_cover.state < 2) {
                break;
            }
        case 7:
            m213_PlayerResultUpdate(obj);
            break;
        case 8:
        case 9:
            m213_PlayerFrontTurn(obj);
            break;
        case 10:
            m213_PlayerWinStart(obj);
            break;
    }
    if (obj->work[2] != 0) {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, 12.0f, obj->trans.z + 30.0f);
    } else {
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y + 2.0, obj->trans.z + 30.0f);
    }
}

void m213_PlayerObjInit(omObjData *obj) {
    u16 character = GwPlayer[obj->work[0]].chr;
    PumpPumpAwayPumper *jet;

    obj->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharModelNoTbl[character][1], 0x2B9);
    omObjMotionRead(obj, 0, CharMotionDataNumGet(character, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(character, 0x14));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(character, 1));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(character, 0x13));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(character, 0x2F));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(character, 0x37));
    Hu3DMotionModelSet(obj->model[0], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    obj->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    HuTranslateF(Hu3DData[obj->model[1]].mtx, 0.0f, 5.0f, 0.0f);
    if (obj->work[1] == 0) {
        obj->trans.x = m213_playerPosTbl[obj->work[1] + m213_team0SlotCnt].x;
        obj->trans.y = m213_playerPosTbl[obj->work[1] + m213_team0SlotCnt].y;
        obj->trans.z = m213_playerPosTbl[obj->work[1] + m213_team0SlotCnt].z;
        obj->work[3] = obj->work[1] + m213_team0SlotCnt;
        m213_team0SlotCnt++;
    } else {
        obj->trans.x = m213_playerPosTbl[obj->work[1] + m213_team1SlotCnt + 1].x;
        obj->trans.y = m213_playerPosTbl[obj->work[1] + m213_team1SlotCnt + 1].y;
        obj->trans.z = m213_playerPosTbl[obj->work[1] + m213_team1SlotCnt + 1].z;
        obj->work[3] = obj->work[1] + m213_team1SlotCnt + 1;
        m213_team1SlotCnt++;
    }
    obj->rot.x = obj->rot.y = obj->rot.z = 0.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y + 2.0, obj->trans.z + 30.0f);
    switch (character) {
        case 0:
            obj->trans.z -= 10.0f;
        case 2:
        case 7:
            obj->trans.z -= 20.0f;
            break;
        case 3:
            obj->trans.z -= 10.0f;
            break;
        case 4:
            obj->trans.z -= 20.0f;
            obj->rot.x = 350.0f;
            break;
        case 5:
            obj->trans.z -= 45.0f;
            break;
    }
    obj->func = m213_PlayerObjMain;
    jet = &m213_pumperTbl[obj->work[0]];
    jet->unk_00 = 0;
    jet->unk_04 = obj;
    jet->unk_08 = 1;
    jet->unk_0C = 0;
    jet->unk_18 = 1;
    jet->unk_10 = 0;
    jet->unk_14 = 0;
    jet->unk_1C = 0;
    jet->unk_20 = GwPlayer[obj->work[0]].stat & 1;
    jet->unk_24 = GwPlayer[obj->work[0]].cpu_difficulty;
    jet->unk_28 = 0;
    jet->unk_2C = 0;
    jet->unk_34 = (u8)(rand8() % 5);
    switch (jet->unk_24) {
        case 0:
            jet->unk_30 = 20;
            break;
        case 1:
            jet->unk_30 = 15;
            break;
        case 2:
            jet->unk_30 = 10;
            break;
        default:
            jet->unk_30 = 5;
            break;
    }
}

void m213_PlayerObjCreateAll(void) {
    s32 i;
    s32 playerIndex;
    omObjData *obj;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(0x12C, 9, 60, -1, m213_PlayerObjInit);
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
        obj->work[0] = playerIndex;
        obj->work[1] = GwPlayer[playerIndex].group;
    }
}

s32 m213_RecordSave(void) {
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRecord *record = &m213_record;
    PumpPumpAwayRocket *other = &player[1];
    u32 distance;

    if (player->unk_18 > other->unk_18) {
        distance = (u16)(player->unk_18 * 0.01);
        if (distance > record->record) {
            GWMgRecordSet(0, distance);
        } else {
            return 0;
        }
    } else {
        distance = other->unk_18 * 0.01;
        if ((u16)distance > record->record) {
            GWMgRecordSet(0, (u16)distance);
        } else {
            return 0;
        }
    }
    return 1;
}

void m213_RecordDigitCalc(omObjData *obj) {
    PumpPumpAwayRecord *record = &m213_record;
    s32 value;

    if (m213_phase < 9) {
        value = GWMgRecordGet(0);
        m213_recordValue = value;
    } else {
        value = GWMgRecordGet(0);
    }
    record->digits[0] = value / 100;
    value %= 100;
    if (record->digits[0] == 0) {
        record->digits[0] = -1;
    }
    record->digits[1] = value / 10;
    value %= 10;
    if (record->digits[1] == 0 && record->digits[0] == -1) {
        record->digits[1] = -1;
    }
    record->digits[2] = value;
    record->digits[3] = 12;
}

void m213_RecordObjMain(omObjData *obj) {
    PumpPumpAwayRecord *record = &m213_record;
    s32 i;

    if (m213_phase == 9 && m213_RecordSave()) {
        m213_RecordDigitCalc(obj);
        if (record->unk_24 == 0) {
            if (record->unk_20 >= 13) {
                record->unk_24 = 1;
            } else {
                record->unk_20 += 2;
            }
        } else if (record->unk_20 > 0) {
            record->unk_20 -= 2;
        }
        HuSprScaleSet(record->group, 0, record->unk_20 / 12.0f + 1.0f, record->unk_20 / 12.0f + 1.0f);
        HuSprPosSet(record->group, 0, record->unk_20 / 4 + 32, record->unk_20 / 4 + 22);
        HuSprGrpMemberSet(record->group, 0, record->spriteData, 0);
        HuSprAnimModeSet(record->group, 0, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(record->group, 0, (s16)record->digits[0]);
        HuSprAttrSet(record->group, 0, 0x1000);
        HuSprAttrSet(record->group, 0, 0);
        for (i = 1; i < 3; i++) {
            HuSprScaleSet(record->group, i, record->unk_20 / 12.0f + 1.0f, record->unk_20 / 12.0f + 1.0f);
            HuSprPosSet(record->group, i, i * 12, 0);
            HuSprGrpMemberSet(record->group, i, record->spriteData, 0);
            HuSprAnimModeSet(record->group, i, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(record->group, i, (s16)record->digits[i]);
            HuSprAttrSet(record->group, i, 0x1000);
            HuSprAttrSet(record->group, i, 0);
        }
        espScaleSet(record->esprite, record->unk_20 / 12.0f + 1.0f, record->unk_20 / 12.0f + 1.0f);
        espPosSet(record->esprite, record->unk_20 * 4 + 78, record->unk_20 / 4 + 22);
    }
}

void m213_RecordObjInit(omObjData *obj) {
    PumpPumpAwayRecord *record;
    s32 i;

    m213_RecordDigitCalc(obj);
    record = &m213_record;
    m213_recordDigitAnim = HuSprAnimDataRead(0x32);
    m213_recordSprGrp = HuSprGrpCreate(4, 5);
    HuSprPosSet(m213_recordSprGrp, 0, 32, 22);
    HuSprGrpMemberSet(m213_recordSprGrp, 0, m213_recordDigitAnim, 0);
    HuSprAnimModeSet(m213_recordSprGrp, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(m213_recordSprGrp, 0, m213_recordDigit0Lo);
    HuSprAttrSet(m213_recordSprGrp, 0, 0x1000);
    HuSprAttrSet(m213_recordSprGrp, 0, 0);
    for (i = 1; i < 3; i++) {
        HuSprParentSet(record->group, i, 0);
        HuSprGrpMemberSet(record->group, i, record->spriteData, 0);
        if (record->digits[i] != -1) {
            HuSprPosSet(record->group, i, i * 12, 0);
            HuSprGrpMemberSet(record->group, i, record->spriteData, 0);
            HuSprAnimModeSet(record->group, i, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(record->group, i, (s16)record->digits[i]);
            HuSprAttrSet(record->group, i, 0x1000);
            HuSprAttrSet(record->group, i, 0);
        } else {
            HuSprPosSet(record->group, i, i * 12, 0);
            HuSprGrpMemberSet(record->group, i, record->spriteData, 0);
            HuSprAnimModeSet(record->group, i, HUSPR_ANIM_MODE_STOP);
            HuSprPatNoSet(record->group, i, 0);
            HuSprAttrSet(record->group, i, 0x1000);
            HuSprDispOff(record->group, i);
        }
    }
    record->espriteData = HuSprAnimDataRead(0x2E0023);
    record->esprite = espEntry(record->espriteData, 0, 0);
    espAttrSet(record->esprite, 0x1000);
    espPosSet(record->esprite, 78, 22);
    espDispOn(record->esprite);
    record->unk_20 = 0;
    record->unk_24 = 0;
    obj->func = m213_RecordObjMain;
}

void m213_RecordObjCreate(void) {
    omAddObj(0x2FD, 1, 0, -1, m213_RecordObjInit);
}

void m213_RecordMarkerObjMain(omObjData *obj) {
    PumpPumpAwayRecordMarker *marker = &m213_recordMarker;
    PumpPumpAwayRocket *first = &m213_rocketTbl[0];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f64 height;

    if (marker->state == -1) {
        return;
    }
    if (m213_recordMarkerHiddenF == 0) {
        height = (first->unk_18 > other->unk_18) ? first->unk_18 : other->unk_18;
        if (marker->record * 10 - height * 0.1 + 400.0 < 2000.0) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj->trans.y = marker->record * 10 - height * 0.1 + 350.0;
            if (obj->trans.y < -1000.0f) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                marker->hidden = 1;
            }
        }
    }
    if (m213_cover.state >= 2 && marker->state < 10) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        marker->state = 10;
    }
}

void m213_RecordMarkerObjInit(omObjData *obj) {
    obj->model[0] = Hu3DModelRead(0x2E001F, 0x1689);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    obj->trans.x = 0.0f;
    obj->trans.y = 1000.0f;
    obj->trans.z = 550.0f;
    obj->func = m213_RecordMarkerObjMain;
    m213_recordMarker.state = 0;
    m213_recordMarkerValue = m213_recordValue;
    m213_recordMarkerHiddenF = 0;
}

void m213_RecordMarkerObjCreate(void) {
    omAddObj(0x302, 1, 0, -1, m213_RecordMarkerObjInit);
}

void m213_Lakitu0Update(omObjData *obj) {
    PumpPumpAwayLakitu *entry = &m213_lakituTbl[obj->work[0]];
    PumpPumpAwayRocket *first = &m213_rocketTbl[0];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f32 height;
    f32 angle;
    s32 hundreds;

    if (entry->unk_0C == 0) {
        height = first->unk_18 > other->unk_18 ? first->unk_18 : other->unk_18;
        hundreds = height * 0.01;
        switch (entry->unk_00) {
            case 0:
                entry->unk_04 = hundreds * 0.01 + 1.0;
                obj->trans.y = entry->unk_04 * 1000 - height * 0.1 + 480.0;
                entry->unk_00 = 1;
                break;
            case 1:
                obj->trans.y = entry->unk_04 * 1000 - height * 0.1 + 480.0;
                if (obj->trans.y < -1000.0f) {
                    entry->unk_00 = 0;
                }
                break;
        }
    }
    Hu3DAnimTimeSet(obj->work[1], (s16)entry->unk_04);
    Hu3DAnimTimeSet(obj->work[2], 0);
    Hu3DAnimTimeSet(obj->work[3], 0);
    if (entry->unk_08 + 6.0f >= 360.0f) {
        angle = entry->unk_08 + 6.0f - 360.0f;
    } else {
        angle = entry->unk_08 + 6.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    }
    entry->unk_08 = angle;
    obj->trans.y += (f64)sindf(angle);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
}

void m213_Lakitu1Update(omObjData *obj) {
    PumpPumpAwayLakitu *entry = &m213_lakituTbl[obj->work[0]];
    PumpPumpAwayRocket *first = &m213_rocketTbl[0];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f32 height;
    f32 angle;
    s32 hundreds;

    if (entry->unk_0C == 0) {
        height = first->unk_18 > other->unk_18 ? first->unk_18 : other->unk_18;
        hundreds = height * 0.01;
        switch (entry->unk_00) {
            case 0:
                entry->unk_04 = hundreds * 0.01 + 2.0;
                obj->trans.y = entry->unk_04 * 1000 - height * 0.1 + 480.0;
                entry->unk_00 = 2;
                break;
            case 1:
                entry->unk_04 = hundreds * 0.01 + 1.0;
                obj->trans.y = entry->unk_04 * 1000 - height * 0.1 + 480.0;
                entry->unk_00 = 2;
                break;
            case 2:
                obj->trans.y = entry->unk_04 * 1000 - height * 0.1 + 480.0;
                if (obj->trans.y < -1000.0f) {
                    entry->unk_00 = 1;
                }
                break;
        }
    }
    Hu3DAnimTimeSet(obj->work[1], (s16)entry->unk_04);
    Hu3DAnimTimeSet(obj->work[2], 0);
    Hu3DAnimTimeSet(obj->work[3], 0);
    if (entry->unk_08 + 6.0f >= 360.0f) {
        angle = entry->unk_08 + 6.0f - 360.0f;
    } else {
        angle = entry->unk_08 + 6.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    }
    entry->unk_08 = angle;
    obj->trans.y += (f64)sindf(angle);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
}

void m213_LakituObjMain(omObjData *obj) {
    PumpPumpAwayLakitu *entry = &m213_lakituTbl[obj->work[0]];

    if (entry->unk_00 == -1) {
        return;
    }
    if (obj->work[0] == 0) {
        m213_Lakitu0Update(obj);
    } else {
        m213_Lakitu1Update(obj);
    }
    if (m213_cover.state >= 2 && entry->unk_00 < 10) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        entry->unk_00 = 10;
    }
}

void m213_LakituObjInit(omObjData *obj) {
    void *data;
    s32 i;
    PumpPumpAwayLakitu *entry;

    if (obj->work[0] == 0) {
        m213_lakituMdl = obj->model[0] = Hu3DModelRead(0xA0089, 0x289);
        obj->model[1] = Hu3DModelRead(0x2E0020, 0x289);
        data = DataRead(0x2E0021);
        obj->work[1] = m213_lakituAnimNo = Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, "m213_plart2_DEF");
        obj->work[2] = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, m213_lakituAnimNo, 0, "m213_plart1_DEF");
        obj->work[3] = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, m213_lakituAnimNo, 0, "m213_plart0_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        obj->model[0] = Hu3DModelLink(m213_lakituMdl);
        obj->model[1] = Hu3DModelRead(0x2E0020, 0x289);
        obj->work[1] = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, m213_lakituAnimNo, 0, "m213_plart2_DEF");
        obj->work[2] = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, m213_lakituAnimNo, 0, "m213_plart1_DEF");
        obj->work[3] = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, m213_lakituAnimNo, 0, "m213_plart0_DEF");
    }
    Hu3DModelRemakeStatic(obj->model[1]);
    Hu3DModelDynamicFree(obj->model[1]);
    for (i = 1; i < 4; i++) {
        Hu3DAnimTimeSet((s16)obj->work[i], 0);
        Hu3DAnimAttrSet((s16)obj->work[i], 1, 1);
    }
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    obj->trans.x = 43.5f;
    obj->trans.y = 1000.0f;
    obj->trans.z = -17.5f;
    obj->rot.y = 345.0f;
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, obj->rot.y, 0.0f);
    obj->func = m213_LakituObjMain;
    entry = &m213_lakituTbl[obj->work[0]];
    entry->unk_00 = 0;
    entry->unk_04 = 0;
    entry->unk_08 = 0;
    entry->unk_0C = 0;
}

void m213_LakituObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x30C, 2, 1, -1, m213_LakituObjInit)->work[0] = i;
    }
}

void m213_LowFlyerObjMain(omObjData *obj) {
    PumpPumpAwayLowFlyer *nozzle = &m213_lowFlyerTbl[obj->work[0]];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f64 distance;
    f32 *positions;
    f32 angle;

    if (nozzle->unk_04 == 0) {
        distance = player->unk_18 > other->unk_18 ? player->unk_18 : other->unk_18;
        positions = m213_lowFlyerYTbl;
        if (m213_lowFlyerYTbl[obj->work[0]] - distance * 0.1 + 400.0 < 1000.0) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            obj->trans.y = positions[obj->work[0]] - distance * 0.1 + 400.0;
            if (obj->trans.y < -1000.0f) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                nozzle->unk_04 = 1;
            }
        }
    }
    obj->rot.y = nozzle->unk_08 * 180 + 90;
    if (nozzle->unk_08 == 0) {
        obj->trans.x += nozzle->unk_0C;
    } else {
        obj->trans.x -= nozzle->unk_0C;
    }
    if ((obj->trans.x < 0.0f ? -obj->trans.x : obj->trans.x) >= 700.0f) {
        if (nozzle->unk_08 == 0) {
            obj->trans.x = 700.0f;
        } else {
            obj->trans.x = -700.0f;
        }
        nozzle->unk_08 ^= 1;
        nozzle->unk_0C = (u8)(rand8() % 6) + 4;
    }
    if (nozzle->unk_10 + 6.0f >= 360.0f) {
        angle = nozzle->unk_10 + 6.0f - 360.0f;
    } else {
        angle = nozzle->unk_10 + 6.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    }
    nozzle->unk_10 = angle;
    obj->trans.y += sindf(angle) * 2.0;
    if (m213_cover.state >= 2 && nozzle->unk_00 < 10) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        nozzle->unk_00 = 10;
    }
}

void m213_LowFlyerObjInit(omObjData *obj) {
    PumpPumpAwayLowFlyer *nozzle;

    if (m213_lowFlyerMdl == 0) {
        m213_lowFlyerMdl = obj->model[0] = Hu3DModelRead(0x2E0011, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(m213_lowFlyerMdl);
    }
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = (u8)(rand8() % 10) * -50;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = m213_LowFlyerObjMain;
    nozzle = &m213_lowFlyerTbl[obj->work[0]];
    nozzle->unk_00 = 0;
    nozzle->unk_04 = 0;
    nozzle->unk_08 = rand8() & 1;
    nozzle->unk_0C = (u8)(rand8() % 6) + 4;
    nozzle->unk_10 = rand8();
}

void m213_LowFlyerObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x2F9, 1, 1, -1, m213_LowFlyerObjInit)->work[0] = i;
    }
}

void m213_MidFlyerObjMain(omObjData *obj) {
    PumpPumpAwayMidFlyer *effect = &m213_midFlyerTbl[obj->work[0]];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f64 distance;
    f32 *positions;

    if (effect->state != -1) {
        if (effect->hidden == 0) {
            distance = (player->unk_18 > other->unk_18) ? player->unk_18 : other->unk_18;
            positions = m213_midFlyerYTbl;
            if (m213_midFlyerYTbl[obj->work[0]] - distance * 0.1 + 400.0 < 1000.0) {
                Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                obj->trans.y = positions[obj->work[0]] - distance * 0.1 + 400.0;
                if (obj->trans.y < -1000.0f) {
                    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    effect->hidden = 1;
                }
            }
        }
        obj->rot.y = effect->direction * 180 + 90;
        if (effect->direction == 0) {
            obj->trans.x += effect->speed;
        } else {
            obj->trans.x -= effect->speed;
        }
        if (((obj->trans.x < 0.0f) ? -obj->trans.x : obj->trans.x) >= 700.0f) {
            if (effect->direction == 0) {
                obj->trans.x = 700.0f;
            } else {
                obj->trans.x = -700.0f;
            }
            effect->speed = (u8)(rand8() % 10) + 10;
            effect->direction ^= 1;
        }
        if (m213_cover.state >= 2 && effect->state < 10) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            effect->state = 10;
        }
    }
}

void m213_MidFlyerObjInit(omObjData *obj) {
    PumpPumpAwayMidFlyer *effect;

    if (m213_midFlyerMdl == 0) {
        m213_midFlyerMdl = obj->model[0] = Hu3DModelRead(0xA0062, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(m213_midFlyerMdl);
    }
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (rand8() & 1) {
        obj->trans.x = (u8)(rand8() % 10) * 50;
    } else {
        obj->trans.x = (u8)(rand8() % 10) * -50;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = m213_MidFlyerObjMain;
    effect = &m213_midFlyerTbl[obj->work[0]];
    effect->state = 0;
    effect->hidden = 0;
    effect->direction = rand8() & 1;
    effect->speed = (u8)(rand8() % 5) + 10;
}

void m213_MidFlyerObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x2FA, 1, 0, -1, m213_MidFlyerObjInit)->work[0] = i;
    }
}

void m213_HighFlyerObjMain(omObjData *obj) {
    PumpPumpAwaySway *spray = &m213_highFlyerTbl[obj->work[0]];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f32 distance;
    f32 *positions;
    f32 angle;
    f32 rotation;

    if (spray->unk_00 != -1) {
        if (spray->unk_04 == 0) {
            distance = (player->unk_18 > other->unk_18) ? player->unk_18 : other->unk_18;
            switch (spray->unk_00) {
                case 0:
                    positions = m213_highFlyerYTbl;
                    if (m213_highFlyerYTbl[m213_highFlyerCnt] - distance * 0.1 + 400.0 < 1000.0) {
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        obj->trans.y = positions[obj->work[0]] + distance * 0.1 + 400.0;
                        spray->unk_00 = 1;
                        obj->work[1] = m213_highFlyerCnt;
                        m213_highFlyerCnt++;
                    }
                    break;
                case 1:
                    obj->trans.y = m213_highFlyerYTbl[obj->work[1]] - distance * 0.1 + 400.0;
                    if (obj->trans.y < -500.0f) {
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        if (obj->work[0] & 1) {
                            obj->trans.x = rand16() % 501 + 100;
                        } else {
                            obj->trans.x = -(rand16() % 501) - 100;
                        }
                        spray->unk_00 = 0;
                    }
                    break;
            }
        }
        if (spray->unk_08 + 3.0f >= 360.0f) {
            angle = (spray->unk_08 + 3.0f) - 360.0f;
        } else {
            angle = spray->unk_08 + 3.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
        }
        spray->unk_08 = angle;
        if (sindf(spray->unk_08) * 15.0f + 0.0f >= 360.0f) {
            rotation = sindf(spray->unk_08) * 15.0f + 0.0f - 360.0f;
        } else if (sindf(spray->unk_08) * 15.0f + 0.0f < 0.0f) {
            rotation = sindf(spray->unk_08) * 15.0f + 0.0f + 360.0f;
        } else {
            rotation = sindf(spray->unk_08) * 15.0f + 0.0f;
        }
        obj->rot.z = rotation;
        if (m213_cover.state >= 2 && spray->unk_00 < 10) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            spray->unk_00 = 10;
        }
    }
}

void m213_HighFlyerObjInit(omObjData *obj) {
    PumpPumpAwaySway *spray;

    if (m213_highFlyerMdl == 0) {
        m213_highFlyerMdl = obj->model[0] = Hu3DModelRead(0x2E0022, 0x289);
    } else {
        obj->model[0] = Hu3DModelLink(m213_highFlyerMdl);
    }
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (obj->work[0] & 1) {
        obj->trans.x = rand16() % 501 + 100;
    } else {
        obj->trans.x = -(rand16() % 501) - 100;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = -150.0f;
    obj->func = m213_HighFlyerObjMain;
    spray = &m213_highFlyerTbl[obj->work[0]];
    spray->unk_00 = 0;
    spray->unk_04 = 0;
    spray->unk_08 = rand8();
}

void m213_HighFlyerObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(0x2FA, 1, 0, -1, m213_HighFlyerObjInit)->work[0] = i;
    }
}

void m213_CloudObjMain(omObjData *obj) {
    PumpPumpAwaySway *spray = &m213_cloudTbl[obj->work[0]];
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];
    f32 distance;
    s32 progress;
    f32 *positions;
    f32 angle;

    if (spray->unk_00 != -1) {
        distance = (player->unk_18 > other->unk_18) ? player->unk_18 : other->unk_18;
        progress = distance * 0.01;
        if (spray->unk_04 == 0) {
            switch (spray->unk_00) {
                case 0:
                    positions = m213_cloudYTbl;
                    if (m213_cloudYTbl[m213_cloudCnt] - distance * 0.1 + 400.0 < 1000.0) {
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        obj->trans.y = positions[obj->work[0]] + distance * 0.1 + 400.0;
                        spray->unk_00 = 1;
                        obj->work[1] = m213_cloudCnt;
                        m213_cloudCnt++;
                    }
                    break;
                case 1:
                    obj->trans.y = m213_cloudYTbl[obj->work[1]] - distance * 0.1 + 400.0;
                    if (obj->trans.y < -1000.0f) {
                        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        if (obj->work[0] & 1) {
                            obj->trans.x = rand16() % 301 + 100;
                        } else {
                            obj->trans.x = -(rand16() % 301) - 100;
                        }
                        obj->trans.z = (rand8() & 1) ? -500.0f : 500.0f;
                        spray->unk_00 = 0;
                    }
                    break;
            }
        }
        if (spray->unk_08 + 6.0f >= 360.0f) {
            angle = (spray->unk_08 + 6.0f) - 360.0f;
        } else {
            angle = spray->unk_08 + 6.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
        }
        spray->unk_08 = angle;
        obj->scale.y = obj->scale.z = obj->scale.x = sindf(angle) * 0.03 + 0.5;
        if ((m213_cover.state >= 2 && spray->unk_00 < 10) || (progress >= 351 && spray->unk_00 == 0)) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            spray->unk_00 = 10;
            spray->unk_04 = 1;
        }
    }
}

void m213_CloudObjInit(omObjData *obj) {
    PumpPumpAwaySway *spray;

    if (m213_cloudMdl == 0) {
        m213_cloudMdl = obj->model[0] = Hu3DModelRead(0x230005, 0x299);
    } else {
        obj->model[0] = Hu3DModelLink(m213_cloudMdl);
    }
    Hu3DMotionAttrSet(obj->model[0], 1, 1);
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (obj->work[0] & 1) {
        obj->trans.x = rand16() % 301 + 100;
    } else {
        obj->trans.x = -(rand16() % 301) - 100;
    }
    obj->trans.y = 1000.0f;
    obj->trans.z = (rand8() & 1) ? -500.0f : 500.0f;
    obj->scale.x = obj->scale.y = obj->scale.z = 0.5f;
    obj->func = m213_CloudObjMain;
    spray = &m213_cloudTbl[obj->work[0]];
    spray->unk_00 = 0;
    spray->unk_04 = 0;
    spray->unk_08 = rand8();
}

void m213_CloudObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        omAddObj(0x2FB, 1, 0, -1, m213_CloudObjInit)->work[0] = i;
    }
}

void m213_CameraViewObjMain(omObjData *obj) {
    Vec position;
    Vec target;
    Vec result;
    u32 i;

    if (m213_cameraSetF == 0) {
        m213_cameraSetF = 1;
        target.x = 650.0f;
        target.y = 0.0f;
        target.z = 2600.0f;
        position.x = 65.0f;
        position.y = 0.0f;
        position.z = -500.0f;
        m213_PolarCalc(&position, &target, &result);
        for (i = 0; i < 1; i++) {
            CZoomM[i] = result.x;
            CRotM[i].x = 360.0f - result.z;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = position.x;
            CenterM[i].z = position.z;
        }
    }
}

void m213_SeqDoneObjMain(omObjData *obj) {
}

void m213_SeqEndObjMain(omObjData *obj) {
    if (m213_phaseTimer > 0) {
        m213_phaseTimer--;
    } else {
        m213_phaseStep = 1;
        obj->func = m213_SeqDoneObjMain;
    }
}

void m213_SeqResultWaitObjMain(omObjData *obj) {
    if (GMesStatGet() & GMES_STAT_TIMEEND) {
        m213_phaseTimer = 0x14;
        obj->func = m213_SeqEndObjMain;
    }
}

s32 m213_RecordNewCheck(void) {
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &m213_rocketTbl[1];
    PumpPumpAwayRecord *record = &m213_record;
    u32 distance;

    if (player->unk_18 > other->unk_18) {
        distance = (u16)(player->unk_18 * 0.01);
    } else {
        distance = (u16)(other->unk_18 * 0.01);
    }
    return distance > record->record;
}

void m213_ResultMesCreate(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[0];
    PumpPumpAwayRocket *other = &m213_rocketTbl[1];
    s32 winningTeam;
    s32 i;
    s32 count;
    PumpPumpAwayPumper *jet;
    u8 winners[2];

    if (player->unk_18 > other->unk_18) {
        winningTeam = 0;
    } else {
        winningTeam = 1;
    }
    for (i = 0, count = 0; i < 4; i++) {
        jet = &m213_pumperTbl[i];
        if (jet->unk_04->work[1] == winningTeam) {
            winners[count] = GwPlayer[jet->unk_04->work[0]].chr;
            count++;
            GwPlayer[jet->unk_04->work[0]].bonusCoin = 10;
        }
    }
    GMesCreate(GMES_MES_MG_WINNERS_2, winners[0], winners[1]);
    if (!m213_RecordNewCheck()) {
        HuAudSeqPlay(0x66);
    } else {
        HuAudSeqPlay(0x6A);
    }
}

void m213_SeqResultObjMain(omObjData *obj) {
    PumpPumpAwayRocket *player = m213_rocketTbl;
    PumpPumpAwayRocket *other = &player[1];

    if (m213_phaseTimer > 0) {
        m213_phaseTimer--;
    } else {
        if (player->unk_18 == other->unk_18) {
            GMesCreate(GMES_MES_MG_DRAW);
            HuAudSeqPlay(0x6C);
            m213_phaseTimer = 144;
        } else {
            m213_ResultMesCreate(obj);
        }
        obj->func = m213_SeqResultWaitObjMain;
    }
}

void m213_SeqResultDelayObjMain(omObjData *obj) {
    if (m213_phaseTimer > 0) {
        m213_phaseTimer--;
    } else {
        m213_phaseStep = 1;
        obj->func = m213_SeqResultObjMain;
    }
}

void m213_SeqRecordWaitObjMain(omObjData *obj) {
    if (GMesStatGet() == 0) {
        if (m213_phaseTimer > 0) {
            m213_phaseTimer--;
        } else {
            m213_phaseStep = 1;
            obj->func = m213_SeqResultObjMain;
        }
    }
}

void m213_SeqRecordObjMain(omObjData *obj) {
    if (m213_phaseTimer > 0) {
        m213_phaseTimer--;
    } else if (m213_RecordNewCheck()) {
        GMesCreate(GMES_MES_MG_RECORD);
        m213_phaseStep = 1;
        m213_phaseTimer = 15;
        obj->func = m213_SeqRecordWaitObjMain;
    } else {
        m213_phaseTimer = 0;
        m213_phaseStep = 2;
        obj->func = m213_SeqResultObjMain;
    }
}

void m213_SeqFinishWaitObjMain(omObjData *obj) {
    if (GMesStatGet() == 0) {
        m213_phaseTimer = 0xF;
        obj->func = m213_SeqRecordObjMain;
    }
}

void m213_SeqFinishObjMain(omObjData *obj) {
    GMesCreate(GMES_MES_16);
    m213_phaseTimer = 0x4B;
    HuAudSeqFadeOut(0x78);
    obj->func = m213_SeqFinishWaitObjMain;
}

void m213_SeqLandWaitObjMain(omObjData *obj) {
    PumpPumpAwayRocket *player = m213_rocketTbl;

    if (player->unk_24 == 2 && m213_rocketTbl[1].unk_24 == 2) {
        m213_phaseStep = 1;
        obj->func = m213_SeqFinishObjMain;
    }
}

void m213_SeqCoverWaitObjMain(omObjData *obj) {
    if (m213_cover.state == -1) {
        m213_phaseStep = 1;
        obj->func = m213_SeqLandWaitObjMain;
    }
}

void m213_SeqFallWaitObjMain(omObjData *obj) {
    PumpPumpAwayRocket *player = m213_rocketTbl;

    if (player->unk_24 != 0 && m213_rocketTbl[1].unk_24 != 0) {
        m213_cover.state = 1;
        m213_phaseStep = 1;
        obj->func = m213_SeqCoverWaitObjMain;
    }
}

void m213_SeqFlightObjMain(omObjData *obj) {
    PumpPumpAwayRocket *player = &m213_rocketTbl[0];
    PumpPumpAwayRocket *other = &m213_rocketTbl[1];

    if (m213_phaseTimer != 0) {
        m213_phaseTimer--;
    } else if (player->unk_14 == 0 && other->unk_14 == 0) {
        if (player->unk_18 == 0.0f && other->unk_18 == 0.0f) {
            m213_phaseStep = 4;
            obj->func = m213_SeqFinishObjMain;
        } else if (player->unk_04 == 10 || other->unk_04 == 10) {
            m213_phaseStep = 1;
            obj->func = m213_SeqFallWaitObjMain;
        }
    }
}

void m213_SeqLaunchObjMain(omObjData *obj) {
    s32 i;
    PumpPumpAwayPumper *jet;

    m213_phaseTimer = 45;
    m213_phaseStep = 1;
    obj->func = m213_SeqFlightObjMain;
    if (m213_launchVibF != 0) {
        for (i = 0; i < 4; i++) {
            jet = &m213_pumperTbl[i];
            if (jet->unk_00 != -1 && jet->unk_20 == 0) {
                omVibrate((s16)jet->unk_04->work[0], 2, 2, 20);
            }
        }
    }
}

void m213_RocketPowerCalc(void) {
    s32 i;
    PumpPumpAwayPumper *jet;
    PumpPumpAwayRocket *player;
    PumpPumpAwayRocket *other;
    PumpPumpAwayRocket *first;
    PumpPumpAwayRocket *team;

    for (i = 0; i < 4; i++) {
        jet = &m213_pumperTbl[i];
        team = &m213_rocketTbl[jet->unk_04->work[1]];
        team->unk_14 += jet->unk_10;
    }

    first = &m213_rocketTbl[0];
    player = m213_rocketTbl;
    other = &player[1];
    if (first->unk_14 == other->unk_14) {
        if (first->unk_14 != 0) {
            if (rand8() & 1) {
                first->unk_14 += 40;
            } else {
                other->unk_14 += 40;
            }
        } else {
            other->unk_14 = 0;
            player->unk_14 = 0;
        }
    } else {
        if (((player->unk_14 - other->unk_14 >= 0) ? player->unk_14 - other->unk_14 : other->unk_14 - player->unk_14) < 40) {
            if (player->unk_14 > other->unk_14) {
                player->unk_14 = other->unk_14 + 40;
            } else {
                other->unk_14 = player->unk_14 + 40;
            }
        }
    }
    if (player->unk_14 != 0 && other->unk_14 != 0) {
        m213_launchVibF = 1;
    }
}

void m213_SeqLaunchWaitObjMain(omObjData *obj) {
    if (m213_phaseTimer != 0) {
        m213_phaseTimer--;
    } else {
        obj->func = m213_SeqLaunchObjMain;
    }
}

void m213_SeqTimeUpWaitObjMain(omObjData *obj) {
    if (m213_phaseTimer != 0) {
        m213_phaseTimer--;
    } else {
        m213_phaseTimer = 0;
        m213_RocketPowerCalc();
        obj->func = m213_SeqLaunchWaitObjMain;
    }
}

void m213_SeqTimerObjMain(omObjData *obj) {
    if (m213_phaseTimer != 0) {
        m213_phaseTimer--;
        GMesTimerValueSet((m213_phaseTimer + 29) / 30);
    } else {
        GMesTimerEnd();
        m213_phaseTimer = 90;
        obj->func = m213_SeqTimeUpWaitObjMain;
        m213_phaseStep = 1;
        omSysPauseDisableF = 1;
    }
}

void m213_SeqTimerStartObjMain(omObjData *obj) {
    GMesCreate(GMES_MES_TIMER, 0xA, 0xA0, 0x1C);
    m213_phaseTimer = 0x12D;
    obj->func = m213_SeqTimerObjMain;
}

void m213_SeqStartWaitObjMain(omObjData *obj) {
    if (++m213_musicTimer == 0x21) {
        HuAudSeqPlay(0x2E);
    }
    if (GMesStatGet() == 0 || (GMesStatGet() & GMES_STAT_TIMEEND)) {
        obj->func = m213_SeqTimerStartObjMain;
        m213_phaseStep = 1;
    }
}

void m213_SeqStartObjMain(omObjData *obj) {
    GMesCreate(5);
    obj->func = m213_SeqStartWaitObjMain;
    m213_phaseStep = 1;
}

void m213_ExitObjMain(omObjData *obj) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m213_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        obj->func = m213_ExitObjMain;
    }
}

void m213_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
        obj->func = m213_ExitWaitObjMain;
        HuAudSeqFadeOut(0x1E);
        HuAudFXAllFadeOut(0x1E);
    }
}

void m213_PhaseUpdate(void) {
    m213_phase += m213_phaseStep;
    m213_phaseStep = 0;
}

void m213_MainObjMain(omObjData *obj) {
    m213_PhaseUpdate();
    switch (m213_phase) {
        case 0:
            break;
        case 1:
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
        case 10:
            break;
        case 11:
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            obj->func = m213_ExitWaitObjMain;
            break;
    }
}

void m213_PumperWorkInit(void) {
    s32 i;
    PumpPumpAwayPumper *jet;

    for (i = 0, jet = m213_pumperTbl; i < 4; i++) {
        jet[i].unk_00 = -1;
        jet[i].unk_04 = 0;
        jet[i].unk_08 = 0;
        jet[i].unk_0C = 0;
        jet[i].unk_10 = 0;
        jet[i].unk_14 = 0.0f;
        jet[i].unk_1C = 0;
        jet[i].unk_20 = 0;
        jet[i].unk_24 = 0;
        jet[i].unk_30 = 0;
    }
}

void m213_PumpWorkInit(void) {
    s32 i;
    PumpPumpAwayPump *entry;

    for (i = 0, entry = m213_pumpTbl; i < 2; i++) {
        entry[i].unk_00 = -1;
    }
}

void m213_HoseWorkInit(void) {
    s32 i;
    PumpPumpAwayHose *entry;

    for (i = 0, entry = m213_hoseTbl; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
}

void m213_RocketWorkInit(void) {
    s32 i;
    PumpPumpAwayRocket *entry;

    for (i = 0; i < 2; i++) {
        entry = &m213_rocketTbl[i];
        entry->unk_00 = -1;
        entry->unk_04 = 0;
        entry->unk_08 = 0;
        entry->unk_0C = 0;
        entry->unk_10 = 0;
        entry->unk_14 = 0;
        entry->unk_18 = 0;
        entry->unk_1C = 0;
        entry->unk_20 = 0;
        entry->unk_24 = 0;
        entry->unk_2C = 0;
    }
}

void m213_HudWorkInit(void) {
    s32 i;
    s32 j;
    PumpPumpAwayHud *entry;

    for (i = 0; i < 2; i++) {
        entry = &m213_hudTbl[i];
        entry->unk_00 = -1;
        entry->unk_04 = 0;
        entry->unk_0C = 0;
        entry->unk_08 = 0;
        entry->unk_30 = 0;
        for (j = 0; j < 8; j++) {
            entry->unk_10[j] = 0;
        }
    }
}

void m213_LaunchEffWorkInit(void) {
    s32 i;
    PumpPumpAwayLaunchEff *entry;

    for (i = 0, entry = m213_launchEffTbl; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
    }
}

void m213_ParachuteWorkInit(void) {
    m213_parachute.state = -1;
    m213_parachuteRocketNo = -1;
    m213_parachuteAngle = 0.0f;
}

void m213_SmokeWorkInit(void) {
    s32 i;
    PumpPumpAwaySmoke *entry;

    for (i = 0, entry = m213_smokeTbl; i < 20; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
}

void m213_LakituWorkInit(void) {
    s32 i;
    PumpPumpAwayLakitu *entry;

    for (i = 0, entry = m213_lakituTbl; i < 2; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0;
    }
    m213_lakituMdl = 0;
}

void m213_RecordMarkerWorkInit(void) {
    m213_recordMarker.state = -1;
    m213_recordMarkerValue = 0;
    m213_recordMarkerHiddenF = 0;
}

void m213_LowFlyerWorkInit(void) {
    s32 i;
    PumpPumpAwayLowFlyer *entry;

    for (i = 0, entry = m213_lowFlyerTbl; i < 4; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 0;
        entry[i].unk_0C = 0.0f;
        entry[i].unk_10 = 0.0f;
    }
    m213_lowFlyerMdl = 0;
}

void m213_MidFlyerWorkInit(void) {
    s32 i;
    PumpPumpAwayMidFlyer *entry;

    for (i = 0, entry = m213_midFlyerTbl; i < 4; i++) {
        entry[i].state = -1;
        entry[i].hidden = 0;
        entry[i].direction = 0;
        entry[i].speed = 0.0f;
    }
    m213_midFlyerMdl = 0;
}

void m213_HighFlyerWorkInit(void) {
    s32 i;
    PumpPumpAwaySway *entry;

    for (i = 0, entry = m213_highFlyerTbl; i < 6; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 1.0f;
    }
    m213_highFlyerMdl = 0;
}

void m213_CloudWorkInit(void) {
    s32 i;
    PumpPumpAwaySway *entry;

    for (i = 0, entry = m213_cloudTbl; i < 6; i++) {
        entry[i].unk_00 = -1;
        entry[i].unk_04 = 0;
        entry[i].unk_08 = 1.0f;
    }
    m213_cloudMdl = 0;
}

void m213_WorkInitAll(void) {
    m213_phase = 0;
    m213_phaseStep = 0;
    m213_phaseTimer = 0;
    m213_team0SlotCnt = 0;
    m213_team1SlotCnt = 0;
    m213_turnDelay = 30;
    m213_launchVibF = 0;
    m213_PumperWorkInit();
    m213_PumpWorkInit();
    m213_HoseWorkInit();
    m213_RocketWorkInit();
    m213_HudWorkInit();
    m213_LaunchEffWorkInit();
    m213_ParachuteWorkInit();
    m213_SmokeWorkInit();
    m213_LakituWorkInit();
    m213_RecordMarkerWorkInit();
    m213_LowFlyerWorkInit();
    m213_MidFlyerWorkInit();
    m213_HighFlyerWorkInit();
    m213_CloudWorkInit();
}

void m213_ObjCreateAll(void) {
    m213_WorkInitAll();
    m213_SkyObjCreate();
    m213_GroundObjCreate();
    m213_NearBackObjCreate();
    m213_FarBackObjCreate();
    m213_PlayerObjCreateAll();
    m213_PumpObjCreateAll();
    m213_HoseObjCreateAll();
    m213_RocketObjCreateAll();
    m213_ParachuteObjCreate();
    m213_LaunchEffObjCreateAll();
    m213_SmokeObjCreateAll();
    m213_HudObjCreate();
    m213_RecordObjCreate();
    m213_RecordMarkerObjCreate();
    m213_LakituObjCreateAll();
    m213_LowFlyerObjCreateAll();
    m213_MidFlyerObjCreateAll();
    m213_HighFlyerObjCreateAll();
    m213_CloudObjCreateAll();
    m213_CoverObjCreate();
}

void m213_MainObjInit(omObjData *obj) {
    m213_ObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    obj->func = m213_MainObjMain;
    omAddObj(0x32, 0, 0, -1, m213_CameraViewObjMain);
    omAddObj(0x320, 0, 0, -1, m213_SeqStartObjMain);
}

void m213_Dummy(void) {
}

void m213_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    CamSetupMapCullAddMulti(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, m213_cameraViewTbl[i].scissorX, m213_cameraViewTbl[i].scissorY,
                   m213_cameraViewTbl[i].scissorWidth, m213_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m213_cameraViewTbl[i].viewportScale.x, m213_cameraViewTbl[i].viewportScale.y,
                    m213_cameraViewTbl[i].viewportScale.z, m213_cameraViewTbl[i].viewportTranslate.x,
                    m213_cameraViewTbl[i].viewportTranslate.y, m213_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m213_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m213_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(100);
    omInitObjMan(100, 0);
    omGameSysInit();
    m213_CameraInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 255, 255, 255);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m213_fontMesTbl, 0);
    GMesFontMesCreate(m213_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m213_MainObjInit);
    omAddObj(1000, 0, 0, -1, m213_ExitCheckObjMain);
    m213_ObjWorkInit();
}

const s16 m213_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
