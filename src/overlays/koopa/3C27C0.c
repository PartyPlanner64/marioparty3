#include "common.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F2910.h"

typedef struct UnkBowser {
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
} UnkBowser; // sizeof 0x8

typedef struct UnkBowser2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
} UnkBowser2; // sizeof 0x24

void func_800E4A94_shared_board(void);
void func_800E4B18_shared_board(void);
void func_80108360_koopa(s32);
void func_800F5828_shared_board(s32);
void func_800F591C_shared_board(s32);
void func_80108D2C_koopa(void);
void func_80109220_koopa(omObjData *);
void func_8010926C_koopa(void);
void func_801092D4_koopa(void);
void func_801091C4_koopa(omObjData *);
void func_80109320_koopa(void);
void func_801092A0_koopa(void);
void func_80107724_koopa(void);
void func_80107190_koopa(void);
void func_80105AD8_koopa(omObjData *);
void func_80106FC8_koopa(void);
void func_80106A54_koopa(void);
void func_80106AB8_koopa(void);
s32 func_80107658_koopa(s32, s32);
s32 func_80107A9C_koopa(void);
s32 func_80107DDC_koopa(void);
s32 func_801085E4_koopa(void);
s32 func_80108664_koopa(void);
s32 func_801086E4_koopa(void);
s32 func_80108A2C_koopa(void);
s32 func_80108BB0_koopa(void);
s32 func_8010778C_koopa(void);
s32 func_801078CC_koopa(void);

extern s16 D_801094F6_koopa;
extern Object *D_801094F8_koopa;
extern char D_80109508_koopa[];

extern u8 D_801094F0_koopa;
extern s32 D_801094F4_koopa;
extern s32 D_801094FC_koopa;
extern u32 D_800D2094_main;
extern s32 D_8010956C_koopa;
extern omObjData *D_80109550_koopa;
extern s16 D_80109518_koopa[5][5];
extern s16 D_80109554_koopa[2];
extern s16 D_80109558_koopa;
extern s16 D_8010955A_koopa;
extern s16 D_8010955C_koopa;
extern s16 D_8010955E_koopa;
extern s16 D_80109560_koopa;
extern s16 D_80109562_koopa;
extern s16 D_80109564_koopa;
extern s32 D_80109568_koopa;
extern s32 D_80109500_koopa;
extern s32 D_80109504_koopa;
extern s16 D_8010951A_koopa[];
extern u8 D_8010954A_koopa[5];

//.data
void *D_80109350_koopa = 0;

s32 D_80109354_koopa[] = {
    0x00004200,
    0x00004201,
    0x00004202,
    0x00004203,
    0x00004204,
    0x00004205,
    0x00004206,
    0x00004207,
    0x00004208,
    0x00004209,
};

UnkBowser D_8010937C_koopa[] = {
    { 64, -206, 200, 20 },
    { 64, -186, 200, 20 },
    { 64, -166, 200, 20 },
    { 64, -146, 200, 20 },
    { 64, -126, 200, 20 }
};

u8 D_801093A4_koopa = 94;
s8 D_801093A8_koopa[] = { 1, 0, 9, 15, 11, 8, 13, 0 };
Vec D_801093B0_koopa = { 0.0f, 0.0f, 2250.0f };
Vec D_801093BC_koopa = { 0.0f, 0.0f, -1000.0f };

UnkBowser2 D_801093C8_koopa = {
    0x00000008, 0x000A0035, 0x000A0032, 0x000A0038,
    0x000A0040, 0x000A0043, 0x000A0041, 0x000A0042, 0x000A0044
};

s32 (*D_801093EC_koopa[])(void) = {
    func_8010778C_koopa,
    func_801078CC_koopa,
    func_80107A9C_koopa,
    func_80107DDC_koopa,
    func_801085E4_koopa,
    func_80108664_koopa,
    func_801086E4_koopa,
    func_80108A2C_koopa,
    func_80108BB0_koopa,
    func_80108BB0_koopa
};

u32 D_80109414_koopa = 0;
s16 D_80109418_koopa[] = { 90, 89, 87, 71, 70, 84, 85, 86, 62, 61, 58, 59, 60, -1 };
u16 D_80109434_koopa[2][3][4] = {
    { { 20, 20, 10, 10 },
      { 20, 20, 15, 15 },
      { 30, 30, 20, 20 } },
    { { 10, 10, 10, 10 },
      { 20, 20, 20, 20 },
      { 30, 30, 30, 30 } }
};

// unused
s16 D_80109464_koopa[][2] = {
    { 20, 20 },
    { 30, 30 },
    { 30, 30 },
    { 40, 40 },
    { 30, 40 },
    { 50, 50 },
    { 0, 0 }
};

//.text
void func_801059A0_koopa(void) {
    s32 i;

    D_801094F0_koopa = GwSystem.current_board_index;
    D_801094F4_koopa = GwSystem.playerIndexVisitingBowser;
    omInitObjMan(0x32, 0x32);
    func_801092D4_koopa();
    func_8010926C_koopa();
    func_800D95C4_shared_board(1000.0f);
    HuWinInit();
    func_800F453C_shared_board();
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusPosSet(i, 0x1E, -0x32);
    }
    omAddPrcObj(func_80108D2C_koopa, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, func_80109220_koopa);
    func_800EA60C_shared_board();
    MBMasuCreate(0x13, 0x23A);
    func_8004A208_main();
}

