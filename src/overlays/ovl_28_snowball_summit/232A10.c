#include "common.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define WRAP_ANGLE(angle) \
    ((angle) >= 360.0f ? (angle) - 360.0f : ((angle) < 0.0f ? (angle) + 360.0f : (angle)))

extern s32 D_8010F880_snowball_summit;
extern s32 D_8010F884_snowball_summit;
extern u16 D_8010F888_snowball_summit;
extern s32 D_8010F88C_snowball_summit;
extern s32 D_80110044_snowball_summit;
extern s32 D_801101E8_snowball_summit;
extern u16 D_801101F2_snowball_summit;
extern f32 D_801101F4_snowball_summit;
extern f32 D_801101F8_snowball_summit;
extern s32 D_80110248_snowball_summit;
extern s32 D_8011024C_snowball_summit;
extern s16 D_80110030_snowball_summit;
extern s32 D_8010F8C0_snowball_summit;
extern s32 D_8010F8C8_snowball_summit;
extern s16 D_8010F8CA_snowball_summit;
extern HuSprite_Unk84_Struct *D_8010F8CC_snowball_summit;
extern HuSprite_Unk84_Struct *D_8010F8D4_snowball_summit;
extern s16 D_801101F0_snowball_summit;
extern s16 D_8010F8AC_snowball_summit;
extern s16 D_8010F8AE_snowball_summit;
extern s16 D_8010F8B0_snowball_summit;
extern s32 D_800A178C_main[][6];

typedef struct SnowballSummitCamera {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} SnowballSummitCamera; // sizeof 0x2C

extern SnowballSummitCamera D_8010F5CC_snowball_summit[];
extern const s16 D_8010F870_snowball_summit[];

typedef struct UnkSnowballSummitSnowball {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the snowball is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ omObjData *unk_18; // minigame object that owns the slot
} UnkSnowballSummitSnowball;      // sizeof 0x1C

extern UnkSnowballSummitSnowball D_8010F8D8_snowball_summit[8];

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

extern UnkSnowballSummitSlot D_8010FC30_snowball_summit[16];

typedef struct UnkSnowballSummitRoll {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the roll is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ omObjData *unk_14; // minigame object that owns the slot
} UnkSnowballSummitRoll;          // sizeof 0x18

extern UnkSnowballSummitRoll D_80110048_snowball_summit[16];

typedef struct UnkSnowballSummitObjSlot {
    /* 0x00 */ s32 id;       // -1 when the slot is unused
    /* 0x04 */ void *unk_04; // minigame object that owns the slot
} UnkSnowballSummitObjSlot;  // sizeof 0x8

extern UnkSnowballSummitObjSlot D_801101C8_snowball_summit[4];

typedef struct UnkSnowballSummitThrow {
    /* 0x00 */ s32 state; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} UnkSnowballSummitThrow; // sizeof 0x18

extern UnkSnowballSummitThrow D_80110200_snowball_summit[3];

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
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 unk_68;
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

extern UnkSnowballSummitMover D_8010F9B8_snowball_summit[4];

typedef struct UnkSnowballSummitStick {
    /* 0x00 */ f32 magnitude;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 angle;
} UnkSnowballSummitStick; // sizeof 0xC, passed by value

typedef struct UnkSnowballSummitNode {
    /* 0x00 */ s32 id; // -1 when the slot is unused, 0 when the node is dead, 1 when it is in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08; // sound effect id, -1 when unset
    /* 0x0C */ void *unk_0C;
} UnkSnowballSummitNode; // sizeof 0x10

extern UnkSnowballSummitNode D_80110250_snowball_summit[4];

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801062E0_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010699C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80106D58_snowball_summit);

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

void func_80107A18_snowball_summit(omObjData *object, UnkSnowballSummitStick stick, f32 speed) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    s32 direction = func_80107988_snowball_summit(object->rot.y, stick.angle, speed);
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
                object->rot.y = stick.angle;
            }
            break;
    }
    mover->posX = object->rot.y;
}

// NON_MATCHING: float register allocation differs around the 0.6/0.4 blend.
#ifdef NON_MATCHING
void func_80107B58_snowball_summit(omObjData *object, UnkSnowballSummitStick stick) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    f32 velocity;
    f32 scaled;

    if (stick.magnitude > 70.0f) {
        velocity = 7.0f;
    } else {
        velocity = stick.magnitude * 0.1;
    }
    mover->unk_10 = velocity;
    if (mover->unk_70 != -1) {
        scaled = velocity * 0.6;
        mover->unk_10 = velocity * 0.4 + scaled * (1.0f / D_8010FC30_snowball_summit[mover->unk_70].unk_0C);
    }
    mover->posZ = sindf(object->rot.y) * mover->unk_10;
    mover->unk_28 = cosdf(object->rot.y) * mover->unk_10;
    mover->spawnPosX = object->trans.x + mover->posZ;
    mover->spawnPosZ = object->trans.z + mover->unk_28;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107B58_snowball_summit);
#endif

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010811C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A0B0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A384_snowball_summit);

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

// NON_MATCHING: the double intermediates for `distance` are allocated to $f20 instead of $f2.
#ifdef NON_MATCHING
void func_8010A940_snowball_summit(omObjData *object) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[object->work[0]];
    UnkSnowballSummitSlot *slot;
    f32 distance;

    switch (mover->unk_04) {
        case 3:
            func_80107CA4_snowball_summit(object, 5);
            break;
        case 4:
            func_80107CA4_snowball_summit(object, 6);
            break;
        default:
            return;
    }

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
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A940_snowball_summit);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AA78_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AE74_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B01C_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B250_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B34C_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B9E4_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA98_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CD58_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D304_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D55C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D86C_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DD00_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DFD0_snowball_summit);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E52C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E824_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EA68_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EBC0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EEEC_snowball_summit);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", D_8010F870_snowball_summit);
