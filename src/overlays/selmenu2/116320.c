#include "common.h"
#include "gcc/string.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct UnkSelmenu2Space {
    u8 available;
    u8 player_groups;
    u8 unk_02;
    u8 unk_03;
    u32 unk_04;
    f32 unk_08;
    char *unk_0C;
} UnkSelmenu2Space; // sizeof 0x10

typedef struct UnkSelmenu2SpaceGroups {
    u8 group[4];
    u8 unk_04[4];
    s16 unk_08[4];
} UnkSelmenu2SpaceGroups; // sizeof 0x10

typedef struct UnkSelmenu2Sound {
    s16 fx;
    u8 unk_02;
    s8 vol;
} UnkSelmenu2Sound; // sizeof 0x4

extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s16 D_80109B00_selmenu2;
extern s16 D_80109B02_selmenu2;
extern UnkSelmenu2Space D_80108BE0_selmenu2[];
extern UnkSelmenu2SpaceGroups D_801090D0_selmenu2[];
extern s16 D_80109B08_selmenu2[];
extern s16 D_80109B18_selmenu2;
extern s16 D_80109B1A_selmenu2;
extern s16 D_80109B1C_selmenu2;
extern GW_PLAYER D_80109B20_selmenu2[];
extern UnkSelmenu2Sound D_801092F0_selmenu2[];
extern u16 D_80109304_selmenu2[2][2]; // text colors
extern u8 D_801093B0_selmenu2;
extern s32 D_801093C0_selmenu2;
extern s32 D_801093C4_selmenu2;
extern s32 D_801093C8_selmenu2;
extern UnkSelmenu2Space D_8010930C_selmenu2[];
extern char *D_8010936C_selmenu2[];
extern char *D_80109374_selmenu2[];
extern char *D_80109384_selmenu2[];
extern char D_80109A98_selmenu2[];
extern char D_80109AA4_selmenu2[];
extern char D_80109A8C_selmenu2[];
extern s16 D_800D1F28_main;
extern u8 D_80109C38_selmenu2[];
extern u8 D_80109C3C_selmenu2[];
extern s16 D_80109C78_selmenu2[];
extern f32 D_80109CE8_selmenu2[];
extern s16 D_80109C48_selmenu2[];
extern s16 D_80109C58_selmenu2[];
extern s16 D_80109C68_selmenu2[];
extern s8 D_80109C80_selmenu2[];
extern s8 D_80109C84_selmenu2[];
extern u8 D_80109C88_selmenu2;
extern s16 D_80109C8A_selmenu2;
extern s16 D_80109C8C_selmenu2;
extern u16 D_80109C8E_selmenu2;
extern s16 D_80109C90_selmenu2;
extern s16 D_80109C98_selmenu2[];
extern u8 D_80109CF8_selmenu2[];
extern u16 D_80109CFC_selmenu2[];
extern u16 D_80109D04_selmenu2[];
extern u16 D_80109D0C_selmenu2[];

