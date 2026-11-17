#include "common.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define WRAP_ANGLE(angle) \
    ((angle) >= 360.0f ? (angle) - 360.0f : ((angle) < 0.0f ? (angle) + 360.0f : (angle)))

typedef struct SnowballSummitCamera {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} SnowballSummitCamera; // sizeof 0x2C

typedef struct SnowballSummitBackBallPath {
    /* 0x00 */ Vec start;
    /* 0x0C */ Vec end;
} SnowballSummitBackBallPath; // sizeof 0x18

typedef struct SnowballSummitBackdrop {
    /* 0x00 */ s32 state; // -1 when not drawn
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 hookId;
    /* 0x0C */ HuSprAnimData *leftSprite;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ HuSprAnimData *rightSprite;
} SnowballSummitBackdrop; // sizeof 0x18

typedef struct SnowballSummitBurst {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the snowball is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ omObjData *unk_18; // minigame object that owns the slot
} SnowballSummitBurst;      // sizeof 0x1C

typedef struct SnowballSummitBall {
    /* 0x00 */ s32 id; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10; // index into m240_playerWorkTbl of the object that owns the slot
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38; // sound effect id, -1 when unset
    /* 0x3C */ omObjData *unk_3C;
} SnowballSummitBall; // sizeof 0x40

typedef struct SnowballSummitPuff {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the roll is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ omObjData *unk_14; // minigame object that owns the slot
} SnowballSummitPuff;          // sizeof 0x18

typedef struct SnowballSummitBallMakeEff {
    /* 0x00 */ s32 id;       // -1 when the slot is unused
    /* 0x04 */ void *unk_04; // minigame object that owns the slot
} SnowballSummitBallMakeEff;  // sizeof 0x8

typedef struct SnowballSummitBackBall {
    /* 0x00 */ s32 state; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} SnowballSummitBackBall; // sizeof 0x18

typedef struct SnowballSummitPlayer {
    /* 0x00 */ s32 id;     // -1 when the slot is unused
    /* 0x04 */ s32 unk_04; // 0 while unused, otherwise the selected model variant
    /* 0x08 */ s32 unk_08; // one of the owner's player flags
    /* 0x0C */ s32 unk_0C; // player id this mover belongs to
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 posX;
    /* 0x1C */ f32 posY;
    /* 0x20 */ f32 posZ;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 spawnPosX;
    /* 0x34 */ f32 spawnPosY;
    /* 0x38 */ f32 spawnPosZ;
    /* 0x3C */ s32 unk_3C; // 0, or 1..3 while the mover is animating
    /* 0x40 */ s32 unk_40; // 3d model handle
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48; // 3d model handle
    /* 0x4C */ s32 unk_4C; // index of the owning object
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ s32 unk_58;    // set when colliding with another mover
    /* 0x5C */ s32 unk_5C[4]; // per-player collision flags
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70; // -1 when unset, else an index into m240_ballTbl
    /* 0x74 */ s32 unk_74;
    /* 0x78 */ omObjData *unk_78; // minigame object that owns the slot
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s16 unk_94;
    /* 0x96 */ s16 unk_96;
    /* 0x98 */ f32 unk_98;
} SnowballSummitPlayer; // sizeof 0x9C

typedef struct SnowballSummitRollEff {
    /* 0x00 */ s32 id; // -1 when the slot is unused, 0 when the node is dead, 1 when it is in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08; // sound effect id, -1 when unset
    /* 0x0C */ omObjData *unk_0C;
} SnowballSummitRollEff; // sizeof 0x10

extern s32 omCharModelNoTbl[][6];

SnowballSummitBackBallPath m240_backBallPathTbl[3] = {
    { { -50.0f, 500.0f, -800.0f }, { -1200.0f, -330.0f, -800.0f } },
    { { 700.0f, 500.0f, -800.0f }, { -900.0f, -375.0f, -800.0f } },
    { { 1100.0f, 500.0f, -800.0f }, { 200.0f, -350.0f, -800.0f } },
};
// x: trans.x, y: trans.z, z: rot.y
Vec m240_startPosTbl[4] = {
    { -400.0f, -400.0f, 45.0f },
    { 400.0f, -400.0f, 315.0f },
    { 400.0f, 400.0f, 225.0f },
    { -400.0f, 400.0f, 135.0f },
};
s32 m240_ambientSeNo = -1;
SnowballSummitCamera m240_cameraViewTbl[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 24.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 24.0f },
};

extern const s16 m240_fontMesTbl[];

s32 m240_phase BSS;
s32 m240_phaseStep BSS;
u16 m240_cameraSetF BSS;
s32 m240_phaseTimer BSS;
s16 m240_backBallMdl BSS;
u8 m240_backBallAnim BSS;
u8 m240_backBallAnimPad[4] BSS; /* Unreferenced. */
s32 m240_hitTimerTbl[4] BSS;
s32 m240_startPosNo BSS;
s16 m240_ballMdl BSS;
s16 m240_ballMakeEffMdl BSS;
s16 m240_rollEffMdl BSS;
u8 m240_rollEffMdlPad[0xC] BSS; /* Unreferenced. */
SnowballSummitBackdrop m240_backdrop BSS;
// m240_BackdropObjInit accesses the backdrop fields as separate symbols.
extern s32 m240_backdropState;                    // m240_backdrop.state
extern s32 m240_backdropHookId;                    // m240_backdrop.hookId
extern s16 m240_backdropHookMdl;                    // m240_backdrop.hookId (low half)
extern HuSprAnimData *m240_backdropLeftSpr; // m240_backdrop.leftSprite
extern HuSprAnimData *m240_backdropRightSpr; // m240_backdrop.rightSprite
SnowballSummitBurst m240_burstTbl[8] BSS;
SnowballSummitPlayer m240_playerWorkTbl[4] BSS;
u8 m240_playerWorkTblPad[8] BSS; /* Unreferenced. */
SnowballSummitBall m240_ballTbl[16] BSS;
s16 m240_snowMdl BSS;
u8 m240_snowMdlPad[0x10] BSS; /* Unreferenced. */
s32 m240_winnerF BSS;
SnowballSummitPuff m240_puffTbl[16] BSS;
SnowballSummitBallMakeEff m240_ballMakeEffTbl[4] BSS;
s32 m240_unusedF BSS;
u8 m240_unusedFPad[4] BSS; /* Unreferenced. */
s16 m240_hudSprGrp BSS;
u16 m240_hudSpr BSS;
f32 m240_hudX BSS;
f32 m240_hudY BSS;
u8 m240_hudYPad[4] BSS; /* Unreferenced. */
SnowballSummitBackBall m240_backBallTbl[3] BSS;
s32 m240_unusedNo BSS;
s32 m240_ballSeF BSS;
SnowballSummitRollEff m240_rollEffTbl[4] BSS;
u8 m240_rollEffTblPad[0x10] BSS; /* Unreferenced. */

void m240_ObjectSetup(void);
void m240_BackdropDraw(Gfx **gfxPos, s32 arg1, s32 arg2);
void m240_BackdropObjMain(omObjData *object);
void m240_PlayerObjInit(omObjData *object);
void m240_PuffObjMain(omObjData *object);
void m240_SeqFinishObjMain(omObjData *object);
void m240_BallMakeEffObjMain(omObjData *object);
void m240_RollEffObjMain(omObjData *object);
void m240_BurstObjMain(omObjData *object);
void m240_MainObjMain(omObjData *object);
void m240_BallObjMain(omObjData *object);
s32 m240_BallCreate(omObjData *object);
void m240_HudObjInit(omObjData *);
void m240_PuffObjInit(omObjData *);
void m240_BackdropObjInit(omObjData *);
void m240_StageObjInit(omObjData *);
void m240_MountainObjInit(omObjData *);
void m240_BackBallObjInit(omObjData *);
void m240_BackBallObjMain(omObjData *object);
void m240_PlayerSpeedUpdate(omObjData *object, Vec stick);
void m240_PlayerObjMain(omObjData *object);
void m240_PlayerBallRelease(omObjData *object);
void m240_PlayerMoveUpdate(void);
void m240_PlayerComInput(omObjData *object);
void m240_BurstObjInit(omObjData *);
void m240_SnowObjInit(omObjData *);
void m240_SnowObjMain(omObjData *);
void m240_SeqSettleWaitObjMain(omObjData *);
void m240_BallObjInit(omObjData *);
void m240_SeqTimerObjMain(omObjData *);
void m240_SeqStartWaitObjMain(omObjData *);
void m240_BallMakeEffObjInit(omObjData *);
void m240_RollEffObjInit(omObjData *);

void m240_Executor(void) {
    m240_ObjectSetup();
}

