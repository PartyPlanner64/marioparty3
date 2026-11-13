#include "common.h"
#include "overlays/minigame.h"

typedef struct RidiculousRelayPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ s32 unk08; // run animation file
} RidiculousRelayPlayer;  // sizeof 0xC

extern D_80111B50_vine_with_me_Struct D_80110CB0_ridiculous_relay;
extern Gfx D_80110CD8_ridiculous_relay[];
extern u8 D_80110D68_ridiculous_relay;
extern RidiculousRelayPlayer D_80111940_ridiculous_relay[4];
extern RidiculousRelayPlayer *D_80111970_ridiculous_relay[4]; // players indexed by group
extern f32 D_80111980_ridiculous_relay[7];
extern f32 D_8011199C_ridiculous_relay[2];
extern f32 D_801119A8_ridiculous_relay[4];
extern u8 D_801119B8_ridiculous_relay[4]; // group of each player
extern omObjData *D_801119BC_ridiculous_relay;
extern s8 D_801119C0_ridiculous_relay;
extern f32 D_801119C4_ridiculous_relay;
extern s32 D_801119C8_ridiculous_relay;
extern u16 D_801119CC_ridiculous_relay;
extern f32 D_801119D0_ridiculous_relay;
extern s32 D_801119D4_ridiculous_relay;
extern s16 D_801119D8_ridiculous_relay;
extern u8 D_801119DA_ridiculous_relay;
extern f32 D_801119DC_ridiculous_relay;
extern s16 D_801119E0_ridiculous_relay[31];
extern omObjData *D_80111A20_ridiculous_relay[4];
extern u16 D_80111A40_ridiculous_relay[5];
extern u16 D_80111A4A_ridiculous_relay;
extern u16 D_80111A4E_ridiculous_relay;
extern s16 D_80111A58_ridiculous_relay[31];
extern s32 D_80111A30_ridiculous_relay[3];
extern f32 D_80111A50_ridiculous_relay;
extern Gfx *gMainGfxPos;

