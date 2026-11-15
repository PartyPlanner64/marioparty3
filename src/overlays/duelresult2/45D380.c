#include "common_duel.h"
#include "../ovl_81_name/ovl_81.h"

// In duel mode, GW_SYSTEM's board data (from halfWordBytes[2] onward, running
// past the end of the union) holds six per-player duel records, one s16 for
// each of the two players.
#define DUEL_RECORD(record, player) (GwSystem.boardData.halfWordBytes[(record) * 2 + 2 + (player)])

typedef struct DuelResult2Positions {
    s32 x[4];
} DuelResult2Positions;

typedef struct DuelResult2PlayerFiles {
    s32 files[2][3];
} DuelResult2PlayerFiles;

typedef struct DuelResult2Portraits {
    s32 files[8];
} DuelResult2Portraits;

typedef struct DuelResult2StatFiles {
    s32 files[11];
} DuelResult2StatFiles;

extern const DuelResult2Portraits D_80108D08_duelresult2;
extern const DuelResult2Portraits D_80108D28_duelresult2;
extern const DuelResult2StatFiles D_80108D48_duelresult2;
extern s16 kakusiMasuItemHis[10];

void func_80105B98_duelresult2(s16 model, s16 animIdx);
void func_80106F7C_duelresult2(void);
void func_801084F4_duelresult2(void);
void func_80108B38_duelresult2(omObjData *);
void func_80108B7C_duelresult2(omObjData *);
void func_80108BA0_duelresult2(void);
void func_80108BF8_duelresult2(void);
void func_80108BCC_duelresult2(void);
void func_80108C28_duelresult2(void);

UnkBoard4 *D_80108C30_duelresult2 = NULL;
s32 D_80108C34_duelresult2 = 0;
s32 D_80108C38_duelresult2 = 0;

const DuelResult2PlayerFiles D_80108C40_duelresult2 = { { { 0x130035, 0x130071, 0x130045 }, { 0x130032, 0x130070, 0x130042 } } };
const DuelResult2PlayerFiles D_80108C58_duelresult2 = { { { 0x130066, 0x130067, 0x130068 }, { 0x130063, 0x130064, 0x130065 } } };
const DuelResult2Portraits D_80108C70_duelresult2 = { { 0x130036, 0x130037, 0x130038, 0x130039, 0x13003A, 0x13003B, 0x13003C, 0x13003D } };
const DuelResult2Positions D_80108C90_duelresult2 = { { 0, 60, 142, 0 } };

UnkBoard4 *D_80108DB0_duelresult2 BSS;
UnkBoard4 *D_80108DB4_duelresult2[2] BSS;
UnkBoard4 *D_80108DBC_duelresult2 BSS;
UnkOvl81_2 *D_80108DC0_duelresult2 BSS;
UnkBoard4 *D_80108DC4_duelresult2 BSS;
UnkBoard4 *D_80108DC8_duelresult2 BSS;
UnkBoard4 *D_80108DCC_duelresult2 BSS;
UnkBoard4 *D_80108DD0_duelresult2[2] BSS;
UnkBoard4 *D_80108DD8_duelresult2 BSS;
UnkBoard4 *D_80108DDC_duelresult2 BSS;
UnkBoard4 *D_80108DE0_duelresult2 BSS;
UnkBoard4 *D_80108DE4_duelresult2 BSS;
s32 D_80108DE8_duelresult2[16] BSS;
s16 D_80108E28_duelresult2[10] BSS;
s16 D_80108E3C_duelresult2 BSS;
s16 D_80108E3E_duelresult2 BSS;

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