void func_80105A8C_koopa(void) {
    if (D_800D2094_main >= (D_80109414_koopa + 4)) {
        HuAudFXPlay(0x104);
        D_80109414_koopa = D_800D2094_main;
    }
}

void func_80105AD8_koopa(omObjData *obj) {
    s16 *window;
    s32 i;
    s32 index = 0;
    u16 buttons;

    switch (obj->work[0]) {
        case 0:
            obj->trans.y += 16.0f;
            for (i = 0; i < 5; i++) {
                window = D_80109518_koopa[i];
                HuWinPosSet(window[0], window[1] + window[3] / 2, (window[2] + window[4] / 2) + (s16)obj->trans.y);
            }
            if (D_8010955E_koopa != -1) {
                HuSprPosSet(D_8010955E_koopa, 0, D_8010951A_koopa[0] + 100, (s32)obj->trans.y + D_8010951A_koopa[1] + 50);
            }
            if (D_8010955A_koopa != -1) {
                HuSprPosSet(D_8010955A_koopa, 0, D_8010951A_koopa[0] + 100, (s32)obj->trans.y + D_8010951A_koopa[1] - 30);
            }
            for (i = 0; i < 2; i++) {
                if (D_80109554_koopa[i] != -1) {
                    HuSprPosSet(D_80109554_koopa[i], 0, D_8010951A_koopa[0] + i * 200, (s32)obj->trans.y + D_8010951A_koopa[1] - 40);
                }
            }
            if (obj->trans.y >= 288.0f) {
                func_80105A8C_koopa();
                D_80109350_koopa = func_800E210C_shared_board(23, 200, 1);
                obj->work[0] = 1;
                obj->scale.x = 0.5f;
                obj->scale.z = -1.0f;
                obj->scale.y = 0;
                obj->work[1] = 0;
                obj->work[3] = 0;
                obj->trans.z = 0;
                obj->rot.y = D_80109500_koopa;
                if (D_80109504_koopa != 0) {
                    for (i = 0; i < 5; i++) {
                        if (D_8010954A_koopa[i] >= 8) {
                            index = i - (s32)obj->rot.y;
                            break;
                        }
                    }
                    if (index < 0) {
                        index += 5;
                    } else {
                        index %= 5;
                    }
                    obj->work[2] = index;
                } else {
                    obj->work[2] = 0;
                }
                i = MBRand(100.0f);
                if (i < 60) {
                    obj->mdlcnt = 20;
                } else if (i < 90) {
                    obj->mdlcnt = 14;
                } else {
                    obj->mdlcnt = 8;
                }
                obj->mtncnt = 0;
                func_80106FC8_koopa();
            }
            break;
        case 1:
            if (obj->trans.z == 0) {
                if (GwPlayer[D_801094F4_koopa].stat & 1) {
                    obj->trans.z = 1.0f;
                } else {
                    buttons = D_800C9520_main[GwPlayer[D_801094F4_koopa].pad];
                    if (buttons & A_BUTTON) {
                        obj->trans.z = 1.0f;
                    }
                }
                if (obj->trans.z == 1.0f && D_80109350_koopa != 0) {
                    MBHelpWinKill(D_80109350_koopa);
                    D_80109350_koopa = 0;
                }
                if (D_80109504_koopa == 0) {
                    for (i = 0;; i++) {
                        index = i + obj->work[1];
                        if (index < 0) {
                            index += 5;
                        } else {
                            index %= 5;
                        }
                        if (D_8010954A_koopa[index] < 8) {
                            index -= (s32)obj->rot.y;
                            if (index < 0) {
                                index += 5;
                                break;
                            }
                            index %= 5;
                            break;
                        }
                    }
                    obj->work[2] = index;
                }
            }
            if (obj->mtncnt != 0) {
                obj->scale.x = obj->mdlcnt / 100.0f;
            }
            obj->scale.z += obj->scale.x;
            if (obj->scale.z >= 1.0f) {
                if (obj->work[3] != 0 && obj->scale.x <= 0.08f) {
                    obj->work[3]--;
                }
                obj->scale.z -= 1.0f;
                if (obj->scale.y == 0) {
                    obj->work[1] = (obj->work[1] + 1) % 5;
                } else {
                    obj->work[1]--;
                    if (obj->work[1] >= 128) {
                        obj->work[1] = 4;
                    }
                }
                func_80105A8C_koopa();
            }
            for (i = 0; i < 5; i++) {
                window = D_80109518_koopa[i];
                if (i == obj->work[1]) {
                    HuWinBGColSet(window[0], 0, 200, 0);
                    HuWinBGTPLvlSet(window[0], 256);
                    HuWinPriSet(window[0], 9000);
                } else {
                    HuWinBGColSet(window[0], 64, 64, 128);
                    HuWinBGTPLvlSet(window[0], 0);
                    HuWinPriSet(window[0], 10000);
                }
            }
            if (obj->trans.z != 0 && (obj->work[1] == obj->work[2] || obj->scale.x < 1.0f)) {
                if (obj->mtncnt == 0) {
                    obj->scale.x -= 0.01f;
                }
            }
            if (obj->scale.x <= 0.08f || obj->mtncnt != 0) {
                if (obj->mtncnt == 0) {
                    obj->scale.x = 0.08f;
                }
                if (obj->work[1] == obj->work[2] && obj->work[3] == 0 && obj->scale.z + obj->scale.x >= 1.0f) {
                    if ((obj->rot.y > 0 ? obj->rot.y : 0.0f - obj->rot.y) <= 0.5f) {
                        HuAudFXPlay(0x105);
                        switch (D_8010954A_koopa[obj->work[2]]) {
                            case 0:
                            case 2:
                            case 3:
                            case 8:
                            case 9:
                                MBPlayerVibrate(D_801094F6_koopa, 2);
                                break;
                            case 1:
                                MBPlayerVibrate(0, 2);
                                MBPlayerVibrate(1, 2);
                                MBPlayerVibrate(2, 2);
                                MBPlayerVibrate(3, 2);
                                break;
                            case 4:
                            case 5:
                                MBPlayerVibrate(0, 3);
                                MBPlayerVibrate(1, 3);
                                MBPlayerVibrate(2, 3);
                                MBPlayerVibrate(3, 3);
                                break;
                            case 6:
                                MBPlayerVibrate(0, 4);
                                MBPlayerVibrate(1, 4);
                                MBPlayerVibrate(2, 4);
                                MBPlayerVibrate(3, 4);
                                break;
                            case 7:
                                MBPlayerVibrate(0, 5);
                                MBPlayerVibrate(1, 5);
                                MBPlayerVibrate(2, 5);
                                MBPlayerVibrate(3, 5);
                                break;
                        }
                        obj->work[0] = 2;
                        obj->work[3] = 60;
                        HuWinHomeClear(D_80109518_koopa[obj->work[1]][0]);
                        if (D_8010954A_koopa[obj->work[1]] == 0) {
                            HuWinInsertMesSet(D_80109518_koopa[obj->work[1]][0], (u32)D_80109508_koopa, 0);
                            HuWinInsertMesSizeGet((u32)D_80109508_koopa, 0);
                        }
                        HuWinMesSet(D_80109518_koopa[obj->work[1]][0], D_80109354_koopa[D_8010954A_koopa[obj->work[1]]], HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(D_80109518_koopa[obj->work[1]][0], 1);
                        func_8005C154_main(D_80109518_koopa[obj->work[1]][0], 160, 160, 160);
                        HuWinBGColSet(D_80109518_koopa[obj->work[1]][0], 254, 255, 208);
                        HuWinMesSpeedSet(D_80109518_koopa[obj->work[1]][0], 0);
                    } else {
                        obj->mtncnt = 1;
                        if (obj->rot.y >= 0.5f) {
                            obj->rot.y -= 1.0f;
                            obj->work[2] = (obj->work[2] + 1) % 5;
                        } else {
                            obj->rot.y += 1.0f;
                            obj->scale.y = 1.0f;
                            obj->work[2]--;
                            if (obj->work[2] >= 128) {
                                obj->work[2] = 4;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (obj->work[3] == 0) {
                obj->work[0] = 4;
                func_80106A54_koopa();
            } else {
                obj->work[3]--;
                obj->rot.z += 1.0f;
                if (obj->rot.z >= 13.0f) {
                    obj->rot.z -= 13.0f;
                }
            }
            break;
        case 3:
            break;
        case 4:
            obj->trans.y -= 32.0f;
            for (i = 0; i < 5; i++) {
                window = D_80109518_koopa[i];
                HuWinPosSet(window[0], window[1] + window[3] / 2, (window[2] + window[4] / 2) + (s16)obj->trans.y);
            }
            if (D_8010955E_koopa != -1) {
                HuSprPosSet(D_8010955E_koopa, 0, D_8010951A_koopa[0] + 100, (s32)obj->trans.y + D_8010951A_koopa[1] + 50);
            }
            if (D_8010955A_koopa != -1) {
                HuSprPosSet(D_8010955A_koopa, 0, D_8010951A_koopa[0] + 100, (s32)obj->trans.y + D_8010951A_koopa[1] - 30);
            }
            for (i = 0; i < 2; i++) {
                if (D_80109554_koopa[i] != -1) {
                    HuSprPosSet(D_80109554_koopa[i], 0, D_8010951A_koopa[0] + i * 200, (s32)obj->trans.y + D_8010951A_koopa[1] - 40);
                }
            }
            if (obj->trans.y <= 0) {
                D_80109568_koopa = D_8010954A_koopa[obj->work[2]];
                func_80106AB8_koopa();
            }
            break;
    }
    if (D_80109562_koopa != -1) {
        for (i = 0;; i++) {
            if (obj->rot.z < D_801093A8_koopa[i * 2]) {
                break;
            }
        }
        HuSprPosSet(D_80109562_koopa, 0, D_801093A8_koopa[i * 2 + 1] + 50, D_801093A4_koopa + obj->work[1] * 20);
    }
}

s32 func_80106968_koopa(void) {
    return D_80109568_koopa;
}

s32 func_80106974_koopa(void) {
    return D_8010956C_koopa;
}

s32 func_80106980_koopa(void) {
    if (D_80109550_koopa == NULL) {
        return -1;
    }
    return D_80109550_koopa->work[0];
}

void func_8010699C_koopa(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80109518_koopa); i++) {
        D_80109518_koopa[i][0] = -1;
    }

    D_80109550_koopa = NULL;

    for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
        D_80109554_koopa[i] = -1;
    }

    D_80109558_koopa = -1;
    D_8010955C_koopa = -1;
    D_8010955A_koopa = -1;
    D_80109560_koopa = -1;
    D_8010955E_koopa = -1;
    D_80109564_koopa = -1;
    D_80109562_koopa = -1;
    D_80109568_koopa = -1;
    D_80109350_koopa = 0;
}

void func_80106A54_koopa(void) {
    if (D_80109562_koopa != -1) {
        HuSprGrpKill(D_80109562_koopa);
        D_80109562_koopa = -1;
    }
    if (D_80109564_koopa != -1) {
        HuSprAnimKill(D_80109564_koopa);
        D_80109564_koopa = -1;
    }
}

void func_80106AB8_koopa(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80109518_koopa); i++) {
        s16 *temp = D_80109518_koopa[i];
        if (temp[0] != -1) {
            HuWinKill(temp[0]);
            temp[0] = -1;
        }
    }

    if (D_80109350_koopa != 0) {
        MBHelpWinKill(D_80109350_koopa);
        D_80109350_koopa = 0;
    }

    if (D_80109550_koopa != NULL) {
        omDelObj(D_80109550_koopa);
        D_80109550_koopa = NULL;
    }

    if (D_8010955E_koopa != -1) {
        HuSprGrpKill(D_8010955E_koopa);
        D_8010955E_koopa = -1;
    }

    if (D_80109560_koopa != -1) {
        HuSprAnimKill(D_80109560_koopa);
        D_80109560_koopa = -1;
    }

    if (D_8010955A_koopa != -1) {
        HuSprGrpKill(D_8010955A_koopa);
        D_8010955A_koopa = -1;
    }

    if (D_8010955C_koopa != -1) {
        HuSprAnimKill(D_8010955C_koopa);
        D_8010955C_koopa = -1;
    }

    for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
        if (D_80109554_koopa[i] != -1) {
            HuSprGrpKill(D_80109554_koopa[i]);
            D_80109554_koopa[i] = -1;
        }
    }

    if (D_80109558_koopa != -1) {
        HuSprAnimKill(D_80109558_koopa);
        D_80109558_koopa = -1;
    }

    func_80106A54_koopa();
}