Gfx **m240_GfxRectTexInit(Gfx **gfxPos) {
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

Gfx **m240_GfxRectXluInit(Gfx **gfxPos) {
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

Gfx **m240_GfxPrimAlphaSet(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

void m240_PadClear(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

f32 m240_ArcTanCalc(f32 value) {
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

void m240_PolarCalc(Vec *position, Vec *target, Vec *result) {
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
            yaw = m240_ArcTanCalc(difference.x / difference.z) * 57.2957795130823229;
        } else if (difference.z == 0.0f) {
            yaw = difference.x >= 0.0f ? 90.0f : 270.0f;
        } else {
            yaw = 0.0f;
        }
        if (difference.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontalDistance != 0.0f && difference.y != 0.0f) {
            pitch = m240_ArcTanCalc(difference.y / horizontalDistance) * 57.2957795130823229;
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

void m240_TextPrint(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

f32 m240_AngleCalc(f32 y, f32 x) {
    f32 angle = atan2df(y, x);

    if (angle > 360.0) {
        angle -= 360.0;
    } else if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

void m240_HudObjMain(omObjData *object) {
    espPosSet(m240_hudSpr, m240_hudX, m240_hudY);
}

void m240_HudObjInit(omObjData *object) {
    m240_hudX = 160.0f;
    m240_hudY = 33.0f;
    m240_hudSprGrp = HuSprAnimDataRead(0x490002);
    m240_hudSpr = espEntry(m240_hudSprGrp, 0, 0);
    espAttrSet(m240_hudSpr, 0x5000);
    espPosSet(m240_hudSpr, m240_hudX, m240_hudY);
    object->func = m240_HudObjMain;
}

void m240_HudObjCreate(void) {
    omAddObj(0x96, 1, 0, -1, m240_HudObjInit);
}

void m240_BackdropDraw(Gfx **gfxPos, s32 arg1, s32 arg2) {
    SnowballSummitBackdrop *backdrop = (SnowballSummitBackdrop *)&m240_backdropState;
    Gfx *gfx;
    s32 y;

    if (backdrop->state == -1) {
        return;
    }
    gfxPos = m240_GfxRectTexInit(gfxPos);
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, backdrop->leftSprite->pal);
    for (y = 0; y < 110; y += 10) {
        gDPLoadTextureTile(gfx++, backdrop->leftSprite->data, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 110,
                           0, y, 104, y + 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
        gSPTextureRectangle(gfx++, 0 << 2, (y + 66) << 2, 104 << 2, (y + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, backdrop->rightSprite->pal);
    for (y = 0; y < 110; y += 10) {
        gDPLoadTextureTile(gfx++, backdrop->rightSprite->data, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 110,
                           0, y, 104, y + 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
        gSPTextureRectangle(gfx++, 216 << 2, (y + 66) << 2, 320 << 2, (y + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfxPos = gfx;
}

void m240_BackdropObjMain(omObjData *object) {
}

void m240_BackdropObjInit(omObjData *object) {
    m240_backdropLeftSpr = HuSprAnimDataGet(HuSprAnimDataRead(0x490000));
    m240_backdropRightSpr = HuSprAnimDataGet(HuSprAnimDataRead(0x490001));
    m240_backdropHookId = Hu3DHookFuncCreate(0, m240_BackdropDraw, 2);
    Hu3DModelCameraSet(m240_backdropHookMdl, HU3D_CAM0);
    m240_backdropState = 0;
    object->func = m240_BackdropObjMain;
}

void m240_BackdropObjCreate(void) {
    omObjData *object = omAddObj(0xA0, 1, 0, -1, m240_BackdropObjInit);
    object->work[0] = 0;
}

void m240_StageObjMain(omObjData *object) {
}

void m240_StageObjInit(omObjData *this) {
    *this->model = Hu3DModelRead(0x490003, 0x2B9);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 20.0f;
    Hu3DModelCameraSet(*this->model, HU3D_CAM1);
    this->func = m240_StageObjMain;
}

void m240_StageObjCreate(void) {
    omAddObj(0xC8, 1, 0, -1, m240_StageObjInit);
}

void m240_MountainObjMain(omObjData *object) {
}

void m240_MountainObjInit(omObjData *this) {
    *this->model = Hu3DModelRead(0x490006, 0x2B9);
    Hu3DMotionAttrSet(*this->model, 2, 2);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 0.0f;
    Hu3DModelCameraSet(*this->model, HU3D_CAM0);
    this->func = m240_MountainObjMain;
}

void m240_MountainObjCreate(void) {
    omAddObj(0xAA, 1, 1, -1, m240_MountainObjInit);
}

void m240_BackBallObjMain(omObjData *object) {
    SnowballSummitBackBall *throw = &m240_backBallTbl[object->work[0]];
    s32 variant;

    if (throw->state == -1) {
        return;
    }

    switch (throw->state) {
        case 0:
            if (throw->unk_04 > 0) {
                throw->unk_04--;
            } else {
                throw->state = 1;
            }
            break;
        case 1:
            variant = rand8() & 1;
            Hu3DModelAttrSet(object->model[variant], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(object->model[variant ^ 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            object->trans.x = m240_backBallPathTbl[object->work[0]].start.x;
            object->trans.y = m240_backBallPathTbl[object->work[0]].start.y;
            object->trans.z = m240_backBallPathTbl[object->work[0]].start.z;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            throw->unk_08 = (u8)(rand8() % 15) + 30;
            throw->unk_04++;
            throw->state = 2;
            break;
        case 2:
            throw->unk_0C = (m240_backBallPathTbl[object->work[0]].end.x - m240_backBallPathTbl[object->work[0]].start.x) / throw->unk_08 * throw->unk_04;
            throw->unk_10 = (m240_backBallPathTbl[object->work[0]].end.y - m240_backBallPathTbl[object->work[0]].start.y) / throw->unk_08 * throw->unk_04;
            throw->unk_14 = (m240_backBallPathTbl[object->work[0]].end.z - m240_backBallPathTbl[object->work[0]].start.z) / throw->unk_08 * throw->unk_04;
            object->trans.x = m240_backBallPathTbl[object->work[0]].start.x + throw->unk_0C;
            object->trans.y = m240_backBallPathTbl[object->work[0]].start.y + throw->unk_10;
            object->trans.z = m240_backBallPathTbl[object->work[0]].start.z + throw->unk_14;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            if (throw->unk_04 >= throw->unk_08) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                throw->state = 0;
                throw->unk_04 = (u8)(rand8() % 60) + 150;
                throw->unk_0C = throw->unk_10 = throw->unk_14 = 0.0f;
            } else {
                throw->unk_04++;
            }
            break;
    }
}

void m240_BackBallObjInit(omObjData *object) {
    SnowballSummitBackBall *throw;
    void *data;

    if (object->work[0] == 0) {
        object->model[0] = m240_backBallMdl = Hu3DModelRead(0x490007, 0x2B9);
        object->model[1] = Hu3DModelRead(0x490007, 0x2A9);
        data = DataRead(0x490008);
        object->work[1] = m240_backBallAnim = Hu3DAnimCreate(Hu3DData[object->model[1]].hmf, data, 0, "s240_002_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        object->model[0] = Hu3DModelLink(m240_backBallMdl);
        object->model[1] = Hu3DModelRead(0x490007, 0x2A9);
        object->work[1] = Hu3DAnimLink(Hu3DData[object->model[1]].hmf, m240_backBallAnim, 0, "s240_002_DEF");
    }
    Hu3DAnimAttrSet(object->work[1], 1, 1);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = m240_backBallPathTbl[object->work[0]].start.x;
    object->trans.y = m240_backBallPathTbl[object->work[0]].start.y;
    object->trans.z = m240_backBallPathTbl[object->work[0]].start.z;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    throw = &m240_backBallTbl[object->work[0]];
    throw->state = 0;
    throw->unk_04 = (u8)(rand8() % 60) + 150;
    throw->unk_0C = throw->unk_10 = throw->unk_14 = 0.0f;
    object->func = m240_BackBallObjMain;
}

void m240_BackBallObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        omAddObj(0xB4, 2, 0, -1, m240_BackBallObjInit)->work[0] = i;
    }
}

void m240_PuffEmit(omObjData *object, s32 arg1, f32 arg2, f32 arg3, f32 x, f32 y, f32 z) {
    s32 i;
    SnowballSummitPuff *roll;

    for (i = 0; i < ARRAY_COUNT(m240_puffTbl); i++) {
        roll = &m240_puffTbl[i];
        if (roll->state == 0) {
            roll->state = 1;
            roll->unk_14->trans.x = x + object->trans.x;
            roll->unk_14->trans.y = y + object->trans.y;
            roll->unk_14->trans.z = z + object->trans.z;
            roll->unk_08 = arg1;
            roll->unk_10 = arg2;
            roll->unk_0C = arg3;
            break;
        }
    }
}

void m240_PuffObjMain(omObjData *object) {
    SnowballSummitPuff *roll = &m240_puffTbl[object->work[0]];

    if (roll->state == -1) {
        return;
    }

    switch (roll->state) {
        case 0:
            break;
        case 1:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            roll->state = 2;
            break;
        case 2:
            roll->unk_04 -= roll->unk_08;
            if (roll->unk_04 > 0) {
                Hu3DModelTPLvlSet(object->model[0], roll->unk_04);
                object->scale.x += roll->unk_10;
                object->scale.y += roll->unk_10;
                object->scale.z += roll->unk_10;
            } else {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                roll->state = 0;
                roll->unk_04 = 255;
                roll->unk_08 = 0;
                roll->unk_10 = 0;
                object->scale.x = object->scale.y = object->scale.z = 1.0f;
                Hu3DModelTPLvlSet(object->model[0], 255);
            }
            break;
    }
}

void m240_PuffObjInit(omObjData *object) {
    SnowballSummitPuff *roll;

    object->model[0] = Hu3DModelRead(0x490009, 0x289);
    Hu3DModelTPLvlInit(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], 255);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = m240_PuffObjMain;
    roll = &m240_puffTbl[object->work[0]];
    roll->state = 0;
    roll->unk_04 = 255;
    roll->unk_08 = 0;
    roll->unk_0C = 1.6f;
    roll->unk_10 = 0.0f;
    roll->unk_14 = object;
}

void m240_PuffObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x1F4, 1, 0, -1, m240_PuffObjInit)->work[0] = i;
    }
}

void m240_BurstEmit(omObjData *object, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 x, f32 y, f32 z) {
    s32 i;
    SnowballSummitBurst *snowball;

    for (i = 0; i < ARRAY_COUNT(m240_burstTbl); i++) {
        snowball = &m240_burstTbl[i];
        if (snowball->state == 0) {
            snowball->state = 1;
            snowball->unk_18->trans.x = x + object->trans.x;
            snowball->unk_18->trans.y = y + object->trans.y;
            snowball->unk_18->trans.z = z + object->trans.z;
            snowball->unk_08 = arg1;
            snowball->unk_10 = arg2;
            snowball->unk_0C = arg4;
            snowball->unk_14 = arg3;
            break;
        }
    }
}

void m240_BurstObjMain(omObjData *object) {
    SnowballSummitBurst *snowball = &m240_burstTbl[object->work[0]];

    if (snowball->state == -1) {
        return;
    }

    switch (snowball->state) {
        case 0:
            break;
        case 1:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionAttrSet(object->model[0], 1, 0);
            object->scale.x = object->scale.y = object->scale.z = snowball->unk_14;
            snowball->state = 2;
            break;
        case 2:
            snowball->unk_04 -= snowball->unk_08;
            if (snowball->unk_04 > 0) {
                if (snowball->unk_04 < 255) {
                    Hu3DModelTPLvlSet(object->model[0], snowball->unk_04);
                } else {
                    Hu3DModelTPLvlSet(object->model[0], 255);
                }
                if (object->scale.x < snowball->unk_0C) {
                    object->scale.x += snowball->unk_10;
                    object->scale.y += snowball->unk_10;
                    object->scale.z += snowball->unk_10;
                }
            } else {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(object->model[0], 0);
                Hu3DMotionAttrSet(object->model[0], 1, 1);
                snowball->state = 0;
                snowball->unk_04 = 450;
                snowball->unk_08 = 0;
                snowball->unk_10 = 0;
                object->scale.x = object->scale.y = object->scale.z = 0.5f;
                Hu3DModelTPLvlSet(object->model[0], 255);
            }
            break;
    }
}

void m240_BurstObjInit(omObjData *object) {
    SnowballSummitBurst *snowball;

    object->model[0] = Hu3DModelRead(0x49000A, 0x1689);
    Hu3DModelTPLvlInit(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], 255);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    Hu3DMotionTimeSet(object->model[0], 0);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.7f;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = m240_BurstObjMain;
    snowball = &m240_burstTbl[object->work[0]];
    snowball->state = 0;
    snowball->unk_04 = 450;
    snowball->unk_08 = 0;
    snowball->unk_0C = 0.7f;
    snowball->unk_10 = 0.0f;
    snowball->unk_18 = object;
}

void m240_BurstObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        omAddObj(0x258, 1, 1, -1, m240_BurstObjInit)->work[0] = i;
    }
}

void m240_SnowObjMain(omObjData *this) {
    s16 *model = &m240_snowMdl;
    f32 x;
    f32 z;
    s32 i;

    for (i = 0; i < 4; i++) {
        do {
            x = (rand8() - 128) * 12;
            z = i * 720 - 700;
        } while (!(x * x + z * z < 1.0e8f));
        EffectEmit(*model, x, i * 180 + 1000, z);
    }
}

void m240_SnowObjInit(omObjData *this) {
    s16 *model = &m240_snowMdl;

    *model = EffectModelCreate(0x49000D, 0x2A9);
    EffectParamSet(*model, 15.0f, 110.0f, 8.0f);
    Hu3DModelCameraSet(*model, HU3D_CAM1);
    this->func = m240_SnowObjMain;
}

void m240_SnowObjCreate(void) {
    omAddObj(0x3DE, 1, 0, -1, m240_SnowObjInit);
}

void m240_PolarXZCalc(f32 targetX, f32 targetZ, f32 posX, f32 posZ, Vec *result) {
    Vec position;
    Vec target;

    target.x = targetX;
    target.y = 0.0f;
    target.z = targetZ;
    position.x = posX;
    position.y = 0.0f;
    position.z = posZ;
    m240_PolarCalc(&position, &target, result);
}

void m240_PolarXYZCalc(f32 targetX, f32 targetY, f32 targetZ, f32 posX, f32 posY, f32 posZ, Vec *result) {
    Vec position;
    Vec target;

    target.x = targetX;
    target.y = targetY;
    target.z = targetZ;
    position.x = posX;
    position.y = posY;
    position.z = posZ;
    m240_PolarCalc(&position, &target, result);
}

s32 m240_TurnDirGet(f32 arg0, f32 arg1, f32 arg2) {
    f32 angle = arg1 - arg0;

    if (angle < 0.0f) {
        angle += 360.0f;
    }

    if (angle < arg2) {
        return 0;
    }

    if (360.0f - arg2 < angle) {
        return 0;
    }

    if (180.0f <= angle) {
        return -1;
    }

    return 1;
}

void m240_PlayerTurnUpdate(omObjData *object, Vec stick, f32 speed) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    s32 direction = m240_TurnDirGet(object->rot.y, stick.z, speed);
    f32 angle;

    switch (mover->unk_04) {
        case 0:
        case 1:
        case 3:
        case 4:
            if (direction != 0) {
                if (speed * direction + object->rot.y >= 360.0f) {
                    angle = speed * direction + object->rot.y - 360.0f;
                } else {
                    angle = object->rot.y + speed * direction;
                    if (angle < 0.0f) {
                        angle += 360.0f;
                    }
                }
                object->rot.y = angle;
            } else {
                object->rot.y = stick.z;
            }
            break;
    }
    mover->posX = object->rot.y;
}

void m240_PlayerSpeedUpdate(omObjData *object, Vec stick) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    SnowballSummitBall *slot;
    f32 velocity;
    f32 scaled;

    if (stick.x > 70.0f) {
        velocity = 7.0f;
    } else {
        velocity = stick.x * 0.1;
    }
    mover->unk_10 = velocity;
    if (mover->unk_70 != -1) {
        slot = &m240_ballTbl[mover->unk_70];
        scaled = velocity * 0.6;
        mover->unk_10 = velocity * 0.4 + scaled * (1.0f / slot->unk_0C);
    }
    mover->posZ = sindf(object->rot.y) * mover->unk_10;
    mover->unk_28 = cosdf(object->rot.y) * mover->unk_10;
    mover->spawnPosX = object->trans.x + mover->posZ;
    mover->spawnPosZ = object->trans.z + mover->unk_28;
}

void m240_PlayerMotSet(omObjData *object, s32 motion) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    Hu3DMotionModelSet(object->model[0], object->motion[motion]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    mover->unk_04 = motion;
}

void m240_PlayerMotShiftSet(omObjData *object, s32 motion, s16 start, s16 end) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[motion]].motId, start, end, 2);
    mover->unk_04 = motion;
}

void m240_ComTimerSet(SnowballSummitPlayer *mover) {
    switch (mover->unk_0C) {
        case 0:
            mover->unk_90 = (u8)(rand8() % 31) + 60;
            break;
        case 1:
            mover->unk_90 = (u8)(rand8() % 31) + 48.0;
            break;
        case 2:
            mover->unk_90 = (u8)(rand8() % 31) + 36.0;
            break;
        default:
            mover->unk_90 = (u8)(rand8() % 31) + 24.0;
            break;
    }
}

s32 m240_ComTimeGet(SnowballSummitPlayer *mover) {
    switch (mover->unk_0C) {
        case 0:
            return (u8)(rand8() % 31) + 60;
        case 1:
            return (u8)(rand8() % 31) + 48.0;
        case 2:
            return (u8)(rand8() % 31) + 36.0;
        default:
            return (u8)(rand8() % 31) + 24.0;
    }
}

void m240_PlayerComInput(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    SnowballSummitPlayer *other;
    SnowballSummitBall *slot;
    omObjData *target;
    Vec result;
    f32 angle;
    f32 offset;
    f32 maxDistSq;
    s32 i;

    m240_PadClear(object->work[0]);
    if (mover->unk_70 != -1 && mover->unk_8C == 1) {
        mover->unk_8C = 0;
        mover->unk_94 = sindf(WRAP_ANGLE(rand16() % 360)) * 70.0f;
        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(rand16() % 360)) * 70.0f);
        HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
        HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
        m240_ComTimerSet(mover);
        return;
    }

    if (mover->unk_8C != 0) {
        if (rand8() < mover->unk_7C && rand8() < mover->unk_7C) {
            HuPadBtnDown[GwPlayer[object->work[0]].pad] |= B_BUTTON;
        }
    }

    if (mover->unk_8C == 0) {
        maxDistSq = 590.0f * 590.0f;
        if (object->trans.x * object->trans.x + object->trans.z * object->trans.z > maxDistSq) {
            m240_ComTimerSet(mover);
            angle = m240_AngleCalc(object->trans.x, object->trans.z);
            offset = 180.0 - m240_ComTimeGet(mover) * 0.5;
            mover->unk_94 = sindf(WRAP_ANGLE(angle + offset + m240_ComTimeGet(mover))) * 70.0f;
            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(angle + offset + m240_ComTimeGet(mover))) * 70.0f);
            HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
            HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
            return;
        }
    }

    if (mover->unk_70 == -1) {
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
                slot = &m240_ballTbl[i];
                if (slot->id > 0) {
                    target = slot->unk_3C;
                    m240_PolarXZCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80 && rand8() % mover->unk_88 != 0) {
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f);
                        HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        mover->unk_8C = 0;
                        m240_ComTimerSet(mover);
                        return;
                    }
                }
            }
        }
        if (mover->unk_8C == 0 && mover->unk_70 == -1 && mover->unk_90 == 0 && rand8() % mover->unk_7C != 0) {
            mover->unk_8C = 1;
            HuPadStkX[GwPlayer[object->work[0]].pad] = HuPadStkY[GwPlayer[object->work[0]].pad] = 0;
            mover->unk_94 = mover->unk_96 = 0;
            HuPadBtnDown[GwPlayer[object->work[0]].pad] |= B_BUTTON;
            return;
        }
    } else {
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
                slot = &m240_ballTbl[i];
                if (slot->id > 0 && i != mover->unk_70) {
                    target = slot->unk_3C;
                    m240_PolarXZCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80) {
                        if (rand8() % mover->unk_88 != 0) {
                            if (rand8() % mover->unk_88 != 0) {
                                mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                                mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                            } else {
                                mover->unk_94 = sindf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f;
                                mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f);
                            }
                            HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
                            HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
                            m240_ComTimerSet(mover);
                            return;
                        }
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                        HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        m240_ComTimerSet(mover);
                        if (m240_TurnDirGet(object->rot.y, WRAP_ANGLE(result.z + 180.0f), 20.0f) == 0) {
                            HuPadBtnDown[GwPlayer[object->work[0]].pad] |= A_BUTTON;
                            if (rand8() % mover->unk_88 != 0) {
                                mover->unk_8C = 1;
                                HuPadStkX[GwPlayer[object->work[0]].pad] = HuPadStkY[GwPlayer[object->work[0]].pad] = 0;
                                mover->unk_94 = mover->unk_96 = 0;
                                HuPadBtnDown[GwPlayer[object->work[0]].pad] |= B_BUTTON;
                                mover->unk_90 = 0;
                                return;
                            }
                        }
                    }
                }
            }
        }
        for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
            if (i == object->work[0]) {
                continue;
            }
            other = &m240_playerWorkTbl[i];
            if (other->id >= 0 && other->id < 90) {
                target = other->unk_78;
                m240_PolarXZCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                if (m240_TurnDirGet(object->rot.y, WRAP_ANGLE(result.z + 180.0f), 15.0f) == 0 && mover->unk_98 < m240_ballTbl[mover->unk_70].unk_0C && rand8() % mover->unk_88 != 0) {
                    HuPadBtnDown[GwPlayer[object->work[0]].pad] |= A_BUTTON;
                    if (rand8() % mover->unk_88 != 0) {
                        mover->unk_8C = 1;
                        HuPadStkX[GwPlayer[object->work[0]].pad] = HuPadStkY[GwPlayer[object->work[0]].pad] = 0;
                        mover->unk_94 = mover->unk_96 = 0;
                        HuPadBtnDown[GwPlayer[object->work[0]].pad] |= B_BUTTON;
                        mover->unk_90 = 0;
                        return;
                    }
                }
            }
        }
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
                if (i == object->work[0]) {
                    continue;
                }
                other = &m240_playerWorkTbl[i];
                if (other->id >= 0 && other->id < 90 && other->unk_08 == 0) {
                    target = other->unk_78;
                    if (rand8() % mover->unk_84 == 0) {
                        m240_PolarXZCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                        if (ABS(result.x) < mover->unk_80 * 2 && rand8() % mover->unk_88 == 0) {
                            mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                            HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
                            HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
                            m240_ComTimerSet(mover);
                            return;
                        }
                    }
                }
            }
            for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
                if (i == object->work[0]) {
                    continue;
                }
                other = &m240_playerWorkTbl[i];
                if (other->id >= 0 && other->id < 90) {
                    target = other->unk_78;
                    m240_PolarXZCalc(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80 * 2) {
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                        HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        m240_ComTimerSet(mover);
                        return;
                    }
                }
            }
        }
    }

    if (mover->unk_8C == 0) {
        if (mover->unk_90 > 0) {
            mover->unk_90--;
            HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
            HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
        } else {
            mover->unk_94 = sindf(WRAP_ANGLE(rand16() % 360)) * 70.0f;
            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(rand16() % 360)) * 70.0f);
            HuPadStkX[GwPlayer[object->work[0]].pad] = mover->unk_94;
            HuPadStkY[GwPlayer[object->work[0]].pad] = mover->unk_96;
            m240_ComTimerSet(mover);
        }
    }
}

