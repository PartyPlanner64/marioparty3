#include "common.h"
#include "overlays/minigame.h"

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
} HideAndSneakWork; // sizeof 0x84

typedef struct {
    /* 0x00 */ s8 unk_00;
    /* 0x01 */ s8 unk_01; // movement step
    /* 0x02 */ s8 unk_02;
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ s8 unk_05;
} HideAndSneakUnk788; // sizeof 0x06

typedef struct {
    /* 0x00 */ s8 unk_00; // nonzero when the solo player is CPU controlled
    /* 0x01 */ s8 unk_01; // CPU state
    /* 0x02 */ s8 unk_02; // stick X
    /* 0x03 */ s8 unk_03; // timer
    /* 0x04 */ s8 unk_04; // duration
    /* 0x05 */ s8 unk_05; // direction change count
    /* 0x06 */ s8 unk_06; // direction change limit
    /* 0x07 */ s8 unk_07; // target column
} HideAndSneakSoloCpu;    // sizeof 0x08

typedef struct {
    /* 0x00 */ u8 count;
    /* 0x01 */ s8 slots[3];
} HideAndSneakSpot; // sizeof 0x04

typedef struct {
    /* 0x00 */ s16 sprite;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 unk_06;
} HideAndSneakSprite; // sizeof 0x08

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} HideAndSneakSpritePos; // sizeof 0x04

typedef struct {
    /* 0x00 */ f32 scissorX;
    /* 0x04 */ f32 scissorY;
    /* 0x08 */ f32 scissorWidth;
    /* 0x0C */ f32 scissorHeight;
    /* 0x10 */ Vec viewportScale;
    /* 0x1C */ Vec viewportTranslate;
    /* 0x28 */ f32 fov;
} HideAndSneakCamera; // sizeof 0x2C

extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern s16 D_8010C370_hide_and_sneak[5][4];
extern s32 D_8010C398_hide_and_sneak[8];
extern f32 D_8010C3E4_hide_and_sneak[4];
extern f32 D_8010C3F4_hide_and_sneak[4];
extern s16 D_8010C474_hide_and_sneak[4];
extern const char *D_8010C47C_hide_and_sneak[4];
extern const char *D_8010C48C_hide_and_sneak[4];
extern s16 D_8010C49C_hide_and_sneak[4];
extern HideAndSneakSpritePos D_8010C4A4_hide_and_sneak[4];
extern s16 D_8010C4B4_hide_and_sneak[4];
extern s32 D_8010C4BC_hide_and_sneak;
extern HideAndSneakCamera D_8010C4C0_hide_and_sneak[2];
extern const s16 D_8010C754_hide_and_sneak[];
extern HideAndSneakSprite D_8010C760_hide_and_sneak[4];
extern s8 D_8010C780_hide_and_sneak;
extern s8 D_8010C782_hide_and_sneak;
extern HideAndSneakUnk788 D_8010C788_hide_and_sneak[4];
// Work slots: [0] obj 0x1F4, [1] solo player, [2..4] team players (by work[1]), [5..8] and [9..12] per-player objects,
// [13] screen fade (unk_04 is its alpha)
extern HideAndSneakWork D_8010C7A0_hide_and_sneak[50];
extern HideAndSneakSoloCpu D_8010E168_hide_and_sneak;
extern s8 D_8010E170_hide_and_sneak;
extern s8 D_8010E174_hide_and_sneak;
extern s8 D_8010E175_hide_and_sneak[4];
extern s16 D_8010E17A_hide_and_sneak;
extern s8 D_8010E17C_hide_and_sneak;
extern u8 D_8010E17D_hide_and_sneak[3];
extern s8 D_8010E180_hide_and_sneak;
extern s8 D_8010E182_hide_and_sneak[4];
extern u8 D_8010E186_hide_and_sneak;
extern HideAndSneakSpot D_8010E188_hide_and_sneak[4];
extern HuSprite_Unk84_Struct *D_8010E198_hide_and_sneak[4];
extern u8 D_8010E1A8_hide_and_sneak;
extern u8 D_8010E1A9_hide_and_sneak[3];
extern s8 D_8010E1AC_hide_and_sneak;
extern s8 D_8010E1AD_hide_and_sneak;
extern u8 D_8010E1AE_hide_and_sneak[3];
extern s8 D_8010E1B2_hide_and_sneak;
extern s8 D_8010E1B3_hide_and_sneak;