void func_80106C78_koopa(void) {
    s32 randVal;
    s32 var_v0_2;
    void *temp_v0;
    s32 i;

    if (D_8010955E_koopa == -1) {
        D_8010955E_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EB);
        D_80109560_koopa = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(D_8010955E_koopa, 0, D_80109560_koopa, 0);
        HuSprPriSet(D_8010955E_koopa, 0, 0x4770);
        HuSprAttrSet(D_8010955E_koopa, 0, 0x1000);
        HuSprPosSet(D_8010955E_koopa, 0, D_8010951A_koopa[0] + 0x64, D_8010951A_koopa[1] + 0x32);
        HuSprColorSet(D_8010955E_koopa, 0, 0, 0, 0);
        D_8010955A_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301E9);
        D_8010955C_koopa = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(D_8010955A_koopa, 0, D_8010955C_koopa, 0);
        HuSprPriSet(D_8010955A_koopa, 0, 0x4770);
        HuSprAttrSet(D_8010955A_koopa, 0, 0x1000);
        HuSprPosSet(D_8010955A_koopa, 0, D_8010951A_koopa[0] + 0x64, D_8010951A_koopa[1] - 0x1E);
        temp_v0 = DataRead(0x130260);
        D_80109558_koopa = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        randVal = MBRand(5.0f);
        for (i = 0; i < ARRAY_COUNT(D_80109554_koopa); i++) {
            D_80109554_koopa[i] = HuSprGrpCreate(1, 5);
            HuSprGrpMemberSet(D_80109554_koopa[i], 0, D_80109558_koopa, 1);
            HuSprPriSet(D_80109554_koopa[i], 0, 0x4770);
            HuSprAttrSet(D_80109554_koopa[i], 0, 0x1000);
            HuSprPosSet(D_80109554_koopa[i], 0, D_8010951A_koopa[0] + (i * 0xC8), (D_8010951A_koopa[1] - 0x28));
            if ((randVal == 0) && (D_80109504_koopa == 0)) {
                var_v0_2 = D_80109500_koopa;
                if (var_v0_2 == 0) {
                    HuSprColorSet(D_80109554_koopa[i], 0, 0, 0, 0xFF);
                } else {
                    if (var_v0_2 < 0) {
                        var_v0_2 = -var_v0_2;
                    }
                    if (var_v0_2 < 2) {
                        HuSprColorSet(D_80109554_koopa[i], 0, 0xFF, 0xFF, 0);
                    } else {
                        HuSprColorSet(D_80109554_koopa[i], 0, 0xFF, 0, 0);
                    }
                }
            } else {
                HuSprColorSet(D_80109554_koopa[i], 0, 0xFF, 0, 0);
            }
        }
    }
}