void func_80105F74_selmenu2(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void func_8010600C_selmenu2(omObjData *obj);
void func_801067B4_selmenu2(omObjData *obj);
void func_80106A54_selmenu2(omObjData *obj);
void func_80106D94_selmenu2(omObjData *obj);
void func_801078CC_selmenu2(omObjData *obj);
void func_80107D94_selmenu2(omObjData *obj);
void func_80107DA4_selmenu2(omObjData *obj);
void func_80108718_selmenu2(u16 index);
void func_80108764_selmenu2(s16 dir);
void func_80108910_selmenu2(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void func_801087E0_selmenu2(s16 dir);
void func_80108990_selmenu2(void);
void func_80108A04_selmenu2(void);
void func_80108A6C_selmenu2(void);
void func_80108B38_selmenu2(void);

void func_801059A0_selmenu2(void) {
    omObjData *obj;
    GW_PLAYER *player;
    u16 sprite;
    s32 i;

    D_80109C88_selmenu2 = 0;
    _SetFlag(0x12);
    _ClearFlag(0xD);
    GwSystem.show_minigame_explanations = 0;
    if (D_800A12B0_main < 71) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].coin += GwPlayer[i].gameCoin;
            if (GwPlayer[i].coin >= 1000) {
                GwPlayer[i].coin = 999;
            }
            if (GwPlayer[i].coin < 0) {
                GwPlayer[i].coin = 0;
            }
            GwPlayer[i].gameCoin = 0;
        }
    }
    omInitObjMan(50, 0);
    func_80105F74_selmenu2(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0x60, 0x60, 0x10);
    Hu3DGLightDirSet(1, 100.0f, -100.0f, 100.0f);
    omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omAddObj(0, 0, 0, -1, func_8010600C_selmenu2);
    omAddObj(1, 0, 0, -1, func_801067B4_selmenu2);
    omMakeGroup(0, 32);
    obj = omAddObj(10, 1, 80, -1, NULL);
    for (i = 0; i < 8; i++) {
        D_80109C48_selmenu2[i] = func_8000B108_main(D_800A178C_main[i][0] | D_800A1790_main[i][0], 0x69D);
        Hu3DData[D_80109C48_selmenu2[i]].motAttr |= 2;
        func_8000B460_main(obj, 0, func_80017BB8_main(i, 0));
        D_80109C58_selmenu2[i] = obj->motion[0];
        func_8000B460_main(obj, 1, func_80017BB8_main(i, 0x2F));
        D_80109C68_selmenu2[i] = obj->motion[1];
    }
    omDelObj(obj);
    for (i = 0; i < 4; i++) {
        D_80109C84_selmenu2[i] = 0;
        D_80109C80_selmenu2[i] = 0;
    }
    D_80109C8A_selmenu2 = func_8000B838_main(0x10020);
    func_8000B880_main(D_80109C8A_selmenu2, 0.3f, 0.3f, 0.3f);
    for (i = 0; i < 35; i++) {
        sprite = espEntry(D_80109C8A_selmenu2, i % 6, 1);
        espDispOn(sprite);
        espPriSet(sprite, 0xFFFF);
        espAttrSet(sprite, 0x4000);
        espTPLvlSet(sprite, 0xFF);
        espPosSet(sprite, (i % 7) * 48, (i / 7) * 48);
    }
    D_80109C8C_selmenu2 = func_8000B838_main(10);
    D_80109C8E_selmenu2 = espEntry(D_80109C8C_selmenu2, 0, 1);
    espDispOn(D_80109C8E_selmenu2);
    espPosSet(D_80109C8E_selmenu2, 0x80, 0x80);
    espScaleSet(D_80109C8E_selmenu2, 0.25f, 0.25f);
    for (i = 0; i < 40; i++) {
        D_80109C98_selmenu2[i] = -1;
    }
    D_80109C90_selmenu2 = func_8000B838_main(12);
    for (i = 0; i < 4; i++) {
        D_80109D04_selmenu2[i] = 0;
        D_80109D0C_selmenu2[i] = 0;
        D_80109CFC_selmenu2[i] = 0;
    }
    WipeCreateIn(0xFF, 16);
    HuAudSeqPlay(rand8() % 9);
    for (i = 0; i < 4; i++) {
        player = &GwPlayer[i];
        player->gamePrize = -1;
        player->coinPrize = -1;
        player->stats.prize.hatenaPrize = 0;
        player->stats.prize.redPrize = 0;
        player->stats.prize.bluePrize = 0;
        player->stats.prize.eventPrize = 0;
        player->stats.prize.kupaPrize = 0;
        player->stats.prize.battlePrize = 0;
        player->stats.prize.itemPrize = 0;
        player->stats.prize.bankPrize = 0;
        player->star = 5;
    }
    GwSystem.bank_coins = 0;
}

void func_80105F74_selmenu2(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    func_8000B5F0_main(1);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
}

void func_8010600C_selmenu2(omObjData *obj);
void func_80106770_selmenu2(omObjData *obj);
void func_80106A10_selmenu2(omObjData *obj);
void func_80106DEC_selmenu2(omObjData *obj);
void func_80107924_selmenu2(omObjData *obj);
void func_80107DEC_selmenu2(omObjData *obj);
void func_80107DFC_selmenu2(omObjData *obj);
void func_801087C8_selmenu2(u16 index);
void func_80108814_selmenu2(s16 dir);
void func_801089C0_selmenu2(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4);
void func_80108890_selmenu2(s16 dir);
void func_80108A40_selmenu2(void);

