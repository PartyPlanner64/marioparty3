#include "common.h"
#include "gcc/memory.h"
#include "game/overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define WRAP_ANGLE(angle) \
    ((angle) >= 360.0f ? (angle) - 360.0f : ((angle) < 0.0f ? (angle) + 360.0f : (angle)))

typedef struct StormChaserStart {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
} StormChaserStart; // sizeof 0x14

typedef struct StormChaserGoal {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
    /* 0x08 */ f32 unk_08;
} StormChaserGoal; // sizeof 0xC

typedef struct StormChaserHome {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} StormChaserHome; // sizeof 0x8

typedef struct StormChaserCamera {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} StormChaserCamera; // sizeof 0x2C

typedef struct StormChaserBackdrop {
    /* 0x00 */ s32 state; // -1 when unused
    /* 0x04 */ s32 spriteData;
    /* 0x08 */ s32 hookId;
    /* 0x0C */ HuSprAnimData *sprite;
} StormChaserBackdrop; // sizeof 0x10

typedef struct StormChaserCloud {
    /* 0x00 */ s32 state;         // -1 when unused
    /* 0x04 */ f32 unk_04;        // movement speed
    /* 0x08 */ f32 unk_08;        // movement angle
    /* 0x0C */ s32 unk_0C;        // frames until the next direction change
    /* 0x10 */ s32 unk_10;        // 0 when the cloud curves
    /* 0x14 */ f32 unk_14;        // per-frame angle delta
    /* 0x18 */ omObjData *unk_18; // cloud object
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ s16 unk_1E;
} StormChaserCloud; // sizeof 0x20

typedef struct StormChaserRain {
    /* 0x00 */ s32 state;         // -1 when unused
    /* 0x04 */ f32 unk_04;        // texture scroll offset
    /* 0x08 */ f32 unk_08;        // opacity
    /* 0x0C */ omObjData *unk_0C; // rain object
} StormChaserRain;                // sizeof 0x10

typedef struct StormChaserData {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 unk_22;
    /* 0x24 */ omObjData *unk_24;
} StormChaserData; // sizeof 0x28

typedef struct StormChaserEntry {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ omObjData *unk_08;
} StormChaserEntry; // sizeof 0xC

typedef struct StormChaserState {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk_04;        // index into the texture frame sequences
    /* 0x08 */ s32 unk_08;        // frames to wait before the next strike
    /* 0x0C */ s32 unk_0C;        // opacity
    /* 0x10 */ omObjData *unk_10; // lightning object
} StormChaserState;               // sizeof 0x14

typedef struct StormChaserPlayer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40; // CPU: frames to keep the stored stick direction
    /* 0x44 */ omObjData *unk_44;
    /* 0x48 */ f32 unk_48; // CPU difficulty parameters
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s16 unk_54; // CPU: stored stick x
    /* 0x56 */ s16 unk_56; // CPU: stored stick y
} StormChaserPlayer;       // sizeof 0x58

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;
extern f32 D_8010CF24_storm_chasers; // D_8010CF20_storm_chasers.unk_04; func_801075F8_storm_chasers accesses it as a separate symbol
extern s16 D_8010CF6E_storm_chasers; // low half of D_8010CF6C_storm_chasers
extern s16 D_8010CF72_storm_chasers; // low half of D_8010CF70_storm_chasers
extern const s16 D_8010CC8C_storm_chasers[];

MinigameFlow D_8010C8B0_storm_chasers = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    90, 900, 0, 30, 150
};
StormChaserStart D_8010C8D8_storm_chasers[4] = {
    { -200.0f, -200.0f, 45.0f, 45.0f, -5.0f },
    { 200.0f, -200.0f, 315.0f, 315.0f, 5.0f },
    { -200.0f, 200.0f, 135.0f, 45.0f, -15.0f },
    { 200.0f, 200.0f, 225.0f, 315.0f, 15.0f },
};
StormChaserGoal D_8010C928_storm_chasers[4] = {
    { -220.0f, -220.0f, 0.0f },
    { 220.0f, -220.0f, 0.0f },
    { -220.0f, 220.0f, 0.0f },
    { 220.0f, 220.0f, 0.0f },
};
s32 D_8010C958_storm_chasers = 300;
s32 D_8010C95C_storm_chasers = -1;
// lightning texture frame sequences, each terminated by -1
s32 D_8010C960_storm_chasers[25] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 3, 3, 2, 2, 1, 1, 0, 0, -1 };
s32 D_8010C9C4_storm_chasers[25] = { 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, 0, 0, 1, 1, 2, 2, 1, 1, -1 };
s32 D_8010CA28_storm_chasers[25] = { 3, 3, 4, 4, 5, 5, 4, 4, 3, 3, 4, 4, 5, 5, 4, 4, 3, 3, 4, 4, 5, 5, 4, 4, -1 };
StormChaserHome D_8010CA8C_storm_chasers[4] = {
    { -110.0f, -110.0f },
    { 110.0f, -110.0f },
    { -110.0f, 110.0f },
    { 110.0f, 110.0f },
};
s32 D_8010CAAC_storm_chasers = 0;
s32 D_8010CAB0_storm_chasers = 0;
s16 D_8010CAB4_storm_chasers = -1;
StormChaserCamera D_8010CAB8_storm_chasers[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 26.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 26.0f },
};

s32 D_8010CCA0_storm_chasers BSS;
s32 D_8010CCA4_storm_chasers BSS;
u16 D_8010CCA8_storm_chasers BSS;
s32 D_8010CCAC_storm_chasers BSS;
u8 D_8010CCB0_storm_chasers BSS;
u8 D_8010CCB4_storm_chasers[0xC] BSS; /* Unreferenced. */
StormChaserCloud D_8010CCC0_storm_chasers BSS;
StormChaserData D_8010CCE0_storm_chasers[4] BSS;
StormChaserPlayer D_8010CD80_storm_chasers[4] BSS;
StormChaserState D_8010CEE0_storm_chasers[2] BSS;
s16 D_8010CF08_storm_chasers BSS;
u16 D_8010CF0A_storm_chasers BSS;
f32 D_8010CF0C_storm_chasers BSS;
f32 D_8010CF10_storm_chasers BSS;
u8 D_8010CF14_storm_chasers[4] BSS; /* Unreferenced. */
s32 D_8010CF18_storm_chasers BSS;
u16 D_8010CF1C_storm_chasers[2] BSS;
StormChaserRain D_8010CF20_storm_chasers BSS;
s32 D_8010CF30_storm_chasers BSS; // lightning texture animation ids, shared by both lightning objects
s32 D_8010CF34_storm_chasers BSS;
StormChaserEntry D_8010CF38_storm_chasers[4] BSS;
s32 D_8010CF68_storm_chasers BSS;
s32 D_8010CF6C_storm_chasers BSS;
s32 D_8010CF70_storm_chasers BSS;
HuSprAnimData *D_8010CF74_storm_chasers BSS;

void func_801061C0_storm_chasers(omObjData *);
void func_80106218_storm_chasers(omObjData *);
void func_8010637C_storm_chasers(void);
void func_801063B0_storm_chasers(Gfx **, s32, s32);
void func_8010662C_storm_chasers(omObjData *);
void func_801066BC_storm_chasers(void);
void func_80106794_storm_chasers(omObjData *);
void func_801068C8_storm_chasers(omObjData *);
void func_801070A8_storm_chasers(omObjData *);
void func_801069EC_storm_chasers(void);
void func_8010746C_storm_chasers(omObjData *);
void func_801075C4_storm_chasers(void);
void func_801075F8_storm_chasers(omObjData *);
void func_801077A0_storm_chasers(omObjData *);
void func_801078A0_storm_chasers(void);
void func_801078E0_storm_chasers(omObjData *);
void func_80107F70_storm_chasers(omObjData *);
void func_8010834C_storm_chasers(void);
void func_8010891C_storm_chasers(omObjData *);
void func_80108C64_storm_chasers(omObjData *);
void func_80108F88_storm_chasers(void);
void func_801090A4_storm_chasers(omObjData *);
void func_80109170_storm_chasers(omObjData *);
void func_8010A260_storm_chasers(omObjData *);
void func_8010AF20_storm_chasers(omObjData *);
void func_8010B1B0_storm_chasers(omObjData *);
void func_8010B738_storm_chasers(void);
void func_8010B840_storm_chasers(omObjData *);
void func_8010B87C_storm_chasers(omObjData *);
void func_8010B980_storm_chasers(omObjData *);
void func_8010BA00_storm_chasers(void);
void func_8010BD04_storm_chasers(void);
void func_8010BDF4_storm_chasers(omObjData *);
void func_8010BE8C_storm_chasers(omObjData *);
void func_8010BF84_storm_chasers(omObjData *);
void func_8010C060_storm_chasers(omObjData *);
void func_8010C0E0_storm_chasers(omObjData *);
void func_8010C120_storm_chasers(omObjData *);
void func_8010C29C_storm_chasers(omObjData *);
void func_8010C2F4_storm_chasers(void);
void func_8010C3A8_storm_chasers(void);
void func_8010C3EC_storm_chasers(void);
void func_8010C448_storm_chasers(void);
void func_8010C484_storm_chasers(void);
void func_8010C57C_storm_chasers(omObjData *);
void func_8010C60C_storm_chasers(void);
void func_8010C780_storm_chasers(void);