void m240_PlayerWalkUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    Vec stick;

    switch (mover->unk_04) {
        case 0:
        case 2:
            if (mover->unk_70 != -1) {
                m240_PlayerMotSet(object, 3);
            } else {
                m240_PlayerMotSet(object, 1);
            }
            break;
        case 5:
        case 6:
            if (Hu3DData[object->model[0]].motTime >= Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - 2) {
                m240_PlayerMotSet(object, 1);
            } else {
                mover->unk_10 = 0;
                mover->posZ = mover->unk_28 = mover->unk_10;
            }
            break;
        case 3:
        case 4:
            if (mover->unk_70 == -1) {
                m240_PlayerMotShiftSet(object, 1, 0, 10);
            } else {
                if (mover->unk_04 == 3 && m240_ballTbl[mover->unk_70].unk_0C >= 1.7) {
                    m240_PlayerMotShiftSet(object, 4, 12, 6);
                }
                Hu3DMotionAttrSet(object->model[0], 2, 2);
                Hu3DMotionAttrSet(object->model[0], 1, 0);
            }
            break;
    }

    m240_PolarXZCalc(HuPadStkX[GwPlayer[object->work[0]].pad], -HuPadStkY[GwPlayer[object->work[0]].pad], 0.0f, 0.0f, &stick);
    if (mover->unk_70 == -1) {
        m240_PlayerTurnUpdate(object, stick, 30.0f);
    } else {
        m240_PlayerTurnUpdate(object, stick, 1.0f / (m240_ballTbl[mover->unk_70].unk_0C * m240_ballTbl[mover->unk_70].unk_0C) * 30.0f);
    }
    if (mover->unk_04 != 5 && mover->unk_04 != 6) {
        m240_PlayerSpeedUpdate(object, stick);
    }
    if (mover->unk_48 == 0) {
        mover->unk_40 = 0;
        mover->unk_44 = 0;
    }
}

