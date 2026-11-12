#include "common.h"

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
    /* 0x00 */ u8 count;
    /* 0x01 */ s8 slots[3];
} HideAndSneakSpot; // sizeof 0x04

extern HideAndSneakUnk788 D_8010C788_hide_and_sneak[4];
// Work slots: [0] obj 0x1F4, [1] solo player, [2..4] team players (by work[1]), [5..8] and [9..12] per-player objects,
// [13] screen fade (unk_04 is its alpha)
extern HideAndSneakWork D_8010C7A0_hide_and_sneak[50];
extern const char *D_8010C47C_hide_and_sneak[4];
extern const char *D_8010C48C_hide_and_sneak[4];
extern s32 D_8010C4BC_hide_and_sneak;
extern s8 D_8010C780_hide_and_sneak;
extern s8 D_8010E180_hide_and_sneak;
extern s8 D_8010E182_hide_and_sneak[4];
extern u8 D_8010E186_hide_and_sneak;
extern HideAndSneakSpot D_8010E188_hide_and_sneak[4];
extern u8 D_8010E1A8_hide_and_sneak;

void func_80106738_hide_and_sneak(omObjData *);
void func_8010C220_hide_and_sneak(void);
void func_80107638_hide_and_sneak(omObjData *);
void func_8010AFA0_hide_and_sneak(omObjData *);
void func_8010AAC8_hide_and_sneak(omObjData *);
void func_8010B410_hide_and_sneak(omObjData *);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80105D94_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010661C_hide_and_sneak);

void func_80106730_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106738_hide_and_sneak);

void func_80106960_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[0].obj = omAddObj(0x1F4, 4, 2, -1, func_80106738_hide_and_sneak);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010699C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106ABC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80106D10_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107638_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_801079E8_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107BD8_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107D98_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80107EF0_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108130_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108278_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010841C_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80108990_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109688_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109870_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109BF4_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_80109D88_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A1CC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A48C_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010A88C_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AAC8_hide_and_sneak);

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

void func_8010AF98_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010AFA0_hide_and_sneak);

void func_8010B0D0_hide_and_sneak(void) {
    D_8010C7A0_hide_and_sneak[13].obj = omAddObj(0x3E8, 2, 1, -1, func_8010AFA0_hide_and_sneak);
    omSetStatBit(D_8010C7A0_hide_and_sneak[13].obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B118_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010B410_hide_and_sneak);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010BFE8_hide_and_sneak);

void func_8010C0A4_hide_and_sneak(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C0AC_hide_and_sneak);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", func_8010C220_hide_and_sneak);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_06_hide_and_sneak/137C00", D_8010C754_hide_and_sneak);