void func_80106FC8_koopa(void) {
    void *temp_v0;

    if (D_80109562_koopa == -1) {
        D_80109562_koopa = HuSprGrpCreate(1, 5);
        temp_v0 = DataRead(0x1301EA);
        D_80109564_koopa = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(D_80109562_koopa, 0, D_80109564_koopa, 0);
        HuSprPriSet(D_80109562_koopa, 0, 0x100);
        HuSprAttrSet(D_80109562_koopa, 0, 0x1000);
        HuSprPosSet(D_80109562_koopa, 0, 0x32, D_801093A4_koopa);
    }
}

s32 func_80107090_koopa(void) {
    s32 var_s3;
    GW_PLAYER *temp_s1;
    s32 i, j;

    if (GwSystem.current_board_index == CHILLY_WATERS) {
        for (var_s3 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
            temp_s1 = MBPlayerGet(i);
            for (j = 0; D_80109418_koopa[j] != -1; j++) {
                if (MBMasuLinkMasuIdGet(temp_s1->clink, temp_s1->cidx) == D_80109418_koopa[j]) {
                    var_s3++;
                    break;
                }
            }
        }
        if (var_s3 < 2) {
            return 0;
        } else {
            return 1;
        }
    }
    return 0;
}

const char D_801094C0_koopa[] = "%d";
const char D_801094C4_koopa[] = "";