void func_80105CB0_duelresult2(void) {
    DuelResult2PlayerFiles playerFiles = D_80108C40_duelresult2;
    DuelResult2PlayerFiles rankFiles = D_80108C58_duelresult2;
    DuelResult2Portraits portraits = D_80108C70_duelresult2;
    DuelResult2Positions memberX = D_80108C90_duelresult2;
    void *data;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        D_80108DB4_duelresult2[i] = func_800F4528_name_81(11, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(playerFiles.files[i][j]);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1], 0);
            HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 98 - j);
            HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
            HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, memberX.x[j], 0);
        }

        data = DataRead(portraits.files[GwPlayer[i].chr]);
        D_80108DB4_duelresult2[i]->unk_0C[4] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, 4, D_80108DB4_duelresult2[i]->unk_0C[4], 0);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, 4, 95);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, 4, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, 4, memberX.x[3], 1);

        j = 4;
        if (GwPlayer[i].star >= 10) {
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                          GwPlayer[i].star / 10);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 68, 4);

        data = DataRead(0xC0086);
        D_80108DB4_duelresult2[i]->unk_0C[6] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, 6, D_80108DB4_duelresult2[i]->unk_0C[6],
                          GwPlayer[i].star % 10);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, 6, 93);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, 6, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, 6, 84, 4);

        j = 6;
        if (GwPlayer[i].coin >= 100) {
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                          GwPlayer[i].coin / 100);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 142, 4);

        j = 7;
        data = DataRead(0xC0086);
        D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        if (GwPlayer[i].coin >= 10) {
            HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                              GwPlayer[i].coin / 10 % 10);
        } else {
            HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1],
                              GwPlayer[i].coin);
        }
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 158, 4);

        if (GwPlayer[i].coin >= 10) {
            data = DataRead(0xC0086);
            D_80108DB4_duelresult2[i]->unk_0C[9] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, 9, D_80108DB4_duelresult2[i]->unk_0C[9],
                              GwPlayer[i].coin % 10);
            HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, 9, 90);
            HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, 9, 0x4000);
            HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, 9, 174, 4);
        }

        j = 9;
        if (kakusiMasuItemHis[2] == -1) {
            data = DataRead(rankFiles.files[i][2]);
        } else if (kakusiMasuItemHis[0] == i) {
            data = DataRead(rankFiles.files[i][0]);
        } else {
            data = DataRead(rankFiles.files[i][1]);
        }
        D_80108DB4_duelresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, D_80108DB4_duelresult2[i]->unk_0C[j + 1], 0);
        HuSprPriSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_80108DB4_duelresult2[i]->unk_0A, j + 1, -56, 0);
    }

    for (j = 0; j < 2; j++) {
        HuSprPosSet(D_80108DB4_duelresult2[j]->unk_0A, 0, 111, j * 62 + 91);
    }

    D_80108DBC_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130046);
    D_80108DBC_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DBC_duelresult2->unk_0A, 0, D_80108DBC_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DBC_duelresult2->unk_0A, 0, 90);
    HuSprAttrSet(D_80108DBC_duelresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_80108DBC_duelresult2->unk_0A, 0, 160, 33);

    if (kakusiMasuItemHis[2] != -1) {
        D_80108C30_duelresult2 = func_800F4528_name_81(1, 0);
        data = DataRead(0x130062);
        D_80108C30_duelresult2->unk_0C[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108C30_duelresult2->unk_0A, 0, D_80108C30_duelresult2->unk_0C[0], 0);
        HuSprPriSet(D_80108C30_duelresult2->unk_0A, 0, 89);
        HuSprAttrSet(D_80108C30_duelresult2->unk_0A, 0, 0x4000);
        if (kakusiMasuItemHis[0] == 0) {
            HuSprPosSet(D_80108C30_duelresult2->unk_0A, 0, 55, 64);
        } else {
            HuSprPosSet(D_80108C30_duelresult2->unk_0A, 0, 55, 126);
        }
    } else {
        D_80108C30_duelresult2 = NULL;
    }
}

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
                HuSprAnimModeSet(D_80108DE0_duelresult2->unk_0A, row * 16 + j * 4 + k, 1);
            }
        }
    }

    HuSprPosSet(D_80108DE4_duelresult2->unk_0A, 0, D_80108C38_duelresult2 * 44 + 146, 100);
}

const DuelResult2Portraits D_80108D08_duelresult2 = { { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F } };

const DuelResult2Portraits D_80108D28_duelresult2 = { { 0x1301D5, 0x1301D6, 0x1301D7, 0x1301D8, 0x1301D9, 0x1301DA, 0x1301DB, 0x1301DC } };

const DuelResult2StatFiles D_80108D48_duelresult2 = { { 0x13005A, 0x13004E, 0x13004F, 0x130050, 0x13005B, 0x13005C, 0x13005D, 0x13005E, 0x13005F, 0x130060, 0x130061 } };

