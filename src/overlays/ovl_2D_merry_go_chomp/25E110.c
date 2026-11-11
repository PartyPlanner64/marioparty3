#include "common.h"
#include "math.h"

// Per-chomp state at D_8010C420_merry_go_chomp, indexed by omObjData::work[0]
typedef struct D_8010C420_merry_go_chomp_Entry {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ s8 unk_1C;
    /* 0x1D */ s8 unk_1D;
    /* 0x1E */ s8 unk_1E;
    /* 0x1F */ s8 unk_1F;
    /* 0x20 */ s8 unk_20;
    /* 0x21 */ char unk_21[3];
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

extern s32 D_800A178C_main[][6];
extern s32 D_8010C140_merry_go_chomp[];
extern s8 D_8010C160_merry_go_chomp[];
extern f32 D_8010C174_merry_go_chomp[];
extern f32 D_8010C1B8_merry_go_chomp[];
extern f32 D_8010C1C8_merry_go_chomp[];
extern f32 D_8010C1D8_merry_go_chomp[][5];
extern Vec2f D_8010C214_merry_go_chomp;
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
extern Vec2f D_8010C4D0_merry_go_chomp[6];
extern s8 D_8010C4BD_merry_go_chomp;
extern s8 D_8010C4BE_merry_go_chomp[5];
extern omObjData *D_8010C4C8_merry_go_chomp;
extern s8 D_8010C4CE_merry_go_chomp;
extern u8 D_8010DECC_merry_go_chomp[];
extern f32 D_8010DED4_merry_go_chomp;
extern u8 D_8010DEDC_merry_go_chomp;
extern s8 D_8010DEDD_merry_go_chomp;
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
void func_80109A04_merry_go_chomp(omObjData *obj);
void func_8010A9D0_merry_go_chomp(omObjData *);
void func_8010AE24_merry_go_chomp(omObjData *obj);
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

void func_80106AF4_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[obj->work[0] + 5];

    if (obj->work[2] == 0) {
        if (entry->unk_14 != 0) {
            HuAudFXStop(entry->unk_14);
        }
        entry->unk_14 = PlayerFXPlay(0x28, obj->work[0]);
    }
    obj->work[2] = (obj->work[2] + 1) % 11;
}

void func_80106B9C_merry_go_chomp(omObjData *obj, s8 motion) {
    s8 chr = GwPlayer[obj->work[0]].chr;
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[obj->work[0] + 5];
    s16 shift;

    if (entry->unk_06 != motion) {
        switch (motion) {
            case 6:
            case 7:
            case 8:
                shift = 0;
                break;
            case 9:
            case 10:
                shift = 0;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            default:
                shift = 2;
                break;
        }
        Hu3DMotionSpeedSet(obj->model[0], 1.0f);
        func_80105DA0_merry_go_chomp(obj, motion, 0, 5, shift);
        entry->unk_06 = motion;
        if (motion == 9) {
            func_80045ED0_main((D_8010C140_merry_go_chomp[chr] << 16) | 0x30);
        }
    }
}