void func_80107190_koopa(void) {
    u8 order[5];
    u8 events[5];
    s32 i;
    s32 randVal;
    s16 *window;
    UnkBowser *positions = D_8010937C_koopa;

    i = MBRand(256.0f);
    if (i < 70) {
        D_80109500_koopa = 0;
    } else if (i < 115) {
        D_80109500_koopa = 1;
    } else if (i < 160) {
        D_80109500_koopa = 2;
    } else if (i < 185) {
        D_80109500_koopa = 3;
    } else if (i < 200) {
        D_80109500_koopa = 4;
    } else if (i < 225) {
        D_80109500_koopa = -1;
    } else if (i < 240) {
        D_80109500_koopa = -2;
    } else {
        D_80109500_koopa = -3;
    }
    if (MBRand(70.0f) == 0) {
        D_80109504_koopa = 1;
    } else {
        D_80109504_koopa = 0;
    }
    for (i = 0; i < 5; i++) {
        window = D_80109518_koopa[i];
        window[1] = positions[i].unk_00;
        window[2] = positions[i].unk_02;
        window[3] = positions[i].unk_04;
        window[4] = positions[i].unk_06;
        window[0] = HuWinCreate(window[1] + window[3] / 2, window[2] + window[4] / 2, window[3], window[4], 0, 4);
        func_80060144_main(window[0]);
        HuWinCenterPosSet(window[0], window[3] / 2, window[4] / 2);
        HuWinBGTPLvlSet(window[0], 0);
        switch (i) {
            case 0:
            case 1:
                events[i] = 0;
                break;
            case 2:
                events[i] = MBRand(2.0f) + 8;
                break;
            case 3:
            case 4:
            retry:
                randVal = MBRand(100.0f);
                if (randVal < 20) {
                    if (i == 4 && events[3] == 1) {
                        goto retry;
                    }
                    events[i] = 1;
                } else if (randVal < 60) {
                    if (i == 4 && (events[3] == 2 || events[3] == 3)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 2;
                } else if (randVal < 90) {
                    if (i == 4 && (events[3] == 4 || events[3] == 5)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 4;
                } else {
                    if (i == 4 && (events[3] == 6 || events[3] == 7)) {
                        goto retry;
                    }
                    events[i] = MBRand(2.0f) + 6;
                    if (events[i] == 6 && func_80107090_koopa()) {
                        goto retry;
                    }
                }
                break;
        }
    }
    MBArrayShuffle(order, 4);
    for (i = 0; i < 5; i++) {
        D_8010954A_koopa[i] = events[order[i]];
    }
    for (i = 0; i < 5; i++) {
        window = D_80109518_koopa[i];
        if (D_8010954A_koopa[i] == 0) {
            sprintf(D_80109508_koopa, D_801094C0_koopa, func_80107658_koopa(0, D_801094F4_koopa));
            HuWinInsertMesSet(window[0], (u32)D_80109508_koopa, 0);
            HuWinInsertMesSizeGet((u32)D_80109508_koopa, 0);
        }
        HuWinMesSet(window[0], D_80109354_koopa[D_8010954A_koopa[i]], HUWIN_POS_CENTER, 4);
        HuWinMesSpeedSet(window[0], 0);
    }
    D_80109550_koopa = omAddObj(0x8000, 0, 0, -1, func_80105AD8_koopa);
    D_80109550_koopa->work[0] = 3;
    D_80109550_koopa->trans.y = 0;
    D_80109550_koopa->rot.z = 0;
    func_80106C78_koopa();
}

void func_80107648_koopa(void) {
    D_80109550_koopa->work[0] = 0;
}

s32 func_80107658_koopa(s32 arg0, s32 arg1) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = BoardGetTurnTier(CUR_TURN);
    playerRank = BoardPlayerRankCalc(arg1);
    return D_80109434_koopa[arg0][temp_s0][playerRank];
}

s32 func_801076CC_koopa(s32 playerIndex) {
    s32 temp_s0;
    s32 playerRank;

    temp_s0 = BoardGetTurnTier(CUR_TURN);
    playerRank = BoardPlayerRankCalc(playerIndex);
    return D_80109434_koopa[2][temp_s0][playerRank];
}

void func_80107724_koopa(void) {
    func_800F5E24_shared_board(D_801094F4_koopa);
    MBStatusDispMoveSet(0x18);
    func_800F5E24_shared_board(-1);
    HuPrcSleep(20);
}

void func_8010775C_koopa(void) {
    func_800F5E24_shared_board(D_801094F4_koopa);
    MBStatusDispMoveSet(0x18);
    func_800F5E24_shared_board(-1);
}

s32 func_8010778C_koopa(void) {
    s32 temp_v0;

    temp_v0 = func_80107658_koopa(0, D_801094F4_koopa);
    sprintf(D_80109508_koopa, D_801094C0_koopa, temp_v0);
    if (GwPlayer[D_801094F4_koopa].coin >= temp_v0) {
        MBWinInsertOpen(0x420D, D_80109508_koopa, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x420E, D_80109508_koopa, 0, 0, 0, 0);
    }

    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80107724_koopa();
    MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
    func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    MBCoinTakeCreate(D_801094F4_koopa, -temp_v0);
    MBPlayerVibrate(D_801094F6_koopa, 3);
    HuPrcSleep(30);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

s32 func_801078CC_koopa(void) {
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v0_2;
    s32 i;

    temp_v0 = func_80107658_koopa(1, D_801094F4_koopa);
    sprintf(D_80109508_koopa, D_801094C0_koopa, temp_v0);
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].coin < temp_v0) {
            break;
        }
    }

    if (i == 4) {
        MBWinInsertOpen(0x4210, D_80109508_koopa, 0, 0, 0, 0);
    } else {
        MBWinInsertOpen(0x4211, D_80109508_koopa, 0, 0, 0, 0);
    }

    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBStatusDispMoveSet(0);
    HuPrcSleep(20);
    MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
    func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
    HuPrcSleep(14);
    HuAudFXPlay(0x29F);
    var_a0_2 = -10000;
    var_s1 = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        temp_v1 = GwPlayer[i].coin - temp_v0;
        if (var_a0_2 < temp_v1) {
            var_a0_2 = temp_v1;
            var_s1 = i;
        }
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBCoinTakeCreateSound(i, -temp_v0, i == var_s1);
        MBPlayerVibrate(i, 3);
    }

    HuPrcSleep(30);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

