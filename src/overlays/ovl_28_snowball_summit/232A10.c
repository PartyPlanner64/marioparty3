#include "common.h"
#include "overlays/minigame.h"

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

typedef struct UnkSnowballSummitPath {
    /* 0x00 */ Vec start;
    /* 0x0C */ Vec end;
} UnkSnowballSummitPath; // sizeof 0x18

typedef struct SnowballSummitBackdrop {
    /* 0x00 */ s32 state; // -1 when not drawn
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 hookId;
    /* 0x0C */ HuSprite_Unk84_Struct *leftSprite;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ HuSprite_Unk84_Struct *rightSprite;
} SnowballSummitBackdrop; // sizeof 0x18

typedef struct UnkSnowballSummitSnowball {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the snowball is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ omObjData *unk_18; // minigame object that owns the slot
} UnkSnowballSummitSnowball;      // sizeof 0x1C

typedef struct UnkSnowballSummitSlot {
    /* 0x00 */ s32 id; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10; // index into D_8010F9B8_snowball_summit of the object that owns the slot
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
} UnkSnowballSummitSlot; // sizeof 0x40

typedef struct UnkSnowballSummitRoll {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the roll is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ omObjData *unk_14; // minigame object that owns the slot
} UnkSnowballSummitRoll;          // sizeof 0x18

typedef struct UnkSnowballSummitObjSlot {
    /* 0x00 */ s32 id;       // -1 when the slot is unused
    /* 0x04 */ void *unk_04; // minigame object that owns the slot
} UnkSnowballSummitObjSlot;  // sizeof 0x8

typedef struct UnkSnowballSummitThrow {
    /* 0x00 */ s32 state; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} UnkSnowballSummitThrow; // sizeof 0x18

typedef struct UnkSnowballSummitMover {
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
    /* 0x70 */ s32 unk_70; // -1 when unset, else an index into D_8010FC30_snowball_summit
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
} UnkSnowballSummitMover; // sizeof 0x9C

typedef struct UnkSnowballSummitNode {
    /* 0x00 */ s32 id; // -1 when the slot is unused, 0 when the node is dead, 1 when it is in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08; // sound effect id, -1 when unset
    /* 0x0C */ omObjData *unk_0C;
} UnkSnowballSummitNode; // sizeof 0x10

extern s32 D_800A178C_main[][6];

UnkSnowballSummitPath D_8010F550_snowball_summit[3] = {
    { { -50.0f, 500.0f, -800.0f }, { -1200.0f, -330.0f, -800.0f } },
    { { 700.0f, 500.0f, -800.0f }, { -900.0f, -375.0f, -800.0f } },
    { { 1100.0f, 500.0f, -800.0f }, { 200.0f, -350.0f, -800.0f } },
};
// x: trans.x, y: trans.z, z: rot.y
Vec D_8010F598_snowball_summit[4] = {
    { -400.0f, -400.0f, 45.0f },
    { 400.0f, -400.0f, 315.0f },
    { 400.0f, 400.0f, 225.0f },
    { -400.0f, 400.0f, 135.0f },
};
s32 D_8010F5C8_snowball_summit = -1;
SnowballSummitCamera D_8010F5CC_snowball_summit[2] = {
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 24.0f },
    { 0.0f, 0.0f, 320.0f, 240.0f, { 640.0f, 480.0f, 511.0f }, { 640.0f, 480.0f, 511.0f }, 24.0f },
};

extern const s16 D_8010F870_snowball_summit[];

s32 D_8010F880_snowball_summit BSS;
s32 D_8010F884_snowball_summit BSS;
u16 D_8010F888_snowball_summit BSS;
s32 D_8010F88C_snowball_summit BSS;
s16 D_8010F890_snowball_summit BSS;
u8 D_8010F892_snowball_summit BSS;
u8 D_8010F894_snowball_summit[4] BSS; /* Unreferenced. */
s32 D_8010F898_snowball_summit[4] BSS;
s32 D_8010F8A8_snowball_summit BSS;
s16 D_8010F8AC_snowball_summit BSS;
s16 D_8010F8AE_snowball_summit BSS;
s16 D_8010F8B0_snowball_summit BSS;
u8 D_8010F8B4_snowball_summit[0xC] BSS; /* Unreferenced. */
SnowballSummitBackdrop snowballSummitBackdrop BSS;
// func_80106760_snowball_summit accesses the backdrop fields as separate symbols.
extern s32 D_8010F8C0_snowball_summit;                    // snowballSummitBackdrop.state
extern s32 D_8010F8C8_snowball_summit;                    // snowballSummitBackdrop.hookId
extern s16 D_8010F8CA_snowball_summit;                    // snowballSummitBackdrop.hookId (low half)
extern HuSprite_Unk84_Struct *D_8010F8CC_snowball_summit; // snowballSummitBackdrop.leftSprite
extern HuSprite_Unk84_Struct *D_8010F8D4_snowball_summit; // snowballSummitBackdrop.rightSprite
UnkSnowballSummitSnowball D_8010F8D8_snowball_summit[8] BSS;
UnkSnowballSummitMover D_8010F9B8_snowball_summit[4] BSS;
u8 D_8010FC28_snowball_summit[8] BSS; /* Unreferenced. */
UnkSnowballSummitSlot D_8010FC30_snowball_summit[16] BSS;
s16 D_80110030_snowball_summit BSS;
u8 D_80110034_snowball_summit[0x10] BSS; /* Unreferenced. */
s32 D_80110044_snowball_summit BSS;
UnkSnowballSummitRoll D_80110048_snowball_summit[16] BSS;
UnkSnowballSummitObjSlot D_801101C8_snowball_summit[4] BSS;
s32 D_801101E8_snowball_summit BSS;
u8 D_801101EC_snowball_summit[4] BSS; /* Unreferenced. */
s16 D_801101F0_snowball_summit BSS;
u16 D_801101F2_snowball_summit BSS;
f32 D_801101F4_snowball_summit BSS;
f32 D_801101F8_snowball_summit BSS;
u8 D_801101FC_snowball_summit[4] BSS; /* Unreferenced. */
UnkSnowballSummitThrow D_80110200_snowball_summit[3] BSS;
s32 D_80110248_snowball_summit BSS;
s32 D_8011024C_snowball_summit BSS;
UnkSnowballSummitNode D_80110250_snowball_summit[4] BSS;
u8 D_80110290_snowball_summit[0x10] BSS; /* Unreferenced. */

