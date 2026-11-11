#include "common.h"
#include "game/hmfmath.h"
#include "overlays/minigame.h"

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011B920_mstory2;
extern Vec D_8011B92C_mstory2;
extern Vec D_8011B938_mstory2;

extern s16 D_8011B944_mstory2;
extern void (*const D_8011BDE0_mstory2[])(void);
extern const s32 D_8011BDF4_mstory2[];
extern s16 D_8011B946_mstory2;
extern s16 D_8011B948_mstory2;
extern s32 D_8011B94C_mstory2;
extern s16 D_8011C640_mstory2;
extern s16 D_8011C642_mstory2;
extern s16 D_8011C644_mstory2;
extern u16 D_8011C646_mstory2;
extern s16 D_8011C648_mstory2;
extern s32 D_8011C674_mstory2;
extern s16 D_8011C650_mstory2[8];
extern s16 D_8011C660_mstory2[8];
extern s16 D_8011C670_mstory2;
extern const s32 D_8011BE2C_mstory2[7];
extern const s16 D_8011BE48_mstory2[][2];
extern s16 D_8011CA80_mstory2[4];

void func_80105C1C_mstory2(void);
void func_80105DB4_mstory2(omObjData *obj);
void func_80105F94_mstory2(omObjData *obj);
void func_801063B0_mstory2(void);
void func_80105EC4_mstory2(omObjData *);
void func_80105F4C_mstory2(omObjData *);
void func_80105FBC_mstory2(void);
void func_80106D58_mstory2(s16 model, s16 arg1, s16 arg2);
void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801070D8_mstory2(omObjData *obj, Vec *pos, s32 frames);
s32 func_801072F8_mstory2(s16 model);
void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames);
void func_801076DC_mstory2(omObjData *obj, omObjData *target);
void func_801064AC_mstory2(void);
void func_80106D50_mstory2(void);
void func_80107824_mstory2(omObjData *obj, Vec *target, s32 frames, s32 faceDir);

void func_801059A0_mstory2(void) {
    func_80105C1C_mstory2();
}

void func_801059BC_mstory2(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory2(omObjData *obj) {
    D_800CE17C_main[0] = D_8011B920_mstory2.x;
    D_800CE17C_main[1] = D_8011B920_mstory2.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_8011B920_mstory2, &D_8011B92C_mstory2, &D_8011B938_mstory2);
    Hu3DCamUpdateMtx(0);
}

void func_80105A64_mstory2(void) {
    omObjData *obj;

    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, func_801059E4_mstory2);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_801059E4_mstory2(obj);
}

void func_80105B44_mstory2(void) {
    HuWinInit();
}

void func_80105B60_mstory2(void) {
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                D_8011CA80_mstory2[count++] = i;
            }
            if (count >= 4) {
                return;
            }
        }
        if (count >= 4) {
            return;
        }
    }
}

void func_80105C1C_mstory2(void) {
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_801059BC_mstory2();
    func_80105A64_mstory2();
    func_80105B44_mstory2();
    func_80105B60_mstory2();
    D_8011C640_mstory2 = GwPlayer[0].coin;
    if (D_8011C640_mstory2 >= 5) {
        D_8011C640_mstory2 = 4;
    }
    omAddObj(0, 0, 0, -1, func_80105DB4_mstory2);
    omAddObj(0, 0, 0, -1, func_80105F94_mstory2);
    func_801063B0_mstory2();
    if (D_8011C640_mstory2 != 0) {
        if (_CheckFlag(D_8011BDF4_mstory2[D_8011C640_mstory2])) {
            D_8011B944_mstory2 = 1;
        } else {
            _SetFlag(D_8011BDF4_mstory2[D_8011C640_mstory2]);
        }
    }
    for (D_8011C642_mstory2 = 0; D_8011C642_mstory2 < 4; D_8011C642_mstory2++) {
        if (CheckControllerRead(D_8011C642_mstory2)) {
            break;
        }
    }
    if (D_8011C642_mstory2 >= 4) {
        D_8011C642_mstory2 = 0;
    }
    D_8011BDE0_mstory2[D_8011C640_mstory2]();
    WipeCreateIn(2, 16);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDF4_mstory2);

void func_80105DB4_mstory2(omObjData *obj) {
    s16 state = D_8011B946_mstory2;

    switch (state) {
        case 0:
            HuAudSeqPlay(D_8011C640_mstory2 == 0 ? 0x2C : 0x26);
            state++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                state++;
            }
            break;
        case 2:
            if (D_8011C640_mstory2 != 0 && D_8011B944_mstory2 == 1 && (D_800D5558_main[D_8011C642_mstory2] & START_BUTTON)) {
                state++;
            }
            break;
        case 4:
            D_8011B948_mstory2 = 1;
        case 3:
        default:
            obj->func = func_80105F4C_mstory2;
            break;
    }
    D_8011B946_mstory2 = state;
}

