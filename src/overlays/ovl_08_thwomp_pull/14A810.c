#include "common.h"
#include "overlays/minigame.h"

typedef struct ThwompPullPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ThwompPullPlayer; // sizeof 0x10

extern D_80111B50_vine_with_me_Struct D_8010ED60_thwomp_pull;
extern u32 D_8010ED88_thwomp_pull;
extern f32 D_8010F470_thwomp_pull[3];
extern f32 D_8010F47C_thwomp_pull[3];
extern f32 D_8010F488_thwomp_pull[3];
extern f32 D_8010F494_thwomp_pull[3];
extern f32 D_8010F4A0_thwomp_pull[3];
extern f32 D_8010F4AC_thwomp_pull[3];
extern ThwompPullPlayer D_8010F4B8_thwomp_pull[4];
extern ThwompPullPlayer *D_8010F4F8_thwomp_pull[4]; // players indexed by group
extern f32 D_8010F510_thwomp_pull[4];
extern f32 D_8010F520_thwomp_pull[4];
extern HmfModelSet *D_8010F528_thwomp_pull;
extern omObjData *D_8010F52C_thwomp_pull;
extern s16 D_8010F530_thwomp_pull;
extern s32 D_8010F53C_thwomp_pull;
extern f32 D_8010F540_thwomp_pull[4];
extern s16 D_8010F550_thwomp_pull[10]; // sprite data ids
extern u8 D_8010F564_thwomp_pull[2];
extern s8 D_8010F566_thwomp_pull;
extern omObjData *D_8010F568_thwomp_pull[2];
extern u16 D_8010F570_thwomp_pull;
extern f32 D_8010F578_thwomp_pull[4];
extern f32 D_8010F588_thwomp_pull;
extern s16 D_8010F590_thwomp_pull[10]; // sprite ids
extern Gfx D_8010ED90_thwomp_pull[];
extern u8 D_8010EE20_thwomp_pull;
extern Gfx *gMainGfxPos;
extern s32 D_8010F5A4_thwomp_pull;
extern u8 D_8010F5A8_thwomp_pull;
extern HmfModelSet *D_8010F5AC_thwomp_pull[2];
extern u8 D_8010F5B4_thwomp_pull[4]; // group of each player

