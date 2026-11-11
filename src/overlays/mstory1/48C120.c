#include "common.h"
#include "game/hmfmath.h"

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_80114A8C_mstory1;
extern Vec D_80114A98_mstory1;
extern Vec D_80114AA4_mstory1;

extern s32 D_80114A80_mstory1;
extern s32 D_80114A84_mstory1;
extern s8 D_80114A88_mstory1;
extern s32 D_80114AB0_mstory1;
extern s16 D_801158B0_mstory1;
extern s16 D_801158B2_mstory1;
extern u16 D_801158B8_mstory1;
extern s32 D_801158B4_mstory1;
extern s32 D_801158E4_mstory1;
extern s16 D_801158C0_mstory1[8];
extern s16 D_801158D0_mstory1[8];
extern s16 D_801158E0_mstory1;
extern const s32 D_80114C6C_mstory1[7];
extern const s16 D_80114C88_mstory1[][2];

void func_80105FF4_mstory1(void);
void func_801068A0_mstory1(void);
void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106D80_mstory1(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_8010704C_mstory1(omObjData *obj, const Vec *pos, s32 frames);
s32 func_8010726C_mstory1(s16 model);
void func_80106984_mstory1(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C50_mstory1);

void func_80105C90_mstory1(omObjData *obj) {
    u32 state = D_80114A80_mstory1;
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
            if (D_80114A84_mstory1 == 1) {
                btn = D_800D5558_main[D_801158B4_mstory1] & START_BUTTON;
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
    D_80114A80_mstory1 = state;
}

void func_80105D80_mstory1(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114A88_mstory1 == 0) {
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            D_80114A88_mstory1 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E00_mstory1(void) {
    D_801158B8_mstory1 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_801158B8_mstory1, 160, 120);
    espAttrSet(D_801158B8_mstory1, 0x4000);
    D_801158B2_mstory1 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801158B2_mstory1, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801158B2_mstory1, 2, 0);
    func_8001C814_main(D_801158B2_mstory1, 1, 1);
}

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_801158B8_mstory1);
}

void func_80105F28_mstory1(omObjData *obj) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

void func_80105FA8_mstory1(void) {
    D_80114A80_mstory1 = 3;
}

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

