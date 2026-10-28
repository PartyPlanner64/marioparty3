#include "common.h"
#include "mallocblock.h"
#include "overlays/minigame.h"

// Per-object work block, reached via ObjData->data
typedef struct ChipShotChallengeWork {
    /* 0x00 */ char pad_00[0x34];
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ char pad_4C[4];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s8 unk_52;
    /* 0x53 */ s8 unk_53;
    /* 0x54 */ s8 unk_54;
    /* 0x55 */ char pad_55[4];
    /* 0x59 */ s8 playerIndex;
    /* 0x5A */ char pad_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ char pad_68[0xC];
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ char pad_80[4];
    /* 0x84 */ s32 unk_84[9];
    /* 0xA8 */ char pad_A8[4];
} ChipShotChallengeWork; // Size 0xAC

typedef struct ChipShotChallengeSphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} ChipShotChallengeSphere; // Size 0x10

extern s32 D_8010AAA0_chip_shot_challenge;
extern s32 D_8010A824_chip_shot_challenge;
extern f32 D_8010A828_chip_shot_challenge;
extern f32 D_8010A82C_chip_shot_challenge;
extern f32 D_8010A970_chip_shot_challenge;
extern f32 D_8010A974_chip_shot_challenge;
extern f32 D_8010A834_chip_shot_challenge;
extern Vec D_8010AAA4_chip_shot_challenge;
extern s32 D_8010A840_chip_shot_challenge;
extern s16 D_8010A846_chip_shot_challenge;
extern s32 D_8010AAC0_chip_shot_challenge;
extern s32 D_8010AAC4_chip_shot_challenge;
extern s32 D_8010AAC8_chip_shot_challenge;
extern s32 D_8010AACC_chip_shot_challenge;
extern f32 D_800D5410_main;
extern f32 D_800D51FC_main;
extern s16 D_8010AAD2_chip_shot_challenge[];
extern s32 D_8010AAD8_chip_shot_challenge[4];
extern s16 D_8010AAE8_chip_shot_challenge;
extern omObjData *D_8010AAF0_chip_shot_challenge;
extern f32 D_8010A954_chip_shot_challenge;
extern f32 D_8010A984_chip_shot_challenge[4];
extern f32 D_8010A994_chip_shot_challenge[4];
extern f32 D_8010A9A4_chip_shot_challenge[];
extern s32 D_8010A958_chip_shot_challenge;
extern s32 D_8010A928_chip_shot_challenge;
extern s32 D_8010A92C_chip_shot_challenge;
extern s32 D_8010A930_chip_shot_challenge;
extern s32 D_8010A934_chip_shot_challenge;
extern s32 D_800A178C_main[][6];

f32 func_800202A8_main(f32 angle);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_800E149C_minigame(omObjData *, s32, s32);
void func_800E3584_minigame(s16);
void func_800E3628_minigame(s16, Vec *);
void func_80013390_main(s16 model, s32 arg1, s32 arg2, void (*callback)(s16));
s16 HmfAnimRead(HmfData *, s32, char *);
void func_801071A8_chip_shot_challenge(void);
void func_801073D4_chip_shot_challenge(s16 model);
void func_80107238_chip_shot_challenge(s16 model);
void func_801087AC_chip_shot_challenge(omObjData *object);
void func_801091E8_chip_shot_challenge(omObjData *object);
void func_801094D8_chip_shot_challenge(omObjData *object);
void func_80109B24_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z);
f32 func_80109DE0_chip_shot_challenge(omObjData *object, ChipShotChallengeSphere *sphere);
void func_80109EF0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_8010A04C_chip_shot_challenge(ChipShotChallengeSphere *sphere, Vec *normal);
void func_8010A3DC_chip_shot_challenge(omObjData *object, Vec *arg1);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801059A0_chip_shot_challenge);

s32 func_80105DE0_chip_shot_challenge(s32 playerIndex) {
    s32 scores[4];
    s32 rank;
    s32 i;

    for (i = 0; i < 4; i++) {
        scores[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }
    for (i = 0, rank = 0; i < 4; i++) {
        if (i != playerIndex) {
            rank += scores[playerIndex] < scores[i];
        }
    }
    return rank;
}

void func_80105E8C_chip_shot_challenge(void) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80105EB8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010646C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80106B84_chip_shot_challenge);