void func_80107454_duelresult2(void) {
    s32 rankFiles[2] = { 0x13004A, 0x130047 };
    DuelResult2Portraits nameFiles = D_80108D08_duelresult2;
    DuelResult2Portraits faceFiles = D_80108D28_duelresult2;
    s32 lengthFiles[2] = { 0x130072, 0x130074 };
    DuelResult2StatFiles statFiles = D_80108D48_duelresult2;
    void *data;
    s32 i;

    D_80108DC4_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13006F);
    D_80108DC4_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DC4_duelresult2->unk_0A, 0, D_80108DC4_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DC4_duelresult2->unk_0A, 0, 110);
    HuSprAttrSet(D_80108DC4_duelresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_80108DC4_duelresult2->unk_0A, 0, 74, 39);

    D_80108DC8_duelresult2 = func_800F4528_name_81(2, 0);
    data = DataRead(0x13004B);
    D_80108DC8_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DC8_duelresult2->unk_0A, 0, D_80108DC8_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DC8_duelresult2->unk_0A, 0, 100);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_80108DC8_duelresult2->unk_0A, 0, 210, 36);

    if (GwSystem.playMode & 4) {
        data = DataRead(0x13007C);
    } else if (GwSystem.total_turns == 20) {
        data = DataRead(lengthFiles[0]);
    } else {
        data = DataRead(lengthFiles[1]);
    }
    D_80108DC8_duelresult2->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DC8_duelresult2->unk_0A, 1, D_80108DC8_duelresult2->unk_0C[1], 0);
    HuSprPriSet(D_80108DC8_duelresult2->unk_0A, 1, 99);
    HuSprAttrSet(D_80108DC8_duelresult2->unk_0A, 1, 0x4000);
    HuSprPosSet(D_80108DC8_duelresult2->unk_0A, 1, 210, 36);

    D_80108DCC_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13004C);
    D_80108DCC_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DCC_duelresult2->unk_0A, 0, D_80108DCC_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DCC_duelresult2->unk_0A, 0, 99);
    HuSprAttrSet(D_80108DCC_duelresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_80108DCC_duelresult2->unk_0A, 0, 218, 73);

    for (i = 0; i < 2; i++) {
        D_80108DD0_duelresult2[i] = func_800F4528_name_81(10, 2);
        data = DataRead(rankFiles[i]);
        D_80108DD0_duelresult2[i]->unk_0C[1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DD0_duelresult2[i]->unk_0A, 1, D_80108DD0_duelresult2[i]->unk_0C[1], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 1, 98);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 1, 0x4000);
        HuSprPosSet(D_80108DD0_duelresult2[i]->unk_0A, 1, 172, 0);

        data = DataRead(nameFiles.files[GwPlayer[i].chr]);
        D_80108DD0_duelresult2[i]->unk_0C[2] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DD0_duelresult2[i]->unk_0A, 2, D_80108DD0_duelresult2[i]->unk_0C[2], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 2, 97);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 2, 0x4000);
        HuSprPosSet(D_80108DD0_duelresult2[i]->unk_0A, 2, 36, 1);

        data = DataRead(faceFiles.files[GwPlayer[i].chr]);
        D_80108DD0_duelresult2[i]->unk_0C[3] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DD0_duelresult2[i]->unk_0A, 3, D_80108DD0_duelresult2[i]->unk_0C[3], 0);
        HuSprPriSet(D_80108DD0_duelresult2[i]->unk_0A, 3, 96);
        HuSprAttrSet(D_80108DD0_duelresult2[i]->unk_0A, 3, 0x4000);
        HuSprPosSet(D_80108DD0_duelresult2[i]->unk_0A, 3, 77, 1);
    }

    for (i = 0; i < 2; i++) {
        HuSprPosSet(D_80108DD0_duelresult2[i]->unk_0A, 0, 0, i * 26 + 99);
    }

    D_80108DD8_duelresult2 = func_800F4528_name_81(2, 0);
    for (i = 0; i < 2; i++) {
        data = DataRead(0x13002E);
        D_80108DD8_duelresult2->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DD8_duelresult2->unk_0A, i, D_80108DD8_duelresult2->unk_0C[i], 0);
        HuSprPriSet(D_80108DD8_duelresult2->unk_0A, i, 90);
        HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, i, 0x4000);
        HuSprPosSet(D_80108DD8_duelresult2->unk_0A, i, i * 154 + 133, 161);
    }
    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 0, 1);

    D_80108DDC_duelresult2 = func_800F4528_name_81(10, 0);
    for (i = 0; i < 10; i++) {
        if (i == 9 && GwSystem.current_board_index == 5) {
            data = DataRead(statFiles.files[10]);
        } else {
            data = DataRead(statFiles.files[i]);
        }
        D_80108DDC_duelresult2->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80108DDC_duelresult2->unk_0A, i, D_80108DDC_duelresult2->unk_0C[i], 0);
        HuSprPriSet(D_80108DDC_duelresult2->unk_0A, i, 80);
        HuSprAttrSet(D_80108DDC_duelresult2->unk_0A, i, 0xC000);
    }

    D_80108DE0_duelresult2 = func_800F4528_name_81(64, 0);
    data = DataRead(0x130077);
    D_80108DE0_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x130078);
    D_80108DE0_duelresult2->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 64; i++) {
        HuSprGrpMemberSet(D_80108DE0_duelresult2->unk_0A, i, D_80108DE0_duelresult2->unk_0C[0], 0);
        HuSprPriSet(D_80108DE0_duelresult2->unk_0A, i, 70);
        HuSprAttrSet(D_80108DE0_duelresult2->unk_0A, i, 0xC000);
    }

    D_80108DE4_duelresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13007B);
    D_80108DE4_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_80108DE4_duelresult2->unk_0A, 0, D_80108DE4_duelresult2->unk_0C[0], 0);
    HuSprPriSet(D_80108DE4_duelresult2->unk_0A, 0, 60);
    HuSprAttrSet(D_80108DE4_duelresult2->unk_0A, 0, 0x4000);

    D_80108DC0_duelresult2 = func_800E4B64_name_81(0, 8);
    func_800E4EAC_name_81(D_80108DC0_duelresult2, 105, 8);
    HuVecCopyXYZ(&D_80108DC0_duelresult2->obj->scale, 0.1f, 0.1f, 0.1f);
    HuWinScaleSet(D_80108DC0_duelresult2->win_id, 1.0f, 1.0f);
    func_8005B63C_main(D_80108DC0_duelresult2->win_id, 0x4000, 0x4000);
    HuWinMesPalSet(D_80108DC0_duelresult2->win_id, 2, 255, 96, 96);
    HuWinMesPalSet(D_80108DC0_duelresult2->win_id, 4, 96, 255, 64);
    HuWinMesPalSet(D_80108DC0_duelresult2->win_id, 6, 64, 255, 255);
    func_800E4EAC_name_81(D_80108DC0_duelresult2, 113, 8);

    D_80108E28_duelresult2[0] =
        func_80105A8C_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80108E28_duelresult2[1] = func_80105C68_duelresult2(0xA007F);
    D_80108E28_duelresult2[2] = func_80105C68_duelresult2(0xA0080);
    D_80108E28_duelresult2[3] = func_80105C68_duelresult2(0xA0081);
    D_80108E28_duelresult2[4] = func_80105C68_duelresult2(0xA0082);
    D_80108E28_duelresult2[5] = func_80105C68_duelresult2(0xA0083);
    D_80108E28_duelresult2[6] = func_80105C68_duelresult2(0xA0084);
    func_80105B98_duelresult2(D_80108DC0_duelresult2->obj->omObj1->model[0], D_80108E28_duelresult2[0]);
}

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

