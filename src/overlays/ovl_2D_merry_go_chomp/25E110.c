#include "common.h"
#include "math.h"

// Per-chomp state at D_8010C420_merry_go_chomp, indexed by omObjData::work[0]
typedef struct D_8010C420_merry_go_chomp_Entry {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ s8 unk_18[4];
    /* 0x1C */ s8 unk_1C[4];
    /* 0x20 */ s8 unk_20[4];
} D_8010C420_merry_go_chomp_Entry; // Size 0x24

// One entry of the 50 entry object table at D_8010C500_merry_go_chomp. Layout
// derived from the table clear in func_80105A74_merry_go_chomp, which walks 50
// entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} MerryGoChompEntry; // sizeof 0x84

extern D_8010C420_merry_go_chomp_Entry D_8010C420_merry_go_chomp[];
extern MerryGoChompEntry D_8010C500_merry_go_chomp[50];
extern MerryGoChompEntry D_8010C794_merry_go_chomp[];

extern HuSprite_Unk84_Struct *D_8010C414_merry_go_chomp;
// Fields of the first entry of D_8010C500_merry_go_chomp are accessed through
// these separate symbols.
extern s16 D_8010C540_merry_go_chomp;
extern s16 D_8010C542_merry_go_chomp;
extern f32 D_8010C544_merry_go_chomp;
extern f32 D_8010C548_merry_go_chomp;
// Fields of D_8010C500_merry_go_chomp[15].
extern f32 D_8010CD04_merry_go_chomp;
extern f32 D_8010CD08_merry_go_chomp;
extern s8 D_8010C4B0_merry_go_chomp;
extern s16 D_8010C4B2_merry_go_chomp;
extern s8 D_8010C4BE_merry_go_chomp[5];
extern s8 D_8010C4CE_merry_go_chomp;
extern f32 D_8010DED4_merry_go_chomp;
extern u8 D_8010DEDC_merry_go_chomp;
extern omObjData *D_8010CA28_merry_go_chomp;
extern omObjData *D_8010CCBC_merry_go_chomp;
extern omObjData *D_8010D1E4_merry_go_chomp;
extern omObjData *D_8010D478_merry_go_chomp;

void func_80106384_merry_go_chomp(omObjData *);
void func_801064E0_merry_go_chomp(omObjData *obj);
void func_8010637C_merry_go_chomp(omObjData *obj);
void func_801064E8_merry_go_chomp(omObjData *);
void func_80106668_merry_go_chomp(omObjData *obj);
void func_80106920_merry_go_chomp(omObjData *);
void func_8010A9D0_merry_go_chomp(omObjData *);
void func_8010AE2C_merry_go_chomp(omObjData *);
void func_8010C030_merry_go_chomp(void);

void func_801059A0_merry_go_chomp(void) {
    func_8010C030_merry_go_chomp();
}

f32 func_801059BC_merry_go_chomp(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_merry_go_chomp(u32 arg0) {
    return (rand8() * arg0) >> 8;
}

void func_80105A74_merry_go_chomp(void) {
    MerryGoChompEntry *entry;
    u32 i;

    for (i = 0, entry = D_8010C500_merry_go_chomp; i < 50; i++, entry++) {
        entry->obj = NULL;
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
        entry->unk_40[0] = -1;
        entry->unk_40[1] = -1;
        entry->unk_44.x = entry->unk_44.y = entry->unk_44.z = 0.0f;
        entry->unk_50.x = entry->unk_50.y = entry->unk_50.z = 0.0f;
        entry->unk_5C.x = entry->unk_5C.y = entry->unk_5C.z = 0.0f;
        entry->unk_68[0] = 0.0f;
        entry->unk_68[1] = 0.0f;
        entry->unk_68[2] = 0.0f;
        entry->unk_68[3] = 0.0f;
        entry->unk_78.x = entry->unk_78.y = entry->unk_78.z = 0.0f;
    }
}

void func_80105B3C_merry_go_chomp(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105BB4_merry_go_chomp(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = (x0 - x1) * 5.0f;
    f32 dz = (z0 - z1) * 5.0f;
    f32 zoom;
    f32 rot;

    if (dx < 0.0f) {
        dx = 0.0f - dx;
    }
    if (dz < 0.0f) {
        dz = 0.0f - dz;
    }
    zoom = sqrtf(dx * dx + dz * dz);
    rot = func_801059BC_merry_go_chomp(atan2df(dx, dz), 0.0f);
    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

s32 func_80105CE4_merry_go_chomp(s32 arg0) {
    return rand8() % arg0;
}

void func_80105D38_merry_go_chomp(omObjData *obj, u16 motion, s16 shift) {
    func_8001C5B4_main(obj->model[0], obj->motion[motion]);
    func_8001C814_main(obj->model[0], shift, shift);
}

void func_80105DA0_merry_go_chomp(omObjData *arg0, u16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[arg1]].motId, arg2, arg3, arg4);
}

void func_80105E0C_merry_go_chomp(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 *angle, f32 speed) {
    f32 dx = x0 - x1;
    f32 dz = z0 - z1;
    f32 dist = sqrtf(dx * dx + dz * dz);
    f32 steps;

    if (dist == 0.0f) {
        *velX = 0.0f;
        *velZ = 0.0f;
        return;
    }
    if (dist <= speed) {
        *velX = dx;
        *velZ = dz;
    } else {
        steps = dist / speed;
        if (dx != 0.0f) {
            *velX = dx / steps;
        } else {
            *velX = 0.0f;
        }
        if (dz != 0.0f) {
            *velZ = dz / steps;
        } else {
            *velZ = 0.0f;
        }
    }
    *angle = atan2df(dx, dz);
}

s8 func_80105F40_merry_go_chomp(omObjData *obj, f32 target) {
    f32 rotY = obj->rot.y;
    f32 diff = target - rotY;

    if (diff < 0.0f) {
        diff = 0.0f - diff;
    }
    if (diff < 15.0f) {
        obj->rot.y = target;
    } else if (rotY < target) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -15.0f);
        } else {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, 15.0f);
        }
        return 1;
    } else if (target < rotY) {
        if (diff > 180.0f) {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, 15.0f);
        } else {
            obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -15.0f);
        }
        return 1;
    }
    return 0;
}