void func_8010600C_selmenu2(omObjData *obj) {
    s8 stickX;
    s8 stickY;
    s32 i;

    for (i = 0; i < 4; i++) {
        D_80109CF8_selmenu2[i] = 0;
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (WipeStatGet() == 1) {
            continue;
        }
        stickX = D_800CBB6E_main[i];
        stickY = D_800D20A1_main[i];
        if (D_800D5558_main[i] & (U_JPAD | U_CBUTTONS)) {
            D_80109CF8_selmenu2[i] |= 1;
        }
        if (D_800D5558_main[i] & (D_JPAD | D_CBUTTONS)) {
            D_80109CF8_selmenu2[i] |= 2;
        }
        if (D_800D5558_main[i] & (L_JPAD | L_CBUTTONS)) {
            D_80109CF8_selmenu2[i] |= 4;
        }
        if (D_800D5558_main[i] & (R_JPAD | R_CBUTTONS)) {
            D_80109CF8_selmenu2[i] |= 8;
        }
        if (stickY < -10 && ABS(D_80109C84_selmenu2[i]) < 10) {
            D_80109CF8_selmenu2[i] |= 2;
        }
        if (stickY > 10 && ABS(D_80109C84_selmenu2[i]) < 10) {
            D_80109CF8_selmenu2[i] |= 1;
        }
        if (stickX < -10 && ABS(D_80109C80_selmenu2[i]) < 10) {
            D_80109CF8_selmenu2[i] |= 4;
        }
        if (stickX > 10 && ABS(D_80109C80_selmenu2[i]) < 10) {
            D_80109CF8_selmenu2[i] |= 8;
        }
        D_80109C80_selmenu2[i] = stickX;
        D_80109C84_selmenu2[i] = stickY;
        if (D_800D5558_main[i] & Z_TRIG) {
            D_80109CF8_selmenu2[i] |= 0x40;
        }
        if ((D_800CDA7C_main[i] & (U_JPAD | U_CBUTTONS)) || stickY > 10) {
            if (D_80109CFC_selmenu2[i] & 1) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 1) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 1;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 1;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (D_JPAD | D_CBUTTONS)) || stickY < -10) {
            if (D_80109CFC_selmenu2[i] & 2) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 2) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 2;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 2;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (L_JPAD | L_CBUTTONS)) || stickX < -10) {
            if (D_80109CFC_selmenu2[i] & 4) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 4) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 4;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 4;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else if ((D_800CDA7C_main[i] & (R_JPAD | R_CBUTTONS)) || stickX > 10) {
            if (D_80109CFC_selmenu2[i] & 8) {
                D_80109D04_selmenu2[i]++;
                if (D_80109D04_selmenu2[i] >= 16) {
                    D_80109D04_selmenu2[i] = 15;
                }
            } else {
                D_80109D04_selmenu2[i] = 0;
            }
            if (D_80109CFC_selmenu2[i] != 8) {
                D_80109D0C_selmenu2[i] = 0;
                D_80109D04_selmenu2[i] = 0;
            }
            D_80109CFC_selmenu2[i] = 8;
            if (D_80109D04_selmenu2[i] == 15) {
                if (D_80109D0C_selmenu2[i] == 0) {
                    D_80109CF8_selmenu2[i] |= 8;
                    D_80109D0C_selmenu2[i] = 2;
                } else {
                    D_80109D0C_selmenu2[i]--;
                }
            }
        } else {
            D_80109D04_selmenu2[i] = 0;
        }
        if (D_800D5558_main[i] & A_BUTTON) {
            D_80109CF8_selmenu2[i] |= 0x10;
        }
        if (D_800D5558_main[i] & B_BUTTON) {
            D_80109CF8_selmenu2[i] |= 0x20;
        }
        if (D_800D5558_main[i] & START_BUTTON) {
            D_80109CF8_selmenu2[i] |= 0x80;
        }
        if ((D_800CDA7C_main[i] & (L_TRIG | R_TRIG)) == (L_TRIG | R_TRIG)) {
            omOvlReturnEx(0);
            return;
        }
    }
}

