#include "common.h"
#include "overlays/mgmode.h"

extern MgmodeEsprite *D_8011B450_mgmode;
extern s16 D_8011B454_mgmode;
extern s16 D_8011B458_mgmode[8];
extern u8 D_8011B430_mgmode[4];
extern u8 D_8011B434_mgmode;
extern s16 D_800CC438_main;
extern s16 D_800CE29C_main;
extern s16 D_800D03FE_main[4];
extern u8 D_80119430_mgmode[];
extern s16 D_800D4194_main;
extern s16 D_800D0418_main[8];
extern u8 D_8011B6B0_mgmode[][25];
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B6A8_mgmode;
extern MgmodeSpaceCoord D_80119424_mgmode[];
extern u8 D_800D1F20_main[4];
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8E8_mgmode[];
extern s16 D_8011B8A8_mgmode[];
extern s16 D_8011B796_mgmode[];
extern s16 D_8011B78E_mgmode[];
extern s16 D_8011B78C_mgmode;
extern s16 D_8011B788_mgmode;
extern s16 D_80119340_mgmode;
extern s16 D_800D1F2C_main;
extern MgmodeEsprite *D_8011B480_mgmode;
extern s16 D_8011B484_mgmode;
extern u16 D_8011B488_mgmode[28];
extern s16 D_8011B808_mgmode;
extern MgmodeSpaceCoord D_8011943C_mgmode[];
extern s16 D_8011944C_mgmode[];
extern MgmodeEspriteDef D_80119EB0_mgmode[];
extern s16 D_800CB894_main;
extern u8 D_80118EB1_mgmode;
extern s16 D_80118EB4_mgmode;
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;
extern MgmodeSpaceCoord D_80119454_mgmode[];
extern MgmodeSpaceCoord D_8011B468_mgmode[];
extern s16 D_8011B4C0_mgmode;
extern s16 D_80119490_mgmode[];
extern CamData *D_8011B954_mgmode;
extern CamData D_80119344_mgmode[];
extern f32 D_8011B888_mgmode;
extern s16 D_8011B436_mgmode[4];
extern s16 D_8011B43E_mgmode[4];
extern s16 D_8011B446_mgmode[4];
extern MgmodeModelEntry D_8011997C_mgmode[];
extern u8 D_80119434_mgmode[];
extern HuMtx4F D_8011B3F0_mgmode;
extern s16 D_8011B884_mgmode;
extern u8 D_8011B958_mgmode;
extern s16 D_8011B78A_mgmode;
extern s16 D_8011B79E_mgmode[];
extern s16 D_8011B7A6_mgmode[];
extern s16 D_8011B7AE_mgmode[];
extern s16 D_8011B7B6_mgmode[];
extern u8 D_8011A3CC_mgmode[];
extern s32 D_8011946C_mgmode[];
extern s32 D_80119478_mgmode[];
extern s32 D_80119484_mgmode[];
extern MgmodeEspriteDef D_80119F28_mgmode[];

void func_8010CBFC_mgmode(void);
s16 func_8010DAB8_mgmode(s32 arg0);
void func_8010E494_mgmode(s16 arg0);
void func_8010E6F0_mgmode(s16 arg0);
void func_8010D98C_mgmode(void);
void func_8010E40C_mgmode(void);
void func_8010E1F0_mgmode(void);
void func_8010EE84_mgmode(s16 arg0);
s16 func_8010F348_mgmode(s16 category);
s16 func_8010A148_mgmode(s16 arg0);
void func_8010A5F0_mgmode(void);
void func_8010D308_mgmode(void);
s16 func_8010D3B0_mgmode(s32 arg0);
MgmodeEsprite *func_80116794_mgmode(MgmodeEspriteDef *defs);
void func_801169F0_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2);
void func_80116D4C_mgmode(void);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116A78_mgmode(MgmodeEsprite *arg0, s16 index, s16 tpLvl);
void func_80116A48_mgmode(MgmodeEsprite *arg0, s16 index, f32 x, f32 y);
void func_80118888_mgmode(s16 index);
void func_801188A4_mgmode(s16 index);
s16 func_80116B20_mgmode(void);
void func_80116C18_mgmode(s16 arg0);
void func_80118624_mgmode(s16 dstModel, s16 srcModel);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_8011829C_mgmode(s16 arg0);
void func_801182A8_mgmode(s16 arg0);
s16 func_801182DC_mgmode(s16 stickX, s16 stickY);
void func_80118D0C_mgmode(void);
void func_8010CB20_mgmode(void);
s32 func_8010F648_mgmode(void);
void func_80110554_mgmode(void);
s16 func_80110420_mgmode(s16 mgIndex);
s32 func_80111380_mgmode(void);
void func_80111BB0_mgmode(void);
void func_80111ED8_mgmode(void);
void func_80111F9C_mgmode(void);
void func_80112060_mgmode(s32 arg0);
void func_80116E24_mgmode(s16 arg0);
void func_8011667C_mgmode(MgmodeModelEntry *entries);
s16 func_80118678_mgmode(f32 arg0, f32 arg1, f32 arg2, f32 arg3);