void func_80106054_merry_go_chomp(Gfx **gfxP, s32 arg1, s32 arg2) {
    Gfx *gfx = *gfxP;
    s32 x;
    s32 y;
    s32 i;

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gfx++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gfx++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    gDPSetRenderMode(gfx++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetTextureLUT(gfx++, G_TT_RGBA16);
    gDPLoadTLUT_pal256(gfx++, D_8010C414_merry_go_chomp->unk0C);
    x = 0;
    for (i = 0, y = 180; i < 60; i += 4) {
        gDPLoadTextureTile(gfx++, D_8010C414_merry_go_chomp->unk08, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0, 0, i, 320, i + 4,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 320 << 2, 4 << 2);
        gSPTextureRectangle(gfx++, x << 2, (y + i) << 2, (x + 320) << 2, (y + i + 4) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);
    }
    *gfxP = gfx;
}

void func_8010637C_merry_go_chomp(omObjData *obj) {
}

void func_80106384_merry_go_chomp(omObjData *obj) {
    D_8010C544_merry_go_chomp = 160.0f;
    D_8010C548_merry_go_chomp = 107.0f;
    D_8010C540_merry_go_chomp = func_8000B838_main(0x4E0000);
    D_8010C542_merry_go_chomp = espEntry(D_8010C540_merry_go_chomp, 0, 0);
    espAttrSet(D_8010C542_merry_go_chomp, 0x5000);
    espPosSet(D_8010C542_merry_go_chomp, D_8010C544_merry_go_chomp,
              D_8010C548_merry_go_chomp);
    D_8010C414_merry_go_chomp = func_80055194_main(func_8000B838_main(0x4E0001));
    Hu3DModelCameraSet(Hu3DHookFuncCreate(0, func_80106054_merry_go_chomp, 2), 1);
    obj->model[0] = -1;
    obj->func = func_8010637C_merry_go_chomp;
}

void func_801064A0_merry_go_chomp(void) {
    omObjData *obj = omAddObj(0x1F4, 1, 1, -1, func_80106384_merry_go_chomp);
    obj->work[0] = 0;
    D_8010C500_merry_go_chomp[0].obj = obj;
}

void func_801064E0_merry_go_chomp(omObjData *obj) {
}

void func_801064E8_merry_go_chomp(omObjData *obj) {
    f32 zero;

    obj->model[0] = func_8000B108_main(0x4E0004, 0x2B9);
    obj->model[1] = func_8000B108_main(0x4E0005, 0x2B9);
    obj->model[2] = func_8000B108_main(0x4E0002, 0x2B9);
    obj->trans.x = -500.0f;
    obj->trans.y = zero = 0.0f;
    D_8010CD04_merry_go_chomp = zero;
    obj->trans.z = -400.0f;
    D_8010CD08_merry_go_chomp = -225.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, D_8010CD04_merry_go_chomp, D_8010CD08_merry_go_chomp);
    Hu3DModelPosSet(obj->model[2], zero, zero, zero);
    Hu3DModelCameraSet(obj->model[0], 2);
    Hu3DModelCameraSet(obj->model[1], 2);
    Hu3DModelCameraSet(obj->model[2], 2);
    obj->func = func_801064E0_merry_go_chomp;
}

void func_8010662C_merry_go_chomp(void) {
    D_8010CCBC_merry_go_chomp = omAddObj(0x2BC, 4, 1, -1, func_801064E8_merry_go_chomp);
}