void func_801059A0_storm_chasers(void) {
    func_8010C780_storm_chasers();
}

Gfx **func_801059BC_storm_chasers(Gfx **gfxPos) {
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

Gfx **func_80105AA0_storm_chasers(Gfx **gfxPos) {
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

Gfx **func_80105B6C_storm_chasers(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

void func_80105B9C_storm_chasers(s32 playerIndex) {
    HuPadBtn[GwPlayer[playerIndex].pad] = 0;
    HuPadBtnDown[GwPlayer[playerIndex].pad] = 0;
    HuPadStkX[GwPlayer[playerIndex].pad] = 0;
    HuPadStkY[GwPlayer[playerIndex].pad] = 0;
}

f32 func_80105C14_storm_chasers(f32 value) {
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

void func_80105D64_storm_chasers(Vec *position, Vec *target, Vec *result) {
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
            yaw = func_80105C14_storm_chasers(difference.x / difference.z) * 57.2957795130823229;
        } else if (difference.z == 0.0f) {
            yaw = difference.x >= 0.0f ? 90.0f : 270.0f;
        } else {
            yaw = 0.0f;
        }
        if (difference.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontalDistance != 0.0f && difference.y != 0.0f) {
            pitch = func_80105C14_storm_chasers(difference.y / horizontalDistance) * 57.2957795130823229;
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

void func_801060E0_storm_chasers(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

f32 func_8010610C_storm_chasers(f32 y, f32 x) {
    f32 angle = atan2df(y, x);

    if (angle > 360.0) {
        angle -= 360.0;
    } else if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

void func_80106184_storm_chasers(f32 targetX, f32 targetZ, f32 posX, f32 posZ, Vec *result) {
    Vec position;
    Vec target;

    target.x = targetX;
    target.y = 0.0f;
    target.z = targetZ;
    position.x = posX;
    position.y = 0.0f;
    position.z = posZ;
    func_80105D64_storm_chasers(&position, &target, result);
}

void func_801061C0_storm_chasers(omObjData *object) {
    espPosSet(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
}

void func_80106218_storm_chasers(omObjData *object) {
    MgMapWork *work;

    D_8010CF0C_storm_chasers = 160.0f;
    D_8010CF10_storm_chasers = 120.0f;
    D_8010CF08_storm_chasers = HuSprAnimDataRead(0x500000);
    D_8010CF0A_storm_chasers = espEntry(D_8010CF08_storm_chasers, 0, 0);
    espAttrSet(D_8010CF0A_storm_chasers, 0x5000);
    espPosSet(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
    mgMapObjTbl[mgMapObjNum++] = object;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    MgMapSlideSet(object, 20.0f);
    MgMapFrictionSet(object, 0.5f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapCircleSet(mgMapObjTbl[0], 0.0f, 500.0f);
    object->func = func_801061C0_storm_chasers;
}

void func_8010637C_storm_chasers(void) {
    omAddObj(0x96, 1, 0, -1, func_80106218_storm_chasers);
}

void func_801063B0_storm_chasers(Gfx **gfxPos, s32 arg1, s32 arg2) {
    StormChaserBackdrop *backdrop = (StormChaserBackdrop *)&D_8010CF68_storm_chasers;
    Gfx *gfx;
    s32 y;

    if (backdrop->state == -1) {
        return;
    }
    gfxPos = func_801059BC_storm_chasers(gfxPos);
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, backdrop->sprite->pal);
    for (y = 0; y < 106; y += 2) {
        gDPLoadTextureTile(gfx++, backdrop->sprite->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 106,
                           0, y, 320, y + 2, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 2 << 2);
        gSPTextureRectangle(gfx++, 0 << 2, (y + 134) << 2, 320 << 2, (y + 136) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfxPos = gfx;
}

void func_80106624_storm_chasers(omObjData *object) {
}

void func_8010662C_storm_chasers(omObjData *object) {
    D_8010CF6C_storm_chasers = HuSprAnimDataRead(0x500001);
    D_8010CF74_storm_chasers = HuSprAnimDataGet(D_8010CF6E_storm_chasers);
    D_8010CF70_storm_chasers =
        Hu3DHookFuncCreate(0, func_801063B0_storm_chasers, 2);
    Hu3DModelCameraSet(D_8010CF72_storm_chasers, HU3D_CAM0);
    object->func = func_80106624_storm_chasers;
    D_8010CF68_storm_chasers = 0;
}

void func_801066BC_storm_chasers(void) {
    omObjData *object = omAddObj(0xA0, 1, 0, -1, func_8010662C_storm_chasers);
    object->work[0] = 0;
}

void func_801066F4_storm_chasers(omObjData *object) {
    StormChaserEntry *entry = &D_8010CF38_storm_chasers[object->work[0]];

    entry->state = 1;
    entry->unk_08->trans.x = object->trans.x;
    entry->unk_08->trans.y = 100.0f;
    entry->unk_08->trans.z = object->trans.z + 80.0f;
    if (D_8010C95C_storm_chasers == -1) {
        D_8010C95C_storm_chasers = HuAudFXPlay(0x487);
    }
}

void func_80106794_storm_chasers(omObjData *object) {
    StormChaserEntry *entry = &D_8010CF38_storm_chasers[object->work[0]];

    if (entry->state == -1) {
        return;
    }

    switch (entry->state) {
        case 0:
            break;
        case 1:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, 0);
            entry->state = 2;
            break;
        case 2:
            entry->unk_04 -= 25;
            if (entry->unk_04 > 0) {
                Hu3DModelTPLvlSet(object->model[0], entry->unk_04);
                object->scale.x += 0.1;
                object->scale.y += 0.1;
                object->scale.z += 0.1;
            } else {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                entry->unk_04 = 255;
                entry->state = 0;
                object->scale.x = object->scale.y = object->scale.z = 1.0f;
            }
            break;
    }
}

void func_801068C8_storm_chasers(omObjData *object) {
    StormChaserPlayer *player;
    StormChaserEntry *entry;

    object->model[0] = Hu3DModelRead(0x50000D, 0x289);
    Hu3DModelTPLvlInit(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], 255);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    player = &D_8010CD80_storm_chasers[object->work[0]];
    object->trans.x = player->unk_44->trans.x;
    object->trans.y = 100.0f;
    object->trans.z = player->unk_44->trans.z + 80.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->func = func_80106794_storm_chasers;
    entry = &D_8010CF38_storm_chasers[object->work[0]];
    entry->state = 0;
    entry->unk_04 = 255;
    entry->unk_08 = object;
}

void func_801069EC_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0xD2, 1, 0, -1, func_801068C8_storm_chasers)->work[0] = i;
    }
}

void func_80106A48_storm_chasers(omObjData *object) {
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;
    f32 angle;

    if (cloud->unk_0C > 0) {
        cloud->unk_0C--;
    } else {
        cloud->unk_08 = rand16() % 360;
        cloud->unk_04 = (u8)(rand8() % 7) + 6;
        cloud->unk_0C = (u8)(rand8() % 30) + 45;
        cloud->unk_10 = (u8)(rand8() % 3);
        if (cloud->unk_10 == 0) {
            cloud->unk_14 = (u8)(rand8() % 9) + 1;
            if (rand8() & 1) {
                cloud->unk_14 = -cloud->unk_14;
            }
        } else {
            cloud->unk_14 = 0.0f;
        }
    }

    if (object->trans.x * object->trans.x + object->trans.z * object->trans.z > 160000.0f) {
        angle = func_8010610C_storm_chasers(object->trans.x, object->trans.z);
        cloud->unk_08 = WRAP_ANGLE(angle + 135.0f + (u8)(rand8() % 90));
        cloud->unk_04 = (u8)(rand8() % 7) + 6;
        cloud->unk_0C = (u8)(rand8() % 30) + 20;
        cloud->unk_14 = 0.0f;
    }
    cloud->unk_08 = WRAP_ANGLE(cloud->unk_08 + cloud->unk_14);
    object->trans.x += sindf(cloud->unk_08) * cloud->unk_04;
    object->trans.z += cosdf(cloud->unk_08) * cloud->unk_04;
}

void func_80106F98_storm_chasers(omObjData *object) {
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;
    StormChaserRain *rain = &D_8010CF20_storm_chasers;
    f32 scale;

    cloud->unk_04 = 0.0f;
    cloud->unk_08 = 0.0f;
    cloud->unk_0C = 0;
    if (rain->unk_08 > 0.0f) {
        return;
    }
    object->trans.y += 20.0f;
    if (object->trans.y > 1000.0f) {
        object->trans.y = 1000.0f;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        scale = (1000.0f - object->trans.y) / 800.0f * 1.3;
        Hu3DModelScaleSet(object->model[1], scale, scale, scale);
    }
}

void func_801070A8_storm_chasers(omObjData *object) {
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;
    f32 ratio;
    s8 pan;

    if (cloud->state == -1) {
        return;
    }
    if (D_8010CCA0_storm_chasers == 1 && (cloud->unk_1C == -1 || cloud->unk_1E == -1)) {
        cloud->unk_1C = HuAudFXPlay(0x481);
        cloud->unk_1E = HuAudFXPlay(0x482);
        HuAudFXVolSet(cloud->unk_1C, 64);
        HuAudFXVolSet(cloud->unk_1E, 64);
        HuAudFXPanning(cloud->unk_1C, 64);
        HuAudFXPanning(cloud->unk_1E, 64);
    }

    switch (D_8010CCA0_storm_chasers) {
        case 0:
        case 1:
            cloud->unk_08 = rand16() % 360;
            cloud->unk_04 = (u8)(rand8() % 7) + 6;
            cloud->unk_0C = (u8)(rand8() % 30) + 45;
            cloud->unk_14 = 0.0f;
            if (cloud->unk_1C != -1 && cloud->unk_1E != -1) {
                ratio = (object->trans.z + 400.0f) / 800.0f;
                HuAudFXVolSet(cloud->unk_1C, (s32)((1.0f - ratio) * 64.0f) + 32);
                HuAudFXVolSet(cloud->unk_1E, (s32)(ratio * 64.0f) + 32);
                ratio = (object->trans.x + 400.0f) / 800.0f;
                pan = (1.0f - ratio) * 64.0f;
                HuAudFXPanning(cloud->unk_1C, pan + 32);
                HuAudFXPanning(cloud->unk_1E, pan + 32);
            }
            break;
        case 2:
            func_80106A48_storm_chasers(object);
            ratio = (object->trans.z + 400.0f) / 800.0f;
            HuAudFXVolSet(cloud->unk_1C, (s32)((1.0f - ratio) * 64.0f) + 32);
            HuAudFXVolSet(cloud->unk_1E, (s32)(ratio * 64.0f) + 32);
            ratio = (object->trans.x + 400.0f) / 800.0f;
            pan = (1.0f - ratio) * 64.0f;
            HuAudFXPanning(cloud->unk_1C, pan + 32);
            HuAudFXPanning(cloud->unk_1E, pan + 32);
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            func_80106F98_storm_chasers(object);
            if (cloud->unk_1C != -1) {
                HuAudFXFadeOut(cloud->unk_1C, 0x1E);
                cloud->unk_1C = -1;
            }
            if (cloud->unk_1E != -1) {
                HuAudFXFadeOut(cloud->unk_1E, 0x1E);
                cloud->unk_1E = -1;
            }
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, -10.0f, object->trans.z);
}

void func_8010746C_storm_chasers(omObjData *object) {
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;

    object->model[0] = Hu3DModelRead(0x500006, 0x289);
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    object->trans.x = 0.0f;
    object->trans.y = 350.0f;
    object->trans.z = 0.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, -10.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    object->func = func_801070A8_storm_chasers;
    cloud->state = 0;
    cloud->unk_1C = cloud->unk_1E = -1;
    cloud->unk_18 = object;
}

void func_801075C4_storm_chasers(void) {
    omAddObj(0xAA, 2, 1, -1, func_8010746C_storm_chasers);
}

void func_801075F8_storm_chasers(omObjData *object) {
    StormChaserRain *rain = &D_8010CF20_storm_chasers;
    StormChaserCloud *cloud;

    if (rain->state == -1) {
        return;
    }
    cloud = &D_8010CCC0_storm_chasers;
    if (cloud->state == -1) {
        return;
    }
    if (omPauseChk() + omAllPauseF == 0) {
        D_8010CF24_storm_chasers -= 4.0f;
    }
    Hu3DModelObjTexScroll(object->model[0], 0.0f, rain->unk_04, D_8010CF1C_storm_chasers[0], D_8010CF1C_storm_chasers[1], "247_1-ame", 0);
    object->trans.x = cloud->unk_18->trans.x;
    object->trans.y = 0.0f;
    object->trans.z = cloud->unk_18->trans.z;
    if (D_8010CCA0_storm_chasers < 3) {
        return;
    }
    rain->unk_08 -= 20.0f;
    if (rain->unk_08 < 0.0f) {
        rain->unk_08 = 0.0f;
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelTPLvlSet(object->model[0], rain->unk_08);
    }
}

void func_801077A0_storm_chasers(omObjData *object) {
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;
    StormChaserRain *rain = &D_8010CF20_storm_chasers;

    if (cloud->state == -1) {
        return;
    }
    object->model[0] = Hu3DModelRead(0x500007, 0x289);
    Hu3DModelVtxBufMake(object->model[0]);
    Hu3DModelTPLvlInit(object->model[0]);
    Hu3DModelTPLvlSet(object->model[0], 255);
    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, 0);
    Hu3DTexSizeGet("247_ame_IA44", D_8010CF1C_storm_chasers);
    object->trans.x = cloud->unk_18->trans.x;
    object->trans.y = 0.0f;
    object->trans.z = cloud->unk_18->trans.z;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->func = func_801075F8_storm_chasers;
    rain->state = 0;
    rain->unk_04 = 0.0f;
    rain->unk_08 = 255.0f;
    rain->unk_0C = object;
}

void func_801078A0_storm_chasers(void) {
    omObjData *object = omAddObj(0xB4, 1, 0, -1, func_801077A0_storm_chasers);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_801078E0_storm_chasers(omObjData *object) {
    StormChaserState *state = &D_8010CEE0_storm_chasers[object->work[0]];
    f32 angle;
    f32 radius;
    f32 edgeAngle;

    if (state->unk_08 > 0) {
        state->unk_08--;
        return;
    }

    switch (state->state) {
        case 0:
            if (D_8010CCAC_storm_chasers <= 90) {
                break;
            }
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, 0);
            if (state->state == 0) {
                angle = ((u8)(rand8() % 5) + 1) * 30;
                radius = ((rand8() & 3) + 1) * 80;
                if (object->work[0] != 0) {
                    angle = WRAP_ANGLE(angle + 180.0f);
                }
                object->trans.x = sindf(angle) * radius;
                object->trans.y = 0.0f;
                object->trans.z = cosdf(angle) * radius;
                state->state = 1;
            }
            if (object->trans.x * object->trans.x + object->trans.z * object->trans.z > 122500.0f) {
                edgeAngle = func_8010610C_storm_chasers(object->trans.x, object->trans.z);
                object->trans.x = sindf(edgeAngle) * (350 - (u8)(rand8() % 50));
                object->trans.z = cosdf(edgeAngle) * (350 - (u8)(rand8() % 50));
            }
            Hu3DAnimTimeSet(object->work[2], D_8010C9C4_storm_chasers[state->unk_04]);
            state->unk_04++;
            break;
        case 1:
            if (D_8010C9C4_storm_chasers[state->unk_04] == -1) {
                HuAudFXPlay(0x483);
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, 0);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, 0);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, 0);
                state->unk_04 = 0;
                state->state = 2;
                Hu3DMotionAttrSet(object->model[2], 1, 0);
                Hu3DAnimTimeSet(object->work[1], D_8010C960_storm_chasers[state->unk_04]);
                Hu3DAnimTimeSet(object->work[2], D_8010CA28_storm_chasers[state->unk_04]);
                state->unk_04++;
                Hu3DModelTPLvlSet(object->model[2], state->unk_0C);
            } else {
                Hu3DAnimTimeSet(object->work[2], D_8010C9C4_storm_chasers[state->unk_04]);
                state->unk_04++;
            }
            break;
        case 2:
            if (D_8010C960_storm_chasers[state->unk_04] == -1) {
                Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(object->model[2], 0.0f);
                Hu3DMotionAttrSet(object->model[2], 1, 1);
                state->unk_0C = 255;
                state->unk_04 = 0;
                state->unk_08 = (u8)(rand8() % 75) + 75;
                state->state = 0;
            } else {
                if (Hu3DData[object->model[2]].motTime > 30.0f) {
                    state->unk_0C -= 52;
                    if (state->unk_0C < 0) {
                        state->unk_0C = 255;
                        Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                }
                Hu3DModelTPLvlSet(object->model[2], state->unk_0C);
                Hu3DAnimTimeSet(object->work[1], D_8010C960_storm_chasers[state->unk_04]);
                Hu3DAnimTimeSet(object->work[2], D_8010CA28_storm_chasers[state->unk_04]);
                state->unk_04++;
            }
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
}

void func_80107EA4_storm_chasers(omObjData *object) {
    StormChaserState *state = &D_8010CEE0_storm_chasers[object->work[0]];

    if (state->state == -1) {
        return;
    }

    switch (D_8010CCA0_storm_chasers) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            func_801078E0_storm_chasers(object);
            break;
        case 3:
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            state->state = 0;
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
    }
}

void func_80107F70_storm_chasers(omObjData *object) {
    StormChaserState *state;
    void *animData;
    s32 i;

    object->model[0] = Hu3DModelRead(0x500008, 0x2A9);
    object->model[1] = Hu3DModelRead(0x50000A, 0x2A9);
    object->model[2] = Hu3DModelRead(0x50000C, 0x2A9);
    if (object->work[0] == 0) {
        animData = DataRead(0x500009);
        object->work[1] = D_8010CF30_storm_chasers =
            (s16)Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, animData, 0, "247_tyropu1_DEF");
        HuMemMemoryFreePerm(animData);
        animData = DataRead(0x50000B);
        object->work[2] = D_8010CF34_storm_chasers =
            (s16)Hu3DAnimCreate(Hu3DData[object->model[1]].hmf, animData, 0, "s247_004_DEF");
        HuMemMemoryFreePerm(animData);
    } else {
        object->work[1] = Hu3DAnimLink(Hu3DData[object->model[0]].hmf, D_8010CF30_storm_chasers, 0, "247_tyropu1_DEF");
        object->work[2] = Hu3DAnimLink(Hu3DData[object->model[1]].hmf, D_8010CF34_storm_chasers, 0, "s247_004_DEF");
    }
    for (i = 0; i < 2; i++) {
        Hu3DAnimTimeSet(object->work[i + 1], 0);
        Hu3DAnimAttrSet(object->work[i + 1], 1, 1);
        Hu3DModelRemakeStatic(object->model[i]);
        Hu3DModelDynamicFree(object->model[i]);
        Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    Hu3DModelTPLvlInit(object->model[2]);
    Hu3DModelTPLvlSet(object->model[2], 0xFF);
    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(object->model[2], 0.0f);
    Hu3DMotionAttrSet(object->model[2], 1, 1);
    Hu3DMotionAttrSet(object->model[2], 2, 0);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = 1.3f;
    for (i = 1; i < 3; i++) {
        Hu3DModelPosSet(object->model[i], object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelScaleSet(object->model[i], object->scale.x, object->scale.y, object->scale.z);
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelCameraSet(object->model[i], HU3D_CAM0);
    }
    object->func = func_80107EA4_storm_chasers;
    state = &D_8010CEE0_storm_chasers[object->work[0]];
    state->state = 0;
    state->unk_04 = 0;
    state->unk_08 = (u8)(rand8() % 75) + 75;
    state->unk_0C = 255;
    state->unk_10 = object;
}

void func_8010834C_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x190, 3, 1, -1, func_80107F70_storm_chasers)->work[0] = i;
    }
}

void func_801083A8_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];

    object->trans.x = player->unk_44->trans.x;
    object->trans.y = 100.0f;
    object->trans.z = player->unk_44->trans.z + 50.0f;
    object->rot.y = D_8010C8D8_storm_chasers[player->unk_0C].unk_0C;
    data->unk_0C = 14.0f;
    data->unk_10 = 2.0f;
    data->unk_18 = object->trans.x;
    data->unk_1C = object->trans.z;
    data->state = 2;
}