void func_801067B4_selmenu2(omObjData *obj) {
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        D_80109C3C_selmenu2[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].chr = i;
        D_80109C78_selmenu2[i] = i;
        D_80109C38_selmenu2[i] = 0;
        D_80109CE8_selmenu2[i] = 0.0f;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            D_80109C3C_selmenu2[i] = 1;
        }
    }
    D_80109B00_selmenu2 = -1;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 10; j++) {
            if (D_80108BE0_selmenu2[i * 10 + j].available != 1) {
                break;
            }
        }
        if (j == 10) {
            D_80109B08_selmenu2[i] = -1;
        } else {
            D_80109B08_selmenu2[i] = j;
        }
    }
    func_801087E0_selmenu2(1);
    if (D_800A12B0_main != 999) {
        for (i = 0; i < 80; i++) {
            if (D_80108BE0_selmenu2[i].unk_04 == D_800A12B0_main) {
                D_80109B00_selmenu2 = i / 10;
                D_80109B02_selmenu2 = i % 10;
                D_80109B08_selmenu2[D_80109B00_selmenu2] = D_80109B02_selmenu2;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        D_80109B20_selmenu2[i] = GwPlayer[i];
    }
    func_80108990_selmenu2();
    obj->func = func_80106A54_selmenu2;
}

void func_80106A54_selmenu2(omObjData *obj) {
    UnkSelmenu2Space *space;
    u16 *color;
    s32 x;
    s32 i;

    rand8();
    space = &D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10];
    for (i = 0; i < 10; i++, space++) {
        sprintf(D_800D5218_main, space->unk_0C);
        x = strlen(D_800D5218_main);
        x = 0x40;
        if (D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + i].available == 0) {
            color = D_80109304_selmenu2[0];
        } else {
            color = D_80109304_selmenu2[1];
        }
        if (D_80109B02_selmenu2 == i) {
            func_80108910_selmenu2(x, (i + 10) * 9, D_800D5218_main, color[1], color[0]);
        } else {
            func_80108910_selmenu2(x, (i + 10) * 9, D_800D5218_main, color[0], 0);
        }
    }
    sprintf(D_800D5218_main, D_80109A8C_selmenu2, D_80109B00_selmenu2 + 1, 8);
    func_80108910_selmenu2(0x80, 0x40, D_800D5218_main, 15, 7);
    espPosSet(D_80109C8E_selmenu2, 0x3C, (D_80109B02_selmenu2 + 11) * 9 - 1);
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if ((D_80109CF8_selmenu2[i] & 0x90) && D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + D_80109B02_selmenu2].available == 0) {
            if (D_801093B0_selmenu2 == 0) {
                omAddObj(2, 0, 0, -1, func_80107D94_selmenu2);
                D_801093B0_selmenu2 = 1;
                espDispOff(D_80109C8E_selmenu2);
                obj->func = func_801078CC_selmenu2;
                func_80108718_selmenu2(1);
            }
        } else if (D_80109CF8_selmenu2[i] & 1) {
            func_80108764_selmenu2(-1);
            func_80108990_selmenu2();
            func_80108718_selmenu2(0);
        } else if (D_80109CF8_selmenu2[i] & 2) {
            func_80108764_selmenu2(1);
            func_80108990_selmenu2();
            func_80108718_selmenu2(0);
        } else if (D_80109CF8_selmenu2[i] & 4) {
            func_801087E0_selmenu2(-1);
            func_80108990_selmenu2();
            func_80108718_selmenu2(4);
        } else if (D_80109CF8_selmenu2[i] & 8) {
            func_801087E0_selmenu2(1);
            func_80108990_selmenu2();
            func_80108718_selmenu2(4);
        } else if (D_80109CF8_selmenu2[i] & 0x40) {
            D_80109B18_selmenu2 = 0;
            D_80109B1A_selmenu2 = 0;
            D_80109B1C_selmenu2 = 0;
            obj->func = func_80106D94_selmenu2;
        }
    }
}

