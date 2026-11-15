#include "common.h"
#include "overlays/minigame.h"

#define SPEED_SCALE 0.028935185185185185
#define ABS(x) ((x) > 0 ? (x) : -(x))
#define ABS_DIFF(a, b) (((a) - (b) > 0) ? (a) - (b) : (b) - (a))
#define SETTLE_ANGLE(angle) (((angle) < -10.0f) ? (angle) + 9.0f - (angle) * 0.1 : ((angle) > 10.0f) ? (angle) - 9.0f - (angle) * 0.1 \
                                                                                                     : 0.0f)
#define PEDAL_POWER(speed) (((speed) < 20.0f) ? 2.0f * (speed) - 20.0f : (speed))
#define ROWER_OFFSET()                              \
    ((D_80110E12_ridiculous_relay == 0)             \
         ? rowerSpeeds[D_80110E10_ridiculous_relay] \
         : rowerSpeeds[D_80110E0F_ridiculous_relay] * (1.0f - (f32)D_80110E11_ridiculous_relay / (f32)D_80110E12_ridiculous_relay) + rowerSpeeds[D_80110E10_ridiculous_relay] * ((f32)D_80110E11_ridiculous_relay / (f32)D_80110E12_ridiculous_relay))

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
extern u32 D_80110D6C_ridiculous_relay;
extern u32 D_80110D70_ridiculous_relay[2];
extern u8 D_80110D78_ridiculous_relay;
extern u16 D_80110D7C_ridiculous_relay[18];
extern f32 D_80110DA0_ridiculous_relay[2];
extern u16 D_80110DA8_ridiculous_relay;
extern f32 D_80110DAC_ridiculous_relay[4];
extern f32 D_80110DBC_ridiculous_relay[4];
extern f32 D_80110DCC_ridiculous_relay[4];
extern f32 D_80110DDC_ridiculous_relay[4];
extern s16 D_80110DEE_ridiculous_relay[3];
extern s16 D_80110DF4_ridiculous_relay[4];
extern u32 D_80110DFC_ridiculous_relay[2];
extern u8 D_80110E04_ridiculous_relay;
extern f32 D_80110E08_ridiculous_relay;
extern u8 D_80110E0C_ridiculous_relay[3];
extern u8 D_80110E0F_ridiculous_relay;
extern u8 D_80110E10_ridiculous_relay;
extern u8 D_80110E11_ridiculous_relay;
extern u8 D_80110E12_ridiculous_relay;
extern f32 D_80110E14_ridiculous_relay;
extern u8 D_80110E18_ridiculous_relay;
extern f32 D_80110E1C_ridiculous_relay;
extern f32 D_80110E20_ridiculous_relay[2];
extern f32 D_80110E28_ridiculous_relay[2];
extern f32 D_80110E30_ridiculous_relay[2];
extern u16 D_80110E38_ridiculous_relay[2];
extern u8 D_80110E3C_ridiculous_relay[4];
extern u32 D_80110E40_ridiculous_relay[4];
extern u8 D_80110E50_ridiculous_relay;
extern f32 D_80110E54_ridiculous_relay;
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
extern f32 D_801117F0_ridiculous_relay;
extern f32 D_801117F8_ridiculous_relay[18];
extern f32 D_80111840_ridiculous_relay[18];
extern f32 D_80111888_ridiculous_relay[18];
extern f32 D_801118D0_ridiculous_relay[18];
extern f32 D_80111918_ridiculous_relay;
extern f32 D_8011191C_ridiculous_relay;
extern f32 D_80111920_ridiculous_relay;
extern f32 D_80111924_ridiculous_relay;
extern f32 D_80111928_ridiculous_relay;
extern f32 D_8011192C_ridiculous_relay;
extern f32 D_80111930_ridiculous_relay;
extern f32 D_80111934_ridiculous_relay;
extern f32 D_80111938_ridiculous_relay;
extern f32 D_8011193C_ridiculous_relay;
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
s16 func_80110BF4_ridiculous_relay(s16 arg0, s16 arg1);
s16 func_80110C3C_ridiculous_relay(s16 seId, s16 playerIdx);

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