void func_80108478_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];

    if (object->trans.y > 0.0f) {
        object->trans.y += data->unk_0C;
        data->unk_0C -= data->unk_10;
        data->unk_14++;
        object->trans.x = data->unk_18 - (data->unk_18 - D_8010CA8C_storm_chasers[player->unk_0C].x) * 0.05 * data->unk_14;
        object->trans.z = data->unk_1C - (data->unk_1C - D_8010CA8C_storm_chasers[player->unk_0C].z) * 0.05 * data->unk_14;
    } else {
        object->trans.y = 0.0f;
        object->trans.x = D_8010CA8C_storm_chasers[player->unk_0C].x;
        object->trans.z = D_8010CA8C_storm_chasers[player->unk_0C].z;
        data->unk_08 = 1;
    }
    if (D_8010CCA0_storm_chasers == 5) {
        data->state = 10;
    }
}

void func_801085E4_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];

    if (D_8010CAAC_storm_chasers == 1 && player->unk_1C == 0 && data->unk_20 == -1) {
        data->unk_20 = HuAudFXPlay(0x484);
    }
    if (player->unk_1C != 3) {
        Hu3DMotionAttrSet(object->model[0], 1, 0);
        data->state = 0xB;
    } else {
        data->state = 0xC;
        data->unk_08 = 2;
    }
}