void func_80106730_hide_and_sneak(omObjData *object);
void func_80106738_hide_and_sneak(omObjData *);
void func_80106D10_hide_and_sneak(omObjData *object);
void func_80107638_hide_and_sneak(omObjData *);
void func_80107B30_hide_and_sneak(omObjData *object);
void func_80109D88_hide_and_sneak(omObjData *object);
void func_8010A1CC_hide_and_sneak(omObjData *object);
void func_8010A6BC_hide_and_sneak(omObjData *object);
void func_8010A88C_hide_and_sneak(omObjData *);
void func_8010AAC8_hide_and_sneak(omObjData *);
void func_8010ACC4_hide_and_sneak(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_8010AF98_hide_and_sneak(omObjData *object);
void func_8010AFA0_hide_and_sneak(omObjData *);
void func_8010B33C_hide_and_sneak(omObjData *object);
void func_8010B410_hide_and_sneak(omObjData *);
void func_8010BD40_hide_and_sneak(omObjData *object);
void func_8010BFE8_hide_and_sneak(omObjData *object);
void func_8010C220_hide_and_sneak(void);

void func_801059A0_hide_and_sneak(void) {
    func_8010C220_hide_and_sneak();
}

f32 func_801059BC_hide_and_sneak(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_hide_and_sneak(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_hide_and_sneak(void) {
    HideAndSneakWork *work;
    u32 i;

    for (i = 0, work = D_8010C7A0_hide_and_sneak; i < 50; i++, work++) {
        work->obj = NULL;
        work->unk_04 = 0;
        work->unk_06 = 0;
        work->unk_08 = 0;
        work->unk_0A = 0;
        work->unk_0C = 0;
        work->unk_0E = 0;
        work->unk_10 = 0;
        work->unk_12 = 0;
        work->unk_14 = 0;
        work->unk_16 = 0;
        work->unk_18 = 0;
        work->unk_1C = 0;
        work->unk_20 = 0;
        work->unk_24 = 0;
        work->unk_28 = 0;
        work->unk_2C = 0;
        work->unk_30 = 0;
        work->unk_34 = 0;
        work->unk_38 = 0;
        work->unk_3C = 0;
        work->unk_40 = -1;
        work->unk_42 = -1;
        work->unk_44.x = work->unk_44.y = work->unk_44.z = 0.0f;
        work->unk_50.x = work->unk_50.y = work->unk_50.z = 0.0f;
        work->unk_5C.x = work->unk_5C.y = work->unk_5C.z = 0.0f;
        work->unk_68 = 0.0f;
        work->unk_6C = 0.0f;
        work->unk_70 = 0.0f;
        work->unk_74 = 0.0f;
        work->unk_78.x = work->unk_78.y = work->unk_78.z = 0.0f;
    }
}

void func_80105B3C_hide_and_sneak(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

Gfx **func_80105BB4_hide_and_sneak(Gfx **gfxPos) {
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

Gfx **func_80105C98_hide_and_sneak(Gfx **gfxPos) {
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

Gfx **func_80105D64_hide_and_sneak(Gfx **gfxPos, s32 alpha) {
    Gfx *gfx = *gfxPos;

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
    *gfxPos = gfx;
    return gfxPos;
}

void func_80105D94_hide_and_sneak(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 dx = (arg0 - arg2) * 5.0f;
    f32 dz = (arg1 - arg3) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = func_801059BC_hide_and_sneak(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105EC4_hide_and_sneak);

s32 func_801064F4_hide_and_sneak(s32 arg0) {
    return rand8() % arg0;
}

void func_80106548_hide_and_sneak(omObjData *object, u16 motionIndex, s16 arg2) {
    func_8001C5B4_main(object->model[0], object->motion[motionIndex]);
    func_8001C814_main(object->model[0], arg2, arg2);
}

void func_801065B0_hide_and_sneak(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

s32 func_8010661C_hide_and_sneak(omObjData *object, f32 target) {
    f32 current = object->rot.y;
    f32 diff = target - current;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 10.0f) {
        object->rot.y = target;
    } else {
        if (current < target) {
            if (diff > 180.0f) {
                object->rot.y = func_801059BC_hide_and_sneak(object->rot.y, -10.0f);
            } else {
                object->rot.y = func_801059BC_hide_and_sneak(object->rot.y, 10.0f);
            }
        } else if (target < current) {
            if (diff > 180.0f) {
                object->rot.y = func_801059BC_hide_and_sneak(object->rot.y, 10.0f);
            } else {
                object->rot.y = func_801059BC_hide_and_sneak(object->rot.y, -10.0f);
            }
        } else {
            return 0;
        }
        return 1;
    }
    return 0;
}

void func_80106730_hide_and_sneak(omObjData *object) {
}

void func_80106738_hide_and_sneak(omObjData *object) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[0];

    work->unk_44.x = 160.0f;
    work->unk_44.y = 120.0f;
    work->unk_40 = func_8000B838_main(0x270000);
    work->unk_42 = espEntry(work->unk_40, 0, 0);
    espAttrSet(work->unk_42, 0x5000);
    espPosSet(work->unk_42, work->unk_44.x, work->unk_44.y);
    work->unk_44.x = 160.0f;
    work->unk_44.y = 231.0f;
    work->unk_40 = func_8000B838_main(0x270001);
    work->unk_42 = espEntry(work->unk_40, 0, 0);
    espAttrSet(work->unk_42, 0x1000);
    espPosSet(work->unk_42, work->unk_44.x, work->unk_44.y);
    object->model[0] = func_8000B108_main(0x270003, 0x299);
    object->model[1] = func_8000B108_main(0x270002, 0x299);
    object->model[2] = func_8000B108_main(0x27000C, 0x299);
    Hu3DMotionSpeedSet(object->model[0], 0.0f);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], 4.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
    object->func = func_80106730_hide_and_sneak;
}

void func_80106960_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[0].obj = omAddObj(0x1F4, 4, 2, -1, func_80106738_hide_and_sneak);
}

void func_8010699C_hide_and_sneak(omObjData *object, s8 motion) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[1];
    s16 mode = 0;

    if (work->unk_06 != motion) {
        switch (motion) {
            case 0:
            case 1:
            case 3:
                mode = 2;
                break;
            case 2:
            case 4:
            case 5:
            case 6:
            case 7:
                mode = 0;
                break;
        }
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        func_801065B0_hide_and_sneak(object, motion, 0, 10, mode);
        if (motion == 6) {
            func_80045ED0_main((D_8010C398_hide_and_sneak[GwPlayer[object->work[0]].chr] << 16) | 0x30);
        }
        work->unk_06 = motion;
    }
}

s32 func_80106ABC_hide_and_sneak(omObjData *object) {
    HideAndSneakSoloCpu *cpu = &D_8010E168_hide_and_sneak;

    if (cpu->unk_00 != 0) {
        func_80105B3C_hide_and_sneak(object->work[0]);
        // Reading the state through the global rather than `cpu` is required to match.
        switch (D_8010E168_hide_and_sneak.unk_01) {
            case 0:
                cpu->unk_05 = 0;
                cpu->unk_06 = func_801064F4_hide_and_sneak(9 - D_8010C782_hide_and_sneak);
                cpu->unk_02 = func_801064F4_hide_and_sneak(2) * 40 - 20;
                cpu->unk_03 = 0;
                cpu->unk_04 = (D_8010C782_hide_and_sneak - 1) * 9;
                cpu->unk_07 = func_801064F4_hide_and_sneak(D_8010C782_hide_and_sneak);
                cpu->unk_01++;
                break;
            case 1:
                D_800CBB6E_main[object->work[3]] = cpu->unk_02;
                cpu->unk_03++;
                if (cpu->unk_03 >= cpu->unk_04) {
                    cpu->unk_05++;
                    if (cpu->unk_05 >= cpu->unk_06) {
                        cpu->unk_01 = 2;
                    } else {
                        cpu->unk_02 = -cpu->unk_02;
                        cpu->unk_03 = 0;
                        cpu->unk_04 = (D_8010C782_hide_and_sneak - 1) * 18;
                    }
                }
                break;
            case 2:
                if (D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][cpu->unk_07] < object->trans.x) {
                    D_800CBB6E_main[object->work[3]] = -20;
                } else if (object->trans.x < D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][cpu->unk_07]) {
                    D_800CBB6E_main[object->work[3]] = 20;
                } else if (object->trans.x == D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][cpu->unk_07]) {
                    cpu->unk_01 = 0;
                    return 1;
                }
                break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106D10_hide_and_sneak);

void func_80107638_hide_and_sneak(omObjData *object) {
    HideAndSneakSoloCpu *cpu = &D_8010E168_hide_and_sneak;
    u16 character = GwPlayer[object->work[0]].chr;

    object->model[0] = func_8000B108_main(D_800A178C_main[character][0] | D_800A178C_main[character][3], 0x2B9);
    func_8000B460_main(object, 0, func_80017BB8_main(character, 0));
    func_8000B460_main(object, 1, func_80017BB8_main(character, 1));
    func_8000B460_main(object, 2, func_80017BB8_main(character, 0x14));
    func_8000B460_main(object, 3, func_80017BB8_main(character, 0x6C));
    func_8000B460_main(object, 4, func_80017BB8_main(character, 0x33));
    func_8000B460_main(object, 5, func_80017BB8_main(character, 0x3A));
    func_8000B460_main(object, 6, func_80017BB8_main(character, 0x30));
    func_8000B460_main(object, 7, func_80017BB8_main(character, 0x36));
    object->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    object->rot.y = 180.0f;
    func_80106548_hide_and_sneak(object, 0, 2);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
    cpu->unk_00 = GwPlayer[object->work[0]].stat & 1;
    cpu->unk_01 = 0;
    object->work[3] = GwPlayer[object->work[0]].pad;
    object->func = func_80106D10_hide_and_sneak;
}

void func_801078E4_hide_and_sneak(void) {
    omObjData *obj;
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
    obj = omAddObj(0x2BC, 3, 0xA, -1, func_80107638_hide_and_sneak);
    obj->work[0] = playerIndex;
    D_8010C7A0_hide_and_sneak[1].obj = obj;
    D_8010E1A8_hide_and_sneak = obj->work[0];
    D_8010E186_hide_and_sneak = GwPlayer[obj->work[0]].chr;
}

void func_801079E8_hide_and_sneak(omObjData *object) {
    s8 i;

    for (i = 0; i < 4; i++) {
        if (D_8010E182_hide_and_sneak[i] != 0) {
            if (D_8010C3E4_hide_and_sneak[i] - 150.0f < object->trans.x && object->trans.x < D_8010C3E4_hide_and_sneak[i] + 150.0f && D_8010C3F4_hide_and_sneak[i] - 20.0f < object->trans.z &&
                object->trans.z < D_8010C3F4_hide_and_sneak[i] + 100.0f) {
                func_8001C258_main(object->model[0], 4, 4);
                break;
            }
            func_8001C258_main(object->model[0], 4, 0);
        }
    }
}

void func_80107B30_hide_and_sneak(omObjData *object) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[2 + object->work[1]];

    if (object->work[2] == 0) {
        if (work->unk_14 != 0) {
            HuAudFXStop(work->unk_14);
        }
        work->unk_14 = PlayerFXPlay(0x28, object->work[0]);
    }
    object->work[2] = (object->work[2] + 1) % 11;
}

void func_80107BD8_hide_and_sneak(omObjData *object, s8 motion) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[2 + object->work[0]];
    s8 mode = 0;

    if (work->unk_06 != motion) {
        switch (motion) {
            case 0:
                mode = 2;
                break;
            case 1:
                mode = 2;
                break;
            case 2:
                mode = 2;
                break;
            case 3:
                mode = 0;
                break;
            case 4:
                mode = 0;
                break;
        }
        func_801065B0_hide_and_sneak(object, motion, 0, 15, mode);
        Hu3DMotionSpeedSet(object->model[0], 1.0f);
        work->unk_06 = motion;
        if (motion == 4) {
            func_80045ED0_main((D_8010C398_hide_and_sneak[GwPlayer[object->work[0]].chr] << 16) | 0x30);
        }
    }
}