s8 func_80106CC4_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[obj->work[0] + 5];
    omObjData *chomp = D_8010C500_merry_go_chomp[25].obj;
    s8 zone = 99;
    f32 angle = func_801059BC_merry_go_chomp(chomp->rot.y, -120.0f);

    if (!(GwPlayer[obj->work[0]].stat & 1)) {
        switch (D_8010C4CE_merry_go_chomp) {
            case 0:
                if (angle >= 324.0f || angle < 36.0f) {
                    zone = 0;
                }
                if (angle >= 36.0f && angle < 108.0f) {
                    zone = 1;
                }
                if (angle >= 108.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 180.0f && angle < 252.0f) {
                    zone = 3;
                }
                if (angle >= 252.0f && angle < 324.0f) {
                    zone = 4;
                }
                break;
            case 1:
                if (angle >= 315.0f || angle < 45.0f) {
                    zone = 0;
                }
                if (angle >= 45.0f && angle < 135.0f) {
                    zone = 1;
                }
                if (angle >= 135.0f && angle < 225.0f) {
                    zone = 2;
                }
                if (angle >= 225.0f && angle < 315.0f) {
                    zone = 3;
                }
                break;
            case 2:
                if (angle >= 300.0f || angle < 60.0f) {
                    zone = 0;
                }
                if (angle >= 60.0f && angle < 180.0f) {
                    zone = 1;
                }
                if (angle >= 180.0f && angle < 300.0f) {
                    zone = 2;
                }
                break;
        }
    } else {
        switch (D_8010C4CE_merry_go_chomp) {
            case 0:
                if (angle >= 324.0f || angle < 36.0f) {
                    zone = 0;
                }
                if (angle >= 36.0f && angle < 108.0f) {
                    zone = 1;
                }
                if (angle >= 108.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 180.0f && angle < 252.0f) {
                    zone = 3;
                }
                if (angle >= 252.0f && angle < 324.0f) {
                    zone = 4;
                }
                break;
            case 1:
                if (angle >= 315.0f) {
                    zone = 0;
                }
                if (angle >= 45.0f && angle < 90.0f) {
                    zone = 1;
                }
                if (angle >= 135.0f && angle < 180.0f) {
                    zone = 2;
                }
                if (angle >= 225.0f && angle < 270.0f) {
                    zone = 3;
                }
                break;
            case 2:
                if (angle >= 300.0f) {
                    zone = 0;
                }
                if (angle >= 60.0f && angle < 120.0f) {
                    zone = 1;
                }
                if (angle >= 180.0f && angle < 240.0f) {
                    zone = 2;
                }
                break;
        }
        if (zone == 99) {
            return 0;
        }
    }
    if (!(GwPlayer[obj->work[0]].stat & 1) || D_8010C4B2_merry_go_chomp <= 0) {
        if (D_8010C4BE_merry_go_chomp[zone] != 0) {
            entry->unk_0A = zone;
            D_8010DECC_merry_go_chomp[entry->unk_0A] = obj->work[0];
            D_8010C4BE_merry_go_chomp[zone] = 0;
            return 1;
        }
    } else if (entry->unk_0C == zone) {
        entry->unk_0A = zone;
        D_8010DECC_merry_go_chomp[entry->unk_0A] = obj->work[0];
        D_8010C4BE_merry_go_chomp[zone] = 0;
        return 1;
    }
    return 0;
}

void func_80107664_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[obj->work[0] + 5];
    omObjData *chomp = D_8010C500_merry_go_chomp[25].obj;
    D_8010C420_merry_go_chomp_Entry *move = &D_8010C420_merry_go_chomp[obj->work[0]];
    f32 angle;

    angle = func_801059BC_merry_go_chomp(chomp->rot.y,
                                         -D_8010C1D8_merry_go_chomp[D_8010C4CE_merry_go_chomp][entry->unk_0A]);
    angle = func_801059BC_merry_go_chomp(angle, -(D_8010DED4_merry_go_chomp * 15.0f));
    move->unk_00.x = sindf(angle) * 180.0f;
    move->unk_00.y = cosdf(angle) * 180.0f;
    move->unk_00.x = (move->unk_00.x - obj->trans.x) / 15.0f;
    move->unk_00.y = (move->unk_00.y - obj->trans.z) / 15.0f;
    move->unk_00.z = atan2df(move->unk_00.x, move->unk_00.y);
    func_80105D38_merry_go_chomp(obj, 6, 0);
    Hu3DMotionSpeedSet(obj->model[0], 1.5f);
    entry->unk_06 = 6;
}

void func_801077D0_merry_go_chomp(omObjData *obj) {
    D_8010C420_merry_go_chomp_Entry *entry = &D_8010C420_merry_go_chomp[obj->work[0]];

    obj->trans.x += entry->unk_00.x;
    obj->trans.z += entry->unk_00.y;
    obj->rot.y = entry->unk_00.z;
}

void func_80107818_merry_go_chomp(omObjData *obj, f32 *outX, f32 *outZ, f32 scale) {
    f32 angle = obj->rot.y;
    s16 quadrant = 0;

    if (angle >= 90.0f) {
        quadrant++;
    }
    if (angle >= 180.0f) {
        quadrant++;
    }
    if (angle >= 270.0f) {
        quadrant++;
    }
    switch (quadrant) {
        case 0:
            *outX = angle * scale;
            *outZ = (90.0f - angle) * scale;
            break;
        case 1:
            angle -= 90.0f;
            *outX = (90.0f - angle) * scale;
            *outZ = -(angle * scale);
            break;
        case 2:
            angle -= 180.0f;
            *outX = -(angle * scale);
            *outZ = -(90.0f - angle) * scale;
            break;
        case 3:
            angle -= 270.0f;
            *outX = -(90.0f - angle) * scale;
            *outZ = angle * scale;
            break;
    }
}