void m240_PlayerIdleUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    Vec stick;

    switch (mover->unk_04) {
        case 1:
            m240_PlayerMotSet(object, 0);
            break;
        case 2:
            if (mover->unk_40 > 0) {
                break;
            }
            if (mover->unk_48 == 0) {
                m240_PlayerMotShiftSet(object, 0, 0, 10);
                break;
            }
            m240_PlayerMotShiftSet(object, 3, 12, 10);
            Hu3DMotionTimeSet(object->model[0], 12.0f);
            Hu3DMotionAttrSet(object->model[0], 2, 0);
            Hu3DMotionAttrSet(object->model[0], 1, 1);
            break;
        case 3:
        case 4:
            if (mover->unk_70 == -1) {
                m240_PlayerMotShiftSet(object, 0, 0, 10);
                break;
            }
            if (mover->unk_04 == 3 && m240_ballTbl[mover->unk_70].unk_0C >= 1.7) {
                m240_PlayerMotShiftSet(object, 4, 12, 3);
            }
            Hu3DMotionTimeSet(object->model[0], 12.0f);
            Hu3DMotionAttrSet(object->model[0], 2, 0);
            Hu3DMotionAttrSet(object->model[0], 1, 1);
            break;
        case 5:
        case 6:
            if (Hu3DData[object->model[0]].motTime >= Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - 2) {
                m240_PlayerMotSet(object, 0);
            }
            break;
    }
    mover->unk_10 = 0;
    mover->posZ = mover->unk_28 = mover->unk_10;

    if (ABS(HuPadStkX[GwPlayer[object->work[0]].pad]) >= 11 || ABS(HuPadStkY[GwPlayer[object->work[0]].pad]) >= 11) {
        m240_PolarXZCalc(HuPadStkX[GwPlayer[object->work[0]].pad], -HuPadStkY[GwPlayer[object->work[0]].pad], 0.0f, 0.0f, &stick);
        if (mover->unk_70 == -1) {
            m240_PlayerTurnUpdate(object, stick, 30.0f);
        } else {
            m240_PlayerTurnUpdate(object, stick, 1.0f / (m240_ballTbl[mover->unk_70].unk_0C * m240_ballTbl[mover->unk_70].unk_0C) * 30.0f);
        }
    }
}

void m240_PlayerBallMake(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    if (ABS(HuPadStkX[GwPlayer[object->work[0]].pad]) >= 11) {
        return;
    }
    if (ABS(HuPadStkY[GwPlayer[object->work[0]].pad]) >= 11) {
        return;
    }
    if (mover->unk_04 == 5 || mover->unk_04 == 6) {
        return;
    }

    if (mover->unk_04 != 1 && mover->unk_04 != 2) {
        m240_PlayerMotSet(object, 2);
        mover->unk_10 = 0;
        mover->posZ = mover->unk_28 = mover->unk_10;
    } else if (mover->unk_04 != 2 && mover->unk_10 == 0.0f) {
        m240_PlayerMotSet(object, 2);
        mover->posZ = mover->unk_28 = mover->unk_10 = 0.0f;
    }

    mover->unk_40 = 30;
    if (++mover->unk_44 >= 10) {
        mover->unk_70 = m240_BallCreate(object);
        mover->unk_48 = 1;
        mover->unk_40 = 0;
        mover->unk_44 = 0;
        m240_PlayerMotSet(object, 3);
        Hu3DMotionTimeSet(object->model[0], 12.0f);
        if (mover->unk_08 == 0) {
            omVibrate(object->work[0], 2, 3, 10);
        }
    } else {
        HuAudPlayerFXPlay(0x438, object->work[0]);
    }
}

void m240_PlayerBallRelease(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    SnowballSummitBall *slot;
    f32 distance;

    switch (mover->unk_04) {
        case 3:
            m240_PlayerMotSet(object, 5);
            slot = &m240_ballTbl[mover->unk_70];
            distance = slot->unk_0C * 37.5 + mover->unk_50;
            slot->unk_3C->trans.x = sindf(mover->posX) * distance + object->trans.x;
            slot->unk_3C->trans.z = cosdf(mover->posX) * distance + object->trans.z;
            if (slot->id != 20) {
                slot->id = 10;
            }
            slot->unk_10 = -1;
            mover->unk_10 = 0;
            mover->posZ = mover->unk_28 = mover->unk_10;
            mover->unk_48 = 0;
            mover->unk_70 = -1;
            break;
        case 4:
            m240_PlayerMotSet(object, 6);
            slot = &m240_ballTbl[mover->unk_70];
            distance = slot->unk_0C * 37.5 + mover->unk_50;
            slot->unk_3C->trans.x = sindf(mover->posX) * distance + object->trans.x;
            slot->unk_3C->trans.z = cosdf(mover->posX) * distance + object->trans.z;
            if (slot->id != 20) {
                slot->id = 10;
            }
            slot->unk_10 = -1;
            mover->unk_10 = 0;
            mover->posZ = mover->unk_28 = mover->unk_10;
            mover->unk_48 = 0;
            mover->unk_70 = -1;
            break;
    }
}

void m240_PlayerInputUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    if (mover->unk_04 == 5 || mover->unk_04 == 6) {
        m240_PlayerIdleUpdate(object);
    } else if ((HuPadBtnDown[GwPlayer[object->work[0]].pad] & A_BUTTON) && mover->unk_48 == 1) {
        m240_PlayerBallRelease(object);
    } else if (ABS(HuPadStkX[GwPlayer[object->work[0]].pad]) >= 31 || ABS(HuPadStkY[GwPlayer[object->work[0]].pad]) >= 31) {
        m240_PlayerWalkUpdate(object);
    } else {
        m240_PlayerIdleUpdate(object);
    }

    if ((HuPadBtnDown[GwPlayer[object->work[0]].pad] & B_BUTTON) && mover->unk_48 == 0) {
        m240_PlayerBallMake(object);
    }
    if (mover->unk_48 == 0) {
        if (mover->unk_40 > 0) {
            mover->unk_40--;
        } else {
            mover->unk_44 = 0;
        }
    }
}

void m240_PlayerKnockMove(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    mover->posZ = sindf(WRAP_ANGLE(mover->posX + 180.0f)) * mover->unk_10;
    mover->unk_24 -= mover->unk_2C;
    mover->unk_28 = cosdf(WRAP_ANGLE(mover->posX + 180.0f)) * mover->unk_10;
    mover->spawnPosX = object->trans.x + mover->posZ;
    mover->spawnPosY = object->trans.y + mover->unk_24;
    mover->spawnPosZ = object->trans.z + mover->unk_28;
    if (mover->spawnPosY < 0.0f && mover->unk_4C == 0) {
        mover->unk_74 = 2;
        mover->unk_10 = mover->unk_2C = mover->posZ = mover->unk_24 = mover->unk_28 = mover->spawnPosY = 0.0f;
    }
}

void m240_PlayerKnockUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    if (mover->unk_4C != 0) {
        if (mover->unk_04 != 8) {
            m240_PlayerMotSet(object, 8);
        }
    } else if (mover->unk_74 == 1) {
        if (mover->unk_04 != 7) {
            m240_PlayerMotSet(object, 7);
            Hu3DMotionAttrSet(object->model[0], 2, 0);
            Hu3DMotionAttrSet(object->model[0], 1, 1);
        }
    } else if (mover->unk_74 == 2) {
        m240_PlayerMotSet(object, 7);
        Hu3DMotionAttrSet(object->model[0], 1, 0);
        mover->unk_74 = 3;
    } else if (mover->unk_74 == 3) {
        if (Hu3DData[object->model[0]].motTime >= Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - 2) {
            m240_PlayerMotSet(object, 0);
            mover->unk_74 = 0;
            mover->unk_3C = 0;
        }
    }
    if (mover->unk_74 == 1 && mover->unk_3C != 0) {
        m240_PlayerKnockMove(object);
    }
}

void m240_PlayerFinishUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    SnowballSummitBall *slot;

    switch (mover->unk_3C) {
        case 0:
            if (mover->unk_04 != 0) {
                m240_PlayerMotShiftSet(object, 0, 0, 10);
                if (mover->unk_70 != -1) {
                    slot = &m240_ballTbl[mover->unk_70];
                    slot->id = 20;
                    slot->unk_10 = -1;
                    mover->unk_48 = 0;
                    mover->unk_70 = -1;
                }
            }
            break;
        case 1:
            if (object->trans.y == 0.0f && mover->unk_04 != 0) {
                m240_PlayerMotShiftSet(object, 0, 0, 10);
                object->rot.y = 0.0f;
                break;
            }
            m240_PlayerKnockUpdate(object);
            break;
        case 2:
            m240_PlayerKnockUpdate(object);
            break;
        case 3:
            m240_PlayerKnockUpdate(object);
            break;
    }
    if (mover->unk_04 == 0) {
        object->rot.y = 0.0f;
    }
}

void m240_PlayerResultUpdate(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];
    s32 charBase = omCharModelNoTbl[GwPlayer[object->work[0]].chr][0];

    if (m240_winnerF != 0) {
        if (mover->unk_3C == 0 && mover->unk_04 != 9) {
            m240_PlayerMotSet(object, 9);
            Hu3DMotionAttrSet(object->model[0], 2, 0);
            HuAudCharVoicePlay(charBase | 0x2F);
        }
    } else if (mover->unk_04 != 10) {
        m240_PlayerMotSet(object, 10);
        Hu3DMotionAttrSet(object->model[0], 2, 0);
    }
}

void m240_PlayerObjMain(omObjData *object) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[object->work[0]];

    if (mover->id == -1) {
        return;
    }

    switch (m240_phase) {
        case 2:
            if (mover->unk_08 != 0) {
                m240_PlayerComInput(object);
            }
            if (mover->unk_3C == 0) {
                m240_PlayerInputUpdate(object);
            } else {
                m240_PlayerKnockUpdate(object);
            }
            break;
        case 3:
            m240_PadClear(object->work[0]);
            m240_PlayerFinishUpdate(object);
            break;
        case 4:
            m240_PadClear(object->work[0]);
            m240_PlayerResultUpdate(object);
            break;
        case 0:
        case 1:
        case 5:
            m240_PadClear(object->work[0]);
            break;
    }
}

