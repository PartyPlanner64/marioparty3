#include "common.h"
#include "../ovl_81_name/ovl_81.h"
#include "overlays/minigame.h"

typedef struct BoardResult2Positions {
    s32 x[4];
} BoardResult2Positions;

typedef struct BoardResult2PlayerFiles {
    s32 files[4][3];
} BoardResult2PlayerFiles;

typedef struct BoardResult2Portraits {
    s32 files[8];
} BoardResult2Portraits;

typedef struct BoardResult2Files4 {
    s32 files[4];
} BoardResult2Files4;

typedef struct BoardResult2BoardFiles {
    s32 files[6];
} BoardResult2BoardFiles;

typedef struct BoardResult2StatFiles {
    s32 files[13];
} BoardResult2StatFiles;

extern BoardResult2Positions D_801097C0_boardresult2;
extern BoardResult2PlayerFiles D_801097D0_boardresult2;
extern BoardResult2Portraits D_80109800_boardresult2;
extern BoardResult2Positions D_80109820_boardresult2;
extern BoardResult2Files4 D_801098B4_boardresult2;
extern BoardResult2BoardFiles D_801098C4_boardresult2;
extern BoardResult2Portraits D_801098DC_boardresult2;
extern BoardResult2Portraits D_801098FC_boardresult2;
extern BoardResult2Files4 D_8010991C_boardresult2;
extern BoardResult2StatFiles D_8010992C_boardresult2;

extern UnkBoard4 *D_801099A0_boardresult2;
extern UnkBoard4 *D_801099A4_boardresult2;
extern UnkBoard4 *D_801099A8_boardresult2;
extern UnkBoard4 *D_801099B0_boardresult2[4];
extern UnkBoard4 *D_801099C0_boardresult2;
extern UnkBoard4 *D_801099C4_boardresult2;
extern UnkOvl81_2 *D_801099C8_boardresult2;
extern UnkBoard4 *D_801099CC_boardresult2;
extern UnkBoard4 *D_801099D0_boardresult2;
extern UnkBoard4 *D_801099D4_boardresult2;
extern UnkBoard4 *D_801099D8_boardresult2[4];
extern UnkBoard4 *D_801099E8_boardresult2;
extern UnkBoard4 *D_801099EC_boardresult2;
extern UnkBoard4 *D_801099F0_boardresult2;
extern UnkBoard4 *D_801099F4_boardresult2;
extern s32 D_801099F8_boardresult2[16];
extern s16 D_80109A38_boardresult2[10];
extern s16 D_80109A4C_boardresult2;
extern s16 D_80109A4E_boardresult2;
extern s32 D_801097B0_boardresult2;
extern s32 D_801097B4_boardresult2;
extern s16 kakusiMasuItemHis[10];

void func_80105B98_boardresult2(s16 model, s16 animIdx);
void func_80105CB0_boardresult2(void);
void func_80106924_boardresult2(void);
void func_801069A4_boardresult2(void);
void func_80106A9C_boardresult2(void);
void func_80107964_boardresult2(void);
void func_80108548_boardresult2(void);
void func_801085F8_boardresult2(void);
void func_8010879C_boardresult2(void);
void func_80108958_boardresult2(void);
void func_80108A48_boardresult2(void);
void func_80108C70_boardresult2(void);
void func_801074B4_boardresult2(void);
s32 func_80106B94_boardresult2(s32);
void func_80108E1C_boardresult2(void);
void func_801096AC_boardresult2(omObjData *);
void func_801096F0_boardresult2(omObjData *);
void func_80109714_boardresult2(void);
void func_8010976C_boardresult2(void);
void func_80109740_boardresult2(void);
void func_8010979C_boardresult2(void);

void func_801059A0_boardresult2(void) {
    u32 i;

    omInitObjMan(0x50, 0x50);
    func_8010976C_boardresult2();
    func_80109714_boardresult2();
    HuWinInit();
    omAddPrcObj(func_80108E1C_boardresult2, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, func_801096F0_boardresult2);

    for (i = 0; i < 16; i++) {
        do {
            D_801099F8_boardresult2[i] = func_800EFE20_name_81(7.0f);
        } while (i != 0 && D_801099F8_boardresult2[i - 1] == D_801099F8_boardresult2[i]);
    }
}