s8 func_80107980_merry_go_chomp(void) {
    MerryGoChompEntry *entry;
    D_8010C420_merry_go_chomp_Entry *move;
    omObjData *obj;
    s8 found = -1;
    s8 zone;
    s8 i;
    f32 angle;

    for (i = 0; i < 4; i++) {
        entry = &D_8010C500_merry_go_chomp[i + 5];
        obj = entry->obj;
        if (entry->unk_04 == 0) {
            move = &D_8010C420_merry_go_chomp[i];
            zone = -1;
            angle = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            switch (D_8010C4CE_merry_go_chomp) {
                case 0:
                    if (angle >= 306.0f || angle < 18.0f) {
                        zone = 0;
                    }
                    if (angle >= 18.0f && angle < 90.0f) {
                        zone = 1;
                    }
                    if (angle >= 90.0f && angle < 162.0f) {
                        zone = 2;
                    }
                    if (angle >= 162.0f && angle < 234.0f) {
                        zone = 3;
                    }
                    if (angle >= 234.0f && angle < 306.0f) {
                        found = i;
                    }
                    break;
                case 1:
                    if (angle >= 315.0f || angle < 45.0f) {
                        zone = 0;
                    }
                    if (angle >= 45.0f && angle < 135.0f) {
                        zone = 1;
                    }
                    if (angle >= 135.0f && angle < 225.0f) {
                        zone = 2;
                    }
                    if (angle >= 225.0f && angle < 315.0f) {
                        found = i;
                    }
                    break;
                case 2:
                    if (angle >= 330.0f || angle < 90.0f) {
                        zone = 0;
                    }
                    if (angle >= 90.0f && angle < 210.0f) {
                        zone = 1;
                    }
                    if (angle >= 210.0f && angle < 330.0f) {
                        found = i;
                    }
                    break;
            }
            move->unk_20 = zone;
        }
    }
    return found;
}

void func_80107E34_merry_go_chomp(omObjData *obj) {
    s8 index = obj->work[0];
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[index + 5];
    D_8010C420_merry_go_chomp_Entry *move = &D_8010C420_merry_go_chomp[index];

    if (entry->unk_04 != 0) {
        return;
    }
    switch (move->unk_1C) {
        case 0:
            move->unk_1D = 0;
            move->unk_1E = 0;
            move->unk_14 = obj->trans.x;
            move->unk_18 = obj->trans.z;
            move->unk_10 = 18.0f;
            move->unk_0C = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
            func_80106B9C_merry_go_chomp(obj, 1);
            move->unk_1C++;
            D_8010C4BD_merry_go_chomp = 0;
            break;
        case 1:
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (sqrtf(move->unk_14 * move->unk_14 + move->unk_18 * move->unk_18) > 350.0f) {
                move->unk_1C++;
            }
            break;
        case 2:
            if (move->unk_1E != 0) {
                func_80106B9C_merry_go_chomp(obj, 0);
                move->unk_1E++;
                if (move->unk_1E < 16) {
                    break;
                }
                func_80106B9C_merry_go_chomp(obj, 1);
                move->unk_1E = 0;
            }
            move->unk_0C =
                func_801059BC_merry_go_chomp(atan2df(410.0f - move->unk_14, 100.0f - move->unk_18), 0.0f);
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (move->unk_10 == 0.0f) {
                func_80106B9C_merry_go_chomp(obj, 0);
            } else {
                func_80106B9C_merry_go_chomp(obj, 1);
            }
            if (move->unk_14 > 390.0f && move->unk_14 < 430.0f && move->unk_18 > 80.0f && move->unk_18 < 120.0f) {
                move->unk_1C++;
            }
            break;
        case 3:
            if (move->unk_1E != 0) {
                func_80106B9C_merry_go_chomp(obj, 0);
                move->unk_1E++;
                if (move->unk_1E < 16) {
                    break;
                }
                func_80106B9C_merry_go_chomp(obj, 1);
                move->unk_1E = 0;
            }
            move->unk_0C =
                func_801059BC_merry_go_chomp(atan2df(490.0f - move->unk_14, -20.0f - move->unk_18), 0.0f);
            move->unk_14 += sindf(move->unk_0C) * move->unk_10;
            move->unk_18 += cosdf(move->unk_0C) * move->unk_10;
            if (move->unk_10 == 0.0f) {
                func_80106B9C_merry_go_chomp(obj, 0);
            } else {
                func_80106B9C_merry_go_chomp(obj, 1);
            }
            if (move->unk_14 > 470.0f && move->unk_14 < 510.0f && move->unk_18 > -40.0f && move->unk_18 < 0.0f) {
                move->unk_1C++;
                obj->work[1] = D_8010C4BD_merry_go_chomp;
                D_8010C4BD_merry_go_chomp++;
            }
            break;
        case 4:
            func_80106B9C_merry_go_chomp(obj, 2);
            func_8001C258_main(obj->model[1], 4, 4);
            obj->rot.y = 210.0f;
            if (obj->trans.y < 630.0f) {
                obj->trans.y += 10.0f;
            } else {
                obj->trans.y = 630.0f;
                func_80106B9C_merry_go_chomp(obj, 6);
                move->unk_00.x = (D_8010C1B8_merry_go_chomp[obj->work[1]] - move->unk_14) / 17.0f;
                move->unk_00.y = (D_8010C1C8_merry_go_chomp[obj->work[1]] - move->unk_18) / 17.0f;
                move->unk_00.z = atan2df(move->unk_00.x, move->unk_00.y);
                move->unk_1D = 0;
                move->unk_1C++;
            }
            break;
        case 5:
            if (move->unk_1D == 0) {
                PlayerFXPlay(0x3A, obj->work[0]);
            }
            func_8001C258_main(obj->model[1], 4, 0);
            func_801077D0_merry_go_chomp(obj);
            move->unk_1F = 1;
            obj->trans.y += D_8010C160_merry_go_chomp[move->unk_1D];
            entry->unk_24 = D_8010C174_merry_go_chomp[move->unk_1D];
            move->unk_1D++;
            if (move->unk_1D >= 17) {
                move->unk_1F = 0;
                func_80106B9C_merry_go_chomp(obj, 0);
                move->unk_1C++;
                PlayerFXPlay(0x31, obj->work[0]);
            }
            break;
        case 6:
            if (func_80105F40_merry_go_chomp(obj, 330.0f)) {
                func_80106B9C_merry_go_chomp(obj, 1);
            } else {
                func_80106B9C_merry_go_chomp(obj, 0);
                D_8010DEDC_merry_go_chomp |= 1 << obj->work[1];
                move->unk_1C++;
            }
            break;
        case 7:
            break;
    }
    if (entry->unk_06 == 1) {
        func_80106AF4_merry_go_chomp(obj);
    }
}