void func_80106668_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[25];

    obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -D_8010DED4_merry_go_chomp);
    switch (D_8010C4B0_merry_go_chomp) {
        case 0:
            D_8010DED4_merry_go_chomp = 3.0f;
            entry->unk_06 = 0;
            entry->unk_08 = 0;
            break;
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            if (D_8010C4B2_merry_go_chomp < 50) {
                if (obj->trans.y > 0.0f) {
                    obj->trans.y -= 10.0f;
                } else {
                    obj->trans.y = 0.0f;
                }
            }
            break;
        case 9:
            if (D_8010C4B2_merry_go_chomp == 50) {
                if (entry->unk_06 == 0) {
                    if (entry->unk_08 == 0) {
                        HuAudFXPlay(0x473);
                        entry->unk_08++;
                    }
                    if (obj->trans.y > -650.0f) {
                        obj->trans.y -= 15.0f;
                    } else {
                        func_8001C258_main(obj->model[entry->unk_04], 4, 4);
                        entry->unk_04++;
                        func_8001C258_main(obj->model[entry->unk_04], 4, 0);
                        entry->unk_06 = 1;
                        if (D_8010C4CE_merry_go_chomp == 0) {
                            obj->rot.y = 0.0f;
                        }
                        if (D_8010C4CE_merry_go_chomp == 1) {
                            obj->rot.y = 30.0f;
                        }
                    }
                } else {
                    if (entry->unk_08 == 1) {
                        HuAudFXPlay(0x473);
                        entry->unk_08++;
                    }
                    if (obj->trans.y < 500.0f) {
                        obj->trans.y += 15.0f;
                    } else {
                        obj->trans.y = 500.0f;
                        D_8010DEDC_merry_go_chomp |= 8;
                        if (entry->unk_08 == 2) {
                            HuAudFXPlay(0x478);
                            entry->unk_08++;
                        }
                    }
                }
            }
            break;
    }
    Hu3DModelPosSet(obj->model[entry->unk_04], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[entry->unk_04], obj->rot.x, obj->rot.y, obj->rot.z);
}

void func_80106920_merry_go_chomp(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4E0006, 0x2B9);
    obj->model[1] = func_8000B108_main(0x4E0007, 0x2B9);
    obj->model[2] = func_8000B108_main(0x4E0008, 0x2B9);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->model[3] = func_8000B108_main(0x4E0009, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    D_8010C500_merry_go_chomp[25].unk_04 = 1;
    obj->trans.x = 0.0f;
    obj->trans.y = 500.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelPosSet(obj->model[3], obj->trans.x, obj->trans.y, obj->trans.z);
    D_8010C4BE_merry_go_chomp[0] = 1;
    D_8010C4BE_merry_go_chomp[1] = 1;
    D_8010C4BE_merry_go_chomp[2] = 1;
    D_8010C4BE_merry_go_chomp[3] = 1;
    D_8010C4BE_merry_go_chomp[4] = 1;
    Hu3DModelCameraSet(obj->model[0], 1);
    Hu3DModelCameraSet(obj->model[1], 1);
    Hu3DModelCameraSet(obj->model[2], 1);
    Hu3DModelCameraSet(obj->model[3], 1);
    obj->func = func_80106668_merry_go_chomp;
}

void func_80106AB8_merry_go_chomp(void) {
    D_8010D1E4_merry_go_chomp = omAddObj(0x258, 5, 1, -1, func_80106920_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106AF4_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106B9C_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80106CC4_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107664_merry_go_chomp);

void func_801077D0_merry_go_chomp(omObjData *obj) {
    D_8010C420_merry_go_chomp_Entry *entry = &D_8010C420_merry_go_chomp[obj->work[0]];

    obj->trans.x += entry->unk_00.x;
    obj->trans.z += entry->unk_00.y;
    obj->rot.y = entry->unk_00.z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107818_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107980_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80107E34_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801084C8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80108A88_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801090B0_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109420_merry_go_chomp);

void func_80109604_merry_go_chomp(void) {
    MerryGoChompEntry *entry;
    s8 i;

    for (i = 0; i < 4; i++) {
        entry = &D_8010C794_merry_go_chomp[i];
        GwPlayer[entry->obj->work[0]].bonusCoin = entry->unk_0E;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109670_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109A04_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010A9D0_merry_go_chomp);

void func_8010ADE8_merry_go_chomp(void) {
    D_8010CA28_merry_go_chomp = omAddObj(0x384, 0xF, 4, -1, func_8010A9D0_merry_go_chomp);
}

void func_8010AE24_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AE2C_merry_go_chomp);

void func_8010AECC_merry_go_chomp(void) {
    D_8010D478_merry_go_chomp = omAddObj(0x3E8, 1, 1, -1, func_8010AE2C_merry_go_chomp);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010AF08_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BAB8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BB7C_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BBA0_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BBD8_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BC30_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BDE8_merry_go_chomp);

void func_8010BEB4_merry_go_chomp(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010BEBC_merry_go_chomp);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010C030_merry_go_chomp);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", D_8010C400_merry_go_chomp);
