#include "common.h"
#include "game/hmfmath.h"

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011473C_mstory5;
extern Vec D_80114748_mstory5;
extern Vec D_80114754_mstory5;

extern s32 D_80114730_mstory5;
extern s32 D_80114734_mstory5;
extern s8 D_80114738_mstory5;
extern s32 D_80114760_mstory5;
extern s16 D_801151B0_mstory5;
extern s16 D_801151B2_mstory5;
extern s32 D_801151B4_mstory5;
extern void (*const D_801148A0_mstory5[])(void);
extern const s32 D_801148A8_mstory5[];
extern u16 D_801151B8_mstory5;
extern s32 D_801151E4_mstory5;
extern s16 D_801151C0_mstory5[8];
extern s16 D_801151D0_mstory5[8];
extern s16 D_801151E0_mstory5;
extern const s32 D_801148C4_mstory5[7];
extern const s16 D_801148E0_mstory5[][2];

void func_80106028_mstory5(void);
void func_801068D4_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106DB4_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, const Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
s32 func_801072A0_mstory5(s16 model);
void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames);
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);

void func_801059A0_mstory5(void) {
    omObjData *obj;
    s16 chapter;

    func_800142A0_main(60);
    omInitObjMan(30, 30);
    HuWinInit();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_80105F5C_mstory5);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80105F5C_mstory5(obj);
    omAddObj(0, 0, 0, -1, func_80105BDC_mstory5);
    omAddObj(0, 0, 0, -1, func_80105CCC_mstory5);
    func_80105E34_mstory5();
    for (D_801151B4_mstory5 = 0; D_801151B4_mstory5 < 4; D_801151B4_mstory5++) {
        if (CheckControllerRead(D_801151B4_mstory5)) {
            break;
        }
    }
    if (D_801151B4_mstory5 >= 4) {
        D_801151B4_mstory5 = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    D_801148A0_mstory5[chapter]();
    if (_CheckFlag(D_801148A8_mstory5[chapter])) {
        D_80114734_mstory5 = 1;
    } else {
        _SetFlag(D_801148A8_mstory5[chapter]);
    }
    WipeCreateIn(2, 16);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148A0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148A8_mstory5);

void func_80105BDC_mstory5(omObjData *obj) {
    u32 state = D_80114730_mstory5;
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
            if (D_80114734_mstory5 == 1) {
                btn = D_800D5558_main[D_801151B4_mstory5] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    D_80114730_mstory5 = state;
}

void func_80105CCC_mstory5(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114738_mstory5 == 0) {
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            D_80114738_mstory5 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105D4C_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    Hu3DMotionTimeSet(D_801151B2_mstory5, 0.0f);
    HuAudFXPlay(0x216);
}

void func_80105DA0_mstory5(void) {
    func_8001C814_main(D_801151B2_mstory5, 4, 4);
    func_8001C814_main(D_801151B2_mstory5, 1, 0);
    Hu3DMotionTimeSet(D_801151B2_mstory5, D_800CCF58_main[Hu3DData[D_801151B2_mstory5].motId].unk02);
}

void func_80105E34_mstory5(void) {
    D_801151B8_mstory5 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_801151B8_mstory5, 160, 120);
    espAttrSet(D_801151B8_mstory5, 0x4000);
    D_801151B2_mstory5 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801151B2_mstory5, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801151B2_mstory5, 2, 0);
    func_8001C814_main(D_801151B2_mstory5, 1, 1);
}

void func_80105EF4_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_801151B8_mstory5);
}

void func_80105F28_mstory5(void) {
    func_8001C258_main(D_801151B2_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_801151B8_mstory5);
}

void func_80105F5C_mstory5(omObjData *obj) {
    D_800CE17C_main[0] = D_8011473C_mstory5.x;
    D_800CE17C_main[1] = D_8011473C_mstory5.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_8011473C_mstory5, &D_80114748_mstory5, &D_80114754_mstory5);
    Hu3DCamUpdateMtx(0);
}

