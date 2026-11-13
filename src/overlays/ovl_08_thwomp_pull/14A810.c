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
extern f32 D_8010F534_thwomp_pull[2];
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
void func_80107FF4_thwomp_pull(s16 *left, s16 *top, s16 *right, s16 *bottom);
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

void func_80106E78_thwomp_pull(omObjData *object) {
    s16 left[2] = { 0, 160 };
    s16 top[2] = { 0, 0 };
    s16 right[2] = { 160, 320 };
    s16 bottom[2] = { 240, 240 };
    s32 other;
    s32 i;

    if (D_8010F53C_thwomp_pull == 100) {
        CenterM[0].x = CenterM[1].x = 0.0f;
        CenterM[0].y = CenterM[1].y = 115.0f;
        CenterM[0].z = CenterM[1].z = -500.0f;
        CRotM[0].x = CRotM[1].x = -16.0f;
        CRotM[0].y = CRotM[1].y = 0.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 1260.0f;
        Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
    }
    if (D_8010F588_thwomp_pull > 0.0f && D_8010F566_thwomp_pull < 2) {
        f32 progress = D_8010F588_thwomp_pull;
        f32 remain = 1.0f - progress;
        f32 scissorLeft[2] = { 0.0f, 180.0f };
        f32 scissorRight[2] = { 140.0f, 320.0f };
        f32 viewScale[2] = { 1.0f, 1.0f };
        f32 viewX[2] = { 320.0f, 960.0f };
        f32 viewY[2] = { 480.0f, 480.0f };
        s32 offset;

        CenterM[D_8010F566_thwomp_pull].y = remain * 115.0f - progress * 80.0f;
        CRotM[D_8010F566_thwomp_pull].x = remain * -16.0f - progress * 6.0f;
        CZoomM[D_8010F566_thwomp_pull] = remain * 1260.0f + (D_8010F566_thwomp_pull * 150 + 1600) * progress;
        viewScale[D_8010F566_thwomp_pull] = progress + 1.0f;
        scissorLeft[D_8010F566_thwomp_pull] = remain * scissorLeft[D_8010F566_thwomp_pull] + progress * 0.0f;
        scissorRight[D_8010F566_thwomp_pull] = remain * scissorRight[D_8010F566_thwomp_pull] + progress * 320.0f;
        viewX[D_8010F566_thwomp_pull] = remain * viewX[D_8010F566_thwomp_pull] + progress * 640.0f;
        viewY[D_8010F566_thwomp_pull] = remain * viewY[D_8010F566_thwomp_pull] + progress * ((D_8010F566_thwomp_pull != 0) ? 780.0 : 720.0);
        left[D_8010F566_thwomp_pull] = left[D_8010F566_thwomp_pull] * remain + progress * 0.0f;
        right[D_8010F566_thwomp_pull] = right[D_8010F566_thwomp_pull] * remain + progress * 320.0f;
        top[D_8010F566_thwomp_pull] =
            top[D_8010F566_thwomp_pull] * remain + progress * ((D_8010F566_thwomp_pull != 0) ? -30.0f : -60.0f);
        bottom[D_8010F566_thwomp_pull] =
            bottom[D_8010F566_thwomp_pull] * remain + progress * ((D_8010F566_thwomp_pull != 0) ? 450.0f : 420.0f);
        if (D_8010F566_thwomp_pull == 0) {
            scissorLeft[1] = remain * scissorLeft[1] + progress * 318.0f;
            scissorRight[1] = remain * scissorRight[1] + progress * 320.0f;
            viewX[1] = progress * 712.0f + viewX[1];
            offset = progress * 178.0f;
            left[1] += offset;
            right[1] += offset;
        } else {
            scissorLeft[0] = remain * scissorLeft[0] + progress * 0.0f;
            scissorRight[0] = remain * scissorRight[0] + progress * 2.0f;
            viewX[0] = viewX[0] - progress * 712.0f;
            offset = progress * 178.0f;
            left[0] -= offset;
            right[0] -= offset;
        }
        ScissorSet(0, scissorLeft[0], 0.0f, scissorRight[0], 240.0f);
        ScissorSet(1, scissorLeft[1], 0.0f, scissorRight[1], 240.0f);
        ViewportSet(0, viewScale[0] * 640.0f, viewScale[0] * 480.0f, 511.0f, viewX[0], viewY[0], 511.0f);
        ViewportSet(1, viewScale[1] * 640.0f, viewScale[1] * 480.0f, 511.0f, viewX[1], viewY[1], 511.0f);
        func_80107FF4_thwomp_pull(left, top, right, bottom);
        if (D_8010F588_thwomp_pull == 1.0f) {
            object = D_8010F568_thwomp_pull[1 - D_8010F566_thwomp_pull];
            other = 1 - D_8010F566_thwomp_pull;
            func_8001C258_main(object->model[7], 4, 4);
            for (i = 0; i < other * 2 + 1; i++) {
                func_8001C258_main(object->model[i + 1], 4, 4);
            }
            for (i = 0; i < 3; i++) {
                func_8001C258_main(object->model[i + 4], 4, 4);
            }
            for (i = 0; i < 4; i++) {
                func_8001C258_main(object->model[i + 12], 4, 4);
                func_8001C258_main(object->model[i + 18], 4, 4);
            }
        }
    } else if (D_8010F53C_thwomp_pull < 100) {
        f32 progress;
        f32 remain;

        if (D_8010F53C_thwomp_pull < 80) {
            progress = D_8010F53C_thwomp_pull / 80.0;
        } else {
            progress = 1.0f;
        }
        remain = 1.0f - progress;
        CenterM[0].x = CenterM[1].x = progress * 435.0f - remain * 60.0f;
        CenterM[0].y = CenterM[1].y = 140.0f;
        CenterM[0].z = CenterM[1].z = -660.0f;
        CRotM[0].x = CRotM[1].x = -8.0f;
        CRotM[0].y = CRotM[1].y = -225.0f;
        CRotM[0].z = CRotM[1].z = 0.0f;
        CZoomM[0] = CZoomM[1] = 100.0f;
        CenterM[1].x = -CenterM[1].x;
        CRotM[1].y = -CRotM[1].y;
        Hu3DCameraPerspectiveSet(0, 65.0f, 50.0f, 4000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 50.0f, 4000.0f);
        top[0] += D_8010F534_thwomp_pull[0];
        bottom[0] += D_8010F534_thwomp_pull[0];
        top[1] += D_8010F534_thwomp_pull[1];
        bottom[1] += D_8010F534_thwomp_pull[1];
        func_80107FF4_thwomp_pull(left, top, right, bottom);
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, D_8010F534_thwomp_pull[0] * 4.0f + 480.0f, 511.0f);
        ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, D_8010F534_thwomp_pull[1] * 4.0f + 480.0f, 511.0f);
    } else if (D_8010F53C_thwomp_pull < 150) {
        f32 scale;
        f32 remain;

        if (D_8010F53C_thwomp_pull >= 100) {
            if (D_8010F53C_thwomp_pull < 115) {
                scale = (D_8010F53C_thwomp_pull - 100) / 15.0;
            } else {
                scale = 1.0f;
            }
        } else {
            scale = 0.0f;
        }
        remain = 1.0f - scale;
        scale = (remain * remain * remain * 0.75 + remain * 0.25) * 0.5 + 1.0;
        ViewportSet(0, scale * 640.0f, scale * 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
        ViewportSet(1, scale * 640.0f, scale * 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
        left[0] = (left[0] - 80) * scale + 80.0f;
        top[0] = (top[0] - 120) * scale + 120.0f;
        right[0] = (right[0] - 80) * scale + 80.0f;
        bottom[0] = (bottom[0] - 120) * scale + 120.0f;
        left[1] = (left[1] - 240) * scale + 240.0f;
        top[1] = (top[1] - 120) * scale + 120.0f;
        right[1] = (right[1] - 240) * scale + 240.0f;
        bottom[1] = (bottom[1] - 120) * scale + 120.0f;
        Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
        Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
        func_80107FF4_thwomp_pull(left, top, right, bottom);
    } else {
        f32 scale;

        if (D_8010F53C_thwomp_pull >= 90) {
            if (D_8010F53C_thwomp_pull < 120) {
                scale = 2.5 - (D_8010F53C_thwomp_pull - 90) / 30.0 * 1.5;
            } else {
                scale = 1.0f;
            }
        } else {
            scale = 2.5f;
        }
        ViewportSet(0, scale * 640.0f, scale * 480.0f, 511.0f, 320.0f, D_8010F534_thwomp_pull[0] * 4.0f + 480.0f,
                    511.0f);
        ViewportSet(1, scale * 640.0f, scale * 480.0f, 511.0f, 960.0f, D_8010F534_thwomp_pull[1] * 4.0f + 480.0f,
                    511.0f);
        left[0] = (left[0] - 80) * scale + 80.0f;
        top[0] = (top[0] - 120) * scale + 120.0f;
        right[0] = (right[0] - 80) * scale + 80.0f;
        bottom[0] = (bottom[0] - 120) * scale + 120.0f;
        left[1] = (left[1] - 240) * scale + 240.0f;
        top[1] = (top[1] - 120) * scale + 120.0f;
        right[1] = (right[1] - 240) * scale + 240.0f;
        bottom[1] = (bottom[1] - 120) * scale + 120.0f;
        top[0] += D_8010F534_thwomp_pull[0];
        bottom[0] += D_8010F534_thwomp_pull[0];
        top[1] += D_8010F534_thwomp_pull[1];
        bottom[1] += D_8010F534_thwomp_pull[1];
        func_80107FF4_thwomp_pull(left, top, right, bottom);
    }
    if (!omPauseChk()) {
        s32 shake;

        shake = D_8010F564_thwomp_pull[0];
        D_8010F534_thwomp_pull[0] = ((shake & 1) ? -shake : shake) * 0.5;
        D_8010F564_thwomp_pull[0] -= (D_8010F564_thwomp_pull[0] != 0) ? 1 : 0;
        shake = D_8010F564_thwomp_pull[1];
        D_8010F534_thwomp_pull[1] = ((shake & 1) ? -shake : shake) * 0.5;
        D_8010F564_thwomp_pull[1] -= (D_8010F564_thwomp_pull[1] != 0) ? 1 : 0;
    }
}

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

void func_801097AC_thwomp_pull(omObjData *object, s8 group) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 files[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 shadowFiles[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 motionFiles[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    s32 attr;
    u16 i;
    u16 chr;

    attr = 0x8B9;
    for (i = 0; i < ((group != 0) ? 3 : 1); i++) {
        chr = D_8010F4F8_thwomp_pull[group + i]->chr;
        object->model[i + 1] = func_8000B108_main((dirs[chr] << 16) | files[chr], attr);
        Hu3DModelCameraSet(object->model[i + 1], (group != 0) ? 2 : 1);
        object->model[i + 39] = func_8000B108_main((dirs[chr] << 16) | shadowFiles[chr], 0x8AD);
        Hu3DModelCameraSet(object->model[i + 39], (group != 0) ? 2 : 1);
        D_8010F4F8_thwomp_pull[group + i]->unk_06 = func_80017790_main(
            object->model[i + 39], 1, slots[chr], (dirs[chr] << 16) | motionFiles[0][chr]);
        D_8010F4F8_thwomp_pull[group + i]->unk_08 =
            func_80017AD8_main((dirs[chr] << 16) | motionFiles[1][chr]);
        func_80033910_main(Hu3DData[object->model[i + 39]].hmf);
        func_8001C514_main(object->model[i + 39]);
        D_8010F4F8_thwomp_pull[group + i]->unk_0C = (rand8() & 1) ? 0x2F : 0x30;
        func_8000B460_main(object, i, func_80017BB8_main(chr, 0));
        func_8000B460_main(object, i + 3, func_80017BB8_main(chr, 0x84));
        func_8000B460_main(object, i + 6, func_80017BB8_main(chr, 0x21));
        func_8000B460_main(object, i + 12, func_80017BB8_main(chr, 4));
        func_8000B460_main(object, i + 15, func_80017BB8_main(chr, 0x1F));
        func_8000B460_main(object, i + 9, func_80017BB8_main(chr, D_8010F4F8_thwomp_pull[group + i]->unk_0C));
        D_8010F4F8_thwomp_pull[group + i]->unk_0C |= dirs[chr] << 16;
        D_8010F578_thwomp_pull[group + i] = (group != 0) ? (1 - i) * 125 : 0.0f;
        D_8010F510_thwomp_pull[group + i] = 25.0f;
        D_8010F540_thwomp_pull[group + i] = (group != 0) ? -((i % 2) * 20) : 0.0f;
        Hu3DModelPosSet(object->model[i + 1], D_8010F578_thwomp_pull[group + i], D_8010F510_thwomp_pull[group + i],
                        D_8010F540_thwomp_pull[group + i]);
        Hu3DModelRotSet(object->model[i + 1], 0.0f, 180.0f, 0.0f);
        func_8001C5B4_main(object->model[i + 1], object->motion[i + 3]);
        func_8001C814_main(object->model[i + 1], 3, 1);
        func_8001C5B4_main(object->model[i + 39], object->motion[i + 3]);
        func_8001C2FC_main(object->model[1], 0x600, 0x400);
    }

    attr = 0x8B9;
    object->model[7] = func_8000B108_main((group == 0) ? 0x290009 : 0x29000A, attr);
    Hu3DModelCameraSet(object->model[7], (group != 0) ? 2 : 1);
    Hu3DModelPosSet(object->model[7], 0.0f, 0.0f, (group != 0) ? -25.0f : 35.0f);
    Hu3DModelRotSet(object->model[7], 0.0f, 180.0f, 0.0f);

    attr = 0xAB9;
    for (i = 0; i < 3; i++) {
        object->model[i + 8] = func_8000B108_main(0x290007, attr);
        Hu3DModelCameraSet(object->model[i + 8], (group != 0) ? 2 : 1);
        func_8001C814_main(object->model[i + 8], 3, 1);
        func_8001FDE8_main(object->model[i + 8]);
    }
    if (group == 0) {
        func_8000B460_main(object, 20, 0x290008);
        func_8001C5B4_main(object->model[8], object->motion[20]);
        D_8010F528_thwomp_pull = func_80016784_main(object->model[8], 1);
        Hu3DModelKill(object->motion[20]);
    }
    for (i = 0; i < 3; i++) {
        func_8001C5B4_main(object->model[i + 8], D_8010F568_thwomp_pull[0]->motion[20]);
    }

    attr = 0x8B9;
    for (i = 0; i < 3; i++) {
        if (group == 0 && i == 0) {
            object->model[4] = func_8000B108_main(0x290012, attr);
        } else {
            object->model[i + 4] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[4]);
        }
        Hu3DModelPosSet(object->model[i + 4], (1 - i) * (group * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[i + 4], 0.0f, 180.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 4], group * 0.5 + 1.0, group * 0.5 + 1.0, group * 0.5 + 1.0);
        Hu3DModelCameraSet(object->model[i + 4], (group != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[i + 4], 0x600, 0);
    }

    attr = 0xABD;
    for (i = 0; i < 3; i++) {
        s32 lightFiles[2][3] = { { 0x13, 0x14, 0x15 }, { 0x16, 0x17, 0x18 } };

        object->model[i + 46] = func_8000B108_main(lightFiles[group][i] | 0x290000, attr);
        Hu3DModelPosSet(object->model[i + 46], (1 - i) * (group * 60 + 200), 0.0f, -300.0f);
        Hu3DModelRotSet(object->model[i + 46], -16.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[i + 46], group * 0.5 + 1.0, group * 0.5 + 1.0, group * 0.5 + 1.0);
        Hu3DModelCameraSet(object->model[i + 46], (group != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[i + 46], 0x600, 0);
        func_8001C2FC_main(object->model[i + 46], 0x70000000, 0x70000000);
        Hu3DLLightCreate(object->model[i + 46], 1);
        Hu3DLLightColorSet(object->model[i + 46], 255, 255, 255);
        Hu3DLLightDirSet(object->model[i + 46], 0.0f, 0.0f, 127.0f);
    }

    attr = 0x8BD;
    for (i = 0; i < 3; i++) {
        if (group == 0) {
            object->model[i + 30] =
                func_8000B108_main((i == 0) ? 0x29000B : (i == 1) ? 0x29000C
                                                                  : 0x29000D,
                                   attr);
        } else {
            object->model[i + 30] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[i + 30]);
        }
        Hu3DModelPosSet(object->model[i + 30],
                        ((1 - i) * 175 + 50) - (i == 2) * ((group == 0) ? 10 : 60), 300.0f, -300.0f);
        Hu3DModelScaleSet(object->model[i + 30], 1.6820346f, 1.6820346f, 1.6820346f);
        func_8001C2FC_main(object->model[i + 30], 0x70000000, 0x70000000);
        Hu3DModelCameraSet(object->model[i + 30], (group != 0) ? 2 : 1);
    }

    if (group >= 0) {
        object->model[33] = func_8000B108_main(0x29001C, 0x4DD);
    } else {
        object->model[33] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[33]);
    }
    Hu3DModelCameraSet(object->model[33], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[33], 4.0f, 4.0f, 4.0f);
    Hu3DModelRotSet(object->model[33], 0.0f, 45.0f, 0.0f);
    func_8001FDE8_main(object->model[33]);
    if (group == 0) {
        func_8000B460_main(object, 18, 0x29001D);
        func_8001C5B4_main(object->model[33], object->motion[18]);
        D_8010F5AC_thwomp_pull[0] = func_80016784_main(object->model[33], 2);
        Hu3DModelKill(object->motion[18]);
        func_8000B460_main(object, 19, 0x29001E);
        func_8001C5B4_main(object->model[33], object->motion[19]);
        D_8010F5AC_thwomp_pull[1] = func_80016784_main(object->model[33], 2);
        Hu3DModelKill(object->motion[19]);
    }
    func_8001C5B4_main(object->model[33], D_8010F568_thwomp_pull[0]->motion[18]);
    func_80016FB4_main(object->model[33], D_8010F5AC_thwomp_pull[0], 0);

    object->model[34] = func_8000B108_main(0x29001A, 0x8DD);
    Hu3DModelCameraSet(object->model[34], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[34], 1.0f, 1.0f, 1.0f);
    func_8001C814_main(object->model[34], 3, 1);
    func_8001C2FC_main(object->model[34], 0x600, 0x400);

    object->model[36] = func_8000B108_main(0x29001B, 0x8CD);
    Hu3DModelCameraSet(object->model[36], (group != 0) ? 2 : 1);
    Hu3DModelScaleSet(object->model[36], 2.5f, 2.5f, 2.5f);
    func_8001C2FC_main(object->model[36], 0x600, 0x400);

    for (i = 0; i < 1; i++) {
        object->model[35] = func_8000B108_main(0x29001A, 0x8CD);
        func_8001FA68_main(object->model[35]);
        func_8001F9E4_main(object->model[35], 255);
        Hu3DModelCameraSet(object->model[i + 35], (group != 0) ? 2 : 1);
        Hu3DModelScaleSet(object->model[i + 35], 0.25f, 0.25f, 0.25f);
        func_8001C814_main(object->model[i + 35], 3, 1);
        func_8001C2FC_main(object->model[i + 35], 0x600, 0x400);
    }

    object->model[38] = func_8000B108_main(9, 0x4CD);
    Hu3DModelScaleSet(object->model[38], 3.5f, 3.5f, 3.0f);
    Hu3DModelCameraSet(object->model[38], (group != 0) ? 2 : 1);
    func_8001FA68_main(object->model[38]);
    func_8001F9E4_main(object->model[38], 128);

    for (i = 0; i < group * 2 + 1; i++) {
        if (i == 0) {
            object->model[42] = func_8000B108_main(9, 0x4C9);
            func_8001FA68_main(object->model[42]);
            func_8001F9E4_main(object->model[42], 128);
            Hu3DModelLayerSet(object->model[42], 0x800);
        } else {
            object->model[i + 42] = Hu3DModelLink(object->model[42]);
        }
        Hu3DModelPosSet(object->model[i + 42], D_8010F578_thwomp_pull[group + i], 28.0f,
                        D_8010F540_thwomp_pull[group + i]);
        Hu3DModelCameraSet(object->model[i + 42], (group != 0) ? 2 : 1);
    }

    if (group == 0) {
        object->model[22] = func_8000B108_main(0x290003, 0x4BD);
    } else {
        object->model[22] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[22]);
    }
    Hu3DModelCameraSet(object->model[22], (group != 0) ? 2 : 1);
    Hu3DLLightCreate(object->model[22], 1);
    Hu3DLLightColorSet(object->model[22], 255, 255, 255);
    Hu3DLLightDirSet(object->model[22], 0.0f, 0.0f, 127.0f);

    for (i = 0; i < 4; i++) {
        if (group == 0 && i == 0) {
            object->model[18] = func_8000B108_main(0x290004, 0x4BD);
        } else {
            object->model[i + 18] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[18]);
        }
        Hu3DModelCameraSet(object->model[i + 18], (group != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[i + 18], 0x600, 0);
        Hu3DLLightCreate(object->model[i + 18], 1);
        Hu3DLLightColorSet(object->model[i + 18], 255, 255, 255);
        Hu3DLLightDirSet(object->model[i + 18], 0.0f, 0.0f, 127.0f);
    }

    if (group == 0) {
        object->model[23] = func_8000B108_main(0x290005, 0x4DD);
    } else {
        object->model[23] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[23]);
    }
    Hu3DModelCameraSet(object->model[23], (group != 0) ? 2 : 1);
    Hu3DLLightCreate(object->model[23], 1);
    Hu3DLLightColorSet(object->model[23], 255, 255, 255);
    Hu3DLLightDirSet(object->model[23], 0.0f, 0.0f, 127.0f);

    attr = 0x41D;
    for (i = 0; i < 2; i++) {
        object->model[i + 24] = func_8000B108_main((group == 0) ? 0x29000E : 0x29000F, attr);
        Hu3DModelCameraSet(object->model[i + 24], (group != 0) ? 2 : 1);
    }
    func_8001C258_main(object->model[24], 4, 0);
    Hu3DModelPosSet(object->model[24], 0.0f, 0.0f, -315.0f);

    object->model[11] = func_8000B108_main((group == 0) ? 0x290010 : 0x290011, 0x4D9);
    Hu3DModelPosSet(object->model[11], 0.0f, 10.0f, 0.0f);
    Hu3DModelScaleSet(object->model[11], 1.0f, 1.0f, 12.0f);
    func_8001C2FC_main(object->model[11], 0x600, 0);
    Hu3DModelCameraSet(object->model[11], (group != 0) ? 2 : 1);

    attr = 0x6CD;
    for (i = 0; i < 3; i++) {
        object->model[i + 49] = func_8000B108_main(0x290019, attr);
        Hu3DModelCameraSet(object->model[i + 49], (group != 0) ? 2 : 1);
        Hu3DModelScaleSet(object->model[i + 49], group * 0.5 + 1.75, group * 0.5 + 1.75, group * 0.5 + 1.75);
    }

    if (group == 0) {
        object->model[16] = func_8000B108_main(0x290000, 0x45D);
    } else {
        object->model[16] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[16]);
    }
    Hu3DModelCameraSet(object->model[16], (group != 0) ? 2 : 1);
    func_8001C2FC_main(object->model[16], 0x600, 0);

    for (i = 0; i < 4; i++) {
        if (group == 0 && i == 0) {
            object->model[12] = func_8000B108_main(0x290001, 0x41D);
        } else {
            object->model[i + 12] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[12]);
        }
        Hu3DModelCameraSet(object->model[i + 12], (group != 0) ? 2 : 1);
        func_8001C2FC_main(object->model[i + 12], 0x600, 0);
        func_8001C2FC_main(object->model[i + 12], 0x600, 0);
    }

    if (group == 0) {
        object->model[17] = func_8000B108_main(0x290002, 0x45D);
    } else {
        object->model[17] = Hu3DModelLink(D_8010F568_thwomp_pull[0]->model[17]);
    }
    Hu3DModelCameraSet(object->model[17], (group != 0) ? 2 : 1);
    func_8001C2FC_main(object->model[17], 0x600, 0);
}

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
