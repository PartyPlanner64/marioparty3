#include "common_duel.h"
#include "../ovl_81_name/ovl_81.h"

// In duel mode, GW_SYSTEM's board data (from halfWordBytes[2] onward, running
// past the end of the union) holds six per-player duel records, one s16 for
// each of the two players.
#define DUEL_RECORD(record, player) (GwSystem.boardData.halfWordBytes[(record) * 2 + 2 + (player)])

extern UnkBoard4 *D_80108DB4_duelresult2[2];
extern UnkBoard4 *D_80108DBC_duelresult2;
extern UnkOvl81_2 *D_80108DC0_duelresult2;
extern UnkBoard4 *D_80108DC4_duelresult2;
extern UnkBoard4 *D_80108DC8_duelresult2;
extern UnkBoard4 *D_80108DCC_duelresult2;
extern UnkBoard4 *D_80108DD0_duelresult2[2];
extern UnkBoard4 *D_80108DD8_duelresult2;
extern UnkBoard4 *D_80108DDC_duelresult2;
extern UnkBoard4 *D_80108DE0_duelresult2;
extern UnkBoard4 *D_80108DE4_duelresult2;
extern s32 D_80108DE8_duelresult2[16];
extern s16 D_80108E28_duelresult2[10];
extern UnkBoard4 *D_80108C30_duelresult2;
extern s32 D_80108C34_duelresult2;
extern s32 D_80108C38_duelresult2;
extern s16 D_80108E3C_duelresult2;
extern s16 D_80108E3E_duelresult2;

void func_80105B98_duelresult2(s16 model, s16 animIdx);
void func_80106F7C_duelresult2(void);
void func_801084F4_duelresult2(void);
void func_80108B38_duelresult2(omObjData *);
void func_80108B7C_duelresult2(omObjData *);
void func_80108BA0_duelresult2(void);
void func_80108BF8_duelresult2(void);
void func_80108BCC_duelresult2(void);
void func_80108C28_duelresult2(void);

void func_801059A0_duelresult2(void) {
    u32 i;

    omInitObjMan(0x50, 0x50);
    func_80108BF8_duelresult2();
    func_80108BA0_duelresult2();
    HuWinInit();
    omAddPrcObj(func_801084F4_duelresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80108B7C_duelresult2);

    for (i = 0; i < 16; i++) {
        do {
            D_80108DE8_duelresult2[i] = func_800EFE20_name_81(7.0f);
        } while (i != 0 && D_80108DE8_duelresult2[i - 1] == D_80108DE8_duelresult2[i]);
    }
}