void func_80106D94_selmenu2(omObjData *obj) {
    UnkSelmenu2Space *space;
    u16 *color;
    s32 x;
    s32 y;
    s32 row;
    s32 line;
    s16 sel;
    s16 cursorCol;
    s16 cursorRow;
    s32 i;
    s32 j;

    rand8();
    sprintf(D_800D5218_main, D_80109A98_selmenu2);
    func_80108910_selmenu2(0x70, 0x40, D_800D5218_main, 15, 7);
    for (i = 0; i < 5; i++) {
        space = D_8010930C_selmenu2;
        if (i == 4) {
            sprintf(D_800D5218_main, D_80109AA4_selmenu2, GwSystem.current_board_index);
            color = D_80109304_selmenu2[0];
            if (D_80109B1A_selmenu2 == i) {
                func_80108910_selmenu2(0x80, 0x50, D_800D5218_main, color[1], color[0]);
            } else {
                func_80108910_selmenu2(0x80, 0x50, D_800D5218_main, color[0], 0);
            }
            continue;
        }
        for (j = 0; j < 6; j++, space++) {
            x = (i % 2) * 144 + 40;
            row = (i / 2) * 7;
            line = j + 12;
            y = (row + line) * 8;
            switch (j) {
                case 0:
                    sprintf(D_800D5218_main, space->unk_0C, i);
                    break;
                case 1:
                    sprintf(D_800D5218_main, space->unk_0C, D_80109B20_selmenu2[i].pad,
                            D_8010936C_selmenu2[D_80109B20_selmenu2[i].stat & 1]);
                    break;
                case 2:
                    sprintf(D_800D5218_main, space->unk_0C, D_80109B20_selmenu2[i].group);
                    break;
                case 3:
                    sprintf(D_800D5218_main, space->unk_0C, D_80109374_selmenu2[D_80109B20_selmenu2[i].cpu_difficulty]);
                    break;
                case 4:
                    sprintf(D_800D5218_main, space->unk_0C, D_80109B20_selmenu2[i].coin);
                    break;
                case 5:
                    sprintf(D_800D5218_main, space->unk_0C, D_80109B20_selmenu2[i].pad);
                    break;
            }
            switch (D_80109B1C_selmenu2) {
                case 0:
                    if (j == 0) {
                        color = D_80109304_selmenu2[0];
                        if (i == D_80109B1A_selmenu2) {
                            func_80108910_selmenu2(x, y, D_800D5218_main, color[1], color[0]);
                        } else {
                            func_80108910_selmenu2(x, y, D_800D5218_main, color[0], 0);
                        }
                    } else {
                        func_80108910_selmenu2(x, y, D_800D5218_main, D_80109304_selmenu2[1][0], 0);
                    }
                    break;
                case 1:
                    if (i == D_80109B1A_selmenu2) {
                        color = D_80109304_selmenu2[0];
                        if (j == D_80109B18_selmenu2) {
                            func_80108910_selmenu2(x, y, D_800D5218_main, color[1], color[0]);
                        } else {
                            func_80108910_selmenu2(x, y, D_800D5218_main, color[0], 0);
                        }
                    } else {
                        func_80108910_selmenu2(x, y, D_800D5218_main, D_80109304_selmenu2[1][0], 0);
                    }
                    break;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        if (D_80109CF8_selmenu2[i] & 0x40) {
            obj->func = func_80106A54_selmenu2;
            return;
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            continue;
        }
        switch (D_80109B1C_selmenu2) {
            case 0:
                if (D_80109B1A_selmenu2 < 2 && (D_80109CF8_selmenu2[i] & 1)) {
                    D_80109B1A_selmenu2 = 4;
                } else if (D_80109B1A_selmenu2 == 4 && (D_80109CF8_selmenu2[i] & 2)) {
                    D_80109B1A_selmenu2 = 0;
                } else if (D_80109B1A_selmenu2 == 4 && (D_80109CF8_selmenu2[i] & 4)) {
                    if (--GwSystem.current_board_index < 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (D_80109B1A_selmenu2 == 4 && (D_80109CF8_selmenu2[i] & 8)) {
                    if (++GwSystem.current_board_index > 0) {
                        GwSystem.current_board_index = 0;
                    }
                } else if (D_80109B1A_selmenu2 != 4) {
                    if (D_80109CF8_selmenu2[i] & 0xC) {
                        D_80109B1A_selmenu2 ^= 1;
                    } else if (D_80109CF8_selmenu2[i] & 3) {
                        D_80109B1A_selmenu2 ^= 2;
                    }
                    if (D_80109CF8_selmenu2[i] & 0x20) {
                        obj->func = func_80106A54_selmenu2;
                        return;
                    }
                    if (D_80109CF8_selmenu2[i] & 0x10) {
                        D_80109B1C_selmenu2 = 1;
                        return;
                    }
                    if (D_80109CF8_selmenu2[i] & 0x80) {
                        func_80108A6C_selmenu2();
                        func_80108B38_selmenu2();
                    }
                }
                break;
            case 1:
                if (D_80109CF8_selmenu2[i] & 1) {
                    if (--D_80109B18_selmenu2 < 0) {
                        D_80109B18_selmenu2 = 5;
                    }
                } else if (D_80109CF8_selmenu2[i] & 2) {
                    if (++D_80109B18_selmenu2 >= 6) {
                        D_80109B18_selmenu2 = 0;
                    }
                }
                if (D_80109CF8_selmenu2[i] & 8) {
                    switch (D_80109B18_selmenu2) {
                        case 0:
                            break;
                        case 1:
                            D_80109B20_selmenu2[D_80109B1A_selmenu2].stat ^= 1;
                            break;
                        case 2:
                            if (++D_80109B20_selmenu2[D_80109B1A_selmenu2].group >= 4) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].group = 0;
                            }
                            break;
                        case 3:
                            if (++D_80109B20_selmenu2[D_80109B1A_selmenu2].cpu_difficulty >= 4) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].cpu_difficulty = 0;
                            }
                            break;
                        case 4:
                            if (++D_80109B20_selmenu2[D_80109B1A_selmenu2].coin >= 1000) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].coin = 0;
                            }
                            break;
                        case 5:
                            if (++D_80109B20_selmenu2[D_80109B1A_selmenu2].pad == 4) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].pad = 0;
                            }
                            break;
                    }
                } else if (D_80109CF8_selmenu2[i] & 4) {
                    switch (D_80109B18_selmenu2) {
                        case 0:
                            break;
                        case 1:
                            D_80109B20_selmenu2[D_80109B1A_selmenu2].stat ^= 1;
                            break;
                        case 2:
                            if (D_80109B20_selmenu2[D_80109B1A_selmenu2].group == 0) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].group = 3;
                            } else {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].group--;
                            }
                            break;
                        case 3:
                            if (D_80109B20_selmenu2[D_80109B1A_selmenu2].cpu_difficulty == 0) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].cpu_difficulty = 3;
                            } else {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].cpu_difficulty--;
                            }
                            break;
                        case 4:
                            if (--D_80109B20_selmenu2[D_80109B1A_selmenu2].coin < 0) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].coin = 999;
                            }
                            break;
                        case 5:
                            if (--D_80109B20_selmenu2[D_80109B1A_selmenu2].pad == 0xFF) {
                                D_80109B20_selmenu2[D_80109B1A_selmenu2].pad = 3;
                            }
                            break;
                    }
                } else if (D_80109CF8_selmenu2[i] & 0x30) {
                    D_80109B1C_selmenu2 = 0;
                    D_80109B18_selmenu2 = 0;
                    return;
                } else if (D_80109CF8_selmenu2[i] & 0x80) {
                    switch (D_80109B18_selmenu2) {
                        case 2:
                            func_80108A6C_selmenu2();
                            break;
                        case 5:
                            func_80108B38_selmenu2();
                            break;
                    }
                }
                break;
        }
    }
    sel = D_80109B1A_selmenu2;
    if (sel != 4) {
        cursorCol = sel % 2;
        cursorRow = sel / 2;
        x = cursorCol * 144;
        x += 40;
        y = cursorRow * 7;
        line = D_80109B18_selmenu2 + 12;
        y += line;
        y++;
        y *= 8;
    } else {
        x = 0x80;
        y = 0x58;
    }
    espPosSet(D_80109C8E_selmenu2, x - 4, y);
}