void func_8010BEC0_mgmode(void) {
    s16 size[2];
    HmfMotionNode *node;
    MgmodeModelEntry *entry;
    void *anim;
    s16 choice;
    s16 changed;
    s16 model;
    s16 chr;
    s16 i;

    D_8011B954_mgmode = D_80119344_mgmode;
    D_8011B888_mgmode = 2500.0f;
    HuWinMesMaxSizeBetGet(size, 0x5600, 0x560E);
    D_8011B6A8_mgmode = HuWinExCreate(-1, (320 - size[0]) / 2, 224 - size[1], size[0], size[1], 0);
    HuWinActivePlayerSet(D_8011B6A8_mgmode, 1 << D_8011B808_mgmode);
    HuWinPriSet(D_8011B6A8_mgmode, 5);
    for (i = 0; i < 4; i++) {
        chr = D_8011B43E_mgmode[i] = GwPlayer[i].chr;
        D_8011997C_mgmode[i + 7].unk_00 = func_80017BB8_main(chr, 0xA1);
        D_8011997C_mgmode[i + 11].unk_00 = func_80017BB8_main(chr, 0x2);
        D_8011997C_mgmode[i + 15].unk_00 = func_80017BB8_main(chr, 0x33);
        D_8011997C_mgmode[i + 19].unk_00 = func_80017BB8_main(chr, 0x3A);
        D_8011997C_mgmode[i + 23].unk_00 = func_80017BB8_main(chr, 0x2F);
        D_8011997C_mgmode[i + 27].unk_00 = func_80017BB8_main(chr, D_80119434_mgmode[chr]);
        entry = &D_8011997C_mgmode[i + 7];
        D_8011B446_mgmode[i] = func_80118678_mgmode(entry->pos.x, 400.0f, entry->pos.z, 30.0f);
    }
    func_8011667C_mgmode(D_8011997C_mgmode);
    node = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
    func_8002367C_main(D_8011B3F0_mgmode, node->unk58);
    Hu3DModelCameraSet(D_8011B8A8_mgmode[4], 2);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[4], 0.7f, 0.7f, 0.7f);
    Hu3DModelScaleSet(D_8011B8A8_mgmode[31], 0.7f, 0.7f, 0.7f);
    for (i = 0; i < 4; i++) {
        model = D_8011B8A8_mgmode[i + 7];
        Hu3DModelCameraSet(model, 2);
        func_8001C258_main(model, 4, 4);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        Hu3DModelScaleSet(model, 0.7f, 0.7f, 0.7f);
        D_8011B436_mgmode[i] = func_80017790_main(model, 1, D_8011B43E_mgmode[i],
                                                  func_80017B6C_main(D_8011B43E_mgmode[i], 1, 0));
        func_8001C514_main(model);
    }
    model = D_8011B8A8_mgmode[4];
    anim = DataRead(0xA002A);
    HmfAnimCreate(HmfModelData[model].hmf, anim, 0, "c180n_0_DEF");
    DataClose(anim);
    Hu3DModelRemakeStatic(model);
    func_8001C514_main(model);
    if (omovlevtno != 4) {
        Hu3DMotionSet(D_8011B8A8_mgmode[4], D_8011B78A_mgmode);
        func_8001C814_main(D_8011B8A8_mgmode[4], 2, 2);
        func_80116E24_mgmode(0);
        WipeCreateIn(0xFF, 0);
        RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
        HuAudFXPlay(0x2EB);
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
            func_8002367C_main(node->unk58, D_8011B3F0_mgmode);
            func_80017D24_main(node->unk58, 0.0f, -i * 5, 0.0f);
        }
        func_80116ED4_mgmode(1, 10, 1, (void (*)(s16 *))-1);
        HuPrcSleep(5);
        func_8002367C_main(node->unk58, D_8011B3F0_mgmode);
        func_80116ED4_mgmode(5, 20, 1, (void (*)(s16 *))-1);
    } else {
        D_8011B884_mgmode = 1;
        if (func_8010F648_mgmode()) {
            goto resume;
        }
        func_80116ED4_mgmode(5, 10, 1, (void (*)(s16 *))-1);
        HuAudSeqPlay(0x4C);
    }
    func_8011822C_mgmode(D_80119424_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
    goto loop;
resume:
    HuWinExAnimIn(D_8011B6A8_mgmode);
    HuAudSeqPlay(0x4C);
    func_8010CB20_mgmode();
loop:
    while (TRUE) {
        HuPrcVSleep();
        func_8011829C_mgmode(5);
        switch (D_8011B958_mgmode) {
            case 5:
                if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
                    HuAudFXPlay(2);
                    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
                    func_801182B4_mgmode(0);
                    HuAudFXPlay(0x299);
                    HuWinMesSet(D_8011B6A8_mgmode, 0x5603, -1, -1);
                    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                        HuPrcVSleep();
                    }
                    while (TRUE) {
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5604, -1, -1);
                        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                            HuPrcVSleep();
                        }
                        if ((s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) != 0) {
                            choice = -1;
                            break;
                        }
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5605, -1, -1);
                        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                            HuPrcVSleep();
                        }
                        choice = HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0);
                        if (choice == -1) {
                            continue;
                        }
                        if (choice == 0) {
                            HuWinMesSet(D_8011B6A8_mgmode, 0x5606, -1, -1);
                            while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                                HuPrcVSleep();
                            }
                        }
                        break;
                    }
                    if (choice == -1) {
                        func_801182B4_mgmode(1);
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
                        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                            HuPrcVSleep();
                        }
                    } else {
                        func_8010CB20_mgmode();
                    }
                } else {
                    changed = FALSE;
                    if ((D_800C9520_main[D_8011B808_mgmode] & L_JPAD) ||
                        (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON)) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(20);
                        func_801182A8_mgmode(1);
                        func_80116ED4_mgmode(3, 20, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (D_800C9520_main[D_8011B808_mgmode] & R_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(25);
                        func_801182A8_mgmode(1);
                        func_80116ED4_mgmode(6, 10, 0, (void (*)(s16 *))-1);
                        func_80116ED4_mgmode(3, 15, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (changed) {
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5601, -1, -1);
                        HuWinExAnimIn(D_8011B6A8_mgmode);
                    }
                }
                break;
            case 3:
                if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
                    HuAudFXPlay(2);
                    HuWinMesSet(D_8011B6A8_mgmode, 0x5602, -1, -1);
                    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                        HuPrcVSleep();
                    }
                    if ((s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) != 0) {
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5601, -1, -1);
                        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                            HuPrcVSleep();
                        }
                        break;
                    }
                    func_801182B4_mgmode(0);
                    HuWinExAnimOut(D_8011B6A8_mgmode, 0);
                    func_80116ED4_mgmode(3, 20, 1, (void (*)(s16 *))-1);
                    node = func_8001D33C_main(D_8011B8A8_mgmode[0], "door");
                    RepeatVibrator(D_8011B808_mgmode, 5, 0, 5);
                    HuAudFXPlay(0x2EB);
                    for (i = 0; i < 19; i++) {
                        HuPrcVSleep();
                        func_8002367C_main(node->unk58, D_8011B3F0_mgmode);
                        func_80017D24_main(node->unk58, 0.0f, -i * 5, 0.0f);
                    }
                    func_80116ED4_mgmode(4, 20, 1, (void (*)(s16 *))-1);
                    D_80118EB1_mgmode = 1;
                    D_80118EB4_mgmode = 0x80;
                    HuAudSeqFadeOut(60);
                    while (TRUE) {
                        HuPrcVSleep();
                    }
                } else {
                    changed = FALSE;
                    if (D_800C9520_main[D_8011B808_mgmode] & L_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(25);
                        func_801182A8_mgmode(0);
                        func_80116ED4_mgmode(6, 10, 0, (void (*)(s16 *))-1);
                        func_80116ED4_mgmode(5, 15, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (D_800C9520_main[D_8011B808_mgmode] & R_JPAD) {
                        HuAudFXPlay(1);
                        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
                        func_8011829C_mgmode(20);
                        func_801182A8_mgmode(0);
                        func_80116ED4_mgmode(5, 20, 1, (void (*)(s16 *))-1);
                        changed = TRUE;
                    }
                    if (changed) {
                        HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
                        HuWinExAnimIn(D_8011B6A8_mgmode);
                    }
                }
                break;
        }
        if (HmfModelData[D_8011B8A8_mgmode[4]].motId != D_8011B78A_mgmode &&
            HmfModelData[D_8011B8A8_mgmode[4]].motIdShift != D_8011B78A_mgmode) {
            Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B78A_mgmode, 0, 8, 2);
        }
    }
}