void func_801086C4_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];

    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    data->state = 0xC;
}

void func_80108738_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    f32 time;

    if (player->unk_14 != 0) {
        time = Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - player->unk_1C * 60;
    } else {
        time = Hu3DMotion[Hu3DData[object->model[0]].motId].unk02 - 180;
    }
    if (Hu3DData[object->model[0]].motTime >= time - 2.0f) {
        if (player->unk_1C == 0 && data->unk_20 != -1) {
            HuAudFXStop(data->unk_20);
            data->unk_20 = -1;
        }
        Hu3DMotionTimeSet(object->model[0], time);
        Hu3DMotionAttrSet(object->model[0], 1, 1);
        if (player->unk_1C != 0) {
            data->state = 0xC;
        } else {
            data->state = 0xD;
        }
        data->unk_08 = 2;
    }
}

void func_8010891C_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    Vec result;

    if (data->state == -1) {
        return;
    }

    switch (data->state) {
        case 0:
            if (data->unk_04 == 0) {
                data->state = 1;
                Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, 0);
            }
            object->trans.x = player->unk_44->trans.x;
            object->trans.y = 100.0f;
            object->trans.z = player->unk_44->trans.z + 50.0f;
            break;
        case 1:
            func_801083A8_storm_chasers(object);
            break;
        case 2:
            func_80108478_storm_chasers(object);
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
            func_801085E4_storm_chasers(object);
            break;
        case 11:
            func_80108738_storm_chasers(object);
            break;
        case 12:
            break;
        case 13:
            func_801086C4_storm_chasers(object);
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z + 10.0f);

    if (D_8010CCA0_storm_chasers == 2) {
        if (D_8010CCC0_storm_chasers.state == -1) {
            return;
        }
        player = &D_8010CD80_storm_chasers[object->work[0]];
        func_80106184_storm_chasers(D_8010CCC0_storm_chasers.unk_18->trans.x, D_8010CCC0_storm_chasers.unk_18->trans.z,
                                    player->unk_44->trans.x + sindf(player->unk_44->rot.y) * 50.0f,
                                    player->unk_44->trans.z + sindf(player->unk_44->rot.y) * 50.0f, &result);
        if (ABS(result.x) < 85.0f) {
            player->unk_14++;
            if (object->work[2] == 0) {
                if (object->work[3] < 2) {
                    object->work[3]++;
                } else {
                    object->work[2] = 1;
                }
            } else {
                if (object->work[3] != 0) {
                    object->work[3]--;
                } else {
                    object->work[2] = 0;
                }
            }
            Hu3DAnimTimeSet(object->work[1], object->work[3]);
        } else {
            if (object->work[3] != 0) {
                object->work[3]--;
            }
            Hu3DAnimTimeSet(object->work[1], object->work[3]);
        }
    } else {
        Hu3DAnimTimeSet(object->work[1], 0);
    }

    if (D_8010CCA0_storm_chasers == 8 && data->unk_20 != -1) {
        HuAudFXFadeOut(data->unk_20, 0x1E);
        data->unk_20 = -1;
    }
}