// `float best` and `int i` (instead of f32/s32) are deliberate: the typedef variants change fold/cross-jumping.
void func_8010B4A8_ridiculous_relay(omObjData *object) {
    f32 hurdleX[18] = { 0.0f, 32.0f, 64.0f, 96.0f, 128.0f, 128.0f, 160.0f, 192.0f, 224.0f,
                        256.0f, 288.0f, 320.0f, 352.0f, 384.0f, 384.0f, 416.0f, 448.0f, 480.0f };
    f32 hurdleLane[18] = { 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f,
                           1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 1.0f };
    f32 visX[5];
    f32 visY[5];
    u8 visIdx[5];
    f32 prevCenter[2] = { CenterM[0].x, CenterM[1].x };
    s32 visCount = 0;
    s16 cpuParams[3][3][4] = {
        { { 4, 3, 3, 2 }, { 12, 10, 9, 8 }, { 3, 2, 2, 2 } },
        { { 2, 3, 2, 2 }, { 6, 7, 6, 6 }, { 3, 5, 4, 3 } },
        { { 0, 0, 0, 0 }, { 10, 15, 30, 40 }, { 0, 0, 0, 0 } },
    };
    f32 rowerSpeeds[5] = { 0.0f, 27.0f, 54.0f, 81.0f, 54.0f };
    f32 waves[3];
    omObjData *obj;
    RidiculousRelayPlayer *player;
    int i;
    s32 j;
    s32 lane;
    u8 mode;
    f32 stickX;
    f32 stickY;
    f32 x;
    f32 y;

    mode = ((D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay >= 63) || D_801119D8_ridiculous_relay == 2)  ? 1
           : ((D_801119D8_ridiculous_relay == 1 && D_801119D4_ridiculous_relay < 63) || D_801119D8_ridiculous_relay == 0) ? 2
                                                                                                                          : 0;
    for (i = 0; i < 7; i++) {
        D_80111980_ridiculous_relay[i] = 0.0f;
    }
    D_801119D0_ridiculous_relay = (D_80110D6C_ridiculous_relay % 1200) / 1200.0 * 20.0;
    D_801119DC_ridiculous_relay = sindf(D_80110D6C_ridiculous_relay * 4) * 0.2;
    waves[0] = sindf(D_80110D6C_ridiculous_relay % 60 * 6) * 20.0f;
    waves[1] = sindf(D_80110D6C_ridiculous_relay % 60 * 6 + 120) * 20.0f;
    waves[2] = sindf(D_80110D6C_ridiculous_relay % 60 * 6 + 240) * 20.0f;

    for (i = 0; i < 18; i++) {
        f32 hx = 2.0 * (hurdleX[i] + 60.0f) * 100.0 / 4.0 * 0.125;

        if (CenterM[0].x - 137.5 < hx && hx < CenterM[0].x + 137.5) {
            if (visCount >= 5) {
                break;
            }
            visIdx[visCount] = i;
            visX[visCount] = hx;
            visY[visCount] = (hurdleLane[i] * 200.0 + waves[i % 3] + D_80110D7C_ridiculous_relay[i] * 10.5) * 0.125;
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[visCount + 12], visX[visCount], visY[visCount], -250.0f);
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[visCount + 12], visX[visCount], visY[visCount], 0.0f);
            func_8001C258_main(D_801119BC_ridiculous_relay->model[visCount + 12], 4, 0);
            visCount++;
        }
    }
    for (i = visCount; i < 5; i++) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[i + 12], 4, 4);
    }

    for (j = 0; j < 2; j++) {
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f && D_80110E38_ridiculous_relay[j] != 0 && D_801119D8_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[0] >= 50.0 && D_80110DAC_ridiculous_relay[0] < 1775.0) {
            // Saturating decrement (same form as the unguarded timers); reuses the tested value.
            D_80110E38_ridiculous_relay[j] -= (D_80110E38_ridiculous_relay[j] != 0) ? 1 : 0;
        }
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f && D_80110E38_ridiculous_relay[j] == 0 && D_801119D8_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[0] >= 50.0 && D_80110DAC_ridiculous_relay[0] < 1775.0) {
            D_80110E20_ridiculous_relay[j] = CenterM[0].x + 125.0;
            HuAudFXPlay(0x332);
            i = rand8() % 9;
            if (D_801119D8_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[0] > D_80110DAC_ridiculous_relay[D_80110D78_ridiculous_relay + 1]) {
                f32 laneDist[3] = { 16382.0f, 16382.0f, 16382.0f };
                float best = 0.0f;
                s32 start = rand8() % 3;
                s32 playerLane = D_80111A20_ridiculous_relay[0]->trans.y / 0.125 + 125.0;

                playerLane = (playerLane >= 100) ? 2 : (playerLane >= -99);

                for (i = 0; i < visCount; i++) {
                    lane = (s32)hurdleLane[visIdx[i]] + 1;
                    if (D_80110D7C_ridiculous_relay[visIdx[i]] == 0 && D_80111A20_ridiculous_relay[0]->trans.x < visX[i] + 12.5) {
                        laneDist[lane] = MIN(visX[i] + 100.0f - D_80111A20_ridiculous_relay[0]->trans.x, laneDist[lane]);
                    }
                }
                for (i = 0, lane = 0; i < 3; i++) {
                    if (best < laneDist[(i + start) % 3] + ((playerLane == (i + start) % 3) ? 1.0f : 0.0f)) {
                        lane = (i + start) % 3;
                        best = laneDist[(i + start) % 3] + ((playerLane == (i + start) % 3) ? 1.0f : 0.0f);
                    }
                }
                if (laneDist[0] != 16382.0f || laneDist[1] != 16382.0f || laneDist[2] != 16382.0f) {
                    i = lane * 3 + rand8() % 3;
                } else {
                    i = rand8() % 9;
                }
            }
            D_80110E28_ridiculous_relay[j] = ((i / 3 - 1) * 200 + (i % 3 - 1) * 40) * 0.125;
        }
        D_80110E20_ridiculous_relay[j] -= D_80110E30_ridiculous_relay[j] * SPEED_SCALE;
        if (D_80110E20_ridiculous_relay[j] <= CenterM[0].x - 137.5 && D_80110E20_ridiculous_relay[j] > -1000.0f) {
            D_80110E20_ridiculous_relay[j] = -1000.0f;
            D_80110E38_ridiculous_relay[j] = (D_80110DAC_ridiculous_relay[0] < 250.0)    ? 20
                                             : (D_80110DAC_ridiculous_relay[0] > 1250.0) ? 0
                                                                                         : (s32)((1250.0 - D_80110DAC_ridiculous_relay[0]) / 1000.0 * 20.0);
        }
        if (D_80110E20_ridiculous_relay[j] <= -1000.0f) {
            func_8001C258_main(D_801119BC_ridiculous_relay->model[j + 10], 4, 4);
        } else {
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[j + 10], D_80110E20_ridiculous_relay[j], D_80110E28_ridiculous_relay[j], 0.0f);
            func_8001C258_main(D_801119BC_ridiculous_relay->model[j + 10], 4, 0);
        }
    }

    // Group 0: hurdle runner
    obj = D_80111A20_ridiculous_relay[0];
    player = D_80111970_ridiculous_relay[0];
    D_80110D70_ridiculous_relay[0] += (D_80110D70_ridiculous_relay[0] != 0 && D_80110D70_ridiculous_relay[0] != 99 && D_80110D70_ridiculous_relay[0] != 199 && D_80110D70_ridiculous_relay[0] != 299);
    if (D_80110D70_ridiculous_relay[0] != 0 && D_80110D70_ridiculous_relay[0] < 100 && D_80110DAC_ridiculous_relay[0] > 1900.0) {
        D_80110D70_ridiculous_relay[0] = 100;
        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[4], obj->trans.x + 12.5, obj->trans.y - 3.125, obj->trans.z);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[4], 4, 0);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    if (D_80110D70_ridiculous_relay[0] >= 100) {
        func_8001C258_main(obj->model[0], 4, 0);
        if (D_80110D70_ridiculous_relay[0] == 100) {
            D_80111918_ridiculous_relay = obj->trans.x;
            D_8011191C_ridiculous_relay = obj->trans.y;
            D_80111924_ridiculous_relay = 0.0f;
            D_80111928_ridiculous_relay = 90.0f;
            D_80111920_ridiculous_relay = 2.0 * (D_80110DCC_ridiculous_relay[0] * SPEED_SCALE);
            func_8001C5B4_main(obj->model[0], obj->motion[5]);
            func_8001C814_main(obj->model[0], 2, 0);
            Hu3DMotionTimeSet(obj->model[0], 14.0f);
        }
        if (D_80110D70_ridiculous_relay[0] == 203) {
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
        }
        if (D_80110D70_ridiculous_relay[0] < 200) {
            D_80111918_ridiculous_relay += D_80111920_ridiculous_relay;
            D_8011191C_ridiculous_relay += D_80111924_ridiculous_relay;
            D_80111924_ridiculous_relay -= 0.8125;
            if (D_8011191C_ridiculous_relay <= -20.0) {
                D_8011191C_ridiculous_relay = -20.0f;
                D_80110D70_ridiculous_relay[0] = 200;
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[6]].motId, 10, 4, 0);
            }
        } else if (D_80110D70_ridiculous_relay[0] >= 215) {
            if (D_801119C0_ridiculous_relay == 0) {
                D_80111928_ridiculous_relay = SETTLE_ANGLE(D_80111928_ridiculous_relay);
            } else if (D_80110D70_ridiculous_relay[0] >= 215) {
                if (D_801119D8_ridiculous_relay == 4 && ((D_801119D4_ridiculous_relay > 30 && D_801119D4_ridiculous_relay < 120 && D_80110D70_ridiculous_relay[0] == 215) || (D_801119D4_ridiculous_relay == 30 && D_801119D4_ridiculous_relay < 120 && D_80110D70_ridiculous_relay[0] >= 215))) {
                    D_80110D70_ridiculous_relay[0] = 300;
                    func_8001C5B4_main(obj->model[0], obj->motion[4]);
                    func_8001C814_main(obj->model[0], 3, 0);
                }
                if (D_80110D70_ridiculous_relay[0] >= 300) {
                    D_80111928_ridiculous_relay = SETTLE_ANGLE(D_80111928_ridiculous_relay);
                }
            }
        }
        omSetTra(obj, D_80111918_ridiculous_relay, D_8011191C_ridiculous_relay, 0.0f);
        omSetRot(obj, 0.0f, D_80111928_ridiculous_relay, 0.0f);
    } else {
        stickX = (mode == 1 && player->cpuDifficulty == -1) ? D_800CBB6E_main[player->pad] : 0.0f;
        stickY = (mode == 1 && player->cpuDifficulty == -1) ? D_800D20A1_main[player->pad] : 0.0f;
        if (D_80110D70_ridiculous_relay[0] != 0) {
            stickX = 0.0f;
            stickY = (D_80110DBC_ridiculous_relay[0] < -135.0f) ? 60.0f : 0.0f;
        } else {
            if (mode == 1 && player->cpuDifficulty != -1) {
                f32 targetSpeeds[4] = { 35.0f, 39.0f, 42.0f, 46.0f };
                f32 laneDist[3] = { D_80110E08_ridiculous_relay, D_80110E08_ridiculous_relay, D_80110E08_ridiculous_relay };
                float best = 0.0f;

                i = targetSpeeds[player->cpuDifficulty];
                stickX = (D_80110DCC_ridiculous_relay[0] < i - 1)   ? 50.0f
                         : (i + 1 < D_80110DCC_ridiculous_relay[0]) ? -50.0f
                                                                    : (D_80110DCC_ridiculous_relay[0] - i) * -50.0f;
                stickX = (stickX < 0.0f) ? 0.0f : stickX;
                for (i = 0; i < visCount; i++) {
                    lane = (s32)hurdleLane[visIdx[i]] + 1;
                    if (D_80110D7C_ridiculous_relay[visIdx[i]] == 0 && obj->trans.x < visX[i] + 12.5) {
                        laneDist[lane] = MIN(visX[i] + 100.0f - obj->trans.x, laneDist[lane]);
                    }
                }
                for (j = 0; j < 2; j++) {
                    f32 range[4] = { 100.0f, 115.0f, 130.0f, 150.0f };
                    f32 dx;
                    f32 move;

                    lane = (D_80110E28_ridiculous_relay[j] < -12.5) ? 0 : (D_80110E28_ridiculous_relay[j] < 12.5) ? 1
                                                                                                                  : 2;
                    dx = D_80110E20_ridiculous_relay[j] - obj->trans.x;
                    move = dx / ((D_80110DCC_ridiculous_relay[0] + D_80110E30_ridiculous_relay[j]) * SPEED_SCALE);
                    move = move * -D_80110E30_ridiculous_relay[j] * SPEED_SCALE;
                    // No braces: keeps range[] alive in this scope, which the original stack layout needs.
                    // NOLINTBEGIN(readability-braces-around-statements)
                    if (move < 0.0f && obj->trans.x < move + D_80110E20_ridiculous_relay[j] + 12.5 && dx < range[player->cpuDifficulty])
                        laneDist[lane] = MIN(move + D_80110E20_ridiculous_relay[j] + 100.0f - obj->trans.x, laneDist[lane]);
                    // NOLINTEND(readability-braces-around-statements)
                }
                lane = 0;
                for (i = 0; i < 3; i++) {
                    if (best < laneDist[i] - ABS_DIFF(D_80110E04_ridiculous_relay, i)) {
                        best = laneDist[i] - ABS_DIFF(D_80110E04_ridiculous_relay, i);
                        lane = i;
                    }
                }
                if (laneDist[0] != D_80110E08_ridiculous_relay || laneDist[1] != D_80110E08_ridiculous_relay || laneDist[2] != D_80110E08_ridiculous_relay) {
                    f32 laneMemory[4] = { 185.0f, 200.0f, 215.0f, 230.0f };
                    f32 laneTolerance[4] = { 30.0f, 37.0f, 44.0f, 50.0f };

                    if (D_80110E04_ridiculous_relay != lane) {
                        D_80110E08_ridiculous_relay = laneMemory[player->cpuDifficulty];
                    }
                    D_80110E04_ridiculous_relay = lane;
                    i = laneTolerance[player->cpuDifficulty];
                    if (((D_80110E04_ridiculous_relay - 1) * 200.0 - i) * 0.125 > obj->trans.y + 15.625) {
                        stickY = i;
                    } else if (((D_80110E04_ridiculous_relay - 1) * 200.0 + i) * 0.125 < obj->trans.y + 15.625) {
                        stickY = -i;
                    }
                }
            }
            stickX = (D_80110DF4_ridiculous_relay[0] != 0) ? -50.0f : (stickX < -50.0f) ? -50.0f
                                                                  : (stickX > 50.0f)    ? 50.0f
                                                                                        : stickX;
            stickY = (D_80110DF4_ridiculous_relay[0] != 0) ? 0.0f : (stickY < -50.0f) ? -50.0f
                                                                : (stickY > 50.0f)    ? 50.0f
                                                                                      : stickY;
            stickY = !(D_80110DBC_ridiculous_relay[0] >= 46.0f && stickY > 0.0f) ? (!(D_80110DBC_ridiculous_relay[0] <= -330.0f && stickY < 0.0f) ? stickY : 0.0f) : 0.0f;
        }
        if (D_80110E18_ridiculous_relay < 31) {
            D_80110DCC_ridiculous_relay[0] += stickX / 50.0 * 5.0 / 30.0;
            D_80110DCC_ridiculous_relay[0] = (mode == 2)                                            ? 40.0f
                                             : (D_80110DCC_ridiculous_relay[0] < 35.0 - 5.0 / 30.0) ? D_80110DCC_ridiculous_relay[0] + 5.0 / 30.0
                                             : (D_80110DCC_ridiculous_relay[0] < 35.0f)             ? 35.0f
                                             : (D_80110DCC_ridiculous_relay[0] > 46.0f)             ? 46.0f
                                                                                                    : D_80110DCC_ridiculous_relay[0];
        }
        D_80110DAC_ridiculous_relay[0] += D_80110DCC_ridiculous_relay[0] * SPEED_SCALE;
        if (D_80110DAC_ridiculous_relay[0] > 1871.875 && D_80110D70_ridiculous_relay[0] == 0) {
            D_80110D70_ridiculous_relay[0] = 1;
            if (D_801119C0_ridiculous_relay == 5) {
                D_801119C0_ridiculous_relay = 0;
            }
            D_80110E40_ridiculous_relay[0] = D_80110D6C_ridiculous_relay;
        }
        D_80110DAC_ridiculous_relay[0] -= D_80110E54_ridiculous_relay;
        CenterM[0].x = 2.0 * D_80110DAC_ridiculous_relay[0] + 56.25;
        D_80110E54_ridiculous_relay = (D_80110DCC_ridiculous_relay[0] + -40.0f) * 3.0f;
        D_80110DAC_ridiculous_relay[0] += D_80110E54_ridiculous_relay;
        i = (D_80110D70_ridiculous_relay[0] != 0) ? 6 : 3;
        D_80110DDC_ridiculous_relay[0] = (D_80110DDC_ridiculous_relay[0] < stickY - i)   ? D_80110DDC_ridiculous_relay[0] + i
                                         : (stickY + i < D_80110DDC_ridiculous_relay[0]) ? D_80110DDC_ridiculous_relay[0] - i
                                                                                         : stickY;
        D_80110DBC_ridiculous_relay[0] += D_80110DDC_ridiculous_relay[0] / 5.0;
        D_80110DBC_ridiculous_relay[0] = (D_80110DBC_ridiculous_relay[0] > 30.0f)     ? 30.0f
                                         : (D_80110DBC_ridiculous_relay[0] < -330.0f) ? -330.0f
                                                                                      : D_80110DBC_ridiculous_relay[0];
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[0], D_80110DBC_ridiculous_relay[0] * 0.125, 0.0f);
        omSetRot(obj, -90.0f, 90.0 - D_80110DDC_ridiculous_relay[0] / 8.0, D_80110DDC_ridiculous_relay[0] / 4.0 + -90.0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
    }
    if (D_80110D70_ridiculous_relay[0] < 100) {
        for (i = 0; i < visCount + 2; i++) {
            x = (i < visCount) ? visX[i] : D_80110E20_ridiculous_relay[i - visCount];
            y = (i < visCount) ? visY[i] : D_80110E28_ridiculous_relay[i - visCount];
            j = i - visCount;
            if ((i < visCount || !(D_80110E20_ridiculous_relay[j] <= -1000.0f)) && mode == 1 && D_80110DF4_ridiculous_relay[0] == 0 && (i >= visCount || D_80110D7C_ridiculous_relay[visIdx[i]] == 0) && D_80110E18_ridiculous_relay == 0) {
                f32 dx = x - obj->trans.x;

                if (dx < 15.625 && dx > -15.625) {
                    f32 ax = ABS(dx) * 0.75;
                    f64 dy = ABS(y - (obj->trans.y + 15.625));
                    f32 ay;

                    if (i >= visCount) {
                        dy *= 0.875;
                    }
                    ay = dy;
                    if (HuSqrtf(ax * ax + ay * ay) < 11.25) {
                        s16 fx;

                        if (i < visCount) {
                            D_80110D7C_ridiculous_relay[visIdx[i]] = 1;
                        }
                        D_80110E1C_ridiculous_relay = D_80110DCC_ridiculous_relay[0];
                        D_80110DF4_ridiculous_relay[0] = 60;
                        D_80110E18_ridiculous_relay = 60;
                        D_80110E50_ridiculous_relay = (i >= visCount);
                        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[5], x * 0.5 + obj->trans.x * 0.5, y * 0.5 + obj->trans.y * 0.5 + 5.0, 0.0f);
                        Hu3DModelRotSet(D_801119BC_ridiculous_relay->model[5], 0.0f, 0.0f, rand8() / 256.0 * 360.0);
                        Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[5], 0.1875f, 0.1875f, 0.1875f);
                        func_8001C258_main(D_801119BC_ridiculous_relay->model[5], 4, 0);
                        func_8001F9E4_main(D_801119BC_ridiculous_relay->model[5], 0xFF);
                        obj->trans.y += -0.75;
                        omVibrate(D_80111970_ridiculous_relay[0]->playerNo, 20, 0, 20);
                        func_80110C3C_ridiculous_relay(0x286, D_80111970_ridiculous_relay[0]->playerNo);
                        func_80110BF4_ridiculous_relay(D_80111970_ridiculous_relay[0]->chr + 0x95, D_80111970_ridiculous_relay[0]->playerNo);
                        if (D_80110E50_ridiculous_relay == 0) {
                            fx = HuAudFXPlay(0x333);
                            if (fx != -1) {
                                HuAudFXPanning(fx, (obj->trans.x - CenterM[0].x) / 90.0 * 32.0 + 64.0);
                            }
                        }
                    }
                }
            }
        }
        if (D_80110DF4_ridiculous_relay[0] == 58 || D_80110DF4_ridiculous_relay[0] == 56) {
            i = (D_80110DF4_ridiculous_relay[0] == 58);
            func_8001F9E4_main(D_801119BC_ridiculous_relay->model[5], i ? 0x80 : 0x30);
            Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[5], i ? 0.28125f : 0.34375f, i ? 0.28125f : 0.34375f,
                              i ? 0.28125f : 0.34375f);
            obj->trans.x += i ? 0.5 : -0.75;
        } else if (D_80110DF4_ridiculous_relay[0] == 54) {
            func_8001C258_main(D_801119BC_ridiculous_relay->model[5], 4, 4);
            obj->trans.x += 0.25;
        }
        if (D_80110DF4_ridiculous_relay[0] != 0) {
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        }
        D_80110DF4_ridiculous_relay[0] = MAX((s16)(D_80110DF4_ridiculous_relay[0] - 2), 0);
        Hu3DMotionTimeSet(obj->model[0], (D_80110DF4_ridiculous_relay[0] != 0) ? (f32)(60 - D_80110DF4_ridiculous_relay[0]) : 0.0f);
        if (D_80110E18_ridiculous_relay != 0) {
            // Saturating decrement (same form as the unguarded timers); reuses the tested value.
            D_80110E18_ridiculous_relay -= (D_80110E18_ridiculous_relay != 0) ? 1 : 0;
            if (D_80110E18_ridiculous_relay >= 30) {
                f32 t = sindf((60 - D_80110E18_ridiculous_relay) / 30.0 * 90.0);

                D_80110DCC_ridiculous_relay[0] = (1.0f - t) * D_80110E1C_ridiculous_relay + t * 35.0f;
                D_80110DAC_ridiculous_relay[0] -= (1.0f - sindf((60 - D_80110E18_ridiculous_relay) / 30.0 * 90.0)) / 2.0f * (D_80110E50_ridiculous_relay ? 4.0 : 2.5);
            }
            if (D_80110E18_ridiculous_relay < 31) {
                func_8001C258_main(obj->model[0], 4, (D_80110E18_ridiculous_relay % 2) * 4);
            }
        } else {
            func_8001C258_main(obj->model[0], 4, 0);
        }
        for (i = 0; i < 18; i++) {
            D_80110D7C_ridiculous_relay[i] += (D_80110D7C_ridiculous_relay[i] != 0 || D_801119D8_ridiculous_relay >= 3) && D_80110D7C_ridiculous_relay[i] < 0xFFFF;
        }
    }
    D_801119A8_ridiculous_relay[0] = (D_80110DAC_ridiculous_relay[0] < 0.0f) ? 0.0f : D_80110DAC_ridiculous_relay[0] / 1868.75f;
    D_801119A8_ridiculous_relay[0] = (D_801119A8_ridiculous_relay[0] >= 1.0f) ? 1.0f : D_801119A8_ridiculous_relay[0];

    // Group 1: rowing
    obj = D_80111A20_ridiculous_relay[1];
    player = D_80111970_ridiculous_relay[1];
    if (D_80110D78_ridiculous_relay == 0 || (D_80110D78_ridiculous_relay == 1 && D_80110DAC_ridiculous_relay[2] < 875.0)) {
        D_80110E0C_ridiculous_relay[0] -= D_80110D78_ridiculous_relay == 0 && D_80110E0C_ridiculous_relay[0] != 0;
        if (D_80110D78_ridiculous_relay == 0 && mode == 1) {
            u16 btn = D_800D5558_main[player->pad];

            if ((D_80110DEE_ridiculous_relay[0] ? (btn & (B_BUTTON | Z_TRIG)) : (btn & A_BUTTON)) || (player->cpuDifficulty != -1 && D_80110E0C_ridiculous_relay[0] == 0)) {
                D_80110DEE_ridiculous_relay[0] = 1 - D_80110DEE_ridiculous_relay[0];
                D_80110DF4_ridiculous_relay[1] = (D_80110DF4_ridiculous_relay[1] != 0) ? D_80110DF4_ridiculous_relay[1] : 60;
                D_80110DCC_ridiculous_relay[1] += 40.0 / 9.0;
                if (player->cpuDifficulty != -1) {
                    D_80110E0C_ridiculous_relay[0] = cpuParams[0][0][player->cpuDifficulty] + rand8() % cpuParams[1][0][player->cpuDifficulty];
                }
            }
        }
        if (mode == 2 && D_80110D6C_ridiculous_relay % 24 == 15) {
            D_80110DF4_ridiculous_relay[1] = (D_80110DF4_ridiculous_relay[1] != 0) ? D_80110DF4_ridiculous_relay[1] : 60;
        }
        D_80110DAC_ridiculous_relay[1] += D_80110DCC_ridiculous_relay[1] * SPEED_SCALE;
        D_80110DCC_ridiculous_relay[1] -= D_80110DCC_ridiculous_relay[1] / 6.0 / 5.0 * (29.0 / 30.0);
        D_80110DCC_ridiculous_relay[1] = (mode == 2)                                ? 40.0f
                                         : (D_80110DCC_ridiculous_relay[1] > 43.5)  ? 43.5f
                                         : (D_80110DCC_ridiculous_relay[1] < -43.5) ? -43.5f
                                                                                    : D_80110DCC_ridiculous_relay[1];
        if (D_80110DAC_ridiculous_relay[1] > 626.25) {
            D_80110DAC_ridiculous_relay[1] = 626.25f;
            D_80110DCC_ridiculous_relay[1] *= (D_80110DCC_ridiculous_relay[1] > 0.0f) ? -0.25 : 1.0;
            if (D_80110D78_ridiculous_relay == 0) {
                D_80110D78_ridiculous_relay = 1;
                D_80110DFC_ridiculous_relay[0] = 1;
                D_80110DA8_ridiculous_relay = 1;
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 0.5) ? 0.5f : D_801117F0_ridiculous_relay;
                D_80110E40_ridiculous_relay[1] = D_80110D6C_ridiculous_relay;
                omVibrate(D_80111970_ridiculous_relay[2]->playerNo, 2, 3, 10);
            }
        }
        if (D_80110D78_ridiculous_relay == 0) {
            f32 camX = 2.0 * D_80110DAC_ridiculous_relay[1] + 56.25;

            D_801117F0_ridiculous_relay = prevCenter[1] - D_80110DA0_ridiculous_relay[1];
            CenterM[1].x = camX;
        }
        func_8001C258_main(obj->model[0], 4, 0);
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[1], D_801119DC_ridiculous_relay * 100.0f * 0.125 + -25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        {
            s32 prev = D_80110DF4_ridiculous_relay[1];

            i = prev >= 58;
            D_80110DF4_ridiculous_relay[1] = prev - ((D_80110DCC_ridiculous_relay[1] < 0.0f) ? 1.0 : D_80110DCC_ridiculous_relay[1] / 15.0);
            D_80110DF4_ridiculous_relay[1] = MAX(D_80110DF4_ridiculous_relay[1], 0);
            if (D_80110DF4_ridiculous_relay[1] < 58 && i) {
                HuAudFXPlay(0x32F);
            }
        }
        Hu3DMotionTimeSet(obj->model[0], (D_80110DF4_ridiculous_relay[1] != 0) ? (f32)(60 - D_80110DF4_ridiculous_relay[1]) : 0.0f);
        if (D_80110D78_ridiculous_relay == 0 && mode == 1) {
            D_80111980_ridiculous_relay[D_80110DEE_ridiculous_relay[0]] = obj->trans.x;
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        func_8001C258_main(obj->model[2], 4, 4);
    }
    if (D_80110E3C_ridiculous_relay[0] == 1) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[7], 4, 4);
    }
    D_80110E3C_ridiculous_relay[0] -= (D_80110E3C_ridiculous_relay[0] != 0) ? 1 : 0;
    D_801119A8_ridiculous_relay[1] = (D_80110D78_ridiculous_relay != 0)        ? 1.0f
                                     : (D_80110DAC_ridiculous_relay[1] < 0.0f) ? 0.0f
                                                                               : D_80110DAC_ridiculous_relay[1] / 626.5625f;
    D_801119A8_ridiculous_relay[1] = (D_801119A8_ridiculous_relay[1] >= 1.0f) ? 1.0f : D_801119A8_ridiculous_relay[1];

    // Group 2: swimming
    obj = D_80111A20_ridiculous_relay[2];
    player = D_80111970_ridiculous_relay[2];
    if (D_80110D78_ridiculous_relay == 1 || (D_80110D78_ridiculous_relay == 0 && D_80110DAC_ridiculous_relay[1] > 375.0) || (D_80110D78_ridiculous_relay == 2 && D_80110DAC_ridiculous_relay[3] < 1500.0)) {
        f32 step;

        D_80110E0C_ridiculous_relay[1] -= D_80110D78_ridiculous_relay == 1 && D_80110E0C_ridiculous_relay[1] != 0;
        if (D_80110D78_ridiculous_relay == 1 && mode == 1 && (((D_800D5558_main[player->pad] & ((D_80110DEE_ridiculous_relay[1] / 2) ? B_BUTTON : A_BUTTON)) && ((D_80110DEE_ridiculous_relay[1] & 1) ? -1 : 1) * D_800D20A1_main[player->pad] > 32) || (player->cpuDifficulty != -1 && D_80110E0C_ridiculous_relay[1] == 0))) {
            D_80110E0F_ridiculous_relay = D_80110E10_ridiculous_relay;
            D_80110E10_ridiculous_relay = D_80110DEE_ridiculous_relay[1];
            D_80110E11_ridiculous_relay = 0;
            D_80110E12_ridiculous_relay = 2;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[D_80110DEE_ridiculous_relay[1] + 7]].motId,
                               (D_80110DEE_ridiculous_relay[1] == 3) ? 7 : 5, 4, 0);
            D_80110DEE_ridiculous_relay[1]++;
            D_80110DEE_ridiculous_relay[1] %= 4;
            if (D_80110DEE_ridiculous_relay[1] == 0) {
                D_80110DF4_ridiculous_relay[2] = 50;
                D_80110DCC_ridiculous_relay[2] = 53.0f;
                if (D_80110D78_ridiculous_relay == 1) {
                    func_8001C258_main(D_801119BC_ridiculous_relay->model[8], 4, 0);
                    Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[8], 0.234375f, 0.234375f, 0.234375f);
                    Hu3DMotionTimeSet(D_801119BC_ridiculous_relay->model[8], 0.0f);
                    Hu3DMotionSpeedSet(D_801119BC_ridiculous_relay->model[8], 1.5f);
                    func_8001C258_main(D_801119BC_ridiculous_relay->model[9], 4, 0);
                    Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[9], 0.234375f, 0.234375f, 0.234375f);
                    Hu3DMotionTimeSet(D_801119BC_ridiculous_relay->model[9], 0.0f);
                    Hu3DMotionSpeedSet(D_801119BC_ridiculous_relay->model[9], 1.5f);
                    D_80110E3C_ridiculous_relay[1] = 10;
                    HuAudFXPlay(0x330);
                }
            }
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[8], obj->trans.x - 31.25, obj->trans.y - 3.90625, obj->trans.z);
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[9], obj->trans.x + 23.4375, obj->trans.y - 1.953125, obj->trans.z);
            if (player->cpuDifficulty != -1) {
                D_80110E0C_ridiculous_relay[1] = cpuParams[0][1][player->cpuDifficulty] + rand8() % cpuParams[1][1][player->cpuDifficulty];
            }
        } else if (D_80110D78_ridiculous_relay == 1 && mode == 1 && D_80110E10_ridiculous_relay != 4 && player->cpuDifficulty == -1 && (D_800D5558_main[player->pad] & (A_BUTTON | B_BUTTON))) {
            D_80110E0F_ridiculous_relay = D_80110E10_ridiculous_relay;
            D_80110E10_ridiculous_relay = 4;
            D_80110E11_ridiculous_relay = 0;
            D_80110E12_ridiculous_relay = 3;
            Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[11]].motId, 0, 6, 0);
            omVibrate(D_80111970_ridiculous_relay[2]->playerNo, 10, 0, 10);
        }
        // About 125 / 60, but the original constant is one ulp below the correctly rounded quotient.
        step = D_80110DCC_ridiculous_relay[2] / 60.0 * 2.083333333333333;
        D_80110DAC_ridiculous_relay[2] += step;
        D_80110DCC_ridiculous_relay[2] = (D_80110DCC_ridiculous_relay[2] > 1.0f)    ? D_80110DCC_ridiculous_relay[2] - 1.0f
                                         : (D_80110DCC_ridiculous_relay[2] < -1.0f) ? D_80110DCC_ridiculous_relay[2] + 1.0f
                                                                                    : 0.0f;
        if (D_80110DAC_ridiculous_relay[2] > 1245.3125) {
            D_80110DAC_ridiculous_relay[2] = 1245.3125f;
            D_80110DCC_ridiculous_relay[2] *= (D_80110DCC_ridiculous_relay[2] > 0.0f) ? -0.2 : 1.0;
            if (D_80110D78_ridiculous_relay < 2) {
                D_80110D78_ridiculous_relay = 2;
                D_80110DFC_ridiculous_relay[1] = 1;
                D_80110DA8_ridiculous_relay = 1;
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 0.5) ? 0.5f : D_801117F0_ridiculous_relay;
                if (D_801119D8_ridiculous_relay == 2) {
                    D_80111A30_ridiculous_relay[2] = HuAudFXPlay(0x331);
                    HuAudFXVolSet(D_80111A30_ridiculous_relay[2], 127);
                }
                D_80110E40_ridiculous_relay[2] = D_80110D6C_ridiculous_relay;
                omVibrate(D_80111970_ridiculous_relay[3]->playerNo, 2, 3, 10);
            }
        }
        if (D_80110D78_ridiculous_relay == 1) {
            f32 camX = 2.0 * D_80110DAC_ridiculous_relay[2] + 56.25;

            D_80110DA8_ridiculous_relay = (D_80110DA8_ridiculous_relay != 0 && CenterM[1].x + D_801117F0_ridiculous_relay <= camX) ? D_80110DA8_ridiculous_relay + 1 : 0;
            if (D_80110DA8_ridiculous_relay != 0) {
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 2.0 * step) ? 2.0 * step : D_801117F0_ridiculous_relay;
                CenterM[1].x += D_801117F0_ridiculous_relay;
            } else {
                D_801117F0_ridiculous_relay = prevCenter[1] - D_80110DA0_ridiculous_relay[1];
                CenterM[1].x = camX;
            }
        }
        func_8001C258_main(obj->model[0], 4, 0);
        func_8001C258_main(obj->model[2], 4, 0);
        D_80110E11_ridiculous_relay = (D_80110E0F_ridiculous_relay == D_80110E10_ridiculous_relay) ? 0 : D_80110E11_ridiculous_relay + 1;
        if (D_80110E11_ridiculous_relay > D_80110E12_ridiculous_relay) {
            u8 prevAnim = D_80110E0F_ridiculous_relay;

            D_80110E0F_ridiculous_relay = D_80110E10_ridiculous_relay;
            D_80110E11_ridiculous_relay = 0;
            if (D_80110E10_ridiculous_relay == 4) {
                D_80110E10_ridiculous_relay = prevAnim;
                D_80110E12_ridiculous_relay = 10;
                Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[D_80110E10_ridiculous_relay + 7]].motId, 60, 20, 0);
            } else {
                D_80110E12_ridiculous_relay = 0;
            }
        }
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[2], D_801119DC_ridiculous_relay * 100.0f * 0.125 + -25.0 + 25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, 0.0f);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        obj->trans.x -= ROWER_OFFSET() * 0.125 * 1.25;
        obj->trans.y -= ROWER_OFFSET() * 0.125 * 1.25;
        obj->trans.y += 1.875;
        Hu3DModelPosSet(obj->model[2], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[2], obj->rot.x, obj->rot.y, obj->rot.z);
        if (D_80110DF4_ridiculous_relay[2] > 0) {
            if (D_80110DF4_ridiculous_relay[2] == 2) {
                D_80110DF4_ridiculous_relay[2] = 0;
                func_8001C5B4_main(obj->model[0], obj->motion[1]);
                Hu3DMotionTimeSet(obj->model[2], 0.0f);
            } else {
                if (D_80110DF4_ridiculous_relay[2] == 50) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[2]].motId, 0, 6, 2);
                }
                D_80110DF4_ridiculous_relay[2] = MAX((s16)(D_80110DF4_ridiculous_relay[2] - 2), 0);
                Hu3DMotionTimeSet(obj->model[0], (D_80110DF4_ridiculous_relay[2] != 0) ? (f32)(50 - D_80110DF4_ridiculous_relay[2]) : 0.0f);
                Hu3DMotionTimeSet(obj->model[2], (D_80110DF4_ridiculous_relay[2] == 0)   ? 0.0f
                                                 : (D_80110DF4_ridiculous_relay[2] < 25) ? (f32)D_80110DF4_ridiculous_relay[2]
                                                                                         : (f32)(50 - D_80110DF4_ridiculous_relay[2]));
            }
        }
        func_8001C814_main(obj->model[0], 3, 2);
        func_8001C814_main(obj->model[2], 3, 1);
        if (D_80110D78_ridiculous_relay == 1 && mode == 1) {
            D_80111980_ridiculous_relay[D_80110DEE_ridiculous_relay[1] + 2] = Hu3DData[obj->model[1]].pos.x;
        }
        if (D_80110E0F_ridiculous_relay == 4 && (D_80110E11_ridiculous_relay == 0 || D_80110E11_ridiculous_relay == 4)) {
            for (i = (D_80110E11_ridiculous_relay != 0) ? 9 : 0; i < ((D_80110E11_ridiculous_relay == 0) ? 9 : 18); i++) {
                func_8001C258_main(D_801119BC_ridiculous_relay->model[i + 17], 4, 0);
                D_801117F8_ridiculous_relay[i] = Hu3DData[obj->model[1]].pos.x + ((D_80110E11_ridiculous_relay == 0) ? -31.25 : 27.5);
                D_80111840_ridiculous_relay[i] = D_801119DC_ridiculous_relay * 100.0f * 0.125 + -25.0;
                D_80111888_ridiculous_relay[i] = (rand8() / 256.0 * 30.0 - 10.0) * 0.125 * ((D_80110E11_ridiculous_relay != 0) ? 1 : -1);
                D_801118D0_ridiculous_relay[i] = (rand8() / 256.0 * 30.0 + 20.0) * 0.125;
                Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[i + 17], D_801117F8_ridiculous_relay[i], D_80111840_ridiculous_relay[i], 0.0f);
            }
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
        func_8001C258_main(obj->model[2], 4, 4);
    }
    if (D_80110E3C_ridiculous_relay[1] == 1) {
        func_8001C258_main(D_801119BC_ridiculous_relay->model[8], 4, 4);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[9], 4, 4);
    }
    D_80110E3C_ridiculous_relay[1] -= (D_80110E3C_ridiculous_relay[1] != 0) ? 1 : 0;
    D_801119A8_ridiculous_relay[2] = (D_80110D78_ridiculous_relay >= 2)        ? 1.0f
                                     : (D_80110DAC_ridiculous_relay[2] < 0.0f) ? 0.0f
                                                                               : (D_80110DAC_ridiculous_relay[2] - 650.0) / 601.5625;
    D_801119A8_ridiculous_relay[2] = (D_801119A8_ridiculous_relay[2] >= 1.0f)  ? 1.0f
                                     : (D_801119A8_ridiculous_relay[2] < 0.0f) ? 0.0f
                                                                               : D_801119A8_ridiculous_relay[2];
    for (i = 0; i < 18; i++) {
        if (D_80111840_ridiculous_relay[i] == -1000.0f) {
            continue;
        }
        D_801117F8_ridiculous_relay[i] += D_80111888_ridiculous_relay[i];
        D_80111840_ridiculous_relay[i] += D_801118D0_ridiculous_relay[i];
        D_801118D0_ridiculous_relay[i] -= 0.625;
        if (D_801118D0_ridiculous_relay[i] < 0.0f && D_80111840_ridiculous_relay[i] < D_801119DC_ridiculous_relay * 100.0f * 0.125 + -25.0) {
            func_8001C258_main(D_801119BC_ridiculous_relay->model[i + 17], 4, 4);
            D_80111840_ridiculous_relay[i] = -1000.0f;
        } else {
            Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[i + 17], D_801117F8_ridiculous_relay[i], D_80111840_ridiculous_relay[i], 0.0f);
        }
    }

    // Group 3: bicycle
    obj = D_80111A20_ridiculous_relay[3];
    player = D_80111970_ridiculous_relay[3];
    if (D_80110D78_ridiculous_relay == 2 || D_80110D78_ridiculous_relay == 3 || (D_80110D78_ridiculous_relay == 1 && D_80110DAC_ridiculous_relay[2] > 1000.0)) {
        f32 step;

        D_80110E0C_ridiculous_relay[2] -= D_80110D78_ridiculous_relay == 2 && D_80110E0C_ridiculous_relay[2] != 0;
        if (D_80110D78_ridiculous_relay >= 2 && mode == 1) {
            if ((D_800D5558_main[player->pad] & A_BUTTON) || (player->cpuDifficulty != -1 && D_80110E0C_ridiculous_relay[2] == 0)) {
                D_80110DCC_ridiculous_relay[3] += 5.0f;
                if (player->cpuDifficulty != -1) {
                    D_80110E0C_ridiculous_relay[2] = cpuParams[0][2][player->cpuDifficulty] + rand8() % cpuParams[1][2][player->cpuDifficulty];
                }
            }
        }
        step = D_80110DCC_ridiculous_relay[3] * SPEED_SCALE;
        D_80110DAC_ridiculous_relay[3] = step + D_80110DAC_ridiculous_relay[3];
        D_80110DCC_ridiculous_relay[3] -= D_80110DCC_ridiculous_relay[3] / 6.0 / 5.0;
        D_80110DCC_ridiculous_relay[3] = (D_80110DCC_ridiculous_relay[3] > 50.0f)    ? 50.0f
                                         : (D_80110DCC_ridiculous_relay[3] < -50.0f) ? -50.0f
                                                                                     : D_80110DCC_ridiculous_relay[3];
        if (D_80111A30_ridiculous_relay[2] != -1) {
            HuAudFXPitchSet((s16)D_80111A30_ridiculous_relay[2], (s16)(D_80110DCC_ridiculous_relay[3] / 50.0 * 400.0 - 400.0));
        }
        if (D_80110DAC_ridiculous_relay[3] > 1865.625 && D_80110D70_ridiculous_relay[1] == 0) {
            if (D_801119C0_ridiculous_relay == 5 || (D_801119C0_ridiculous_relay == 0 && D_80110D70_ridiculous_relay[0] == 1 && D_80110DAC_ridiculous_relay[0] < D_80110DAC_ridiculous_relay[3])) {
                D_801119C0_ridiculous_relay = 1;
                D_80110D70_ridiculous_relay[1] = 1;
            }
            if (D_80110E40_ridiculous_relay[3] == 0) {
                D_80110E40_ridiculous_relay[3] = D_80110D6C_ridiculous_relay;
            }
            D_80110DAC_ridiculous_relay[3] = 1865.625f;
            D_80110DCC_ridiculous_relay[3] *= (D_80110DCC_ridiculous_relay[3] > 0.0f) ? -0.125 : 1.0;
        }
        if (D_80110D78_ridiculous_relay == 2) {
            f32 camX = 2.0 * D_80110DAC_ridiculous_relay[3] + 56.25;

            D_80110DA8_ridiculous_relay = (D_80110DA8_ridiculous_relay != 0 && CenterM[1].x + D_801117F0_ridiculous_relay <= camX) ? D_80110DA8_ridiculous_relay + 1 : 0;
            if (D_80110DA8_ridiculous_relay != 0) {
                D_801117F0_ridiculous_relay = (D_801117F0_ridiculous_relay < 2.0 * step) ? 2.0 * step : D_801117F0_ridiculous_relay;
                CenterM[1].x += D_801117F0_ridiculous_relay;
            } else {
                D_801117F0_ridiculous_relay = prevCenter[1] - D_80110DA0_ridiculous_relay[1];
                CenterM[1].x = camX;
            }
        }
        D_80110DEE_ridiculous_relay[2] = D_80110DEE_ridiculous_relay[2] * 0.875 + D_80110DCC_ridiculous_relay[3] / 50.0 * 10.0 * 1000.0 * 0.125;
        func_8001C258_main(obj->model[0], 4, 0);
        omSetTra(obj, 2.0 * D_80110DAC_ridiculous_relay[3], D_801119DC_ridiculous_relay * 100.0f * 0.125 + -25.0, 0.0f);
        omSetRot(obj, 0.0f, 90.0f, D_80110DEE_ridiculous_relay[2] / 1000.0);
        func_8001C258_main(obj->model[1], 4, 0);
        Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        Hu3DModelRotSet(obj->model[1], obj->rot.x, obj->rot.y, obj->rot.z);
        D_80110DF4_ridiculous_relay[3] += ABS(D_80110DCC_ridiculous_relay[3]) / 50.0 * 350.0;
        D_80110DF4_ridiculous_relay[3] %= 3000;
        D_80110E14_ridiculous_relay = (D_80110E14_ridiculous_relay - 4.0 / 47.5 < PEDAL_POWER(D_80110DCC_ridiculous_relay[3]) / 47.5)
                                          ? PEDAL_POWER(D_80110DCC_ridiculous_relay[3]) / 47.5
                                          : D_80110E14_ridiculous_relay - 4.0 / 47.5;
        D_80110E14_ridiculous_relay = (D_80110E14_ridiculous_relay < 0.0f) ? 0.0f : D_80110E14_ridiculous_relay;
        Hu3DMotionTimeSet(obj->model[1], D_80110DF4_ridiculous_relay[3] / 100.0);
        func_8001C258_main(D_801119BC_ridiculous_relay->model[6], 4, 0);
        Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[6], obj->trans.x - (D_80110E14_ridiculous_relay * 40.0f + 200.0f) * 1.25 * 0.125,
                        obj->trans.y + D_80110E14_ridiculous_relay * 100.0f * 1.25 * 0.125, obj->trans.z);
        Hu3DModelScaleSet(D_801119BC_ridiculous_relay->model[6], D_80110E14_ridiculous_relay * 1.25 * 0.125 * 1.3,
                          D_80110E14_ridiculous_relay * 1.25 * 0.125, D_80110E14_ridiculous_relay * 1.25 * 0.125);
        if (D_80110D70_ridiculous_relay[1] != 0) {
            if (D_80110D70_ridiculous_relay[1] == 15) {
                D_80111930_ridiculous_relay = obj->trans.y + 4.375;
                D_80111938_ridiculous_relay = 7.5f;
                for (i = 0; i < 85; i++) {
                    D_80111930_ridiculous_relay += D_80111938_ridiculous_relay;
                    D_80111938_ridiculous_relay -= 0.8125;
                    if (D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay <= -13.75) {
                        break;
                    }
                }
                D_8011192C_ridiculous_relay = obj->trans.x + 4.375;
                D_80111930_ridiculous_relay = obj->trans.y + 4.375;
                D_8011193C_ridiculous_relay = 90.0f;
                D_80111934_ridiculous_relay = (3768.75 - obj->trans.x) / (f32)i;
                D_80111938_ridiculous_relay = 7.5f;
                func_8001C5B4_main(obj->model[0], obj->motion[5]);
                func_8001C814_main(obj->model[0], 3, 0);
                D_80110DCC_ridiculous_relay[3] -= 2.0;
            }
            if (D_80110D70_ridiculous_relay[1] >= 16 && D_80110D70_ridiculous_relay[1] < 100) {
                D_8011192C_ridiculous_relay += D_80111934_ridiculous_relay;
                D_80111930_ridiculous_relay += D_80111938_ridiculous_relay;
                D_80111938_ridiculous_relay -= 0.8125;
                if ((D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay <= -13.75) || D_80111930_ridiculous_relay < -1875.0) {
                    D_80111930_ridiculous_relay = -13.75f;
                    D_80110D70_ridiculous_relay[1] = 100;
                } else if (D_80111938_ridiculous_relay < 0.0f && D_80111930_ridiculous_relay + D_80111938_ridiculous_relay <= -13.75) {
                    Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[6]].motId, 10, 4, 0);
                }
            }
            if (D_80110D70_ridiculous_relay[1] == 102) {
                Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
            }
            if (D_80110D70_ridiculous_relay[1] >= 115 && D_801119C0_ridiculous_relay == 1) {
                D_8011193C_ridiculous_relay = SETTLE_ANGLE(D_8011193C_ridiculous_relay);
            }
            if (D_80110D70_ridiculous_relay[1] >= 16) {
                omSetTra(obj, D_8011192C_ridiculous_relay, D_80111930_ridiculous_relay, 0.0f);
                omSetRot(obj, 0.0f, D_8011193C_ridiculous_relay, 0.0f);
            }
            D_80110D70_ridiculous_relay[1]++;
        } else {
            func_8001C814_main(obj->model[0], 3, 2);
        }
        if (D_80110D78_ridiculous_relay >= 2 && mode == 1) {
            D_80111980_ridiculous_relay[6] = obj->trans.x;
        }
    } else {
        func_8001C258_main(obj->model[0], 4, 4);
        func_8001C258_main(obj->model[1], 4, 4);
    }
    D_801119A8_ridiculous_relay[3] = (D_80110D78_ridiculous_relay >= 3)        ? 1.0f
                                     : (D_80110DAC_ridiculous_relay[3] < 0.0f) ? 0.0f
                                                                               : (D_80110DAC_ridiculous_relay[3] - 1275.0) / 593.75;
    D_801119A8_ridiculous_relay[3] = (D_801119A8_ridiculous_relay[3] >= 1.0f || D_80110D70_ridiculous_relay[1] != 0) ? 1.0f
                                     : (D_801119A8_ridiculous_relay[3] < 0.0f)                                       ? 0.0f
                                                                                                                     : D_801119A8_ridiculous_relay[3];

    // Camera and finish line flags
    CenterM[0].x = (CenterM[0].x > 3750.0) ? 3750.0f : CenterM[0].x;
    CenterM[1].x = (CenterM[1].x > 3750.0) ? 3750.0f : CenterM[1].x;
    i = (CenterM[1].x < 1875.0) ? 0 : 1;
    omSetTra(D_801119BC_ridiculous_relay, (2.0 * ((i + 1) * 5000) + 950.0) * 0.125,
             ((D_80110DFC_ridiculous_relay[i] < 10)
                  ? 0.125 * (D_80110DFC_ridiculous_relay[i] * D_80110DFC_ridiculous_relay[i] / 100.0 * 100.0)
                  : ((D_80110DFC_ridiculous_relay[i] < 30) ? (D_80110DFC_ridiculous_relay[i] - 10) * 36 + 100
                     : ((D_80110DFC_ridiculous_relay[i] - 30) * (D_80110DFC_ridiculous_relay[i] - 30) * 2 < 460)
                         ? 460 - (D_80110DFC_ridiculous_relay[i] - 30) * (D_80110DFC_ridiculous_relay[i] - 30) * 2
                         : 0) *
                        0.125) +
                 -46.875,
             0.0f);
    Hu3DModelPosSet(D_801119BC_ridiculous_relay->model[1], (2.0 * ((i + 1) * 5000) + 150.0) * 0.125, -25.0f, 0.0f);
    D_80110DFC_ridiculous_relay[0] += (D_80110DFC_ridiculous_relay[0] != 0 && D_80110DFC_ridiculous_relay[0] < 24) || (D_80110DFC_ridiculous_relay[0] >= 30 && D_80110DFC_ridiculous_relay[0] < 45);
    if (D_80110DFC_ridiculous_relay[1] == 44) {
        HuAudFXPlay(0x334);
    }
    D_80110DFC_ridiculous_relay[1] += (D_80110DFC_ridiculous_relay[1] != 0 && D_80110DFC_ridiculous_relay[1] < 20) || (D_80110DFC_ridiculous_relay[1] >= 30 && D_80110DFC_ridiculous_relay[1] < 45);
    if (D_80110DFC_ridiculous_relay[1] == 20 && CenterM[1].x > 2721.875) {
        D_80110DFC_ridiculous_relay[1] = 30;
    }
    if (D_80110D6C_ridiculous_relay < 123) {
        CenterM[0].x = CenterM[0].x * 0.75 + 14.5718165;
        CenterM[1].x = CenterM[1].x * 0.75 + 14.5718165;
    }
    D_80110DAC_ridiculous_relay[0] = (D_80110DAC_ridiculous_relay[0] < -2000.0f) ? -2000.0f : D_80110DAC_ridiculous_relay[0];
    D_8011199C_ridiculous_relay[0] = CenterM[0].x / 0.125 / 100.0 * 16.0;
    if (CenterM[0].x < 3750.0) {
        D_801119C4_ridiculous_relay = (D_80110DCC_ridiculous_relay[0] - 35.0f) / 10.0 * 0.25 - 0.5;
    }
    D_801119C4_ridiculous_relay = 0.0f;
    D_80111A50_ridiculous_relay += D_801119C4_ridiculous_relay;
    D_80111A50_ridiculous_relay -= (D_80111A50_ridiculous_relay >= 320.0f) ? 320.0f : 0.0f;
    D_80111A50_ridiculous_relay += (D_80111A50_ridiculous_relay < 0.0f) ? 320.0f : 0.0f;
    D_8011199C_ridiculous_relay[1] = CenterM[1].x / 0.125 / 100.0 * 16.0;
    for (i = 0; i < 7; i++) {
        if (D_80111980_ridiculous_relay[i] != 0.0f) {
            D_80111980_ridiculous_relay[i] = func_8010B474_ridiculous_relay(D_80111980_ridiculous_relay[i]);
        }
    }
    D_80110D6C_ridiculous_relay++;
    D_80110DA0_ridiculous_relay[0] = prevCenter[0];
    D_80110DA0_ridiculous_relay[1] = prevCenter[1];
}

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