void func_80105FF4_mstory1(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    D_801158C0_mstory1[0] = espEntry(func_8000B838_main(0x1D0001), 0, 0);
    espPosSet(D_801158C0_mstory1[0], 160, 120);
    espDispOff(D_801158C0_mstory1[0]);
    for (i = 0; i < 7; i++) {
        D_801158C0_mstory1[i + 1] = espEntry(func_8000B838_main(D_80114C6C_mstory1[i]), 0, 0);
        espPosSet(D_801158C0_mstory1[i + 1], D_80114C88_mstory1[i][0] + 48, D_80114C88_mstory1[i][1] + 48);
        espAttrSet(D_801158C0_mstory1[i + 1], 8);
        espDispOff(D_801158C0_mstory1[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_801158D0_mstory1[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = D_80114C88_mstory1[D_801158E4_mstory1][0] + 48;
        y = D_80114C88_mstory1[D_801158E4_mstory1][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(D_801158D0_mstory1[i], x, y);
        espAttrSet(D_801158D0_mstory1[i], 0x1000);
        espColorSet(D_801158D0_mstory1[i], 255, 255, 192);
        espAttrSet(D_801158D0_mstory1[i], 8);
        espScaleSet(D_801158D0_mstory1[i], 1.5f, 1.5f);
        espTPLvlSet(D_801158D0_mstory1[i], 255);
        espDispOff(D_801158D0_mstory1[i]);
    }
    HuMemMemoryFreePerm(data);
    D_801158E0_mstory1 = espEntry(func_8000B838_main(0x1D0000), 0, 0);
    espPosSet(D_801158E0_mstory1, 160, 120);
    espScaleSet(D_801158E0_mstory1, 40.0f, 30.0f);
    espAttrSet(D_801158E0_mstory1, 0);
    espDispOff(D_801158E0_mstory1);
    omPrcSetDestructor(0, func_801068A0_mstory1);
    espDispOn(D_801158E0_mstory1);
    espTPLvlSet(D_801158E0_mstory1, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801158E0_mstory1, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801158E0_mstory1, 256);
    for (i = 0; i < D_801158E4_mstory1; i++) {
        espDispOn(D_801158C0_mstory1[i + 1]);
    }
    func_80105EC0_mstory1();
    espDispOn(D_801158C0_mstory1[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801158E0_mstory1, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801158E0_mstory1);
    espTPLvlSet(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 0);
    espDispOn(D_801158C0_mstory1[D_801158E4_mstory1 + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(D_801158C0_mstory1[D_801158E4_mstory1 + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 255);
    espScaleSet(D_801158C0_mstory1[D_801158E4_mstory1 + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(D_801158D0_mstory1[i], 0, 0);
        func_8000BDDC_main(D_801158D0_mstory1[i], 1);
        espDispOn(D_801158D0_mstory1[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(D_801158D0_mstory1[i]);
    }
    if (D_801158E4_mstory1 == 6) {
        HuPrcSleep(40);
        espDispOn(D_801158E0_mstory1);
        espTPLvlSet(D_801158E0_mstory1, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_801158E0_mstory1, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(D_801158E0_mstory1, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_801158E0_mstory1, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(D_801158E0_mstory1);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(D_801158E0_mstory1);
    espTPLvlSet(D_801158E0_mstory1, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801158E0_mstory1, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_801158E0_mstory1, 256);
    espDispOff(D_801158C0_mstory1[D_801158E4_mstory1 + 1]);
    espDispOff(D_801158C0_mstory1[0]);
    func_80105EF4_mstory1();
    HuPrcSleep(30);
    for (i = 0; i < D_801158E4_mstory1; i++) {
        espDispOff(D_801158C0_mstory1[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_801158E0_mstory1, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_801158E0_mstory1);
    D_80114AB0_mstory1 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106894_mstory1(void) {
    return D_80114AB0_mstory1;
}

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

void func_801068B0_mstory1(s16 model, s16 animSlot, s16 anim) {
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

void func_80106984_mstory1(void) {
    D_801158B0_mstory1 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_801158B0_mstory1, 1 << D_801158B4_mstory1);
    HuWinInsertMesSet(D_801158B0_mstory1, GwStory.unk1 + 0x1C00, 0);
}

void func_801069EC_mstory1(void) {
    HuWinHomeClear(D_801158B0_mstory1);
    func_80060C14_main(D_801158B0_mstory1, 1);
}

void func_80106A1C_mstory1(void) {
    func_80060EA8_main(D_801158B0_mstory1, 1);
}

void func_80106A40_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

void func_80106A94_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
}

void func_80106AC0_mstory1(void) {
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106AFC_mstory1(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106B30_mstory1(obj, pos, frames, 1);
}

void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void func_80106D64_mstory1(omObjData *obj, Vec *pos, s32 frames) {
    func_80106D80_mstory1(obj, pos, frames, 1);
}

void func_80106D80_mstory1(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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

void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B14_mstory1(obj, &pos, frames);
}

void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B30_mstory1(obj, &pos, frames, arg3);
}

void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D64_mstory1(obj, &pos, frames);
}

void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D80_mstory1(obj, &pos, frames, arg3);
}

void func_8010704C_mstory1(omObjData *obj, const Vec *target, s32 frames) {
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

void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010704C_mstory1(obj, &pos, frames);
}

void func_80107220_mstory1(s16 model) {
    HuPrcSleep(10);
    while (!func_8010726C_mstory1(model)) {
        HuPrcVSleep();
    }
}

s32 func_8010726C_mstory1(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_80107318_mstory1(omObjData *obj, f32 speed, s16 frames) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);