void func_8010F42C_snowball_summit(void);
void func_801062E0_snowball_summit(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_80106758_snowball_summit(omObjData *object);
void func_8010B34C_snowball_summit(omObjData *object);
void func_801070F4_snowball_summit(omObjData *object);
void func_8010C600_snowball_summit(omObjData *object);
void func_8010BEE8_snowball_summit(omObjData *object);
void func_8010C168_snowball_summit(omObjData *object);
void func_8010742C_snowball_summit(omObjData *object);
void func_8010EEEC_snowball_summit(omObjData *object);
void func_8010B9E4_snowball_summit(omObjData *object);
s32 func_8010B994_snowball_summit(omObjData *object);
void func_801061DC_snowball_summit(omObjData *);
void func_80107230_snowball_summit(omObjData *);
void func_80106760_snowball_summit(omObjData *);
void func_8010683C_snowball_summit(omObjData *);
void func_801068EC_snowball_summit(omObjData *);
void func_80106D58_snowball_summit(omObjData *);
void func_8010699C_snowball_summit(omObjData *object);
void func_80107B58_snowball_summit(omObjData *object, Vec stick);
void func_8010B250_snowball_summit(omObjData *object);
void func_8010A940_snowball_summit(omObjData *object);
void func_8010D86C_snowball_summit(void);
void func_8010811C_snowball_summit(omObjData *object);
void func_801075E0_snowball_summit(omObjData *);
void func_80107860_snowball_summit(omObjData *);
void func_8010775C_snowball_summit(omObjData *);
void func_8010C4F4_snowball_summit(omObjData *);
void func_8010BC7C_snowball_summit(omObjData *);
void func_8010C6A8_snowball_summit(omObjData *);
void func_8010C7F0_snowball_summit(omObjData *);
void func_8010C000_snowball_summit(omObjData *);
void func_8010C170_snowball_summit(omObjData *);

void func_801059A0_snowball_summit(void) {
    func_8010F42C_snowball_summit();
}

Gfx **func_801059BC_snowball_summit(Gfx **gfxPos) {
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

Gfx **func_80105AA0_snowball_summit(Gfx **gfxPos) {
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

Gfx **func_80105B6C_snowball_summit(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

void func_80105B9C_snowball_summit(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

f32 func_80105C14_snowball_summit(f32 value) {
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

void func_80105D64_snowball_summit(Vec *position, Vec *target, Vec *result) {
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
            yaw = func_80105C14_snowball_summit(difference.x / difference.z) * 57.2957795130823229;
        } else if (difference.z == 0.0f) {
            yaw = difference.x >= 0.0f ? 90.0f : 270.0f;
        } else {
            yaw = 0.0f;
        }
        if (difference.z < 0.0f) {
            yaw -= 180.0f;
        }
        if (horizontalDistance != 0.0f && difference.y != 0.0f) {
            pitch = func_80105C14_snowball_summit(difference.y / horizontalDistance) * 57.2957795130823229;
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

void func_801060E0_snowball_summit(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

f32 func_8010610C_snowball_summit(f32 y, f32 x) {
    f32 angle = atan2df(y, x);

    if (angle > 360.0) {
        angle -= 360.0;
    } else if (angle < 0.0) {
        angle += 360.0;
    }
    return angle;
}

void func_80106184_snowball_summit(omObjData *object) {
    espPosSet(D_801101F2_snowball_summit, D_801101F4_snowball_summit, D_801101F8_snowball_summit);
}

void func_801061DC_snowball_summit(omObjData *object) {
    D_801101F4_snowball_summit = 160.0f;
    D_801101F8_snowball_summit = 33.0f;
    D_801101F0_snowball_summit = func_8000B838_main(0x490002);
    D_801101F2_snowball_summit = espEntry(D_801101F0_snowball_summit, 0, 0);
    espAttrSet(D_801101F2_snowball_summit, 0x5000);
    espPosSet(D_801101F2_snowball_summit, D_801101F4_snowball_summit, D_801101F8_snowball_summit);
    object->func = func_80106184_snowball_summit;
}

void func_801062AC_snowball_summit(void) {
    omAddObj(0x96, 1, 0, -1, func_801061DC_snowball_summit);
}

void func_801062E0_snowball_summit(Gfx **gfxPos, s32 arg1, s32 arg2) {
    SnowballSummitBackdrop *backdrop = (SnowballSummitBackdrop *)&D_8010F8C0_snowball_summit;
    Gfx *gfx;
    s32 y;

    if (backdrop->state == -1) {
        return;
    }
    gfxPos = func_801059BC_snowball_summit(gfxPos);
    gfx = *gfxPos;
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, backdrop->leftSprite->unk0C);
    for (y = 0; y < 110; y += 10) {
        gDPLoadTextureTile(gfx++, backdrop->leftSprite->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 110,
                           0, y, 104, y + 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
        gSPTextureRectangle(gfx++, 0 << 2, (y + 66) << 2, 104 << 2, (y + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, backdrop->rightSprite->unk0C);
    for (y = 0; y < 110; y += 10) {
        gDPLoadTextureTile(gfx++, backdrop->rightSprite->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 104, 110,
                           0, y, 104, y + 10, 0, G_TX_WRAP, G_TX_WRAP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 104 << 2, 10 << 2);
        gSPTextureRectangle(gfx++, 216 << 2, (y + 66) << 2, 320 << 2, (y + 76) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
    }
    *gfxPos = gfx;
}

void func_80106758_snowball_summit(omObjData *object) {
}

void func_80106760_snowball_summit(omObjData *object) {
    D_8010F8CC_snowball_summit = func_80055194_main(func_8000B838_main(0x490000));
    D_8010F8D4_snowball_summit = func_80055194_main(func_8000B838_main(0x490001));
    D_8010F8C8_snowball_summit = Hu3DHookFuncCreate(0, func_801062E0_snowball_summit, 2);
    Hu3DModelCameraSet(D_8010F8CA_snowball_summit, HU3D_CAM0);
    D_8010F8C0_snowball_summit = 0;
    object->func = func_80106758_snowball_summit;
}

void func_801067FC_snowball_summit(void) {
    omObjData *object = omAddObj(0xA0, 1, 0, -1, func_80106760_snowball_summit);
    object->work[0] = 0;
}

void func_80106834_snowball_summit(omObjData *object) {
}

void func_8010683C_snowball_summit(omObjData *this) {
    *this->model = func_8000B108_main(0x490003, 0x2B9);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 20.0f;
    Hu3DModelCameraSet(*this->model, HU3D_CAM1);
    this->func = func_80106834_snowball_summit;
}

void func_801068B0_snowball_summit(void) {
    omAddObj(0xC8, 1, 0, -1, func_8010683C_snowball_summit);
}

void func_801068E4_snowball_summit(omObjData *object) {
}

void func_801068EC_snowball_summit(omObjData *this) {
    *this->model = func_8000B108_main(0x490006, 0x2B9);
    func_8001C814_main(*this->model, 2, 2);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 0.0f;
    Hu3DModelCameraSet(*this->model, HU3D_CAM0);
    this->func = func_801068E4_snowball_summit;
}

void func_80106968_snowball_summit(void) {
    omAddObj(0xAA, 1, 1, -1, func_801068EC_snowball_summit);
}

void func_8010699C_snowball_summit(omObjData *object) {
    UnkSnowballSummitThrow *throw = &D_80110200_snowball_summit[object->work[0]];
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
            func_8001C258_main(object->model[variant], HU3D_ATTR_DISPOFF, 0);
            func_8001C258_main(object->model[variant ^ 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            object->trans.x = D_8010F550_snowball_summit[object->work[0]].start.x;
            object->trans.y = D_8010F550_snowball_summit[object->work[0]].start.y;
            object->trans.z = D_8010F550_snowball_summit[object->work[0]].start.z;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            throw->unk_08 = (u8)(rand8() % 15) + 30;
            throw->unk_04++;
            throw->state = 2;
            break;
        case 2:
            throw->unk_0C = (D_8010F550_snowball_summit[object->work[0]].end.x - D_8010F550_snowball_summit[object->work[0]].start.x) / throw->unk_08 * throw->unk_04;
            throw->unk_10 = (D_8010F550_snowball_summit[object->work[0]].end.y - D_8010F550_snowball_summit[object->work[0]].start.y) / throw->unk_08 * throw->unk_04;
            throw->unk_14 = (D_8010F550_snowball_summit[object->work[0]].end.z - D_8010F550_snowball_summit[object->work[0]].start.z) / throw->unk_08 * throw->unk_04;
            object->trans.x = D_8010F550_snowball_summit[object->work[0]].start.x + throw->unk_0C;
            object->trans.y = D_8010F550_snowball_summit[object->work[0]].start.y + throw->unk_10;
            object->trans.z = D_8010F550_snowball_summit[object->work[0]].start.z + throw->unk_14;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            if (throw->unk_04 >= throw->unk_08) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                throw->state = 0;
                throw->unk_04 = (u8)(rand8() % 60) + 150;
                throw->unk_0C = throw->unk_10 = throw->unk_14 = 0.0f;
            } else {
                throw->unk_04++;
            }
            break;
    }
}

void func_80106D58_snowball_summit(omObjData *object) {
    UnkSnowballSummitThrow *throw;
    void *data;

    if (object->work[0] == 0) {
        object->model[0] = D_8010F890_snowball_summit = func_8000B108_main(0x490007, 0x2B9);
        object->model[1] = func_8000B108_main(0x490007, 0x2A9);
        data = DataRead(0x490008);
        object->work[1] = D_8010F892_snowball_summit = Hu3DAnimCreate(Hu3DData[object->model[1]].hmf, data, 0, "s240_002_DEF");
        HuMemMemoryFreePerm(data);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F890_snowball_summit);
        object->model[1] = func_8000B108_main(0x490007, 0x2A9);
        object->work[1] = Hu3DAnimLink(Hu3DData[object->model[1]].hmf, D_8010F892_snowball_summit, 0, "s240_002_DEF");
    }
    func_80032FC0_main(object->work[1], 1, 1);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = D_8010F550_snowball_summit[object->work[0]].start.x;
    object->trans.y = D_8010F550_snowball_summit[object->work[0]].start.y;
    object->trans.z = D_8010F550_snowball_summit[object->work[0]].start.z;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    throw = &D_80110200_snowball_summit[object->work[0]];
    throw->state = 0;
    throw->unk_04 = (u8)(rand8() % 60) + 150;
    throw->unk_0C = throw->unk_10 = throw->unk_14 = 0.0f;
    object->func = func_8010699C_snowball_summit;
}

void func_80107000_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        omAddObj(0xB4, 2, 0, -1, func_80106D58_snowball_summit)->work[0] = i;
    }
}

void func_8010705C_snowball_summit(omObjData *object, s32 arg1, f32 arg2, f32 arg3, f32 x, f32 y, f32 z) {
    s32 i;
    UnkSnowballSummitRoll *roll;

    for (i = 0; i < ARRAY_COUNT(D_80110048_snowball_summit); i++) {
        roll = &D_80110048_snowball_summit[i];
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

void func_801070F4_snowball_summit(omObjData *object) {
    UnkSnowballSummitRoll *roll = &D_80110048_snowball_summit[object->work[0]];

    if (roll->state == -1) {
        return;
    }

    switch (roll->state) {
        case 0:
            break;
        case 1:
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, 0);
            roll->state = 2;
            break;
        case 2:
            roll->unk_04 -= roll->unk_08;
            if (roll->unk_04 > 0) {
                func_8001F9E4_main(object->model[0], roll->unk_04);
                object->scale.x += roll->unk_10;
                object->scale.y += roll->unk_10;
                object->scale.z += roll->unk_10;
            } else {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                roll->state = 0;
                roll->unk_04 = 255;
                roll->unk_08 = 0;
                roll->unk_10 = 0;
                object->scale.x = object->scale.y = object->scale.z = 1.0f;
                func_8001F9E4_main(object->model[0], 255);
            }
            break;
    }
}

void func_80107230_snowball_summit(omObjData *object) {
    UnkSnowballSummitRoll *roll;

    object->model[0] = func_8000B108_main(0x490009, 0x289);
    func_8001FA68_main(object->model[0]);
    func_8001F9E4_main(object->model[0], 255);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = func_801070F4_snowball_summit;
    roll = &D_80110048_snowball_summit[object->work[0]];
    roll->state = 0;
    roll->unk_04 = 255;
    roll->unk_08 = 0;
    roll->unk_0C = 1.6f;
    roll->unk_10 = 0.0f;
    roll->unk_14 = object;
}

void func_80107330_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x1F4, 1, 0, -1, func_80107230_snowball_summit)->work[0] = i;
    }
}

void func_8010738C_snowball_summit(omObjData *object, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 x, f32 y, f32 z) {
    s32 i;
    UnkSnowballSummitSnowball *snowball;

    for (i = 0; i < ARRAY_COUNT(D_8010F8D8_snowball_summit); i++) {
        snowball = &D_8010F8D8_snowball_summit[i];
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

void func_8010742C_snowball_summit(omObjData *object) {
    UnkSnowballSummitSnowball *snowball = &D_8010F8D8_snowball_summit[object->work[0]];

    if (snowball->state == -1) {
        return;
    }

    switch (snowball->state) {
        case 0:
            break;
        case 1:
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, 0);
            func_8001C814_main(object->model[0], 1, 0);
            object->scale.x = object->scale.y = object->scale.z = snowball->unk_14;
            snowball->state = 2;
            break;
        case 2:
            snowball->unk_04 -= snowball->unk_08;
            if (snowball->unk_04 > 0) {
                if (snowball->unk_04 < 255) {
                    func_8001F9E4_main(object->model[0], snowball->unk_04);
                } else {
                    func_8001F9E4_main(object->model[0], 255);
                }
                if (object->scale.x < snowball->unk_0C) {
                    object->scale.x += snowball->unk_10;
                    object->scale.y += snowball->unk_10;
                    object->scale.z += snowball->unk_10;
                }
            } else {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(object->model[0], 0);
                func_8001C814_main(object->model[0], 1, 1);
                snowball->state = 0;
                snowball->unk_04 = 450;
                snowball->unk_08 = 0;
                snowball->unk_10 = 0;
                object->scale.x = object->scale.y = object->scale.z = 0.5f;
                func_8001F9E4_main(object->model[0], 255);
            }
            break;
    }
}

void func_801075E0_snowball_summit(omObjData *object) {
    UnkSnowballSummitSnowball *snowball;

    object->model[0] = func_8000B108_main(0x49000A, 0x1689);
    func_8001FA68_main(object->model[0]);
    func_8001F9E4_main(object->model[0], 255);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C814_main(object->model[0], 1, 1);
    Hu3DMotionTimeSet(object->model[0], 0);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.7f;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = func_8010742C_snowball_summit;
    snowball = &D_8010F8D8_snowball_summit[object->work[0]];
    snowball->state = 0;
    snowball->unk_04 = 450;
    snowball->unk_08 = 0;
    snowball->unk_0C = 0.7f;
    snowball->unk_10 = 0.0f;
    snowball->unk_18 = object;
}

void func_80107700_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        omAddObj(0x258, 1, 1, -1, func_801075E0_snowball_summit)->work[0] = i;
    }
}

void func_8010775C_snowball_summit(omObjData *this) {
    s16 *model = &D_80110030_snowball_summit;
    f32 x;
    f32 z;
    s32 i;

    for (i = 0; i < 4; i++) {
        do {
            x = (rand8() - 128) * 12;
            z = i * 720 - 700;
        } while (!(x * x + z * z < 1.0e8f));
        func_8000CD74_main(*model, x, i * 180 + 1000, z);
    }
}

void func_80107860_snowball_summit(omObjData *this) {
    s16 *model = &D_80110030_snowball_summit;

    *model = func_8000CBA0_main(0x49000D, 0x2A9);
    func_8000CD00_main(*model, 15.0f, 110.0f, 8.0f);
    Hu3DModelCameraSet(*model, HU3D_CAM1);
    this->func = func_8010775C_snowball_summit;
}

void func_801078D4_snowball_summit(void) {
    omAddObj(0x3DE, 1, 0, -1, func_80107860_snowball_summit);
}

void func_80107908_snowball_summit(f32 targetX, f32 targetZ, f32 posX, f32 posZ, Vec *result) {
    Vec position;
    Vec target;

    target.x = targetX;
    target.y = 0.0f;
    target.z = targetZ;
    position.x = posX;
    position.y = 0.0f;
    position.z = posZ;
    func_80105D64_snowball_summit(&position, &target, result);
}

void func_80107944_snowball_summit(f32 targetX, f32 targetY, f32 targetZ, f32 posX, f32 posY, f32 posZ, Vec *result) {
    Vec position;
    Vec target;

    target.x = targetX;
    target.y = targetY;
    target.z = targetZ;
    position.x = posX;
    position.y = posY;
    position.z = posZ;
    func_80105D64_snowball_summit(&position, &target, result);
}

s32 func_80107988_snowball_summit(f32 arg0, f32 arg1, f32 arg2) {
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

void func_80107A18_snowball_summit(omObjData *object, Vec stick, f32 speed) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    s32 direction = func_80107988_snowball_summit(object->rot.y, stick.z, speed);
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

void func_80107B58_snowball_summit(omObjData *object, Vec stick) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    UnkSnowballSummitSlot *slot;
    f32 velocity;
    f32 scaled;

    if (stick.x > 70.0f) {
        velocity = 7.0f;
    } else {
        velocity = stick.x * 0.1;
    }
    mover->unk_10 = velocity;
    if (mover->unk_70 != -1) {
        slot = &D_8010FC30_snowball_summit[mover->unk_70];
        scaled = velocity * 0.6;
        mover->unk_10 = velocity * 0.4 + scaled * (1.0f / slot->unk_0C);
    }
    mover->posZ = sindf(object->rot.y) * mover->unk_10;
    mover->unk_28 = cosdf(object->rot.y) * mover->unk_10;
    mover->spawnPosX = object->trans.x + mover->posZ;
    mover->spawnPosZ = object->trans.z + mover->unk_28;
}

void func_80107CA4_snowball_summit(omObjData *object, s32 motion) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    func_8001C5B4_main(object->model[0], object->motion[motion]);
    func_8001C814_main(object->model[0], 2, 2);
    mover->unk_04 = motion;
}

void func_80107D30_snowball_summit(omObjData *object, s32 motion, s16 start, s16 end) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[motion]].motId, start, end, 2);
    mover->unk_04 = motion;
}

void func_80107DD4_snowball_summit(UnkSnowballSummitMover *mover) {
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

s32 func_80107F80_snowball_summit(UnkSnowballSummitMover *mover) {
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

void func_8010811C_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    UnkSnowballSummitMover *other;
    UnkSnowballSummitSlot *slot;
    omObjData *target;
    Vec result;
    f32 angle;
    f32 offset;
    f32 maxDistSq;
    s32 i;

    func_80105B9C_snowball_summit(object->work[0]);
    if (mover->unk_70 != -1 && mover->unk_8C == 1) {
        mover->unk_8C = 0;
        mover->unk_94 = sindf(WRAP_ANGLE(rand16() % 360)) * 70.0f;
        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(rand16() % 360)) * 70.0f);
        D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
        D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
        func_80107DD4_snowball_summit(mover);
        return;
    }

    if (mover->unk_8C != 0) {
        if (rand8() < mover->unk_7C && rand8() < mover->unk_7C) {
            D_800D5558_main[GwPlayer[object->work[0]].pad] |= B_BUTTON;
        }
    }

    if (mover->unk_8C == 0) {
        maxDistSq = 590.0f * 590.0f;
        if (object->trans.x * object->trans.x + object->trans.z * object->trans.z > maxDistSq) {
            func_80107DD4_snowball_summit(mover);
            angle = func_8010610C_snowball_summit(object->trans.x, object->trans.z);
            offset = 180.0 - func_80107F80_snowball_summit(mover) * 0.5;
            mover->unk_94 = sindf(WRAP_ANGLE(angle + offset + func_80107F80_snowball_summit(mover))) * 70.0f;
            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(angle + offset + func_80107F80_snowball_summit(mover))) * 70.0f);
            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
            D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
            return;
        }
    }

    if (mover->unk_70 == -1) {
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
                slot = &D_8010FC30_snowball_summit[i];
                if (slot->id > 0) {
                    target = slot->unk_3C;
                    func_80107908_snowball_summit(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80 && rand8() % mover->unk_88 != 0) {
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f);
                        D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        mover->unk_8C = 0;
                        func_80107DD4_snowball_summit(mover);
                        return;
                    }
                }
            }
        }
        if (mover->unk_8C == 0 && mover->unk_70 == -1 && mover->unk_90 == 0 && rand8() % mover->unk_7C != 0) {
            mover->unk_8C = 1;
            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = D_800D20A1_main[GwPlayer[object->work[0]].pad] = 0;
            mover->unk_94 = mover->unk_96 = 0;
            D_800D5558_main[GwPlayer[object->work[0]].pad] |= B_BUTTON;
            return;
        }
    } else {
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
                slot = &D_8010FC30_snowball_summit[i];
                if (slot->id > 0 && i != mover->unk_70) {
                    target = slot->unk_3C;
                    func_80107908_snowball_summit(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80) {
                        if (rand8() % mover->unk_88 != 0) {
                            if (rand8() % mover->unk_88 != 0) {
                                mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                                mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                            } else {
                                mover->unk_94 = sindf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f;
                                mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 70.0f + (u8)(rand8() % 60))) * 70.0f);
                            }
                            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
                            D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
                            func_80107DD4_snowball_summit(mover);
                            return;
                        }
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                        D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        func_80107DD4_snowball_summit(mover);
                        if (func_80107988_snowball_summit(object->rot.y, WRAP_ANGLE(result.z + 180.0f), 20.0f) == 0) {
                            D_800D5558_main[GwPlayer[object->work[0]].pad] |= A_BUTTON;
                            if (rand8() % mover->unk_88 != 0) {
                                mover->unk_8C = 1;
                                D_800CBB6E_main[GwPlayer[object->work[0]].pad] = D_800D20A1_main[GwPlayer[object->work[0]].pad] = 0;
                                mover->unk_94 = mover->unk_96 = 0;
                                D_800D5558_main[GwPlayer[object->work[0]].pad] |= B_BUTTON;
                                mover->unk_90 = 0;
                                return;
                            }
                        }
                    }
                }
            }
        }
        for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
            if (i == object->work[0]) {
                continue;
            }
            other = &D_8010F9B8_snowball_summit[i];
            if (other->id >= 0 && other->id < 90) {
                target = other->unk_78;
                func_80107908_snowball_summit(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                if (func_80107988_snowball_summit(object->rot.y, WRAP_ANGLE(result.z + 180.0f), 15.0f) == 0 && mover->unk_98 < D_8010FC30_snowball_summit[mover->unk_70].unk_0C && rand8() % mover->unk_88 != 0) {
                    D_800D5558_main[GwPlayer[object->work[0]].pad] |= A_BUTTON;
                    if (rand8() % mover->unk_88 != 0) {
                        mover->unk_8C = 1;
                        D_800CBB6E_main[GwPlayer[object->work[0]].pad] = D_800D20A1_main[GwPlayer[object->work[0]].pad] = 0;
                        mover->unk_94 = mover->unk_96 = 0;
                        D_800D5558_main[GwPlayer[object->work[0]].pad] |= B_BUTTON;
                        mover->unk_90 = 0;
                        return;
                    }
                }
            }
        }
        if (mover->unk_90 < 30) {
            for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
                if (i == object->work[0]) {
                    continue;
                }
                other = &D_8010F9B8_snowball_summit[i];
                if (other->id >= 0 && other->id < 90 && other->unk_08 == 0) {
                    target = other->unk_78;
                    if (rand8() % mover->unk_84 == 0) {
                        func_80107908_snowball_summit(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                        if (ABS(result.x) < mover->unk_80 * 2 && rand8() % mover->unk_88 == 0) {
                            mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
                            D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
                            func_80107DD4_snowball_summit(mover);
                            return;
                        }
                    }
                }
            }
            for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
                if (i == object->work[0]) {
                    continue;
                }
                other = &D_8010F9B8_snowball_summit[i];
                if (other->id >= 0 && other->id < 90) {
                    target = other->unk_78;
                    func_80107908_snowball_summit(object->trans.x, object->trans.z, target->trans.x, target->trans.z, &result);
                    if (ABS(result.x) < mover->unk_80 * 2) {
                        mover->unk_94 = sindf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f;
                        mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(result.z + 180.0f)) * 70.0f);
                        D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
                        D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
                        func_80107DD4_snowball_summit(mover);
                        return;
                    }
                }
            }
        }
    }

    if (mover->unk_8C == 0) {
        if (mover->unk_90 > 0) {
            mover->unk_90--;
            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
            D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
        } else {
            mover->unk_94 = sindf(WRAP_ANGLE(rand16() % 360)) * 70.0f;
            mover->unk_96 = -(s16)(cosdf(WRAP_ANGLE(rand16() % 360)) * 70.0f);
            D_800CBB6E_main[GwPlayer[object->work[0]].pad] = mover->unk_94;
            D_800D20A1_main[GwPlayer[object->work[0]].pad] = mover->unk_96;
            func_80107DD4_snowball_summit(mover);
        }
    }
}

