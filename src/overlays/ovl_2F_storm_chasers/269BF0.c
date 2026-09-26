#include "common.h"

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
extern s32 D_8010CCA0_storm_chasers;
extern s32 D_8010CCA4_storm_chasers;
extern s32 D_8010CCAC_storm_chasers;
extern StormChaserPlayer D_8010CD80_storm_chasers[4];
extern StormChaserData D_8010CCE0_storm_chasers[4];
extern StormChaserState D_8010CEE0_storm_chasers[2];
extern StormChaserEntry D_8010CF38_storm_chasers[4];
extern u16 D_8010CF0A_storm_chasers;
extern f32 D_8010CF0C_storm_chasers;
extern f32 D_8010CF10_storm_chasers;
extern s32 fontcolor;

void func_80106218_storm_chasers(omObjData *);
void func_8010662C_storm_chasers(omObjData *);
void func_801068C8_storm_chasers(omObjData *);
void func_8010746C_storm_chasers(omObjData *);
void func_801077A0_storm_chasers(omObjData *);
void func_80107F70_storm_chasers(omObjData *);
void func_80108C64_storm_chasers(omObjData *);
void func_8010B87C_storm_chasers(omObjData *);
void func_8010BE8C_storm_chasers(omObjData *);
void func_8010BF84_storm_chasers(omObjData *);
void func_8010C060_storm_chasers(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801059A0_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801059BC_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80105AA0_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80105B6C_storm_chasers);

void func_80105B9C_storm_chasers(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80105C14_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80105D64_storm_chasers);

void func_801060E0_storm_chasers(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010610C_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106184_storm_chasers);

void func_801061C0_storm_chasers(void) {
    func_8000BBD4_main(D_8010CF0A_storm_chasers, D_8010CF0C_storm_chasers, D_8010CF10_storm_chasers);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_80106218_storm_chasers);

void func_8010637C_storm_chasers(void) {
    omAddObj(0x96, 1, 0, -1, func_80106218_storm_chasers);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_801063B0_storm_chasers);

void func_80106624_storm_chasers(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010662C_storm_chasers);

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
    omSetStatBit(object, 0xA0);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010B738_storm_chasers);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010BF84_storm_chasers);

void func_8010C014_storm_chasers(omObjData *object) {
    GMesCreate(0x1A, 0x1E, 0xA0, 0x1C);
    D_8010CCAC_storm_chasers = 0x385;
    object->func = func_8010BF84_storm_chasers;
}

void func_8010C060_storm_chasers(omObjData *object) {
    if (++D_8010CAB0_storm_chasers == 0x3F) {
        HuAudSeqPlay(0x38);
    }
    if (GMesStatGet() == 0 || (GMesStatGet() & 2)) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C240_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C264_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C29C_storm_chasers);

void func_8010C2F4_storm_chasers(void) {
    D_8010CCA0_storm_chasers += D_8010CCA4_storm_chasers;
    D_8010CCA4_storm_chasers = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C31C_storm_chasers);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C428_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C438_storm_chasers);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C4C0_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C520_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C57C_storm_chasers);

void func_8010C604_storm_chasers(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C60C_storm_chasers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", func_8010C780_storm_chasers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2F_storm_chasers/269BF0", D_8010CC8C_storm_chasers);