#ifdef NON_MATCHING
// Only difference: GCC hoists the D_8010C420_merry_go_chomp address out of the
// first loop into a saved register, which the original does not.
void func_801084C8_merry_go_chomp(void) {
    D_8010C420_merry_go_chomp_Entry *move;
    D_8010C420_merry_go_chomp_Entry *other;
    MerryGoChompEntry *entry;
    MerryGoChompEntry *otherEntry;
    omObjData *obj;
    omObjData *otherObj;
    s8 push = 0;
    s8 collided;
    s8 i;
    s8 j;
    f32 angle;
    f32 dist;
    f32 dx;
    f32 dz;

    for (i = 0; i < 4; i++) {
        move = &D_8010C420_merry_go_chomp[i];
        entry = &D_8010C500_merry_go_chomp[i + 5];
        if (move->unk_1C >= 2 && entry->unk_04 == 0) {
            dist = sqrtf(move->unk_14 * move->unk_14 + move->unk_18 * move->unk_18);
            if (dist < 350.0f) {
                angle = func_801059BC_merry_go_chomp(atan2df(move->unk_14, move->unk_18), 0.0f);
                move->unk_14 = sindf(angle) * 350.0f;
                move->unk_18 = cosdf(angle) * 350.0f;
            }
        }
    }

    do {
        collided = 0;
        for (i = 0; i < 4; i++) {
            move = &D_8010C420_merry_go_chomp[i];
            entry = &D_8010C500_merry_go_chomp[i + 5];
            obj = entry->obj;
            if (entry->unk_04 != 0 || obj->trans.y > 5.0f) {
                continue;
            }
            for (j = 0; j < 4; j++) {
                if (i == j) {
                    continue;
                }
                other = &D_8010C420_merry_go_chomp[j];
                otherEntry = &D_8010C500_merry_go_chomp[j + 5];
                otherObj = otherEntry->obj;
                if (otherEntry->unk_04 != 0) {
                    continue;
                }
                dx = move->unk_14 - other->unk_14;
                dz = move->unk_18 - other->unk_18;
                if (sqrtf(dx * dx + dz * dz) >= 120.0f) {
                    continue;
                }
                dx = move->unk_14 - 490.0f;
                dz = move->unk_18 + 20.0f;
                dist = sqrtf(dx * dx + dz * dz);
                dx = other->unk_14 - 490.0f;
                dz = other->unk_18 + 20.0f;
                if (dist < sqrtf(dx * dx + dz * dz)) {
                    push = 2;
                }
                if (obj->trans.y > 5.0f && obj->trans.y < 160.0f) {
                    push = 2;
                }
                if (otherObj->trans.y > 5.0f && otherObj->trans.y < 160.0f) {
                    push = 1;
                }
                if (obj->trans.y > 160.0f) {
                    push = 0;
                }
                if (otherObj->trans.y > 160.0f) {
                    push = 0;
                }
                switch (push) {
                    case 1:
                        angle = func_801059BC_merry_go_chomp(
                            atan2df(move->unk_14 - other->unk_14, move->unk_18 - other->unk_18), 0.0f);
                        move->unk_14 = sindf(angle) * 121.0f + other->unk_14;
                        move->unk_18 = cosdf(angle) * 121.0f + other->unk_18;
                        move->unk_1E = collided = 1;
                        break;
                    case 2:
                        angle = func_801059BC_merry_go_chomp(
                            atan2df(other->unk_14 - move->unk_14, other->unk_18 - move->unk_18), 0.0f);
                        other->unk_14 = sindf(angle) * 121.0f + move->unk_14;
                        other->unk_18 = cosdf(angle) * 121.0f + move->unk_18;
                        collided = 1;
                        break;
                }
            }
        }
    } while (collided);

    for (i = 0; i < 4; i++) {
        move = &D_8010C420_merry_go_chomp[i];
        entry = &D_8010C500_merry_go_chomp[i + 5];
        obj = entry->obj;
        if (entry->unk_04 == 0 && move->unk_1C < 5) {
            obj->trans.x = move->unk_14;
            obj->trans.z = move->unk_18;
            obj->rot.y = move->unk_0C;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_801084C8_merry_go_chomp);
#endif

void func_80108A88_merry_go_chomp(omObjData *obj) {
    s8 index = obj->work[0];
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[index + 5];
    D_8010C420_merry_go_chomp_Entry *move = &D_8010C420_merry_go_chomp[index];
    s8 choices[5];
    s8 count;
    s8 i;

    if (entry->unk_04 != 0) {
        if (entry->unk_04 == 2) {
            Hu3DMotionSpeedSet(obj->model[0], 1.0f);
            entry->unk_04 = 3;
        }
        return;
    }
    switch (D_8010C4B0_merry_go_chomp) {
        case 0:
            move->unk_1C = 0;
            move->unk_1D = 0;
            entry->unk_0C = -1;
            func_80106B9C_merry_go_chomp(obj, 0);
            break;
        case 1:
            if (D_8010C4B2_merry_go_chomp < 144 && obj->work[1] == D_8010DEDD_merry_go_chomp) {
                if (D_8010C4B2_merry_go_chomp > 0) {
                    if (GwPlayer[index].stat & 1) {
                        if (entry->unk_0C < 0) {
                            for (i = 0, count = 0; i < 5 - D_8010C4CE_merry_go_chomp; i++) {
                                if (D_8010C4BE_merry_go_chomp[i] != 0) {
                                    choices[count] = i;
                                    count++;
                                }
                            }
                            entry->unk_0C = choices[func_80105CE4_merry_go_chomp(count)];
                        }
                    } else if (!(D_800D5558_main[obj->work[3]] & 0x8000)) {
                        break;
                    }
                }
                if (func_80106CC4_merry_go_chomp(obj)) {
                    D_8010DEDC_merry_go_chomp = 1;
                    func_80107664_merry_go_chomp(obj);
                }
            }
            break;
        case 2:
            if (obj->work[1] == D_8010DEDD_merry_go_chomp) {
                if (D_8010C4B2_merry_go_chomp == 0) {
                    PlayerFXPlay(0x3A, obj->work[0]);
                }
                if (D_8010C4B2_merry_go_chomp < 15) {
                    move->unk_1F = 1;
                    obj->trans.x += move->unk_00.x;
                    obj->trans.z += move->unk_00.y;
                    obj->trans.y += D_8010C160_merry_go_chomp[D_8010C4B2_merry_go_chomp];
                    obj->rot.y = move->unk_00.z;
                    entry->unk_24 = D_8010C174_merry_go_chomp[D_8010C4B2_merry_go_chomp];
                }
                if (D_8010C4B2_merry_go_chomp == 10) {
                    func_80106B9C_merry_go_chomp(obj, 0);
                }
                if (D_8010C4B2_merry_go_chomp == 15) {
                    PlayerFXPlay(0x31, obj->work[0]);
                    move->unk_1F = 0;
                    entry->unk_18 = func_801059BC_merry_go_chomp(atan2df(obj->trans.x, obj->trans.z), 0.0f);
                    entry->unk_1C = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
                    entry->unk_08++;
                }
            } else if (entry->unk_08 == 0) {
                func_80106B9C_merry_go_chomp(obj, 1);
                func_80106AF4_merry_go_chomp(obj);
                obj->trans.x -= 7.0f;
                obj->trans.z += 4.0f;
            }
            break;
        case 3:
            func_80106B9C_merry_go_chomp(obj, 0);
            break;
        case 4:
            if (D_8010C4B2_merry_go_chomp < 50) {
                func_80106B9C_merry_go_chomp(obj, 5);
                if (obj->trans.y > 5.0f) {
                    obj->trans.y -= 10.0f;
                } else {
                    obj->trans.y = 5.0f;
                }
            }
            break;
        case 5:
            if (D_8010C4B2_merry_go_chomp < 30) {
                entry->unk_08 = 0;
                if (move->unk_20 == -1) {
                    entry->unk_0E = 3 - D_8010C4CE_merry_go_chomp;
                }
            } else if (move->unk_20 == -1) {
                if (!func_80105F40_merry_go_chomp(obj, 270.0f)) {
                    func_80106B9C_merry_go_chomp(obj, 7);
                    PlayerFXPlay(0x286, obj->work[0]);
                    entry->unk_04 = 1;
                }
            } else if (!func_80105F40_merry_go_chomp(obj, 0.0f)) {
                if (D_8010C4CE_merry_go_chomp == 2) {
                    D_8010C4C8_merry_go_chomp = obj;
                    func_80106B9C_merry_go_chomp(obj, 0);
                } else {
                    func_80106B9C_merry_go_chomp(obj, 8);
                }
            }
            break;
        case 9:
            func_80107E34_merry_go_chomp(obj);
            break;
        case 6:
            if (!func_80105F40_merry_go_chomp(obj, 0.0f)) {
                func_80106B9C_merry_go_chomp(obj, 8);
            }
            break;
        case 7:
            func_80106B9C_merry_go_chomp(obj, 5);
            break;
        case 8:
            break;
    }
    if (entry->unk_08 != 0) {
        entry->unk_18 = func_801059BC_merry_go_chomp(entry->unk_18, -D_8010DED4_merry_go_chomp);
        obj->trans.x = sindf(entry->unk_18) * entry->unk_1C;
        obj->trans.z = cosdf(entry->unk_18) * entry->unk_1C;
        obj->rot.y = func_801059BC_merry_go_chomp(obj->rot.y, -D_8010DED4_merry_go_chomp);
    }
    if (move->unk_1F == 0) {
        entry->unk_20 = obj->trans.y;
    }
    if (obj->trans.y > 505.0f) {
        entry->unk_20 = 505.0f;
    }
    if (obj->trans.y <= 5.0f) {
        entry->unk_20 = 5.0f;
    }
    Hu3DModelPosSet(obj->model[1], obj->trans.x, entry->unk_20, obj->trans.z);
    Hu3DModelScaleSet(obj->model[1], entry->unk_24, 1.0f, entry->unk_24);
}

void func_801090B0_merry_go_chomp(omObjData *obj) {
    u16 player = obj->work[0];
    MerryGoChompEntry *entry = &D_8010C500_merry_go_chomp[player + 5];
    u16 chr = GwPlayer[player].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][3], 0x2B9);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 2));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x15));
    func_8000B460_main(obj, 5, func_80017BB8_main(chr, 8));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x8B));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x29));
    func_8000B460_main(obj, 7, func_80017BB8_main(chr, 0x7A));
    func_8000B460_main(obj, 6, func_80017BB8_main(chr, 4));
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, func_80017BB8_main(chr, 0x30));
    func_8000B460_main(obj, 10, func_80017BB8_main(chr, 0x37));
    obj->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(obj->model[1], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80088800_main(Hu3DData[obj->model[1]].mtx, 0.0f, 0.0f, 0.0f);
    omSetTra(obj, D_8010C1B8_merry_go_chomp[obj->work[1]], 505.0f, D_8010C1C8_merry_go_chomp[obj->work[1]]);
    omSetRot(obj, 0.0f, 330.0f, 0.0f);
    Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
    entry->unk_24 = 1.0f;
    func_80105D38_merry_go_chomp(obj, 0, 2);
    entry->unk_06 = 0;
    Hu3DModelCameraSet(obj->model[0], 2);
    Hu3DModelCameraSet(obj->model[1], 2);
    D_8010C420_merry_go_chomp[player].unk_00.x = 0.0f;
    D_8010C420_merry_go_chomp[player].unk_00.y = 0.0f;
    D_8010C420_merry_go_chomp[player].unk_00.z = 0.0f;
    D_8010C420_merry_go_chomp[player].unk_1C = 0;
    D_8010C420_merry_go_chomp[player].unk_1D = 0;
    D_8010C420_merry_go_chomp[player].unk_1F = 0;
    D_8010DEDD_merry_go_chomp = 0;
    obj->work[3] = GwPlayer[player].pad;
    obj->func = func_80108A88_merry_go_chomp;
}