void func_8010A0B0_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    Vec stick;

    switch (mover->unk_04) {
        case 0:
        case 2:
            if (mover->unk_70 != -1) {
                func_80107CA4_snowball_summit(object, 3);
            } else {
                func_80107CA4_snowball_summit(object, 1);
            }
            break;
        case 5:
        case 6:
            if (Hu3DData[object->model[0]].motTime >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 - 2) {
                func_80107CA4_snowball_summit(object, 1);
            } else {
                mover->unk_10 = 0;
                mover->posZ = mover->unk_28 = mover->unk_10;
            }
            break;
        case 3:
        case 4:
            if (mover->unk_70 == -1) {
                func_80107D30_snowball_summit(object, 1, 0, 10);
            } else {
                if (mover->unk_04 == 3 && D_8010FC30_snowball_summit[mover->unk_70].unk_0C >= 1.7) {
                    func_80107D30_snowball_summit(object, 4, 12, 6);
                }
                func_8001C814_main(object->model[0], 2, 2);
                func_8001C814_main(object->model[0], 1, 0);
            }
            break;
    }

    func_80107908_snowball_summit(D_800CBB6E_main[GwPlayer[object->work[0]].pad], -D_800D20A1_main[GwPlayer[object->work[0]].pad], 0.0f, 0.0f, &stick);
    if (mover->unk_70 == -1) {
        func_80107A18_snowball_summit(object, stick, 30.0f);
    } else {
        func_80107A18_snowball_summit(object, stick, 1.0f / (D_8010FC30_snowball_summit[mover->unk_70].unk_0C * D_8010FC30_snowball_summit[mover->unk_70].unk_0C) * 30.0f);
    }
    if (mover->unk_04 != 5 && mover->unk_04 != 6) {
        func_80107B58_snowball_summit(object, stick);
    }
    if (mover->unk_48 == 0) {
        mover->unk_40 = 0;
        mover->unk_44 = 0;
    }
}

