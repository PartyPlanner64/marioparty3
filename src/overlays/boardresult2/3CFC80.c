#include "common.h"
#include "../ovl_81_name/ovl_81.h"

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80105CB0_boardresult2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80107964_boardresult2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult2/3CFC80", func_80108E1C_boardresult2);

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
