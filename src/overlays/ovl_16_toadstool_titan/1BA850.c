#include "common.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

typedef struct ToadstoolTitanPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 playerNo;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ToadstoolTitanPlayer; // sizeof 0x10

extern s32 D_800A178C_main[][6];
extern s16 D_800CDBC8_main;
extern s16 D_800D037E_main;
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern omObjData *D_800D6A40_main;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern u8 D_800CD6A6_main;
extern ToadstoolTitanPlayer D_8010F528_toadstool_titan[4];
extern ToadstoolTitanPlayer *D_8010F568_toadstool_titan[4]; // players indexed by group
extern u32 D_8010F580_toadstool_titan;
extern u8 D_8010F584_toadstool_titan;
extern s16 D_8010F586_toadstool_titan;
extern s16 D_8010F588_toadstool_titan[1];
extern Gfx D_8010EDF0_toadstool_titan[];
extern Gfx *gMainGfxPos;
extern s8 D_8010F58A_toadstool_titan;
extern D_80111B50_vine_with_me_Struct D_8010F590_toadstool_titan;
extern u16 D_8010F5BC_toadstool_titan;
extern u8 D_8010F5F4_toadstool_titan;
extern omObjData *D_8010F5F8_toadstool_titan;
extern s16 D_8010F5FC_toadstool_titan;
extern s16 D_8010F60C_toadstool_titan[1];
extern s8 D_8010F60E_toadstool_titan;
extern u8 D_8010F614_toadstool_titan[2];
extern u8 D_8010F616_toadstool_titan[4];
extern s32 D_8010F61C_toadstool_titan;
extern omObjData *D_8010F640_toadstool_titan[4];
extern u8 D_8010F650_toadstool_titan[9];
extern u8 D_8010F65D_toadstool_titan[4];         // group of each player
extern u8 D_8010F668_toadstool_titan[4];         // start corner of each group
extern u8 D_8010F66C_toadstool_titan;            // number of human players
extern u8 D_8010EDA0_toadstool_titan;            // number of mushrooms created so far
extern s32 D_8010EE38_toadstool_titan;           // set once the camera has been initialized
extern Vec D_8010F5C0_toadstool_titan;           // camera target
extern omObjData *D_8010F5D0_toadstool_titan[9]; // mushroom objects
extern f32 D_8010F600_toadstool_titan;           // music volume
extern f32 D_8010F624_toadstool_titan;           // camera fov
extern Vec D_8010F628_toadstool_titan;           // camera position

const s16 D_8010EE80_toadstool_titan[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C,
    0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279,
    0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x0000, 0x0000
};