void func_8010A384_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    Vec stick;

    switch (mover->unk_04) {
        case 1:
            func_80107CA4_snowball_summit(object, 0);
            break;
        case 2:
            if (mover->unk_40 > 0) {
                break;
            }
            if (mover->unk_48 == 0) {
                func_80107D30_snowball_summit(object, 0, 0, 10);
                break;
            }
            func_80107D30_snowball_summit(object, 3, 12, 10);
            Hu3DMotionTimeSet(object->model[0], 12.0f);
            func_8001C814_main(object->model[0], 2, 0);
            func_8001C814_main(object->model[0], 1, 1);
            break;
        case 3:
        case 4:
            if (mover->unk_70 == -1) {
                func_80107D30_snowball_summit(object, 0, 0, 10);
                break;
            }
            if (mover->unk_04 == 3 && D_8010FC30_snowball_summit[mover->unk_70].unk_0C >= 1.7) {
                func_80107D30_snowball_summit(object, 4, 12, 3);
            }
            Hu3DMotionTimeSet(object->model[0], 12.0f);
            func_8001C814_main(object->model[0], 2, 0);
            func_8001C814_main(object->model[0], 1, 1);
            break;
        case 5:
        case 6:
            if (Hu3DData[object->model[0]].motTime >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 - 2) {
                func_80107CA4_snowball_summit(object, 0);
            }
            break;
    }
    mover->unk_10 = 0;
    mover->posZ = mover->unk_28 = mover->unk_10;

    if (ABS(D_800CBB6E_main[GwPlayer[object->work[0]].pad]) >= 11 || ABS(D_800D20A1_main[GwPlayer[object->work[0]].pad]) >= 11) {
        func_80107908_snowball_summit(D_800CBB6E_main[GwPlayer[object->work[0]].pad], -D_800D20A1_main[GwPlayer[object->work[0]].pad], 0.0f, 0.0f, &stick);
        if (mover->unk_70 == -1) {
            func_80107A18_snowball_summit(object, stick, 30.0f);
        } else {
            func_80107A18_snowball_summit(object, stick, 1.0f / (D_8010FC30_snowball_summit[mover->unk_70].unk_0C * D_8010FC30_snowball_summit[mover->unk_70].unk_0C) * 30.0f);
        }
    }
}