void func_801078CC_selmenu2(omObjData *obj) {
    u32 x;
    s32 y;
    s32 shadowOfs = 12;
    // The comparison is folded away, but the join it leaves behind keeps textOfs in a register below.
    s32 textOfs = MIN(6, shadowOfs);
    s32 i;

    rand8();
    sprintf(D_800D5218_main, D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + D_80109B02_selmenu2].unk_0C);
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    y = (D_80109B02_selmenu2 + 10) * 9;
    if (y - D_801093C0_selmenu2 > 48) {
        if (--D_801093C8_selmenu2 == 0) {
            D_80109C98_selmenu2[D_801093C4_selmenu2] = espEntry(D_80109C90_selmenu2, 0, 1);
            espAttrSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0x4000);
            espPriSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0x8000);
            espScaleSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0.75f, 0.75f);
            espSpeedSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 8.0f);
            espPosSet(D_80109C98_selmenu2[D_801093C4_selmenu2], x, y - (u16)D_801093C0_selmenu2 + textOfs + 8);
            espColorSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0xFF, 0xFF, 0xBE);
            D_801093C4_selmenu2++;
            D_80109C98_selmenu2[D_801093C4_selmenu2] = espEntry(D_80109C90_selmenu2, 0, 1);
            espAttrSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0x4000);
            espPriSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0x8000);
            espScaleSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0.75f, 0.75f);
            espSpeedSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 8.0f);
            espPosSet(D_80109C98_selmenu2[D_801093C4_selmenu2],
                      x + strlen(D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + D_80109B02_selmenu2].unk_0C) * 8,
                      y - (u16)D_801093C0_selmenu2 + textOfs + 8);
            espColorSet(D_80109C98_selmenu2[D_801093C4_selmenu2], 0xFF, 0xFF, 0xBE);
            D_801093C4_selmenu2++;
            D_801093C8_selmenu2 = 4;
        }
        D_801093C0_selmenu2 += 4;
        if (y < y - D_801093C0_selmenu2 + shadowOfs) {
            shadowOfs = (y - D_801093C0_selmenu2 + shadowOfs) - y;
        }
        if (y < y - D_801093C0_selmenu2 + textOfs) {
            textOfs = (y - D_801093C0_selmenu2 + textOfs) - y;
        }
        fontcolor = 9;
        print8(x, y - (u16)D_801093C0_selmenu2 + shadowOfs, D_800D5218_main);
        fontcolor = 13;
        print8(x, y - (u16)D_801093C0_selmenu2 + textOfs, D_800D5218_main);
    }
    for (i = 0; i < D_801093C4_selmenu2; i++) {
        if (D_80109C98_selmenu2[i] != -1 && (func_8000BE1C_main(D_80109C98_selmenu2[i]) & 6)) {
            espKill(D_80109C98_selmenu2[i]);
            D_80109C98_selmenu2[i] = -1;
        }
    }
    x = (320 - strlen(D_800D5218_main) * 8) / 2;
    fontcolor = 7;
    print8(x + 1, y + 1 - (u16)D_801093C0_selmenu2, D_800D5218_main);
    fontcolor = 15;
    print8(x, y - (u16)D_801093C0_selmenu2, D_800D5218_main);
}

void func_80107D94_selmenu2(omObjData *obj) {
    obj->func = func_80107DA4_selmenu2;
}