void func_80105E50_toadstool_titan(omObjData *object);
void func_801060AC_toadstool_titan(omObjData *object);
void func_80106984_toadstool_titan(void);
void func_801069DC_toadstool_titan(omObjData *object);
void func_80106C98_toadstool_titan(omObjData *object);
void func_80107360_toadstool_titan(omObjData *object);
void func_8010B658_toadstool_titan(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void func_8010B99C_toadstool_titan(omObjData *object);
void func_8010BA80_toadstool_titan(omObjData *object);
void func_8010BB64_toadstool_titan(omObjData *object);
void func_8010BC48_toadstool_titan(omObjData *object);
void func_8010B510_toadstool_titan(omObjData *object);
void func_8010BD2C_toadstool_titan(omObjData *object);

void func_801059A0_toadstool_titan(void) {
    omObjData *object;
    s32 i;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(1);
    D_800CD6A6_main = func_8000B638_main();
    ScissorSet(D_800CD6A6_main, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_800CD6A6_main, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB73C_minigame = 15.0f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    func_800E19F0_minigame(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 73.0f, 95.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightDirSet(1, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    omAddObj(0, 0, 0, -1, func_80105E50_toadstool_titan);
    func_800E1490_minigame(D_800EBE28_minigame);
    object = omAddObj(4, 58, 58, -1, func_80106C98_toadstool_titan);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010F5F8_toadstool_titan = object;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 9; i++) {
        D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010F5D0_toadstool_titan[i] = omAddObj(2, 2, 2, -1, func_801069DC_toadstool_titan);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[0] = omAddObj(3, 12, 60, -1, func_8010B99C_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[1] = omAddObj(3, 12, 60, -1, func_8010BA80_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[2] = omAddObj(3, 12, 60, -1, func_8010BB64_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[3] = omAddObj(3, 12, 60, -1, func_8010BC48_toadstool_titan);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010B510_toadstool_titan), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(0xFF, 30);
    func_80045010_main(D_8010EE80_toadstool_titan, 1);
    D_8010F590_toadstool_titan.unk01 = 0;
    D_8010F590_toadstool_titan.unk1C = 45;
    D_8010F590_toadstool_titan.unk1E = 1800;
    D_8010F590_toadstool_titan.unk03 = 2;
    D_8010F590_toadstool_titan.unk02 = 1;
    D_8010F590_toadstool_titan.unk22 = 60;
    D_8010F590_toadstool_titan.unk24 = 165;
    D_8010F590_toadstool_titan.unk04 = 0;
    D_8010F590_toadstool_titan.unk05 = 0;
    D_8010F590_toadstool_titan.unk20 = -1;
    func_800E5EA0_minigame(&D_8010F590_toadstool_titan);
}

void func_80105E48_toadstool_titan(void) {
}

void func_80105E50_toadstool_titan(omObjData *object) {
    s32 i;
    s32 j;

    D_8010F5BC_toadstool_titan = 0;
    D_8010F5FC_toadstool_titan = 0;
    D_8010F580_toadstool_titan = 0;
    D_8010F58A_toadstool_titan = 5;
    D_8010F584_toadstool_titan = 0;
    D_8010F586_toadstool_titan = 0;
    D_8010F61C_toadstool_titan = 0;
    D_8010F60E_toadstool_titan = -1;
    D_8010F616_toadstool_titan[0] = D_8010F616_toadstool_titan[1] = D_8010F616_toadstool_titan[2] = D_8010F616_toadstool_titan[3] = 0;
    D_8010F5F4_toadstool_titan = 0;
    D_8010F66C_toadstool_titan = 0;
    D_8010F614_toadstool_titan[0] = D_8010F614_toadstool_titan[1] = 0;
    D_8010F600_toadstool_titan = -1.0f;
    for (i = 0; i < 4; i++) {
        D_8010F568_toadstool_titan[i] = &D_8010F528_toadstool_titan[i];
        bzero(D_8010F568_toadstool_titan[i], sizeof(ToadstoolTitanPlayer));
    }
    for (i = 0; i < 4; i++) {
        // j holds the player's group here; a separate variable changes the register allocation.
        j = D_8010F65D_toadstool_titan[i] = GwPlayer[i].group;
        D_8010F568_toadstool_titan[j]->playerNo = i;
        D_8010F568_toadstool_titan[j]->pad = GwPlayer[i].pad;
        D_8010F568_toadstool_titan[j]->chr = GwPlayer[i].chr;
        D_8010F568_toadstool_titan[j]->group = j;
        D_8010F568_toadstool_titan[j]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
        D_8010F66C_toadstool_titan += (D_8010F568_toadstool_titan[j]->cpuDifficulty == -1) ? 1 : 0;
    }
    for (i = 0; i < 4; i++) {
        D_8010F668_toadstool_titan[i] = rand8() & 3;
        for (j = 0; j < i; j++) {
            if (D_8010F668_toadstool_titan[i] == D_8010F668_toadstool_titan[j]) {
                i--;
                break;
            }
        }
    }
    object->func = func_801060AC_toadstool_titan;
}

void func_801060AC_toadstool_titan(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s16 i;

    D_8010F580_toadstool_titan++;
    func_800E6F40_minigame();
    switch (D_8010F5FC_toadstool_titan) {
        case 0:
            if (func_800E6E8C_minigame() == 1) {
                D_8010F5FC_toadstool_titan = 1;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 1:
            if (D_8010F580_toadstool_titan == 61 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x38);
                D_8010F614_toadstool_titan[0] = 1;
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010F5FC_toadstool_titan = 2;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 2:
            if (D_8010F580_toadstool_titan == 1) {
                func_80106984_toadstool_titan();
            }
            if (D_8010F58A_toadstool_titan != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010F58A_toadstool_titan == 5) {
                    D_8010F5FC_toadstool_titan = 6;
                    D_8010F58A_toadstool_titan = 4;
                    if (D_8010F586_toadstool_titan == 5) {
                        D_8010F61C_toadstool_titan = 150;
                    }
                } else {
                    D_8010F5FC_toadstool_titan = 3;
                }
                D_8010F580_toadstool_titan = 0;
            }
            if (D_8010F5FC_toadstool_titan != 3) {
                break;
            }
        case 3:
            if (D_8010F580_toadstool_titan == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010F590_toadstool_titan.unk06 = 0;
                D_8010F590_toadstool_titan.unk18[0] = D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->playerNo;
                GwPlayer[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->playerNo].bonusCoin = 10;
                D_8010F614_toadstool_titan[0] = 0;
                if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A7C4_main(60);
                    D_8010F614_toadstool_titan[1] = 0;
                }
            }
            if (D_8010F580_toadstool_titan == 2) {
                func_800E6F34_minigame(30);
                D_8010F590_toadstool_titan.unk22 = 60;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F5FC_toadstool_titan = 4;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 6:
            if (D_8010F580_toadstool_titan == 1) {
                D_8010F590_toadstool_titan.unk06 = 4;
                D_8010F590_toadstool_titan.unk22 = 90;
                D_8010F590_toadstool_titan.unk24 = 0x90;
                D_8010F614_toadstool_titan[0] = 0;
                if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A7C4_main(60);
                    D_8010F614_toadstool_titan[1] = 0;
                }
            }
            if (D_8010F580_toadstool_titan == 64 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqStop();
            }
            if (D_8010F580_toadstool_titan == 67 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A72C_main(3);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F5FC_toadstool_titan = 5;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 4:
            if (D_8010F580_toadstool_titan == 24 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqStop();
            }
            if (D_8010F580_toadstool_titan == 27 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A72C_main(3);
            }
            if (D_8010F580_toadstool_titan == 29) {
                if (D_8010F586_toadstool_titan == 9) {
                    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                    func_80017954_main(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->model[0], 1,
                                       slots[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr],
                                       D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unk_08);
                    func_800E5A00_minigame(
                        D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 13,
                        func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr, (rand8() & 1) ? 0x2F : 0x30), 1, 120);
                    func_80045ED0_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unk_0C);
                    msmMusStop(D_800D037E_main);
                }
            }
            if (D_8010F580_toadstool_titan == 30 && D_8010F586_toadstool_titan == 9) {
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 13);
            }
        case 5:
            if (D_8010F5FC_toadstool_titan == 5) {
                if (D_8010F580_toadstool_titan == 1) {
                    for (i = 0; i < 4; i++) {
                        func_800E5A00_minigame(D_8010F640_toadstool_titan[i], 14, func_80017BB8_main(D_8010F568_toadstool_titan[i]->chr, 0x3A), 1,
                                               120);
                    }
                    msmMusStop(D_800D037E_main);
                }
                if (D_8010F5FC_toadstool_titan == 5 && D_8010F580_toadstool_titan >= 2) {
                    for (i = 0; i < 4; i++) {
                        data = D_8010F640_toadstool_titan[i]->data;
                        if (data->unk5C != 0x1000 && data->unk38 == 1000.0f) {
                            data->unk3C = 0.0f;
                            func_800E5690_minigame(D_8010F640_toadstool_titan[i], 14);
                        }
                    }
                }
            }
            if (func_800E6E8C_minigame() == 5) {
                D_8010F5FC_toadstool_titan = 7;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 7:
            if (D_8010F580_toadstool_titan == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010F580_toadstool_titan >= 32) {
                D_8010F5BC_toadstool_titan = 1;
            }
            break;
    }
    if (D_8010F5BC_toadstool_titan != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010F584_toadstool_titan == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004A7C4_main(20);
                func_8004AB0C_main(20);
            }
            D_8010F584_toadstool_titan++;
            if (D_8010F584_toadstool_titan == 21 && D_800D6A40_main != NULL) {
                msmMusStop(D_800CDBC8_main);
                msmMusStop(D_800D037E_main);
            }
            if (D_8010F584_toadstool_titan == 23 && D_800D6A40_main != NULL && D_8010F600_toadstool_titan != -1.0f) {
                msmMusSetVolume(D_800CDBC8_main, D_8010F600_toadstool_titan);
            }
            if (D_8010F584_toadstool_titan < 25) {
                return;
            }
        }
        msmMusStop(D_800CDBC8_main);
        msmMusStop(D_800D037E_main);
        omOvlReturnEx(1);
    }
}

void func_80106984_toadstool_titan(void) {
    UnkAudioObjData *data;

    if (D_800D6A40_main != NULL) {
        data = D_800D6A40_main->data;
        D_8010F600_toadstool_titan = data->unk24 = data->unk2C = func_800037C4_main(D_800CDBC8_main);
    }
}

void func_801069DC_toadstool_titan(omObjData *object) {
    f32 xs[9] = { 0.0f, 110.0f, 250.0f, 250.0f, 110.0f, -110.0f, -250.0f, -250.0f, -110.0f };
    f32 zs[9] = { 0.0f, -230.0f, -110.0f, 110.0f, 240.0f, 240.0f, 110.0f, -110.0f, -230.0f };
    D_800EC1C0_minigame_ObjData *work;

    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[0] = func_8000B108_main(0x370000, 0xBD);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[0]);
    }
    omSetTra(object, xs[D_8010EDA0_toadstool_titan] * 1.11, 375.0f, zs[D_8010EDA0_toadstool_titan] * 1.11 + 20.0);
    omSetSca(object, 0.6666667f, 0.6666667f, 0.6666667f);
    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[1] = func_8000B108_main(0x370001, 0xBD);
    } else {
        object->model[1] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[1]);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E13CC_minigame(object, 50.0f, 100.0f, -60.0f, -60.0f, 60.0f,
                           (D_8010EDA0_toadstool_titan >= 4 && D_8010EDA0_toadstool_titan < 6) ? 120.0f : 60.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    work->unk04 = D_8010EDA0_toadstool_titan + 1;
    D_8010F650_toadstool_titan[D_8010EDA0_toadstool_titan] = 0;
    D_8010EDA0_toadstool_titan++;
    object->func = NULL;
}