void func_8010A71C_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    if (ABS(D_800CBB6E_main[GwPlayer[object->work[0]].pad]) >= 11) {
        return;
    }
    if (ABS(D_800D20A1_main[GwPlayer[object->work[0]].pad]) >= 11) {
        return;
    }
    if (mover->unk_04 == 5 || mover->unk_04 == 6) {
        return;
    }

    if (mover->unk_04 != 1 && mover->unk_04 != 2) {
        func_80107CA4_snowball_summit(object, 2);
        mover->unk_10 = 0;
        mover->posZ = mover->unk_28 = mover->unk_10;
    } else if (mover->unk_04 != 2 && mover->unk_10 == 0.0f) {
        func_80107CA4_snowball_summit(object, 2);
        mover->posZ = mover->unk_28 = mover->unk_10 = 0.0f;
    }

    mover->unk_40 = 30;
    if (++mover->unk_44 >= 10) {
        mover->unk_70 = func_8010B994_snowball_summit(object);
        mover->unk_48 = 1;
        mover->unk_40 = 0;
        mover->unk_44 = 0;
        func_80107CA4_snowball_summit(object, 3);
        Hu3DMotionTimeSet(object->model[0], 12.0f);
        if (mover->unk_08 == 0) {
            omVibrate(object->work[0], 2, 3, 10);
        }
    } else {
        func_8004AC98_main(0x438, object->work[0]);
    }
}

void func_8010A940_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    UnkSnowballSummitSlot *slot;
    f32 distance;

    switch (mover->unk_04) {
        case 3:
            func_80107CA4_snowball_summit(object, 5);
            slot = &D_8010FC30_snowball_summit[mover->unk_70];
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
            func_80107CA4_snowball_summit(object, 6);
            slot = &D_8010FC30_snowball_summit[mover->unk_70];
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

void func_8010AA78_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    if (mover->unk_04 == 5 || mover->unk_04 == 6) {
        func_8010A384_snowball_summit(object);
    } else if ((D_800D5558_main[GwPlayer[object->work[0]].pad] & A_BUTTON) && mover->unk_48 == 1) {
        func_8010A940_snowball_summit(object);
    } else if (ABS(D_800CBB6E_main[GwPlayer[object->work[0]].pad]) >= 31 || ABS(D_800D20A1_main[GwPlayer[object->work[0]].pad]) >= 31) {
        func_8010A0B0_snowball_summit(object);
    } else {
        func_8010A384_snowball_summit(object);
    }

    if ((D_800D5558_main[GwPlayer[object->work[0]].pad] & B_BUTTON) && mover->unk_48 == 0) {
        func_8010A71C_snowball_summit(object);
    }
    if (mover->unk_48 == 0) {
        if (mover->unk_40 > 0) {
            mover->unk_40--;
        } else {
            mover->unk_44 = 0;
        }
    }
}

void func_8010AC94_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

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

void func_8010AE74_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    if (mover->unk_4C != 0) {
        if (mover->unk_04 != 8) {
            func_80107CA4_snowball_summit(object, 8);
        }
    } else if (mover->unk_74 == 1) {
        if (mover->unk_04 != 7) {
            func_80107CA4_snowball_summit(object, 7);
            func_8001C814_main(object->model[0], 2, 0);
            func_8001C814_main(object->model[0], 1, 1);
        }
    } else if (mover->unk_74 == 2) {
        func_80107CA4_snowball_summit(object, 7);
        func_8001C814_main(object->model[0], 1, 0);
        mover->unk_74 = 3;
    } else if (mover->unk_74 == 3) {
        if (Hu3DData[object->model[0]].motTime >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 - 2) {
            func_80107CA4_snowball_summit(object, 0);
            mover->unk_74 = 0;
            mover->unk_3C = 0;
        }
    }
    if (mover->unk_74 == 1 && mover->unk_3C != 0) {
        func_8010AC94_snowball_summit(object);
    }
}

void func_8010B01C_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    UnkSnowballSummitSlot *slot;

    switch (mover->unk_3C) {
        case 0:
            if (mover->unk_04 != 0) {
                func_80107D30_snowball_summit(object, 0, 0, 10);
                if (mover->unk_70 != -1) {
                    slot = &D_8010FC30_snowball_summit[mover->unk_70];
                    slot->id = 20;
                    slot->unk_10 = -1;
                    mover->unk_48 = 0;
                    mover->unk_70 = -1;
                }
            }
            break;
        case 1:
            if (object->trans.y == 0.0f && mover->unk_04 != 0) {
                func_80107D30_snowball_summit(object, 0, 0, 10);
                object->rot.y = 0.0f;
                break;
            }
            func_8010AE74_snowball_summit(object);
            break;
        case 2:
            func_8010AE74_snowball_summit(object);
            break;
        case 3:
            func_8010AE74_snowball_summit(object);
            break;
    }
    if (mover->unk_04 == 0) {
        object->rot.y = 0.0f;
    }
}

void func_8010B158_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    s32 charBase = D_800A178C_main[GwPlayer[object->work[0]].chr][0];

    if (D_80110044_snowball_summit != 0) {
        if (mover->unk_3C == 0 && mover->unk_04 != 9) {
            func_80107CA4_snowball_summit(object, 9);
            func_8001C814_main(object->model[0], 2, 0);
            func_80045ED0_main(charBase | 0x2F);
        }
    } else if (mover->unk_04 != 10) {
        func_80107CA4_snowball_summit(object, 10);
        func_8001C814_main(object->model[0], 2, 0);
    }
}

void func_8010B250_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];

    if (mover->id == -1) {
        return;
    }

    switch (D_8010F880_snowball_summit) {
        case 2:
            if (mover->unk_08 != 0) {
                func_8010811C_snowball_summit(object);
            }
            if (mover->unk_3C == 0) {
                func_8010AA78_snowball_summit(object);
            } else {
                func_8010AE74_snowball_summit(object);
            }
            break;
        case 3:
            func_80105B9C_snowball_summit(object->work[0]);
            func_8010B01C_snowball_summit(object);
            break;
        case 4:
            func_80105B9C_snowball_summit(object->work[0]);
            func_8010B158_snowball_summit(object);
            break;
        case 0:
        case 1:
        case 5:
            func_80105B9C_snowball_summit(object->work[0]);
            break;
    }
}

void func_8010B34C_snowball_summit(omObjData *object) {
    u16 character = GwPlayer[object->work[0]].chr;
    UnkSnowballSummitMover *mover;

    object->model[0] = func_8000B108_main(D_800A178C_main[character][0] | D_800A178C_main[character][1], 0x2B9);
    func_8000B460_main(object, 0, func_80017BB8_main(character, 0));
    func_8000B460_main(object, 1, func_80017BB8_main(character, 1));
    func_8000B460_main(object, 2, func_80017BB8_main(character, 0x89));
    func_8000B460_main(object, 3, func_80017BB8_main(character, 0x85));
    func_8000B460_main(object, 4, func_80017BB8_main(character, 0x86));
    func_8000B460_main(object, 5, func_80017BB8_main(character, 0x87));
    func_8000B460_main(object, 6, func_80017BB8_main(character, 0x88));
    func_8000B460_main(object, 7, func_80017BB8_main(character, 0xF));
    func_8000B460_main(object, 8, func_80017BB8_main(character, 0x9F));
    func_8000B460_main(object, 9, func_80017BB8_main(character, 0x2F));
    func_8000B460_main(object, 10, func_80017BB8_main(character, 0x38));
    object->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    func_8001C5B4_main(object->model[0], object->motion[0]);
    func_8001C814_main(object->model[0], 2, 2);
    if (object->work[0] == 0) {
        D_8010F8A8_snowball_summit = rand8() & 3;
        object->trans.x = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].x;
        object->trans.y = 0.0f;
        object->trans.z = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].y;
        object->rot.y = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].z;
    } else {
        if (++D_8010F8A8_snowball_summit >= 4) {
            D_8010F8A8_snowball_summit = 0;
        }
        object->trans.x = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].x;
        object->trans.y = 0.0f;
        object->trans.z = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].y;
        object->rot.y = D_8010F598_snowball_summit[D_8010F8A8_snowball_summit].z;
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 20.0f + 5.0f, object->trans.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    object->func = func_8010B250_snowball_summit;

    mover = &D_8010F9B8_snowball_summit[object->work[0]];
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

void func_8010B8E4_snowball_summit(void) {
    omObjData *object;
    s32 player;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = omAddObj(0x12C, 9, 0x3C, -1, func_8010B34C_snowball_summit);
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

s32 func_8010B994_snowball_summit(omObjData *object) {
    s32 i;
    UnkSnowballSummitSlot *slot;

    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id == 0) {
            slot->id = 1;
            slot->unk_10 = object->work[0];
            return i;
        }
    }
    return -1;
}

void func_8010B9E4_snowball_summit(omObjData *object) {
    UnkSnowballSummitSlot *slot = &D_8010FC30_snowball_summit[object->work[0]];
    UnkSnowballSummitMover *mover;

    if (slot->id == -1) {
        return;
    }

    if (D_8010F880_snowball_summit >= 3 && slot->id > 0 && slot->unk_18 == 0) {
        slot->id = 20;
    }

    switch (slot->id) {
        case 0:
            break;
        case 1:
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, 0);
            func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, 0);
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
                D_8011024C_snowball_summit = 0;
            }
            func_8010738C_snowball_summit(object, 30, 0.1f, slot->unk_0C * 0.5, slot->unk_0C * 0.5 + 0.2, 0.0f, 0.0f, 0.0f);
            func_8010705C_snowball_summit(object, 40, slot->unk_0C * 0.1 * 0.5, slot->unk_0C * 1.2 * 0.5, 0.0f, 0.0f, 0.0f);
            if (slot->unk_10 != -1) {
                mover = &D_8010F9B8_snowball_summit[slot->unk_10];
                mover->unk_70 = -1;
                mover->unk_48 = 0;
                mover->unk_40 = 0;
                mover->unk_44 = 0;
            }
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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