void func_80107048_chip_shot_challenge(void) {
    s32 files[4] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E };
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(files[i], 0xAA9);
        D_8010AAD8_chip_shot_challenge[i] = model;
        func_8003302C_main(HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, 0, func_801073D4_chip_shot_challenge);
    }
}

void func_801071A8_chip_shot_challenge(void) {
    s32 *entries;
    s16 i;

    for (i = 0, entries = D_8010AAD8_chip_shot_challenge; i < 4; i++) {
        if (((D_8010AAE8_chip_shot_challenge + i) & 3) == 0) {
            func_80107238_chip_shot_challenge(entries[i]);
        }
    }
    D_8010AAE8_chip_shot_challenge++;
}

void func_80107238_chip_shot_challenge(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (rand8() - 127.0f) * 2.0f;
            particle->unk10 = D_8010AAA4_chip_shot_challenge.y + 700.0f;
            particle->unk14 = ((rand8() * 125) >> 5) - 500;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk08 = 5.0f;
            break;
        }
    }
}

void func_801073D4_chip_shot_challenge(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 15.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_80107520_chip_shot_challenge(omObjData *object) {
    void *data;
    s16 image1;
    s16 image2;
    s16 group;
    s16 i;
    s16 x;

    D_800D51FC_main = D_800D5410_main = 0.0f;
    object->model[1] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[2] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[3] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[4] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[5] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[6] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[7] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[8] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[9] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[10] = func_8000B0A0_main(0x3C0007, 0xAD9);
    D_800D5410_main = 1.0f;
    D_800D51FC_main = 1.0f;
    object->func = func_801091E8_chip_shot_challenge;

    data = DataRead(0x2D);
    image1 = func_80055810_main(data);
    DataClose(data);
    data = DataRead(0x3C001F);
    image2 = func_80055810_main(data);
    DataClose(data);

    group = D_8010AAC0_chip_shot_challenge = HuSprGrpCreate(4, 5);
    func_80055024_main(group, 0, image1, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    func_80054904_main(group, 0, 0x80, 0x64);
    HuSprPriSet(group, 0, 1);
    x = 15;
    for (i = 1; i < 4; i++) {
        HuSprPriSet(group, i, 1);
        func_80055024_main(group, i, image1, 0);
        func_80054904_main(group, i, x, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x8000);
        if (i == 1) {
            x += 20;
        } else {
            x += 15;
        }
        func_800554C4_main(group, i, 0);
    }
    HuSprAttrReset(group, 2, 0x8000);

    group = D_8010AAC4_chip_shot_challenge = HuSprGrpCreate(2, 5);
    func_80055024_main(group, 0, image2, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    func_80054904_main(group, 0, 0x9F, 0x64);
    HuSprPriSet(group, 0, 1);
    HuSprPriSet(group, 1, 1);
    func_80055024_main(group, 1, image2, 0);
    func_80054904_main(group, 1, 0x23, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, 0x8000);
    func_800554C4_main(group, 1, 0);
    HuSprAttrReset(group, 2, 0x8000);

    D_8010AACC_chip_shot_challenge = func_8000B0A0_main(0x3C001D, 0xAD9);
    D_8010AAC8_chip_shot_challenge = func_8000B0A0_main(0x3C001C, 0xAD9);
}

void func_80107960_chip_shot_challenge(s16 value) {
    s16 digit;

    if ((s16)(value / 1000) != 0) {
        HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
        func_80055140_main(D_8010AAC0_chip_shot_challenge, 0, value / 1000, 0);
        func_800550F4_main(D_8010AAC0_chip_shot_challenge, 0, 1);
    }
    value -= (s16)(value / 1000) * 1000;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    digit = value / 100;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 1, digit, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 1, 1);
    value -= digit * 100;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    digit = value / 10;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 2, digit, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 2, 1);
    value -= digit * 10;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 3, value, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 3, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 0, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 1, 0);
}

