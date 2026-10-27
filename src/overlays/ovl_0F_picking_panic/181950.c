#include "common.h"
#include "overlays/minigame.h"
#include "game/pause.h"

typedef struct PickingPanicPlayer {
    /* 0x00 */ s8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ char unk5;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
} PickingPanicPlayer; // sizeof 0x10

extern D_80111B50_vine_with_me_Struct D_8010E5B0_picking_panic;
extern const s16 D_8010E720_picking_panic[];
extern PickingPanicPlayer D_8010EEA0_picking_panic[4];
extern PickingPanicPlayer *D_8010EEE0_picking_panic[4];
extern s8 D_8010EEF0_picking_panic[2];
extern omObjData *D_8010EEFC_picking_panic;
extern omObjData *D_8010EF00_picking_panic[4];
extern s16 D_8010EF10_picking_panic[2];
extern s8 D_8010EF14_picking_panic;
extern u8 D_8010EF15_picking_panic[2];
extern s16 *D_8010EF18_picking_panic[2][4][3];
extern s32 D_8010EF7C_picking_panic;
extern s16 D_8010EF80_picking_panic;
extern f32 D_8010EF84_picking_panic[2];
extern f32 D_8010EF94_picking_panic;
extern s8 D_8010EF98_picking_panic[2];
extern u8 D_8010EFA4_picking_panic;
extern u8 D_8010EFA5_picking_panic;
extern s32 D_8010EFA8_picking_panic;
extern s8 D_8010EFBC_picking_panic[2];
extern u16 D_8010EFBE_picking_panic;
extern u8 D_8010EFC0_picking_panic[4];
extern u16 D_8010EFD0_picking_panic[10];
extern s16 D_8010EFF8_picking_panic[10];

void func_8000B710_main(s32 arg0);
void func_80105D3C_picking_panic(omObjData *object);
void func_80106020_picking_panic(omObjData *object);
void func_8010664C_picking_panic(omObjData *object);
void func_8010B160_picking_panic(omObjData *object);
void func_8010B194_picking_panic(omObjData *object);
void func_8010B1C0_picking_panic(omObjData *object);
void func_8010B1F4_picking_panic(omObjData *object);
void func_80106E84_picking_panic(omObjData *object);
void func_80109C00_picking_panic(Gfx **, s32, s32);
void func_8010B220_picking_panic(omObjData *object, s8 arg1);
void func_8010B8D0_picking_panic(omObjData *object);
void func_8010B8EC_picking_panic(omObjData *object);
void func_8010B908_picking_panic(omObjData *object, s32 arg1);

void func_801059A0_picking_panic(void) {
    omObjData *object;

    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCamSetPerspective(0, 22.619865f, 4000.0f, 10000.0f);
    Hu3DCamSetPerspective(1, 22.619865f, 4000.0f, 10000.0f);
    HmfLightMaxSet(1);
    HmfLightDirSet(0, 0.0f, 0.0f, 90.0f);
    HmfLightColorSet(0, 0x90, 0x90, 0x90);
    HmfLightDirSet(1, 0.0f, 65.0f, 90.0f);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 4687.5f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 4687.5f;
    omAddObj(0, 0, 0, -1, func_80105D3C_picking_panic);
    D_8010EEFC_picking_panic = omAddObj(8, 38, 38, -1, func_8010664C_picking_panic);
    omSetStatBit(D_8010EEFC_picking_panic, 0xA0);
    D_8010EF00_picking_panic[0] = omAddObj(3, 8, 5, -1, func_8010B160_picking_panic);
    D_8010EF00_picking_panic[1] = omAddObj(3, 8, 5, -1, func_8010B194_picking_panic);
    D_8010EF00_picking_panic[2] = omAddObj(3, 8, 5, -1, func_8010B1C0_picking_panic);
    D_8010EF00_picking_panic[3] = omAddObj(3, 8, 5, -1, func_8010B1F4_picking_panic);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, 0xA0);
    func_80045010_main(D_8010E720_picking_panic, 1);
    WipeCreateIn(0xFF, 16);
    D_8010E5B0_picking_panic.unk01 = 1;
    D_8010E5B0_picking_panic.unk1C = 60;
    D_8010E5B0_picking_panic.unk1E = 900;
    D_8010E5B0_picking_panic.unk03 = 2;
    D_8010E5B0_picking_panic.unk02 = 1;
    D_8010E5B0_picking_panic.unk22 = 75;
    D_8010E5B0_picking_panic.unk24 = 165;
    D_8010E5B0_picking_panic.unk04 = 0;
    D_8010E5B0_picking_panic.unk05 = 0;
    D_8010E5B0_picking_panic.unk20 = -1;
    func_800E5EA0_minigame(&D_8010E5B0_picking_panic);
}