void func_8010CB20_mgmode(void) {
    HuWinMesSet(D_8011B6A8_mgmode, 0x5607, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    func_80116ED4_mgmode(2, 10, 1, (void (*)(s16 *))-1);
    func_8010CBFC_mgmode();
    func_80116ED4_mgmode(5, 10, 1, (void (*)(s16 *))-1);
    func_8011822C_mgmode(D_80119424_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5600, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
}

void func_8010CBFC_mgmode(void) {
    s16 i;
    s16 state;
    s16 back;
    s16 result;
    f32 t;
    f32 sx;
    f32 sy;

    HuPrcSleep(3);
    D_8011B450_mgmode = func_80116794_mgmode(D_80119EB0_mgmode);
    func_80116968_mgmode(D_8011B450_mgmode, 0, 180, 110);
    for (i = 0; i < 9; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, i);
        func_801169F0_mgmode(D_8011B450_mgmode, i, 0x4000);
    }
    HuAudFXPlay(0x243);
    HuPrcSleep(5);
    func_801169A0_mgmode(D_8011B450_mgmode, 0);
    for (i = 0; i < 11; i++) {
        t = i / 10.0f;
        sx = sindf(t * 90.0f);
        sy = cosdf(t * 270.0f + 90.0f);
        if (sy < 0.0f) {
            sy = -sy;
        }
        func_80116A48_mgmode(D_8011B450_mgmode, 0, sx, sy);
        HuPrcVSleep();
    }
    for (i = 0, D_8011B454_mgmode = 0; i < 5; i++) {
        if (D_8011B928_mgmode[i] >= 3) {
            D_8011B458_mgmode[D_8011B454_mgmode] = i;
            D_8011B454_mgmode++;
        }
    }
    D_800D1F2C_main = 0;
    state = 0;
    back = 0;
    while (state != 4) {
        switch (state) {
            case 0:
                D_800CC438_main = func_8010D3B0_mgmode(back);
                if (D_800CC438_main == -1) {
                    func_8010D98C_mgmode();
                    state = 4;
                } else {
                    back = 0;
                    state++;
                }
                break;
            case 1:
                result = func_8010DAB8_mgmode(back);
                if (result == -1) {
                    func_8010E40C_mgmode();
                    back = 1;
                    state--;
                } else {
                    D_800D4194_main = D_8011B458_mgmode[result];
                    if (D_800D4194_main != 1 && D_800D4194_main != 2) {
                        for (i = 0; i < 4; i++) {
                            GwPlayer[i].group = i;
                        }
                        state++;
                    }
                    state++;
                }
                break;
            case 2:
                HuWinMesSet(D_8011B6A8_mgmode, 0x560A, -1, -1);
                while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                    HuPrcVSleep();
                }
                result = func_8010A148_mgmode(D_800D4194_main);
                func_8010A5F0_mgmode();
                if (result != 0) {
                    state++;
                } else {
                    back = 1;
                    state--;
                }
                break;
            case 3:
                for (i = 0; i < 4; i++) {
                    D_800D1F20_main[i] = GwPlayer[i].group;
                }
                func_8010E6F0_mgmode(D_800D4194_main);
                func_8010E1F0_mgmode();
                HuWinMesSet(D_8011B6A8_mgmode, 0x560B, -1, -1);
                while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                    HuPrcVSleep();
                }
                D_800CE29C_main = func_8010F348_mgmode(D_800D4194_main);
                HuPrcSleep(20);
                HuWinInsertMesSet(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
                HuWinMesSet(D_8011B6A8_mgmode, 0x560D, -1, -1);
                while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                    HuPrcVSleep();
                }
                HuWinMesSet(D_8011B6A8_mgmode, 0x560E, -1, -1);
                while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
                    HuPrcVSleep();
                }
                result = HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0);
                if (result == -1) {
                    func_8010EE84_mgmode(D_800D4194_main);
                    func_80116D4C_mgmode();
                    D_80119340_mgmode = -1;
                    state -= 2;
                    if (D_800D4194_main == 1 || D_800D4194_main == 2) {
                        state++;
                    }
                    break;
                }
                if (result == 0) {
                    GwSystem.show_minigame_explanations = 1;
                } else {
                    GwSystem.show_minigame_explanations = 0;
                }
                _SetFlag(0xD);
                for (i = 0; i < 4; i++) {
                    D_800D03FE_main[i] = 0;
                }
                GwSystem.minigame_index = (u8)D_800CE29C_main + 1;
                D_800CB894_main = 100;
                omOvlHisChg(0, 0x69, 4, 0x84);
                D_80118EB1_mgmode = 1;
                D_8011B95A_mgmode = 0x70;
                D_8011B950_mgmode = 0;
                D_80118EB4_mgmode = 2;
                if (D_800D4194_main == 0 || D_800D4194_main == 3) {
                    for (i = 0; i < 4; i++) {
                        GwPlayer[i].star = D_800D03FE_main[i];
                        GwPlayer[i].coin = rand8() & 0xF;
                    }
                }
                while (TRUE) {
                    HuPrcVSleep();
                }
        }
    }
    func_8010D308_mgmode();
    func_80116D4C_mgmode();
    D_80119340_mgmode = -1;
    func_801182B4_mgmode(0);
    func_801168E0_mgmode(D_8011B450_mgmode);
}

void func_8010D308_mgmode(void) {
    s16 i;
    f32 scale;

    HuAudFXPlay(0x244);
    for (i = 0; i < 11; i++) {
        scale = cosdf(i / 10.0f * 90.0f);
        func_80116A48_mgmode(D_8011B450_mgmode, 0, scale, scale);
        HuPrcVSleep();
    }
}

