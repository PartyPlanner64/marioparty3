#include "common.h"
#include "game/hmfmath.h"

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern Vec D_80111AD0_mstory4;
extern Vec D_80111ADC_mstory4;
extern Vec D_80111AE8_mstory4;

extern s32 D_80111AC0_mstory4;
extern s32 D_80111AC4_mstory4;
extern s32 D_80111AC8_mstory4;
extern s8 D_80111ACC_mstory4;
extern s32 D_80111AF4_mstory4;
extern s16 D_80112120_mstory4;
extern s16 D_80112122_mstory4;
extern s32 D_80112124_mstory4;
extern u16 D_80112128_mstory4;
extern s32 D_801121B4_mstory4;
extern s16 D_80112130_mstory4[8];
extern s16 D_80112140_mstory4[7][8];
extern s16 D_801121B0_mstory4;
extern const s32 D_80111C34_mstory4[7];
extern const s16 D_80111C50_mstory4[][2];
extern s32 D_801123B0_mstory4[4];
extern void (*const D_80111C10_mstory4[])(void);
extern const s32 D_80111C18_mstory4[];

void MBDBackKill(void);
void MBDBackClose(void);
void func_80106134_mstory4(void);
void func_80106B2C_mstory4(void);
void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames);
void func_80106DBC_mstory4(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_8010700C_mstory4(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801072D8_mstory4(omObjData *obj, const Vec *pos, s32 frames);
s32 func_801074F8_mstory4(s16 model);
void func_80105C90_mstory4(omObjData *obj);
void func_80105DA8_mstory4(omObjData *obj);
void func_80105F40_mstory4(void);
void func_80106068_mstory4(omObjData *obj);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);

void func_801059A0_mstory4(void) {
    omObjData *obj;
    s16 chapter;
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                D_801123B0_mstory4[count] = i;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }
    func_800142A0_main(60);
    omInitObjMan(30, 30);
    HuWinInit();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_80106068_mstory4);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80106068_mstory4(obj);
    omAddObj(0, 0, 0, -1, func_80105C90_mstory4);
    omAddObj(0, 0, 0, -1, func_80105DA8_mstory4);
    func_80105F40_mstory4();
    for (D_80112124_mstory4 = 0; D_80112124_mstory4 < 4; D_80112124_mstory4++) {
        if (CheckControllerRead(D_80112124_mstory4)) {
            break;
        }
    }
    if (D_80112124_mstory4 >= 4) {
        D_80112124_mstory4 = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    D_80111C10_mstory4[chapter]();
    if (_CheckFlag(D_80111C18_mstory4[chapter])) {
        D_80111AC8_mstory4 = 1;
    } else {
        _SetFlag(D_80111C18_mstory4[chapter]);
    }
    WipeCreateIn(2, 16);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C18_mstory4);

void func_80105C90_mstory4(omObjData *obj) {
    u32 state = D_80111AC0_mstory4;
    s32 btn;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            state += WipeStatGet() == 0;
            break;
        case 2:
            if (D_80111AC8_mstory4 == 1) {
                btn = D_800D5558_main[D_80112124_mstory4] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(WIPE_STARS, 20);
            } else {
                WipeCreateOut(WIPE_FADE, 20);
            }
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                if (D_80111AC4_mstory4 == 1) {
                    MBDBackKill();
                    MBDBackClose();
                }
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    D_80111AC0_mstory4 = state;
}

void func_80105DA8_mstory4(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80111ACC_mstory4 == 0) {
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(WIPE_STARS, 20);
            } else {
                WipeCreateOut(WIPE_FADE, 20);
            }
            D_80111ACC_mstory4 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            if (D_80111AC4_mstory4 == 1) {
                MBDBackKill();
                MBDBackClose();
            }
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E58_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    Hu3DMotionTimeSet(D_80112122_mstory4, 0.0f);
    HuAudFXPlay(0x217);
}

void func_80105EAC_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 4);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    Hu3DMotionTimeSet(D_80112122_mstory4, D_800CCF58_main[Hu3DData[D_80112122_mstory4].motId].unk02);
}

void func_80105F40_mstory4(void) {
    D_80112128_mstory4 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_80112128_mstory4, 160, 120);
    espAttrSet(D_80112128_mstory4, 0x4000);
    D_80112122_mstory4 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80112122_mstory4, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80112122_mstory4, 2, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 1);
}

void func_80106000_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_80112128_mstory4);
}

void func_80106034_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_80112128_mstory4);
}