s32 func_80107A9C_koopa(void) {
    UnkBoard8 *sprite;
    void *data;
    s32 i;

    MBWinOpen(0x4212);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    if (MBItemFindEmpty(D_801094F4_koopa) == -1) {
        func_80107724_koopa();
        MBWinOpen(0x4213);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    sprite = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x21003A);
    sprite->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->spriteGroup, 0, sprite->model[0], 0);
    HuSprAttrReset(sprite->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPriSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPosSet(sprite->spriteGroup, 0, 160, -32);
    func_8010775C_koopa();
    for (i = 0; i <= 120; i += 4) {
        HuSprPosSet(sprite->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
        HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
        HuPrcVSleep();
    }
    func_800F2CA4_shared_board(sprite);
    HuAudFXPlay(0x10);
    GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = ITEM_BOWSER_SUIT;
    MBStatusItemIconSprReinit(D_801094F4_koopa);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

s32 func_80107DDC_koopa(void) {
    UnkBoard8 *sprite;
    void *data;
    s32 i;

    MBWinOpen(0x4214);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    if (MBItemFindEmpty(D_801094F4_koopa) == -1) {
        func_80107724_koopa();
        MBWinOpen(0x4215);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        return 1;
    }
    sprite = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x210034);
    sprite->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->spriteGroup, 0, sprite->model[0], 0);
    HuSprAttrReset(sprite->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPriSet(sprite->spriteGroup, 0, 0x1000);
    HuSprPosSet(sprite->spriteGroup, 0, 160, -32);
    func_8010775C_koopa();
    for (i = 0; i <= 120; i += 4) {
        HuSprPosSet(sprite->spriteGroup, 0, 160, i - 32);
        HuPrcVSleep();
    }
    HuPrcSleep(15);
    for (i = 0; i < 70; i += 5) {
        HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
        HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
        HuPrcVSleep();
    }
    HuSprDispOff(sprite->spriteGroup, 0);
    HuAudFXPlay(0x10);
    GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = ITEM_BOWSER_PHONE;
    MBStatusItemIconSprReinit(D_801094F4_koopa);
    if (MBItemFindEmpty(D_801094F4_koopa) != -1 && MBRand(10.0f) == 0) {
        MBWinOpen(0x4216);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuSprDispOn(sprite->spriteGroup, 0);
        HuSprTPLvlSet(sprite->spriteGroup, 0, 256);
        for (i = 0; i <= 10; i++) {
            HuSprPosSet(sprite->spriteGroup, 0, 160, 88);
            HuSprScaleSet(sprite->spriteGroup, 0, i / 10.0f, i / 10.0f);
            HuPrcVSleep();
        }
        HuPrcSleep(15);
        for (i = 0; i < 70; i += 5) {
            HuSprPosSet(sprite->spriteGroup, 0, sindf(i) * 90.0f + 160.0f, sindf(i + 90) * 50.0f + 38.0f);
            HuSprTPLvlSet(sprite->spriteGroup, 0, 256 - i * 2);
            HuSprScaleSet(sprite->spriteGroup, 0, 1.0f - i / 140.0f, 1.0f - i / 140.0f);
            HuPrcVSleep();
        }
        HuSprDispOff(sprite->spriteGroup, 0);
        HuAudFXPlay(0x10);
        GwPlayer[D_801094F4_koopa].itemNo[MBItemFindEmpty(D_801094F4_koopa)] = ITEM_BOWSER_PHONE;
        MBStatusItemIconSprReinit(D_801094F4_koopa);
    }
    func_800F2CA4_shared_board(sprite);
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

void func_80108360_koopa(s32 modelFile) {
    Object *object;
    f32 angle;
    f32 scale;
    s32 i;

    MBMotionShiftSet(D_801094F8_koopa, 5, 0, 5, 0);
    object = MBModelFileCreate(modelFile, -1, 1.0f, NULL, NULL);
    func_8001C258_main(object->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(object->omObj1->model[0], 0);
    HuVecCopy3F(&object->coords, &D_801094F8_koopa->coords);
    object->coords.y += 200.0f;
    angle = 0.0f;
    scale = 1.0f;
    for (i = 0; scale < 12.0f; scale += 0.25) {
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[object->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (i == 5) {
            HuAudFXPlay(0x12D);
        }
        i++;
        HuPrcVSleep();
    }
    for (i = 0; scale >= 1.0f; scale -= 0.25) {
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[object->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (i == 32) {
            HuAudFXPlay(0x13E);
        }
        i++;
        HuPrcVSleep();
    }
    MBModelKill(object);
    MBModelMotionWait(D_801094F8_koopa);
    MBMotionShiftSet(D_801094F8_koopa, -1, 0, 5, 2);
}

s32 func_801085E4_koopa(void) {
    MBWinOpen(0x4217);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0036);
    MBWinOpen(0x4218);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_800E4A94_shared_board();
    return 0;
}

s32 func_80108664_koopa(void) {
    MBWinOpen(0x421A);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0037);
    MBWinOpen(0x421B);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    func_800E4B18_shared_board();
    return 0;
}

s32 func_801086E4_koopa(void) {
    s32 player1;
    s32 player2;
    s32 other1;
    s32 other2;
    s32 i;

    MBWinOpen(0x421D);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    player1 = 0;
    func_800EC3E4_shared_board();
    func_80108360_koopa(0xB0038);
    player2 = MBRand(3.0f) + 1;
    MBPlayerMasuSwap(player1, player2);
    other2 = -1;
    other1 = -1;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i != player1) & (i != player2)) {
            if (other1 == -1) {
                other1 = i;
            } else {
                other2 = i;
            }
        }
    }
    MBPlayerMasuSwap(other1, other2);
    MBWinOpen(0x421E);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    MBWinOpen(0x420F);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 0;
}