void func_80108C64_storm_chasers(omObjData *object) {
    StormChaserPlayer *player;
    StormChaserData *data;
    void *animData;

    object->model[0] = Hu3DModelRead(0x500002, 0x289);
    omObjMotionRead(object, 0, 0x500003);
    omObjMotionRead(object, 1, 0x500004);
    if (object->work[0] == 0) {
        animData = DataRead(0x500005);
        object->work[1] = D_8010CCB0_storm_chasers =
            Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, animData, 0, "pakkun_optimized_00_DEF");
        HuMemMemoryFreePerm(animData);
    } else {
        object->work[1] =
            Hu3DAnimLink(Hu3DData[object->model[0]].hmf, D_8010CCB0_storm_chasers, 0, "pakkun_optimized_00_DEF");
    }
    Hu3DAnimTimeSet(object->work[1], 0);
    Hu3DAnimAttrSet(object->work[1], 1, 1);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DModelDynamicFree(object->model[0]);
    object->model[1] = Hu3DModelRead2(0, 0xC9);
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionTimeSet(object->model[0], 0.0f);
    Hu3DMotionAttrSet(object->model[0], 2, 0);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    player = &D_8010CD80_storm_chasers[object->work[0]];
    object->trans.x = player->unk_44->trans.x;
    object->trans.y = player->unk_44->trans.y + 100.0f;
    object->trans.z = player->unk_44->trans.z + 50.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.0f, object->trans.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    object->func = func_8010891C_storm_chasers;
    data = &D_8010CCE0_storm_chasers[object->work[0]];
    data->state = 0;
    data->unk_04 = 0;
    data->unk_08 = 0;
    data->unk_14 = 0;
    data->unk_18 = 0.0f;
    data->unk_1C = 0.0f;
    data->unk_20 = -1;
    data->unk_24 = object;
    func_801090A4_storm_chasers(object);
}

void func_80108F88_storm_chasers(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x12C, 2, 2, -1, func_80108C64_storm_chasers)->work[0] = i;
    }
}

void func_80108FF8_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];

    if (data->state != -1) {
        Hu3DModelAttrSet(data->unk_24->model[0], 0x4000, 0x4000);
        Hu3DModelHookSet(data->unk_24->model[0], object->model[0], "item_hook");
        Hu3DMotionShapeSet(object->model[0], object->motion[22], 1);
        object->work[1] = 1;
        data->unk_04 = 1;
    }
}

void func_801090A4_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];

    Hu3DModelAttrSet(object->model[0], 0x4000, 0x4000);
    Hu3DModelHookSet(object->model[0], player->unk_44->model[0], "item_hook");
    Hu3DMotionShapeSet(player->unk_44->model[0], player->unk_44->motion[22], 1);
    player->unk_44->work[1] = 1;
    data->unk_04 = 1;
}

const char D_8010CC3C_storm_chasers[] = "";

void func_80109170_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    StormChaserCloud *cloud = &D_8010CCC0_storm_chasers;
    Vec result;
    f32 angle;

    if (object->trans.x * object->trans.x + object->trans.z * object->trans.z > 202500.0f) {
        angle = func_8010610C_storm_chasers(object->trans.x, object->trans.z);
        HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(angle + 180.0f + (u8)(rand8() % 3))) * 70.0f;
        HuPadStkY[GwPlayer[object->work[0]].pad] = -(s32)(cosdf(WRAP_ANGLE(angle + 180.0f + (u8)(rand8() % 3))) * 70.0f);
        player->unk_54 = HuPadStkX[GwPlayer[object->work[0]].pad];
        player->unk_56 = HuPadStkY[GwPlayer[object->work[0]].pad];
        player->unk_50 = (u8)(rand8() % 30) + player->unk_4C * 6;
    }

    if (player->unk_50 > 0) {
        player->unk_50--;
        func_80106184_storm_chasers(cloud->unk_18->trans.x, cloud->unk_18->trans.z, object->trans.x, object->trans.z, &result);
        if (player->unk_48 < ABS(result.x)) {
            HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(result.z + (u8)(rand8() % 3))) * 70.0f;
            HuPadStkY[GwPlayer[object->work[0]].pad] = -(s32)(cosdf(WRAP_ANGLE(result.z + (u8)(rand8() % 3))) * 70.0f);
            player->unk_54 = HuPadStkX[GwPlayer[object->work[0]].pad];
            player->unk_56 = HuPadStkY[GwPlayer[object->work[0]].pad];
            player->unk_50 = (u8)(rand8() % 30) + player->unk_4C * 6;
        }
        HuPadStkX[GwPlayer[object->work[0]].pad] = player->unk_54;
        HuPadStkY[GwPlayer[object->work[0]].pad] = player->unk_56;
    } else {
        func_80106184_storm_chasers(cloud->unk_18->trans.x, cloud->unk_18->trans.z, object->trans.x, object->trans.z, &result);
        HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(result.z + (u8)(rand8() % 3))) * 70.0f;
        HuPadStkY[GwPlayer[object->work[0]].pad] = -(s32)(cosdf(WRAP_ANGLE(result.z + (u8)(rand8() % 3))) * 70.0f);
        player->unk_54 = HuPadStkX[GwPlayer[object->work[0]].pad];
        player->unk_56 = HuPadStkY[GwPlayer[object->work[0]].pad];
        player->unk_50 = (u8)(rand8() % 30) + player->unk_4C * 6;
    }
}

void func_8010A070_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *work = object->data;
    StormChaserState *state;
    Vec result;
    s32 i;

    for (i = 0; i < 2; i++) {
        state = &D_8010CEE0_storm_chasers[i];
        if (state->state < 2) {
            continue;
        }
        func_80106184_storm_chasers(object->trans.x, object->trans.z, state->unk_10->trans.x, state->unk_10->trans.z, &result);
        if (ABS(result.x) < 80.0f) {
            if (player->unk_3C == 0) {
                MgPlayerMotSet(object, 0x21);
                player->unk_3C = 1;
                if (player->unk_04 == 0) {
                    omVibrate(object->work[0], 2, 2, 20);
                }
            }
            player->unk_38 = work->unk3C;
            player->unk_30 = work->unk3C = result.z;
            player->unk_34 = work->unk40 = 15.0f;
            player->unk_20 = 2;
            player->unk_28 = 12.0f;
            player->unk_2C = 4.0f;
            player->unk_24 = object->trans.y;
        }
    }
    if (player->unk_20 > 0) {
        func_80105B9C_storm_chasers(object->work[0]);
        if (player->unk_24 > 0.0f) {
            work->unk40 = player->unk_34;
        }
        work->unk3C = player->unk_30;
    }
}