void func_80106068_mstory4(omObjData *obj) {
    D_800CE17C_main[0] = D_80111AD0_mstory4.x;
    D_800CE17C_main[1] = D_80111AD0_mstory4.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80111AD0_mstory4, &D_80111ADC_mstory4, &D_80111AE8_mstory4);
    Hu3DCamUpdateMtx(0);
}

void func_801060E8_mstory4(void) {
    D_80111AC0_mstory4 = 3;
}

void func_801060F8_mstory4(s32 arg0) {
    D_801121B4_mstory4 = arg0;
    D_80111AF4_mstory4 = 0;
    omAddPrcObj(func_80106134_mstory4, 0x1000, 0x800, 0);
}

void func_80106134_mstory4(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;
    s32 k;

    D_80112130_mstory4[0] = espEntry(func_8000B838_main(0x1D0001), 0, 0);
    espPosSet(D_80112130_mstory4[0], 160, 120);
    espDispOff(D_80112130_mstory4[0]);
    for (i = 0; i < 7; i++) {
        D_80112130_mstory4[i + 1] = espEntry(func_8000B838_main(D_80111C34_mstory4[i]), 0, 0);
        espPosSet(D_80112130_mstory4[i + 1], D_80111C50_mstory4[i][0] + 48, D_80111C50_mstory4[i][1] + 48);
        espAttrSet(D_80112130_mstory4[i + 1], 8);
        espDispOff(D_80112130_mstory4[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            D_80112140_mstory4[j][i] = espEntry(HuSprAnimRead(data), 0, 1);
            x = D_80111C50_mstory4[j][0] + 48;
            y = D_80111C50_mstory4[j][1] + 48;
            angle = i * 45.0f;
            x += cosdf(angle) * 32.0f;
            y -= sindf(angle) * 32.0f;
            espPosSet(D_80112140_mstory4[j][i], x, y);
            espAttrSet(D_80112140_mstory4[j][i], 0x1000);
            espColorSet(D_80112140_mstory4[j][i], 255, 255, 192);
            espAttrSet(D_80112140_mstory4[j][i], 8);
            espScaleSet(D_80112140_mstory4[j][i], 1.5f, 1.5f);
            espTPLvlSet(D_80112140_mstory4[j][i], 255);
            espDispOff(D_80112140_mstory4[j][i]);
        }
    }
    HuMemMemoryFreePerm(data);
    D_801121B0_mstory4 = espEntry(func_8000B838_main(0x1D0000), 0, 0);
    espPosSet(D_801121B0_mstory4, 160, 120);
    espScaleSet(D_801121B0_mstory4, 40.0f, 30.0f);
    espAttrSet(D_801121B0_mstory4, 0);
    espDispOff(D_801121B0_mstory4);
    omPrcSetDestructor(0, func_80106B2C_mstory4);
    espDispOn(D_801121B0_mstory4);
    espTPLvlSet(D_801121B0_mstory4, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801121B0_mstory4, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801121B0_mstory4, 256);
    for (i = 0; i < D_801121B4_mstory4; i++) {
        espDispOn(D_80112130_mstory4[i + 1]);
    }
    func_80106000_mstory4();
    espDispOn(D_80112130_mstory4[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801121B0_mstory4, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801121B0_mstory4);
    espTPLvlSet(D_80112130_mstory4[D_801121B4_mstory4 + 1], 0);
    espDispOn(D_80112130_mstory4[D_801121B4_mstory4 + 1]);
    for (k = 0, tpLvl = 0.0f; k < 20; k++) {
        tpLvl += 12.75f;
        espTPLvlSet(D_80112130_mstory4[D_801121B4_mstory4 + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(D_80112130_mstory4[D_801121B4_mstory4 + 1], 255);
    espScaleSet(D_80112130_mstory4[D_801121B4_mstory4 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(D_80112140_mstory4[D_801121B4_mstory4][i], 0, 0);
        func_8000BDDC_main(D_80112140_mstory4[D_801121B4_mstory4][i], 1);
        espDispOn(D_80112140_mstory4[D_801121B4_mstory4][i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(D_80112140_mstory4[D_801121B4_mstory4][i]);
    }
    HuPrcSleep(30);
    HuAudFXPlay(0x131);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            espBankSet(D_80112140_mstory4[j][i], 0, 0);
            func_8000BDDC_main(D_80112140_mstory4[j][i], 1);
            espDispOn(D_80112140_mstory4[j][i]);
        }
    }
    HuPrcSleep(20);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            espDispOff(D_80112140_mstory4[j][i]);
        }
    }
    if (D_801121B4_mstory4 != 6) {
        HuPrcSleep(60);
    } else {
        HuPrcSleep(40);
        HuAudFXPlay(0x221);
        for (j = 0; j < 2; j++) {
            espDispOn(D_801121B0_mstory4);
            espTPLvlSet(D_801121B0_mstory4, 0);
            for (i = 0; i < 7; i++) {
                espTPLvlSet(D_801121B0_mstory4, i * (1.0f / 7.0f) * 255.0f);
                HuPrcVSleep();
            }
            espTPLvlSet(D_801121B0_mstory4, 256);
            HuPrcSleep(3);
            for (i = 0; i < 7; i++) {
                espTPLvlSet(D_801121B0_mstory4, 255.0f - i * (1.0f / 7.0f) * 255.0f);
                HuPrcVSleep();
            }
            espDispOff(D_801121B0_mstory4);
            HuPrcSleep(5);
        }
    }
    espDispOn(D_801121B0_mstory4);
    espTPLvlSet(D_801121B0_mstory4, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801121B0_mstory4, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801121B0_mstory4, 256);
    espDispOff(D_80112130_mstory4[D_801121B4_mstory4 + 1]);
    espDispOff(D_80112130_mstory4[0]);
    func_80106034_mstory4();
    HuPrcSleep(30);
    for (i = 0; i < D_801121B4_mstory4; i++) {
        espDispOff(D_80112130_mstory4[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801121B0_mstory4, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801121B0_mstory4);
    D_80111AF4_mstory4 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106B20_mstory4(void) {
    return D_80111AF4_mstory4;
}

void func_80106B2C_mstory4(void) {
}

void func_80106B34_mstory4(void) {
}

void func_80106B3C_mstory4(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            entry = &D_800D1714_main[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void func_80106C10_mstory4(void) {
    D_80112120_mstory4 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_80112120_mstory4, 1 << D_80112124_mstory4);
    HuWinInsertMesSet(D_80112120_mstory4, GwStory.unk1 + 0x1C00, 0);
}

void func_80106C78_mstory4(void) {
    HuWinHomeClear(D_80112120_mstory4);
    func_80060C14_main(D_80112120_mstory4, 1);
}

void func_80106CA8_mstory4(void) {
    func_80060EA8_main(D_80112120_mstory4, 1);
}

void func_80106CCC_mstory4(s32 mess) {
    HuWinMesSet(D_80112120_mstory4, mess, -1, -1);
    while (HuWinStatGet(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

void func_80106D20_mstory4(s32 mess) {
    HuWinMesSet(D_80112120_mstory4, mess, -1, -1);
}

void func_80106D4C_mstory4(void) {
    while (HuWinStatGet(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106D88_mstory4(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106DBC_mstory4(obj, pos, frames, 1);
}

void func_80106DBC_mstory4(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, -5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, -5.0f, pos->z);
    }
    HuPrcVSleep();
}

void func_80106FF0_mstory4(omObjData *obj, Vec *pos, s32 frames) {
    func_8010700C_mstory4(obj, pos, frames, 1);
}

void func_8010700C_mstory4(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, cur.y, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    HuPrcVSleep();
}

void func_80107220_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DA0_mstory4(obj, &pos, frames);
}

void func_8010724C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DBC_mstory4(obj, &pos, frames, arg3);
}

void func_8010727C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106FF0_mstory4(obj, &pos, frames);
}

void func_801072A8_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010700C_mstory4(obj, &pos, frames, arg3);
}

void func_801072D8_mstory4(omObjData *obj, const Vec *target, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model = obj->model[1];
    f32 t;
    f32 angle;

    start.x = Hu3DData[model].rot.x;
    start.y = Hu3DData[model].rot.y;
    start.z = Hu3DData[model].rot.z;
    delta.x = target->x - start.x;
    delta.y = target->y - start.y;
    delta.z = target->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        angle = 90.0f / frames * t;
        rot.x = sindf(angle) * delta.x + start.x;
        rot.y = sindf(angle) * delta.y + start.y;
        rot.z = sindf(angle) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, target->x, target->y, target->z);
    HuPrcVSleep();
}

void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_801072D8_mstory4(obj, &pos, frames);
}

void func_801074AC_mstory4(s16 model) {
    HuPrcSleep(10);
    while (!func_801074F8_mstory4(model)) {
        HuPrcVSleep();
    }
}

s32 func_801074F8_mstory4(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C50_mstory4);