s16 func_8010D3B0_mgmode(s32 arg0) {
    s16 i;
    s16 j;
    s16 frame;
    s16 next;
    s16 sel;
    f32 dist;

    if (arg0 != 0) {
        for (i = 1; i < 6; i++) {
            func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        func_801169C8_mgmode(D_8011B450_mgmode, D_800CC438_main + 1);
    }
    HuWinMesSet(D_8011B6A8_mgmode, 0x5608, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    func_80116968_mgmode(D_8011B450_mgmode, 1, 180, 91);
    func_80116968_mgmode(D_8011B450_mgmode, 2, 180, 121);
    func_80116968_mgmode(D_8011B450_mgmode, 3, 180, 151);
    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - j * 3;
            if (frame < 0) {
                func_801169C8_mgmode(D_8011B450_mgmode, j + 1);
            } else if (frame < 9) {
                func_801169A0_mgmode(D_8011B450_mgmode, j + 1);
                func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, sindf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    sel = 0;
    func_8011822C_mgmode(D_8011943C_mgmode);
    func_801181F4_mgmode(0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            HuPrcSleep(5);
            sel = next;
        } else if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
            HuAudFXPlay(2);
            dist = 47 - D_8011944C_mgmode[sel];
            for (i = 1; i < 6; i++) {
                for (j = 0; j < 3; j++) {
                    if (j == sel) {
                        func_80116968_mgmode(D_8011B450_mgmode, sel + 1, 180,
                                             D_8011944C_mgmode[j] + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            func_801169C8_mgmode(D_8011B450_mgmode, 1);
            func_801169C8_mgmode(D_8011B450_mgmode, 2);
            func_801169C8_mgmode(D_8011B450_mgmode, 3);
            func_801169A0_mgmode(D_8011B450_mgmode, sel + 1);
            break;
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
    }
    func_801182B4_mgmode(0);
    HuPrcSleep(5);
    return sel;
}

void func_8010D98C_mgmode(void) {
    s16 i;
    s16 j;
    s16 frame;

    for (i = 1; i < 15; i++) {
        for (j = 0; j < 3; j++) {
            frame = i - (2 - j) * 3;
            if (frame < 0) {
                continue;
            }
            if (frame >= 9) {
                func_801169C8_mgmode(D_8011B450_mgmode, j + 1);
            } else {
                func_80116A48_mgmode(D_8011B450_mgmode, j + 1, 1.0f, cosdf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
}

s16 func_8010DAB8_mgmode(s32 arg0) {
    s16 i;
    s16 j;
    s16 frame;
    s16 next;
    s16 sel;
    f32 dist;

    if (arg0 != 0) {
        for (i = 1; i < 6; i++) {
            func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 1.0f, cosdf(i / 5.0f * 90.0f));
            HuPrcVSleep();
        }
        func_801169C8_mgmode(D_8011B450_mgmode, D_800D4194_main + 4);
    }
    HuWinMesSet(D_8011B6A8_mgmode, 0x5609, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    for (i = 1; i <= D_8011B454_mgmode * 3 + 8; i++) {
        for (j = 0; j < D_8011B454_mgmode; j++) {
            func_80116968_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 180, j * 22 + 79);
            frame = i - j * 3;
            if (frame < 0) {
                func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4);
            } else if (frame < 9) {
                func_801169A0_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4);
                func_80116A48_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 1.0f,
                                     sindf(frame / 8.0f * 90.0f));
            }
        }
        HuPrcVSleep();
    }
    for (j = 0; j < D_8011B454_mgmode; j++) {
        D_8011B468_mgmode[j] = D_80119454_mgmode[j];
    }
    D_8011B468_mgmode[j].x = D_8011B468_mgmode[j].y = -1;
    sel = 0;
    func_8011822C_mgmode(D_8011B468_mgmode);
    func_801181F4_mgmode(0);
    func_8011829C_mgmode(5);
    func_801182B4_mgmode(1);
    while (TRUE) {
        HuPrcVSleep();
        func_80118D0C_mgmode();
        if (ABS(D_800CBB6E_main[D_8011B808_mgmode]) >= 31 || ABS(D_800D20A1_main[D_8011B808_mgmode]) >= 31) {
            next = func_801182DC_mgmode(-D_800CBB6E_main[D_8011B808_mgmode], D_800D20A1_main[D_8011B808_mgmode]);
            if (next == -1) {
                continue;
            }
            HuAudFXPlay(1);
            func_801182A8_mgmode(next);
            HuPrcSleep(5);
            sel = next;
        } else if (D_800D5558_main[D_8011B808_mgmode] & A_BUTTON) {
            HuAudFXPlay(2);
            dist = -9 - sel * 22;
            for (i = 1; i < 6; i++) {
                for (j = 0; j < D_8011B454_mgmode; j++) {
                    if (j == sel) {
                        func_80116968_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 180,
                                             j * 22 + 79 + dist * sindf(i / 5.0f * 90.0f));
                    } else {
                        func_80116A48_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4, 1.0f,
                                             cosdf(i / 5.0f * 90.0f));
                    }
                }
                HuPrcVSleep();
            }
            for (j = 0; j < 5; j++) {
                func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[j] + 4);
            }
            func_801169A0_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[sel] + 4);
            break;
        } else if (D_800D5558_main[D_8011B808_mgmode] & B_BUTTON) {
            HuAudFXPlay(4);
            sel = -1;
            break;
        }
    }
    func_801182B4_mgmode(0);
    HuPrcSleep(5);
    return sel;
}

void func_8010E1F0_mgmode(void) {
    s16 list[20];
    s16 count;
    s16 i;
    s16 j;
    s16 r;
    s16 tmp;
    s16 category;

    category = D_800D4194_main;
    count = 0;
    for (i = 0; i < D_8011B940_mgmode[category]; i++) {
        if (D_8011B6B0_mgmode[category][i] != 0xFF) {
            list[count++] = D_8011B6B0_mgmode[category][i];
        }
    }
    for (i = 0; i < count * 2; i++) {
        j = i % count;
        r = (rand8() * count) >> 8;
        tmp = list[j];
        list[j] = list[r];
        list[r] = tmp;
    }
    for (i = 0; i < D_8011B928_mgmode[category]; i++) {
        D_800D0418_main[i] = list[i];
    }
}

void func_8010E40C_mgmode(void) {
    s16 i;

    for (i = 0; i < D_8011B454_mgmode; i++) {
        func_801169C8_mgmode(D_8011B450_mgmode, D_8011B458_mgmode[i] + 4);
    }
}

#ifdef NON_MATCHING
// Matches except for one register copy: target emits `move t3,a2` for rank = 0,
// but GCC propagates the constant (`move t3,zero`) whenever `slot = 0` and
// `rank = 0` share a basic block, regardless of how the initializer is written.
// Partial workaround: putting an empty `if (count) {}` between `slot = 0;` and
// `rank = slot;` keeps the copy and gets within 2 instructions, but it's an
// artificial construct. A real fix likely needs a different loop structure.
// Compiler analysis (gcc 2.7.2 sources, -O1): cse.c always swaps a pseudo copy
// for a known constant (const_int costs 0, a pseudo costs 1), so the copy can
// only survive if `slot = 0` and `rank = slot` land in different CSE blocks
// (a used label or a NOTE_INSN_LOOP_END between them). The target's outer-loop
// pretest is still folded to `count != 0`, though, which needs CSE to know that
// rank and slot are both 0. That contradiction is unresolved. A LOOP_END
// boundary (`slot = 0; do {} while (0); for (rank = slot; ...)`) keeps the copy
// but the pretest turns into `slot < count` (score 495). The `move a1,v0` next
// to the pretest is a copy inserted by cse_around_loop. Also brute-forced
// every s16/int/u16/s8/u8/u32 combination for slot/rank with each initializer
// spelling, `slot` initialized in its declaration, before `count`, before or
// in the init of the order loop, `rank`/`slot` aliased onto `arg0`, `for` vs
// `while` vs guarded `do`/`while`, and `for (;;)` with a `break`. None keep
// the copy and the folded pretest. No other function in asm/nonmatchings
// (besides func_8010E6F0_mgmode) and no matched build output shows a
// zero-then-copy between two pseudos, so there's no reference pattern.
void func_8010E494_mgmode(s16 arg0) {
    Vec pos[4];
    s16 order[4];
    s16 count;
    s16 i;
    s16 slot;
    s16 rank;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        order[i] = D_800D1F20_main[i];
    }
    for (slot = 0, rank = 0; rank < count || slot < count; rank++) {
        for (i = 0; i < count; i++) {
            if (rank == order[i]) {
                pos[i].x = slot * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                order[i] = -1;
                slot++;
            }
        }
    }
    for (i = 0; i < count; i++) {
        func_8001C258_main(D_8011B8B6_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8B6_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
        func_8001C258_main(D_8011B8E8_mgmode[i], 4, 0);
        Hu3DModelPosSet(D_8011B8E8_mgmode[i], pos[i].x, pos[i].y, pos[i].z);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E494_mgmode);
#endif

#ifdef NON_MATCHING
// Matches except for one register copy, the same issue as func_8010E494_mgmode:
// target emits `move t2,a2` for rank = 0 (copying slot), but GCC propagates the
// constant (`move t2,zero`). Tried `rank = slot = 0`, a while loop, moving
// `slot = 0` before the order loop or to the top of the function, `|` instead
// of `||`, and the `if (count) {}` workaround from func_8010E494_mgmode; none
// produce the copy without other diffs. See func_8010E494_mgmode for the CSE
// analysis and the list of other loop shapes and types tried; the
// `do {} while (0);` boundary keeps the copy here too but unfolds the pretest
// (score 1204). Notes for the rest of the function:
// the second Hu3DModelPosSet z coordinate really uses delta[i].x (original
// bug), model ids must come from the shared D_8011B8A8_mgmode table in the
// first setup loop to get both table bases hoisted, and `count` must be
// declared before `node` for the stack slots to match.
void func_8010E6F0_mgmode(s16 arg0) {
    Vec pos[4];
    Vec delta[4];
    s16 order[4];
    f32 angle[4];
    s16 count;
    HmfMotionNode *node;
    s16 i;
    s16 j;
    s16 slot;
    s16 rank;
    s16 model;
    f32 t;
    f32 rot;

    rot = 0.0f;
    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        order[i] = D_800D1F20_main[i];
    }
    for (slot = 0, rank = 0; rank < count || slot < count; rank++) {
        for (i = 0; i < count; i++) {
            if (rank == order[i]) {
                pos[i].x = slot * 80 - 122;
                pos[i].y = 26.0f;
                pos[i].z = -312.0f;
                order[i] = -1;
                slot++;
            }
        }
    }
    for (i = 0; i < count; i++) {
        delta[i].x = 400.0f - pos[i].x;
        delta[i].z = 900.0f - pos[i].z;
        func_8001C258_main(D_8011B8A8_mgmode[i + 7], 4, 0);
        Hu3DMotionSet(D_8011B8A8_mgmode[i + 7], D_8011B796_mgmode[i]);
        func_8001C814_main(D_8011B8A8_mgmode[i + 7], 2, 2);
        func_8001C258_main(D_8011B8A8_mgmode[i + 32], 4, 0);
        angle[i] = atan2df(delta[i].x, delta[i].z) + 180.0f;
        Hu3DModelRotSet(D_8011B8A8_mgmode[i + 7], 0.0f, angle[i], 0.0f);
    }
    model = D_8011B8A8_mgmode[4];
    func_8002FD8C_main(model, HmfModelData[model].motId, "c100_1-atama", 0x4C, 0x46);
    node = func_8001D33C_main(model, "c100_1-atama");
    for (j = 0; j < 31; j++) {
        t = 1.0f - sindf(j * 3.0f);
        for (i = 0; i < count; i++) {
            Hu3DModelPosSet(D_8011B8A8_mgmode[i + 7], pos[i].x + t * delta[i].x, pos[i].y, pos[i].z + t * delta[i].x);
            func_80118624_mgmode(D_8011B8A8_mgmode[i + 32], D_8011B8A8_mgmode[i + 7]);
            if (j < 25 && j % 5 == 0) {
                func_8004AC5C_main(GwPlayer[i].chr + 0x29, i);
            }
        }
        if (j < 10) {
            rot = atan2df(HmfModelData[D_8011B8A8_mgmode[7]].pos.x - HmfModelData[D_8011B8A8_mgmode[4]].pos.x,
                          HmfModelData[D_8011B8A8_mgmode[7]].pos.z - HmfModelData[D_8011B8A8_mgmode[4]].pos.z) -
                  HmfModelData[D_8011B8A8_mgmode[4]].rot.y;
            rot *= j / 10.0f;
        } else if (j < 20) {
            rot = atan2df(HmfModelData[D_8011B8A8_mgmode[7]].pos.x - HmfModelData[D_8011B8A8_mgmode[4]].pos.x,
                          HmfModelData[D_8011B8A8_mgmode[7]].pos.z - HmfModelData[D_8011B8A8_mgmode[4]].pos.z) -
                  HmfModelData[D_8011B8A8_mgmode[4]].rot.y;
        } else {
            rot -= 5.0f;
        }
        node->baseRot.y = node->rot.y = rot;
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        Hu3DMotionShiftSet(D_8011B8B6_mgmode[i], D_8011B78E_mgmode[i], 0, 8, 2);
    }
    for (j = 0; j < 9; j++) {
        t = 1.0f - j / 8.0f;
        for (i = 0; i < count; i++) {
            Hu3DModelRotSet(D_8011B8B6_mgmode[i], 0.0f, t * angle[i], 0.0f);
        }
        rot -= 5.0f;
        if (rot < 0.0f) {
            rot = 0.0f;
        }
        node->baseRot.y = node->rot.y = rot;
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010E6F0_mgmode);
#endif

void func_8010EE84_mgmode(s16 arg0) {
    Vec pos[4];
    Vec delta[4];
    f32 angle[4];
    s16 count;
    s16 i;
    s16 j;
    f32 t;

    count = (arg0 != 4) ? 4 : 2;
    for (i = 0; i < count; i++) {
        pos[i].x = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.x;
        pos[i].y = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.y;
        pos[i].z = HmfModelData[D_8011B8A8_mgmode[i + 7]].pos.z;
        delta[i].x = 400.0f - pos[i].x;
        delta[i].z = 900.0f - pos[i].z;
        func_8001C258_main(D_8011B8A8_mgmode[i + 7], 4, 0);
        Hu3DMotionShiftSet(D_8011B8A8_mgmode[i + 7], D_8011B796_mgmode[i], 0, 8, 2);
        angle[i] = atan2df(delta[i].x, delta[i].z);
    }
    for (j = 0; j < 9; j++) {
        t = j / 8.0f;
        for (i = 0; i < count; i++) {
            Hu3DModelRotSet(D_8011B8A8_mgmode[i + 7], 0.0f, t * angle[i], 0.0f);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 31; j++) {
        if (j == 10) {
            Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B78C_mgmode, 0, 8, 2);
        }
        t = 1.0f - sindf(j / 30.0f * 90.0f + 90.0f);
        for (i = 0; i < count; i++) {
            Hu3DModelPosSet(D_8011B8A8_mgmode[i + 7], pos[i].x + t * delta[i].x, pos[i].y, pos[i].z + t * delta[i].z);
            func_80118624_mgmode(D_8011B8A8_mgmode[i + 32], D_8011B8A8_mgmode[i + 7]);
            if (j < 25 && j % 5 == 0) {
                func_8004AC5C_main(GwPlayer[i].chr + 0x29, i);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < count; i++) {
        func_8001C258_main(D_8011B8A8_mgmode[i + 7], 4, 4);
        func_8001C258_main(D_8011B8A8_mgmode[i + 32], 4, 4);
    }
    Hu3DMotionShiftSet(D_8011B8A8_mgmode[4], D_8011B788_mgmode, 0, 8, 2);
}

#ifdef NON_MATCHING
// Matches except for one register: after `prev = idx;`, CSE substitutes `prev`
// for `idx` in the following `list[idx]` access (s0 instead of target s2).
// Reusing `category` for prev/result fixes that but changes register
// allocation priority so that `count` takes s0 and an extra s4 is saved.
s16 func_8010F348_mgmode(s16 category) {
    s16 list[32];
    s16 count;
    s16 i;
    s16 idx;
    s16 prev;

    if (D_80119340_mgmode == -1) {
        D_80119340_mgmode = func_80116B20_mgmode();
        espAttrSet(D_80119340_mgmode, 0x4008);
        espPosSet(D_80119340_mgmode, 180, 134);
        for (i = 0; i < 10; i++) {
            espTPLvlSet(D_80119340_mgmode, i / 10.0f * 255.0f);
            HuPrcVSleep();
        }
    }
    count = 0;
    for (i = 0; i < D_8011B940_mgmode[category]; i++) {
        if (D_8011B6B0_mgmode[category][i] != 0xFF) {
            list[count++] = D_8011B6B0_mgmode[category][i];
        }
    }
    prev = -1;
    idx = (rand8() * count) >> 8;
    func_80116C18_mgmode(D_800A6D40_main[list[idx]].flags & 0x7FF);
    for (i = 0; i < 30; i++) {
        HuPrcVSleep();
        while (idx == prev) {
            idx = (rand8() * count) >> 8;
        }
        prev = idx;
        func_80116C18_mgmode(D_800A6D40_main[list[idx]].flags & 0x7FF);
        HuAudFXPlay(0x104);
    }
    HuPrcVSleep();
    prev = D_800D0418_main[D_800D1F2C_main];
    func_80116C18_mgmode(D_800A6D40_main[prev].flags & 0x7FF);
    HuPrcVSleep();
    HuAudFXPlay(0x105);
    return prev;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_8010F348_mgmode);
#endif

s32 func_8010F648_mgmode(void) {
    s16 i;
    s16 mesId;
    s16 choice;
    s16 count;

    D_800D1F2C_main++;
    if (D_8011B928_mgmode[D_800D4194_main] <= D_800D1F2C_main) {
        D_800D1F2C_main = 0;
    }
    func_80116E24_mgmode(2);
    func_8010E494_mgmode(D_800D4194_main);
    D_8011B450_mgmode = func_80116794_mgmode(D_80119EB0_mgmode);
    func_80116968_mgmode(D_8011B450_mgmode, 0, 180, 110);
    for (i = 0; i < 9; i++) {
        if (i != 0) {
            func_801169C8_mgmode(D_8011B450_mgmode, i);
        }
        func_801169F0_mgmode(D_8011B450_mgmode, i, 0x4000);
    }
    func_801169A0_mgmode(D_8011B450_mgmode, D_800CC438_main + 1);
    func_80116968_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 180, 42);
    func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 0.7f, 0.7f);
    func_801169F0_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 8);
    func_801169A0_mgmode(D_8011B450_mgmode, D_800D4194_main + 4);
    func_80116968_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 180, 59);
    func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 0.7f, 0.7f);
    func_801169F0_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 8);
    D_80119340_mgmode = func_80116B20_mgmode();
    espAttrSet(D_80119340_mgmode, 0x4008);
    espPosSet(D_80119340_mgmode, 180, 134);
    func_80116C18_mgmode(D_800A6D40_main[D_800CE29C_main].flags & 0x7FF);
    WipeCreateIn(0xB, 0xA);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_80110554_mgmode();
    count = func_80110420_mgmode(D_800CE29C_main);
    for (i = 0; i < count; i++) {
        HuWinInsertMesSet(D_8011B6A8_mgmode, GwPlayer[D_8011B430_mgmode[i]].chr + 0x1C00, i);
        Hu3DMotionShiftSet(D_8011B8B6_mgmode[D_8011B430_mgmode[i]], D_8011B79E_mgmode[D_8011B430_mgmode[i]], 0, 8, 0);
        func_80045ED0_main((D_8011A3CC_mgmode[GwPlayer[D_8011B430_mgmode[i]].chr] << 16) | 0x33);
    }
    for (i = 0; i < 4; i++) {
        if (HmfModelData[D_8011B8B6_mgmode[i]].motIdShift == 0xFF) {
            Hu3DMotionShiftSet(D_8011B8B6_mgmode[i], D_8011B7A6_mgmode[i], 0, 8, 0);
        }
    }
    switch (count) {
        case 0:
            HuWinMesSet(D_8011B6A8_mgmode, 0x5613, -1, -1);
            break;
        case 1:
            HuWinMesSet(D_8011B6A8_mgmode, 0x560F, -1, -1);
            break;
        case 2:
            HuWinMesSet(D_8011B6A8_mgmode, 0x5610, -1, -1);
            break;
        case 3:
            HuWinMesSet(D_8011B6A8_mgmode, 0x5611, -1, -1);
            break;
        case 4:
            HuWinMesSet(D_8011B6A8_mgmode, 0x5612, -1, -1);
            break;
    }
    HuWinExAnimIn(D_8011B6A8_mgmode);
    if (func_80111380_mgmode()) {
        for (i = 0; i < D_8011B434_mgmode; i++) {
            HuWinInsertMesSet(D_8011B6A8_mgmode, GwPlayer[D_8011B430_mgmode[i]].chr + 0x1C00, i);
        }
        switch (D_8011B434_mgmode) {
            case 1:
                HuWinMesSet(D_8011B6A8_mgmode, 0x5614, -1, -1);
                break;
            case 2:
                HuWinMesSet(D_8011B6A8_mgmode, 0x5615, -1, -1);
                break;
            case 3:
                HuWinMesSet(D_8011B6A8_mgmode, 0x5616, -1, -1);
                break;
            case 4:
                HuWinMesSet(D_8011B6A8_mgmode, 0x5617, -1, -1);
                break;
        }
        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
            HuPrcVSleep();
        }
        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
        if (D_8011B434_mgmode != 4) {
            for (i = 0; i < D_8011B434_mgmode; i++) {
                Hu3DMotionShiftSet(D_8011B8B6_mgmode[D_8011B430_mgmode[i]], D_8011B7AE_mgmode[D_8011B430_mgmode[i]], 0, 8, 0);
                func_8004AC5C_main(GwPlayer[D_8011B430_mgmode[i]].chr + 0x27E, i);
            }
            HuAudFXPlay(0x248);
            func_80112060_mgmode(1);
        }
        for (i = 0; i < 4; i++) {
            if (HmfModelData[D_8011B8B6_mgmode[i]].motIdShift == 0xFF) {
                Hu3DMotionShiftSet(D_8011B8B6_mgmode[i], D_8011B7B6_mgmode[i], 0, 8, 0);
            }
        }
        mesId = -1;
        switch (D_8011B434_mgmode) {
            case 1:
                mesId = GMesCreate(0x16, GwPlayer[D_8011B430_mgmode[0]].chr);
                GMesPosSet(mesId, 160.0f, 120.0f);
                break;
            case 2:
                mesId = GMesCreate(0x1E, GwPlayer[D_8011B430_mgmode[0]].chr, GwPlayer[D_8011B430_mgmode[1]].chr);
                break;
            case 3:
                mesId = GMesCreate(0x22, GwPlayer[D_8011B430_mgmode[0]].chr, GwPlayer[D_8011B430_mgmode[1]].chr,
                                   GwPlayer[D_8011B430_mgmode[2]].chr);
                break;
            case 4:
                GMesCreate(0x20);
                mesId = -1;
                break;
        }
        if (mesId != -1) {
            while (!(GMesStatGet() & 2)) {
                HuPrcVSleep();
            }
        }
        for (i = 0; i < 60; i++) {
            if (D_800D5558_main[0] & (A_BUTTON | B_BUTTON)) {
                break;
            }
            HuPrcVSleep();
        }
        func_80112060_mgmode(0);
        HuWinExAnimIn(D_8011B6A8_mgmode);
        HuWinMesSet(D_8011B6A8_mgmode, 0x5618, -1, -1);
        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
            HuPrcVSleep();
        }
        choice = (s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) == 0;
        if (mesId != -1) {
            GMesKill(mesId);
        }
        func_80111BB0_mgmode();
        HuWinExAnimOut(D_8011B6A8_mgmode, 0);
        HuAudSeqFadeOut(60);
        func_8010EE84_mgmode(D_800D4194_main);
        func_80111ED8_mgmode();
        func_80111F9C_mgmode();
        func_80116D4C_mgmode();
        D_80119340_mgmode = -1;
        func_8010D308_mgmode();
        func_801168E0_mgmode(D_8011B450_mgmode);
        return choice;
    }
    for (i = 0; i < 90; i++) {
        if (D_800D5558_main[0] & (A_BUTTON | B_BUTTON)) {
            break;
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        Hu3DMotionShiftSet(D_8011B8B6_mgmode[i], D_8011B78E_mgmode[i], 0, 8, 2);
    }
    HuWinMesSet(D_8011B6A8_mgmode, 0x560C, -1, -1);
    HuPrcSleep(10);
    func_80111BB0_mgmode();
    D_800CE29C_main = func_8010F348_mgmode(D_800D4194_main);
    HuPrcSleep(20);
    HuWinInsertMesSet(D_8011B6A8_mgmode, D_800CE29C_main + 0x4700, 0);
    HuWinMesSet(D_8011B6A8_mgmode, 0x560D, -1, -1);
    while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        HuWinMesSet(D_8011B6A8_mgmode, 0x560E, -1, -1);
        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
            HuPrcVSleep();
        }
        choice = HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0);
        if (choice != -1) {
            break;
        }
        HuWinMesSet(D_8011B6A8_mgmode, 0x5619, -1, -1);
        while (HuWinStatGet(D_8011B6A8_mgmode) != 0) {
            HuPrcVSleep();
        }
        if ((s16)HuWinChoiceGet(D_8011B6A8_mgmode, 0, 0) == 0) {
            func_8010EE84_mgmode(D_800D4194_main);
            HuWinExAnimOut(D_8011B6A8_mgmode, 0);
            func_80111ED8_mgmode();
            func_80111F9C_mgmode();
            func_80116D4C_mgmode();
            D_80119340_mgmode = -1;
            func_8010D308_mgmode();
            func_801168E0_mgmode(D_8011B450_mgmode);
            return 0;
        }
    }
    if (choice == 0) {
        GwSystem.show_minigame_explanations = 1;
    } else {
        GwSystem.show_minigame_explanations = 0;
    }
    _SetFlag(0xD);
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = D_800D1F20_main[i];
    }
    GwSystem.minigame_index = (u8)D_800CE29C_main + 1;
    omOvlHisChg(0, 0x69, 4, 0x84);
    D_80118EB1_mgmode = 1;
    D_8011B95A_mgmode = 0x70;
    D_8011B950_mgmode = 0;
    D_80118EB4_mgmode = 2;
    if (D_800D4194_main == 0 || D_800D4194_main == 3) {
        for (i = 0; i < 4; i++) {
            GwPlayer[i].star = D_800D03FE_main[i];
            GwPlayer[i].coin = rand8() & 0xF;
        }
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

s16 func_80110420_mgmode(s16 mgIndex) {
    s16 i;

    D_8011B434_mgmode = 0;
    if (D_800A6D40_main[mgIndex].minigameType != MINIGAME_ITEM) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin + GwPlayer[i].gameCoin >= 10) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].bonusCoin == 0) {
                D_8011B430_mgmode[D_8011B434_mgmode] = i;
                D_8011B434_mgmode++;
            }
        }
    }
    return D_8011B434_mgmode;
}