void func_8010A260_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *work = object->data;
    StormChaserPlayer *other;
    Vec result;
    s32 isBlocked;
    s32 i;
    f32 angle;

    if (player->state < 20) {
        player->state = 20;
    }
    if (D_8010C958_storm_chasers == 0) {
        work->unk50 |= 0x400;
    }

    switch (player->state) {
        case 20:
            if (player->unk_40 > 0) {
                player->unk_40--;
                HuPadStkX[GwPlayer[object->work[0]].pad] = player->unk_54;
                HuPadStkY[GwPlayer[object->work[0]].pad] = player->unk_56;
                break;
            }
            for (i = 0, isBlocked = FALSE; i < 4; i++) {
                if (i == object->work[0]) {
                    continue;
                }
                other = &D_8010CD80_storm_chasers[i];
                if (other->state == -1) {
                    continue;
                }
                func_80106184_storm_chasers(other->unk_44->trans.x, other->unk_44->trans.z, object->trans.x, object->trans.z, &result);
                if (ABS(result.x) < 150.0f) {
                    isBlocked = TRUE;
                    break;
                }
            }
            if (isBlocked) {
                if ((u8)(rand8() % 10) != 0) {
                    player->unk_54 = HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(result.z + 60.0f)) * 35.0f;
                    angle = WRAP_ANGLE(result.z + 60.0f);
                } else {
                    player->unk_54 = HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(result.z + 180.0f)) * 35.0f;
                    angle = WRAP_ANGLE(result.z + 180.0f);
                }
                player->unk_56 = HuPadStkY[GwPlayer[object->work[0]].pad] = -(s32)(cosdf(angle) * 35.0f);
                player->unk_40 = 20;
            } else {
                func_80106184_storm_chasers(D_8010C928_storm_chasers[player->unk_0C].x, D_8010C928_storm_chasers[player->unk_0C].z, object->trans.x, object->trans.z, &result);
                if (ABS(result.x) < 30.0f) {
                    player->state = 21;
                    object->trans.x = D_8010C928_storm_chasers[player->unk_0C].x;
                    object->trans.z = D_8010C928_storm_chasers[player->unk_0C].z;
                } else {
                    HuPadStkX[GwPlayer[object->work[0]].pad] = sindf(WRAP_ANGLE(result.z + (u8)(rand8() % 6))) * 35.0f;
                    HuPadStkY[GwPlayer[object->work[0]].pad] = -(s32)(cosdf(WRAP_ANGLE(result.z + (u8)(rand8() % 6))) * 35.0f);
                }
            }
            break;
        case 21:
            if (work->unk40 <= 0.0f) {
                player->unk_08 = 1;
                work->unk3C = D_8010C8D8_storm_chasers[player->unk_0C].unk_08;
                player->state = 22;
            }
            break;
    }
}

void func_8010AC7C_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *work = object->data;
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];

    if (data->unk_04 != 0) {
        Hu3DData[object->model[0]].motIdShape = 255;
        Hu3DModelAttrSet(data->unk_24->model[0], 0x4000, 0);
        data->unk_04 = 0;
        func_801066F4_storm_chasers(object);
    }
    work->unk3C = D_8010C8D8_storm_chasers[player->unk_0C].unk_08;
}

void func_8010AD68_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *data = object->data;

    if (data->unk3C != 0.0f) {
        data->unk3C = WRAP_ANGLE(data->unk3C + D_8010C8D8_storm_chasers[player->unk_0C].unk_10);
    }
}

void func_8010AE4C_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *data = object->data;
    s32 charBase = omCharModelNoTbl[GwPlayer[object->work[0]].chr][0];

    if (player->unk_18 == 1) {
        MgPlayerMotSet(object, 0xD);
        HuAudCharVoicePlay(charBase | 0x2F);
        player->unk_18 = 2;
    } else if (player->unk_18 == 0) {
        MgPlayerMotSet(object, 0xE);
        player->unk_18 = 2;
    }
    data->unk3C = 0.0f;
}

void func_8010AF20_storm_chasers(omObjData *object) {
    StormChaserPlayer *player = &D_8010CD80_storm_chasers[object->work[0]];
    MgPlayerWork *work;

    if (player->state == -1) {
        return;
    }
    work = object->data;

    switch (D_8010CCA0_storm_chasers) {
        case 0:
        case 1:
            func_80105B9C_storm_chasers(object->work[0]);
            if (object->work[1] == 0) {
                func_80108FF8_storm_chasers(object);
            }
            object->rot.y = 0.0f;
            work->unk3C = D_8010C8D8_storm_chasers[player->unk_0C].unk_08;
            break;
        case 2:
            if (player->unk_04 != 0) {
                func_80105B9C_storm_chasers(object->work[0]);
                func_80109170_storm_chasers(object);
            }
            func_8010A070_storm_chasers(object);
            break;
        case 3:
            func_80105B9C_storm_chasers(object->work[0]);
            func_8010A260_storm_chasers(object);
            break;
        case 4:
        case 5:
            func_80105B9C_storm_chasers(object->work[0]);
            func_8010AC7C_storm_chasers(object);
            break;
        case 6:
            func_80105B9C_storm_chasers(object->work[0]);
            func_8010AD68_storm_chasers(object);
            break;
        case 7:
            func_80105B9C_storm_chasers(object->work[0]);
            func_8010AE4C_storm_chasers(object);
            break;
        case 8:
            func_80105B9C_storm_chasers(object->work[0]);
            break;
    }

    if (player->unk_3C == 1 && Hu3DData[object->model[0]].motTime >= 10.0f) {
        Hu3DMotionAttrSet(object->model[0], 1, 1);
        player->unk_3C = 2;
    }
    if (player->unk_20 > 0) {
        if (player->unk_24 <= 0.0f && player->unk_20 == 1) {
            object->trans.y = 0.0f;
            player->unk_34 = 0.0f;
            work->unk40 = 0.0f;
            Hu3DMotionAttrSet(object->model[0], 1, 0);
            if (work->unk5C & 2) {
                player->unk_20 = 0;
                player->unk_3C = 0;
            }
        } else {
            work->unk40 = player->unk_34;
            player->unk_24 += player->unk_28;
            player->unk_28 -= player->unk_2C;
            object->trans.y = player->unk_24;
            player->unk_20 = 1;
        }
    }
    MgPlayerObjMain(object);
    Hu3DModelPosSet(object->model[1], object->trans.x, 2.0f, object->trans.z);
}