void func_80105EA4_mstory2(void) {
    D_8011B946_mstory2 = 3;
}

void func_80105EB4_mstory2(void) {
    D_8011B946_mstory2 = 4;
}

void func_80105EC4_mstory2(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        if (D_8011B948_mstory2 == 0) {
            if (D_8011C640_mstory2 != 0) {
                SLCommonSet(1);
            }
            omOvlReturnEx(1);
        } else if (D_8011B948_mstory2 == 1) {
            func_800E989C_minigame();
        }
    }
}

void func_80105F4C_mstory2(omObjData *obj) {
    WipeCreateOut(2, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80105EC4_mstory2;
}

void func_80105F94_mstory2(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105F4C_mstory2;
    }
}

void func_80105FBC_mstory2(void) {
    s16 comKeys[4] = { 0, 0, 0, 0 };
    s16 playerBits[4] = { 1, 2, 4, 8 };

    D_8011C644_mstory2 = func_80060880_main(160, 194, 20);
    comKeys[D_8011C642_mstory2] = -1;
    func_8005B63C_main(D_8011C644_mstory2, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
    HuWinActivePlayerSet(D_8011C644_mstory2, playerBits[D_8011C642_mstory2]);
    HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
}

void func_801060A4_mstory2(void) {
    HuWinHomeClear(D_8011C644_mstory2);
    func_80060C14_main(D_8011C644_mstory2, 1);
}

void func_801060D4_mstory2(void) {
    func_80060EA8_main(D_8011C644_mstory2, 1);
}

void func_801060F8_mstory2(s32 mess) {
    HuWinMesSet(D_8011C644_mstory2, mess, -1, -1);
    while (HuWinStatGet(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

void func_8010614C_mstory2(s32 mess) {
    HuWinMesSet(D_8011C644_mstory2, mess, -1, -1);
    HuWinInsertMesSet(D_8011C644_mstory2, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(D_8011C644_mstory2) != 0) {
        HuPrcVSleep();
    }
}

s16 func_801061BC_mstory2(void) {
    return HuWinChoiceGet(D_8011C644_mstory2, 0, 1);
}

void func_801061EC_mstory2(void) {
    espDispOn(D_8011C646_mstory2);
}

void func_8010620C_mstory2(void) {
    espDispOff(D_8011C646_mstory2);
}

void func_8010622C_mstory2(void) {
    HuAudFXPlay(0x216);
    func_8001C814_main(D_8011C648_mstory2, 4, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    Hu3DMotionTimeSet(D_8011C648_mstory2, 0.0f);
    Hu3DMotionSpeedSet(D_8011C648_mstory2, 2.0f);
}

void func_80106290_mstory2(void) {
    func_8001C814_main(D_8011C648_mstory2, 4, 4);
    func_8001C814_main(D_8011C648_mstory2, 1, 0);
    Hu3DMotionTimeSet(D_8011C648_mstory2, Hu3DData[D_8011C648_mstory2].motTime);
}

void func_801062F4_mstory2(void) {
    s16 i = 0;

    Hu3DData[D_8011C648_mstory2].rot.y += -10.6f;
    while (i < 5) {
        Hu3DData[D_8011C648_mstory2].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    }
}

void func_801063B0_mstory2(void) {
    D_8011C646_mstory2 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_8011C646_mstory2, 160, 120);
    espAttrSet(D_8011C646_mstory2, 0x4000);
    D_8011C648_mstory2 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_8011C648_mstory2, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_8011C648_mstory2, 2, 0);
    func_8001C814_main(D_8011C648_mstory2, 1, 1);
}

void func_80106470_mstory2(s32 arg0) {
    D_8011C674_mstory2 = arg0;
    D_8011B94C_mstory2 = 0;
    omAddPrcObj(func_801064AC_mstory2, 0x1000, 0x800, 0);
}

void func_801064AC_mstory2(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    D_8011C650_mstory2[0] = espEntry(func_8000B838_main(0x1D0001), 0, 0);
    espPosSet(D_8011C650_mstory2[0], 160, 120);
    espDispOff(D_8011C650_mstory2[0]);
    for (i = 0; i < 7; i++) {
        D_8011C650_mstory2[i + 1] = espEntry(func_8000B838_main(D_8011BE2C_mstory2[i]), 0, 0);
        espPosSet(D_8011C650_mstory2[i + 1], D_8011BE48_mstory2[i][0] + 48, D_8011BE48_mstory2[i][1] + 48);
        espAttrSet(D_8011C650_mstory2[i + 1], 8);
        espDispOff(D_8011C650_mstory2[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        D_8011C660_mstory2[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = D_8011BE48_mstory2[D_8011C674_mstory2][0] + 48;
        y = D_8011BE48_mstory2[D_8011C674_mstory2][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(D_8011C660_mstory2[i], x, y);
        espAttrSet(D_8011C660_mstory2[i], 0x1000);
        espColorSet(D_8011C660_mstory2[i], 255, 255, 192);
        espAttrSet(D_8011C660_mstory2[i], 8);
        espScaleSet(D_8011C660_mstory2[i], 1.5f, 1.5f);
        espTPLvlSet(D_8011C660_mstory2[i], 255);
        espDispOff(D_8011C660_mstory2[i]);
    }
    HuMemMemoryFreePerm(data);
    D_8011C670_mstory2 = espEntry(func_8000B838_main(0x1D0000), 0, 0);
    espPosSet(D_8011C670_mstory2, 160, 120);
    espScaleSet(D_8011C670_mstory2, 40.0f, 30.0f);
    espAttrSet(D_8011C670_mstory2, 0);
    espDispOff(D_8011C670_mstory2);
    omPrcSetDestructor(0, func_80106D50_mstory2);
    espDispOn(D_8011C670_mstory2);
    espTPLvlSet(D_8011C670_mstory2, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_8011C670_mstory2, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_8011C670_mstory2, 256);
    for (i = 0; i < D_8011C674_mstory2; i++) {
        espDispOn(D_8011C650_mstory2[i + 1]);
    }
    func_8010620C_mstory2();
    espDispOn(D_8011C650_mstory2[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_8011C670_mstory2, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_8011C670_mstory2);
    espTPLvlSet(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 0);
    espDispOn(D_8011C650_mstory2[D_8011C674_mstory2 + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(D_8011C650_mstory2[D_8011C674_mstory2 + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 255);
    espScaleSet(D_8011C650_mstory2[D_8011C674_mstory2 + 1], 1.0f, 1.0f);
    for (i = 0; i < 8; i++) {
        espBankSet(D_8011C660_mstory2[i], 0, 0);
        func_8000BDDC_main(D_8011C660_mstory2[i], 1);
        espDispOn(D_8011C660_mstory2[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(D_8011C660_mstory2[i]);
    }
    if (D_8011C674_mstory2 == 6) {
        HuPrcSleep(40);
        espDispOn(D_8011C670_mstory2);
        espTPLvlSet(D_8011C670_mstory2, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_8011C670_mstory2, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(D_8011C670_mstory2, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(D_8011C670_mstory2, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(D_8011C670_mstory2);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(D_8011C670_mstory2);
    espTPLvlSet(D_8011C670_mstory2, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_8011C670_mstory2, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(D_8011C670_mstory2, 256);
    espDispOff(D_8011C650_mstory2[D_8011C674_mstory2 + 1]);
    espDispOff(D_8011C650_mstory2[0]);
    func_801061EC_mstory2();
    HuPrcSleep(30);
    for (i = 0; i < D_8011C674_mstory2; i++) {
        espDispOff(D_8011C650_mstory2[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(D_8011C670_mstory2, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(D_8011C670_mstory2);
    D_8011B94C_mstory2 = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 func_80106D44_mstory2(void) {
    return D_8011B94C_mstory2;
}

void func_80106D50_mstory2(void) {
}

void func_80106D58_mstory2(s16 model, s16 animSlot, s16 anim) {
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

void func_80106E2C_mstory2(omObjData *obj, Vec *pos, s32 frames) {
    func_80106E48_mstory2(obj, pos, frames, 1);
}

void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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

void func_8010707C_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106E2C_mstory2(obj, &pos, frames);
}

void func_801070A8_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106E48_mstory2(obj, &pos, frames, arg3);
}

void func_801070D8_mstory2(omObjData *obj, Vec *target, s32 frames) {
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

void func_80107280_mstory2(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_801070D8_mstory2(obj, &pos, frames);
}

void func_801072AC_mstory2(s16 model) {
    HuPrcSleep(10);
    while (!func_801072F8_mstory2(model)) {
        HuPrcVSleep();
    }
}

s32 func_801072F8_mstory2(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void func_801073A4_mstory2(omObjData *obj, f32 speed, s16 frames) {
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

void func_80107540_mstory2(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x -= dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z -= dz;
        HuPrcVSleep();
    }
}

void func_801076DC_mstory2(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

void func_80107824_mstory2(omObjData *obj, Vec *target, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec vel;
    Vec pos;
    Vec accel;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = target->x - start.x;
    diff.y = target->y - start.y;
    diff.z = target->z - start.z;
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
        if (pos.x <= target->x) {
            pos.x = target->x;
            pos.y = target->y;
            pos.z = target->z;
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
    Hu3DModelPosSet(model, target->x, target->y, target->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], target->x, target->y - 5.0f, target->z);
    }
    HuPrcVSleep();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE2C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE48_mstory2);