void func_80110554_mgmode(void) {
    s16 chars[4];
    s16 counts[8]; // Only 2 entries used, but the size matches the original stack frame.
    MgmodeEspriteDef *def;
    u16 sprite;
    s16 i;
    s16 j;
    s16 y;
    f32 scaleX;

    D_8011B484_mgmode = func_8000B838_main(0x12002C);
    for (i = 0; i < 28; i++) {
        sprite = D_8011B488_mgmode[i] = espEntry(D_8011B484_mgmode, 0, 1);
        espDispOff(sprite);
        espAttrSet(sprite, 0x4008);
        espPriSet(sprite, 8);
    }
    D_8011B4C0_mgmode = 0;
    def = &D_80119F28_mgmode[1];
    D_80119F28_mgmode[0].x = 180;
    D_80119F28_mgmode[0].y = 116;
    switch (D_800D4194_main) {
        case 0:
        case 3:
            for (i = 0; i < 4; i++) {
                def->dataNum = D_8011946C_mgmode[D_800CC438_main];
                def->x = 180;
                def->y = i * 24 + 80;
                def->attr &= 0x7FFF;
                def++;
            }
            for (i = 0; i < 4; i++) {
                chars[i] = GwPlayer[i].chr;
            }
            for (i = 0; i < 4; i++) {
                for (j = 0; j < D_800D03FE_main[i]; j++) {
                    espDispOn(D_8011B488_mgmode[D_8011B4C0_mgmode]);
                    espPosSet(D_8011B488_mgmode[D_8011B4C0_mgmode], D_80119490_mgmode[D_800CC438_main * 7 + j] + 180,
                              i * 24 + 80);
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                def->dataNum = D_80119478_mgmode[D_800CC438_main];
                def->x = 180;
                def->y = i * 48 + 93;
                def->attr &= 0x7FFF;
                def++;
            }
            j = 0;
            for (i = 0; i < 4; i++) {
                if (D_800D1F20_main[i] == 0) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[0] = D_800D03FE_main[i];
                }
            }
            for (i = 0; i < 4; i++) {
                if (D_800D1F20_main[i] == 1) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[1] = D_800D03FE_main[i];
                }
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < counts[i]; j++) {
                    espDispOn(D_8011B488_mgmode[D_8011B4C0_mgmode]);
                    espPosSet(D_8011B488_mgmode[D_8011B4C0_mgmode], D_80119490_mgmode[D_800CC438_main * 7 + j] + 180,
                              i * 48 + 93);
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 2:
            def->dataNum = D_8011946C_mgmode[D_800CC438_main];
            def->x = 180;
            def->y = 80;
            def->attr &= 0x7FFF;
            def++;
            def->dataNum = D_80119484_mgmode[D_800CC438_main];
            def->x = 180;
            def->y = 128;
            def->attr &= 0x7FFF;
            j = 0;
            for (i = 0; i < 4; i++) {
                if (D_800D1F20_main[i] == 0) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[0] = D_800D03FE_main[i];
                }
            }
            for (i = 0; i < 4; i++) {
                if (D_800D1F20_main[i] == 1) {
                    chars[j++] = GwPlayer[i].chr;
                    counts[1] = D_800D03FE_main[i];
                }
            }
            for (i = 0; i < 2; i++) {
                if (i == 0) {
                    y = 80;
                } else {
                    y = 128;
                }
                for (j = 0; j < counts[i]; j++) {
                    espDispOn(D_8011B488_mgmode[D_8011B4C0_mgmode]);
                    espPosSet(D_8011B488_mgmode[D_8011B4C0_mgmode], D_80119490_mgmode[D_800CC438_main * 7 + j] + 180, y);
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                def->dataNum = D_8011946C_mgmode[D_800CC438_main];
                def->x = 180;
                def->y = i * 24 + 104;
                def->attr &= 0x7FFF;
                def++;
            }
            for (i = 0; i < 2; i++) {
                chars[i] = GwPlayer[i].chr;
            }
            for (i = 2; i < 4; i++) {
                chars[i] = -1;
            }
            for (i = 0; i < 2; i++) {
                for (j = 0; j < D_800D03FE_main[i]; j++) {
                    espDispOn(D_8011B488_mgmode[D_8011B4C0_mgmode]);
                    espPosSet(D_8011B488_mgmode[D_8011B4C0_mgmode], D_80119490_mgmode[D_800CC438_main * 7 + j] + 180,
                              i * 24 + 104);
                    D_8011B4C0_mgmode++;
                }
            }
            break;
    }
    def = &D_80119F28_mgmode[5];
    for (i = 0; i < 4; i++) {
        if (chars[i] != -1) {
            def->dataNum += chars[i];
            if (D_800CC438_main == 0) {
                def->x = 149;
            } else if (D_800CC438_main == 1) {
                def->x = 128;
            } else {
                def->x = 107;
            }
            if (D_800D4194_main != 4) {
                def->y = i * 24 + 80;
            } else {
                def->y = i * 24 + 104;
            }
        } else {
            def->attr |= 0x8000;
        }
        def++;
    }
    D_8011B480_mgmode = func_80116794_mgmode(D_80119F28_mgmode);
    func_80116A78_mgmode(D_8011B480_mgmode, 0, 0);
    if (D_800CC438_main == 0) {
        scaleX = 8.6f;
    } else if (D_800CC438_main == 1) {
        scaleX = 12.8f;
    } else {
        scaleX = 17.0f;
    }
    if (D_800D4194_main == 4) {
        func_80116A48_mgmode(D_8011B480_mgmode, 0, scaleX, 4.9f);
    } else {
        func_80116A48_mgmode(D_8011B480_mgmode, 0, scaleX, 9.8f);
    }
    for (i = 0; i < 28; i++) {
        espScaleSet(D_8011B488_mgmode[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        func_80116A78_mgmode(D_8011B480_mgmode, i + 5, 0);
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 1, j / 5.0 * 255.0);
        }
        func_80116A78_mgmode(D_8011B480_mgmode, 0, j / 5.0 * 192.0);
        HuPrcVSleep();
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 5, j / 5.0 * 255.0);
        }
        for (i = 0; i < 28; i++) {
            espScaleSet(D_8011B488_mgmode[i], j / 5.0, j / 5.0);
        }
        HuPrcVSleep();
    }
}