void func_80107BB0_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&dir);
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010AAA4_chip_shot_challenge.y + 700.0f - D_8010A840_chip_shot_challenge * 10.0f;
        Center.y *= 1.02f;
        D_8010A954_chip_shot_challenge = -9.0f;
        if (D_8010A958_chip_shot_challenge != 0) {
            HuAudFXPlay(0x3DF);
            D_8010A958_chip_shot_challenge = 0;
        }
    } else {
        y = D_8010AAA4_chip_shot_challenge.y + 400.0f + sindf(D_8010A954_chip_shot_challenge) * 100.0f;
        D_8010A954_chip_shot_challenge -= 9.0f;
        Center.y *= 1.02f;
        D_8010A958_chip_shot_challenge = -1;
    }
    if (D_8010A840_chip_shot_challenge < 101) {
        func_801071A8_chip_shot_challenge();
    }
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[0], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[1], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[2], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[3], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    if (D_8010AAA4_chip_shot_challenge.y + 400.0f < Center.y) {
        Center.y = D_8010AAA4_chip_shot_challenge.y + 400.0f;
    }
    Hu3DModelPosSet(D_8010AAD2_chip_shot_challenge[0], x, y, z);
    Hu3DModelPosSet(D_8010AAC8_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AAC8_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 0);
}

void func_80107E94_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&dir);
    if (D_8010A840_chip_shot_challenge == 1) {
        func_8004AC98_main(0x3DC, D_8010A846_chip_shot_challenge);
    }
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010A840_chip_shot_challenge * 10.0f + -200.0f;
    } else {
        y = 100.0f;
    }
    x += dir.x * 200.0f;
    z += dir.z * 200.0f;
    Hu3DModelPosSet(D_8010AAD2_chip_shot_challenge[0], x, y, z);
    Hu3DModelPosSet(D_8010AACC_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACC_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 0);
}

void func_8010802C_chip_shot_challenge(void) {
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 4);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 4);
    if (func_800E6E8C_minigame() >= 2) {
        func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 4);
    }
}

void func_80108108_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ChipShotChallengeWork), 0x7918);
    memset(object->data, 0, sizeof(ChipShotChallengeWork));
    work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    object->model[0] = func_8000B0A0_main(0x3C0008, 0xAB9);
    object->model[1] = func_8000B0D4_main(9, 0xAB9);
    func_800E3584_minigame(object->model[1]);
    work->unk_44 = 0.3f;
    work->unk_48 = 60.0f;
    work->unk_34 = 50.0f;
    work->unk_3C = 0.0f;
    work->unk_78 = 0;
    work->unk_52 = 7;
    work->unk_7C = 0;
    work->unk_50 = 0;
    work->unk_40 = 0.0f;
    work->unk_38 = 1000.0f;
    work->unk_74 = 0.5f;
    work->unk_54 = 1;
    for (i = 0; i < 9; i++) {
        work->unk_84[i] = 0;
    }
    func_800E149C_minigame(object, 0, 2);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelScaleSet(object->model[1], 0.4f, 0.4f, 0.4f);
    object->func = func_801094D8_chip_shot_challenge;
}