const s16 D_80110E60_ridiculous_relay[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void func_80105D40_ridiculous_relay(omObjData *object);
void func_801066A0_ridiculous_relay(omObjData *object);
void func_8010AE4C_ridiculous_relay(omObjData *object);
void func_8010AE80_ridiculous_relay(omObjData *object);
void func_8010AEAC_ridiculous_relay(omObjData *object);
void func_8010AED8_ridiculous_relay(omObjData *object);

void func_80105F48_ridiculous_relay(omObjData *object);
void func_80106D28_ridiculous_relay(omObjData *object);
void func_80106D4C_ridiculous_relay(omObjData *object);
void func_8010AF04_ridiculous_relay(omObjData *object, s8 group);
void func_8010B4A8_ridiculous_relay(omObjData *object);
void func_80108DE8_ridiculous_relay(Gfx **gfxPos, s32 arg1, s32 arg2);

void func_801059A0_ridiculous_relay(void) {
    omObjData *object;

    func_800142A0_main(0x30);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 22.619865f, 375.0f, 1250.0f);
    Hu3DCameraPerspectiveSet(1, 22.619865f, 375.0f, 1250.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, 0.0f, 40.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 468.75f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 468.75f;
    omAddObj(0, 0, 0, -1, func_80105D40_ridiculous_relay);
    D_801119BC_ridiculous_relay = omAddObj(8, 35, 35, -1, func_801066A0_ridiculous_relay);
    omSetStatBit(D_801119BC_ridiculous_relay, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_80111A20_ridiculous_relay[0] = omAddObj(3, 3, 12, -1, func_8010AE4C_ridiculous_relay);
    D_80111A20_ridiculous_relay[1] = omAddObj(3, 3, 12, -1, func_8010AE80_ridiculous_relay);
    D_80111A20_ridiculous_relay[2] = omAddObj(3, 3, 12, -1, func_8010AEAC_ridiculous_relay);
    D_80111A20_ridiculous_relay[3] = omAddObj(3, 3, 12, -1, func_8010AED8_ridiculous_relay);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80045010_main(D_80110E60_ridiculous_relay, 1);
    WipeCreateIn(0xFF, 16);
    D_80110CB0_ridiculous_relay.unk01 = 2;
    D_80110CB0_ridiculous_relay.unk1C = -1;
    D_80110CB0_ridiculous_relay.unk1C = 45;
    D_80110CB0_ridiculous_relay.unk1E = 9000;
    D_80110CB0_ridiculous_relay.unk03 = 0;
    D_80110CB0_ridiculous_relay.unk02 = 1;
    D_80110CB0_ridiculous_relay.unk22 = 45;
    D_80110CB0_ridiculous_relay.unk24 = 165;
    D_80110CB0_ridiculous_relay.unk04 = 0;
    D_80110CB0_ridiculous_relay.unk05 = 0;
    D_80110CB0_ridiculous_relay.unk20 = -1;
    func_800E5EA0_minigame(&D_80110CB0_ridiculous_relay);
}

void func_80105D40_ridiculous_relay(omObjData *object) {
    s32 group;
    s32 i;

    D_801119CC_ridiculous_relay = 0;
    D_801119D8_ridiculous_relay = 0;
    D_801119D4_ridiculous_relay = 0;
    D_801119C8_ridiculous_relay = 0;
    D_801119C0_ridiculous_relay = 5;
    D_801119DA_ridiculous_relay = 0;
    D_8011199C_ridiculous_relay[0] = D_8011199C_ridiculous_relay[1] = 0.0f;
    D_801119C4_ridiculous_relay = 0.0f;
    D_80111A50_ridiculous_relay = 0.0f;
    D_801119DC_ridiculous_relay = 0.0f;
    D_801119D0_ridiculous_relay = 0.0f;
    D_801119A8_ridiculous_relay[0] = D_801119A8_ridiculous_relay[1] = D_801119A8_ridiculous_relay[2] = D_801119A8_ridiculous_relay[3] = 0.0f;
    D_80111980_ridiculous_relay[0] = D_80111980_ridiculous_relay[1] = D_80111980_ridiculous_relay[2] = D_80111980_ridiculous_relay[3] =
        D_80111980_ridiculous_relay[4] = D_80111980_ridiculous_relay[5] = D_80111980_ridiculous_relay[6] = 0.0f;
    D_80111A30_ridiculous_relay[0] = D_80111A30_ridiculous_relay[1] = D_80111A30_ridiculous_relay[2] = -1;
    for (i = 0; i < 4; i++) {
        D_80111970_ridiculous_relay[i] = &D_80111940_ridiculous_relay[i];
        bzero(D_80111970_ridiculous_relay[i], sizeof(RidiculousRelayPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        D_801119B8_ridiculous_relay[i] = group;
        D_80111970_ridiculous_relay[group]->playerNo = i;
        D_80111970_ridiculous_relay[group]->pad = GwPlayer[i].pad;
        D_80111970_ridiculous_relay[group]->chr = GwPlayer[i].chr;
        D_80111970_ridiculous_relay[group]->group = group;
        D_80111970_ridiculous_relay[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, func_80108DE8_ridiculous_relay, 2);
    object->func = func_80105F48_ridiculous_relay;
}

void func_80105F48_ridiculous_relay(omObjData *object) {
    s32 i;
    u8 j;

    D_801119D4_ridiculous_relay++;
    D_801119C8_ridiculous_relay++;
    if (D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay == 31 && D_801119CC_ridiculous_relay == 0 && D_800D530C_main == 0) {
        HuAudSeqPlay(0x32);
    }
    func_800E6F40_minigame();
    switch (D_801119D8_ridiculous_relay) {
        case 0:
            if (D_801119D4_ridiculous_relay == 1 && D_801119CC_ridiculous_relay == 0 && D_800D530C_main == 0) {
                D_80111A30_ridiculous_relay[0] = HuAudFXPlay(0x32D);
                D_80111A30_ridiculous_relay[1] = HuAudFXPlay(0x32E);
            }
            if (func_800E6E8C_minigame() == 1) {
                D_801119D8_ridiculous_relay = 1;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 1:
            if (func_800E6E8C_minigame() == 2) {
                D_801119D8_ridiculous_relay = 2;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 2:
            if (D_801119C0_ridiculous_relay != 5 || func_800E6E8C_minigame() == 3) {
                if (D_801119C0_ridiculous_relay == 5) {
                    D_801119D8_ridiculous_relay = 5;
                    D_801119C0_ridiculous_relay = 4;
                } else {
                    D_801119D8_ridiculous_relay = 3;
                }
                D_801119D4_ridiculous_relay = 0;
            }
            if (D_801119D8_ridiculous_relay != 3) {
                break;
            }
        case 3:
            if (D_801119D4_ridiculous_relay == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                if (D_80111A30_ridiculous_relay[2] != -1) {
                    HuAudFXStop((s16)D_80111A30_ridiculous_relay[2]);
                    D_80111A30_ridiculous_relay[2] = -1;
                }
                if (D_801119C0_ridiculous_relay == 0) {
                    D_80110CB0_ridiculous_relay.unk06 = 0;
                    D_80110CB0_ridiculous_relay.unk18[0] = D_80111970_ridiculous_relay[0]->playerNo;
                    GwPlayer[D_80111970_ridiculous_relay[0]->playerNo].bonusCoin = 10;
                } else {
                    D_80110CB0_ridiculous_relay.unk06 = 2;
                    D_80110CB0_ridiculous_relay.unk18[0] = D_80111970_ridiculous_relay[3]->playerNo;
                    D_80110CB0_ridiculous_relay.unk18[1] = D_80111970_ridiculous_relay[1]->playerNo;
                    D_80110CB0_ridiculous_relay.unk18[2] = D_80111970_ridiculous_relay[2]->playerNo;
                    GwPlayer[D_80111970_ridiculous_relay[1]->playerNo].bonusCoin = 10;
                    GwPlayer[D_80111970_ridiculous_relay[2]->playerNo].bonusCoin = 10;
                    GwPlayer[D_80111970_ridiculous_relay[3]->playerNo].bonusCoin = 10;
                }
            }
            if (D_801119D4_ridiculous_relay == 2) {
                func_800E6F34_minigame(30);
            }
            if (D_801119D4_ridiculous_relay == 15) {
                for (i = 0; i < 3; i++) {
                    if (D_80111A30_ridiculous_relay[i] != -1) {
                        func_8004AEF0_main(D_80111A30_ridiculous_relay[i], 15);
                        D_80111A30_ridiculous_relay[i] = -1;
                    }
                }
            }
            if (func_800E6E8C_minigame() == 4) {
                D_801119D8_ridiculous_relay = 4;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 5:
            if (D_801119D4_ridiculous_relay == 1) {
                D_80110CB0_ridiculous_relay.unk06 = 4;
                D_80110CB0_ridiculous_relay.unk22 = 75;
                D_80110CB0_ridiculous_relay.unk24 = 0x90;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_801119D8_ridiculous_relay = 6;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 4:
            if (D_801119D4_ridiculous_relay == 30) {
                if (D_801119C0_ridiculous_relay == 0) {
                    func_8001C5B4_main(D_80111A20_ridiculous_relay[0]->model[0], D_80111A20_ridiculous_relay[0]->motion[3]);
                    func_8001C814_main(D_80111A20_ridiculous_relay[0]->model[0], 3, 0);
                    func_80045ED0_main(D_80111970_ridiculous_relay[0]->unk08);
                } else if (D_801119C0_ridiculous_relay == 1) {
                    func_8001C5B4_main(D_80111A20_ridiculous_relay[3]->model[0], D_80111A20_ridiculous_relay[3]->motion[3]);
                    func_8001C814_main(D_80111A20_ridiculous_relay[3]->model[0], 3, 0);
                    func_80045ED0_main(D_80111970_ridiculous_relay[3]->unk08);
                }
            }
        case 6:
            if (func_800E6E8C_minigame() == 5) {
                D_801119D8_ridiculous_relay = 7;
                D_801119D4_ridiculous_relay = 0;
            }
            break;
        case 7:
            if (D_801119D4_ridiculous_relay == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_801119D4_ridiculous_relay >= 32) {
                D_801119CC_ridiculous_relay = 1;
            }
            break;
    }
    if (_CheckFlag(FLAG_MG_PRACTICE) && D_800D530C_main == 0 && D_801119DA_ridiculous_relay == 0 && (u16)D_801119D8_ridiculous_relay == 2) {
        for (j = 0; j < 2; j++) {
            if (D_80111970_ridiculous_relay[j]->cpuDifficulty == -1 && (D_800D5558_main[D_80111970_ridiculous_relay[j]->pad] & R_TRIG)) {
                D_801119DA_ridiculous_relay = 1;
            }
        }
    }
    if (D_801119CC_ridiculous_relay != 0 || D_800D530C_main != 0 || D_801119DA_ridiculous_relay != 0) {
        if (D_800D530C_main != 0 && D_801119DA_ridiculous_relay == 0) {
            D_801119DA_ridiculous_relay = 1;
        }
        if (D_801119DA_ridiculous_relay != 0) {
            if (D_801119DA_ridiculous_relay == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_801119DA_ridiculous_relay++;
            if (D_801119DA_ridiculous_relay < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        omOvlReturnEx(1);
    }
}

s16 func_80106610_ridiculous_relay(s32 file, u16 *sprite, u16 flags) {
    void *data = DataRead(file);
    s16 anim = func_800329B4_main(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, flags, 0);
    D_800CBB60_main[idx].unk_02 = anim;
    return D_800CBB60_main[idx].modelId;
}

void func_801066A0_ridiculous_relay(omObjData *object) {
    s32 files[31] = { 0x28001B, 0x28001C, 0x28001E, 0x28001F, 0x280020, 0x28001D, 0x280021, 0x280022,
                      0x280023, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E,
                      0x21000F, 0x280029, 0x280024, 0x280025, 0x280026, 0x280027, 0x280028, 0x280013,
                      0x280014, 0x280015, 0x280016, 0x280017, 0x280018, 0x280019, 0x28001A };
    s16 i;

    for (i = 0; i < 31; i++) {
        D_80111A58_ridiculous_relay[i] = espEntry(D_801119E0_ridiculous_relay[i] = func_8000B838_main(files[i]), 0, 0);
        espDispOff(D_80111A58_ridiculous_relay[i]);
    }
    object->model[0] = func_8000B108_main(0xA00E7, 0x4B9);
    omSetSca(object, 0.3125f, 0.3125f, 0.3125f);
    Hu3DModelCameraSet(object->model[0], 2);
    object->model[2] = func_8000B108_main(0x28000E, 0x39);
    Hu3DModelPosSet(object->model[2], 3787.5f, -26.25f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[2], 1);
    object->model[3] = func_8000B108_main(0x28000F, 0x4B9);
    Hu3DModelPosSet(object->model[3], 3787.5f, -31.25f, 0.0f);
    Hu3DModelScaleSet(object->model[3], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[3], 2);
    object->model[1] = func_8000B108_main(0x280010, 0x4B9);
    Hu3DModelScaleSet(object->model[1], 0.125f, 0.125f, 0.125f);
    Hu3DModelCameraSet(object->model[1], 2);
    for (i = 0; i < 5; i++) {
        object->model[12 + i] = func_80106610_ridiculous_relay(0x280011, &D_80111A40_ridiculous_relay[i], 0x639);
        Hu3DModelCameraSet(object->model[12 + i], 1);
        Hu3DModelScaleSet(object->model[12 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    for (i = 0; i < 2; i++) {
        object->model[10 + i] = func_80106610_ridiculous_relay(0x280012, &D_80111A4A_ridiculous_relay, 0x639);
        Hu3DModelCameraSet(object->model[10 + i], 1);
        Hu3DModelScaleSet(object->model[10 + i], 0.7565625f, 0.7565625f, 0.7565625f);
    }
    object->model[4] = func_80106610_ridiculous_relay(0xB, &D_80111A4E_ridiculous_relay, 0x639);
    func_8001C258_main(object->model[4], 4, 4);
    Hu3DModelScaleSet(object->model[4], 1.6549804f, 0.9457031f, 0.9457031f);
    Hu3DModelCameraSet(object->model[4], 1);
    for (i = 0; i < 18; i++) {
        if (i == 0) {
            object->model[17] = func_8000B108_main(0x280006, 0x4B9);
        } else {
            object->model[17 + i] = Hu3DModelLink(object->model[17]);
        }
        func_8001C258_main(object->model[17 + i], 4, 4);
        func_8001C2FC_main(object->model[17 + i], 0x70000000, 0x70000000);
        Hu3DModelScaleSet(object->model[17 + i], 0.15625f, 0.15625f, 0.15625f);
        Hu3DModelCameraSet(object->model[17 + i], 2);
    }
    object->model[6] = func_8000B108_main(0x28000C, 0x4B9);
    func_8001C258_main(object->model[6], 4, 4);
    func_8001C814_main(object->model[6], 2, 2);
    Hu3DModelScaleSet(object->model[6], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[6], 2);
    object->model[7] = func_8000B108_main(0x28000D, 0x4B9);
    func_8001C258_main(object->model[7], 4, 4);
    Hu3DModelScaleSet(object->model[7], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[7], 2);
    object->model[8] = Hu3DModelLink(object->model[7]);
    func_8001C258_main(object->model[8], 4, 4);
    Hu3DModelScaleSet(object->model[8], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[8], 2);
    func_8001C814_main(object->model[8], 2, 2);
    object->model[9] = func_8000B108_main(0x28000D, 0x839);
    func_8001C258_main(object->model[9], 4, 4);
    Hu3DModelScaleSet(object->model[9], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[9], 2);
    func_8001C814_main(object->model[9], 2, 2);
    object->model[5] = func_8000B108_main(0x370003, 0x82D);
    func_8001FA68_main(object->model[5]);
    Hu3DModelCameraSet(object->model[5], 1);
    Hu3DModelScaleSet(object->model[5], 0.125f, 0.125f, 0.125f);
    object->func = func_80106D28_ridiculous_relay;
}

void func_80106D28_ridiculous_relay(omObjData *object) {
    func_80106D4C_ridiculous_relay(object);
    omPauseChk();
}

void func_80106D4C_ridiculous_relay(omObjData *object) {
    f32 scales[3] = { 0.25f, 0.5f, 0.8f };
    s32 signSprites[15] = { 3, 2, 3, 4, 3, 4, 3, 4, 3, 4, 3, 4, 3, 2, 3 };
    u8 is8Bit[6] = { 1, 1, 1, 1, 1, 1 };
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *sprite;
    s32 layer;
    s32 idx;
    s32 offset;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;
    s32 k;
    s32 row;
    s32 dist;

    gSPDisplayList(gMainGfxPos++, D_80110CD8_ridiculous_relay);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    idx = 0;
    sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[idx]].unk04, 0);
    frame = &sprite->unk_84->unk00[sprite->unk_90];
    for (layer = 0; layer < 3; layer++) {
        if (layer == 0) {
            idx = 0;
            sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[idx]].unk04, 0);
            frame = &sprite->unk_84->unk00[sprite->unk_90];
            if (is8Bit[idx]) {
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
            } else {
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
            }
        }
        if (layer == 1) {
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 15; j++) {
                    offset = -D_8011199C_ridiculous_relay[i] * scales[layer] + (j - 1) * 320;
                    if (offset <= -320 || offset > 320) {
                        continue;
                    }
                    for (k = 0; k < 6; k++) {
                        x = (k % 3) * 40;
                        x2 = x + ((k % 3 < 2) ? 41.0f : 32.0f);
                        for (row = 0; row < 3; row++) {
                            y = (i == 0) ? row * 40 + 31 : row * 40 + 120;
                            if (row == 2) {
                                y2 = y + ((i == 0) ? 9.0f : 27.0f);
                            } else {
                                y2 = y + 41.0f;
                            }
                            xl = (x + ((k < 3) ? 13.0f : 197.0f) + offset) * 4.0f;
                            yl = y * 4.0f;
                            xh = (x2 + ((k < 3) ? 13.0f : 197.0f) + offset) * 4.0f;
                            yh = (s32)(y2 * 4.0f) - (i == 1 && row == 2) * 3;
                            if (xl >= 1280 || yl >= 960 || xh < 0 || yh < 0) {
                                continue;
                            }
                            idx = (k < 3) ? 1 : 5;
                            sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[idx]].unk04, 0);
                            frame = &sprite->unk_84->unk00[sprite->unk_90];
                            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
                            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 112, 0, (s32)x,
                                               (s32)(y - 31.0f), (s32)x2, (s32)(y2 - 31.0f), 0,
                                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                                               G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f,
                                                    (y - 31.0f) * 32.0f, 1024, 1024);
                        }
                    }
                }
            }
        } else {
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 15; j++) {
                    offset = -D_8011199C_ridiculous_relay[i] * scales[layer] + (j - 1) * 320;
                    if (offset <= -320 || offset > 320) {
                        continue;
                    }
                    if (layer != 0 && layer != 1) {
                        idx = (layer == 2) ? signSprites[j] : 0;
                        sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[idx]].unk04, 0);
                        frame = &sprite->unk_84->unk00[sprite->unk_90];
                        if (is8Bit[idx]) {
                            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
                        } else {
                            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
                        }
                    }
                    for (k = 0; k < 8; k++) {
                        x = k * 40;
                        x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                        for (row = 0; row < 3; row++) {
                            y = (row + i * 3) * 40 + (layer == 2 && row == 0 && i == 0) * 34;
                            y2 = y + 40.0f + ((row == 2) ? ((i == 0) ? 0.0 : -0.75) : 1.0);
                            xl = (x + offset) * 4.0f;
                            yl = y * 4.0f;
                            xh = (x2 + offset) * 4.0f;
                            yh = y2 * 4.0f;
                            if (xl >= 1280 || yl >= 960 || xh < 0 || yh < 0) {
                                continue;
                            }
                            if (layer == 2) {
                                y -= 34.0f;
                                y2 -= 34.0f;
                                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0,
                                                   (s32)x, (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                            } else if (is8Bit[idx]) {
                                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 0,
                                                   (s32)x, (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                   G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                                   G_TX_NOLOD);
                            } else {
                                gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 320, 0, (s32)x,
                                                      (s32)y, (s32)x2, (s32)y2, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                                      G_TX_NOLOD, G_TX_NOLOD);
                            }
                            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f,
                                                    y * 32.0f, 1024, 1024);
                        }
                    }
                    if (layer == 2) {
                        dist = (j - 1) * 50;
                        if (dist >= 50 && dist <= 550) {
                            for (k = 0; k < 3; k++) {
                                s16 digitX[4] = { 159, 159, 135, 135 };
                                s16 digitY[4] = { 47, 147, 47, 147 };
                                s16 px;
                                s16 py;
                                if (dist == 50 && k == 0) {
                                    continue;
                                }
                                sprite = HuSprGet(
                                    D_800CD1DC_main[D_80111A58_ridiculous_relay[(k == 0)   ? dist / 100 + 17
                                                                                : (k == 1) ? dist / 10 % 10 + 17
                                                                                           : 17]]
                                        .unk04,
                                    0);
                                frame = &sprite->unk_84->unk00[sprite->unk_90];
                                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
                                gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 10, 14, 0, 0, 10, 14,
                                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                                px = digitX[(dist / 100 * 100 == dist - 50) ? i + 2 : i];
                                py = digitY[(dist / 100 * 100 == dist - 50) ? i + 2 : i];
                                xl = (px + offset + k * 8 - ((dist == 50) ? 4 : 0)) * 4;
                                yl = py * 4;
                                xh = (px + 10 + offset + k * 8 - ((dist == 50) ? 4 : 0)) * 4;
                                yh = (py + 14) * 4;
                                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, 0, 1024,
                                                        1024);
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 1; i++) {
        gDPPipeSync(gMainGfxPos++);
        if (i == 0) {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
        } else {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, 160);
            gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                              PRIMITIVE, 0);
        }
        sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[(i == 0) ? 6 : 7]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        for (j = 0; j < 2; j++) {
            f32 scroll = D_8011199C_ridiculous_relay[i] + D_80111A50_ridiculous_relay + 640.0f;

            offset = -(scroll - (s32)(scroll / 320.0f) * 320) + j * 320;
            for (k = 0; k < 8; k++) {
                x = k * 40;
                x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                y2 = i * 10 + 26;
                xl = (x + offset) * 4.0f;
                yl = (i * 125 + 115 - (i * 10 + 26)) * 4;
                xh = (x2 + offset) * 4.0f - 1.0f;
                yh = (i * 125 + 115) * 4;
                if (xl >= 1280 || xh < 0) {
                    continue;
                }
                y = 0.0f;
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 320, 0, (s32)x, (s32)y, (s32)x2, (s32)y2,
                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                                      G_TX_NOLOD);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f, y * 32.0f, 1024,
                                        1024);
            }
        }
    }
}

void func_80108DE8_ridiculous_relay(Gfx **gfxPos, s32 arg1, s32 arg2) {
    HuSprite_Unk84_Unk00_Struct *frame;
    HuSprite *sprite;
    f32 scroll;
    f32 x;
    f32 y;
    f32 x2;
    f32 y2;
    s32 offset;
    s32 width;
    s32 height;
    s32 tileWidth;
    s32 i;
    s32 j;
    s32 k;
    s32 row;

    D_80110D68_ridiculous_relay = !D_80110D68_ridiculous_relay;
    if (D_80110D68_ridiculous_relay != 0) {
        return;
    }
    gSPDisplayList(gMainGfxPos++, D_80110CD8_ridiculous_relay);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 1; i < 2; i++) {
        gDPPipeSync(gMainGfxPos++);
        if (i == 0) {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
        } else {
            gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
            gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
            gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 128);
            gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 0, 160);
            gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                              PRIMITIVE, 0);
        }
        sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[(i == 0) ? 6 : 7]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        for (j = 0; j < 2; j++) {
            scroll = D_801119D0_ridiculous_relay * 16.0f + D_8011199C_ridiculous_relay[i] + 640.0f;
            offset = -(scroll - (s32)(scroll / 320.0f) * 320) + j * 320;
            for (k = 0; k < 8; k++) {
                s32 xl;
                s32 yl;
                s32 xh;
                s32 yh;

                x = k * 40;
                x2 = x + 40.0f + ((k < 7) ? 1.0f : 0.0f);
                y2 = i * 10 + 26;
                xl = (x + offset) * 4.0f;
                yl = (((D_801119DC_ridiculous_relay * -16.0f + 120.0f) * i + 120.0f) - y2) * 4.0f;
                xh = (x2 + offset) * 4.0f - 1.0f;
                yh = ((D_801119DC_ridiculous_relay * -16.0f + 240.0f) * i + 120.0f) * 4.0f;
                if (xl >= 1280 || xh < 0) {
                    continue;
                }
                y = 0.0f;
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 320, 0, (s32)x, (s32)y, (s32)x2, (s32)y2,
                                      0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, G_TX_NOMASK, 5, G_TX_NOLOD,
                                      G_TX_NOLOD);
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, x * 32.0f, y * 32.0f, 1024,
                                        1024);
            }
        }
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 8; i++) {
        f32 offsets[8] = { 40.0f, -40.0f, 40.0f, -40.0f, 40.0f, -40.0f, 0.0f, 0.0f };
        f32 scales[8] = { 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f, 0.75f };
        s32 xl;
        s32 yl;
        s32 xh;
        s32 yh;
        s32 dsdx;
        s32 dtdy;

        if (D_80111980_ridiculous_relay[(i < 7) ? i : 6] == 0.0f) {
            continue;
        }
        width = (i == 7) ? 20 : 50;
        height = (i == 7) ? 22 : 50;
        tileWidth = (i >= 2 && i < 6) ? 80 : width;
        if (i == 7) {
            scales[7] = sindf((D_801119C8_ridiculous_relay % 12) / 12.0 * 360.0) * 0.125 + 0.8125;
        }
        x = D_80111980_ridiculous_relay[(i < 7) ? i : 6] + offsets[i] - (tileWidth / 2) * scales[i];
        x2 = D_80111980_ridiculous_relay[(i < 7) ? i : 6] + offsets[i] + (tileWidth / 2) * scales[i];
        if (x > 320.0f || x2 < 0.0f) {
            continue;
        }
        sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[23 + i]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        if (!(i >= 2 && i < 6)) {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, width, height, 0, 0, width, height, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
            if (i >= 6) {
                y = sindf((D_801119C8_ridiculous_relay % 30) / 30.0 * 360.0) * 4.0f + 159.0f;
            } else {
                y = 159.0f;
            }
            xl = x * 4.0f;
            yl = (y - (height / 2) * scales[i] - ((i == 7) ? 3.0f : 0.0f)) * 4.0f;
            xh = x2 * 4.0f;
            yh = (y + (height / 2) * scales[i] - ((i == 7) ? 3.0f : 0.0f)) * 4.0f - 3.0f;
            dsdx = width * 4.0 / (xh - xl) * 1024.0;
            dtdy = height * 4.0 / (yh - yl) * 1024.0;
            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, 0, dsdx, dtdy);
        } else {
            for (row = 0; row < 3; row++) {
                y = (row == 0) ? 0.0f : (row == 1) ? 17.0f
                                                   : 34.0f;
                y2 = (row == 0) ? 19.0f : (row == 1) ? 36.0f
                                                     : 49.0f;
                gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 80, 0, 0, (s32)y, 80, (s32)y2,
                                   0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
                xl = x * 4.0f;
                yl = (y * scales[i] + 134.0f + (1.0f - scales[i]) * 25.0f) * 4.0f;
                xh = x2 * 4.0f;
                yh = (y2 * scales[i] + 134.0f + (1.0f - scales[i]) * 25.0f) * 4.0f;
                dsdx = 80 * 4.0 / (xh - xl) * 1024.0;
                dtdy = (y2 - y) * 4.0 / (yh - yl) * 1024.0;
                yh -= 3;
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, 0, (s32)(y * 32.0f), dsdx,
                                        dtdy);
            }
        }
    }
    sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[8]].unk04, 0);
    frame = &sprite->unk_84->unk00[sprite->unk_90];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 0);
    for (k = 0; k < 6; k++) {
        gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 28, k * 59, 0, k * 59 + 60, 28, 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                           G_TX_NOLOD);
        x = k * 59;
        x2 = k * 59 + 60;
        x2 = MIN(320.0f, x2);
        gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        gSPScisTextureRectangle(gMainGfxPos++, (s32)(x * 4.0f), 106 * 4, (s32)(x2 * 4.0f), 134 * 4, G_TX_RENDERTILE,
                                (s32)(x * 32.0f), 0, 1024, 1024);
    }
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0, 0, 0, 224);
    for (i = 0; i < 4; i++) {
        sprite = HuSprGet(D_800CD1DC_main[D_80111A58_ridiculous_relay[9 + D_80111970_ridiculous_relay[i]->chr]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        if (D_80111970_ridiculous_relay[i]->chr == 7) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
        } else {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
        }
        if (D_80111970_ridiculous_relay[i]->chr == 7) {
            gDPLoadTextureTile(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, G_IM_SIZ_8b, 18, 18, 0, 0, 18, 18, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                               G_TX_NOLOD);
        } else {
            gDPLoadTextureTile_4b(gMainGfxPos++, frame->unk00, G_IM_FMT_CI, 18, 18, 0, 0, 18, 18, 0,
                                  G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                  G_TX_NOLOD, G_TX_NOLOD);
        }
        switch (i) {
            case 0:
                x = D_801119A8_ridiculous_relay[0] * 255.0f + 24.0f;
                break;
            case 1:
                x = D_801119A8_ridiculous_relay[1] * 79.0f + 24.0f;
                break;
            case 2:
                x = D_801119A8_ridiculous_relay[2] * 61.0f + 120.0f;
                break;
            case 3:
                x = D_801119A8_ridiculous_relay[3] * 79.0f + 200.0f;
                break;
        }
        y = (i > 0) ? 120.0f : 102.0f;
        gSPScisTextureRectangle(gMainGfxPos++, (s32)x * 4, (s32)(y * 4.0f), ((s32)x + 18) * 4, (y + 18.0f) * 4.0f,
                                G_TX_RENDERTILE, 0, 0, 1024, 1024);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 255, 255, 255, 0);
    gDPPipeSync(gMainGfxPos++);
}