void func_8010B1B0_storm_chasers(omObjData *object) {
    s32 modelAttr = 0x2B9;
    s32 shadowAttr = 0xC9;
    u16 character = GwPlayer[object->work[0]].chr;
    s32 modelFile = omCharModelNoTbl[character][0];
    s32 motionFile = omCharModelNoTbl[character][2];
    MgPlayerWork *work;
    StormChaserPlayer *player;

    MgPlayerParamReset();
    MgPlayerCreate(object, modelFile, motionFile, object->work[0], modelAttr, shadowAttr);
    work = object->data;
    work->unkEC = 0;
    Hu3DModelObjAttrSet(object->model[1], 0x80000000, 0);
    Hu3DModelAttrSet(object->model[1], 0x60, 0x20);
    Hu3DModelAttrSet(object->model[1], 0x180, 0x80);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelDynamicFree(object->model[1]);
    object->model[3] = Hu3DModelRead(3, 0x2BD);
    object->model[4] = Hu3DModelRead(4, 0x2BD);
    object->model[8] = Hu3DModelRead(8, 0x2BD);
    MgPlayerMotLoad(object, 0, CharMotionDataNumGet(character, 0), 1, 0);
    MgPlayerMotLoad(object, 1, CharMotionDataNumGet(character, 1), 1, 0);
    MgPlayerMotLoad(object, 2, CharMotionDataNumGet(character, 2), 1, 0);
    MgPlayerMotLoad(object, 0x11, CharMotionDataNumGet(character, 0xE), 0, 0);
    MgPlayerMotLoad(object, 3, CharMotionDataNumGet(character, 0x1D), 1, 0);
    MgPlayerMotLoad(object, 4, CharMotionDataNumGet(character, 0x1E), 1, 0);
    MgPlayerMotLoad(object, 0x20, CharMotionDataNumGet(character, 0x22), 0, 0);
    MgPlayerMotLoad(object, 0x16, CharMotionDataNumGet(character, 0x96), 1, 0);
    MgPlayerMotLoad(object, 0xD, CharMotionDataNumGet(character, 0x2F), 1, 120);
    MgPlayerMotLoad(object, 0xE, CharMotionDataNumGet(character, 0x37), 1, 120);
    MgPlayerMotLoad(object, 0x21, CharMotionDataNumGet(character, 0x97), 2, 0);
    if (object->work[0] == 0) {
        D_8010CF18_storm_chasers = rand8() & 3;
    } else {
        D_8010CF18_storm_chasers++;
        if (D_8010CF18_storm_chasers >= 4) {
            D_8010CF18_storm_chasers = 0;
        }
    }
    object->trans.x = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].unk_00;
    object->trans.y = 0.0f;
    object->trans.z = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].unk_04;
    Hu3DModelPosSet(object->model[1], object->trans.x, 2.0f, object->trans.z);
    object->rot.y = D_8010C8D8_storm_chasers[D_8010CF18_storm_chasers].unk_08;
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    MgPlayerMotSet(object, 0);
    mgFieldStat = 1;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[3], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[4], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[8], HU3D_CAM0);
    MgPlayerMapAttrSet(object, 0, 2);
    func_80105B9C_storm_chasers(object->work[0]);
    work->unk40 = 0.0f;
    object->func = func_8010AF20_storm_chasers;
    player = &D_8010CD80_storm_chasers[object->work[0]];
    player->state = 0;
    player->unk_04 = GwPlayer[object->work[0]].stat & 1;
    player->unk_14 = 0;
    player->unk_08 = 0;
    player->unk_0C = -1;
    player->unk_10 = 0;
    player->unk_18 = 0;
    player->unk_0C = D_8010CF18_storm_chasers;
    player->unk_1C = 0;
    player->unk_20 = 0;
    player->unk_3C = 0;
    player->unk_44 = object;
    player->unk_40 = 0;
    switch (GwPlayer[object->work[0]].cpu_difficulty) {
        case 0:
            player->unk_48 = 300.0f;
            player->unk_4C = 5;
            player->unk_50 = 0;
            break;
        case 1:
            player->unk_48 = 200.0f;
            player->unk_4C = 4;
            player->unk_50 = 0;
            break;
        case 2:
            player->unk_48 = 100.0f;
            player->unk_4C = 3;
            player->unk_50 = 0;
            break;
        case 3:
            player->unk_48 = 70.0f;
            player->unk_4C = 2;
            player->unk_50 = 0;
            break;
    }
    player->unk_56 = 0;
    player->unk_54 = 0;
}

void func_8010B738_storm_chasers(void) {
    s16 i;
    omObjData *obj;
    s32 value;
    u8 unused_stack[8];

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                value = 0;
                break;
            case 1:
                value = 1;
                break;
            case 2:
                value = 2;
                break;
            case 3:
                value = 3;
                break;
            default:
                value = 0;
                break;
        }
        obj = omAddObj(0xC8, 9, 0x3C, -1, func_8010B1B0_storm_chasers);
        obj->work[0] = value;
        mgPlayerObjTbl[mgPlayerObjNum] = obj;
        mgPlayerObjNum++;
    }
}

void func_8010B838_storm_chasers(omObjData *arg0) {
}

void func_8010B840_storm_chasers(omObjData *arg0) {
    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
    } else {
        D_8010CCA4_storm_chasers = 1;
        arg0->func = func_8010B838_storm_chasers;
    }
}

void func_8010B87C_storm_chasers(omObjData *object) {
    s32 i;
    StormChaserPlayer *player;

    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
        return;
    }
    i = 0;
    player = D_8010CD80_storm_chasers;
    for (; i < 4; i++) {
        if (player[i].state == -1) {
            continue;
        }
        if (player[i].unk_1C == 0) {
            break;
        }
    }
    if (i < 4) {
        HuAudSeqPlay(0x65);
        D_8010CCAC_storm_chasers = 0x62;
    } else {
        HuAudSeqPlay(0x6C);
        D_8010CCAC_storm_chasers = 0x90;
    }
    object->func = func_8010B840_storm_chasers;
}

void func_8010B944_storm_chasers(omObjData *arg0) {
    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
    } else {
        D_8010CCA4_storm_chasers = 1;
        arg0->func = func_8010B87C_storm_chasers;
    }
}

void func_8010B980_storm_chasers(omObjData *arg0) {
    s32 i = 0;
    StormChaserData *data = D_8010CCE0_storm_chasers;

    for (; i < 4; i++) {
        if (data[i].state == -1) {
            continue;
        }
        if (data[i].unk_08 != 2) {
            break;
        }
    }
    if (i < 4) {
        return;
    }
    D_8010CCA4_storm_chasers = 1;
    D_8010CCAC_storm_chasers = 10;
    arg0->func = func_8010B944_storm_chasers;
}

void func_8010BA00_storm_chasers(void) {
    s32 ranking[4][3]; // player index, has-item flag, rank
    s32 i;
    s32 j;
    StormChaserPlayer *player;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            ranking[i][j] = -1;
        }
    }

    for (i = 0; i < 4; i++) {
        player = &D_8010CD80_storm_chasers[i];
        if (player->state == -1) {
            continue;
        }
        if (i == 0) {
            ranking[0][0] = 0;
            ranking[0][1] = player->unk_14;
            ranking[0][2] = 0;
            continue;
        }
        for (j = i - 1; j >= 0; j--) {
            if (player->unk_14 > ranking[j][1]) {
                ranking[j + 1][0] = ranking[j][0];
                ranking[j + 1][1] = ranking[j][1];
                ranking[j + 1][2] = ranking[j][2] + 1;
                ranking[j][0] = i;
                ranking[j][1] = player->unk_14;
            } else if (player->unk_14 < ranking[j][1]) {
                ranking[j + 1][0] = i;
                ranking[j + 1][1] = player->unk_14;
                ranking[j + 1][2] = ranking[j][2] + 1;
                break;
            } else if (ranking[j][1] == 0) {
                ranking[j + 1][0] = i;
                ranking[j + 1][1] = player->unk_14;
                ranking[j + 1][2] = ranking[j][2];
                break;
            } else if (rand8() & 1) {
                ranking[j + 1][0] = ranking[j][0];
                ranking[j + 1][1] = ranking[j][1];
                ranking[j + 1][2] = ranking[j][2] + 1;
                ranking[j][0] = i;
                ranking[j][1] = player->unk_14;
            } else {
                ranking[j + 1][0] = i;
                ranking[j + 1][1] = player->unk_14;
                ranking[j + 1][2] = ranking[j][2] + 1;
                break;
            }
        }
    }

    for (i = 0; i < 4; i++) {
        GwPlayer[ranking[i][0]].bonusCoin = ranking[i][2];
        player = &D_8010CD80_storm_chasers[ranking[i][0]];
        player->unk_1C = ranking[i][2];
        if (ranking[i][2] == 0) {
            player->unk_18 = 1;
        }
    }
}

void func_8010BD04_storm_chasers(void) {
    s32 i;
    s32 count;
    StormChaserPlayer *player;

    for (i = 0, count = 0; i < 4; i++) {
        player = &D_8010CD80_storm_chasers[i];
        if (player->state == -1) {
            continue;
        }
        if (player->unk_14 == 0) {
            count++;
        }
    }
    if (count >= 4) {
        for (i = 0; i < 4; i++) {
            player = &D_8010CD80_storm_chasers[i];
            if (player->state == -1) {
                continue;
            }
            GwPlayer[i].bonusCoin = 3;
            player->unk_1C = 3;
            D_8010CAAC_storm_chasers = 0;
        }
    } else {
        func_8010BA00_storm_chasers();
        D_8010CAAC_storm_chasers = 1;
    }
}