void func_80109420_merry_go_chomp(void) {
    MerryGoChompEntry *entry;
    omObjData *obj;
    s8 slots[4];
    u16 player = 0;
    s8 pick;
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        slots[i] = i;
    }
    for (i = 0; i < 4; i++) {
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
        }
        entry = &D_8010C500_merry_go_chomp[i + 5];
        obj = omAddObj(0x320, 3, 12, -1, func_801090B0_merry_go_chomp);
        obj->work[0] = player;
        entry->obj = obj;
        pick = func_80105CE4_merry_go_chomp(4 - i);
        obj->work[1] = slots[pick];
        slots[pick] = -1;
        for (j = 1; j < 4 - i; j++) {
            if (slots[j - 1] == -1) {
                slots[j - 1] = slots[j];
                slots[j] = -1;
            }
        }
    }
}

void func_80109604_merry_go_chomp(void) {
    MerryGoChompEntry *entry;
    s8 i;

    for (i = 0; i < 4; i++) {
        entry = &D_8010C794_merry_go_chomp[i];
        GwPlayer[entry->obj->work[0]].bonusCoin = entry->unk_0E;
    }
}

#ifdef NON_MATCHING
// Differs in register usage: the 0.0f constant is materialized after the first
// load, and the D_8010C4D0_merry_go_chomp[0] stores go through a saved base
// register instead of direct symbol addressing.
void func_80109670_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *chomp = &D_8010C500_merry_go_chomp[10];
    Vec2f *link;
    f32 angle;
    f32 divisor;
    f32 dx;
    f32 dz;
    f32 dist;
    s8 i;

    if (chomp->unk_18 != 0.0f || chomp->unk_1C != 0.0f || chomp->unk_30 != obj->rot.y) {
        obj->trans.x += chomp->unk_18;
        obj->trans.z += chomp->unk_1C;
        angle = func_801059BC_merry_go_chomp(obj->rot.y, 180.0f);
        D_8010C4D0_merry_go_chomp[0].x = sindf(angle) * 70.0f + obj->trans.x;
        D_8010C4D0_merry_go_chomp[0].y = cosdf(angle) * 70.0f + obj->trans.z;
        if (chomp->unk_2C > 15.0f) {
            divisor = 2.0f;
        } else {
            divisor = 5.0f;
        }
        for (i = 1; i < 6; i++) {
            link = &D_8010C4D0_merry_go_chomp[i];
            dx = D_8010C4D0_merry_go_chomp[i - 1].x - link->x;
            dz = D_8010C4D0_merry_go_chomp[i - 1].y - link->y;
            dist = dx * dx + dz * dz;
            if (dist > 5625.0f) {
                link->x = dx / divisor + link->x;
                link->y = dz / divisor + link->y;
            }
            Hu3DModelPosSet(obj->model[i], link->x, 30.0f, link->y);
            Hu3DModelPosSet(obj->model[i + 6], link->x, 5.0f, link->y);
        }
        link = &D_8010C4D0_merry_go_chomp[5];
        if (link->x != D_8010C214_merry_go_chomp.x || link->y != D_8010C214_merry_go_chomp.y) {
            link->x = D_8010C214_merry_go_chomp.x;
            link->y = D_8010C214_merry_go_chomp.y;
            for (i = 4; i >= 0; i--) {
                link = &D_8010C4D0_merry_go_chomp[i];
                dx = D_8010C4D0_merry_go_chomp[i + 1].x - link->x;
                dz = D_8010C4D0_merry_go_chomp[i + 1].y - link->y;
                dist = dx * dx + dz * dz;
                if (dist > 5625.0f) {
                    link->x = dx / divisor + link->x;
                    link->y = dz / divisor + link->y;
                }
                Hu3DModelPosSet(obj->model[i], link->x, 30.0f, link->y);
                Hu3DModelPosSet(obj->model[i + 6], link->x, 5.0f, link->y);
            }
        }
    }
    chomp->unk_30 = obj->rot.y;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109670_merry_go_chomp);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_80109A04_merry_go_chomp);