void func_801087F0_koopa(void) {
    s32 playSound;
    s32 i;
    s32 average = 0;
    s32 soundPlayer;
    s32 maxGain;
    s32 gain;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        average += GwPlayer[i].coin;
    }
    HuAudFXPlay(0x152);
    average /= MB_MAX_PLAYERS;
    maxGain = 0;
    soundPlayer = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        func_800F5828_shared_board(i);
        gain = average - GwPlayer[i].coin;
        if (maxGain < gain) {
            maxGain = gain;
            soundPlayer = i;
        }
    }
    for (i = 0; i < 60; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        playSound = i == soundPlayer;
        MBCoinTakeCreateSound(i, average - GwPlayer[i].coin, playSound);
    }
    for (i = 0; i < 30; i++) {
        MBStatusColorSet(0, i % 5);
        MBStatusColorSet(1, i % 5);
        MBStatusColorSet(2, i % 5);
        MBStatusColorSet(3, i % 5);
        HuPrcVSleep();
    }
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBStatusColorSet(i, GwPlayer[i].color);
        func_800F591C_shared_board(i);
    }
    omDelPrcObj(NULL);
}

s32 func_80108A2C_koopa(void) {
    s32 total = 0;
    s32 i;
    s32 result;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        total += GwPlayer[i].coin;
    }
    if (total >= MB_MAX_PLAYERS) {
        MBWinOpen(0x421F);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        MBStatusDispMoveSet(0);
        HuPrcSleep(20);
        HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_801087F0_koopa, 0x300, 0x2000, 0));
        func_80108360_koopa(0xB0039);
        HuPrcChildWatch();
        MBWinOpen(0x4221);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        MBWinOpen(0x420F);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        result = 0;
    } else {
        MBWinOpen(0x4220);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        HuAudFXPlay(0x29E);
        MBMotionShiftSet(D_801094F8_koopa, 4, 0, 20, 0);
        MBModelMotionWait(D_801094F8_koopa);
        MBMotionShiftSet(D_801094F8_koopa, 7, 0, 5, 2);
        HuPrcSleep(10);
        result = 1;
    }
    return result;
}