void func_8010BC7C_snowball_summit(omObjData *object) {
    UnkSnowballSummitSlot *slot;

    if (object->work[0] == 0) {
        object->model[0] = D_8010F8AC_snowball_summit = func_8000B108_main(0x490004, 0x16B9);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F8AC_snowball_summit);
    }
    object->model[1] = func_8000B0A0_main(0, 0x14C9);
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 10.0f, 0.0f);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y + 20.0f, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 5.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    object->func = func_8010B9E4_snowball_summit;
    slot = &D_8010FC30_snowball_summit[object->work[0]];
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

void func_8010BE8C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x190, 2, 0, -1, func_8010BC7C_snowball_summit)->work[0] = i;
    }
}

void func_8010BEE8_snowball_summit(omObjData *object) {
    UnkSnowballSummitObjSlot *slot = &D_801101C8_snowball_summit[object->work[0]];
    UnkSnowballSummitMover *mover;

    if (slot->id == -1) {
        return;
    }

    mover = &D_8010F9B8_snowball_summit[object->work[0]];
    if (mover->id == -1) {
        slot->id = 0;
    }

    switch (slot->id) {
        case 0:
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (mover->unk_04 == 2) {
                slot->id = 1;
            }
            break;
        case 1:
            func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, 0);
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

void func_8010C000_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover;
    UnkSnowballSummitObjSlot *slot;

    if (object->work[0] == 0) {
        object->model[0] = D_8010F8AE_snowball_summit = func_8000B108_main(0x49000C, 0x1699);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F8AE_snowball_summit);
    }
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C814_main(object->model[0], 2, 2);
    mover = &D_8010F9B8_snowball_summit[object->work[0]];
    object->trans.x = mover->spawnPosX;
    object->trans.y = mover->spawnPosY + 40.0f;
    object->trans.z = mover->spawnPosZ;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = func_8010BEE8_snowball_summit;
    slot = &D_801101C8_snowball_summit[object->work[0]];
    slot->id = 0;
    slot->unk_04 = object;
}

void func_8010C10C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1FE, 1, 1, -1, func_8010C000_snowball_summit)->work[0] = i;
    }
}

void func_8010C168_snowball_summit(omObjData *object) {
}

void func_8010C170_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover;
    UnkSnowballSummitNode *node;

    if (object->work[0] == 0) {
        object->model[0] = D_8010F8B0_snowball_summit = func_8000B108_main(0x49000B, 0x1699);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F8B0_snowball_summit);
    }
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C814_main(object->model[0], 2, 2);
    mover = &D_8010F9B8_snowball_summit[object->work[0]];
    object->trans.x = mover->spawnPosX;
    object->trans.y = mover->spawnPosY + 20.0f;
    object->trans.z = mover->spawnPosZ;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = func_8010C168_snowball_summit;
    node = &D_80110250_snowball_summit[object->work[0]];
    node->id = 0;
    node->unk_04 = 0;
    node->unk_08 = -1;
    node->unk_0C = object;
}

void func_8010C288_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x208, 1, 1, -1, func_8010C170_snowball_summit)->work[0] = i;
    }
}

void func_8010C2E4_snowball_summit(omObjData *arg0) {
}

void func_8010C2EC_snowball_summit(omObjData *arg0) {
    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
    } else {
        D_8010F884_snowball_summit = 1;
        arg0->func = func_8010C2E4_snowball_summit;
    }
}

void func_8010C328_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() & GMES_STAT_TIMEEND) {
        D_8010F88C_snowball_summit = 0x14;
        arg0->func = func_8010C2EC_snowball_summit;
    }
}

s32 func_8010C36C_snowball_summit(void) {
    s32 i = 0;
    s32 count = 0;
    s32 index = -1;
    UnkSnowballSummitMover *mover = D_8010F9B8_snowball_summit;

    for (; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        if ((u32)mover[i].id < 0x5A) {
            count++;
            index = i;
        }
    }

    if (count == 1) {
        D_80110044_snowball_summit = 1;
        return index;
    }
    return -1;
}

void func_8010C3E4_snowball_summit(s32 arg0) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[arg0];

    GwPlayer[mover->unk_78->work[0]].bonusCoin = 10;
    GMesCreate(0x16, GwPlayer[mover->unk_78->work[0]].chr);
    HuAudSeqPlay(0x65);
}

void func_8010C46C_snowball_summit(omObjData *object) {
    s32 index;

    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
    } else {
        index = func_8010C36C_snowball_summit();
        if (index == -1) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
            D_8010F88C_snowball_summit = 0x90;
        } else {
            func_8010C3E4_snowball_summit(index);
        }
        object->func = func_8010C328_snowball_summit;
    }
}

void func_8010C4F4_snowball_summit(omObjData *object) {
    s32 i;
    UnkSnowballSummitMover *mover;

    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
        return;
    }

    for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover = &D_8010F9B8_snowball_summit[i];
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

    if (i >= ARRAY_COUNT(D_8010F9B8_snowball_summit)) {
        D_8010F884_snowball_summit = 1;
        object->func = func_8010C46C_snowball_summit;
    }
}

void func_8010C5C0_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() == 0) {
        D_8010F88C_snowball_summit = 0xF;
        arg0->func = func_8010C4F4_snowball_summit;
    }
}

void func_8010C600_snowball_summit(omObjData *arg0) {
    GMesCreate(0xE);
    HuAudSeqFadeOut(0x78);
    D_8010F88C_snowball_summit = 0x4B;
    arg0->func = func_8010C5C0_snowball_summit;
}

s32 func_8010C648_snowball_summit(void) {
    s32 i = 0;
    u32 count = 0;
    UnkSnowballSummitMover *mover = D_8010F9B8_snowball_summit;

    for (; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
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

void func_8010C6A8_snowball_summit(omObjData *object) {
    s32 result;

    if (D_8010F88C_snowball_summit != 0) {
        D_8010F88C_snowball_summit--;
        func_8003F578_main((D_8010F88C_snowball_summit + 29) / 30);
        result = func_8010C648_snowball_summit();
        if (result == 1) {
            func_8003F5C0_main();
            D_8010F88C_snowball_summit = 90;
            object->func = func_8010C600_snowball_summit;
            D_8010F884_snowball_summit = 1;
        } else if (result == -1) {
            func_8003F5C0_main();
            D_8010F88C_snowball_summit = 90;
            object->func = func_8010C600_snowball_summit;
            HuAudSeqFadeOut(120);
            D_8010F884_snowball_summit = 1;
        }
    } else {
        func_8003F5C0_main();
        object->func = func_8010C600_snowball_summit;
        HuAudSeqFadeOut(120);
        D_8010F884_snowball_summit = 1;
    }
}

void func_8010C7A4_snowball_summit(omObjData *arg0) {
    GMesCreate(0x1A, 0x3C, 0xA0, 0x1C);
    D_8010F88C_snowball_summit = 0x709;
    arg0->func = func_8010C6A8_snowball_summit;
}

void func_8010C7F0_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() == 0 || GMesStatGet() & GMES_STAT_TIMEEND) {
        arg0->func = func_8010C7A4_snowball_summit;
        D_8010F884_snowball_summit = 1;
        HuAudSeqPlay(0x30);
    }
}

void func_8010C850_snowball_summit(omObjData *arg0) {
    GMesCreate(3);
    arg0->func = func_8010C7F0_snowball_summit;
    D_8010F884_snowball_summit = 1;
}

