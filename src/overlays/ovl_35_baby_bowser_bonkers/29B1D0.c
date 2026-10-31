#include "common.h"

typedef struct UnkBabyBowserBonkers { // 0x12 bytes
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} UnkBabyBowserBonkers;

typedef struct BabyBowserBonkersPlayer { // 0x50 bytes, 2 entries
    s16 unk_00;                          // player index
    s16 unk_02;                          // steps taken
    s16 unk_04;                          // whose turn
    s16 unk_06;
    f32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    Vec unk_1C;
    s16 unk_28; // GwPlayer index
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    f32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
} BabyBowserBonkersPlayer;

typedef struct BabyBowserBonkersActor { // 0x30 bytes, 0xE entries
    s16 unk_00;
    s16 unk_02; // model index
    s16 unk_04;
    s16 unk_06; // state
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s32 unk_14;
    f32 unk_18; // timer
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    void *unk_28;                                    // callback
    void (*unk_2C)(struct BabyBowserBonkersActor *); // callback
} BabyBowserBonkersActor;

typedef union BabyBowserBonkersBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BabyBowserBonkersBytes;

extern UnkBabyBowserBonkers *D_8010BCAC_baby_bowser_bonkers;
extern BabyBowserBonkersActor *D_8010BC60_baby_bowser_bonkers;

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *, f32, f32);
void func_80109E98_baby_bowser_bonkers(s32, s16);
void func_80108F9C_baby_bowser_bonkers(BabyBowserBonkersActor *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801059A0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80105BB0_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B950_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B95C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80105C0C_baby_bowser_bonkers);

void func_801062E8_baby_bowser_bonkers(void) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010630C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801063B4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010660C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106AA4_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106CEC_baby_bowser_bonkers);

void func_801075F4_baby_bowser_bonkers(omObjData *arg0, f32 arg1, f32 arg2) {
    BabyBowserBonkersPlayer *player = func_8010B3AC_baby_bowser_bonkers(arg0, arg1, arg2);

    player->unk_02++;
    player->unk_44 = arg1;
    player->unk_48 = arg2;
    func_80109E98_baby_bowser_bonkers(player->unk_00, player->unk_02);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107648_baby_bowser_bonkers);

void func_80107678_baby_bowser_bonkers(omObjData *arg0, s32 arg1, s32 arg2) {
    HmfModel *model;
    HmfModel *otherModel;
    HmfData *temp;

    model = &HmfModelData[arg0->model[(s16)arg1]];
    otherModel = &HmfModelData[arg0->model[(s16)arg2]];

    temp = model->hmf;
    model->hmf = otherModel->hmf;
    otherModel->hmf = temp;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801076D8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107CD8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107D38_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80107E54_baby_bowser_bonkers);

s32 func_801080D0_baby_bowser_bonkers(f32 arg0, f32 arg1) {
    if (__builtin_fabs((f64)arg0) < 200.0 && __builtin_fabs((f64)arg1) < 200.0) {
        return 0;
    }
    if (arg0 > 0.0f) {
        if (arg1 > 0.0f) {
            return 1;
        }
        return 2;
    }
    if (arg1 > 0.0f) {
        return 3;
    }
    return 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108160_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801081C0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010831C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108454_baby_bowser_bonkers);

void func_801089CC_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = HmfModelData + actor->unk_02;

    actor->unk_06 = 0;
    actor->unk_04 = 0;
    actor->unk_08 = -1;
    actor->unk_18 = 0;
    model->attr |= 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108A0C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108B84_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108D6C_baby_bowser_bonkers);

void func_80108E90_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = HmfModelData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 4;
    actor->unk_04 = 0;
    actor->unk_18 = 110.0f;
    scale = 1.0f - (f32)actor->unk_0A / 5.0f;
    if (scale <= 0.0f) {
        scale = 0.0f;
    }
    model->scale.x = 1.0f;
    model->scale.z = 1.0f;
    model->scale.y = 0.4f - scale * 0.35f;
    model->motSpeed = 0.0f;
    if (15.0f <= (f32)actor->unk_0A) {
        actor->unk_0A = 0;
        actor->unk_2C = func_80108F9C_baby_bowser_bonkers;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108F9C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109080_baby_bowser_bonkers);

BabyBowserBonkersActor *func_8010919C_baby_bowser_bonkers(s32 arg0) {
    if (arg0 < 14) {
        if (arg0 >= 0) {
            return &D_8010BC60_baby_bowser_bonkers[arg0];
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801091D4_baby_bowser_bonkers);

s32 func_80109388_baby_bowser_bonkers(UnkBabyBowserBonkers *arg0, s32 arg1) {
    if (arg0->unk_08 == 0) {
        return 0;
    }
    switch (arg0->unk_06) {
        case 1:
            return 1;
        case 2:
            if (arg0->unk_0A > arg0->unk_0E - arg1) {
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801093D4_baby_bowser_bonkers(s32 arg0) {
    BabyBowserBonkersActor *actor = &D_8010BC60_baby_bowser_bonkers[arg0];

    if (actor->unk_08 != 0) {
        switch (actor->unk_06) {
            case 1:
                return actor->unk_0E;
            case 2:
                return actor->unk_0E - actor->unk_0A;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010943C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010958C_baby_bowser_bonkers);

s32 func_801096D0_baby_bowser_bonkers(void) {
    s32 i;
    BabyBowserBonkersActor *actor;

    for (i = 0, actor = D_8010BC60_baby_bowser_bonkers; i < 14; i++, actor++) {
        if (actor->unk_06 != 0) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109704_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010984C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109890_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109990_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109BFC_baby_bowser_bonkers);

void func_80109E98_baby_bowser_bonkers(s32 arg0, s16 arg1) {
    s16 *field = &D_8010BCAC_baby_bowser_bonkers[arg0].unk_0E;

    *field = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109EB8_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010BA00_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109FE8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010A6D8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AB14_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AD00_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AEF0_baby_bowser_bonkers);

f32 func_8010B044_baby_bowser_bonkers(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B148_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B308_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B320_baby_bowser_bonkers);

void func_8010B380_baby_bowser_bonkers(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *arg0, f32 arg1, f32 arg2) {
    BabyBowserBonkersBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return (BabyBowserBonkersPlayer *)packed.word;
}