void func_8010BDF4_storm_chasers(omObjData *object) {
    s32 i = 0;
    StormChaserData *data = D_8010CCE0_storm_chasers;

    for (; i < 4; i++) {
        if (data[i].state == -1) {
            continue;
        }
        if (data[i].unk_08 != 1) {
            break;
        }
    }
    if (i < 4) {
        return;
    }
    func_8010BD04_storm_chasers();
    D_8010CCA4_storm_chasers = 1;
    object->func = func_8010B980_storm_chasers;
}

void func_8010BE8C_storm_chasers(omObjData *object) {
    s32 i;
    StormChaserPlayer *player;

    if (D_8010CCAC_storm_chasers > 0) {
        D_8010CCAC_storm_chasers--;
    } else {
        i = 0;
        player = D_8010CD80_storm_chasers;
        for (; i < 4; i++) {
            if (player[i].state == -1) {
                continue;
            }
            if (player[i].unk_08 != 1) {
                break;
            }
        }
        if (i >= 4) {
            D_8010CCA4_storm_chasers = 1;
            object->func = func_8010BDF4_storm_chasers;
        }
    }
    if (D_8010C958_storm_chasers > 0) {
        D_8010C958_storm_chasers--;
    }
}

void func_8010BF3C_storm_chasers(omObjData *object) {
    GMesCreate(0x12);
    HuAudSeqFadeOut(0x78);
    D_8010CCAC_storm_chasers = 0x4B;
    object->func = func_8010BE8C_storm_chasers;
}

void func_8010BF84_storm_chasers(omObjData *object) {
    if (D_8010CCAC_storm_chasers != 0) {
        D_8010CCAC_storm_chasers--;
        GMesTimerValueSet((D_8010CCAC_storm_chasers + 0x1D) / 30);
    } else {
        GMesTimerEnd();
        object->func = func_8010BF3C_storm_chasers;
        D_8010CCA4_storm_chasers = 1;
    }
}

void func_8010C014_storm_chasers(omObjData *object) {
    GMesCreate(0x1A, 0x1E, 0xA0, 0x1C);
    D_8010CCAC_storm_chasers = 0x385;
    object->func = func_8010BF84_storm_chasers;
}

void func_8010C060_storm_chasers(omObjData *object) {
    if (++D_8010CAB0_storm_chasers == 0x3F) {
        HuAudSeqPlay(0x38);
    }
    if (GMesStatGet() == 0 || (GMesStatGet() & GMES_STAT_TIMEEND)) {
        object->func = func_8010C014_storm_chasers;
        D_8010CCA4_storm_chasers = 1;
    }
}

void func_8010C0E0_storm_chasers(omObjData *arg0) {
    GMesCreate(7);
    arg0->func = func_8010C060_storm_chasers;
    D_8010CCA4_storm_chasers = 1;
}

void func_8010C120_storm_chasers(omObjData *object) {
    Vec position;
    Vec target;
    Vec result;
    u32 i;

    if (D_8010CCA8_storm_chasers == 0) {
        D_8010CCA8_storm_chasers = 1;
        target.x = 1280.0f;
        target.y = 0.0f;
        target.z = 1900.0f;
        position.x = 70.0f;
        position.y = 0.0f;
        position.z = 20.0f;
        func_80105D64_storm_chasers(&position, &target, &result);
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

void func_8010C240_storm_chasers(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010C264_storm_chasers(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010C240_storm_chasers;
    }
}

void func_8010C29C_storm_chasers(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_8010C264_storm_chasers;
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
    }
}

void func_8010C2F4_storm_chasers(void) {
    D_8010CCA0_storm_chasers += D_8010CCA4_storm_chasers;
    D_8010CCA4_storm_chasers = 0;
}

void func_8010C31C_storm_chasers(omObjData *object) {
    func_8010C2F4_storm_chasers();
    switch (D_8010CCA0_storm_chasers) {
        case 0:
            break;
        case 1:
            if (D_8010CAB4_storm_chasers == -1) {
                D_8010CAB4_storm_chasers = HuAudFXPlay(0x486);
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
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_8010C264_storm_chasers;
            break;
    }
}

void func_8010C3A8_storm_chasers(void) {
    s32 i = 0;
    StormChaserPlayer *data = D_8010CD80_storm_chasers;

    for (; i < 4; i++) {
        data[i].state = -1;
    }
}

void func_8010C3EC_storm_chasers(void) {
    s32 i = 0;
    StormChaserData *data = D_8010CCE0_storm_chasers;

    for (; i < 4; i++) {
        data[i].state = -1;
    }
}

void func_8010C428_storm_chasers(void) {
    D_8010CCC0_storm_chasers.state = -1;
}

void func_8010C438_storm_chasers(void) {
    D_8010CF20_storm_chasers.state = -1;
}

void func_8010C448_storm_chasers(void) {
    s32 i = 0;
    StormChaserEntry *data = D_8010CF38_storm_chasers;

    for (; i < 4; i++) {
        data[i].state = -1;
    }
}

void func_8010C484_storm_chasers(void) {
    s32 i = 0;
    StormChaserState *data = D_8010CEE0_storm_chasers;

    for (; i < 2; i++) {
        data[i].state = -1;
    }
}

void func_8010C4C0_storm_chasers(void) {
    D_8010CCA0_storm_chasers = 0;
    D_8010CCA4_storm_chasers = 0;
    D_8010CCA8_storm_chasers = 0;
    D_8010CF18_storm_chasers = 0;
    func_8010C428_storm_chasers();
    func_8010C438_storm_chasers();
    func_8010C3A8_storm_chasers();
    func_8010C448_storm_chasers();
    func_8010C3EC_storm_chasers();
    func_8010C484_storm_chasers();
}

void func_8010C520_storm_chasers(void) {
    func_8010C4C0_storm_chasers();
    func_8010637C_storm_chasers();
    func_801066BC_storm_chasers();
    func_801075C4_storm_chasers();
    func_801078A0_storm_chasers();
    func_8010B738_storm_chasers();
    func_801069EC_storm_chasers();
    func_80108F88_storm_chasers();
    func_8010834C_storm_chasers();
}

void func_8010C57C_storm_chasers(omObjData *object) {
    MgFlowStatSet(MG_STATE_PLAY);
    func_8010C520_storm_chasers();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = func_8010C31C_storm_chasers;
    omAddObj(0x64, 0, 0, -1, func_8010C120_storm_chasers);
    omAddObj(0x384, 0, 0, -1, func_8010C0E0_storm_chasers);
}

void func_8010C604_storm_chasers(void) {
}

void func_8010C60C_storm_chasers(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010CAB8_storm_chasers[i].scissorX, D_8010CAB8_storm_chasers[i].scissorY,
                   D_8010CAB8_storm_chasers[i].scissorWidth, D_8010CAB8_storm_chasers[i].scissorHeight);
        ViewportSet(i, D_8010CAB8_storm_chasers[i].viewportScale.x, D_8010CAB8_storm_chasers[i].viewportScale.y,
                    D_8010CAB8_storm_chasers[i].viewportScale.z, D_8010CAB8_storm_chasers[i].viewportTranslate.x,
                    D_8010CAB8_storm_chasers[i].viewportTranslate.y, D_8010CAB8_storm_chasers[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010CAB8_storm_chasers[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010C780_storm_chasers(void) {
    MapCollInit(50);
    Hu3DSprModelInit(50);
    omInitObjMan(60, 0);
    omGameSysInit();
    func_8010C60C_storm_chasers();
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, -215.0f, 295.0f, 470.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, -215.0f, 295.0f, 470.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    GMesFontMesCreate(D_8010CC8C_storm_chasers, 0);
    GMesFontMesCreate(D_8010CC8C_storm_chasers, 1);
    omAddObj(1000, 0, 0, -1, func_8010C57C_storm_chasers);
    omAddObj(1000, 0, 0, -1, func_8010C29C_storm_chasers);
    MgFlowInit(&D_8010C8B0_storm_chasers);
}

const s16 D_8010CC8C_storm_chasers[] = { 0x8260, 0x8261, 0x8262, 0 };