s16 func_80105A8C_boardresult2(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = HmfAnimCreate(HmfModelData[model].hmf, data, 0, name);
    D_80109A4C_boardresult2 = anim;
    func_80032FC0_main(anim, 1, 1);
    DataClose(data);
    animIdx = D_800D1714_main[(s16)anim].animIdx;
    D_80109A4E_boardresult2 = HmfAnimLink(HmfModelData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void func_80105B98_boardresult2(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (D_80109A4E_boardresult2 != 0xFF) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            func_80033970_main(HmfModelData[model].hmf);
            anim = &D_800D1714_main[D_80109A4E_boardresult2];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 func_80105C68_boardresult2(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = func_800329B4_main(data);

    DataClose(data);
    return anim;
}

void func_80105CB0_boardresult2(void) {
    BoardResult2Positions headerX = D_801097C0_boardresult2;
    BoardResult2PlayerFiles playerFiles = D_801097D0_boardresult2;
    BoardResult2Portraits portraits = D_80109800_boardresult2;
    BoardResult2Positions memberX = D_80109820_boardresult2;
    void *data;
    s32 i;
    s32 j;

    D_801099A4_boardresult2 = func_800F4528_name_81(4, 0);
    data = DataRead(0x130030);
    D_801099A4_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (j = 0; j < 4; j++) {
        HuSprGrpMemberSet(D_801099A4_boardresult2->unk_0A, j, D_801099A4_boardresult2->unk_0C[0], 0);
        HuSprPriSet(D_801099A4_boardresult2->unk_0A, j, 99);
        HuSprAttrSet(D_801099A4_boardresult2->unk_0A, j, 0x4000);
        HuSprPosSet(D_801099A4_boardresult2->unk_0A, j, headerX.x[j], 104);
    }

    D_801099A8_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130031);
    D_801099A8_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099A8_boardresult2->unk_0A, 0, D_801099A8_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099A8_boardresult2->unk_0A, 0, 99);
    HuSprAttrSet(D_801099A8_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099A8_boardresult2->unk_0A, 0, 55, 129);

    for (i = 0; i < 4; i++) {
        D_801099B0_boardresult2[i] = func_800F4528_name_81(10, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(playerFiles.files[i][j]);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1], 0);
            HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 98 - j);
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
            HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, memberX.x[j], 0);
        }

        data = DataRead(portraits.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        D_801099B0_boardresult2[i]->unk_0C[4] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, 4, D_801099B0_boardresult2[i]->unk_0C[4], 0);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, 4, 95);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, 4, 0x4000);
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, 4, memberX.x[3], 1);

        j = 4;
        if (GwPlayer[kakusiMasuItemHis[i]].star >= 10) {
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                          GwPlayer[kakusiMasuItemHis[i]].star / 10);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 68, 4);

        data = DataRead(0xC0086);
        D_801099B0_boardresult2[i]->unk_0C[6] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, 6, D_801099B0_boardresult2[i]->unk_0C[6],
                          GwPlayer[kakusiMasuItemHis[i]].star % 10);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, 6, 93);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, 6, 0x4000);
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, 6, 84, 4);

        j = 6;
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 100) {
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                          GwPlayer[kakusiMasuItemHis[i]].coin / 100);
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 142, 4);

        j = 7;
        data = DataRead(0xC0086);
        D_801099B0_boardresult2[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                              GwPlayer[kakusiMasuItemHis[i]].coin / 10 % 10);
        } else {
            HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, D_801099B0_boardresult2[i]->unk_0C[j + 1],
                              GwPlayer[kakusiMasuItemHis[i]].coin);
        }
        HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, j + 1, 158, 4);

        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            data = DataRead(0xC0086);
            D_801099B0_boardresult2[i]->unk_0C[9] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(D_801099B0_boardresult2[i]->unk_0A, 9, D_801099B0_boardresult2[i]->unk_0C[9],
                              GwPlayer[kakusiMasuItemHis[i]].coin % 10);
            HuSprPriSet(D_801099B0_boardresult2[i]->unk_0A, 9, 90);
            HuSprAttrSet(D_801099B0_boardresult2[i]->unk_0A, 9, 0x4000);
            HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, 9, 174, 4);
        }
    }

    for (j = 0; j < 4; j++) {
        HuSprPosSet(D_801099B0_boardresult2[j]->unk_0A, 0, 111, j * 40 + 69);
    }

    D_801099C0_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130046);
    D_801099C0_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099C0_boardresult2->unk_0A, 0, D_801099C0_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099C0_boardresult2->unk_0A, 0, 90);
    HuSprAttrSet(D_801099C0_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099C0_boardresult2->unk_0A, 0, 160, 33);

    D_801099C4_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130062);
    D_801099C4_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099C4_boardresult2->unk_0A, 0, D_801099C4_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099C4_boardresult2->unk_0A, 0, 89);
    HuSprAttrSet(D_801099C4_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099C4_boardresult2->unk_0A, 0, 55, 41);
}

