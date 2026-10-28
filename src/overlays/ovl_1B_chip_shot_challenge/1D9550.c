#include "common.h"

// Per-object work block, reached via ObjData->data
typedef struct ChipShotChallengeWork {
    /* 0x00 */ char pad_00[0x38];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ char pad_44[0x15];
    /* 0x59 */ s8 playerIndex;
    /* 0x5A */ char pad_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
} ChipShotChallengeWork; // Size 0x68

typedef struct ChipShotChallengeModelEntry {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 model;
} ChipShotChallengeModelEntry; // Size 0x04

extern s32 D_8010AAA0_chip_shot_challenge;
extern f32 D_8010A834_chip_shot_challenge;
extern Vec D_8010AAA4_chip_shot_challenge;
extern s32 D_8010A840_chip_shot_challenge;
extern s16 D_8010A846_chip_shot_challenge;
extern s16 D_8010AAC2_chip_shot_challenge[];
extern s16 D_8010AAC6_chip_shot_challenge[];
extern s16 D_8010AACA_chip_shot_challenge[];
extern s16 D_8010AACE_chip_shot_challenge[];
extern s16 D_8010AAD2_chip_shot_challenge[];
extern ChipShotChallengeModelEntry D_8010AAD8_chip_shot_challenge[4];
extern s16 D_8010AAE8_chip_shot_challenge;
extern omObjData *D_8010AAF0_chip_shot_challenge;
extern f32 D_8010A954_chip_shot_challenge;
extern f32 D_8010A984_chip_shot_challenge[4];
extern f32 D_8010A994_chip_shot_challenge[4];
extern f32 D_8010A9A4_chip_shot_challenge[];
extern s32 D_8010A958_chip_shot_challenge;

void func_801071A8_chip_shot_challenge(void);
void func_80107238_chip_shot_challenge(s16 model);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010A9D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107048_chip_shot_challenge);

void func_801071A8_chip_shot_challenge(void) {
    ChipShotChallengeModelEntry *entries;
    s16 i;

    for (i = 0, entries = D_8010AAD8_chip_shot_challenge; i < 4; i++) {
        if (((D_8010AAE8_chip_shot_challenge + i) & 3) == 0) {
            func_80107238_chip_shot_challenge(entries[i].model);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80107520_chip_shot_challenge);

void func_80107960_chip_shot_challenge(s16 value) {
    s16 digit;

    if ((s16)(value / 1000) != 0) {
        HuSprAttrReset(D_8010AAC2_chip_shot_challenge[0], 0, 0x8000);
        func_80055140_main(D_8010AAC2_chip_shot_challenge[0], 0, value / 1000, 0);
        func_800550F4_main(D_8010AAC2_chip_shot_challenge[0], 0, 1);
    }
    value -= (s16)(value / 1000) * 1000;
    HuSprAttrReset(D_8010AAC2_chip_shot_challenge[0], 1, 0x8000);
    digit = value / 100;
    func_80055140_main(D_8010AAC2_chip_shot_challenge[0], 1, digit, 0);
    func_800550F4_main(D_8010AAC2_chip_shot_challenge[0], 1, 1);
    value -= digit * 100;
    HuSprAttrReset(D_8010AAC2_chip_shot_challenge[0], 2, 0x8000);
    digit = value / 10;
    func_80055140_main(D_8010AAC2_chip_shot_challenge[0], 2, digit, 0);
    func_800550F4_main(D_8010AAC2_chip_shot_challenge[0], 2, 1);
    value -= digit * 10;
    HuSprAttrReset(D_8010AAC2_chip_shot_challenge[0], 3, 0x8000);
    func_80055140_main(D_8010AAC2_chip_shot_challenge[0], 3, value, 0);
    func_800550F4_main(D_8010AAC2_chip_shot_challenge[0], 3, 1);
    HuSprAttrReset(D_8010AAC6_chip_shot_challenge[0], 0, 0x8000);
    func_80054FF8_main(D_8010AAC6_chip_shot_challenge[0], 0, 1);
    HuSprAttrReset(D_8010AAC6_chip_shot_challenge[0], 1, 0x8000);
    func_80054FF8_main(D_8010AAC6_chip_shot_challenge[0], 1, 0);
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
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge->model, D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[1].model, D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[2].model, D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[3].model, D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    if (D_8010AAA4_chip_shot_challenge.y + 400.0f < Center.y) {
        Center.y = D_8010AAA4_chip_shot_challenge.y + 400.0f;
    }
    Hu3DModelPosSet(D_8010AAD2_chip_shot_challenge[0], x, y, z);
    Hu3DModelPosSet(D_8010AACA_chip_shot_challenge[0], x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACA_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AACA_chip_shot_challenge[0], 4, 0);
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
    Hu3DModelPosSet(D_8010AACE_chip_shot_challenge[0], x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACE_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AACE_chip_shot_challenge[0], 4, 0);
    func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_8010802C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108108_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108274_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801085C0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108638_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801086B4_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80108730_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA00_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801087AC_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801091E8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_801094D8_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109AD0_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109B24_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109DE0_chip_shot_challenge);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", D_8010AA2C_chip_shot_challenge);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_1B_chip_shot_challenge/1D9550", func_80109EF0_chip_shot_challenge);

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