func_800E1BA8_minigame_ObjData *func_80108274_chip_shot_challenge(omObjData *object, s32 player) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;
    s32 chr;
    s32 model;
    s32 motion;
    s32 tag;

    motion = D_800A178C_main[GwPlayer[player].chr][2];
    model = D_800A178C_main[GwPlayer[player].chr][0];
    tag = 0xAA9;
    chr = GwPlayer[player].chr;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    data = HuMemAllocTag(0x15C, 0x7918);
    object->data = data;
    memset(data, 0, 0x15C);
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), 0x7918);
    object->model[0] = func_8000B0A0_main(model | motion, tag);
    object->model[1] = func_8000B0A0_main(9, tag);
    func_80017790_main(object->model[0], 2, chr, func_80017B6C_main(chr, 2, 0));
    object->model[4] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
    func_800E5978_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5978_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5978_minigame(object, 2, func_80017BB8_main(chr, 0x5E), 1, 0);
    func_800E5978_minigame(object, 3, func_80017BB8_main(chr, 0x5F), 0, 0);
    func_800E5978_minigame(object, 5, func_80017BB8_main(chr, 0x2F), 0, 0);
    func_800E5978_minigame(object, 6, func_80017BB8_main(chr, 0x36), 0, 0);
    object->model[2] = func_8000B0A0_main((chr + 10) | 0x3C0000, tag);
    object->model[3] = func_8000B0A0_main((chr + 0x12) | 0x3C0000, 0x4AD);
    func_8001EF6C_main(object->model[2], object->model[0], "item_hook");
    func_8001C258_main(object->model[2], 0x4000, 0x4000);
    func_8001FA68_main(object->model[3]);
    func_8001F9E4_main(object->model[3], 0x80);
    data->unk40 = 50.0f;
    object->func = func_801087AC_chip_shot_challenge;
    data->unk50 = 0;
    func_8001C5B4_main(object->model[0], object->motion[0]);
    func_8001C814_main(object->model[0], 2, 2);
    object->rot.y = 90.0f;
    data->unk59 = player;
    data->unk57 = GwPlayer[player].pad;
    return data;
}

void func_801085C0_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge);

    object->trans.x = -300.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 0;
}

void func_80108638_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A92C_chip_shot_challenge);

    object->trans.x = -600.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 1;
}

void func_801086B4_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A930_chip_shot_challenge);

    object->trans.x = -900.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 2;
}

void func_80108730_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A934_chip_shot_challenge);

    object->trans.x = -1200.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 3;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA00_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801087AC_chip_shot_challenge);

void func_801091E8_chip_shot_challenge(omObjData *object) {
    Vec delta;
    f32 rotX;
    f32 x;
    f32 y;
    f32 z;
    f32 step;
    f32 baseScale;
    f32 scaleStep;
    f32 scale;
    s32 i;

    if (D_8010A824_chip_shot_challenge == 1) {
        rotX = 90.0f;
        x = z = 0.0f;
        y = 20.0f;
        step = D_8010A82C_chip_shot_challenge / 3.0f;
        baseScale = (D_8010A82C_chip_shot_challenge - 60.0f) / 40.0f * 20.0f;
        scaleStep = D_8010A82C_chip_shot_challenge / 100.0f;
        for (i = 0; i < 10; i++) {
            func_8001C258_main(object->model[i + 1], 4, 0);
            delta.x = x;
            delta.y = y;
            delta.z = z;
            y += step;
            step -= 0.1f;
            x += sindf(D_8010A828_chip_shot_challenge + 180.0f) * step;
            z += cosdf(D_8010A828_chip_shot_challenge + 180.0f) * step;
            delta.x -= x;
            delta.y -= y;
            delta.z -= z;
            Hu3DModelPosSet(object->model[i + 1], x, y, z);
            Hu3DModelRotSet(object->model[i + 1], rotX, 0.0f, 0.0f);
            scale = baseScale + scaleStep * i + sindf(D_8010A974_chip_shot_challenge) * 0.5f;
            if (scale >= 30.0f) {
                scale = 30.0f;
            }
            func_8001C6A8_main(object->model[i + 1], scale);
            rotX -= 7.0f;
        }
        D_8010A974_chip_shot_challenge += D_8010A82C_chip_shot_challenge / 10.0f;
        D_8010A970_chip_shot_challenge = func_800202A8_main(D_8010A970_chip_shot_challenge + 10.0f);
    } else {
        for (i = 0; i < 20; i++) {
            func_8001C258_main(object->model[i + 1], 4, 4);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801094D8_chip_shot_challenge);

void func_80109AD0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    ChipShotChallengeSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = data->unk48;
    func_80109B24_chip_shot_challenge(object, x, y, z);
    func_80109DE0_chip_shot_challenge(object, &sphere);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109B24_chip_shot_challenge);

f32 func_80109DE0_chip_shot_challenge(omObjData *object, ChipShotChallengeSphere *sphere) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    Vec normal = { 0.0f, 1.0f, 0.0f };
    f32 y = sphere->pos.y;
    f32 floorY = func_8010A04C_chip_shot_challenge(sphere, &normal);
    f32 resultY = floorY;

    if (floorY < y - work->unk_34 || y + work->unk_34 <= floorY) {
        if (work->unk_38 == 1000.0f) {
            work->unk_38 = 0.0f;
        }
        resultY = y;
    }
    func_8010A3DC_chip_shot_challenge(object, &normal);
    func_80109EF0_chip_shot_challenge(object, sphere->pos.x, resultY, sphere->pos.z, floorY, &normal);
    return resultY;
}