void func_80105D3C_picking_panic(omObjData *object) {
    u8 groups[4];
    u8 group;
    s32 i;

    D_8010EFBE_picking_panic = 0;
    D_8010EF80_picking_panic = 0;
    D_8010EFA8_picking_panic = 0;
    D_8010EF7C_picking_panic = 0;
    D_8010EF14_picking_panic = 5;
    D_8010EF10_picking_panic[0] = D_8010EF10_picking_panic[1] = 1;
    D_8010EF98_picking_panic[0] = D_8010EF98_picking_panic[1] = -1;
    D_8010EFBC_picking_panic[0] = D_8010EFBC_picking_panic[1] = 0;
    D_8010EEF0_picking_panic[0] = D_8010EEF0_picking_panic[1] = 0;
    D_8010EF15_picking_panic[0] = D_8010EF15_picking_panic[1] = 0;
    D_8010EFA4_picking_panic = 0xFF;
    D_8010EF94_picking_panic = D_8010EF84_picking_panic[0] = D_8010EF84_picking_panic[1] = 0.0f;

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[i] = &D_8010EEA0_picking_panic[i];
        bzero(&D_8010EEA0_picking_panic[i], sizeof(PickingPanicPlayer));
    }

    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        groups[i] = group;
        D_8010EFC0_picking_panic[groups[i]] = i;
    }

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[groups[i]]->unk0 = i;
        D_8010EEE0_picking_panic[i]->unk2 = GwPlayer[D_8010EFC0_picking_panic[i]].pad;
        D_8010EEE0_picking_panic[i]->unk3 = GwPlayer[D_8010EFC0_picking_panic[i]].chr;
        D_8010EEE0_picking_panic[i]->unk1 = i;
        D_8010EEE0_picking_panic[i]->unk4 = (GwPlayer[D_8010EFC0_picking_panic[i]].stat & 1)
                                                ? GwPlayer[D_8010EFC0_picking_panic[i]].cpu_difficulty
                                                : -1;
    }

    for (i = 0; i < 4; i++) {
        if (D_8010EEE0_picking_panic[i]->unk4 != -1) {
            if (D_8010EEE0_picking_panic[(i & 1) ? i - 1 : i + 1]->unk4 == -1) {
                D_8010EEE0_picking_panic[i]->unk4 += 4;
            }
        }
    }

    func_8001AC8C_main(0, func_80109C00_picking_panic, 2);
    object->func = func_80106020_picking_panic;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E720_picking_panic);