void func_80105FDC_mstory5(void) {
    D_80114730_mstory5 = 3;
}

void func_80105FEC_mstory5(s32 arg0) {
    D_801151E4_mstory5 = arg0;
    D_80114760_mstory5 = 0;
    omAddPrcObj(func_80106028_mstory5, 0x1000, 0x800, 0);
}

void func_80106028_mstory5(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    D_801151C0_mstory5[0] = espEntry(func_8000B838_main(0x1D0001), 0, 0);
    espPosSet(D_801151C0_mstory5[0], 160, 120);
    espDispOff(D_801151C0_mstory5[0]);
    for (i = 0; i < 7; i++) {
        D_801151C0_mstory5[i + 1] = espEntry(func_8000B838_main(D_801148C4_mstory5[i]), 0, 0);
        espPosSet(D_801151C0_mstory5[i + 1], D_801148E0_mstory5[i][0] + 48, D_801148E0_mstory5[i][1] + 48);
        espAttrSet(D_801151C0_mstory5[i + 1], 8);
        espDispOff(D_801151C0_mstory5[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_801151D0_mstory5[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = D_801148E0_mstory5[D_801151E4_mstory5][0] + 48;
        y = D_801148E0_mstory5[D_801151E4_mstory5][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(D_801151D0_mstory5[i], x, y);
        espAttrSet(D_801151D0_mstory5[i], 0x1000);
        espColorSet(D_801151D0_mstory5[i], 255, 255, 192);
        espAttrSet(D_801151D0_mstory5[i], 8);
        espScaleSet(D_801151D0_mstory5[i], 1.5f, 1.5f);
        espTPLvlSet(D_801151D0_mstory5[i], 255);
        espDispOff(D_801151D0_mstory5[i]);
    }
    HuMemMemoryFreePerm(data);
    D_801151E0_mstory5 = espEntry(func_8000B838_main(0x1D0000), 0, 0);
    espPosSet(D_801151E0_mstory5, 160, 120);
    espScaleSet(D_801151E0_mstory5, 40.0f, 30.0f);
    espAttrSet(D_801151E0_mstory5, 0);
    espDispOff(D_801151E0_mstory5);
    omPrcSetDestructor(0, func_801068D4_mstory5);
    espDispOn(D_801151E0_mstory5);
    espTPLvlSet(D_801151E0_mstory5, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801151E0_mstory5, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801151E0_mstory5, 256);
    for (i = 0; i < D_801151E4_mstory5; i++) {
        espDispOn(D_801151C0_mstory5[i + 1]);
    }
    func_80105EF4_mstory5();
    espDispOn(D_801151C0_mstory5[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801151E0_mstory5, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801151E0_mstory5);
    espTPLvlSet(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 0);
    espDispOn(D_801151C0_mstory5[D_801151E4_mstory5 + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(D_801151C0_mstory5[D_801151E4_mstory5 + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 255);
    espScaleSet(D_801151C0_mstory5[D_801151E4_mstory5 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(D_801151D0_mstory5[i], 0, 0);
        func_8000BDDC_main(D_801151D0_mstory5[i], 1);
        espDispOn(D_801151D0_mstory5[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(D_801151D0_mstory5[i]);
    }
    if (D_801151E4_mstory5 == 6) {
        HuPrcSleep(40);
        espDispOn(D_801151E0_mstory5);
        espTPLvlSet(D_801151E0_mstory5, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_801151E0_mstory5, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(D_801151E0_mstory5, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_801151E0_mstory5, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(D_801151E0_mstory5);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(D_801151E0_mstory5);
    espTPLvlSet(D_801151E0_mstory5, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801151E0_mstory5, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801151E0_mstory5, 256);
    espDispOff(D_801151C0_mstory5[D_801151E4_mstory5 + 1]);
    espDispOff(D_801151C0_mstory5[0]);
    func_80105F28_mstory5();
    HuPrcSleep(30);
    for (i = 0; i < D_801151E4_mstory5; i++) {
        espDispOff(D_801151C0_mstory5[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801151E0_mstory5, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801151E0_mstory5);
    D_80114760_mstory5 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_801068C8_mstory5(void) {
    return D_80114760_mstory5;
}

void func_801068D4_mstory5(void) {
}

void func_801068DC_mstory5(void) {
}

void func_801068E4_mstory5(s16 model, s16 animSlot, s16 anim) {
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

void func_801069B8_mstory5(void) {
    D_801151B0_mstory5 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_801151B0_mstory5, 1 << D_801151B4_mstory5);
    HuWinInsertMesSet(D_801151B0_mstory5, GwStory.unk1 + 0x1C00, 0);
}

void func_80106A20_mstory5(void) {
    HuWinHomeClear(D_801151B0_mstory5);
    func_80060C14_main(D_801151B0_mstory5, 1);
}

void func_80106A50_mstory5(void) {
    func_80060EA8_main(D_801151B0_mstory5, 1);
}

void func_80106A74_mstory5(s32 mess) {
    HuWinMesSet(D_801151B0_mstory5, mess, -1, -1);
    while (HuWinStatGet(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

void func_80106AC8_mstory5(s32 mess) {
    HuWinMesSet(D_801151B0_mstory5, mess, -1, -1);
}

void func_80106AF4_mstory5(void) {
    while (HuWinStatGet(D_801151B0_mstory5) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106B30_mstory5(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106B48_mstory5(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106B64_mstory5(obj, pos, frames, 1);
}

void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void func_80106D98_mstory5(omObjData *obj, Vec *pos, s32 frames) {
    func_80106DB4_mstory5(obj, pos, frames, 1);
}

void func_80106DB4_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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

void func_80106FC8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B48_mstory5(obj, &pos, frames);
}

void func_80106FF4_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B64_mstory5(obj, &pos, frames, arg3);
}

void func_80107024_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D98_mstory5(obj, &pos, frames);
}

void func_80107050_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DB4_mstory5(obj, &pos, frames, arg3);
}

void func_80107080_mstory5(omObjData *obj, const Vec *target, s32 frames) {
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

void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80107080_mstory5(obj, &pos, frames);
}

void func_80107254_mstory5(s16 model) {
    HuPrcSleep(10);
    while (!func_801072A0_mstory5(model)) {
        HuPrcVSleep();
    }
}

s32 func_801072A0_mstory5(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x += dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}

void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec vel;
    Vec pos;
    Vec accel;
    Vec target;
    s16 model;
    f32 t;

    target.x = x;
    target.y = y;
    target.z = z;
    model = obj->model[1];
    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = target.x - start.x;
    diff.y = target.y - start.y;
    diff.z = target.z - start.z;
    if (faceDir) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    t = frames;
    accel.x = diff.x / t / 90.0f;
    accel.y = diff.y / t / 90.0f;
    accel.z = diff.z / t / 90.0f;
    vel.x = diff.x / t;
    vel.y = diff.y / t;
    vel.z = diff.z / t;
    pos.x = start.x;
    pos.y = start.y;
    pos.z = start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        if (t < 50.0f) {
            pos.x += vel.x;
            pos.y += vel.y;
            pos.z += vel.z;
        } else {
            pos.x += vel.x += accel.x;
            pos.y += vel.y += accel.y;
            pos.z += vel.z += accel.z;
        }
        if (pos.x <= target.x) {
            pos.x = target.x;
            pos.y = target.y;
            pos.z = target.z;
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            if (obj->model[2] >= 0) {
                Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
            }
            break;
        }
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, target.x, target.y, target.z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], target.x, target.y - 5.0f, target.z);
    }
    HuPrcVSleep();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148C4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148E0_mstory5);