#ifdef NON_MATCHING
// Matches except for the `case 4` loop. In the target, the store to
// sprites[count] and the following reads of sprites[count] use separately
// computed addresses (as in `case 2`, where the if/else separates them), and
// the sprites base (sp+0x10) is hoisted into a saved register. The compiled
// version below instead CSEs the store/read addresses.
// Partial (artificial) workaround: inserting `do {} while (0);` between the
// sprites[count] store and espDispOn() in `case 4` fixes all of that, leaving
// only the sign-extended loop index at the loop top allocated to v0 instead of
// a0 (and a `bnez` instead of `bnezl` at the loop end). Loop shape, player
// type/variable, and break/default variations did not fix the remaining diff.
// Further findings: anything that ends a CSE block between the store and the
// reads gives the same 5-line result (`while (0) {}`, wrapping the store in
// `do { ... } while (0)`, `for (j = 0; j < 0; j++) { ... }`, or a label that
// CSE folds away such as `j = 0; if (j != 0) { ... }`), so the kind of boundary
// does not affect the remaining diff. The `bnezl` is only a consequence of
// the index being in a0 (reorg treats a0 as live on the fall-through path).
// In all variants the sign-extended index is a single-block pseudo with no
// overlapping values, so local-alloc picks v0. For a0, either v0 and v1 must
// be busy over its short lifetime, or it must be allocated by global-alloc
// instead, where `i`'s copy preference for v0 would push it off v0.
// Also tried without success: 40 random declaration orders, pointer/byte
// arithmetic and (s32)/(u16) casts for the store or read address, an s32 copy
// of `i` as the index (CSE propagates it away), `j` as the loop variable,
// do/while(0) wrappers around the calls, and storing before loading `player`.
s32 func_80111380_mgmode(void) {
    u16 sprites[4];
    s16 i;
    s16 j;
    s16 count;
    s16 mask;
    s16 y;
    s16 player;
    f32 tpLvl;
    f32 scale;

    count = 0;
    if (D_8011B434_mgmode == 0) {
        return 0;
    }
    switch (D_800D4194_main) {
        case 0:
        case 3:
            for (i = 0; i < D_8011B434_mgmode; i++) {
                player = D_8011B430_mgmode[i];
                sprites[i] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                count++;
                espDispOn(sprites[i]);
                espPosSet(sprites[i], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[player]] + 180,
                          player * 24 + 80);
                D_8011B4C0_mgmode++;
            }
            break;
        case 1:
            mask = 0;
            for (i = 0; i < D_8011B434_mgmode; i++) {
                player = D_8011B430_mgmode[i];
                if (!((mask >> D_800D1F20_main[player]) & 1)) {
                    mask |= 1 << D_800D1F20_main[player];
                    sprites[count] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                    espDispOn(sprites[count]);
                    espPosSet(sprites[count], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[player]] + 180,
                              D_800D1F20_main[player] * 48 + 93);
                    count++;
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 2:
            mask = 0;
            for (i = 0; i < D_8011B434_mgmode; i++) {
                player = D_8011B430_mgmode[i];
                if (!((mask >> D_800D1F20_main[player]) & 1)) {
                    mask |= 1 << D_800D1F20_main[player];
                    sprites[count] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                    if (D_800D1F20_main[player] == 0) {
                        y = 80;
                    } else {
                        y = 128;
                    }
                    espDispOn(sprites[count]);
                    espPosSet(sprites[count], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[player]] + 180, y);
                    count++;
                    D_8011B4C0_mgmode++;
                }
            }
            break;
        case 4:
            for (i = 0; i < D_8011B434_mgmode; i++) {
                player = D_8011B430_mgmode[i];
                sprites[count] = D_8011B488_mgmode[D_8011B4C0_mgmode];
                espDispOn(sprites[count]);
                espPosSet(sprites[count], D_80119490_mgmode[D_800CC438_main * 7 + D_800D03FE_main[player]] + 180,
                          player * 24 + 104);
                count++;
                D_8011B4C0_mgmode++;
            }
            break;
    }
    for (i = 0; i < D_8011B434_mgmode; i++) {
        D_800D03FE_main[D_8011B430_mgmode[i]]++;
    }
    for (i = 0, D_8011B434_mgmode = 0; i < 4; i++) {
        if (D_800D03FE_main[i] >= D_80119430_mgmode[D_800CC438_main]) {
            D_8011B430_mgmode[D_8011B434_mgmode] = i;
            D_8011B434_mgmode++;
            if (!(GwPlayer[i].stat & 1)) {
                RepeatVibrator(GwPlayer[i].pad, 10, 0, 10);
            }
        }
    }
    if (D_8011B434_mgmode != 0) {
        HuAudFXPlay(0x24B);
    } else {
        HuAudFXPlay(0x24A);
    }
    for (i = 0; i < 31; i++) {
        tpLvl = sindf(i * 3.0f) * 255.0f;
        scale = sindf(i * 5.0f) * 2;
        for (j = 0; j < count; j++) {
            espTPLvlSet(sprites[j], tpLvl);
            espScaleSet(sprites[j], scale, scale);
        }
        HuPrcVSleep();
    }
    return D_8011B434_mgmode != 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/473130", func_80111380_mgmode);