void func_80106020_picking_panic(omObjData *object) {
    s32 i;
    u8 j;

    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    D_8010EFA8_picking_panic++;
    D_8010EF7C_picking_panic++;
    func_800E6F40_minigame();
    switch (D_8010EF80_picking_panic) {
        case 0:
            if (D_8010EFA8_picking_panic == 2) {
                HuAudFXPlay(0x371);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_8010EF80_picking_panic = 1;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 1:
            if (D_8010EFA8_picking_panic == 33 && D_8010EFBE_picking_panic == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x38);
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010EF80_picking_panic = 2;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 2:
            if (D_8010EF14_picking_panic == 5 && func_800E6E8C_minigame() == 3) {
                if (D_8010EF15_picking_panic[0] == D_8010EF15_picking_panic[1]) {
                    D_8010EF80_picking_panic = 4;
                    D_8010EF14_picking_panic = 4;
                } else {
                    D_8010EF80_picking_panic = 3;
                    D_8010EF14_picking_panic = D_8010EF15_picking_panic[0] <= D_8010EF15_picking_panic[1];
                }
                D_8010EFA8_picking_panic = 0;
            }
            if (D_8010EF80_picking_panic != 3) {
                break;
            }
        case 3:
            if (D_8010EFA8_picking_panic == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010E5B0_picking_panic.unk06 = 1;
                D_8010E5B0_picking_panic.unk18[0] = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk0;
                D_8010E5B0_picking_panic.unk18[1] = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk0;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk0].bonusCoin = 10;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk0].bonusCoin = 10;
            }
            if (D_8010EFA8_picking_panic == 2) {
                func_800E6F34_minigame(30);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010EF80_picking_panic = 5;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 4:
            if (D_8010EFA8_picking_panic == 1) {
                D_8010E5B0_picking_panic.unk06 = 4;
                D_8010E5B0_picking_panic.unk22 = 75;
                D_8010E5B0_picking_panic.unk24 = 0x90;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010EF80_picking_panic = 6;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 5:
            if (D_8010EFA8_picking_panic == 31) {
                for (i = D_8010EF14_picking_panic * 2; i < D_8010EF14_picking_panic * 2 + 2; i++) {
                    s32 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                    func_80017954_main(D_8010EF00_picking_panic[i]->model[1], 1,
                                       motions[D_8010EEE0_picking_panic[i]->unk3],
                                       D_8010EEE0_picking_panic[i]->unk8);
                    func_8001C5B4_main(D_8010EF00_picking_panic[i]->model[1], D_8010EF00_picking_panic[i]->motion[4]);
                    func_80045ED0_main(D_8010EEE0_picking_panic[i]->unkC);
                }
            }
        case 6:
            if (func_800E6E8C_minigame() == 5) {
                D_8010EF80_picking_panic = 7;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 7:
            if (D_8010EFA8_picking_panic == 1) {
                WipeCreateOut(0, 20);
            } else if (D_8010EFA8_picking_panic >= 32) {
                D_8010EFBE_picking_panic = 1;
            }
            break;
    }

    if (_CheckFlag(0xF) && D_800D530C_main == 0 && D_8010EFA5_picking_panic == 0 && (u16)D_8010EF80_picking_panic == 2) {
        for (j = 0; j < 2; j++) {
            if (D_8010EEE0_picking_panic[j]->unk4 == -1 &&
                (D_800D5558_main[D_8010EEE0_picking_panic[j]->unk2] & 0x10)) {
                D_8010EFA5_picking_panic = 1;
            }
        }
    }

    if (D_8010EFBE_picking_panic != 0 || D_800D530C_main != 0 || D_8010EFA5_picking_panic != 0) {
        if (D_800D530C_main != 0 && D_8010EFA5_picking_panic == 0) {
            D_8010EFA5_picking_panic = 1;
        }
        if (D_8010EFA5_picking_panic != 0) {
            if (D_8010EFA5_picking_panic == 1) {
                WipeCreateOut(0, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_8010EFA5_picking_panic++;
            if (D_8010EFA5_picking_panic < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        omOvlReturnEx(1);
    }
}

#ifdef NON_MATCHING
/* The 0.0f constant in the final loop is not hoisted into $f24 as in the original, shifting one mtc1. */
void func_8010664C_picking_panic(omObjData *object) {
    s32 fileIds[10] = { 0x0030000A, 0x0030000B, 0x0030000C, 0x0030000D, 0x0030000E,
                        0x00000031, 0x002A0012, 0x0030000F, 0x00300011, 0x00300010 };
    s16 i;
    s16 j;

    for (i = 0; i < 10; i++) {
        D_8010EFF8_picking_panic[i] = func_8000B838_main(fileIds[i]);
        D_8010EFD0_picking_panic[i] = InitEspriteSlot(D_8010EFF8_picking_panic[i], 0, 0);
        func_8000BB94_main(D_8010EFD0_picking_panic[i]);
    }

    object->model[0] = func_8000B108_main(0x300000, 0x499);
    omSetTra(object, 0.0f, -525.0f, -450.0f);
    omSetSca(object, 1.75f, 1.75f, 1.75f);
    func_8001C814_main(object->model[0], 1, 1);
    func_8001C8A8_main(object->model[0], 1);
    object->model[1] = Hu3DModelLink(object->model[0]);
    Hu3DModelPosSet(object->model[1], 0.0f, -525.0f, -450.0f);
    Hu3DModelScaleSet(object->model[1], 1.75f, 1.75f, 1.75f);
    func_8001C814_main(object->model[1], 1, 1);
    func_8001C8A8_main(object->model[1], 2);

    for (i = 0; i < 2; i++) {
        object->model[4 + i] = func_8000B108_main((i == 1) ? 0x300005 : 0x300006, 0x43D);
        Hu3DModelPosSet(object->model[4 + i], (i == 0) ? 450.0f : 750.0f, (i == 0) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(object->model[4 + i], 2.75f, 2.75f, 2.75f);
        func_8001C814_main(object->model[4 + i], 2, 2);
        object->model[6 + i] = Hu3DModelLink(object->model[4 + i]);
        Hu3DModelPosSet(object->model[6 + i], (i == 1) ? -450.0f : -750.0f, (i == 1) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(object->model[6 + i], 2.75f, 2.75f, 2.75f);
        func_8001C814_main(object->model[6 + i], 2, 2);
    }

    for (i = 0; i < 2; i++) {
        object->model[2 + i] = func_8000B108_main(0x300001, 0x4B9);
        Hu3DModelPosSet(object->model[2 + i], 890.0f, -222.0f, 0.0f);
        Hu3DModelScaleSet(object->model[2 + i], 1.38125f, 1.3f, 1.3f);
        func_8001C814_main(object->model[2 + i], 1, 1);
        func_8001C8A8_main(object->model[2 + i], (i == 0) ? 1 : 2);
    }

    object->model[32] = func_8000B108_main(0x300007, 0x499);
    Hu3DModelScaleSet(object->model[32], 1.0f, 1.1f, 1.0f);
    for (i = 1; i < 6; i++) {
        object->model[32 + i] = Hu3DModelLink(object->model[32]);
        Hu3DModelScaleSet(object->model[32 + i], 1.0f, 1.1f, 1.0f);
    }

    for (i = 0; i < 2; i++) {
        object->model[10 + i] = func_8000B108_main(0x300009, 0x4BD);
        Hu3DModelPosSet(object->model[10 + i], -855.0f, 125.0f, 0.0f);
        Hu3DModelScaleSet(object->model[10 + i], 2.0f, 2.0f, 2.0f);
        func_8001C8A8_main(object->model[10 + i], (i == 0) ? 1 : 2);
    }

    object->model[8] = func_8000B108_main(0x300008, 0x4B9);
    object->model[9] = Hu3DModelLink(object->model[8]);
    object->model[12] = func_8000B108_main(0x300002, 0x4B9);
    for (i = 1; i < 20; i++) {
        object->model[12 + i] = Hu3DModelLink(object->model[12]);
    }

    {
        f32 xs[10] = { -510.0f, -555.0f, -663.0f, -692.0f, -797.0f, -823.0f, -947.0f, -1012.0f, -1121.0f, -1169.0f };
        f32 zs[10] = { 449.0f, 331.0f, 470.0f, 341.0f, 237.0f, 403.0f, 293.0f, 409.0f, 276.0f, 432.0f };

        for (i = 0; i < 10; i++) {
            for (j = 0; j < 2; j++) {
                Hu3DModelPosSet(object->model[(j == 0) ? 12 + i : 22 + i], xs[i] / 4687.5 * 5187.5,
                                zs[i] / 4687.5 * 5187.5, -500.0f);
                Hu3DModelPosSet(object->model[(j == 0) ? 12 + i : 22 + i], 0.0f, 0.0f, -500.0f);
                func_8001C814_main(object->model[(j == 0) ? 12 + i : 22 + i], 1, 1);
                func_8001C8A8_main(object->model[(j == 0) ? 12 + i : 22 + i], (j == 0) ? 1 : 2);
            }
        }
    }

    object->func = func_80106E84_picking_panic;
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E798_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7C0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E7E8_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010664C_picking_panic);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80106E84_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80107A48_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010E990_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_80109C00_picking_panic);

void func_8010B11C_picking_panic(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &HmfModelData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}

void func_8010B160_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 0);
    object->func = func_8010B8D0_picking_panic;
}

void func_8010B194_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 1);
    object->func = NULL;
}

void func_8010B1C0_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 2);
    object->func = func_8010B8EC_picking_panic;
}

void func_8010B1F4_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 3);
    object->func = NULL;
}