void func_8010C890_snowball_summit(omObjData *object) {
    Vec position;
    Vec target;
    Vec result;
    u32 i;

    if (D_8010F888_snowball_summit == 0) {
        D_8010F888_snowball_summit = 1;
        target.x = 1975.0f;
        target.y = 0.0f;
        target.z = 2700.0f;
        position.x = -40.0f;
        position.y = 0.0f;
        position.z = 45.0f;
        func_80105D64_snowball_summit(&position, &target, &result);
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

void func_8010C9B4_snowball_summit(omObjData *object) {
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010C9E0_snowball_summit(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010C9B4_snowball_summit;
    }
}

void func_8010CA18_snowball_summit(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_8010C9E0_snowball_summit;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

void func_8010CA70_snowball_summit(void) {
    D_8010F880_snowball_summit += D_8010F884_snowball_summit;
    D_8010F884_snowball_summit = 0;
}

s32 func_8010CA98_snowball_summit(UnkSnowballSummitMover *mover) {
    UnkSnowballSummitMover *other;
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
        other = &D_8010F9B8_snowball_summit[i];
        if (other->id == -1) {
            continue;
        }
        func_80107908_snowball_summit(mover->spawnPosX, mover->spawnPosZ, other->spawnPosX, other->spawnPosZ, &delta);
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

s32 func_8010CC00_snowball_summit(UnkSnowballSummitMover *mover) {
    f32 dx = mover->unk_78->trans.x + mover->posZ;
    f32 dz = mover->unk_78->trans.z + mover->unk_28;
    f32 angle;

    if (dx * dx + dz * dz > 476100.0f) {
        if (mover->unk_3C == 0 || mover->unk_74 >= 2) {
            mover->spawnPosY = 20.0f;
            angle = func_8010610C_snowball_summit(mover->spawnPosX, mover->spawnPosZ);
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

void func_8010CD58_snowball_summit(UnkSnowballSummitMover *mover) {
    UnkSnowballSummitMover *other;
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
        other = &D_8010F9B8_snowball_summit[i];
        if (other->id == -1) {
            continue;
        }
        func_80107908_snowball_summit(mover->spawnPosX, mover->spawnPosZ, other->spawnPosX, other->spawnPosZ, &delta);
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

void func_8010D108_snowball_summit(UnkSnowballSummitMover *mover) {
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
        func_8001C258_main(mover->unk_78->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mover->id = 90;
    } else if (mover->spawnPosX * mover->spawnPosX + mover->spawnPosZ * mover->spawnPosZ > 9000000.0f) {
        func_8001C258_main(mover->unk_78->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        mover->id = 90;
    } else {
        angle = func_8010610C_snowball_summit(mover->spawnPosX, mover->spawnPosZ);
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

void func_8010D304_snowball_summit(UnkSnowballSummitMover *mover) {
    omObjData *object = mover->unk_78;
    f32 angle;

    if (mover->unk_3C == 2 || mover->unk_3C == 3) {
        object->trans.x = mover->spawnPosX;
        object->trans.y = mover->spawnPosY;
        object->trans.z = mover->spawnPosZ;
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 5.0f, object->trans.z);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
                angle = func_8010610C_snowball_summit(mover->spawnPosX, mover->spawnPosZ);
                func_8010705C_snowball_summit(mover->unk_78, 40, 0.1f, 1.6f, sindf(angle) * 50.0f, 60.0f, cosdf(angle) * 50.0f);
                mover->unk_6C = 1;
            } else {
                mover->unk_6C--;
            }
        }
    }
}

void func_8010D55C_snowball_summit(UnkSnowballSummitMover *mover) {
    omObjData *object = mover->unk_78;
    UnkSnowballSummitMover *other;
    omObjData *otherObject;
    Vec delta;
    f32 radius;
    f32 dist;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == object->work[0]) {
            continue;
        }
        other = &D_8010F9B8_snowball_summit[i];
        if (other->id == 90) {
            continue;
        }
        if (other->unk_4C != 0) {
            continue;
        }
        otherObject = other->unk_78;
        func_80107908_snowball_summit(object->trans.x, object->trans.z, otherObject->trans.x, otherObject->trans.z, &delta);
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

void func_8010D86C_snowball_summit(void) {
    UnkSnowballSummitMover *mover;
    s32 iterations = 0;
    s32 resolved;
    s32 i;
    s32 j;

    do {
        resolved = 1;
        iterations++;
        for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
            mover = &D_8010F9B8_snowball_summit[i];
            for (j = 0; j < ARRAY_COUNT(mover->unk_5C); j++) {
                mover->unk_5C[j] = 0;
            }
            mover->unk_58 = 0;
        }
        for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
            mover = &D_8010F9B8_snowball_summit[i];
            if (mover->id != -1 && mover->unk_3C == 0) {
                if (func_8010CA98_snowball_summit(mover)) {
                    resolved = 0;
                }
            }
        }
        for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
            mover = &D_8010F9B8_snowball_summit[i];
            if (mover->id != -1 && mover->unk_4C == 0) {
                func_8010CC00_snowball_summit(mover);
            }
        }
        for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
            mover = &D_8010F9B8_snowball_summit[i];
            if (mover->id != -1 && mover->unk_58 == 1 && mover->unk_3C == 0) {
                func_8010CD58_snowball_summit(mover);
            }
        }
    } while (resolved == 0 && iterations < 10);

    for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover = &D_8010F9B8_snowball_summit[i];
        if (mover->id != -1 && mover->unk_4C == 1) {
            func_8010D108_snowball_summit(mover);
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover = &D_8010F9B8_snowball_summit[i];
        if (mover->id != -1) {
            func_8010D304_snowball_summit(mover);
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover = &D_8010F9B8_snowball_summit[i];
        if (mover->id != -1 && mover->unk_3C == 1) {
            func_8010D55C_snowball_summit(mover);
        }
    }
}

void func_8010DB10_snowball_summit(UnkSnowballSummitSlot *slot) {
    UnkSnowballSummitMover *mover;
    UnkSnowballSummitNode *node;
    f32 x = slot->unk_3C->trans.x;
    f32 z = slot->unk_3C->trans.z;
    f32 angle;

    if (x * x + z * z > 476100.0f) {
        if (slot->unk_10 != -1) {
            mover = &D_8010F9B8_snowball_summit[slot->unk_10];
            node = &D_80110250_snowball_summit[slot->unk_10];
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
        angle = func_8010610C_snowball_summit(slot->unk_3C->trans.x, slot->unk_3C->trans.z);
        slot->unk_3C->trans.x += sindf(angle) * (slot->unk_0C * 37.5);
        slot->unk_3C->trans.z += cosdf(angle) * (slot->unk_0C * 37.5);
        func_8001C258_main(slot->unk_3C->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        slot->unk_18 = 0;
    }
}

void func_8010DD00_snowball_summit(UnkSnowballSummitSlot *slot) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[slot->unk_10];
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
        func_8010705C_snowball_summit(object, 40, 0.1f, 1.6f, 0.0f, 0.0f, 0.0f);
    }
}

void func_8010DFD0_snowball_summit(UnkSnowballSummitSlot *slot) {
    omObjData *object = slot->unk_3C;
    f32 speed;
    f32 x;
    f32 y;
    f32 z;

    if (D_8011024C_snowball_summit == 0) {
        slot->unk_38 = HuAudFXPlay(0x43A);
        if (slot->unk_38 != -1) {
            slot->unk_34 = 1;
            D_8011024C_snowball_summit = 1;
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
        func_8010705C_snowball_summit(object, 20, 0.2f, 2.0f, x, y, z);
    }
}

void func_8010E2F4_snowball_summit(UnkSnowballSummitSlot *slot) {
    omObjData *object = slot->unk_3C;
    f32 angle;

    if (slot->unk_34 == 1 && slot->unk_38 != -1) {
        HuAudFXStop((s16)slot->unk_38);
        slot->unk_34 = 0;
        slot->unk_38 = -1;
        D_8011024C_snowball_summit = 0;
    }

    if (slot->unk_24 >= 7.0f) {
        slot->unk_24 = 7.0f;
    } else {
        slot->unk_24 += 1.0f;
    }

    if (slot->unk_28 > 0) {
        slot->unk_28--;
    } else {
        func_8010705C_snowball_summit(object, 40, slot->unk_0C * 0.1 * 0.5, slot->unk_0C * 1.2 * 0.5, 0.0f, 0.0f, 0.0f);
        slot->unk_28 = 1;
    }

    if (object->trans.y < -1200.0f) {
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        slot->id = 0;
        slot->unk_18 = 0;
        slot->unk_1C = 0;
        slot->unk_20 = 0;
        slot->unk_24 = 0;
        slot->unk_10 = -1;
        slot->unk_28 = 0;
    } else {
        angle = func_8010610C_snowball_summit(object->trans.x, object->trans.z);
        object->trans.x += slot->unk_24 * slot->unk_24 * cosdf(slot->unk_1C) * sindf(angle);
        object->trans.z += slot->unk_24 * slot->unk_24 * cosdf(slot->unk_1C) * cosdf(angle);
        object->trans.y += slot->unk_20 * slot->unk_20 * sindf(slot->unk_1C);
    }
}

void func_8010E52C_snowball_summit(UnkSnowballSummitSlot *slot) {
    omObjData *object = slot->unk_3C;
    UnkSnowballSummitMover *mover;
    UnkSnowballSummitNode *node;
    omObjData *moverObject;
    Vec delta;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i == slot->unk_10) {
            continue;
        }
        mover = &D_8010F9B8_snowball_summit[i];
        if (mover->id == 90) {
            continue;
        }
        if (mover->unk_4C != 0) {
            continue;
        }
        moverObject = mover->unk_78;
        func_80107908_snowball_summit(object->trans.x, object->trans.z, moverObject->trans.x, moverObject->trans.z, &delta);
        if (slot->unk_0C * 37.5 + mover->unk_50 > ABS(delta.x) && moverObject->trans.y < slot->unk_0C * 37.5 + slot->unk_0C * 37.5) {
            if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                HuAudFXStop((s16)slot->unk_38);
                slot->unk_34 = 0;
                slot->unk_38 = -1;
                D_8011024C_snowball_summit = 0;
            }
            if (slot->unk_10 != -1) {
                node = &D_80110250_snowball_summit[slot->unk_10];
                if (node->unk_04 == 1 && node->unk_08 != -1) {
                    HuAudFXStop((s16)node->unk_08);
                    node->unk_04 = 0;
                    node->unk_08 = -1;
                }
            }
            func_8004AC98_main(0x43C, mover->unk_78->work[0]);
            D_8010F898_snowball_summit[moverObject->work[0]] = 30;
            slot->id = 20;
            mover->unk_74 = 1;
            mover->unk_3C = 1;
            if (slot->unk_0C < 2.0f) {
                mover->unk_10 = slot->unk_0C * 10.0f;
                mover->unk_24 = slot->unk_0C * 16.0f;
            } else {
                mover->unk_10 = slot->unk_0C * 15.0f;
                mover->unk_24 = slot->unk_0C * 20.0f;
                func_8004AC98_main(0x43E, mover->unk_78->work[0]);
            }
            mover->unk_2C = 4.0f;
            mover->posX = delta.z;
            if (mover->unk_70 != -1) {
                D_8010FC30_snowball_summit[mover->unk_70].id = 20;
            }
            if (mover->unk_08 == 0) {
                omVibrate(moverObject->work[0], 20, 0, 20);
            }
        }
    }
}

void func_8010E824_snowball_summit(UnkSnowballSummitSlot *slot) {
    omObjData *object = slot->unk_3C;
    UnkSnowballSummitSlot *other;
    UnkSnowballSummitNode *node;
    Vec delta;
    s32 i;

    func_8010E52C_snowball_summit(slot);
    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        if (i == object->work[0]) {
            continue;
        }
        other = &D_8010FC30_snowball_summit[i];
        if (other->id <= 0) {
            continue;
        }
        func_80107908_snowball_summit(object->trans.x, object->trans.z, other->unk_3C->trans.x, other->unk_3C->trans.z, &delta);
        if (slot->unk_0C * 37.5 + other->unk_0C * 37.5 > ABS(delta.x)) {
            if (slot->unk_10 != -1) {
                slot->id = 20;
                if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                    HuAudFXStop((s16)slot->unk_38);
                    slot->unk_34 = 0;
                    slot->unk_38 = -1;
                    D_8011024C_snowball_summit = 0;
                }
                node = &D_80110250_snowball_summit[slot->unk_10];
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
                    D_8011024C_snowball_summit = 0;
                }
            } else {
                slot->id = 20;
                if (slot->unk_34 == 1 && slot->unk_38 != -1) {
                    HuAudFXStop((s16)slot->unk_38);
                    slot->unk_34 = 0;
                    slot->unk_38 = -1;
                    D_8011024C_snowball_summit = 0;
                }
            }
            HuAudFXPlay(0x43F);
        }
    }
}