#endif

s32 func_80111B08_mgmode(void) {
    s16 i;

    func_80110420_mgmode(D_800CE29C_main);
    for (i = 0; i < D_8011B434_mgmode; i++) {
        if (D_800D03FE_main[D_8011B430_mgmode[i]] + 1 >= D_80119430_mgmode[D_800CC438_main]) {
            return 1;
        }
    }
    return 0;
}

void func_80111BB0_mgmode(void) {
    s16 i;
    s16 j;

    for (i = 0; i < 28; i++) {
        espScaleSet(D_8011B488_mgmode[i], 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        func_80116A78_mgmode(D_8011B480_mgmode, i + 5, 0);
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 5, (1.0 - j / 5.0) * 255.0);
        }
        for (i = 0; i < 28; i++) {
            espScaleSet(D_8011B488_mgmode[i], 1.0 - j / 5.0, 1.0 - j / 5.0);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 6; j++) {
        for (i = 0; i < 4; i++) {
            func_80116A78_mgmode(D_8011B480_mgmode, i + 1, (1.0 - j / 5.0) * 255.0);
        }
        func_80116A78_mgmode(D_8011B480_mgmode, 0, (1.0 - j / 5.0) * 192.0);
        HuPrcVSleep();
    }
    func_801168E0_mgmode(D_8011B480_mgmode);
    for (i = 0; i < 28; i++) {
        espKill(D_8011B488_mgmode[i]);
    }
    HuSprAnimKill(D_8011B484_mgmode);
}

void func_80111ED8_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800D4194_main + 4, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80111F9C_mgmode(void) {
    s16 i;

    for (i = 0; i < 6; i++) {
        func_80116A48_mgmode(D_8011B450_mgmode, D_800CC438_main + 1, 0.7f, (1.0f - i / 5.0f) * 0.7f);
        HuPrcVSleep();
    }
}

void func_80112060_mgmode(s32 arg0) {
    s16 order[4];
    s16 i;
    s16 j;
    s16 k;
    s16 count;

    for (j = 0; j < 4; j++) {
        order[j] = D_800D1F20_main[j];
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == order[j]) {
                for (k = 0; k < D_8011B434_mgmode; k++) {
                    if (D_8011B430_mgmode[k] == j) {
                        break;
                    }
                }
                if (k != D_8011B434_mgmode) {
                    if (arg0) {
                        func_80118888_mgmode(count);
                    } else {
                        func_801188A4_mgmode(count);
                    }
                    order[j] = -1;
                }
                count++;
            }
        }
    }
}