void func_80106924_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099A4_boardresult2);
    func_800F4584_name_81(D_801099A8_boardresult2);

    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099B0_boardresult2[i]);
    }

    func_800F4584_name_81(D_801099C0_boardresult2);
    func_800F4584_name_81(D_801099C4_boardresult2);
}

void func_801069A4_boardresult2(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOff(D_801099A4_boardresult2->unk_0A, j);
    }
    HuSprDispOff(D_801099A8_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(D_801099B0_boardresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOff(D_801099C0_boardresult2->unk_0A, 0);
    HuSprDispOff(D_801099C4_boardresult2->unk_0A, 0);
}

void func_80106A9C_boardresult2(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOn(D_801099A4_boardresult2->unk_0A, j);
    }
    HuSprDispOn(D_801099A8_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(D_801099B0_boardresult2[i]->unk_0A, j);
        }
    }

    HuSprDispOn(D_801099C0_boardresult2->unk_0A, 0);
    HuSprDispOn(D_801099C4_boardresult2->unk_0A, 0);
}

s32 func_80106B94_boardresult2(s32 category) {
    s32 max;
    s32 mask = 0;
    s32 i;

    switch (category) {
        case 0:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].star) {
                    max = GwPlayer[kakusiMasuItemHis[i]].star;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].star == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 1:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].coin) {
                    max = GwPlayer[kakusiMasuItemHis[i]].coin;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].coin == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 2:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].gamePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].gamePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].gamePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 3:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].coinPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].coinPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].coinPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 4:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 5:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 6:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 7:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 8:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 9:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 10:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 11:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 12:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
    }

    if (mask == 0xF) {
        return 0;
    }
    return mask;
}

void func_801074B4_boardresult2(void) {
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

    for (i = 0; i < 13; i++) {
        HuSprDispOff(D_801099EC_boardresult2->unk_0A, i);
    }

    for (i = D_801097B0_boardresult2, row = 0; i < D_801097B0_boardresult2 + 4; i++, row++) {
        HuSprDispOn(D_801099EC_boardresult2->unk_0A, i);
        HuSprPosSet(D_801099EC_boardresult2->unk_0A, i, row * 44 + 145, 52);
    }

    for (i = 0; i < 64; i++) {
        HuSprDispOff(D_801099F0_boardresult2->unk_0A, i);
    }

    for (i = D_801097B0_boardresult2, row = 0; i < D_801097B0_boardresult2 + 4; i++, row++) {
        for (j = 0; j < 4; j++) {
            player = MBDGetPlayerStruct(kakusiMasuItemHis[j]);
            digits = 1;
            mask = func_80106B94_boardresult2(i);
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
                    value = player->stats.prize.bluePrize;
                    digits = 2;
                    break;
                case 5:
                    value = player->stats.prize.redPrize;
                    digits = 2;
                    break;
                case 6:
                    value = player->stats.prize.hatenaPrize;
                    digits = 2;
                    break;
                case 7:
                    value = player->stats.prize.eventPrize;
                    digits = 2;
                    break;
                case 8:
                    value = player->stats.prize.kupaPrize;
                    digits = 2;
                    break;
                case 9:
                    value = player->stats.prize.battlePrize;
                    digits = 2;
                    break;
                case 10:
                    value = player->stats.prize.itemPrize;
                    digits = 2;
                    break;
                case 11:
                    value = player->stats.prize.bankPrize;
                    digits = 2;
                    break;
                case 12:
                    value = player->stats.prize.gamblePrize;
                    digits = 2;
                    break;
            }
            sprintf((char *)buf, "%4d", value);

            for (k = 0; k < 4; k++) {
                if (buf[k] == ' ') {
                    HuSprDispOff(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k);
                    continue;
                }
                if (mask & (1 << j)) {
                    HuSprGrpMemberSet(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k,
                                      D_801099F0_boardresult2->unk_0C[1], 0);
                } else {
                    HuSprGrpMemberSet(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k,
                                      D_801099F0_boardresult2->unk_0C[0], 0);
                }
                HuSprDispOn(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k);
                HuSprPosSet(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k,
                            row * 44 + (s16)(k * 10 + 145) + offsets[digits], j * 22 + 73);
                HuSprBankSet(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k, buf[k] - '0', 0);
                func_800550F4_main(D_801099F0_boardresult2->unk_0A, row * 16 + j * 4 + k, 1);
            }
        }
    }

    HuSprPosSet(D_801099F4_boardresult2->unk_0A, 0, D_801097B4_boardresult2 * 44 + 146, 96);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098B4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098C4_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098DC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_801098FC_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010991C_boardresult2);