const s16 D_8010EFD0_thwomp_pull[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void func_80105D3C_thwomp_pull(omObjData *object);
void func_80106D5C_thwomp_pull(omObjData *object);
void func_8010974C_thwomp_pull(omObjData *object);
void func_80109780_thwomp_pull(omObjData *object);

void func_80105F14_thwomp_pull(omObjData *object);
void func_80106E78_thwomp_pull(omObjData *object);
void func_801089B4_thwomp_pull(Gfx **gfxPos, s32 arg1, s32 arg2);
void func_801097AC_thwomp_pull(omObjData *object, s8 group);
void func_8010AF88_thwomp_pull(omObjData *object);

void func_801059A0_thwomp_pull(void) {
    omObjData *object;

    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 140.0f, 240.0f);
    ScissorSet(1, 180.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
    Hu3DFogSet(950, 1000, 0xFF, 0xFF, 0xFF);
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, -39.0f, 45.0f, 104.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 115.0f;
    CenterM[0].z = -500.0f;
    CRotM[0].x = -16.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 1260.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 115.0f;
    CenterM[1].z = -500.0f;
    CRotM[1].x = -16.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 1260.0f;
    omAddObj(0, 0, 0, -1, func_80105D3C_thwomp_pull);
    D_8010F52C_thwomp_pull = omAddObj(8, 1, 1, -1, func_80106D5C_thwomp_pull);
    omSetStatBit(D_8010F52C_thwomp_pull, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010F568_thwomp_pull[0] = omAddObj(3, 52, 21, -1, func_8010974C_thwomp_pull);
    D_8010F568_thwomp_pull[1] = omAddObj(3, 52, 21, -1, func_80109780_thwomp_pull);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80045010_main(D_8010EFD0_thwomp_pull, 1);
    WipeCreateIn(0xFF, 16);
    D_8010ED60_thwomp_pull.unk01 = 2;
    D_8010ED60_thwomp_pull.unk1C = -1;
    D_8010ED60_thwomp_pull.unk1C = 75;
    D_8010ED60_thwomp_pull.unk1E = 1800;
    D_8010ED60_thwomp_pull.unk03 = 2;
    D_8010ED60_thwomp_pull.unk02 = 1;
    D_8010ED60_thwomp_pull.unk22 = 45;
    D_8010ED60_thwomp_pull.unk24 = 165;
    D_8010ED60_thwomp_pull.unk04 = 0;
    D_8010ED60_thwomp_pull.unk05 = 0;
    D_8010ED60_thwomp_pull.unk20 = -1;
    func_800E5EA0_minigame(&D_8010ED60_thwomp_pull);
}

void func_80105D3C_thwomp_pull(omObjData *object) {
    s32 group;
    s32 i;

    D_8010F570_thwomp_pull = 0;
    D_8010F530_thwomp_pull = 0;
    D_8010F5A4_thwomp_pull = 0;
    D_8010F53C_thwomp_pull = 0;
    D_8010F566_thwomp_pull = 5;
    D_8010F5A8_thwomp_pull = 0;
    D_8010F520_thwomp_pull[0] = D_8010F520_thwomp_pull[1] = D_8010F520_thwomp_pull[2] = D_8010F520_thwomp_pull[3] = 0.0f;
    D_8010F588_thwomp_pull = 0.0f;
    D_8010F564_thwomp_pull[0] = D_8010F564_thwomp_pull[1] = 0;
    for (i = 0; i < 4; i++) {
        D_8010F4F8_thwomp_pull[i] = &D_8010F4B8_thwomp_pull[i];
        bzero(D_8010F4F8_thwomp_pull[i], sizeof(ThwompPullPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        group = (group == 3) ? 1 : (group == 1) ? 3
                                                : group;
        D_8010F5B4_thwomp_pull[i] = group;
        D_8010F4F8_thwomp_pull[group]->playerNo = i;
        D_8010F4F8_thwomp_pull[group]->pad = GwPlayer[i].pad;
        D_8010F4F8_thwomp_pull[group]->chr = GwPlayer[i].chr;
        D_8010F4F8_thwomp_pull[group]->group = group;
        D_8010F4F8_thwomp_pull[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, func_801089B4_thwomp_pull, 2);
    object->func = func_80105F14_thwomp_pull;
}

void func_80105F14_thwomp_pull(omObjData *object) {
    omObjData *winner;
    s32 i;
    s32 j;
    u8 k;

    D_8010F5A4_thwomp_pull++;
    D_8010F53C_thwomp_pull++;
    func_800E6F40_minigame();
    switch (D_8010F530_thwomp_pull) {
        case 0:
            if (D_8010F5A4_thwomp_pull == 1 && D_8010F570_thwomp_pull == 0 && D_800D530C_main == 0) {
                HuAudFXPlay(0x335);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_8010F530_thwomp_pull = 1;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 1:
            if (D_8010F5A4_thwomp_pull == 31 && D_8010F570_thwomp_pull == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x2E);
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010F530_thwomp_pull = 2;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 2:
            if (D_8010F566_thwomp_pull != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010F566_thwomp_pull == 5) {
                    D_8010F530_thwomp_pull = 5;
                    D_8010F566_thwomp_pull = 4;
                } else {
                    D_8010F530_thwomp_pull = 3;
                }
                D_8010F5A4_thwomp_pull = 0;
            }
            if (D_8010F530_thwomp_pull != 3) {
                break;
            }
        case 3:
        case 4:
            if (D_8010F5A4_thwomp_pull == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                if (D_8010F566_thwomp_pull == 0) {
                    D_8010ED60_thwomp_pull.unk06 = 0;
                    D_8010ED60_thwomp_pull.unk18[0] = D_8010F4F8_thwomp_pull[0]->playerNo;
                    GwPlayer[D_8010F4F8_thwomp_pull[0]->playerNo].bonusCoin = 10;
                } else {
                    D_8010ED60_thwomp_pull.unk06 = 2;
                    D_8010ED60_thwomp_pull.unk18[0] = D_8010F4F8_thwomp_pull[1]->playerNo;
                    D_8010ED60_thwomp_pull.unk18[1] = D_8010F4F8_thwomp_pull[3]->playerNo;
                    D_8010ED60_thwomp_pull.unk18[2] = D_8010F4F8_thwomp_pull[2]->playerNo;
                    GwPlayer[D_8010F4F8_thwomp_pull[1]->playerNo].bonusCoin = 10;
                    GwPlayer[D_8010F4F8_thwomp_pull[2]->playerNo].bonusCoin = 10;
                    GwPlayer[D_8010F4F8_thwomp_pull[3]->playerNo].bonusCoin = 10;
                }
            }
            if (D_8010F5A4_thwomp_pull == 2) {
                func_800E6F34_minigame(30);
            }
            if (D_8010F5A4_thwomp_pull >= 31 && D_8010F5A4_thwomp_pull <= 61) {
                D_8010F588_thwomp_pull = (D_8010F5A4_thwomp_pull - 31) / 30.0;
            }
            if (D_8010F5A4_thwomp_pull >= 32 && D_8010F5A4_thwomp_pull < 80 && D_8010F566_thwomp_pull < 2) {
                winner = D_8010F568_thwomp_pull[D_8010F566_thwomp_pull];
                if (D_8010ED88_thwomp_pull == 0) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        D_8010F470_thwomp_pull[i] = D_8010F578_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F47C_thwomp_pull[i] = D_8010F510_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F488_thwomp_pull[i] = D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i];
                        D_8010F494_thwomp_pull[i] = (D_8010F566_thwomp_pull != 0) ? (1 - i) * 1.5 : 0.0;
                        D_8010F4A0_thwomp_pull[i] = 38.0f;
                        D_8010F4AC_thwomp_pull[i] = 20.0f;
                        func_8001C258_main(winner->model[i + 1], 4, 4);
                        func_8001C258_main(winner->model[i + 39], 4, 0);
                        Hu3DModelPosSet(winner->model[i + 39], D_8010F470_thwomp_pull[i], D_8010F47C_thwomp_pull[i],
                                        D_8010F488_thwomp_pull[i]);
                        Hu3DModelRotSet(winner->model[i + 39], 0.0f, 0.0f, 0.0f);
                        Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 15]].motId, 8, 4, 1);
                    }
                } else if (D_8010ED88_thwomp_pull > 0 && D_8010ED88_thwomp_pull < 100) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        if (D_8010ED88_thwomp_pull < 5) {
                            f32 dy[4] = { -23.0f, -98.0f, -86.0f, -98.0f };
                            f32 dz[4] = { -46.0f, -3.0f, -35.0f, -3.0f };

                            D_8010F510_thwomp_pull[D_8010F566_thwomp_pull + i] += dy[D_8010F566_thwomp_pull + i] / 4.0;
                            D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i] += dz[D_8010F566_thwomp_pull + i] / 4.0;
                            if (D_8010F566_thwomp_pull == 1 && i == 0) {
                                D_8010F540_thwomp_pull[D_8010F566_thwomp_pull + i] = dz[D_8010F566_thwomp_pull + i];
                            }
                        }
                        D_8010F470_thwomp_pull[i] += D_8010F494_thwomp_pull[i];
                        D_8010F47C_thwomp_pull[i] += D_8010F4A0_thwomp_pull[i];
                        D_8010F488_thwomp_pull[i] += D_8010F4AC_thwomp_pull[i];
                        D_8010F4A0_thwomp_pull[i] -= 4.0f;
                        Hu3DModelPosSet(winner->model[i + 39], D_8010F470_thwomp_pull[i], D_8010F47C_thwomp_pull[i],
                                        D_8010F488_thwomp_pull[i]);
                        Hu3DModelPosSet(winner->model[i + 42], D_8010F470_thwomp_pull[i],
                                        (D_8010ED88_thwomp_pull == 1) ? 30.0f : 0.0f, D_8010F488_thwomp_pull[i]);
                        if (D_8010ED88_thwomp_pull == 2) {
                            Hu3DModelLayerSet(winner->model[i + 42], 0x400);
                        }
                        if (D_8010ED88_thwomp_pull == 1) {
                            Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 12]].motId, 14, 4, 0);
                        }
                    }
                    if (D_8010F47C_thwomp_pull[0] <= 0.0f) {
                        D_8010ED88_thwomp_pull = 100;
                        D_8010F47C_thwomp_pull[2] = D_8010F47C_thwomp_pull[1] = D_8010F47C_thwomp_pull[0] = 0.0f;
                        for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                            Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i + 15]].motId, 10, 4, 0);
                            Hu3DModelPosSet(winner->model[i + 39], D_8010F470_thwomp_pull[i], 0.0f,
                                            D_8010F488_thwomp_pull[i]);
                            Hu3DModelPosSet(winner->model[i + 42], D_8010F470_thwomp_pull[i], 0.0f,
                                            D_8010F488_thwomp_pull[i]);
                        }
                    }
                } else if (D_8010ED88_thwomp_pull == 102) {
                    for (i = 0; i < D_8010F566_thwomp_pull * 2 + 1; i++) {
                        Hu3DMotionShiftSet(winner->model[i + 39], Hu3DData[winner->motion[i]].motId, 0, 30, 2);
                    }
                }
                D_8010ED88_thwomp_pull += (D_8010ED88_thwomp_pull != 99);
            }
            if (D_800EB934_minigame != 0) {
                s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                if (D_8010F566_thwomp_pull == 0) {
                    func_80017954_main(D_8010F568_thwomp_pull[0]->model[39], 1, slots[D_8010F4F8_thwomp_pull[0]->chr],
                                       D_8010F4F8_thwomp_pull[0]->unk_08);
                    func_8001C5B4_main(D_8010F568_thwomp_pull[0]->model[39], D_8010F568_thwomp_pull[0]->motion[9]);
                    func_8001C814_main(D_8010F568_thwomp_pull[0]->model[39], 3, 0);
                    func_80045ED0_main(D_8010F4F8_thwomp_pull[0]->unk_0C);
                } else if (D_8010F566_thwomp_pull == 1) {
                    for (j = 0; j < 3; j++) {
                        func_80017954_main(D_8010F568_thwomp_pull[1]->model[j + 39], 1,
                                           slots[D_8010F4F8_thwomp_pull[1 + j]->chr],
                                           D_8010F4F8_thwomp_pull[1 + j]->unk_08);
                        func_8001C5B4_main(D_8010F568_thwomp_pull[1]->model[j + 39],
                                           D_8010F568_thwomp_pull[1]->motion[j + 9]);
                        func_8001C814_main(D_8010F568_thwomp_pull[1]->model[j + 39], 3, 0);
                        func_80045F1C_main(D_8010F4F8_thwomp_pull[1 + j]->unk_0C, -1,
                                           D_8010F4F8_thwomp_pull[1 + j]->playerNo);
                    }
                }
            }
            if (D_8010F530_thwomp_pull == 3 && func_800E6E8C_minigame() == 4) {
                D_8010F530_thwomp_pull = 4;
            }
            if (func_800E6E8C_minigame() == 5) {
                D_8010F530_thwomp_pull = 7;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 5:
            if (D_8010F5A4_thwomp_pull == 1) {
                D_8010ED60_thwomp_pull.unk06 = 4;
                D_8010ED60_thwomp_pull.unk22 = 75;
                D_8010ED60_thwomp_pull.unk24 = 0x90;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F530_thwomp_pull = 6;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 6:
            if (func_800E6E8C_minigame() == 5) {
                D_8010F530_thwomp_pull = 7;
                D_8010F5A4_thwomp_pull = 0;
            }
            break;
        case 7:
            if (D_8010F5A4_thwomp_pull == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010F5A4_thwomp_pull >= 32) {
                D_8010F570_thwomp_pull = 1;
            }
            break;
    }
    if (_CheckFlag(15) && D_800D530C_main == 0 && D_8010F5A8_thwomp_pull == 0 && (u16)D_8010F530_thwomp_pull == 2) {
        for (k = 0; k < 2; k++) {
            if (D_8010F4F8_thwomp_pull[k]->cpuDifficulty == -1 &&
                (D_800D5558_main[D_8010F4F8_thwomp_pull[k]->pad] & R_TRIG)) {
                D_8010F5A8_thwomp_pull = 1;
            }
        }
    }
    if (D_8010F570_thwomp_pull != 0 || D_800D530C_main != 0 || D_8010F5A8_thwomp_pull != 0) {
        if (D_800D530C_main != 0 && D_8010F5A8_thwomp_pull == 0) {
            D_8010F5A8_thwomp_pull = 1;
        }
        if (D_8010F5A8_thwomp_pull != 0) {
            if (D_8010F5A8_thwomp_pull == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_8010F5A8_thwomp_pull++;
            if (D_8010F5A8_thwomp_pull < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        func_80017320_main(D_8010F528_thwomp_pull);
        func_80017320_main(D_8010F5AC_thwomp_pull[0]);
        func_80017320_main(D_8010F5AC_thwomp_pull[1]);
        omOvlReturnEx(1);
    }
}

void func_80106D5C_thwomp_pull(omObjData *object) {
    s32 spriteFiles[10] = { 0x29001F, 0x290020, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
    s16 i;

    for (i = 0; i < 10; i++) {
        D_8010F590_thwomp_pull[i] = espEntry(D_8010F550_thwomp_pull[i] = func_8000B838_main(spriteFiles[i]), 0, 0);
        espDispOff(D_8010F590_thwomp_pull[i]);
    }
    object->func = func_80106E78_thwomp_pull;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80106E78_thwomp_pull);

void func_80107FF4_thwomp_pull(s16 *left, s16 *top, s16 *right, s16 *bottom) {
    s32 scissorLeft[2];
    s32 scissorRight[2];
    f32 scaleX[2];
    f32 offsetX[2];
    f32 scaleY[2];
    f32 offsetY[2];
    s32 dsdx[2];
    s32 dtdy[2];
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *sprite;
    f32 progress;
    f32 remain;
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        scaleX[i] = (right[i] - left[i]) / 160.0;
        offsetX[i] = left[i];
        dsdx[i] = (1.0 / scaleX[i]) * 1024.0;
        scaleY[i] = (bottom[i] - top[i]) / 240.0;
        offsetY[i] = top[i];
        dtdy[i] = (1.0 / scaleY[i]) * 1024.0;
        scissorLeft[i] = (i == 0) ? 0 : 180;
        scissorRight[i] = (i != 0) ? 320 : 140;
    }
    if (D_8010F588_thwomp_pull > 0.0f && D_8010F566_thwomp_pull < 2) {
        progress = D_8010F588_thwomp_pull;
        remain = 1.0f - progress;
        i = D_8010F566_thwomp_pull;
        scissorLeft[i] = scissorLeft[i] * remain + progress * 0.0f;
        scissorRight[i] = scissorRight[i] * remain + progress * 320.0f;
        if (i == 0) {
            scissorLeft[1] = scissorLeft[1] * remain + progress * 318.0f;
            scissorRight[1] = scissorRight[1] * remain + progress * 320.0f;
        } else {
            scissorLeft[0] = scissorLeft[0] * remain + progress * 0.0f;
            scissorRight[0] = scissorRight[0] * remain + progress * 2.0f;
        }
    }

    gSPDisplayList(gMainGfxPos++, D_8010ED90_thwomp_pull);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(D_800CD1DC_main[D_8010F590_thwomp_pull[0]].unk04, 0);
    frame = &sprite->unk_84->unk00[sprite->unk_90];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
    for (j = 0; j < 3; j++) {
        t0 = j * 40;
        t1 = t0 + 40.0f + ((j == 2) ? -0.75 : 1.0);
        for (k = 0; k < 4; k++) {
            s0 = k * 40;
            s1 = s0 + 40.0f + ((k < 3) ? 1.0f : 0.0f);
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 160, 120, (s32)s0, (s32)t0, (s32)s1,
                               (s32)t1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            for (i = 0; i < 2; i++) {
                if (D_8010F588_thwomp_pull == 1.0f && i != D_8010F566_thwomp_pull) {
                    continue;
                }
                xl = (s0 * scaleX[i] + offsetX[i]) * 4.0f;
                yl = ((t0 - 1.0f) * scaleY[i] + offsetY[i]) * 4.0f;
                xh = (s1 * scaleX[i] + offsetX[i]) * 4.0f;
                yh = ((t1 - 1.0f) * scaleY[i] + offsetY[i]) * 4.0f;
                if (xl > 1280 || yl > 960) {
                    continue;
                }
                if (xh < 0 || yh < 0) {
                    continue;
                }
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, scissorLeft[i], 0, scissorRight[i], 240);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s0 * 32.0f, t0 * 32.0f, dsdx[i],
                                        dtdy[i]);
            }
        }
    }
}

void func_801089B4_thwomp_pull(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *sprite;
    f32 *gauge;
    f32 slide;
    f32 scale;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 offset = 0;
    s32 group;
    s32 i;
    s32 j;

    D_8010EE20_thwomp_pull = !D_8010EE20_thwomp_pull;
    if (D_8010EE20_thwomp_pull != 0) {
        return;
    }
    if (D_8010F588_thwomp_pull > 0.0f) {
        slide = D_8010F588_thwomp_pull * 178.0f;
        if (D_8010F566_thwomp_pull != 0) {
            offset = -slide * 4.0f;
        } else {
            offset = slide * 4.0f;
        }
    }
    gSPDisplayList(gMainGfxPos++, D_8010ED90_thwomp_pull);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(D_800CD1DC_main[D_8010F590_thwomp_pull[1]].unk04, 0);
    frame = &sprite->unk_84->unk00[sprite->unk_90];
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 0);
    for (j = 0; j < 4; j++) {
        gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 40, 240, 0, j * 60, 40, j * 60 + 60, 0,
                              G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                              G_TX_NOLOD);
        y = j * 60;
        y2 = j * 60 + 61;
        y2 = MIN(240.0f, y2);
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        gSPScisTextureRectangle(gMainGfxPos++, offset + 140 * 4, (s32)(y * 4.0f), offset + 180 * 4, (s32)(y2 * 4.0f),
                                G_TX_RENDERTILE, 0, j * 60 * 32, 1024, 1024);
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 4; i++) {
        s32 order[4] = { 3, 1, 2, 0 };

        group = order[i];
        sprite = HuSprGet(D_800CD1DC_main[D_8010F590_thwomp_pull[2 + D_8010F4F8_thwomp_pull[group]->chr]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        if (D_8010F4F8_thwomp_pull[group]->chr == 7) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        }
        if (D_8010F4F8_thwomp_pull[group]->chr == 7) {
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 18, 18, 0, 0, 18, 18, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                               G_TX_NOLOD);
        } else {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 18, 18, 0, 0, 18, 18, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
        }
        if (group > 0) {
            x = (3 - group) * 7 + 151;
        } else {
            x = 136.0f;
        }
        gauge = (group == 0) ? &D_8010F520_thwomp_pull[0] : &D_8010F520_thwomp_pull[1];
        y = *gauge * 165.0f + 35.0f;
        switch (group) {
            case 0:
                y = (s32)y;
                break;
            case 2:
                y = (s32)y - 3;
                break;
            case 1:
            case 3:
                y = (s32)y + 6;
                break;
        }
        x2 = x + 18.0f;
        y2 = y + 18.0f;
        scale = 1024.0f;
        gSPScisTextureRectangle(gMainGfxPos++, x * 4.0f + offset, (s32)(y * 4.0f), x2 * 4.0f + offset,
                                y2 * 4.0f - 3.0f, G_TX_RENDERTILE, 0, 0, (s32)scale, (s32)scale);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 255, 255, 255, 0);
    gDPPipeSync(gMainGfxPos++);
}

void func_8010974C_thwomp_pull(omObjData *object) {
    func_801097AC_thwomp_pull(object, 0);
    object->func = func_8010AF88_thwomp_pull;
}

void func_80109780_thwomp_pull(omObjData *object) {
    func_801097AC_thwomp_pull(object, 1);
    object->func = NULL;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F150_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F170_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F190_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1B0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1F0_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801097AC_thwomp_pull);

void func_8010AF18_thwomp_pull(s16 arg0, s16 arg1) {
    HmfModel *model = &Hu3DData[arg0];
    f32 value = arg1;

    Hu3DMotionTimeSet(arg0, value);
    model->hmf->unk98->unk08 = value;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F238_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F244_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_8010AF88_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F280_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2A0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2C0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2D8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2F0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F308_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F320_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F338_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F350_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F358_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F360_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F368_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F370_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F378_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F380_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F388_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F390_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F398_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F400_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F408_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F410_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F418_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F420_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F428_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F430_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F438_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F440_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F448_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F450_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F458_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F460_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F468_thwomp_pull);