void func_80106C98_toadstool_titan(omObjData *object) {
    s32 spriteFiles[1] = { 0x37000C };
    D_800EC1C0_minigame_ObjData *work;
    s16 i;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E139C_minigame(object, 0.0f, -475.0f, -425.0f, 475.0f, 425.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    func_800E1468_minigame(object);
    work->unk04 = 0;
    for (i = 0; i < 1; i++) {
        D_8010F588_toadstool_titan[i] = espEntry(D_8010F60C_toadstool_titan[i] = func_8000B838_main(spriteFiles[i]), 0, 0);
        espDispOff(D_8010F588_toadstool_titan[i]);
    }
    object->model[1] = func_8000B108_main(0x370002, 0x4BD);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    Hu3DModelRotSet(object->model[1], -23.0f, 0.0f, 0.0f);
    object->model[3] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(object->model[3]);
    for (i = 1; i < 5; i++) {
        object->model[3 + i] = Hu3DModelLink(object->model[3]);
    }
    object->model[2] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(object->model[2]);
    for (i = 0; i < 3; i++) {
        HmfModel *modelP;

        object->model[26 + i] = func_8000B108_main(0x1001F, 0x8BD);
        Hu3DModelScaleSet(object->model[26 + i], 2.5f, 2.5f, 2.5f);
        func_8001C2FC_main(object->model[26 + i], 0x70000000, 0x70000000);
        modelP = &Hu3DData[object->model[26 + i]];
        modelP->motSpeed = 1.55f;
    }
    for (i = 0; i < 14; i++) {
        s32 files[6] = { 4, 5, 6, 7, 8, 9 };
        f32 scale = 0.5f;

        if (i < 6) {
            object->model[29 + i] = func_8000B108_main(files[(s16)(i % 6)] | 0x370000, 0x4BD);
        } else {
            object->model[29 + i] = Hu3DModelLink(object->model[29 + (s16)(i % 6)]);
        }
        func_8001C2FC_main(object->model[29 + i], 0x70000000, 0x70000000);
        if (i == 0) {
            object->model[43] = func_8000B108_main(9, 0xBD);
        } else {
            object->model[43 + i] = Hu3DModelLink(object->model[43]);
        }
        Hu3DModelScaleSet(object->model[29 + i], scale, scale, scale);
        scale = 0.875f;
        Hu3DModelScaleSet(object->model[43 + i], scale, scale, scale);
    }
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            object->model[8] = func_8000B108_main(0x37000A, 0x8BD);
        } else {
            object->model[8 + i] = Hu3DModelLink(object->model[8]);
        }
        Hu3DModelPosSet(object->model[8 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y + 25.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z + 125.0f);
        Hu3DModelRotSet(object->model[8 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[8 + i], 2.5f, 2.5f, 2.5f);
        object->model[17 + i] = func_8000B108_main(0x37000B, 0x8BD);
        Hu3DModelPosSet(object->model[17 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y - 100.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z);
        Hu3DModelRotSet(object->model[17 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[17 + i], 0.75f, 0.75f, 0.75f);
    }
    object->model[57] = func_8000B108_main(0x37000A, 0x8BD);
    Hu3DModelScaleSet(object->model[57], 2.0f, 2.0f, 2.0f);
    object->func = func_80107360_toadstool_titan;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF88_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80107360_toadstool_titan);

void func_8010AD8C_toadstool_titan(s16 left, s16 top, s16 right, s16 bottom) {
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *sprite;
    f32 scaleX;
    f32 scaleY;
    f32 offsetX;
    f32 offsetY;
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 dsdx;
    s32 dtdy;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;

    scaleX = (right - left) / 320.0;
    offsetX = left;
    dsdx = (1.0 / scaleX) * 1024.0;
    scaleY = (bottom - top) / 240.0;
    offsetY = top;
    dtdy = (1.0 / scaleY) * 1024.0;

    gSPDisplayList(gMainGfxPos++, D_8010EDF0_toadstool_titan);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(D_800CD1DC_main[D_8010F588_toadstool_titan[0]].unk04, 0);
    frame = &sprite->unk_84->unk00[sprite->unk_90];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
    for (i = 0; i < 6; i++) {
        t0 = i * 40;
        t1 = t0 + 40.0f + ((i == 5) ? -0.75 : 1.0);
        for (j = 0; j < 8; j++) {
            s0 = j * 40;
            s1 = s0 + 40.0f + ((j < 7) ? 1.0f : 0.0f);
            xl = (scaleX * s0 + offsetX) * 4.0f;
            yl = (scaleY * t0 + offsetY) * 4.0f;
            xh = (scaleX * s1 + offsetX) * 4.0f;
            yh = (scaleY * t1 + offsetY) * 4.0f;
            if (xl > 1280 || yl > 960) {
                continue;
            }
            if (xh < 0 || yh < 0) {
                continue;
            }
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 240, (s32)s0, (s32)t0, (s32)s1,
                               (s32)t1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s0 * 32.0f, t0 * 32.0f, dsdx, dtdy);
        }
    }
}

void func_8010B4D4_toadstool_titan(s16 model, s16 time) {
    Hu3DMotionTimeSet(model, time);
}

void func_8010B510_toadstool_titan(omObjData *object) {
    Vec up;

    if (D_8010EE38_toadstool_titan == 0) {
        D_8010EE38_toadstool_titan = 1;
        D_8010F628_toadstool_titan.x = 0.0f;
        D_8010F628_toadstool_titan.y = 868.0f;
        D_8010F628_toadstool_titan.z = 1561.0f;
        D_8010F5C0_toadstool_titan.x = 0.0f;
        D_8010F5C0_toadstool_titan.y = -100.0f;
        D_8010F5C0_toadstool_titan.z = -485.0f;
        D_8010F624_toadstool_titan = 32.5f;
    }
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    D_800CE17C_main[0] = D_8010F628_toadstool_titan.x;
    D_800CE17C_main[1] = D_8010F628_toadstool_titan.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPerspectiveSet(0, D_8010F624_toadstool_titan, 800.0f, 2750.0f);
    Hu3DCameraPosSetV(0, &D_8010F628_toadstool_titan, &D_8010F5C0_toadstool_titan, &up);
    Hu3DCamUpdateMtx(0);
}

void func_8010B658_toadstool_titan(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 files[2][8] = { { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B }, { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C } };
    func_800E1BA8_minigame_ObjData *data;
    s32 modelFlags;
    s32 motionFlags;
    u16 chr;

    modelFlags = 0x4A9;
    motionFlags = 0x99;
    chr = D_8010F568_toadstool_titan[group]->chr;
    func_800E18D8_minigame();
    func_800E1BA8_minigame(object, model, motion, D_8010F568_toadstool_titan[group]->playerNo, modelFlags, motionFlags);
    omSetTra(object, x, y, z);
    Hu3DModelPosSet(object->model[1], x, 0.0f, z);
    data = object->data;
    data->unk59 = D_8010F568_toadstool_titan[group]->playerNo;
    D_8010F568_toadstool_titan[group]->unk_0C = (rand8() & 1) ? 0x2F : 0x30;
    D_8010F568_toadstool_titan[group]->unk_0C |= dirs[chr] << 16;
    D_8010F568_toadstool_titan[group]->unk_06 = func_80017790_main(object->model[0], 1, slots[chr], (dirs[chr] << 16) | files[0][chr]);
    D_8010F568_toadstool_titan[group]->unk_08 = func_80017AD8_main((dirs[chr] << 16) | files[1][chr]);
    func_80033910_main(Hu3DData[object->model[0]].hmf);
    func_8001C514_main(object->model[0]);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5978_minigame(object, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E149C_minigame(object, 0, 2);
}

void func_8010B99C_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[0]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[0]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 0, (D_8010F668_toadstool_titan[0] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[0] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BA80_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[1]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[1]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 1, (D_8010F668_toadstool_titan[1] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[1] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BB64_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[2]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[2]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 2, (D_8010F668_toadstool_titan[2] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[2] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BC48_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[3]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[3]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 3, (D_8010F668_toadstool_titan[3] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[3] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F278_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BD2C_toadstool_titan);