INCLUDE_RODATA("asm/nonmatchings/overlays/boardresult2/3CFC80", D_8010992C_boardresult2);

void func_80107964_boardresult2(void) {
    BoardResult2Files4 rankFiles = D_801098B4_boardresult2;
    BoardResult2BoardFiles boardFiles = D_801098C4_boardresult2;
    BoardResult2Portraits nameFiles = D_801098DC_boardresult2;
    BoardResult2Portraits faceFiles = D_801098FC_boardresult2;
    BoardResult2Files4 lengthFiles = D_8010991C_boardresult2;
    BoardResult2StatFiles statFiles = D_8010992C_boardresult2;
    void *data;
    s32 i;

    D_801099CC_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(boardFiles.files[GwSystem.current_board_index]);
    D_801099CC_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099CC_boardresult2->unk_0A, 0, D_801099CC_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099CC_boardresult2->unk_0A, 0, 110);
    HuSprAttrSet(D_801099CC_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099CC_boardresult2->unk_0A, 0, 74, 39);

    D_801099D0_boardresult2 = func_800F4528_name_81(2, 0);
    data = DataRead(0x13004B);
    D_801099D0_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099D0_boardresult2->unk_0A, 0, D_801099D0_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099D0_boardresult2->unk_0A, 0, 100);
    HuSprAttrSet(D_801099D0_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099D0_boardresult2->unk_0A, 0, 210, 28);

    if (GwSystem.playMode & 4) {
        data = DataRead(0x13007C);
    } else {
        data = DataRead(lengthFiles.files[GwSystem.current_game_length]);
    }
    D_801099D0_boardresult2->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099D0_boardresult2->unk_0A, 1, D_801099D0_boardresult2->unk_0C[1], 0);
    HuSprPriSet(D_801099D0_boardresult2->unk_0A, 1, 99);
    HuSprAttrSet(D_801099D0_boardresult2->unk_0A, 1, 0x4000);
    HuSprPosSet(D_801099D0_boardresult2->unk_0A, 1, 210, 28);

    D_801099D4_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x13004C);
    D_801099D4_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099D4_boardresult2->unk_0A, 0, D_801099D4_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099D4_boardresult2->unk_0A, 0, 99);
    HuSprAttrSet(D_801099D4_boardresult2->unk_0A, 0, 0x4000);
    HuSprPosSet(D_801099D4_boardresult2->unk_0A, 0, 218, 51);

    for (i = 0; i < 4; i++) {
        D_801099D8_boardresult2[i] = func_800F4528_name_81(10, 2);
        data = DataRead(rankFiles.files[i]);
        D_801099D8_boardresult2[i]->unk_0C[1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099D8_boardresult2[i]->unk_0A, 1, D_801099D8_boardresult2[i]->unk_0C[1], 0);
        HuSprPriSet(D_801099D8_boardresult2[i]->unk_0A, 1, 98);
        HuSprAttrSet(D_801099D8_boardresult2[i]->unk_0A, 1, 0x4000);
        HuSprPosSet(D_801099D8_boardresult2[i]->unk_0A, 1, 172, 0);

        data = DataRead(nameFiles.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        D_801099D8_boardresult2[i]->unk_0C[2] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099D8_boardresult2[i]->unk_0A, 2, D_801099D8_boardresult2[i]->unk_0C[2], 0);
        HuSprPriSet(D_801099D8_boardresult2[i]->unk_0A, 2, 97);
        HuSprAttrSet(D_801099D8_boardresult2[i]->unk_0A, 2, 0x4000);
        HuSprPosSet(D_801099D8_boardresult2[i]->unk_0A, 2, 36, 1);

        data = DataRead(faceFiles.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        D_801099D8_boardresult2[i]->unk_0C[3] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099D8_boardresult2[i]->unk_0A, 3, D_801099D8_boardresult2[i]->unk_0C[3], 0);
        HuSprPriSet(D_801099D8_boardresult2[i]->unk_0A, 3, 96);
        HuSprAttrSet(D_801099D8_boardresult2[i]->unk_0A, 3, 0x4000);
        HuSprPosSet(D_801099D8_boardresult2[i]->unk_0A, 3, 77, 1);
    }

    for (i = 0; i < 4; i++) {
        HuSprPosSet(D_801099D8_boardresult2[i]->unk_0A, 0, 0, i * 22 + 73);
    }

    D_801099E8_boardresult2 = func_800F4528_name_81(2, 0);
    for (i = 0; i < 2; i++) {
        data = DataRead(0x13002E);
        D_801099E8_boardresult2->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099E8_boardresult2->unk_0A, i, D_801099E8_boardresult2->unk_0C[i], 0);
        HuSprPriSet(D_801099E8_boardresult2->unk_0A, i, 90);
        HuSprAttrSet(D_801099E8_boardresult2->unk_0A, i, 0x4000);
        HuSprPosSet(D_801099E8_boardresult2->unk_0A, i, i * 154 + 133, 161);
    }
    HuSprAttrSet(D_801099E8_boardresult2->unk_0A, 0, 1);

    D_801099EC_boardresult2 = func_800F4528_name_81(13, 0);
    for (i = 0; i < 13; i++) {
        data = DataRead(statFiles.files[i]);
        D_801099EC_boardresult2->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_801099EC_boardresult2->unk_0A, i, D_801099EC_boardresult2->unk_0C[i], 0);
        HuSprPriSet(D_801099EC_boardresult2->unk_0A, i, 80);
        HuSprAttrSet(D_801099EC_boardresult2->unk_0A, i, 0xC000);
    }

    D_801099F0_boardresult2 = func_800F4528_name_81(64, 0);
    data = DataRead(0x130077);
    D_801099F0_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x130078);
    D_801099F0_boardresult2->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 64; i++) {
        HuSprGrpMemberSet(D_801099F0_boardresult2->unk_0A, i, D_801099F0_boardresult2->unk_0C[0], 0);
        HuSprPriSet(D_801099F0_boardresult2->unk_0A, i, 70);
        HuSprAttrSet(D_801099F0_boardresult2->unk_0A, i, 0xC000);
    }

    D_801099F4_boardresult2 = func_800F4528_name_81(1, 0);
    data = DataRead(0x130076);
    D_801099F4_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(D_801099F4_boardresult2->unk_0A, 0, D_801099F4_boardresult2->unk_0C[0], 0);
    HuSprPriSet(D_801099F4_boardresult2->unk_0A, 0, 60);
    HuSprAttrSet(D_801099F4_boardresult2->unk_0A, 0, 0x4000);

    D_801099C8_boardresult2 = func_800E4B64_name_81(0, 8);
    func_800E4EAC_name_81(D_801099C8_boardresult2, 105, 8);
    HuVecCopyXYZ(&D_801099C8_boardresult2->obj->scale, 0.1f, 0.1f, 0.1f);
    HuWinScaleSet(D_801099C8_boardresult2->win_id, 1.0f, 1.0f);
    func_8005B63C_main(D_801099C8_boardresult2->win_id, 0x4000, 0x4000);
    HuWinMesPalSet(D_801099C8_boardresult2->win_id, 2, 255, 96, 96);
    HuWinMesPalSet(D_801099C8_boardresult2->win_id, 4, 96, 255, 64);
    HuWinMesPalSet(D_801099C8_boardresult2->win_id, 6, 64, 255, 255);
    func_800E4EAC_name_81(D_801099C8_boardresult2, 113, 8);

    D_80109A38_boardresult2[0] =
        func_80105A8C_boardresult2(D_801099C8_boardresult2->obj->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    D_80109A38_boardresult2[1] = func_80105C68_boardresult2(0xA007F);
    D_80109A38_boardresult2[2] = func_80105C68_boardresult2(0xA0080);
    D_80109A38_boardresult2[3] = func_80105C68_boardresult2(0xA0081);
    D_80109A38_boardresult2[4] = func_80105C68_boardresult2(0xA0082);
    D_80109A38_boardresult2[5] = func_80105C68_boardresult2(0xA0083);
    D_80109A38_boardresult2[6] = func_80105C68_boardresult2(0xA0084);
    func_80105B98_boardresult2(D_801099C8_boardresult2->obj->omObj1->model[0], D_80109A38_boardresult2[0]);
}