void m240_PlayerObjInit(omObjData *object) {
    u16 character = GwPlayer[object->work[0]].chr;
    SnowballSummitPlayer *mover;

    object->model[0] = Hu3DModelRead(omCharModelNoTbl[character][0] | omCharModelNoTbl[character][1], 0x2B9);
    omObjMotionRead(object, 0, CharMotionDataNumGet(character, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(character, 1));
    omObjMotionRead(object, 2, CharMotionDataNumGet(character, 0x89));
    omObjMotionRead(object, 3, CharMotionDataNumGet(character, 0x85));
    omObjMotionRead(object, 4, CharMotionDataNumGet(character, 0x86));
    omObjMotionRead(object, 5, CharMotionDataNumGet(character, 0x87));
    omObjMotionRead(object, 6, CharMotionDataNumGet(character, 0x88));
    omObjMotionRead(object, 7, CharMotionDataNumGet(character, 0xF));
    omObjMotionRead(object, 8, CharMotionDataNumGet(character, 0x9F));
    omObjMotionRead(object, 9, CharMotionDataNumGet(character, 0x2F));
    omObjMotionRead(object, 10, CharMotionDataNumGet(character, 0x38));
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    HuTranslateF(Hu3DData[object->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    if (object->work[0] == 0) {
        m240_startPosNo = rand8() & 3;
        object->trans.x = m240_startPosTbl[m240_startPosNo].x;
        object->trans.y = 0.0f;
        object->trans.z = m240_startPosTbl[m240_startPosNo].y;
        object->rot.y = m240_startPosTbl[m240_startPosNo].z;
    } else {
        if (++m240_startPosNo >= 4) {
            m240_startPosNo = 0;
        }
        object->trans.x = m240_startPosTbl[m240_startPosNo].x;
        object->trans.y = 0.0f;
        object->trans.z = m240_startPosTbl[m240_startPosNo].y;
        object->rot.y = m240_startPosTbl[m240_startPosNo].z;
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 20.0f + 5.0f, object->trans.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    object->func = m240_PlayerObjMain;

    mover = &m240_playerWorkTbl[object->work[0]];
    mover->id = 0;
    mover->unk_04 = 0;
    mover->unk_08 = GwPlayer[object->work[0]].stat & 1;
    mover->unk_0C = GwPlayer[object->work[0]].cpu_difficulty;
    mover->unk_10 = 0.0f;
    mover->posX = 0.0f;
    mover->posY = 0.0f;
    mover->unk_40 = 30;
    mover->unk_44 = 0;
    mover->unk_48 = 0;
    mover->posZ = 0.0f;
    mover->unk_24 = 0.0f;
    mover->unk_28 = 0.0f;
    mover->unk_2C = 0.0f;
    mover->spawnPosX = object->trans.x;
    mover->spawnPosY = object->trans.y;
    mover->spawnPosZ = object->trans.z;
    mover->unk_3C = 0;
    mover->unk_4C = 0;
    mover->unk_50 = 50.0f;
    mover->unk_54 = 150.0f;
    mover->unk_6C = 0;
    mover->unk_70 = -1;
    mover->unk_74 = 0;
    mover->unk_78 = object;
    mover->unk_8C = 0;
    switch (mover->unk_0C) {
        case 0:
            mover->unk_7C = 90;
            mover->unk_80 = 200;
            mover->unk_84 = 6;
            mover->unk_88 = 4;
            mover->unk_90 = 0;
            mover->unk_96 = 0;
            mover->unk_94 = 0;
            mover->unk_98 = 1.7f;
            break;
        case 1:
            mover->unk_7C = 100;
            mover->unk_80 = 250;
            mover->unk_84 = 5;
            mover->unk_88 = 5;
            mover->unk_90 = 0;
            mover->unk_96 = 0;
            mover->unk_94 = 0;
            mover->unk_98 = 2.0f;
            break;
        case 2:
            mover->unk_7C = 120;
            mover->unk_80 = 300;
            mover->unk_84 = 4;
            mover->unk_88 = 10;
            mover->unk_90 = 0;
            mover->unk_96 = 0;
            mover->unk_94 = 0;
            mover->unk_98 = 1.7f;
            break;
        default:
            mover->unk_7C = 140;
            mover->unk_80 = 400;
            mover->unk_84 = 10;
            mover->unk_88 = 12;
            mover->unk_90 = 0;
            mover->unk_96 = 0;
            mover->unk_94 = 0;
            mover->unk_98 = 2.0f;
            break;
    }
}

void m240_PlayerObjCreateAll(void) {
    omObjData *object;
    s32 player;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = omAddObj(0x12C, 9, 0x3C, -1, m240_PlayerObjInit);
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
        object->work[0] = player;
    }
}

s32 m240_BallCreate(omObjData *object) {
    s32 i;
    SnowballSummitBall *slot;

    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot = &m240_ballTbl[i];
        if (slot->id == 0) {
            slot->id = 1;
            slot->unk_10 = object->work[0];
            return i;
        }
    }
    return -1;
}

void m240_BallObjMain(omObjData *object) {
    SnowballSummitBall *slot = &m240_ballTbl[object->work[0]];
    SnowballSummitPlayer *mover;

    if (slot->id == -1) {
        return;
    }

    if (m240_phase >= 3 && slot->id > 0 && slot->unk_18 == 0) {
        slot->id = 20;
    }

    switch (slot->id) {
        case 0:
            break;
        case 1:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            slot->unk_0C = 1.0f;
            slot->id = 2;
            break;
        case 2:
            slot->id = 3;
            break;
        case 10:
            slot->id = 11;
            break;
        case 11:
            slot->id = 12;
            break;
        case 20:
            if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                HuAudFXStop((s16)slot->unk_38);
                slot->unk_34 = 0;
                slot->unk_38 = -1;
                m240_ballSeF = 0;
            }
            m240_BurstEmit(object, 30, 0.1f, slot->unk_0C * 0.5, slot->unk_0C * 0.5 + 0.2, 0.0f, 0.0f, 0.0f);
            m240_PuffEmit(object, 40, slot->unk_0C * 0.1 * 0.5, slot->unk_0C * 1.2 * 0.5, 0.0f, 0.0f, 0.0f);
            if (slot->unk_10 != -1) {
                mover = &m240_playerWorkTbl[slot->unk_10];
                mover->unk_70 = -1;
                mover->unk_48 = 0;
                mover->unk_40 = 0;
                mover->unk_44 = 0;
            }
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            slot->id = 0;
            slot->unk_04 = 0;
            slot->unk_08 = 0;
            slot->unk_0C = 1.0f;
            slot->unk_14 = 0.0f;
            slot->unk_18 = 0;
            slot->unk_10 = -1;
            slot->unk_28 = 0;
            slot->unk_2C = 0;
            slot->unk_30 = 0;
            break;
    }
}

void m240_BallObjInit(omObjData *object) {
    SnowballSummitBall *slot;

    if (object->work[0] == 0) {
        object->model[0] = m240_ballMdl = Hu3DModelRead(0x490004, 0x16B9);
    } else {
        object->model[0] = Hu3DModelLink(m240_ballMdl);
    }
    object->model[1] = Hu3DModelRead2(0, 0x14C9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    HuTranslateF(Hu3DData[object->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y + 20.0f, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 5.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    object->func = m240_BallObjMain;
    slot = &m240_ballTbl[object->work[0]];
    slot->id = 0;
    slot->unk_04 = 0;
    slot->unk_08 = 0;
    slot->unk_0C = 1.0f;
    slot->unk_14 = 0.0f;
    slot->unk_18 = 0;
    slot->unk_3C = object;
    slot->unk_10 = -1;
    slot->unk_28 = 0;
    slot->unk_2C = 0;
    slot->unk_30 = 0;
}

void m240_BallObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x190, 2, 0, -1, m240_BallObjInit)->work[0] = i;
    }
}

void m240_BallMakeEffObjMain(omObjData *object) {
    SnowballSummitBallMakeEff *slot = &m240_ballMakeEffTbl[object->work[0]];
    SnowballSummitPlayer *mover;

    if (slot->id == -1) {
        return;
    }

    mover = &m240_playerWorkTbl[object->work[0]];
    if (mover->id == -1) {
        slot->id = 0;
    }

    switch (slot->id) {
        case 0:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (mover->unk_04 == 2) {
                slot->id = 1;
            }
            break;
        case 1:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            if (mover->unk_04 != 2) {
                slot->id = 0;
            }
            break;
    }

    object->trans.x = mover->spawnPosX;
    object->trans.y = mover->spawnPosY + 50.0f;
    object->trans.z = mover->spawnPosZ;
    object->rot.y = mover->unk_78->rot.y;
}

void m240_BallMakeEffObjInit(omObjData *object) {
    SnowballSummitPlayer *mover;
    SnowballSummitBallMakeEff *slot;

    if (object->work[0] == 0) {
        object->model[0] = m240_ballMakeEffMdl = Hu3DModelRead(0x49000C, 0x1699);
    } else {
        object->model[0] = Hu3DModelLink(m240_ballMakeEffMdl);
    }
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    mover = &m240_playerWorkTbl[object->work[0]];
    object->trans.x = mover->spawnPosX;
    object->trans.y = mover->spawnPosY + 40.0f;
    object->trans.z = mover->spawnPosZ;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = m240_BallMakeEffObjMain;
    slot = &m240_ballMakeEffTbl[object->work[0]];
    slot->id = 0;
    slot->unk_04 = object;
}

void m240_BallMakeEffObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1FE, 1, 1, -1, m240_BallMakeEffObjInit)->work[0] = i;
    }
}

void m240_RollEffObjMain(omObjData *object) {
}

void m240_RollEffObjInit(omObjData *object) {
    SnowballSummitPlayer *mover;
    SnowballSummitRollEff *node;

    if (object->work[0] == 0) {
        object->model[0] = m240_rollEffMdl = Hu3DModelRead(0x49000B, 0x1699);
    } else {
        object->model[0] = Hu3DModelLink(m240_rollEffMdl);
    }
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    mover = &m240_playerWorkTbl[object->work[0]];
    object->trans.x = mover->spawnPosX;
    object->trans.y = mover->spawnPosY + 20.0f;
    object->trans.z = mover->spawnPosZ;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = m240_RollEffObjMain;
    node = &m240_rollEffTbl[object->work[0]];
    node->id = 0;
    node->unk_04 = 0;
    node->unk_08 = -1;
    node->unk_0C = object;
}

void m240_RollEffObjCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x208, 1, 1, -1, m240_RollEffObjInit)->work[0] = i;
    }
}

void m240_SeqDoneObjMain(omObjData *arg0) {
}

void m240_SeqEndObjMain(omObjData *arg0) {
    if (m240_phaseTimer > 0) {
        m240_phaseTimer--;
    } else {
        m240_phaseStep = 1;
        arg0->func = m240_SeqDoneObjMain;
    }
}

void m240_SeqResultWaitObjMain(omObjData *arg0) {
    if (GMesStatGet() & GMES_STAT_TIMEEND) {
        m240_phaseTimer = 0x14;
        arg0->func = m240_SeqEndObjMain;
    }
}

s32 m240_WinnerGet(void) {
    s32 i = 0;
    s32 count = 0;
    s32 index = -1;
    SnowballSummitPlayer *mover = m240_playerWorkTbl;

    for (; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        if ((u32)mover[i].id < 0x5A) {
            count++;
            index = i;
        }
    }

    if (count == 1) {
        m240_winnerF = 1;
        return index;
    }
    return -1;
}

void m240_WinnerSet(s32 arg0) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[arg0];

    GwPlayer[mover->unk_78->work[0]].bonusCoin = 10;
    GMesCreate(0x16, GwPlayer[mover->unk_78->work[0]].chr);
    HuAudSeqPlay(0x65);
}