s32 func_80108BB0_koopa(void) {
    Vec direction;
    s32 i;
    f32 scale;
    Object *object;

    HuPrcSleep(15);
    MBMotionSet(D_801094F8_koopa, 6, 2);
    Hu3DMotionSpeedSet(D_801094F8_koopa->omObj1->model[0], 2.0f);
    MBVecDirGet(&D_801094F8_koopa->coords, &D_801093BC_koopa, &direction);
    HuPrcChildLink(HuPrcCurrentGet(), func_800ED128_shared_board(&D_801094F8_koopa->rot, &direction, &D_801094F8_koopa->rot, 10));
    HuPrcChildWatch();
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&D_801094F8_koopa->coords, &D_801093BC_koopa, &D_801094F8_koopa->coords, 30));
    for (i = 0; i < 30; i++) {
        object = D_801094F8_koopa;
        scale = 2.0f - i / 15.0f;
        HuVecCopyXYZ(&object->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    MBModelDispOff(D_801094F8_koopa);
    MBWinOpen(0x4222);
    func_800EC3C0_shared_board(D_801094F4_koopa);
    func_800EC3E4_shared_board();
    return 1;
}

void func_80108D2C_koopa(void) {
    s32 result = 0;

    Hu3DFogSet(0x3CA, 1000, 0, 0, 0);
    D_801094F8_koopa = MBModelFileCreate(0xA002F, 9, 0.7f, 1.4f, (u32 *)&D_801093C8_koopa);
    HuVecCopy3F(&D_801094F8_koopa->coords, &D_801093B0_koopa);
    HuVecCopyXYZ(&D_801094F8_koopa->scale, 2.0f, 2.0f, 2.0f);
    if (MBRand(5.0f) == 0) {
        MBMotionSet(D_801094F8_koopa, 7, 2);
        D_801094FC_koopa = 1;
    } else {
        MBMotionSet(D_801094F8_koopa, 1, 2);
        D_801094FC_koopa = 0;
    }
    func_8010699C_koopa();
    func_80107190_koopa();
    HuAudSeqPlay(0x24);
    WipeCreateIn(3, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    if (D_801094FC_koopa == 0) {
        HuPrcSleep(20);
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
    } else {
        HuPrcSleep(20);
        MBMotionSet(D_801094F8_koopa, 4, 4);
        Hu3DMotionTimeSet(D_801094F8_koopa->omObj1->model[0], 1024.0f);
        while (func_800D9E80_shared_board(D_801094F8_koopa) == 0) {
            HuPrcVSleep();
        }
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
        HuPrcSleep(10);
        MBMotionShiftSet(D_801094F8_koopa, 1, 0, 5, 2);
        HuPrcSleep(36);
        MBMotionShiftSet(D_801094F8_koopa, -1, 0, 10, 2);
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x29D);
    if (GwPlayer[D_801094F4_koopa].coin == 0) {
        sprintf(D_80109508_koopa, D_801094C0_koopa, func_801076CC_koopa(D_801094F4_koopa));
        MBWinInsertOpen(0x420B, (char *)mbCharNameMesTbl[GwPlayer[D_801094F4_koopa].chr], (u32)D_80109508_koopa, 0, 0, 0);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        func_80107724_koopa();
        MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
        func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
        HuPrcSleep(14);
        MBCoinTakeCreate(D_801094F4_koopa, func_801076CC_koopa(D_801094F4_koopa));
        HuPrcSleep(30);
        MBWinOpen(0x420C);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
    } else {
        MBWinInsertOpen(0x420A, (char *)mbCharNameMesTbl[GwPlayer[D_801094F4_koopa].chr], 0, 0, 0, 0);
        func_800EC3C0_shared_board(D_801094F4_koopa);
        func_800EC3E4_shared_board();
        MBMotionShiftSet(D_801094F8_koopa, 2, 0, 5, 0);
        func_800EE884_shared_board(D_801094F8_koopa, -1, 2);
        HuPrcSleep(14);
        func_80107648_koopa();
        while (D_80109550_koopa != NULL) {
            HuPrcVSleep();
        }
        result = D_801093EC_koopa[D_80109568_koopa]();
    }
    if (result == 0) {
        HuAudFXPlay(0x29C);
        MBMotionShiftSet(D_801094F8_koopa, 3, 0, 5, 2);
    }
    HuPrcSleep(20);
    D_800D530C_main = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void func_801091C4_koopa(omObjData *obj) {
    if (WipeStatGet() == 0) {
        func_80109320_koopa();
        func_801092A0_koopa();
        func_800F4730_shared_board();
        HuWinAllKill();
        func_800EB09C_shared_board();
        func_800EA694_shared_board();
        omOvlReturnEx(1);
    }
}

void func_80109220_koopa(omObjData *obj) {
    if (D_800D530C_main != 0) {
        WipeCreateOut(3, 20);
        HuAudSeqFadeOut(60);
        obj->func = func_801091C4_koopa;
    }
}

void func_8010926C_koopa(void) {
    MBModelInit();
    func_800F26E8_shared_board();
    func_800EE700_shared_board();
    func_800F2A20_shared_board();
}

void func_801092A0_koopa(void) {
    func_800F2A34_shared_board();
    func_800EE740_shared_board();
    func_800F27C4_shared_board();
    MBModelClose();
}

void func_801092D4_koopa(void) {
    Hu3DCamInit(1);
    func_800E6630_shared_board((u32)hvq_data_ROM_START);
    MBBackLoad(2);
    func_800E9344_shared_board(100.0f, 10000.0f);
}

void func_80109320_koopa(void) {
    MBBackKill();
    MBBackClose();
}