void func_80108548_boardresult2(void) {
    s32 i;

    func_800F4584_name_81(D_801099CC_boardresult2);
    func_800F4584_name_81(D_801099D0_boardresult2);
    func_800F4584_name_81(D_801099D4_boardresult2);

    for (i = 0; i < 4; i++) {
        func_800F4584_name_81(D_801099D8_boardresult2[i]);
    }

    func_800F4584_name_81(D_801099E8_boardresult2);
    func_800F4584_name_81(D_801099EC_boardresult2);
    func_800F4584_name_81(D_801099F0_boardresult2);
    func_800F4584_name_81(D_801099F4_boardresult2);
    func_800E4E64_name_81(D_801099C8_boardresult2);
}

void func_801085F8_boardresult2(void) {
    s32 i;
    s32 j;

    HuSprDispOff(D_801099CC_boardresult2->unk_0A, 0);
    HuSprDispOff(D_801099D0_boardresult2->unk_0A, 0);
    HuSprDispOff(D_801099D0_boardresult2->unk_0A, 1);
    HuSprDispOff(D_801099D4_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(D_801099D8_boardresult2[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOff(D_801099E8_boardresult2->unk_0A, j);
    }

    for (j = 0; j < 13; j++) {
        HuSprDispOff(D_801099EC_boardresult2->unk_0A, j);
    }

    for (j = 0; j < 64; j++) {
        HuSprDispOff(D_801099F0_boardresult2->unk_0A, j);
    }

    HuSprDispOff(D_801099F4_boardresult2->unk_0A, 0);
    func_800D8F0C_name_81(D_801099C8_boardresult2->obj);
    HuWinDispOff(D_801099C8_boardresult2->win_id);
}

void func_8010879C_boardresult2(void) {
    s32 i;
    s32 j;

    HuSprDispOn(D_801099CC_boardresult2->unk_0A, 0);
    HuSprDispOn(D_801099D0_boardresult2->unk_0A, 0);
    HuSprDispOn(D_801099D0_boardresult2->unk_0A, 1);
    HuSprDispOn(D_801099D4_boardresult2->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(D_801099D8_boardresult2[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOn(D_801099E8_boardresult2->unk_0A, j);
    }

    func_801074B4_boardresult2();
    HuSprDispOn(D_801099F4_boardresult2->unk_0A, 0);
    func_800D8E88_name_81(D_801099C8_boardresult2->obj);
    HuWinDispOn(D_801099C8_boardresult2->win_id);

    if (D_801097B0_boardresult2 == 0 && D_801097B4_boardresult2 == 0) {
        HuSprDispOff(D_801099E8_boardresult2->unk_0A, 0);
    }
    if (D_801097B0_boardresult2 == 9 && D_801097B4_boardresult2 == 3) {
        HuSprDispOff(D_801099E8_boardresult2->unk_0A, 1);
    }
}

void func_80108958_boardresult2(void) {
    s32 messages[] = {
        0x1900,
        0x1901,
        0x1902,
        0x1903,
        0x1904,
        0x1905,
        0x1906,
        0x1907,
        0x1908,
        0x1909,
        0x190A,
        0x190B,
        0x190C,
    };

    HuWinHomeClear(D_801099C8_boardresult2->win_id);
    HuWinMesSet(D_801099C8_boardresult2->win_id, messages[D_801097B0_boardresult2 + D_801097B4_boardresult2], -1, -1);
    func_80105B98_boardresult2(D_801099C8_boardresult2->obj->omObj1->model[0],
                               D_80109A38_boardresult2[D_801099F8_boardresult2[D_801097B0_boardresult2 + D_801097B4_boardresult2]]);
}

void func_80108A48_boardresult2(void) {
    s32 index = *(s32 *)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scale;

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(D_801099B0_boardresult2[index]->unk_0A, 0, 111,
                    (index * 40 + 69) + sindf(angle) * -(index * 40 + 109));
        HuPrcVSleep();
    }

    scale = -8.0f;
    HuAudFXPlay(0x178);
    for (angle = 0.0f; angle <= 1260.0f; angle += 50.0f) {
        HuSprPosSet(D_801099B0_boardresult2[index]->unk_0A, 0, 111, (index * 40 + 69) + sindf(angle) * scale);
        scale += 0.3174603f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }

    HuSprPosSet(D_801099B0_boardresult2[index]->unk_0A, 0, 111, index * 40 + 69);
    omDelPrcObj(NULL);
}

void func_80108C70_boardresult2(void) {
    f32 angle;
    f32 scale;

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(D_801099C0_boardresult2->unk_0A, 0, 160, sindf(angle) * -73.0f + 33.0f);
        HuPrcVSleep();
    }

    scale = -4.0f;
    HuAudFXPlay(0x179);
    for (angle = 0.0f; angle <= 720.0f; angle += 50.0f) {
        HuSprPosSet(D_801099C0_boardresult2->unk_0A, 0, 160, sindf(angle) * scale + 33.0f);
        scale += 0.2777778f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }

    HuSprPosSet(D_801099C0_boardresult2->unk_0A, 0, 160, 33);
    omDelPrcObj(NULL);
}

void func_80108E1C_boardresult2(void) {
    Process *process;
    void *data;
    f32 angle;
    f32 scale;
    s32 prevPage;
    s32 prevRow;
    s32 timer;
    s32 allCpu;
    s32 showingDetails;
    s32 leftWindow = 0;
    s32 rightWindow = 0;
    s32 i;

    D_801099A0_boardresult2 = func_800F4528_name_81(6, 0);
    data = DataRead(0x13002F);
    D_801099A0_boardresult2->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 6; i++) {
        HuSprGrpMemberSet(D_801099A0_boardresult2->unk_0A, i, D_801099A0_boardresult2->unk_0C[0], 0);
        HuSprPriSet(D_801099A0_boardresult2->unk_0A, i, 200);
        HuSprAttrSet(D_801099A0_boardresult2->unk_0A, i, 0x4000);
        HuSprPosSet(D_801099A0_boardresult2->unk_0A, i, (i / 2) * 128 + 64, (i & 1) * 128 + 64);
    }

    func_80105CB0_boardresult2();
    showingDetails = 0;
    func_80107964_boardresult2();
    func_80108958_boardresult2();
    func_801085F8_boardresult2();
    func_80106A9C_boardresult2();

    for (i = 0; i < 4; i++) {
        HuSprPosSet(D_801099B0_boardresult2[i]->unk_0A, 0, 111, -40);
    }
    HuSprPosSet(D_801099C0_boardresult2->unk_0A, 0, 160, -40);
    HuSprPosSet(D_801099C4_boardresult2->unk_0A, 0, 55, -40);

    WipeCreateIn(2, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    for (i = 3; i >= 0; i--) {
        process = omAddPrcObj(func_80108A48_boardresult2, 0x1000, 0, 0x40);
        process->user_data = HuMemMemoryAlloc(process->heap, 0x20);
        *(s32 *)process->user_data = i;
        HuPrcSleep(15);
    }
    omAddPrcObj(func_80108C70_boardresult2, 0x1000, 0, 0);
    HuPrcSleep(20);

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(D_801099C4_boardresult2->unk_0A, 0, 55, sindf(angle) * -73.0f + 41.0f);
        HuPrcVSleep();
    }

    scale = -4.0f;
    HuAudFXPlay(0x17A);
    for (angle = 0.0f; angle <= 720.0f; angle += 50.0f) {
        HuSprPosSet(D_801099C4_boardresult2->unk_0A, 0, 55, sindf(angle) * scale + 41.0f);
        scale += 0.2777778f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }
    HuSprPosSet(D_801099C4_boardresult2->unk_0A, 0, 55, 41);

    allCpu = 0;
    for (i = 0; i < 4; i++) {
        if (!func_800F37B8_name_81(i)) {
            break;
        }
    }
    if (i == 4) {
        allCpu = 1;
    }

    timer = 60;
    while (1) {
        if (allCpu) {
            if (--timer == 0) {
                break;
            }
            if (leftWindow == 0) {
                leftWindow = func_800E172C_name_81(0x16, 60, 207, 1);
            }
            if (rightWindow == 0) {
                rightWindow = func_800E172C_name_81(0x17, 200, 207, 1);
            }
        } else {
            for (i = 0; i < 4; i++) {
                if (func_800F37B8_name_81(i)) {
                    continue;
                }
                if (!showingDetails) {
                    if (leftWindow == 0) {
                        leftWindow = func_800E172C_name_81(0x16, 60, 207, 1);
                    }
                    if (rightWindow == 0) {
                        rightWindow = func_800E172C_name_81(0x17, 200, 207, 1);
                    }
                    if (D_800C9520_main[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 1;
                        func_801069A4_boardresult2();
                        func_8010879C_boardresult2();
                        if (leftWindow != 0) {
                            func_800E1854_minigame(leftWindow);
                            leftWindow = 0;
                        }
                        if (rightWindow != 0) {
                            func_800E1854_minigame(rightWindow);
                            rightWindow = 0;
                        }
                    } else if (D_800C9520_main[GwPlayer[i].pad] & A_BUTTON) {
                        goto exit;
                    }
                } else {
                    prevRow = D_801097B4_boardresult2;
                    prevPage = D_801097B0_boardresult2;
                    if (D_800C9520_main[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 0;
                        func_801085F8_boardresult2();
                        func_80106A9C_boardresult2();
                    } else if (D_800D0590_main[GwPlayer[i].pad] & R_JPAD) {
                        if (++D_801097B4_boardresult2 >= 4) {
                            D_801097B4_boardresult2 = 3;
                            if (++D_801097B0_boardresult2 >= 10) {
                                D_801097B0_boardresult2 = 9;
                            }
                        }
                    } else if (D_800D0590_main[GwPlayer[i].pad] & L_JPAD) {
                        if (--D_801097B4_boardresult2 < 0) {
                            D_801097B4_boardresult2 = 0;
                            if (--D_801097B0_boardresult2 < 0) {
                                D_801097B0_boardresult2 = 0;
                            }
                        }
                    }
                    if (D_801097B4_boardresult2 != prevRow || D_801097B0_boardresult2 != prevPage) {
                        func_80108958_boardresult2();
                        func_801074B4_boardresult2();
                    }
                }
            }

            if (showingDetails == 1) {
                if (D_801097B0_boardresult2 == 0 && D_801097B4_boardresult2 == 0) {
                    HuSprAttrSet(D_801099E8_boardresult2->unk_0A, 0, 0x8000);
                } else {
                    HuSprAttrReset(D_801099E8_boardresult2->unk_0A, 0, 0x8000);
                }
                if (D_801097B0_boardresult2 == 9 && D_801097B4_boardresult2 == 3) {
                    HuSprAttrSet(D_801099E8_boardresult2->unk_0A, 1, 0x8000);
                } else {
                    HuSprAttrReset(D_801099E8_boardresult2->unk_0A, 1, 0x8000);
                }
            }
        }
        HuPrcVSleep();
    }

exit:
    if (leftWindow != 0) {
        func_800E1854_minigame(leftWindow);
    }
    if (rightWindow != 0) {
        func_800E1854_minigame(rightWindow);
    }
    if (!(GwSystem.playMode & 4) || (GwPlayer[kakusiMasuItemHis[0]].stat & PLAYER_IS_CPU)) {
        HuAudSeqFadeOut(60);
    }
    WipeCreateOut(0, 20);
    HuPrcSleep(20);
    func_80106924_boardresult2();
    func_80108548_boardresult2();
    func_800F4584_name_81(D_801099A0_boardresult2);
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_801096AC_boardresult2(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_8010979C_boardresult2();
        func_80109740_boardresult2();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void func_801096F0_boardresult2(omObjData *arg0) {
    if (D_800D530C_main != 0) {
        arg0->func = func_801096AC_boardresult2;
    }
}

void func_80109714_boardresult2(void) {
    func_800D7EB8_name_81();
    func_800F3F4C_name_81();
    func_800F4300_name_81();
}

void func_80109740_boardresult2(void) {
    func_800F4030_name_81();
    func_800D7F0C_name_81();
    func_800F4314_name_81();
}

void func_8010976C_boardresult2(void) {
    Hu3DCamInit(2);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_8010979C_boardresult2(void) {
}