void m240_SeqResultObjMain(omObjData *object) {
    s32 index;

    if (m240_phaseTimer > 0) {
        m240_phaseTimer--;
    } else {
        index = m240_WinnerGet();
        if (index == -1) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            m240_phaseTimer = 0x90;
        } else {
            m240_WinnerSet(index);
        }
        object->func = m240_SeqResultWaitObjMain;
    }
}

void m240_SeqSettleWaitObjMain(omObjData *object) {
    s32 i;
    SnowballSummitPlayer *mover;

    if (m240_phaseTimer > 0) {
        m240_phaseTimer--;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        mover = &m240_playerWorkTbl[i];
        if (mover->id < 0) {
            continue;
        }
        if (mover->unk_4C != 0) {
            continue;
        }
        if (object->trans.y != 0.0f) {
            if (mover->unk_3C == 1) {
                break;
            }
        } else if (mover->unk_04 != 0) {
            break;
        }
    }

    if (i >= ARRAY_COUNT(m240_playerWorkTbl)) {
        m240_phaseStep = 1;
        object->func = m240_SeqResultObjMain;
    }
}

void m240_SeqFinishWaitObjMain(omObjData *arg0) {
    if (GMesStatGet() == 0) {
        m240_phaseTimer = 0xF;
        arg0->func = m240_SeqSettleWaitObjMain;
    }
}

void m240_SeqFinishObjMain(omObjData *arg0) {
    GMesCreate(0xE);
    HuAudSeqFadeOut(0x78);
    m240_phaseTimer = 0x4B;
    arg0->func = m240_SeqFinishWaitObjMain;
}

s32 m240_SurvivorCheck(void) {
    s32 i = 0;
    u32 count = 0;
    SnowballSummitPlayer *mover = m240_playerWorkTbl;

    for (; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        // unused movers have an id of -1, so compare as unsigned
        if ((u32)mover[i].id < 0x5A) {
            count++;
        }
    }

    if (count == 1) {
        return 1;
    } else if (count == 0) {
        return -1;
    }
    return 0;
}

void m240_SeqTimerObjMain(omObjData *object) {
    s32 result;

    if (m240_phaseTimer != 0) {
        m240_phaseTimer--;
        GMesTimerValueSet((m240_phaseTimer + 29) / 30);
        result = m240_SurvivorCheck();
        if (result == 1) {
            GMesTimerEnd();
            m240_phaseTimer = 90;
            object->func = m240_SeqFinishObjMain;
            m240_phaseStep = 1;
        } else if (result == -1) {
            GMesTimerEnd();
            m240_phaseTimer = 90;
            object->func = m240_SeqFinishObjMain;
            HuAudSeqFadeOut(120);
            m240_phaseStep = 1;
        }
    } else {
        GMesTimerEnd();
        object->func = m240_SeqFinishObjMain;
        HuAudSeqFadeOut(120);
        m240_phaseStep = 1;
    }
}

void m240_SeqTimerStartObjMain(omObjData *arg0) {
    GMesCreate(0x1A, 0x3C, 0xA0, 0x1C);
    m240_phaseTimer = 0x709;
    arg0->func = m240_SeqTimerObjMain;
}

void m240_SeqStartWaitObjMain(omObjData *arg0) {
    if (GMesStatGet() == 0 || GMesStatGet() & GMES_STAT_TIMEEND) {
        arg0->func = m240_SeqTimerStartObjMain;
        m240_phaseStep = 1;
        HuAudSeqPlay(0x30);
    }
}

void m240_SeqStartObjMain(omObjData *arg0) {
    GMesCreate(3);
    arg0->func = m240_SeqStartWaitObjMain;
    m240_phaseStep = 1;
}

void m240_CameraViewObjMain(omObjData *object) {
    Vec position;
    Vec target;
    Vec result;
    u32 i;

    if (m240_cameraSetF == 0) {
        m240_cameraSetF = 1;
        target.x = 1975.0f;
        target.y = 0.0f;
        target.z = 2700.0f;
        position.x = -40.0f;
        position.y = 0.0f;
        position.z = 45.0f;
        m240_PolarCalc(&position, &target, &result);
        for (i = 0; i < 2; i++) {
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

void m240_ExitObjMain(omObjData *object) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void m240_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m240_ExitObjMain;
    }
}

void m240_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m240_ExitWaitObjMain;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void m240_PhaseUpdate(void) {
    m240_phase += m240_phaseStep;
    m240_phaseStep = 0;
}

s32 m240_PlayerHitCheck(SnowballSummitPlayer *mover) {
    SnowballSummitPlayer *other;
    Vec delta;
    f32 radius;
    f32 dist;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (mover->unk_78->work[0] == i) {
            continue;
        }
        if (mover->unk_5C[i] != 0) {
            continue;
        }
        other = &m240_playerWorkTbl[i];
        if (other->id == -1) {
            continue;
        }
        m240_PolarXZCalc(mover->spawnPosX, mover->spawnPosZ, other->spawnPosX, other->spawnPosZ, &delta);
        radius = mover->unk_50 + other->unk_50;
        dist = delta.x;
        if (dist < 0.0f) {
            dist = -dist;
        }
        if (dist < radius && mover->spawnPosY <= other->unk_54 && mover->unk_3C == 0) {
            mover->unk_5C[i] = 1;
            mover->unk_58 = 1;
            other->unk_5C[mover->unk_78->work[0]] = 1;
            other->unk_58 = 1;
        }
    }
    return mover->unk_58 != 0;
}

s32 m240_PlayerFallCheck(SnowballSummitPlayer *mover) {
    f32 dx = mover->unk_78->trans.x + mover->posZ;
    f32 dz = mover->unk_78->trans.z + mover->unk_28;
    f32 angle;

    if (dx * dx + dz * dz > 476100.0f) {
        if (mover->unk_3C == 0 || mover->unk_74 >= 2) {
            mover->spawnPosY = 20.0f;
            angle = m240_AngleCalc(mover->spawnPosX, mover->spawnPosZ);
            mover->spawnPosX += sindf(angle) * 30.0f;
            mover->spawnPosZ += cosdf(angle) * 30.0f;
            mover->unk_3C = 3;
        } else {
            mover->unk_3C = 2;
        }
        PlayerFXPlay(0x286, mover->unk_78->work[0]);
        HuAudFXPlay(0x43B);
        mover->unk_4C = 1;
        mover->posY = 306.38437f;
        mover->unk_14 = 7.0f;
        mover->unk_10 = 2.0f;
    } else {
        mover->unk_4C = 0;
    }
    return mover->unk_4C;
}

void m240_PlayerPush(SnowballSummitPlayer *mover) {
    SnowballSummitPlayer *other;
    Vec delta;
    f32 push;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (mover->unk_78->work[0] == i) {
            continue;
        }
        if (mover->unk_5C[i] != 1) {
            continue;
        }
        other = &m240_playerWorkTbl[i];
        if (other->id == -1) {
            continue;
        }
        m240_PolarXZCalc(mover->spawnPosX, mover->spawnPosZ, other->spawnPosX, other->spawnPosZ, &delta);
        if (mover->unk_3C != 0) {
            mover->spawnPosX = other->unk_78->trans.x + sindf(delta.z) * (other->unk_50 + mover->unk_50 + 1.0f);
            mover->spawnPosZ = other->unk_78->trans.z + cosdf(delta.z) * (other->unk_50 + mover->unk_50 + 1.0f);
            mover->posZ = -mover->posZ;
            mover->unk_28 = -mover->unk_28;
            mover->unk_5C[i] = 0;
        } else if (other->unk_10 == 0.0f) {
            mover->spawnPosX = other->unk_78->trans.x + sindf(delta.z) * (other->unk_50 + mover->unk_50 + 1.0f);
            mover->spawnPosZ = other->unk_78->trans.z + cosdf(delta.z) * (other->unk_50 + mover->unk_50 + 1.0f);
            mover->posZ = mover->spawnPosX - mover->unk_78->trans.x;
            mover->unk_28 = mover->spawnPosZ - mover->unk_78->trans.z;
            mover->unk_5C[i] = 0;
        } else {
            if (mover->unk_10 == 0.0f) {
                continue;
            }
            push = (other->unk_50 + mover->unk_50 - delta.x) * 0.5;
            mover->spawnPosX += sindf(delta.z) * (push + 1.0f);
            mover->spawnPosZ += cosdf(delta.z) * (push + 1.0f);
            mover->posZ = mover->spawnPosX - mover->unk_78->trans.x;
            mover->unk_28 = mover->spawnPosZ - mover->unk_78->trans.z;
            other->spawnPosX += sindf(WRAP_ANGLE(delta.z + 180.0f)) * (push + 1.0f);
            other->spawnPosZ += cosdf(WRAP_ANGLE(delta.z + 180.0f)) * (push + 1.0f);
            other->posZ = other->spawnPosX - other->unk_78->trans.x;
            other->unk_28 = other->spawnPosZ - other->unk_78->trans.z;
            mover->unk_5C[i] = 0;
        }
        other->unk_5C[mover->unk_78->work[0]] = 0;
    }
}

void m240_PlayerFallUpdate(SnowballSummitPlayer *mover) {
    f32 angle;
    f32 rise;

    if (mover->unk_10 >= 7.0f) {
        mover->unk_10 = 7.0f;
    } else {
        mover->unk_10 += 1.0f;
    }

    if (mover->spawnPosY < -2000.0f) {
        mover->spawnPosY = -2000.0f;
        mover->unk_10 = mover->unk_2C = mover->posY = mover->posZ = mover->unk_24 = mover->unk_28 = 0.0f;
        Hu3DModelAttrSet(mover->unk_78->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mover->id = 90;
    } else if (mover->spawnPosX * mover->spawnPosX + mover->spawnPosZ * mover->spawnPosZ > 9000000.0f) {
        Hu3DModelAttrSet(mover->unk_78->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mover->id = 90;
    } else {
        angle = m240_AngleCalc(mover->spawnPosX, mover->spawnPosZ);
        mover->spawnPosX += mover->unk_10 * mover->unk_10 * cosdf(mover->posY) * sindf(angle);
        mover->spawnPosZ += mover->unk_10 * mover->unk_10 * cosdf(mover->posY) * cosdf(angle);
        rise = mover->unk_14 * mover->unk_14 * sindf(mover->posY);
        if (mover->unk_3C == 3) {
            mover->spawnPosY += rise;
        } else if (mover->unk_3C == 2) {
            mover->unk_24 -= mover->unk_2C;
            if (mover->spawnPosY < rise) {
                mover->spawnPosY += rise;
                mover->unk_3C = 3;
            }
        }
    }
}

void m240_PlayerPosUpdate(SnowballSummitPlayer *mover) {
    omObjData *object = mover->unk_78;
    f32 angle;

    if (mover->unk_3C == 2 || mover->unk_3C == 3) {
        object->trans.x = mover->spawnPosX;
        object->trans.y = mover->spawnPosY;
        object->trans.z = mover->spawnPosZ;
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 5.0f, object->trans.z);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        if (mover->unk_3C == 1) {
            object->trans.x = mover->spawnPosX;
            object->trans.y = mover->spawnPosY;
            object->trans.z = mover->spawnPosZ;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
        } else {
            object->trans.x = mover->spawnPosX;
            object->trans.z = mover->spawnPosZ;
            mover->posX = object->rot.y;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 20.0f + 5.0f, object->trans.z);
    }

    if ((mover->unk_4C != 0 && object->trans.y > -2000.0f) || mover->unk_74 == 1) {
        if (mover->spawnPosY > -1900.0f) {
            if (mover->unk_6C <= 0) {
                angle = m240_AngleCalc(mover->spawnPosX, mover->spawnPosZ);
                m240_PuffEmit(mover->unk_78, 40, 0.1f, 1.6f, sindf(angle) * 50.0f, 60.0f, cosdf(angle) * 50.0f);
                mover->unk_6C = 1;
            } else {
                mover->unk_6C--;
            }
        }
    }
}

void m240_PlayerBumpCheck(SnowballSummitPlayer *mover) {
    omObjData *object = mover->unk_78;
    SnowballSummitPlayer *other;
    omObjData *otherObject;
    Vec delta;
    f32 radius;
    f32 dist;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == object->work[0]) {
            continue;
        }
        other = &m240_playerWorkTbl[i];
        if (other->id == 90) {
            continue;
        }
        if (other->unk_4C != 0) {
            continue;
        }
        otherObject = other->unk_78;
        m240_PolarXZCalc(object->trans.x, object->trans.z, otherObject->trans.x, otherObject->trans.z, &delta);
        radius = mover->unk_50 + other->unk_50;
        dist = delta.x;
        if (dist < 0.0f) {
            dist = -dist;
        }
        if (dist < radius && object->trans.y < otherObject->trans.y + other->unk_54) {
            mover->unk_74 = 1;
            mover->unk_3C = 1;
            mover->unk_10 = 10.0f;
            mover->unk_24 = 20.0f;
            mover->unk_2C = 4.0f;
            mover->posX = WRAP_ANGLE(delta.z + 180.0f + (u8)(rand8() % 20));
        }
    }
}