void func_80109EF0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 scale = 0.5f;
    f32 height = y - floorY;

    if (floorY == -65536.0f) {
        func_8001C258_main(object->model[1], 4, 4);
        return;
    }
    if (height != 0.0f) {
        if (height > 400.0f) {
            scale = 0.1f;
        } else {
            scale = 0.5 - fabs(height) / 1000.0;
        }
        work->unk_53 = -1;
    }
    Hu3DModelPosSet(object->model[1], x, floorY + 3.0f, z);
    Hu3DModelScaleSet(object->model[1], scale, 0.5f, scale);
    func_800E3628_minigame(object->model[1], normal);
    func_8001C258_main(object->model[1], 4, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010A04C_chip_shot_challenge);

void func_8010A3DC_chip_shot_challenge(omObjData *object, Vec *arg1) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);

    if (D_8010AAA0_chip_shot_challenge == 1 && work->unk_38 == 1000.0f) {
        work->unk_5C = arg1->x * D_8010A834_chip_shot_challenge;
        work->unk_60 = arg1->y;
        work->unk_64 = arg1->z * D_8010A834_chip_shot_challenge;
    } else {
        work->unk_5C = 0.0f;
        work->unk_60 = 0.0f;
        work->unk_64 = 0.0f;
    }
}

void func_8010A454_chip_shot_challenge(omObjData *object, s32 *stickX, s32 *stickY, s32 *buttons) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 dist;
    s32 playerIndex;
    s32 difficulty;

    if (GwPlayer[work->playerIndex].stat & 1) {
        *buttons = 0;
        *stickY = 0;
        *stickX = 0;
        x = D_8010AAA4_chip_shot_challenge.x;
        y = D_8010AAA4_chip_shot_challenge.y;
        z = D_8010AAA4_chip_shot_challenge.z;
        playerIndex = work->playerIndex;
        difficulty = GwPlayer[playerIndex].cpu_difficulty;
        if (D_8010A984_chip_shot_challenge[playerIndex] == 1000.0f) {
            angle = (rand8() - 127.0f) / 128.0f * 5.0f * D_8010A9A4_chip_shot_challenge[difficulty];
            D_8010A984_chip_shot_challenge[playerIndex] = angle;
        }
        if (D_8010A994_chip_shot_challenge[playerIndex] == 1000.0f) {
            dist = (rand8() - 127.0f) / 128.0f * 10.0f * D_8010A9A4_chip_shot_challenge[difficulty];
            D_8010A994_chip_shot_challenge[playerIndex] = dist;
        }
        dist = HuSqrtf(x * x + y * y + z * z);
        angle = atan2df(x, z) + D_8010A984_chip_shot_challenge[playerIndex];
        if (angle < 0.0f) {
            angle += 180.0f;
        } else {
            angle -= 180.0f;
        }
        if (fabs(angle - work->unk_3C) > 1.0) {
            if (work->unk_3C < angle) {
                *stickX = -30;
            }
            if (angle < work->unk_3C) {
                *stickX = 30;
            }
        }
        dist = (dist - 150.0f) / 10.0f + D_8010A994_chip_shot_challenge[playerIndex];
        dist *= 1.1f;
        if (dist < 65.0f) {
            dist = 65.0f;
        }
        if (dist > 100.0f) {
            dist = 100.0f;
        }
        if (fabs(dist - work->unk_40) > 10.0) {
            *stickY = !(work->unk_40 < dist) ? 30 : -30;
        }
        if (*stickX == 0 && *stickY == 0) {
            *buttons |= 0x8000;
        }
    }
}
