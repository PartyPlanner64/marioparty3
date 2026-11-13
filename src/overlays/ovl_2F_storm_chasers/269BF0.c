#include "common.h"
#include "overlays/minigame.h"

typedef struct StormChaserData {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
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
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ omObjData *unk_10;
} StormChaserState; // sizeof 0x14

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
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
    /* 0x34 */ s32 unk_34;
    /* 0x38 */ s32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ s32 unk_40;
    /* 0x44 */ omObjData *unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ s32 unk_4C;
    /* 0x50 */ s32 unk_50;
    /* 0x54 */ s16 unk_54;
    /* 0x56 */ s16 unk_56;
} StormChaserPlayer; // sizeof 0x58

extern s32 D_8010CAB0_storm_chasers;
extern s16 D_8010CAB4_storm_chasers;
extern s32 D_8010CCA0_storm_chasers;
extern s32 D_8010CCA4_storm_chasers;
extern s16 D_8010CCA8_storm_chasers;
extern s32 D_8010CCAC_storm_chasers;
extern s32 D_8010CCC0_storm_chasers; // state field of an unmapped 0x20 byte struct
extern StormChaserPlayer D_8010CD80_storm_chasers[4];
extern StormChaserData D_8010CCE0_storm_chasers[4];
extern StormChaserState D_8010CEE0_storm_chasers[2];
extern StormChaserEntry D_8010CF38_storm_chasers[4];
extern u16 D_8010CF0A_storm_chasers;
extern f32 D_8010CF0C_storm_chasers;
extern f32 D_8010CF10_storm_chasers;
extern s32 D_8010CF18_storm_chasers;
extern s32 D_8010CF20_storm_chasers; // state field of an unmapped 0x18 byte struct
extern s32 D_8010CF68_storm_chasers;
extern s32 D_8010CF6C_storm_chasers;
extern s16 D_8010CF6E_storm_chasers;
extern s32 D_8010CF70_storm_chasers;
extern s16 D_8010CF72_storm_chasers;
extern HuSprite_Unk84_Struct *D_8010CF74_storm_chasers;

void func_80106218_storm_chasers(omObjData *);
void func_8010637C_storm_chasers(void);
void func_801063B0_storm_chasers(Gfx **, s32, s32);
void func_8010662C_storm_chasers(omObjData *);
void func_801066BC_storm_chasers(void);
void func_801068C8_storm_chasers(omObjData *);
void func_801069EC_storm_chasers(void);
void func_8010746C_storm_chasers(omObjData *);
void func_801075C4_storm_chasers(void);
void func_801077A0_storm_chasers(omObjData *);
void func_801078A0_storm_chasers(void);
void func_80107F70_storm_chasers(omObjData *);
void func_8010834C_storm_chasers(void);
void func_80108C64_storm_chasers(omObjData *);
void func_80108F88_storm_chasers(void);
void func_8010B1B0_storm_chasers(omObjData *);
void func_8010B738_storm_chasers(void);
void func_8010B87C_storm_chasers(omObjData *);
void func_8010BE8C_storm_chasers(omObjData *);
void func_8010BF84_storm_chasers(omObjData *);
void func_8010C060_storm_chasers(omObjData *);
void func_8010C0E0_storm_chasers(omObjData *);
void func_8010C120_storm_chasers(omObjData *);
void func_8010C2F4_storm_chasers(void);
void func_8010C3A8_storm_chasers(void);
void func_8010C3EC_storm_chasers(void);
void func_8010C448_storm_chasers(void);
void func_8010C484_storm_chasers(void);
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
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
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

void func_801061C0_storm_chasers(void) {
    espPosSet(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106218_storm_chasers);

void func_8010637C_storm_chasers(void) {
    omAddObj(0x96, 1, 0, -1, func_80106218_storm_chasers);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801063B0_storm_chasers);

void func_80106624_storm_chasers(omObjData *object) {
}

void func_8010662C_storm_chasers(omObjData *object) {
    D_8010CF6C_storm_chasers = func_8000B838_main(0x500001);
    D_8010CF74_storm_chasers = func_80055194_main(D_8010CF6E_storm_chasers);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801066F4_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106794_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801068C8_storm_chasers);

void func_801069EC_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0xD2, 1, 0, -1, func_801068C8_storm_chasers)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106A48_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106F98_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801070A8_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010746C_storm_chasers);

void func_801075C4_storm_chasers(void) {
    omAddObj(0xAA, 2, 1, -1, func_8010746C_storm_chasers);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801075F8_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801077A0_storm_chasers);

void func_801078A0_storm_chasers(void) {
    omObjData *object = omAddObj(0xB4, 1, 0, -1, func_801077A0_storm_chasers);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801078E0_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80107EA4_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80107F70_storm_chasers);

void func_8010834C_storm_chasers(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        omAddObj(0x190, 3, 1, -1, func_80107F70_storm_chasers)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801083A8_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80108478_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801085E4_storm_chasers);

void func_801086C4_storm_chasers(omObjData *object) {
    StormChaserData *data = &D_8010CCE0_storm_chasers[object->work[0]];

    func_8001C5B4_main(object->model[0], object->motion[1]);
    func_8001C814_main(object->model[0], 2, 2);
    data->state = 0xC;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80108738_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010891C_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80108C64_storm_chasers);

void func_80108F88_storm_chasers(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x12C, 2, 2, -1, func_80108C64_storm_chasers)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80108FF8_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801090A4_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80109170_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010A070_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010A260_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010AC7C_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010AD68_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010AE4C_storm_chasers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", D_8010CC30_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010AF20_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010B1B0_storm_chasers);

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
        D_800EC598_minigame[D_800EC280_minigame] = obj;
        D_800EC280_minigame++;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010B87C_storm_chasers);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010BA00_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010BD04_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010BDF4_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010BE8C_storm_chasers);

void func_8010BF3C_storm_chasers(omObjData *object) {
    GMesCreate(0x12);
    HuAudSeqFadeOut(0x78);
    D_8010CCAC_storm_chasers = 0x4B;
    object->func = func_8010BE8C_storm_chasers;
}

void func_8010BF84_storm_chasers(omObjData *object) {
    if (D_8010CCAC_storm_chasers != 0) {
        D_8010CCAC_storm_chasers--;
        func_8003F578_main((D_8010CCAC_storm_chasers + 0x1D) / 30);
    } else {
        func_8003F5C0_main();
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C120_storm_chasers);

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
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_8010C264_storm_chasers;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
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
    D_8010CCC0_storm_chasers = -1;
}

void func_8010C438_storm_chasers(void) {
    D_8010CF20_storm_chasers = -1;
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
    func_800E6F0C_minigame(2);
    func_8010C520_storm_chasers();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = func_8010C31C_storm_chasers;
    omAddObj(0x64, 0, 0, -1, func_8010C120_storm_chasers);
    omAddObj(0x384, 0, 0, -1, func_8010C0E0_storm_chasers);
}

void func_8010C604_storm_chasers(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C60C_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C780_storm_chasers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", D_8010CC8C_storm_chasers);