s8 func_80107CF4_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];
    s8 candidates[4];
    s8 i;
    s8 count;

    for (i = 0, count = 0; i < 4; i++) {
        if (D_8010E182_hide_and_sneak[i] != 0 && entry->unk_04 != i) {
            candidates[count] = i;
            count++;
        }
    }
    return candidates[func_801064F4_hide_and_sneak(count)];
}

s32 func_80107D98_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -700.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -700.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < -250.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80107EF0_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -600.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -600.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -850.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -850.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < -400.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108040_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 0.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108130_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > -50.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -50.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -850.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -850.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -400.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -400.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108278_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.z > -1100.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1100.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.x < 60.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.z > -1350.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1350.0f;
                entry->unk_01++;
            }
            break;
        case 3:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_8010841C_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 150.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -1200.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -1200.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -400.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -400.0f;
                entry->unk_01++;
            }
            break;
        case 3:
            if (object->trans.z < -850.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -850.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108588_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 150.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108670_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 60.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x > -250.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801087B4_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -1350.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -1350.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801088A0_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.z > -1600.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1600.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.x > -250.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = -250.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108990_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 60.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 60.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z > -1350.0f) {
                object->trans.z -= 24.0f;
                object->rot.y = 180.0f;
            } else {
                object->trans.z = -1350.0f;
                entry->unk_01++;
            }
            break;
        case 2:
            if (object->trans.x < 475.0f) {
                object->trans.x += 24.0f;
                object->rot.y = 90.0f;
            } else {
                object->trans.x = 475.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108AF0_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];

    switch (entry->unk_01) {
        case 0:
            if (object->trans.x > 150.0f) {
                object->trans.x -= 24.0f;
                object->rot.y = 270.0f;
            } else {
                object->trans.x = 150.0f;
                entry->unk_01++;
            }
            break;
        case 1:
            if (object->trans.z < -575.0f) {
                object->trans.z += 24.0f;
                object->rot.y = 0.0f;
            } else {
                object->trans.z = -575.0f;
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_80108BD8_hide_and_sneak(void) {
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108BE0_hide_and_sneak);

void func_80109578_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010E188_hide_and_sneak[i].slots[0] = -1;
        D_8010E188_hide_and_sneak[i].slots[1] = -1;
        D_8010E188_hide_and_sneak[i].slots[2] = -1;
        D_8010E188_hide_and_sneak[i].count = 0;
    }
}