void func_8010B220_picking_panic(omObjData *object, s8 arg1) {
    s32 files[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 models[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 linkModels[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 anims[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    PickingPanicPlayer *player;
    u16 chr;
    u16 i;
    u16 j;
    s16 *model;

    chr = D_8010EEE0_picking_panic[arg1]->unk3;
    object->model[0] = func_8000B108_main((files[chr] << 16) | models[chr], 0x4B9);
    omSetSca(object, 1.3f, 1.3f, 1.3f);
    func_8001C2FC_main(object->model[0], 0x600, 0x400);
    func_8001C8A8_main(object->model[0], (arg1 >= 2) ? 2 : 1);
    object->model[1] = func_8000B108_main((files[chr] << 16) | linkModels[chr], 0x4AD);
    Hu3DModelScaleSet(object->model[1], 1.3f, 1.3f, 1.3f);
    func_8001C2FC_main(object->model[1], 0x600, 0x400);
    func_8001C8A8_main(object->model[1], (arg1 >= 2) ? 2 : 1);
    D_8010EEE0_picking_panic[arg1]->unk6 =
        func_80017790_main(object->model[1], 1, motions[chr], (files[chr] << 16) | anims[0][chr]);
    D_8010EEE0_picking_panic[arg1]->unk8 = func_80017AD8_main((files[chr] << 16) | anims[1][chr]);
    func_8001C514_main(object->model[1]);
    player = D_8010EEE0_picking_panic[arg1];
    player->unkC = (rand8() & 1) ? 0x2F : 0x30;
    func_8000B460_main(object, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(object, 1, func_80017BB8_main(chr, 0x49));
    func_8000B460_main(object, 2, func_80017BB8_main(chr, 0x4A));
    func_8000B460_main(object, 3, func_80017BB8_main(chr, 0x1F));
    func_8000B460_main(object, 4, func_80017BB8_main(chr, D_8010EEE0_picking_panic[arg1]->unkC));
    D_8010EEE0_picking_panic[arg1]->unkC |= files[chr] << 16;
    func_8001C5B4_main(object->model[0], object->motion[1]);
    func_8001C6A8_main(object->model[0], 12.0f);
    func_8001C814_main(object->model[0], 1, 1);
    func_8001C5B4_main(object->model[1], object->motion[1]);
    func_8001C6A8_main(object->model[1], 12.0f);
    func_8001C814_main(object->model[1], 1, 1);

    if (arg1 % 2 == 1) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                model = D_8010EF18_picking_panic[arg1 / 2][j][i] =
                    &D_8010EF00_picking_panic[(arg1 & 2) + (j % 2)]->model[i + ((j / 2 == 0) ? 2 : 5)];
                if (arg1 / 2 == 0 && j == 0) {
                    s32 fileIds[3] = { 2, 3, 4 };

                    *model = func_8000B108_main(fileIds[i] | 0x300000, 0x8BD);
                } else {
                    *model = Hu3DModelLink(D_8010EF00_picking_panic[0]->model[2 + i]);
                }
                func_8001C8A8_main(*model, (arg1 >= 2) ? 2 : 1);
                func_8001C2FC_main(*model, 0x20000000, 0x20000000);
                func_8001C258_main(*model, 4, 4);
                Hu3DModelScaleSet(*model, 1.3f, 1.3f, 1.3f);
            }
        }
    }
    D_8010EFBE_picking_panic = 0;
}

void func_8010B8D0_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 0);
}

void func_8010B8EC_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 1);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EA8C_picking_panic);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", func_8010B908_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAB8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAE8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAF8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EAFC_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB04_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB08_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB10_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB18_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB20_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB28_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB30_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB38_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB40_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB48_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB50_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB58_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB60_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB68_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB70_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB78_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB80_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB88_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB90_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EB98_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBA8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBB8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBC8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBD8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBE8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF0_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EBF8_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC00_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC08_picking_panic);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0F_picking_panic/181950", D_8010EC10_picking_panic);