#ifdef NON_MATCHING
// The code matches, but the original rodata has an unreferenced "" string
// literal following "c165n_4_DEF" that is not reproduced here.
void func_8010A9D0_merry_go_chomp(omObjData *obj) {
    MerryGoChompEntry *chomp = &D_8010C500_merry_go_chomp[10];
    void *anim = DataRead(0xA00E5);
    s32 chain;
    s32 shadow;
    s16 i;

    obj->model[0] = func_8000B108_main(0xA00D9, 0x2A9);
    Hu3DAnimCreate(Hu3DData[obj->model[0]].hmf, anim, 0, "c165n_4_DEF");
    Hu3DModelRemakeStatic(obj->model[0]);
    func_8001C514_main(obj->model[0]);
    DataClose(anim);
    func_8000B460_main(obj, 0, 0xA00DD);
    func_8000B460_main(obj, 1, 0xA00E3);
    func_8000B460_main(obj, 2, 0xA00DB);
    obj->model[1] = func_8000B108_main(0xA00E4, 0x2B9);
    chain = obj->model[1];
    for (i = 2; i < 6; i++) {
        obj->model[i] = Hu3DModelLink(chain);
    }
    shadow = func_8000B0A0_main(0, 0xC9);
    obj->model[6] = shadow;
    func_8001C2FC_main(obj->model[6], 0x80000000, 0);
    Hu3DModelRemakeStatic(obj->model[6]);
    func_8001C514_main(obj->model[6]);
    func_80088800_main(Hu3DData[obj->model[6]].mtx, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 2.5f, 1.0f, 2.5f);
    for (i = 7; i < 12; i++) {
        obj->model[i] = Hu3DModelLink(shadow);
    }
    func_80105D38_merry_go_chomp(obj, 0, 2);
    chomp->unk_06 = 0;
    omSetTra(obj, -500.0f, 0.0f, 60.0f);
    omSetRot(obj, 0.0f, 60.0f, 0.0f);
    Hu3DModelPosSet(obj->model[6], obj->trans.x, obj->trans.y, obj->trans.z);
    for (i = 0; i < 7; i++) {
        Hu3DModelCameraSet(obj->model[i], 2);
    }
    for (i = 1; i < 6; i++) {
        D_8010C4D0_merry_go_chomp[i].x = (5 - i) * 45 + D_8010C214_merry_go_chomp.x + 20.0f;
        D_8010C4D0_merry_go_chomp[i].y = (5 - i) * 10 + D_8010C214_merry_go_chomp.y;
        Hu3DModelPosSet(obj->model[i], D_8010C4D0_merry_go_chomp[i].x, 30.0f, D_8010C4D0_merry_go_chomp[i].y);
        Hu3DModelPosSet(obj->model[i + 6], D_8010C4D0_merry_go_chomp[i].x, 5.0f, D_8010C4D0_merry_go_chomp[i].y);
        Hu3DModelScaleSet(obj->model[i + 6], 0.8f, 1.0f, 0.8f);
    }
    func_8001C258_main(obj->model[5], 4, 4);
    func_8001C258_main(obj->model[11], 4, 4);
    obj->func = func_80109A04_merry_go_chomp;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2D_merry_go_chomp/25E110", func_8010A9D0_merry_go_chomp);
#endif

void func_8010ADE8_merry_go_chomp(void) {
    D_8010CA28_merry_go_chomp = omAddObj(0x384, 0xF, 4, -1, func_8010A9D0_merry_go_chomp);
}

void func_8010AE24_merry_go_chomp(omObjData *obj) {
}

void func_8010AE2C_merry_go_chomp(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x4E0003, 0x2B9);
    func_8001C258_main(obj->model[0], 4, 4);
    Hu3DMotionSpeedSet(obj->model[0], 0.0f);
    obj->scale.x = obj->scale.y = obj->scale.z = 2.5f;
    obj->rot.y = 270.0f;
    Hu3DModelCameraSet(obj->model[0], 2);
    obj->func = func_8010AE24_merry_go_chomp;
}

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