void func_801095DC_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 3; i++) {
        HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[2 + i];

        if (work->unk_04 == 0 && work->unk_08 != -1) {
            s8 spot = work->unk_08;

            D_8010E188_hide_and_sneak[spot].slots[i] = D_8010E188_hide_and_sneak[spot].count;
            D_8010E188_hide_and_sneak[spot].count++;
        }
    }
}

void func_80109688_hide_and_sneak(omObjData *object) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[2 + object->work[1]];
    s8 pad = object->work[3];
    s8 candidates[4];
    s8 i;
    s8 count;
    s16 stickX;
    s16 stickY;

    if (GwPlayer[object->work[0]].stat & 1) {
        if (work->unk_08 == -1) {
            for (i = 0, count = 0; i < 4; i++) {
                if (D_8010E182_hide_and_sneak[i] != 0) {
                    candidates[count] = i;
                    count++;
                }
            }
            work->unk_08 = candidates[func_801064F4_hide_and_sneak(count)];
        }
    } else {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        if (abs(stickX) > 10 || abs(stickY) > 10) {
            if (abs(stickX) > abs(stickY)) {
                if (stickX < 0 && D_8010E182_hide_and_sneak[0] != 0) {
                    work->unk_08 = 0;
                }
                if (stickX > 0 && D_8010E182_hide_and_sneak[3] != 0) {
                    work->unk_08 = 3;
                }
            } else {
                if (stickY > 0 && D_8010E182_hide_and_sneak[1] != 0) {
                    work->unk_08 = 1;
                }
                if (stickY < 0 && D_8010E182_hide_and_sneak[2] != 0) {
                    work->unk_08 = 2;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109870_hide_and_sneak);

s32 func_80109BF4_hide_and_sneak(omObjData *object) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[2 + object->work[1]];

    if (work->unk_04 == 0) {
        return 0;
    }
    if (work->unk_04 == 2) {
        return 1;
    }
    func_80107B30_hide_and_sneak(object);
    if (work->unk_0C != 0) {
        work->unk_0C--;
    } else {
        if (work->unk_16 == 0) {
            work->unk_16++;
            PlayerFXPlay(0x286, object->work[0]);
        }
        if (abs(object->trans.x) > 1000) {
            work->unk_04 = 2;
            func_8001C258_main(object->model[0], 4, 4);
            func_8001C258_main(object->model[1], 4, 4);
            D_8010E1A9_hide_and_sneak[object->work[1]] = 0;
            return 1;
        }
        if (object->trans.x < 0.0f) {
            object->rot.y = 270.0f;
            object->trans.x -= 24.0f;
        } else {
            object->rot.y = 90.0f;
            object->trans.x += 24.0f;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109D88_hide_and_sneak);

void func_8010A1CC_hide_and_sneak(omObjData *object) {
    HideAndSneakUnk788 *entry = &D_8010C788_hide_and_sneak[object->work[1]];
    u16 character = GwPlayer[object->work[0]].chr;

    object->model[0] = func_8000B108_main(D_800A178C_main[character][0] | D_800A178C_main[character][3], 0x2B9);
    func_8000B460_main(object, 0, func_80017BB8_main(character, 0));
    func_8000B460_main(object, 1, func_80017BB8_main(character, 2));
    func_8000B460_main(object, 3, func_80017BB8_main(character, 0x79));
    func_8000B460_main(object, 4, func_80017BB8_main(character, 0x30));
    func_8000B460_main(object, 2, func_80017BB8_main(character, 0x70));
    object->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    func_80088800_main(Hu3DData[object->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    switch (object->work[1]) {
        case 0:
            object->trans.x = -220.0f;
            break;
        case 1:
            object->trans.x = 0.0f;
            break;
        case 2:
            object->trans.x = 220.0f;
            break;
    }
    object->trans.y = 125.0f;
    object->trans.z = -300.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    func_80106548_hide_and_sneak(object, 0, 2);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
    entry->unk_00 = 0;
    entry->unk_01 = 0;
    entry->unk_02 = func_801064F4_hide_and_sneak(2);
    entry->unk_03 = 0;
    entry->unk_04 = 0;
    entry->unk_05 = 0;
    object->work[3] = GwPlayer[object->work[0]].pad;
    object->func = func_80109D88_hide_and_sneak;
}

void func_8010A48C_hide_and_sneak(void) {
    s8 slots[3];
    u16 playerIndex = 0;
    s32 count = 0;
    s8 i;
    s8 j;
    s8 choice;

    for (i = 0; i < 3; i++) {
        slots[i] = i;
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group != 0) {
            HideAndSneakWork *work;
            omObjData *object;

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
            work = &D_8010C7A0_hide_and_sneak[2 + count];
            object = omAddObj(0x258, 3, 6, -1, func_8010A1CC_hide_and_sneak);
            object->work[0] = playerIndex;
            work->obj = object;
            D_8010E17D_hide_and_sneak[count] = object->work[0];
            D_8010E1AE_hide_and_sneak[count] = GwPlayer[object->work[0]].chr;
            choice = func_801064F4_hide_and_sneak(3 - count);
            object->work[1] = slots[choice];
            slots[choice] = -1;
            for (j = 1; j < 3 - count; j++) {
                if (slots[j - 1] == -1) {
                    slots[j - 1] = slots[j];
                    slots[j] = -1;
                }
            }
            count++;
        }
    }
}

void func_8010A6BC_hide_and_sneak(omObjData *object) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[5 + object->work[0]];

    func_8001E888_main(object->model[0], 0.0f, work->unk_04, 0x60, 0x40, D_8010C47C_hide_and_sneak[object->work[0]], 0);
    func_8001E888_main(object->model[0], 0.0f, work->unk_04, 0x60, 0x40, D_8010C48C_hide_and_sneak[object->work[0]], 0);
}

s32 func_8010A7A4_hide_and_sneak(void) {
    s8 i = 0;
    s8 count1 = 0;
    s8 count2 = 0;
    HideAndSneakWork *players = &D_8010C7A0_hide_and_sneak[5];

    while (i < 4) {
        if (players[i].unk_04 == 0) {
            count1++;
        }
        if (D_8010E182_hide_and_sneak[i] != 0) {
            count2++;
        }
        i++;
    }

    return count1 == count2;
}

s32 func_8010A824_hide_and_sneak(void) {
    s8 i = 0;
    s8 count = 0;
    HideAndSneakWork *players = &D_8010C7A0_hide_and_sneak[5];

    while (i < 4) {
        if (players[i].unk_04 == -0x40) {
            count++;
        }
        i++;
    }
    return count == 4;
}

void func_8010A88C_hide_and_sneak(omObjData *object) {
    s8 index = object->work[0];
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[5 + index];

    switch (D_8010E1B3_hide_and_sneak) {
        case 1:
            if (index == D_8010E17C_hide_and_sneak) {
                if (work->unk_16 == 0) {
                    HuAudFXPlay(0x32C);
                    work->unk_16++;
                }
                if (work->unk_04 < -0x3F) {
                    work->unk_04 = -0x40;
                    D_8010E182_hide_and_sneak[index] = 0;
                    D_8010C760_hide_and_sneak[index].unk_06 = 1;
                    work->unk_08++;
                    if (work->unk_08 > 20) {
                        D_8010E1B3_hide_and_sneak = 2;
                    }
                } else if (omPauseChk() + D_800D6A90_main == 0) {
                    work->unk_04 -= 4;
                }
            }
            break;
        case 2:
            if (D_8010E1AC_hide_and_sneak == 0) {
                HuAudFXPlay(0x327);
                D_8010E1AC_hide_and_sneak = 1;
            }
            if (work->unk_04 >= -0x3F) {
                if (omPauseChk() + D_800D6A90_main == 0) {
                    work->unk_04 -= 4;
                }
            } else {
                work->unk_04 = -0x40;
            }
            break;
        case 3:
            if (D_8010E1AC_hide_and_sneak != 0) {
                HuAudFXPlay(0x327);
                D_8010E1AC_hide_and_sneak = 0;
            }
            if (D_8010E182_hide_and_sneak[index] != 0) {
                if (work->unk_04 < 0) {
                    if (omPauseChk() + D_800D6A90_main == 0) {
                        work->unk_04 += 4;
                    }
                } else {
                    work->unk_04 = 0;
                }
            }
            break;
    }
    switch (D_8010C780_hide_and_sneak) {
        case 0:
        case 1:
        case 4:
        case 5:
        case 6:
        case 7:
            func_8010A6BC_hide_and_sneak(object);
            break;
    }
}

void func_8010AAC8_hide_and_sneak(omObjData *object) {
    s8 index = object->work[0];
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[5 + index];

    object->model[0] = func_8000B108_main(D_8010C474_hide_and_sneak[index] | 0x270000, 0x1689);
    object->trans.z = -10.0f;
    if (index == 1) {
        object->trans.x = -10.0f;
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    func_8001C954_main(object->model[0]);
    work->unk_04 = -0x40;
    func_8010A6BC_hide_and_sneak(object);
    D_8010E182_hide_and_sneak[index] = 1;
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->func = func_8010A88C_hide_and_sneak;
}

void func_8010ABC8_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[5 + i];
        omObjData *object = omAddObj(0x320, 2, 1, -1, func_8010AAC8_hide_and_sneak);

        object->work[0] = i;
        work->obj = object;
        omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
}

void func_8010AC78_hide_and_sneak(void) {
    HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[13];

    if (work->unk_04 < 0xFF) {
        work->unk_04 += 0x1A;
    } else {
        work->unk_04 = 0xFF;
    }
}

void func_8010ACB8_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[13].unk_04 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010ACC4_hide_and_sneak);

void func_8010AF98_hide_and_sneak(omObjData *object) {
}

void func_8010AFA0_hide_and_sneak(omObjData *object) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010C760_hide_and_sneak[i].sprite = func_8000B838_main(D_8010C49C_hide_and_sneak[i] | 0x270000);
        D_8010C760_hide_and_sneak[i].x = D_8010C4A4_hide_and_sneak[i].x;
        D_8010C760_hide_and_sneak[i].y = D_8010C4A4_hide_and_sneak[i].y;
        D_8010C760_hide_and_sneak[i].unk_06 = 0;
        D_8010E198_hide_and_sneak[i] = func_80055194_main(D_8010C760_hide_and_sneak[i].sprite);
    }
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_8010ACC4_hide_and_sneak, 2), HU3D_CAM0);
    object->func = func_8010AF98_hide_and_sneak;
}