void func_80107DA4_selmenu2(omObjData *obj) {
    u8 freeChars[8];
    u16 pads[4];
    s32 ready = 0;
    s32 chr;
    u16 color;
    u16 textColor;
    u8 pick;
    s32 i;
    s32 j;
    u8 missing;
    u8 count;
    u8 index;

    if (D_80109C88_selmenu2 == 1) {
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_80108A04_selmenu2();
            GwSystem.minigame_index = D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + D_80109B02_selmenu2].unk_02;
            GwSystem.current_player_index = 0;
            D_800A12B0_main = D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + D_80109B02_selmenu2].unk_04;
            if (D_800A12B0_main >= 71) {
                omOvlCallEx(D_800A12B0_main, 0, 0x84);
            } else if (D_800A6D40_main[GwSystem.minigame_index - 1].minigameType != 6) {
                omOvlCallEx(0x70, 0, 0x82);
            } else {
                omOvlCallEx(D_800A6D40_main[GwSystem.minigame_index - 1].overlay, 0, 0x94);
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (D_80109C38_selmenu2[i] == 1) {
            ready++;
        }
    }
    missing = 0;
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            pads[missing++] = i;
        }
    }
    if (ready == gNumOfControllers) {
        if (ready < 4) {
            for (index = 0; index < missing; index++) {
                count = 0;
                for (i = 0; i < 8; i++) {
                    freeChars[i] = 0;
                }
                for (i = 0; i < 8; i++) {
                    if (D_80109C3C_selmenu2[i] == 0) {
                        freeChars[count++] = i;
                    }
                }
                if (count == 1) {
                    GwPlayer[pads[index]].chr = freeChars[0];
                    D_80109C3C_selmenu2[freeChars[0]] = 1;
                } else {
                    pick = rand8() % count;
                    GwPlayer[pads[index]].chr = freeChars[pick];
                    D_80109C3C_selmenu2[freeChars[pick]] = 1;
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreateOut(0, 20);
        D_80109C88_selmenu2 = 1;
        D_800D1F28_main = 0;
        for (i = 0; i < 4; i++) {
            if (CheckControllerRead(i) && (D_800CDA7C_main[i] & L_TRIG)) {
                D_800D1F28_main = 1;
                break;
            }
        }
        return;
    }
    for (i = 0; i < 4; i++) {
        if (CheckControllerRead(i) && (D_800D5558_main[i] & START_BUTTON)) {
            for (j = 0; j < 4; j++) {
                if (CheckControllerRead(j)) {
                    D_80109CF8_selmenu2[j] |= 0x10;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (!CheckControllerRead(i)) {
            sprintf(D_800D5218_main, "------");
            func_80108910_selmenu2(i * 56 + 56, 144, D_800D5218_main, 15, 7);
            continue;
        }
        func_8001C258_main(D_80109C48_selmenu2[GwPlayer[i].chr], 4, 0);
        Hu3DModelPosSet(D_80109C48_selmenu2[GwPlayer[i].chr], i * 420 - 650.0f - 60.0f + i * 40, -120.0f, 0.0f);
        Hu3DModelScaleSet(D_80109C48_selmenu2[GwPlayer[i].chr], 2.0f, 2.0f, 2.0f);
        if (D_80109C38_selmenu2[i] == 1) {
            D_80109CE8_selmenu2[i] = 0.0f;
        }
        Hu3DModelRotSet(D_80109C48_selmenu2[GwPlayer[i].chr], 0.0f, D_80109CE8_selmenu2[i], 0.0f);
        D_80109CE8_selmenu2[i] += 1.0f;
        if (D_80109CE8_selmenu2[i] >= 360.0f) {
            D_80109CE8_selmenu2[i] -= 360.0f;
        }
        color = (D_80109C38_selmenu2[i] != 0) ? 15 : 12;
        textColor = color;
        sprintf(D_800D5218_main, D_80109384_selmenu2[GwPlayer[i].chr]);
        func_80108910_selmenu2(i * 56 + 50 + i * 4, 144, D_800D5218_main, textColor, color - 8);
        if ((D_80109CF8_selmenu2[i] & 0x10) && D_80109C38_selmenu2[i] == 0) {
            D_80109C38_selmenu2[i] = 1;
            func_8001C5B4_main(D_80109C48_selmenu2[GwPlayer[i].chr], D_80109C68_selmenu2[GwPlayer[i].chr]);
            func_8001C814_main(D_80109C48_selmenu2[GwPlayer[i].chr], 1, 0);
            func_8001C814_main(D_80109C48_selmenu2[GwPlayer[i].chr], 2, 2);
            func_80108718_selmenu2(2);
        } else if ((D_80109CF8_selmenu2[i] & 0x20) && D_80109C38_selmenu2[i] == 1) {
            D_80109C38_selmenu2[i] = 0;
            func_8001C5B4_main(D_80109C48_selmenu2[GwPlayer[i].chr], D_80109C58_selmenu2[GwPlayer[i].chr]);
            func_8001C814_main(D_80109C48_selmenu2[GwPlayer[i].chr], 1, 0);
            func_8001C814_main(D_80109C48_selmenu2[GwPlayer[i].chr], 2, 2);
            func_80108718_selmenu2(3);
        }
        if (D_80109C38_selmenu2[i] == 0) {
            if (D_80109CF8_selmenu2[i] & 4) {
                chr = GwPlayer[i].chr - 1;
                func_80108718_selmenu2(0);
                while (TRUE) {
                    if (chr < 0) {
                        chr = 7;
                    }
                    if (D_80109C3C_selmenu2[chr] == 0) {
                        break;
                    }
                    chr--;
                }
                D_80109C3C_selmenu2[GwPlayer[i].chr] = 0;
                func_8001C258_main(D_80109C48_selmenu2[GwPlayer[i].chr], 4, 4);
                GwPlayer[i].chr = chr;
                D_80109C3C_selmenu2[GwPlayer[i].chr] = 1;
                D_80109CE8_selmenu2[i] = 0.0f;
            } else if (D_80109CF8_selmenu2[i] & 8) {
                chr = GwPlayer[i].chr + 1;
                func_80108718_selmenu2(0);
                while (TRUE) {
                    if (chr >= 8) {
                        chr = 0;
                    }
                    if (D_80109C3C_selmenu2[chr] == 0) {
                        break;
                    }
                    chr++;
                }
                D_80109C3C_selmenu2[GwPlayer[i].chr] = 0;
                func_8001C258_main(D_80109C48_selmenu2[GwPlayer[i].chr], 4, 4);
                GwPlayer[i].chr = chr;
                D_80109C3C_selmenu2[GwPlayer[i].chr] = 1;
                D_80109CE8_selmenu2[i] = 0.0f;
            }
        }
    }
}

void func_80108718_selmenu2(u16 index) {
    HuAudFXVolSet(HuAudFXPlay(D_801092F0_selmenu2[index].fx), D_801092F0_selmenu2[index].vol);
}

void func_80108764_selmenu2(s16 dir) {
    s16 index = D_80109B02_selmenu2;

    do {
        index += dir;
        if (index >= 10) {
            index = 0;
        } else if (index < 0) {
            index = 9;
        }
    } while (D_80108BE0_selmenu2[D_80109B00_selmenu2 * 10 + index].available == 1);
    D_80109B02_selmenu2 = index;
}

void func_801087E0_selmenu2(s16 dir) {
    u16 found = FALSE;
    s16 prevPage;
    s16 page;
    s32 i;

    prevPage = page = D_80109B00_selmenu2;
    do {
        page += dir;
        if (page >= 8) {
            page = 0;
        } else if (page < 0) {
            page = 7;
        }
        for (i = 0; i < 10; i++) {
            if (D_80108BE0_selmenu2[page * 10 + i].available == 0) {
                found = TRUE;
                break;
            }
        }
    } while (!found);
    D_80109B00_selmenu2 = page;
    if (prevPage == -1) {
        D_80109B02_selmenu2 = -1;
        func_80108764_selmenu2(1);
        D_80109B08_selmenu2[D_80109B00_selmenu2] = D_80109B02_selmenu2;
    } else {
        D_80109B08_selmenu2[prevPage] = D_80109B02_selmenu2;
        D_80109B02_selmenu2 = D_80109B08_selmenu2[D_80109B00_selmenu2];
    }
}

void func_80108910_selmenu2(u16 arg0, u16 arg1, char *arg2, u16 arg3, u16 arg4) {
    fontcolor = arg4;
    print8((arg0 + 1), (arg1 + 1), arg2);
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

void func_80108990_selmenu2(void) {
    s16 x = D_80109B00_selmenu2;
    s16 y = D_80109B02_selmenu2;
    UnkSelmenu2SpaceGroups *groups = &D_801090D0_selmenu2[D_80108BE0_selmenu2[x * 10 + y].player_groups];
    GW_PLAYER *player = D_80109B20_selmenu2;

    player->group = groups->group[0];
    player++;
    player->group = groups->group[1];
    player++;
    player->group = groups->group[2];
    player++;
    player->group = groups->group[3];
}

void func_80108A04_selmenu2(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        GW_PLAYER *src = &D_80109B20_selmenu2[i];
        GW_PLAYER *dst = &GwPlayer[i];

        dst->stat = src->stat;
        dst->group = src->group;
        dst->pad = src->pad;
        dst->cpu_difficulty = src->cpu_difficulty;
        dst->coin = src->coin;
    }
}

void func_80108A6C_selmenu2(void) {
    u8 groups[4];
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        groups[i] = D_80109B20_selmenu2[i].group;
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_80109B20_selmenu2[i].group = groups[r];
    }
}

void func_80108B38_selmenu2(void) {
    u8 used[4];
    s32 i;
    s32 r;

    for (i = 0; i < 4; i++) {
        used[i] = FALSE;
    }
    for (i = 0; i < 4; i++) {
        do {
            r = rand8() & 3;
        } while (used[r] == TRUE);
        used[r] = TRUE;
        D_80109B20_selmenu2[i].pad = r;
    }
}