void m240_PlayerMoveUpdate(void) {
    SnowballSummitPlayer *mover;
    s32 iterations = 0;
    s32 resolved;
    s32 i;
    s32 j;

    do {
        resolved = 1;
        iterations++;
        for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
            mover = &m240_playerWorkTbl[i];
            for (j = 0; j < ARRAY_COUNT(mover->unk_5C); j++) {
                mover->unk_5C[j] = 0;
            }
            mover->unk_58 = 0;
        }
        for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
            mover = &m240_playerWorkTbl[i];
            if (mover->id != -1 && mover->unk_3C == 0) {
                if (m240_PlayerHitCheck(mover)) {
                    resolved = 0;
                }
            }
        }
        for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
            mover = &m240_playerWorkTbl[i];
            if (mover->id != -1 && mover->unk_4C == 0) {
                m240_PlayerFallCheck(mover);
            }
        }
        for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
            mover = &m240_playerWorkTbl[i];
            if (mover->id != -1 && mover->unk_58 == 1 && mover->unk_3C == 0) {
                m240_PlayerPush(mover);
            }
        }
    } while (resolved == 0 && iterations < 10);

    for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        mover = &m240_playerWorkTbl[i];
        if (mover->id != -1 && mover->unk_4C == 1) {
            m240_PlayerFallUpdate(mover);
        }
    }
    for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        mover = &m240_playerWorkTbl[i];
        if (mover->id != -1) {
            m240_PlayerPosUpdate(mover);
        }
    }
    for (i = 0; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        mover = &m240_playerWorkTbl[i];
        if (mover->id != -1 && mover->unk_3C == 1) {
            m240_PlayerBumpCheck(mover);
        }
    }
}

void m240_BallFallCheck(SnowballSummitBall *slot) {
    SnowballSummitPlayer *mover;
    SnowballSummitRollEff *node;
    f32 x = slot->unk_3C->trans.x;
    f32 z = slot->unk_3C->trans.z;
    f32 angle;

    if (x * x + z * z > 476100.0f) {
        if (slot->unk_10 != -1) {
            mover = &m240_playerWorkTbl[slot->unk_10];
            node = &m240_rollEffTbl[slot->unk_10];
            mover->unk_70 = -1;
            mover->unk_48 = 0;
            mover->unk_40 = 0;
            mover->unk_44 = 0;
            if (node->unk_04 == 1 && node->unk_08 != -1) {
                HuAudFXStop((s16)node->unk_08);
                node->unk_04 = 0;
                node->unk_08 = -1;
            }
        }
        slot->unk_18 = 1;
        slot->unk_1C = 306.38437f;
        slot->unk_20 = 7.0f;
        slot->unk_24 = 2.0f;
        slot->unk_10 = -1;
        slot->unk_28 = 0;
        angle = m240_AngleCalc(slot->unk_3C->trans.x, slot->unk_3C->trans.z);
        slot->unk_3C->trans.x += sindf(angle) * (slot->unk_0C * 37.5);
        slot->unk_3C->trans.z += cosdf(angle) * (slot->unk_0C * 37.5);
        Hu3DModelAttrSet(slot->unk_3C->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        slot->unk_18 = 0;
    }
}

void m240_BallPushUpdate(SnowballSummitBall *slot) {
    SnowballSummitPlayer *mover = &m240_playerWorkTbl[slot->unk_10];
    omObjData *object = slot->unk_3C;
    f32 distance;

    if (slot->unk_0C < 4.0f) {
        slot->unk_0C += mover->unk_10 * 0.003;
    } else {
        slot->unk_0C = 4.0f;
    }
    object->scale.x = object->scale.y = object->scale.z = slot->unk_0C;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    if (slot->unk_0C < 1.7) {
        distance = slot->unk_0C * 37.5 + mover->unk_50;
    } else {
        distance = slot->unk_0C * 37.5 + mover->unk_50 * 0.6;
    }
    object->trans.x = sindf(mover->posX) * distance + mover->spawnPosX;
    object->trans.y = slot->unk_0C * 37.5 + 20.0;
    object->trans.z = cosdf(mover->posX) * distance + mover->spawnPosZ;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, 30.0f, object->trans.z);
    object->rot.x = object->rot.x + (mover->unk_10 * 0.3) * (mover->unk_10 * 0.3) >= 360.0
                        ? object->rot.x + (mover->unk_10 * 0.3) * (mover->unk_10 * 0.3) - 360.0
                    : object->rot.x + (mover->unk_10 * 0.3) * (mover->unk_10 * 0.3) < 0.0
                        ? object->rot.x + (mover->unk_10 * 0.3) * (mover->unk_10 * 0.3) + 360.0
                        : object->rot.x + (mover->unk_10 * 0.3) * (mover->unk_10 * 0.3);
    object->rot.y = mover->posX;
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    if (slot->id == 2) {
        m240_PuffEmit(object, 40, 0.1f, 1.6f, 0.0f, 0.0f, 0.0f);
    }
}

void m240_BallRollUpdate(SnowballSummitBall *slot) {
    omObjData *object = slot->unk_3C;
    f32 speed;
    f32 x;
    f32 y;
    f32 z;

    if (m240_ballSeF == 0) {
        slot->unk_38 = HuAudFXPlay(0x43A);
        if (slot->unk_38 != -1) {
            slot->unk_34 = 1;
            m240_ballSeF = 1;
        }
    }

    speed = 1.0f / (slot->unk_0C * slot->unk_0C + 1.0f) * 25.0f + 9.0f;
    object->trans.x += sindf(object->rot.y) * speed;
    object->trans.z += cosdf(object->rot.y) * speed;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, 30.0f, object->trans.z);
    object->rot.x = object->rot.x + (speed * 0.3) * (speed * 0.3) >= 360.0
                        ? object->rot.x + (speed * 0.3) * (speed * 0.3) - 360.0
                    : object->rot.x + (speed * 0.3) * (speed * 0.3) < 0.0
                        ? object->rot.x + (speed * 0.3) * (speed * 0.3) + 360.0
                        : object->rot.x + (speed * 0.3) * (speed * 0.3);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    if (slot->id == 11) {
        x = sindf(WRAP_ANGLE(object->rot.y + 180.0f)) * slot->unk_0C;
        y = object->trans.y - (object->trans.y - 120.0f);
        z = cosdf(WRAP_ANGLE(object->rot.y + 180.0f)) * slot->unk_0C;
        m240_PuffEmit(object, 20, 0.2f, 2.0f, x, y, z);
    }
}

void m240_BallFallUpdate(SnowballSummitBall *slot) {
    omObjData *object = slot->unk_3C;
    f32 angle;

    if (slot->unk_34 == 1 && slot->unk_38 != -1) {
        HuAudFXStop((s16)slot->unk_38);
        slot->unk_34 = 0;
        slot->unk_38 = -1;
        m240_ballSeF = 0;
    }

    if (slot->unk_24 >= 7.0f) {
        slot->unk_24 = 7.0f;
    } else {
        slot->unk_24 += 1.0f;
    }

    if (slot->unk_28 > 0) {
        slot->unk_28--;
    } else {
        m240_PuffEmit(object, 40, slot->unk_0C * 0.1 * 0.5, slot->unk_0C * 1.2 * 0.5, 0.0f, 0.0f, 0.0f);
        slot->unk_28 = 1;
    }

    if (object->trans.y < -1200.0f) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        slot->id = 0;
        slot->unk_18 = 0;
        slot->unk_1C = 0;
        slot->unk_20 = 0;
        slot->unk_24 = 0;
        slot->unk_10 = -1;
        slot->unk_28 = 0;
    } else {
        angle = m240_AngleCalc(object->trans.x, object->trans.z);
        object->trans.x += slot->unk_24 * slot->unk_24 * cosdf(slot->unk_1C) * sindf(angle);
        object->trans.z += slot->unk_24 * slot->unk_24 * cosdf(slot->unk_1C) * cosdf(angle);
        object->trans.y += slot->unk_20 * slot->unk_20 * sindf(slot->unk_1C);
    }
}

void m240_BallPlayerHitCheck(SnowballSummitBall *slot) {
    omObjData *object = slot->unk_3C;
    SnowballSummitPlayer *mover;
    SnowballSummitRollEff *node;
    omObjData *moverObject;
    Vec delta;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == slot->unk_10) {
            continue;
        }
        mover = &m240_playerWorkTbl[i];
        if (mover->id == 90) {
            continue;
        }
        if (mover->unk_4C != 0) {
            continue;
        }
        moverObject = mover->unk_78;
        m240_PolarXZCalc(object->trans.x, object->trans.z, moverObject->trans.x, moverObject->trans.z, &delta);
        if (slot->unk_0C * 37.5 + mover->unk_50 > ABS(delta.x) && moverObject->trans.y < slot->unk_0C * 37.5 + slot->unk_0C * 37.5) {
            if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                HuAudFXStop((s16)slot->unk_38);
                slot->unk_34 = 0;
                slot->unk_38 = -1;
                m240_ballSeF = 0;
            }
            if (slot->unk_10 != -1) {
                node = &m240_rollEffTbl[slot->unk_10];
                if (node->unk_04 == 1 && node->unk_08 != -1) {
                    HuAudFXStop((s16)node->unk_08);
                    node->unk_04 = 0;
                    node->unk_08 = -1;
                }
            }
            HuAudPlayerFXPlay(0x43C, mover->unk_78->work[0]);
            m240_hitTimerTbl[moverObject->work[0]] = 30;
            slot->id = 20;
            mover->unk_74 = 1;
            mover->unk_3C = 1;
            if (slot->unk_0C < 2.0f) {
                mover->unk_10 = slot->unk_0C * 10.0f;
                mover->unk_24 = slot->unk_0C * 16.0f;
            } else {
                mover->unk_10 = slot->unk_0C * 15.0f;
                mover->unk_24 = slot->unk_0C * 20.0f;
                HuAudPlayerFXPlay(0x43E, mover->unk_78->work[0]);
            }
            mover->unk_2C = 4.0f;
            mover->posX = delta.z;
            if (mover->unk_70 != -1) {
                m240_ballTbl[mover->unk_70].id = 20;
            }
            if (mover->unk_08 == 0) {
                omVibrate(moverObject->work[0], 20, 0, 20);
            }
        }
    }
}