void func_8010EA68_snowball_summit(void) {
    UnkSnowballSummitSlot *slot;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            if (slot->unk_10 != -1) {
                func_8010DD00_snowball_summit(slot);
            } else {
                func_8010DFD0_snowball_summit(slot);
            }
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            func_8010DB10_snowball_summit(slot);
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id > 0 && slot->unk_18 == 0) {
            func_8010E824_snowball_summit(slot);
        }
    }
    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id > 0 && slot->id < 20 && slot->unk_18 == 1) {
            func_8010E2F4_snowball_summit(slot);
        }
    }
}

void func_8010EBC0_snowball_summit(void) {
    UnkSnowballSummitNode *node;
    UnkSnowballSummitMover *mover;
    UnkSnowballSummitSlot *slot;
    s32 i;

    for (i = 0; i < 4; i++) {
        node = &D_80110250_snowball_summit[i];
        if (node->id == -1) {
            return;
        }
        mover = &D_8010F9B8_snowball_summit[i];
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
                func_8001C258_main(node->unk_0C->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if ((mover->unk_04 == 3 || mover->unk_04 == 4) && mover->unk_10 > 0.0f) {
                    node->id = 1;
                }
                break;
            case 1:
                func_8001C258_main(node->unk_0C->model[0], HU3D_ATTR_DISPOFF, 0);
                if (node->unk_04 != 1 && node->unk_08 == -1) {
                    node->unk_08 = func_8004AC98_main(0x439, mover->unk_78->work[0]);
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
            slot = &D_8010FC30_snowball_summit[mover->unk_70];
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
    if (D_8010F880_snowball_summit >= 3 && node->unk_04 == 1 && node->unk_08 != -1) {
        HuAudFXStop((s16)node->unk_08);
        node->unk_04 = 0;
        node->unk_08 = -1;
    }
}

void func_8010EEEC_snowball_summit(omObjData *object) {
    func_8010CA70_snowball_summit();
    switch (D_8010F880_snowball_summit) {
        case 0:
            break;
        case 1:
            if (D_8010F5C8_snowball_summit == -1) {
                D_8010F5C8_snowball_summit = HuAudFXPlay(0x43D);
            }
            break;
        case 2:
        case 3:
            func_8010D86C_snowball_summit();
            func_8010EA68_snowball_summit();
            func_8010EBC0_snowball_summit();
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_8010C9E0_snowball_summit;
            break;
    }
}

void func_8010EFA0_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitMover *mover;

    for (i = 0, mover = D_8010F9B8_snowball_summit; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover[i].id = -1;
    }
}

void func_8010EFE4_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitThrow *throwSlot;

    for (i = 0, throwSlot = D_80110200_snowball_summit; i < ARRAY_COUNT(D_80110200_snowball_summit); i++) {
        throwSlot[i].state = -1;
    }
}

void func_8010F020_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitRoll *roll;

    for (i = 0, roll = D_80110048_snowball_summit; i < ARRAY_COUNT(D_80110048_snowball_summit); i++) {
        roll[i].state = -1;
    }
}

void func_8010F05C_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitSlot *slot;

    for (i = 0, slot = D_8010FC30_snowball_summit; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot[i].id = -1;
    }
}

void func_8010F090_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitSnowball *snowball;

    for (i = 0, snowball = D_8010F8D8_snowball_summit; i < ARRAY_COUNT(D_8010F8D8_snowball_summit); i++) {
        snowball[i].state = -1;
    }
}

void func_8010F0CC_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitObjSlot *slot;

    for (i = 0, slot = D_801101C8_snowball_summit; i < ARRAY_COUNT(D_801101C8_snowball_summit); i++) {
        slot[i].id = -1;
    }
}

void func_8010F100_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitNode *node;

    for (i = 0, node = D_80110250_snowball_summit; i < ARRAY_COUNT(D_80110250_snowball_summit); i++) {
        node[i].id = -1;
    }
}

void func_8010F134_snowball_summit(void) {
    D_8010F880_snowball_summit = 0;
    D_8010F884_snowball_summit = 0;
    D_8010F888_snowball_summit = 0;
    D_80110044_snowball_summit = 0;
    D_80110248_snowball_summit = -1;
    D_801101E8_snowball_summit = 0;
    D_8011024C_snowball_summit = 0;
    func_8010EFA0_snowball_summit();
    func_8010EFE4_snowball_summit();
    func_8010F05C_snowball_summit();
    func_8010F020_snowball_summit();
    func_8010F0CC_snowball_summit();
    func_8010F100_snowball_summit();
    func_8010F090_snowball_summit();
}

void func_8010F1B8_snowball_summit(void) {
    func_8010F134_snowball_summit();
    func_801062AC_snowball_summit();
    func_801067FC_snowball_summit();
    func_80106968_snowball_summit();
    func_80107000_snowball_summit();
    func_801068B0_snowball_summit();
    func_8010B8E4_snowball_summit();
    func_8010BE8C_snowball_summit();
    func_80107330_snowball_summit();
    func_8010C10C_snowball_summit();
    func_8010C288_snowball_summit();
    func_80107700_snowball_summit();
    func_801078D4_snowball_summit();
}

void func_8010F234_snowball_summit(omObjData *object) {
    func_8010F1B8_snowball_summit();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    object->func = func_8010EEEC_snowball_summit;
    omAddObj(0x64, 0, 0, -1, func_8010C890_snowball_summit);
    omAddObj(0x384, 0, 0, -1, func_8010C850_snowball_summit);
}

void func_8010F2B0_snowball_summit(void) {
}

void func_8010F2B8_snowball_summit(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010F5CC_snowball_summit[i].scissorX, D_8010F5CC_snowball_summit[i].scissorY,
                   D_8010F5CC_snowball_summit[i].scissorWidth, D_8010F5CC_snowball_summit[i].scissorHeight);
        ViewportSet(i, D_8010F5CC_snowball_summit[i].viewportScale.x, D_8010F5CC_snowball_summit[i].viewportScale.y,
                    D_8010F5CC_snowball_summit[i].viewportScale.z, D_8010F5CC_snowball_summit[i].viewportTranslate.x,
                    D_8010F5CC_snowball_summit[i].viewportTranslate.y, D_8010F5CC_snowball_summit[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010F5CC_snowball_summit[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010F42C_snowball_summit(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(100, 0);
    func_8004A208_main();
    func_8010F2B8_snowball_summit();
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, -215.0f, 295.0f, 470.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, -215.0f, 295.0f, 470.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010F870_snowball_summit, 0);
    func_80045010_main(D_8010F870_snowball_summit, 1);
    omAddObj(1000, 0, 0, -1, func_8010F234_snowball_summit);
    omAddObj(1000, 0, 0, -1, func_8010CA18_snowball_summit);
}

const s16 D_8010F870_snowball_summit[] = { 0x8260, 0x8261, 0x8262, 0 };