void func_801084F4_duelresult2(void) {
    void *data;
    s32 prevPage;
    s32 prevRow;
    s32 timer;
    s32 allCpu;
    s32 showingDetails;
    DuelHelpWin *leftWindow = NULL;
    DuelHelpWin *rightWindow = NULL;
    s32 i;

    D_80108DB0_duelresult2 = func_800F4528_name_81(6, 0);
    data = DataRead(0x13002F);
    D_80108DB0_duelresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 6; i++) {
        HuSprGrpMemberSet(D_80108DB0_duelresult2->unk_0A, i, D_80108DB0_duelresult2->unk_0C[0], 0);
        HuSprPriSet(D_80108DB0_duelresult2->unk_0A, i, 200);
        HuSprAttrSet(D_80108DB0_duelresult2->unk_0A, i, 0x4000);
        HuSprPosSet(D_80108DB0_duelresult2->unk_0A, i, (i / 2) * 128 + 64, (i & 1) * 128 + 64);
    }

    func_80105CB0_duelresult2();
    showingDetails = 0;
    func_80107454_duelresult2();
    func_801083FC_duelresult2();
    func_8010809C_duelresult2();
    func_80106974_duelresult2();

    WipeCreateIn(2, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    allCpu = 0;
    for (i = 0; i < 2; i++) {
        if (!func_800F37B8_name_81(i)) {
            break;
        }
    }
    if (i == 2) {
        allCpu = 1;
    }

    timer = 60;
    while (1) {
        if (allCpu) {
            if (--timer == 0) {
                break;
            }
            if (leftWindow == NULL) {
                leftWindow = func_800E172C_name_81(0x16, 60, 207, 1);
            }
            if (rightWindow == NULL) {
                rightWindow = func_800E172C_name_81(0x17, 200, 207, 1);
            }
        } else {
            for (i = 0; i < 2; i++) {
                if (func_800F37B8_name_81(i)) {
                    continue;
                }
                if (!showingDetails) {
                    if (leftWindow == NULL) {
                        leftWindow = func_800E172C_name_81(0x16, 60, 207, 1);
                    }
                    if (rightWindow == NULL) {
                        rightWindow = func_800E172C_name_81(0x17, 200, 207, 1);
                    }
                    if (D_800C9520_main[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 1;
                        func_801068BC_duelresult2();
                        func_80108240_duelresult2();
                        if (leftWindow != NULL) {
                            func_800E1854_name_81(leftWindow);
                            leftWindow = NULL;
                        }
                        if (rightWindow != NULL) {
                            func_800E1854_name_81(rightWindow);
                            rightWindow = NULL;
                        }
                    } else if (D_800C9520_main[GwPlayer[i].pad] & A_BUTTON) {
                        goto exit;
                    }
                } else {
                    prevRow = D_80108C38_duelresult2;
                    prevPage = D_80108C34_duelresult2;
                    if (D_800C9520_main[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 0;
                        func_8010809C_duelresult2();
                        func_80106974_duelresult2();
                    } else if (D_800D0590_main[GwPlayer[i].pad] & R_JPAD) {
                        if (++D_80108C38_duelresult2 >= 4) {
                            D_80108C38_duelresult2 = 3;
                            if (++D_80108C34_duelresult2 >= 7) {
                                D_80108C34_duelresult2 = 6;
                            }
                        }
                    } else if (D_800D0590_main[GwPlayer[i].pad] & L_JPAD) {
                        if (--D_80108C38_duelresult2 < 0) {
                            D_80108C38_duelresult2 = 0;
                            if (--D_80108C34_duelresult2 < 0) {
                                D_80108C34_duelresult2 = 0;
                            }
                        }
                    }
                    if (D_80108C38_duelresult2 != prevRow || D_80108C34_duelresult2 != prevPage) {
                        func_801083FC_duelresult2();
                        func_80106F7C_duelresult2();
                    }
                }
            }

            if (showingDetails == 1) {
                if (D_80108C34_duelresult2 == 0 && D_80108C38_duelresult2 == 0) {
                    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 0, 0x8000);
                } else {
                    HuSprAttrReset(D_80108DD8_duelresult2->unk_0A, 0, 0x8000);
                }
                if (D_80108C34_duelresult2 == 6 && D_80108C38_duelresult2 == 3) {
                    HuSprAttrSet(D_80108DD8_duelresult2->unk_0A, 1, 0x8000);
                } else {
                    HuSprAttrReset(D_80108DD8_duelresult2->unk_0A, 1, 0x8000);
                }
            }
        }
        HuPrcVSleep();
    }

exit:
    if (leftWindow != NULL) {
        func_800E1854_name_81(leftWindow);
    }
    if (rightWindow != NULL) {
        func_800E1854_name_81(rightWindow);
    }
    if (!(GwSystem.playMode & 4) || kakusiMasuItemHis[2] == -1 ||
        (GwPlayer[kakusiMasuItemHis[0]].stat & PLAYER_IS_CPU)) {
        HuAudSeqFadeOut(60);
    }
    WipeCreateOut(0, 20);
    HuPrcSleep(20);
    func_80106848_duelresult2();
    func_80107FEC_duelresult2();
    func_800F4584_name_81(D_80108DB0_duelresult2);
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

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