void m240_BallHitCheck(SnowballSummitBall *slot) {
    omObjData *object = slot->unk_3C;
    SnowballSummitBall *other;
    SnowballSummitRollEff *node;
    Vec delta;
    s32 i;

    m240_BallPlayerHitCheck(slot);
    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        if (i == object->work[0]) {
            continue;
        }
        other = &m240_ballTbl[i];
        if (other->id <= 0) {
            continue;
        }
        m240_PolarXZCalc(object->trans.x, object->trans.z, other->unk_3C->trans.x, other->unk_3C->trans.z, &delta);
        if (slot->unk_0C * 37.5 + other->unk_0C * 37.5 > ABS(delta.x)) {
            if (slot->unk_10 != -1) {
                slot->id = 20;
                if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                    HuAudFXStop((s16)slot->unk_38);
                    slot->unk_34 = 0;
                    slot->unk_38 = -1;
                    m240_ballSeF = 0;
                }
                node = &m240_rollEffTbl[slot->unk_10];
                if (node->unk_04 == 1 && node->unk_08 != -1) {
                    HuAudFXStop((s16)node->unk_08);
                    node->unk_04 = 0;
                    node->unk_08 = -1;
                }
            } else if (other->unk_10 == -1) {
                if (!(slot->unk_0C - other->unk_0C < 0.2)) {
                    continue;
                }
                slot->id = 20;
                if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                    HuAudFXStop((s16)slot->unk_38);
                    slot->unk_34 = 0;
                    slot->unk_38 = -1;
                    m240_ballSeF = 0;
                }
            } else {
                slot->id = 20;
                if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                    HuAudFXStop((s16)slot->unk_38);
                    slot->unk_34 = 0;
                    slot->unk_38 = -1;
                    m240_ballSeF = 0;
                }
            }
            HuAudFXPlay(0x43F);
        }
    }
}

void m240_BallMoveUpdate(void) {
    SnowballSummitBall *slot;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot = &m240_ballTbl[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            if (slot->unk_10 != -1) {
                m240_BallPushUpdate(slot);
            } else {
                m240_BallRollUpdate(slot);
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot = &m240_ballTbl[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            m240_BallFallCheck(slot);
        }
    }
    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot = &m240_ballTbl[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            m240_BallHitCheck(slot);
        }
    }
    for (i = 0; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot = &m240_ballTbl[i];
        if (slot->id > 0 && slot->id < 20 && slot->unk_18 == 1) {
            m240_BallFallUpdate(slot);
        }
    }
}

void m240_RollEffUpdate(void) {
    SnowballSummitRollEff *node;
    SnowballSummitPlayer *mover;
    SnowballSummitBall *slot;
    s32 i;

    for (i = 0; i < 4; i++) {
        node = &m240_rollEffTbl[i];
        if (node->id == -1) {
            return;
        }
        mover = &m240_playerWorkTbl[i];
        if (mover->id == -1 || mover->unk_70 == -1 || mover->unk_3C != 0 || mover->unk_10 <= 0.0f) {
            node->id = 0;
        }
        switch (node->id) {
            case 0:
                if (node->unk_04 == 1 && node->unk_08 != -1) {
                    HuAudFXStop((s16)node->unk_08);
                    node->unk_04 = 0;
                    node->unk_08 = -1;
                }
                Hu3DModelAttrSet(node->unk_0C->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if ((mover->unk_04 == 3 || mover->unk_04 == 4) && mover->unk_10 > 0.0f) {
                    node->id = 1;
                }
                break;
            case 1:
                Hu3DModelAttrSet(node->unk_0C->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                if (node->unk_04 != 1 && node->unk_08 == -1) {
                    node->unk_08 = HuAudPlayerFXPlay(0x439, mover->unk_78->work[0]);
                    if (node->unk_08 != -1) {
                        node->unk_04 = 1;
                    }
                }
                if (!(mover->unk_04 == 3 || mover->unk_04 == 4) || mover->unk_10 <= 0.0f) {
                    node->id = 0;
                    if (node->unk_04 == 1 && node->unk_08 != -1) {
                        HuAudFXStop((s16)node->unk_08);
                        node->unk_04 = 0;
                        node->unk_08 = -1;
                    }
                }
                break;
        }
        if (mover->unk_70 != -1) {
            slot = &m240_ballTbl[mover->unk_70];
            node->unk_0C->trans.x = slot->unk_3C->trans.x;
            node->unk_0C->trans.y = slot->unk_3C->trans.y;
            node->unk_0C->trans.z = slot->unk_3C->trans.z;
            node->unk_0C->scale.x = node->unk_0C->scale.y = node->unk_0C->scale.z = slot->unk_0C;
        } else {
            node->unk_0C->trans.x = mover->spawnPosX;
            node->unk_0C->trans.y = mover->spawnPosY + 20.0f;
            node->unk_0C->trans.z = mover->spawnPosZ;
            if (node->unk_04 == 1 && node->unk_08 != -1) {
                HuAudFXStop((s16)node->unk_08);
                node->unk_04 = 0;
                node->unk_08 = -1;
            }
        }
    }
    // Only the last node is updated here, as this is outside the loop.
    Hu3DModelPosSet(node->unk_0C->model[0], node->unk_0C->trans.x, node->unk_0C->trans.y, node->unk_0C->trans.z);
    if (m240_phase >= 3 && node->unk_04 == 1 && node->unk_08 != -1) {
        HuAudFXStop((s16)node->unk_08);
        node->unk_04 = 0;
        node->unk_08 = -1;
    }
}

void m240_MainObjMain(omObjData *object) {
    m240_PhaseUpdate();
    switch (m240_phase) {
        case 0:
            break;
        case 1:
            if (m240_ambientSeNo == -1) {
                m240_ambientSeNo = HuAudFXPlay(0x43D);
            }
            break;
        case 2:
        case 3:
            m240_PlayerMoveUpdate();
            m240_BallMoveUpdate();
            m240_RollEffUpdate();
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = m240_ExitWaitObjMain;
            break;
    }
}

void m240_PlayerWorkInit(void) {
    s32 i;
    SnowballSummitPlayer *mover;

    for (i = 0, mover = m240_playerWorkTbl; i < ARRAY_COUNT(m240_playerWorkTbl); i++) {
        mover[i].id = -1;
    }
}

void m240_BackBallWorkInit(void) {
    s32 i;
    SnowballSummitBackBall *throwSlot;

    for (i = 0, throwSlot = m240_backBallTbl; i < ARRAY_COUNT(m240_backBallTbl); i++) {
        throwSlot[i].state = -1;
    }
}

void m240_PuffWorkInit(void) {
    s32 i;
    SnowballSummitPuff *roll;

    for (i = 0, roll = m240_puffTbl; i < ARRAY_COUNT(m240_puffTbl); i++) {
        roll[i].state = -1;
    }
}

void m240_BallWorkInit(void) {
    s32 i;
    SnowballSummitBall *slot;

    for (i = 0, slot = m240_ballTbl; i < ARRAY_COUNT(m240_ballTbl); i++) {
        slot[i].id = -1;
    }
}

void m240_BurstWorkInit(void) {
    s32 i;
    SnowballSummitBurst *snowball;

    for (i = 0, snowball = m240_burstTbl; i < ARRAY_COUNT(m240_burstTbl); i++) {
        snowball[i].state = -1;
    }
}

void m240_BallMakeEffWorkInit(void) {
    s32 i;
    SnowballSummitBallMakeEff *slot;

    for (i = 0, slot = m240_ballMakeEffTbl; i < ARRAY_COUNT(m240_ballMakeEffTbl); i++) {
        slot[i].id = -1;
    }
}

void m240_RollEffWorkInit(void) {
    s32 i;
    SnowballSummitRollEff *node;

    for (i = 0, node = m240_rollEffTbl; i < ARRAY_COUNT(m240_rollEffTbl); i++) {
        node[i].id = -1;
    }
}

void m240_WorkInitAll(void) {
    m240_phase = 0;
    m240_phaseStep = 0;
    m240_cameraSetF = 0;
    m240_winnerF = 0;
    m240_unusedNo = -1;
    m240_unusedF = 0;
    m240_ballSeF = 0;
    m240_PlayerWorkInit();
    m240_BackBallWorkInit();
    m240_BallWorkInit();
    m240_PuffWorkInit();
    m240_BallMakeEffWorkInit();
    m240_RollEffWorkInit();
    m240_BurstWorkInit();
}

void m240_ObjCreateAll(void) {
    m240_WorkInitAll();
    m240_HudObjCreate();
    m240_BackdropObjCreate();
    m240_MountainObjCreate();
    m240_BackBallObjCreateAll();
    m240_StageObjCreate();
    m240_PlayerObjCreateAll();
    m240_BallObjCreateAll();
    m240_PuffObjCreateAll();
    m240_BallMakeEffObjCreateAll();
    m240_RollEffObjCreateAll();
    m240_BurstObjCreateAll();
    m240_SnowObjCreate();
}

void m240_MainObjInit(omObjData *object) {
    m240_ObjCreateAll();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    object->func = m240_MainObjMain;
    omAddObj(0x64, 0, 0, -1, m240_CameraViewObjMain);
    omAddObj(0x384, 0, 0, -1, m240_SeqStartObjMain);
}

void m240_Dummy(void) {
}

void m240_CameraInit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, m240_cameraViewTbl[i].scissorX, m240_cameraViewTbl[i].scissorY,
                   m240_cameraViewTbl[i].scissorWidth, m240_cameraViewTbl[i].scissorHeight);
        ViewportSet(i, m240_cameraViewTbl[i].viewportScale.x, m240_cameraViewTbl[i].viewportScale.y,
                    m240_cameraViewTbl[i].viewportScale.z, m240_cameraViewTbl[i].viewportTranslate.x,
                    m240_cameraViewTbl[i].viewportTranslate.y, m240_cameraViewTbl[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, m240_cameraViewTbl[i].fov, 80.0f, 8000.0f);
    }
}

void m240_ObjectSetup(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(100, 0);
    omGameSysInit();
    m240_CameraInit();
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, -215.0f, 295.0f, 470.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, -215.0f, 295.0f, 470.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(m240_fontMesTbl, 0);
    GMesFontMesCreate(m240_fontMesTbl, 1);
    omAddObj(1000, 0, 0, -1, m240_MainObjInit);
    omAddObj(1000, 0, 0, -1, m240_ExitCheckObjMain);
}

const s16 m240_fontMesTbl[] = { 0x8260, 0x8261, 0x8262, 0 };