s16 func_80105A8C_duelresult2(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    D_80108E3C_duelresult2 = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_80108E3E_duelresult2 = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_80105B98_duelresult2(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_80108E3E_duelresult2 != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            anim = &D_800D1714_main[D_80108E3E_duelresult2];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_80105C68_duelresult2(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80105CB0_duelresult2);

void func_80106848_duelresult2(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800F4584_name_81(D_80108DB4_duelresult2[i]);
    }

    func_800F4584_name_81(D_80108DBC_duelresult2);

    if (D_80108C30_duelresult2 != NULL) {
        func_800F4584_name_81(D_80108C30_duelresult2);
    }
}

void func_801068BC_duelresult2(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprDispOff(D_80108DB4_duelresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOff(D_80108DBC_duelresult2->unk_0A, 0);

    if (D_80108C30_duelresult2 != NULL) {
        HuSprDispOff(D_80108C30_duelresult2->unk_0A, 0);
    }
}

void func_80106974_duelresult2(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprDispOn(D_80108DB4_duelresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOn(D_80108DBC_duelresult2->unk_0A, 0);

    if (D_80108C30_duelresult2 != NULL) {
        HuSprDispOn(D_80108C30_duelresult2->unk_0A, 0);
    }
}

s32 func_80106A2C_duelresult2(s32 category) {
    s32 max;
    s32 mask = 0;
    s32 i;

    switch (category) {
        case 0:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].star) {
                    max = GwPlayer[i].star;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].star == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 1:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].coin) {
                    max = GwPlayer[i].coin;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].coin == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 2:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].gamePrize) {
                    max = GwPlayer[i].gamePrize;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].gamePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 3:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].coinPrize) {
                    max = GwPlayer[i].coinPrize;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].coinPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 4:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(5, i)) {
                    max = DUEL_RECORD(5, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(5, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 5:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(0, i)) {
                    max = DUEL_RECORD(0, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(0, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 6:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(3, i)) {
                    max = DUEL_RECORD(3, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(3, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 7:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(4, i)) {
                    max = DUEL_RECORD(4, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(4, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 8:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(1, i)) {
                    max = DUEL_RECORD(1, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(1, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 9:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(2, i)) {
                    max = DUEL_RECORD(2, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(2, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
    }

    if (mask == 3) {
        return 0;
    }
    return mask;
}

void func_80106F7C_duelresult2(void) {
    u8 buf[8];
    s32 offsets[] = { 0, -30, -25, -20, -15 };
    GW_PLAYER *player;
    s32 mask;
    s32 value;
    s32 digits;
    s32 row;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 10; i++) {
        HuSprDispOff(D_80108DDC_duelresult2->unk_0A, i);
    }

    for (i = D_80108C34_duelresult2, row = 0; i < D_80108C34_duelresult2 + 4; i++, row++) {
        HuSprDispOn(D_80108DDC_duelresult2->unk_0A, i);
        HuSprPosSet(D_80108DDC_duelresult2->unk_0A, i, row * 44 + 145, 73);
    }

    for (i = 0; i < 64; i++) {
        HuSprDispOff(D_80108DE0_duelresult2->unk_0A, i);
    }

    for (i = D_80108C34_duelresult2, row = 0; i < D_80108C34_duelresult2 + 4; i++, row++) {
        for (j = 0; j < 2; j++) {
            player = MBDGetPlayerStruct(j);
            mask = func_80106A2C_duelresult2(i);
            digits = 1;
            value = 1;
            switch (i) {
                case 0:
                    value = player->star;
                    digits = 2;
                    break;
                case 1:
                    value = player->coin;
                    digits = 3;
                    break;
                case 2:
                    value = player->gamePrize;
                    if (value >= 1000) {
                        value = 999;
                    }
                    digits = 3;
                    break;
                case 3:
                    value = player->coinPrize;
                    digits = 3;
                    break;
                case 4:
                    value = DUEL_RECORD(5, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 5:
                    value = DUEL_RECORD(0, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 6:
                    value = DUEL_RECORD(3, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 7:
                    value = DUEL_RECORD(4, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 8:
                    value = DUEL_RECORD(1, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 9:
                    value = DUEL_RECORD(2, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
            }
            if (value < 0) {
                value = 0;
            }
            sprintf((char *)buf, "%4d", value);

            for (k = 0; k < 4; k++) {
                if (buf[k] == ' ') {
                    HuSprDispOff(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k);
                    continue;
                }
                if (mask & (1 << j)) {
                    HuSprGrpMemberSet(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k,
                                      D_80108DE0_duelresult2->unk_0C[1], 0);
                } else {
                    HuSprGrpMemberSet(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k,
                                      D_80108DE0_duelresult2->unk_0C[0], 0);
                }
                HuSprDispOn(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k);
                HuSprPosSet(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k,
                            row * 44 + (s16)(k * 10 + 145) + offsets[digits], j * 26 + 99);
                HuSprBankSet(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k, buf[k] - '0', 0);
                func_800550F4_main(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k, 1);
            }
        }
    }

    HuSprPosSet(D_80108DE4_duelresult2->unk_0A, 0, D_80108C38_duelresult2 * 44 + 146, 100);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D08_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D28_duelresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/duelresult2/45D380", D_80108D48_duelresult2);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_80107454_duelresult2);

void func_80107FEC_duelresult2(void) {
    s32 i;

    func_800F4584_name_81(D_80108DC4_duelresult2);
    func_800F4584_name_81(D_80108DC8_duelresult2);
    func_800F4584_name_81(D_80108DCC_duelresult2);

    for (i = 0; i < 2; i++) {
        func_800F4584_name_81(D_80108DD0_duelresult2[i]);
    }

    func_800F4584_name_81(D_80108DD8_duelresult2);
    func_800F4584_name_81(D_80108DDC_duelresult2);
    func_800F4584_name_81(D_80108DE0_duelresult2);
    func_800F4584_name_81(D_80108DE4_duelresult2);
    func_800E4E64_name_81(D_80108DC0_duelresult2);
}

void func_8010809C_duelresult2(void) {
    s32 i;
    s32 j;

    HuSprDispOff(D_80108DC4_duelresult2->unk_0A, 0);
    HuSprDispOff(D_80108DC8_duelresult2->unk_0A, 0);
    HuSprDispOff(D_80108DC8_duelresult2->unk_0A, 1);
    HuSprDispOff(D_80108DCC_duelresult2->unk_0A, 0);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(D_80108DD0_duelresult2[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOff(D_80108DD8_duelresult2->unk_0A, j);
    }

    for (j = 0; j < 10; j++) {
        HuSprDispOff(D_80108DDC_duelresult2->unk_0A, j);
    }

    for (j = 0; j < 64; j++) {
        HuSprDispOff(D_80108DE0_duelresult2->unk_0A, j);
    }

    HuSprDispOff(D_80108DE4_duelresult2->unk_0A, 0);
    MBDModelDispOff(D_80108DC0_duelresult2->obj);
    HuWinDispOff(D_80108DC0_duelresult2->win_id);
}

void func_80108240_duelresult2(void) {
    s32 i;
    s32 j;

    HuSprDispOn(D_80108DC4_duelresult2->unk_0A, 0);
    HuSprDispOn(D_80108DC8_duelresult2->unk_0A, 0);
    HuSprDispOn(D_80108DC8_duelresult2->unk_0A, 1);
    HuSprDispOn(D_80108DCC_duelresult2->unk_0A, 0);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(D_80108DD0_duelresult2[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOn(D_80108DD8_duelresult2->unk_0A, j);
    }

    func_80106F7C_duelresult2();
    HuSprDispOn(D_80108DE4_duelresult2->unk_0A, 0);
    MBDModelDispOn(D_80108DC0_duelresult2->obj);
    HuWinDispOn(D_80108DC0_duelresult2->win_id);

    if (D_80108C34_duelresult2 == 0 && D_80108C38_duelresult2 == 0) {
        HuSprDispOff(D_80108DD8_duelresult2->unk_0A, 0);
    }
    if (D_80108C34_duelresult2 == 6 && D_80108C38_duelresult2 == 3) {
        HuSprDispOff(D_80108DD8_duelresult2->unk_0A, 1);
    }
}

void func_801083FC_duelresult2(void) {
    s32 messages[] = {
        0x2800,
        0x2801,
        0x2802,
        0x2803,
        0x2804,
        0x2805,
        0x2806,
        0x2807,
        0x2808,
        0x2809,
    };

    HuWinHomeClear(D_80108DC0_duelresult2->win_id);
    HuWinMesSet(D_80108DC0_duelresult2->win_id, messages[D_80108C34_duelresult2 + D_80108C38_duelresult2], -1, -1);
    func_80105B98_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0],
                              D_80108E28_duelresult2[D_80108DE8_duelresult2[D_80108C34_duelresult2 + D_80108C38_duelresult2]]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult2/45D380", func_801084F4_duelresult2);

void func_80108B38_duelresult2(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80108C28_duelresult2();
        func_80108BCC_duelresult2();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_80108B7C_duelresult2(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        arg0->func = func_80108B38_duelresult2;
    }
}

void func_80108BA0_duelresult2(void) {
    MBDModelInit();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80108BCC_duelresult2(void) {
    func_800F4030_name_81();
    MBDModelClose();
    func_800F4314_name_81();
}

void func_80108BF8_duelresult2(void) {
    Hu3DCamInit(2);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_80108C28_duelresult2(void) {
}