void func_8010AE4C_ridiculous_relay(omObjData *object) {
    func_8010AF04_ridiculous_relay(object, 0);
    object->func = func_8010B4A8_ridiculous_relay;
}

void func_8010AE80_ridiculous_relay(omObjData *object) {
    func_8010AF04_ridiculous_relay(object, 1);
    object->func = NULL;
}

void func_8010AEAC_ridiculous_relay(omObjData *object) {
    func_8010AF04_ridiculous_relay(object, 2);
    object->func = NULL;
}

void func_8010AED8_ridiculous_relay(omObjData *object) {
    func_8010AF04_ridiculous_relay(object, 3);
    object->func = NULL;
}

void func_8010AF04_ridiculous_relay(omObjData *object, s8 group) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 files[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 shadowFiles[4] = { 0, 1, 3, 5 };
    u16 chr = D_80111970_ridiculous_relay[group]->chr;

    D_80111970_ridiculous_relay[group]->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    object->model[0] = func_8000B108_main((dirs[chr] << 16) | files[chr], 0x4B9);
    switch (group) {
        case 0:
        case 3:
            func_8000B460_main(object, 0, func_80017BB8_main(chr, 0));
            func_8000B460_main(object, 1, func_80017BB8_main(chr, (group != 0) ? 0x7D : 0x7C));
            func_8000B460_main(object, 3, func_80017BB8_main(chr, D_80111970_ridiculous_relay[group]->unk08));
            func_8000B460_main(object, 4, func_80017BB8_main(chr, 0x3A));
            func_8000B460_main(object, 5, func_80017BB8_main(chr, 4));
            func_8000B460_main(object, 6, func_80017BB8_main(chr, 0x1F));
            if (group == 3) {
                func_8001C258_main(object->model[0], 4, 4);
            }
            func_8001C814_main(object->model[0], 1, 1);
            break;
        case 1:
            func_8000B460_main(object, 1, func_80017BB8_main(chr, 0x7E));
            object->model[2] = func_8000B108_main(0x280002, 0x4B9);
            Hu3DModelScaleSet(object->model[2], 0.15625f, 0.15625f, 0.15625f);
            Hu3DModelCameraSet(object->model[2], (group == 0) ? 1 : 2);
            Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
            func_8001C258_main(object->model[2], 0x4000, 0x4000);
            break;
        case 2:
            func_8000B460_main(object, 1, func_80017BB8_main(chr, 0x7F));
            func_8000B460_main(object, 2, func_80017BB8_main(chr, 0x80));
            func_8001C258_main(object->model[0], 4, 4);
            object->model[2] = func_8000B108_main(0x280004, 0x4B9);
            Hu3DModelScaleSet(object->model[2], 0.15625f, 0.15625f, 0.15625f);
            func_8001C814_main(object->model[2], 1, 1);
            Hu3DModelCameraSet(object->model[2], (group == 0) ? 1 : 2);
            break;
    }
    D_80111970_ridiculous_relay[group]->unk08 |= dirs[chr] << 16;
    omSetSca(object, 0.15625f, 0.15625f, 0.15625f);
    func_8001C5B4_main(object->model[0], object->motion[1]);
    func_8001C2FC_main(object->model[0], 0x600, 0x400);
    Hu3DModelCameraSet(object->model[0], (group != 0) ? 2 : 1);
    object->model[1] = func_8000B108_main(shadowFiles[group] | 0x280000, 0x4B9);
    Hu3DModelScaleSet(object->model[1], 0.15625f, 0.15625f, 0.15625f);
    Hu3DModelCameraSet(object->model[1], (group == 0) ? 1 : 2);
    if (group == 2) {
        func_8000B460_main(object, 7, 0x280007);
        func_8000B460_main(object, 8, 0x280008);
        func_8000B460_main(object, 9, 0x280009);
        func_8000B460_main(object, 10, 0x28000A);
        func_8000B460_main(object, 11, 0x28000B);
    }
}

f32 func_8010B474_ridiculous_relay(f32 x) {
    Vec pos;
    Vec2f out;

    pos.x = x;
    pos.y = 0.0f;
    pos.z = 0.0f;
    func_80012B14_main(1, &pos, &out);
    return out.x;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011108C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801110D4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_8011111C_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111164_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111178_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111184_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_80111194_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111A4_ridiculous_relay);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", D_801111B4_ridiculous_relay);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_07_ridiculous_relay/13E9C0", func_8010B4A8_ridiculous_relay);

s16 func_80110BF4_ridiculous_relay(s16 arg0, s16 arg1) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (arg0 == 0) {
        return 0;
    }
    return func_8004AC5C_main(arg0, 0);
}

s16 func_80110C3C_ridiculous_relay(s16 seId, s16 playerIdx) {
    if (D_800A1902_main == 0) {
        return 0;
    }
    if (seId == 0) {
        return 0;
    }
    return func_8004AC5C_main(seId + GwPlayer[playerIdx].chr + 1, 0);
}