void func_8010B0D0_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[13].obj = omAddObj(0x3E8, 2, 1, -1, func_8010AFA0_hide_and_sneak);
    omSetStatBit(D_8010C7A0_hide_and_sneak[13].obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_8010B118_hide_and_sneak(void) {
    HideAndSneakWork *works;
    s8 candidates[4];
    s8 i;
    s8 j;
    s8 count;
    s8 emptyCount;
    s8 choice;

    for (i = 0, count = 0, emptyCount = 0; i < 4; i++) {
        if (D_8010E182_hide_and_sneak[i] != 0) {
            candidates[count] = i;
            count++;
        } else {
            D_8010E175_hide_and_sneak[3 - emptyCount] = i;
            emptyCount++;
        }
    }
    for (i = 0; i < count; i++) {
        choice = func_801064F4_hide_and_sneak(count - i);
        D_8010E175_hide_and_sneak[i] = candidates[choice];
        candidates[choice] = -1;
        for (j = 1; j < count - i; j++) {
            if (candidates[j - 1] == -1) {
                candidates[j - 1] = candidates[j];
                candidates[j] = -1;
            }
        }
    }
    for (i = 0, works = &D_8010C7A0_hide_and_sneak[9]; i < 4; i++) {
        works[D_8010E175_hide_and_sneak[i]].obj->trans.x = D_8010C370_hide_and_sneak[D_8010C782_hide_and_sneak][i];
    }
}

void func_8010B33C_hide_and_sneak(omObjData *object) {
    if (D_8010E180_hide_and_sneak >= 3) {
        if (object->trans.y > -160.0f) {
            object->trans.y -= 4.0f;
        }
    } else {
        switch (D_8010C780_hide_and_sneak) {
            case 1:
                if (object->trans.y > -160.0f) {
                    object->trans.y -= 4.0f;
                }
                break;
            case 2:
                if (object->trans.y < 0.0f) {
                    object->trans.y += 4.0f;
                }
                break;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C670_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C680_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C694_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6A4_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6B8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6C8_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6DC_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C6EC_hide_and_sneak);

void func_8010B410_hide_and_sneak(omObjData *object) {
    s32 index = (s8)object->work[0];
    void *data;

    object->model[0] = func_8000B108_main(0x27000D, 0x2A9);
    data = DataRead(D_8010C4B4_hide_and_sneak[index] | 0x270000);
    Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "s206_004_DEF");
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C514_main(object->model[0]);
    DataClose(data);
    object->trans.x = index * 130 - 195;
    object->trans.y = -160.0f;
    object->trans.z = 100.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DMotionSpeedSet(object->model[0], 0.0f);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    object->func = func_8010B33C_hide_and_sneak;
}

void func_8010B55C_hide_and_sneak(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        HideAndSneakWork *work = &D_8010C7A0_hide_and_sneak[9 + i];
        omObjData *object = omAddObj(0x384, 1, 1, -1, func_8010B410_hide_and_sneak);

        object->work[0] = i;
        work->obj = object;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B600_hide_and_sneak);

void func_8010BBBC_hide_and_sneak(void) {
    u32 i;

    if (D_8010C4BC_hide_and_sneak == 0) {
        D_8010C4BC_hide_and_sneak = 1;
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 2695.0789f;
            CRotM[i].x = 340.1531f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = -0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = 385.0f;
            CenterM[i].z = -100.0f;
        }
    }
}

void func_8010BC8C_hide_and_sneak(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_8010BCB0_hide_and_sneak(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010BC8C_hide_and_sneak;
    }
}

void func_8010BCE8_hide_and_sneak(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_8010BCB0_hide_and_sneak;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BD40_hide_and_sneak);

void func_8010BFE8_hide_and_sneak(omObjData *object) {
    D_8010E180_hide_and_sneak = 0;
    D_8010E170_hide_and_sneak = 0;
    D_8010E17A_hide_and_sneak = 0;
    D_8010E174_hide_and_sneak = 0;
    D_8010E1B3_hide_and_sneak = 3;
    D_8010E1AD_hide_and_sneak = 0;
    D_8010E1B2_hide_and_sneak = 0;
    D_8010C782_hide_and_sneak = 4;
    D_8010E1AC_hide_and_sneak = 0;
    func_8010BBBC_hide_and_sneak();
    func_80106960_hide_and_sneak();
    func_801078E4_hide_and_sneak();
    func_8010A48C_hide_and_sneak();
    func_8010ABC8_hide_and_sneak();
    func_8010B55C_hide_and_sneak();
    func_8010B0D0_hide_and_sneak();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = func_8010BD40_hide_and_sneak;
}

void func_8010C0A4_hide_and_sneak(void) {
}

void func_8010C0AC_hide_and_sneak(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 2;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, D_8010C4C0_hide_and_sneak[i].scissorX, D_8010C4C0_hide_and_sneak[i].scissorY, D_8010C4C0_hide_and_sneak[i].scissorWidth, D_8010C4C0_hide_and_sneak[i].scissorHeight);
        ViewportSet(i, D_8010C4C0_hide_and_sneak[i].viewportScale.x, D_8010C4C0_hide_and_sneak[i].viewportScale.y, D_8010C4C0_hide_and_sneak[i].viewportScale.z, D_8010C4C0_hide_and_sneak[i].viewportTranslate.x,
                    D_8010C4C0_hide_and_sneak[i].viewportTranslate.y, D_8010C4C0_hide_and_sneak[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010C4C0_hide_and_sneak[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010C220_hide_and_sneak(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010C0AC_hide_and_sneak();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 144, 144, 144);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    Hu3DGLightColorSet(2, 255, 255, 255);
    Hu3DGLightDirSet(2, 0.0f, 0.0f, 100.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010C754_hide_and_sneak, 0);
    func_80045010_main(D_8010C754_hide_and_sneak, 1);
    omAddObj(1500, 0, 0, -1, func_8010BFE8_hide_and_sneak);
    omAddObj(1500, 0, 0, -1, func_8010BCE8_hide_and_sneak);
    func_80105A74_hide_and_sneak();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C754_hide_and_sneak);
