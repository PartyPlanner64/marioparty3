#include "common.h"

typedef struct UnkStoryObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkStoryObj; // sizeof 0x18

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

typedef struct UnkMstory4Work {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec pos;
} UnkMstory4Work; // sizeof 0x10

extern Vec D_80111B04_mstory4[];
extern Vec D_80111B34_mstory4[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern Vec D_80111AD0_mstory4;
extern const Vec D_80111DDC_mstory4;
extern const Vec D_80111DF4_mstory4;
extern const Vec D_80111E0C_mstory4;
extern const Vec D_80111E18_mstory4;
extern const Vec D_80111E24_mstory4;
extern const Vec D_80111E30_mstory4;
extern const Vec D_80111E3C_mstory4;
extern const Vec D_80111E48_mstory4;
extern const Vec D_80111E54_mstory4;
extern const Vec D_80111E60_mstory4;
extern Vec D_80111ADC_mstory4;
extern Vec D_80111AE8_mstory4;

extern s32 D_80111AC0_mstory4;
extern s32 D_80111AC4_mstory4;
extern s32 D_80111AC8_mstory4;
extern s8 D_80111ACC_mstory4;
extern s32 D_80111AF4_mstory4;
extern s32 D_80111B00_mstory4;
extern s32 D_80111B80_mstory4;
extern s32 D_80111B84_mstory4;
extern s32 D_80111B88_mstory4;
extern s32 D_80111B8C_mstory4;
extern f32 D_80111B90_mstory4;
extern char D_80111FF8_mstory4[];
extern s16 D_80112326_mstory4;
extern u8 D_80111BFC_mstory4[];
extern Vec D_80111DB8_mstory4;
extern Vec D_80111DC4_mstory4;
extern Vec D_80111E78_mstory4;
extern Vec D_80111E84_mstory4;
extern Vec D_80111ECC_mstory4;
extern Vec D_80111EE4_mstory4;
extern Vec D_80111F1C_mstory4;
extern s16 D_80112120_mstory4;
extern s16 D_80112122_mstory4;
extern s32 D_80112124_mstory4;
extern u16 D_80112128_mstory4;
extern s32 D_801121B4_mstory4;
extern s32 D_801123B0_mstory4[4];
extern void (*const D_80111C10_mstory4[])(void);
extern const s32 D_80111C18_mstory4[];
extern UnkStoryObj D_801121C0_mstory4[5];
extern s16 D_8011223A_mstory4;
extern s32 D_80112238_mstory4[4];
extern Vec D_8011225C_mstory4;
extern const Vec D_80111C7C_mstory4;
extern s16 D_8011223E_mstory4;
extern s16 D_80112242_mstory4;
extern s16 D_80112246_mstory4;
extern s16 D_80112248_mstory4;
extern s16 D_8011228C_mstory4;
extern Vec D_80112274_mstory4;
extern const Vec D_80111C94_mstory4;
extern u16 D_8011234A_mstory4[2][2];
extern s16 D_80112352_mstory4;
extern const s32 D_80112008_mstory4[8];
extern const s32 D_801120D4_mstory4[8];
extern const s16 D_801120F4_mstory4[8][2];
extern const s16 D_80112114_mstory4[2];
extern s16 D_80112358_mstory4[];
extern s16 D_80112366_mstory4;
extern s16 D_80112368_mstory4[];
extern u16 D_80112376_mstory4;
extern s16 D_801123A6_mstory4[2];
extern UnkStoryObj D_801122A0_mstory4[4];
extern s16 D_80112324_mstory4;
extern Vec D_80112318_mstory4;
extern const Vec D_80111F28_mstory4;
extern const Vec D_80111F80_mstory4;
extern u8 D_80111C04_mstory4[];
extern Vec D_80112268_mstory4;
extern const Vec D_80111C88_mstory4;
extern Vec D_80112280_mstory4;
extern const Vec D_80111CA0_mstory4;
extern s16 D_8011228E_mstory4;
extern const s32 D_80111F08_mstory4[];

void MBDBackKill(void);
void MBDBackClose(void);
void func_801078B4_mstory4(MstoryPath *path, f32 t, Vec *out);
void func_80106134_mstory4(void);
void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames);
void func_80106DBC_mstory4(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_8010700C_mstory4(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801072D8_mstory4(omObjData *obj, const Vec *pos, s32 frames);
s32 func_801074F8_mstory4(s16 model);
void func_80105C90_mstory4(omObjData *obj);
void func_80105DA8_mstory4(omObjData *obj);
void func_80105F40_mstory4(void);
void func_80106068_mstory4(omObjData *obj);
void func_80108280_mstory4(omObjData *obj);
void func_801086F4_mstory4(omObjData *obj);
void func_801093B0_mstory4(omObjData *obj);
void func_8010A44C_mstory4(omObjData *obj);
void func_8010A76C_mstory4(omObjData *obj);
void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_8010A3C8_mstory4(void);
void func_80109840_mstory4(omObjData *obj);
void func_8010ABD0_mstory4(s32 index, s32 seNo);
void func_8010AC84_mstory4(s32 index);
void func_80109B5C_mstory4(omObjData *object);
void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5);
void func_8010BAF0_mstory4(omObjData *obj);
void func_8010CAE8_mstory4(void);
void func_80108288_mstory4(void);
void func_801094DC_mstory4(void);
void func_80109838_mstory4(void);
void func_80109EA4_mstory4(void);
void func_8010A1C4_mstory4(void);
void func_8010A480_mstory4(void);
void func_8010A05C_mstory4(void);
void func_8010A064_mstory4(omObjData *obj);
void func_8010A5AC_mstory4(void);
void func_8010A764_mstory4(void);
void func_8010ACF4_mstory4(void);
void func_8010BAF8_mstory4(void);
void func_8010C0BC_mstory4(void);
void func_8010C8D0_mstory4(void);
void func_8010CE90_mstory4(void);
void func_8010CD40_mstory4(void);
void func_8010D128_mstory4(void);
void func_801119C0_mstory4(void);
void func_8010D1A0_mstory4(omObjData *object);
s16 func_80110394_mstory4(s32 file, s32 flags);
void func_801104D4_mstory4(s16 modelId, f32 value);
void func_80110888_mstory4(s16 modelId, f32 x, f32 y, f32 z);
void func_80110528_mstory4(omObjData *obj);
s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z);
s16 func_801108FC_mstory4(s32 file, s32 flags);
void func_801109EC_mstory4(s16 model);
s16 func_80110B4C_mstory4(s32 dataNum, s32 attr);
void func_80110E3C_mstory4(void);
void func_801118F8_mstory4(s32 index, s32 seNo);
void func_8011196C_mstory4(s32 index);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106134_mstory4);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801074F8_mstory4);

MstoryPath *func_801075B0_mstory4(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801078B4_mstory4);

void func_8010815C_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010818C_mstory4(void) {
    func_80106C10_mstory4();
    D_8011228C_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80108288_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_801094DC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109EA4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A1C4_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A480_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A5AC_mstory4, 900, 0x800, 0);
    omAddPrcObj(func_8010ACF4_mstory4, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_8011228C_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80108280_mstory4(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80108288_mstory4);

void func_801086EC_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C50_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C70_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C7C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C88_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C94_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CA0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CAC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CCC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CEC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D2C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D38_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801086F4_mstory4);

void func_801093B0_mstory4(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[10]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_80109474_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DB8_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801094A8_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DC4_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D74_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D80_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D8C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DB0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DC4_mstory4);

const char D_80111DD0_mstory4[] = "c204n_0_DEF";

void func_801094DC_mstory4(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801121C0_mstory4[1].obj = obj;
    D_801121C0_mstory4[1].unk_08 = 0;
    D_801121C0_mstory4[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_8011225C_mstory4 = D_80111C7C_mstory4;
    Hu3DModelPosSet(obj->model[1], D_8011225C_mstory4.x, D_8011225C_mstory4.y, D_8011225C_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_8011225C_mstory4.x, -5.0f, D_8011225C_mstory4.z);
    data = DataRead(0xA007E);
    D_80112238_mstory4[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80111DD0_mstory4);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_8011223A_mstory4, 1, 0);
    Hu3DAnimBankSet(D_8011223A_mstory4, 0);
    D_80112248_mstory4 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_8011223A_mstory4, 0, D_80111DD0_mstory4);
    D_80112238_mstory4[0] = D_800D1714_main[D_80112238_mstory4[0]].animIdx;
    data = DataRead(0xA0080);
    D_80112238_mstory4[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80112238_mstory4[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0084);
    D_80112238_mstory4[3] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_8011223A_mstory4);
    omPrcSetDestructor(0, func_80109838_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
    while (TRUE) {
        D_801121C0_mstory4[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109838_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DDC_mstory4);

const Vec D_80111DE8_mstory4 = { 10.0f, 378.9f, 0.0f };

void func_80109840_mstory4(omObjData *obj) {
    D_801121C0_mstory4[0].func = func_801093B0_mstory4;
    D_801121C0_mstory4[3].func = func_8010A44C_mstory4;
    func_801072D8_mstory4(obj, &D_80111DE8_mstory4, 30);
    func_80106DA0_mstory4(obj, &D_80111E48_mstory4, 20);
    HuPrcSleep(30);
    func_801072D8_mstory4(obj, &D_80111E18_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111E3C_mstory4, 15);
    func_80107480_mstory4(D_801121C0_mstory4[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_801072D8_mstory4(obj, &D_80111DF4_mstory4, 15);
    HuPrcSleep(20);
    func_801072D8_mstory4(obj, &D_80111E0C_mstory4, 10);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, &D_80111E54_mstory4, 10);
    Hu3DMotionShiftSet(D_801121C0_mstory4[3].obj->model[1], Hu3DData[D_801121C0_mstory4[3].obj->motion[1]].motId, 0, 10, 2);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A71);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(D_801121C0_mstory4[3].obj->model[1], Hu3DData[D_801121C0_mstory4[3].obj->motion[0]].motId, 0, 10, 2);
    func_801072D8_mstory4(D_801121C0_mstory4[3].obj, &D_80111E60_mstory4, 10);
    D_801121C0_mstory4[4].func = func_8010A76C_mstory4;
    func_801072D8_mstory4(obj, &D_80111DDC_mstory4, 20);
    Hu3DMotionShiftSet(D_801121C0_mstory4[0].obj->model[1], Hu3DData[D_801121C0_mstory4[0].obj->motion[13]].motId, 0, 10, 2);
    while (!(D_801121C0_mstory4[4].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801121C0_mstory4[0].func = func_801086F4_mstory4;
    HuPrcSleep(40);
    func_801072D8_mstory4(obj, &D_80111E30_mstory4, 50);
    func_801072D8_mstory4(obj, &D_80111E24_mstory4, 40);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109AE0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111E84_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111E78_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109B5C_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, y + orig.y, orig.z);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_80112242_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109CCC_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, y + orig.y, orig.z);
    func_80106B3C_mstory4(obj->model[1], D_80112248_mstory4, D_80112246_mstory4);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109E3C_mstory4(void) {
    HuPrcSleep(5);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
}

void func_80109E68_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

void func_80109EA4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[2].obj = obj;
    D_801121C0_mstory4[2].unk_08 = 0;
    D_801121C0_mstory4[2].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0x800A0, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    func_8000B460_main(obj, 0, 0x80000);
    func_8000B460_main(obj, 1, 0x1D0076);
    func_8000B460_main(obj, 2, 0x1D0077);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80112268_mstory4 = D_80111C88_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112268_mstory4.x, D_80112268_mstory4.y, D_80112268_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112268_mstory4.x, -5.0f, D_80112268_mstory4.z);
    omPrcSetDestructor(0, func_8010A05C_mstory4);
    D_801121C0_mstory4[2].func = func_8010A064_mstory4;
    while (1) {
        D_801121C0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A05C_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DF4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E18_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E24_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E30_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E3C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E48_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E54_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E60_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E78_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E84_mstory4);

const Vec D_80111E9C_mstory4 = { 200.0f, 0.0f, 1200.0f };
const Vec D_80111EA8_mstory4 = { 166.66666f, 0.0f, 150.0f };

void func_8010A064_mstory4(omObjData *obj) {
    HuPrcSleep(10);
    CharFXPlay(0x26B, 6);
    HuPrcSleep(30);
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, D_8011223E_mstory4);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A70);
    func_80106CA8_mstory4();
    func_80106B3C_mstory4(D_801121C0_mstory4[1].obj->model[1], D_80112248_mstory4, D_8011223A_mstory4);
    D_801121C0_mstory4[1].func = func_80109840_mstory4;
    CharFXPlay(0x286, 6);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010ABD0_mstory4(2, 40);
    func_80106DA0_mstory4(obj, &D_80111E9C_mstory4, 40);
    func_8010AC84_mstory4(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[2].func = func_80108280_mstory4;
}

void func_8010A1C4_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801121C0_mstory4[3].obj = obj;
    D_801121C0_mstory4[3].unk_08 = 0;
    D_801121C0_mstory4[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_8011228C_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_80112274_mstory4 = D_80111C94_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112274_mstory4.x, D_80112274_mstory4.y, D_80112274_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112274_mstory4.x, -5.0f, D_80112274_mstory4.z);
    omPrcSetDestructor(0, func_8010A3C8_mstory4);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
    D_80111B00_mstory4 = 1;
    while (1) {
        D_801121C0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A3C8_mstory4(void) {
}

const Vec D_80111EB4_mstory4 = { 700.0f, 0.0f, 150.0f };
const Vec D_80111EC0_mstory4 = { 216.66666f, 0.0f, 150.0f };

void func_8010A3D0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111ECC_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111EB4_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A44C_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111EE4_mstory4, 20);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A480_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B00_mstory4 != 0) {
        model = D_801121C0_mstory4[3].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

void func_8010A5AC_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801121C0_mstory4[4].obj = obj;
    D_801121C0_mstory4[4].unk_08 = 0;
    D_801121C0_mstory4[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_80111F08_mstory4[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112280_mstory4 = D_80111CA0_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112280_mstory4.x, D_80112280_mstory4.y, D_80112280_mstory4.z);
    D_8011228E_mstory4 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_8011228E_mstory4, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_8011228E_mstory4, 60.0f);
    func_800138EC_main(D_8011228E_mstory4, 1, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    omPrcSetDestructor(0, func_8010A764_mstory4);
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
    while (1) {
        D_801121C0_mstory4[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010A764_mstory4(void) {
}

void func_8010A76C_mstory4(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_801075B0_mstory4(D_80111B04_mstory4, 0);
    paths[1] = func_801075B0_mstory4(D_80111B34_mstory4, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_8011228E_mstory4, 4, 0);
    func_800138EC_main(D_8011228E_mstory4, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_801078B4_mstory4(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801121C0_mstory4[3].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801121C0_mstory4[4].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_801078B4_mstory4(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_8011228E_mstory4, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_8011228E_mstory4, 4, 4);
    HuAudFXPlay(0x21A);
    func_8010815C_mstory4(paths[0]);
    func_8010815C_mstory4(paths[1]);
    D_801121C0_mstory4[4].unk_08 = 1;
    D_801121C0_mstory4[4].func = func_80108280_mstory4;
}

void func_8010AA88_mstory4(omObjData *obj, omObjData *target) {
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

void func_8010ABD0_mstory4(s32 index, s32 seNo) {
    if (D_801121C0_mstory4[index].unk_0C == 0) {
        D_801121C0_mstory4[index].unk_0C = 1;
        D_801121C0_mstory4[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, 6);
                break;
        }
    }
}

void func_8010AC84_mstory4(s32 index) {
    if (D_801121C0_mstory4[index].unk_0C == 1) {
        D_801121C0_mstory4[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801121C0_mstory4[index].unk_14);
        }
    }
}

// Code matches, but the target is followed by alignment padding, which suggests
// a file boundary at func_8010AE20_mstory4.
#ifdef NON_MATCHING
void func_8010ACF4_mstory4(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 5; i++) {
            if (D_801121C0_mstory4[i].unk_0C == 1 && Hu3DData[D_801121C0_mstory4[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801121C0_mstory4[i].unk_10;
                switch (i) {
                    case 0:
                        D_801121C0_mstory4[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        D_801121C0_mstory4[i].unk_14 = CharFXPlay(seNo, 6);
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010ACF4_mstory4);
#endif

MstoryPath *func_8010AE20_mstory4(Vec *points, s32 flags) {
    MstoryPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(MstoryPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B124_mstory4);

void func_8010B9CC_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010B9FC_mstory4(void) {
    func_80106C10_mstory4();
    D_80112324_mstory4 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_8010BAF8_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C0BC_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010C8D0_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CE90_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010CD40_mstory4, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010D128_mstory4, 0x1002, 0x800, 0);
    omAddPrcObj(func_801119C0_mstory4, 0x1002, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80112324_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010BAF0_mstory4(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010BAF8_mstory4);

void func_8010BF3C_mstory4(void) {
}

void func_8010BF44_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    HuPrcSleep(30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(obj, pos.x, pos.y, pos.z + 50.0f, 15, 0);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

void func_8010C080_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 180.0f, 0.0f, 40);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111ECC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111EE4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F08_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F1C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F28_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F54_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C0BC_mstory4);

void func_8010C54C_mstory4(void) {
}

void func_8010C554_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 230.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C590_mstory4(omObjData *obj) {
    Vec pos;
    f32 scale;
    s32 i;

    func_80107480_mstory4(obj, 0.0f, 360.0f, 0.0f, 10);
    Hu3DData[obj->model[1]].rot.y = 0.0f;
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    func_8010724C_mstory4(obj, pos.x, pos.y - 50.0f, pos.z, 20, 0);
    pos.x = Hu3DData[obj->model[1]].pos.x;
    pos.y = Hu3DData[obj->model[1]].pos.y + 80.0f;
    pos.z = Hu3DData[obj->model[1]].pos.z;
    func_8001C258_main(obj->model[5], 4, 0);
    Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
    Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
    HuAudFXPlay(0x222);
    for (i = 0; i < 10; i++) {
        Hu3DModelPosSet(obj->model[5], pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[6], pos.x, pos.y, pos.z);
        scale = sindf(i * 9.0f) * 2.0f;
        Hu3DModelScaleSet(obj->model[5], scale, scale, 1.0f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C7F8_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 10.0f, -30.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    HuPrcSleep(30);
    func_8010724C_mstory4(obj, D_80111F1C_mstory4.x + 300.0f, D_80111F1C_mstory4.y + 100.0f, D_80111F1C_mstory4.z, 20,
                          0);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_8010C8D0_mstory4(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801122A0_mstory4[2].obj = obj;
    D_801122A0_mstory4[2].unk_08 = 0;
    D_801122A0_mstory4[2].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0129);
    func_8000B460_main(obj, 3, 0xA0127);
    func_8000B460_main(obj, 4, 0xA012D);
    obj->model[2] = Hu3DModelLink(D_80112324_mstory4);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80112318_mstory4 = D_80111F28_mstory4;
    Hu3DModelPosSet(obj->model[1], D_80112318_mstory4.x, D_80112318_mstory4.y, D_80112318_mstory4.z);
    Hu3DModelPosSet(obj->model[2], D_80112318_mstory4.x, -5.0f, D_80112318_mstory4.z);
    omPrcSetDestructor(0, func_8010CAE8_mstory4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
    D_80111B80_mstory4 = 1;
    while (1) {
        D_801122A0_mstory4[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CAE8_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F80_mstory4);

void func_8010CAF0_mstory4(omObjData *obj) {
    s16 models[2];
    Vec pos;
    Vec ofs;
    f32 rot;
    f32 scale;
    f32 t;
    f32 s;
    f32 c;
    s32 i;

    models[0] = obj->model[1];
    models[1] = obj->model[2];
    pos.x = Hu3DData[models[0]].pos.x;
    pos.y = Hu3DData[models[0]].pos.y;
    pos.z = Hu3DData[models[0]].pos.z;
    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;
    rot = ofs.x;
    scale = rot;
    D_80111B84_mstory4 = 1;
    for (i = 0; i < 20; i++) {
        t = i * 4.5f;
        s = sindf(t);
        ofs.x = s * D_80111F80_mstory4.x;
        ofs.y = s * D_80111F80_mstory4.y;
        ofs.z = s * D_80111F80_mstory4.z;
        Hu3DModelPosSet(models[0], pos.x + ofs.x, pos.y + ofs.y, pos.z + ofs.z);
        Hu3DModelPosSet(models[1], pos.x + ofs.x, 0.0f, pos.z + ofs.z);
        c = cosdf(t) * 2.0f;
        Hu3DModelScaleSet(models[0], c, c, c);
        scale -= 0.2;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        Hu3DModelScaleSet(models[1], scale, scale, scale);
        rot += 0.5f;
        Hu3DModelRotSet(models[0], 0.0f, 0.0f, rot);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801122A0_mstory4[2].func = func_8010BAF0_mstory4;
}

void func_8010CD40_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B80_mstory4 != 0) {
        model = D_801122A0_mstory4[2].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            if (D_80111B84_mstory4 == 1) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            HuPrcVSleep();
        }
    }
}

void func_8010CE90_mstory4(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80111B88_mstory4 != 0) {
        model = D_801122A0_mstory4[1].obj->model[6];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            if (D_80111B8C_mstory4 == 0) {
                pos.x = Hu3DData[model].pos.x;
                pos.z = Hu3DData[model].pos.z;
                ofs = sindf(angle) * 40.0f;
                angle += 2.0f;
                angle = (angle >= 360.0f) ? angle - 360.0f : angle;
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            } else {
                pos.y = Hu3DData[model].pos.y;
                angle = 0.0f;
            }
            HuPrcVSleep();
        }
    }
}

void func_8010CFE0_mstory4(omObjData *obj, omObjData *target) {
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

void func_8010D128_mstory4(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801122A0_mstory4[3].obj = obj;
    D_801122A0_mstory4[3].unk_08 = 0;
    D_801122A0_mstory4[3].unk_0C = 0;
    D_801122A0_mstory4[3].func = func_8010D1A0_mstory4;

    for (;;) {
        D_801122A0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FC8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010D1A0_mstory4);

void func_8010E5C4_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
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
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

void func_8010E7C0_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg5) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;
    f32 angle;
    f32 scale;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (arg5 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    scale = 1.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        angle = i / frames * 90.0f;
        cur.y = sindf(angle) * diff.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = sindf(angle) * 5.0f;
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    HuPrcVSleep();
}

f32 func_8010EA34_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[6];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = x - start.x;
    diff.y = y - start.y;
    diff.z = z - start.z;
    if (faceDir != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    D_80111B90_mstory4 = 0.0f;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, x, y, z);
    return 20.0f;
}

void func_8010EC38_mstory4(void) {
    s32 i;
    s32 j;

    D_80112352_mstory4 = func_8000B838_main(0x1D0028);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            D_8011234A_mstory4[i][j] = espEntry(D_80112352_mstory4, 0, 0);
            espPosSet(D_8011234A_mstory4[i][j], j * 160 + 80, i * 120 + 60);
            espAttrSet(D_8011234A_mstory4[i][j], 0x4000);
        }
    }
    espAttrSet(D_8011234A_mstory4[0][1], 1);
    espAttrSet(D_8011234A_mstory4[1][0], 2);
    espAttrSet(D_8011234A_mstory4[1][1], 3);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOn(D_8011234A_mstory4[i][j]);
        }
    }
}

void func_8010EDA0_mstory4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOff(D_8011234A_mstory4[i][j]);
            espKill(D_8011234A_mstory4[i][j]);
        }
    }
    HuSprAnimKill(D_80112352_mstory4);
}

void func_8010EE3C_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80112358_mstory4[i] = func_8000B838_main(D_80112008_mstory4[i]);
        D_80112368_mstory4[i] = espEntry(D_80112358_mstory4[i], 0, 0);
        espPosSet(D_80112368_mstory4[i], 160, 120);
        espAttrSet(D_80112368_mstory4[i], 0x4000);
        espDispOff(D_80112368_mstory4[i]);
    }
}

void func_8010EF00_mstory4(s32 index) {
    espDispOn(D_80112368_mstory4[index]);
}

void func_8010EF28_mstory4(s32 index) {
    espDispOff(D_80112368_mstory4[index]);
}

void func_8010EF50_mstory4(s32 index, s16 level) {
    espTPLvlSet(D_80112368_mstory4[index], level);
}

void func_8010EF80_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
    }
    HuPrcSleep(3);
}

void func_8010F010_mstory4(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
        HuPrcSleep(3);
    }
}

void func_8010F0A0_mstory4(void) {
    u16 *espriteSlot = &D_80112376_mstory4;
    s16 *sprite = &D_80112366_mstory4;

    espDispOff(*espriteSlot);
    espKill(*espriteSlot);
    HuSprAnimKill(*sprite);
}

void func_8010F0E0_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010F12C_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010F178_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->model[1]);
    Hu3DModelKill(obj->model[3]);
    Hu3DModelKill(obj->model[4]);
    Hu3DModelKill(obj->model[5]);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FF8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112008_mstory4);

// Code matches, but the string literals end unaligned and the following
// INCLUDE_RODATA D_80112088_mstory4 table is not padded back to a word
// boundary, so rodata shifts until that table is defined in C.
#ifdef NON_MATCHING
void func_8010F1F4_mstory4(void) {
    while (TRUE) {
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 0x800) {
                D_80111AD0_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x400) {
                D_80111AD0_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x100) {
                D_80111AD0_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 0x200) {
                D_80111AD0_mstory4.y += 10.0f;
            }
        }
        if (D_800CDA7C_main[0] & 0x2000) {
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.x -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.x += 10.0f;
            }
        } else {
            if (D_800CDA7C_main[0] & 8) {
                D_80111ADC_mstory4.z -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 4) {
                D_80111ADC_mstory4.z += 10.0f;
            }
            if (D_800CDA7C_main[0] & 1) {
                D_80111ADC_mstory4.y -= 10.0f;
            }
            if (D_800CDA7C_main[0] & 2) {
                D_80111ADC_mstory4.y += 10.0f;
            }
        }
        sprintf(D_800D5218_main, "POSX   :[%f]", D_80111AD0_mstory4.x);
        print8(24, 128, D_800D5218_main);
        sprintf(D_800D5218_main, "POSY   :[%f]", D_80111AD0_mstory4.y);
        print8(24, 136, D_800D5218_main);
        sprintf(D_800D5218_main, "POSZ   :[%f]", D_80111AD0_mstory4.z);
        print8(24, 144, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERX :[%f]", D_80111ADC_mstory4.x);
        print8(24, 160, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERY :[%f]", D_80111ADC_mstory4.y);
        print8(24, 168, D_800D5218_main);
        sprintf(D_800D5218_main, "INTERZ :[%f]", D_80111ADC_mstory4.z);
        print8(24, 176, D_800D5218_main);
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F1F4_mstory4);
#endif

void func_8010F588_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8010EF00_mstory4(1);
    D_80111AD0_mstory4.x = 1720.0f;
    D_80111AD0_mstory4.y = 4000.0f;
    D_80111AD0_mstory4.z = 4000.0f;
    D_80111ADC_mstory4.x = 140.0f;
    D_80111ADC_mstory4.y = 1000.0f;
    D_80111ADC_mstory4.z = 500.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x225);
    func_8010E7C0_mstory4(obj, 0.0f, 3000.0f, 0.0f, 100, 0);
}

void func_8010F660_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;
    HmfMotionNode *node;
    f32 speed;
    s32 i;

    D_80112326_mstory4 = func_80110394_mstory4(0xB0004, 0x689);
    func_80110888_mstory4(D_80112326_mstory4, 7.0f, 50.0f, 12.0f);
    func_801104D4_mstory4(D_80112326_mstory4, 120.0f);
    func_800138EC_main(D_80112326_mstory4, 1, 0);
    func_8001C258_main(D_80112326_mstory4, 4, 4);
    func_8010EF28_mstory4(1);
    func_8010EF00_mstory4(0);
    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 0.0f;
    D_80111AD0_mstory4.z = 500.0f;
    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 0.0f;
    D_80111ADC_mstory4.z = 0.0f;
    HuPrcVSleep();
    Hu3DModelPosSet(obj->model[6], 0.0f, -100.0f, 0.0f);
    Hu3DModelScaleSet(obj->model[6], 1.0f, 1.0f, 1.0f);
    func_8002FD8C_main(obj->model[6], Hu3DData[obj->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    func_8010EA34_mstory4(obj, 0.0f, 50.0f, 0.0f, 40, 0);
    speed = 0.0f;
    HuPrcSleep(20);
    node = func_8001D33C_main(obj->model[6], D_80111FF8_mstory4);
    node->rot.z = node->baseRot.y = D_80111B90_mstory4;
    HuAudFXPlay(0x226);
    for (i = 0; i < 80; i++) {
        if (i == 30) {
            func_800138EC_main(D_80112326_mstory4, 1, 1);
            func_8001C258_main(D_80112326_mstory4, 4, 0);
        }
        D_80111B90_mstory4 += speed;
        speed += 1.0f;
        if (speed > 30.0f) {
            speed = 40.0f;
        }
        node->rot.z = node->baseRot.y = D_80111B90_mstory4;
        HuPrcVSleep();
    }
    func_8002FDCC_main(obj->model[6], Hu3DData[obj->model[6]].motId, D_80111FF8_mstory4, 76, 70);
    D_80111B90_mstory4 = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F910_mstory4);

void func_800E4F50_name_81(u8 *);
void MBDBackCreate(s32, s32);                   /* extern */
void func_8010EF28_mstory4(s32);                /* extern */
void func_8010F0A0_mstory4(void);               /* extern */
void func_8010F12C_mstory4(void);               /* extern */
void func_80110270_mstory4(void);               /* extern */
void func_80110DB0_mstory4(f32, f32, f32, s16); /* extern */
extern Addr D_128CC60;

typedef struct Unk {
    s16 unk_00;
    char unk_02[6];
} Unk; // sizeof 0x8

extern const Unk D_80112088_mstory4[6];

extern s16 D_80112330_mstory4;
extern s16 D_80112378_mstory4[];
extern s16 D_801123A4_mstory4;

void func_8010FC98_mstory4(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 var_s3;
    u16 temp_fp;
    s32 i, j;

    temp_s5 = D_801122A0_mstory4[0].obj;
    temp_s7 = D_801122A0_mstory4[1].obj;
    temp_fp = temp_s5->model[1];
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);

    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 190.0f;
    D_80111AD0_mstory4.z = 3770.0f;

    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 130.0f;
    D_80111ADC_mstory4.z = 450.0f;

    D_80111AC4_mstory4 = 1;
    var_s3 = 0;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    func_8010EF28_mstory4(7);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].unk_00; var_s3++, j++) {
            espBankSet(D_80112378_mstory4[var_s3], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[var_s3], 1);
            espDispOff(D_80112378_mstory4[var_s3]);
            espKill(D_80112378_mstory4[var_s3]);
        }
    }

    HuSprAnimKill(D_801123A4_mstory4);
    func_8010F12C_mstory4();
    func_8001C5B4_main(temp_s5->model[1], temp_s5->motion[13]);
    func_8001C814_main(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    func_8010F0A0_mstory4();
    HuPrcSleep(30);
    func_8001C258_main(temp_s7->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    D_80111B8C_mstory4 = 0;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7E);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[4]].motId, 0, 0xA, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[11]].motId, 0, 0xA, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[2]].motId, 0, 0xA, 0);
    func_80017954_main(temp_fp, 2, GwStory.unk1, D_80112330_mstory4);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[3]].motId, 0, 0xA, 2);
    func_80110270_mstory4();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        func_80110DB0_mstory4(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

void func_80110270_mstory4(void) {
    s8 chr = GwStory.unk1;
    s8 i;

    D_801123A6_mstory4[0] = espEntry(func_8000B838_main(D_801120D4_mstory4[chr]), 0, 0);
    D_801123A6_mstory4[1] = espEntry(func_8000B838_main(0x1D001E), 0, 0);
    for (i = 0; i < 2; i++) {
        espPosSet(D_801123A6_mstory4[i], D_801120F4_mstory4[chr][i] + D_80112114_mstory4[i] / 2, 194);
    }
}

s16 func_80110394_mstory4(s32 file, s32 flags) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *effect;
    s16 model;

    obj = omAddObj(1000, 0, 0, -1, func_80110528_mstory4);
    obj->work[0] = model = func_801108FC_mstory4(file, flags);
    effect = Hu3DData[model].unkBC;
    effect->unk1C.f = effect->unk20.f = effect->unk24.f = 0.0f;
    effect->unk04 |= 1;
    effect->unk10.f = 100.0f;
    effect->unk14 = -1.0f;
    return model;
}

void func_80110460_mstory4(s16 modelId, s32 x, s32 y, s32 z) {
    HmfModelData_UnkBC_Struct *model = Hu3DData[modelId].unkBC;
    model->unk1C.i = x;
    model->unk20.i = y;
    model->unk24.i = z;
}

void func_80110494_mstory4(s16 modelId, s16 value) {
    Hu3DData[modelId].unkBC->unk14 = value;
}

void func_801104D4_mstory4(s16 modelId, f32 value) {
    Hu3DData[modelId].unkBC->unk10.f = value;
}

void func_80110500_mstory4(s16 model) {
    func_800138EC_main(model, 5, 4);
}

void func_80110528_mstory4(omObjData *obj) {
    s16 model = obj->work[0];
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 i;
    f32 x;
    f32 z;

    if (bc->unk04 & 4) {
        particle = bc->unk58;
        for (i = 0; i < hmf->unk1A; i++, particle++) {
            if (particle->unk04 > 0.0f) {
                break;
            }
        }
        if (i == hmf->unk1A) {
            Hu3DModelKill(model);
            omDelObj(obj);
            return;
        }
        bc->unk04 &= ~1;
    }
    if (bc->unk14 >= 0.0f) {
        if ((bc->unk14 -= 1.0f) <= 0.0f) {
            bc->unk04 &= ~1;
        }
    }
    if (bc->unk04 & 1) {
        x = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        z = rand8() * bc->unk10.f / 256.0f - bc->unk10.f / 2.0f;
        func_80110724_mstory4(model, x + bc->unk1C.f, bc->unk20.f, z + bc->unk24.f);
    }
}

s32 func_80110724_mstory4(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk04 = particle->unk08 =
                bc->unk08.f * 0.7f + bc->unk08.f * 0.3f * ((rand8() % 10 + 1) * 0.1f);
            return 1;
        }
    }
    return 0;
}

void func_80110888_mstory4(s16 modelId, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = unkBC->unk58;
    s16 i;

    unkBC->unk08.f = x;
    unkBC->unk0C.f = y;
    for (i = 0; i < hmf->unk1A; i++) {
        entry->unk1C = -z;
        entry++;
    }
}

s16 func_801108FC_mstory4(s32 file, s32 flags) {
    s16 model = func_80110B4C_mstory4(file, flags);
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry;
    s16 i;

    func_80013390_main(model, -1, 0, func_801109EC_mstory4);
    hmf = Hu3DData[model].hmf;
    unkBC = Hu3DData[model].unkBC;
    entry = unkBC->unk58;
    unkBC->unk08.f = 5.0f;
    unkBC->unk0C.f = 20.0f;
    for (i = 0; i < hmf->unk1A; i++, entry++) {
        entry->unk0C = entry->unk10 = entry->unk14 = 0.0f;
        entry->unk18 = entry->unk20 = 0.0f;
        entry->unk1C = -10.0f;
        entry->unk04 = entry->unk08 = 0.0f;
    }
    return model;
}

void func_801109EC_mstory4(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 i;
    s16 count;

    for (i = 0, count = hmf->unk1A; i < count; i++, particle++) {
        if (particle->unk04 > 0.0f) {
            particle->unk0C = particle->unk0C * 0.04f + particle->unk18 + particle->unk0C;
            particle->unk10 += particle->unk1C;
            particle->unk14 = particle->unk14 * 0.04f + particle->unk20 + particle->unk14;
            particle->unk04 -= bc->unk08.f / bc->unk0C.f;
            if (particle->unk04 <= 0.0f) {
                particle->unk04 = 0.0f;
            }
            particle->unk08 = (D_80111BFC_mstory4[(bc->unk02 + i) & 3] * 0.15f + 1.0f) * particle->unk04;
        }
    }
    bc->unk02++;
}

s16 func_80110B4C_mstory4(s32 dataNum, s32 attr) {
    s16 model = func_8000B108_main(dataNum, attr);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

void func_80110BB4_mstory4(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    Vec rot;
    f32 step;
    f32 y;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    step = (230.0f - rot.y) / 12.0f;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        y = sindf(i * 15.0f) * 80.0f;
        rot.y += step;
        Hu3DModelPosSet(model, pos.x, y + pos.y, pos.z);
        Hu3DModelRotSet(model, rot.x, y + rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110D5C_mstory4(omObjData *obj) {
    HuPrcSleep(30);
    func_80107480_mstory4(obj, -30.0f, -45.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110DB0_mstory4(f32 x, f32 y, f32 z, s16 arg3) {
    Process *process = omAddPrcObj(func_80110E3C_mstory4, 0x3F00, 0x2000, 0);
    UnkMstory4Work *work = HuMemAllocTag(sizeof(UnkMstory4Work), 0x7918);

    process->user_data = work;
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    work->unk_02 = arg3;
    work->unk_00 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110E3C_mstory4);

void func_80111430_mstory4(s16 model, f32 x, f32 y, f32 z, s16 count, s32 randomAxis) {
    f32 step = 360.0f / count;
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = Hu3DData[model].unkBC->unk58;
    s16 total = hmf->unk1A;
    f32 ax;
    f32 ay;
    f32 az;
    f32 len;
    f32 angle;
    s16 type;
    s16 i;
    s16 j;

    if (randomAxis) {
        while (TRUE) {
            ax = rand8() - 128;
            ay = rand8() - 128;
            az = rand8() - 128;
            len = ax * ax + ay * ay + az * az;
            if (len != 0.0f) {
                break;
            }
        }
    } else {
        ax = 0.0f;
        ay = 0.0f;
        az = 1.0f;
        len = ax * ax + ay * ay + az * az;
    }
    len = HuSqrtf(len);
    ax /= len;
    ay /= len;
    az /= len;
    type = rand8() & 3;
    for (i = 0, j = 0; j < total; j++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            angle = step * i;
            particle->unk18 = ax * ay * (1.0f - cosdf(angle)) - az * sindf(angle);
            particle->unk1C = ay * ay + (1.0f - ay * ay) * cosdf(angle);
            particle->unk20 = ay * az * (1.0f - cosdf(angle)) + ax * sindf(angle);
            particle->unk24 = type;
            particle->unk28 = 0.0f;
            particle->unk08 = 1.0f;
            particle->unk04 = 20.0f;
            if (++i >= count) {
                break;
            }
        }
    }
}

void func_80111740_mstory4(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count;
    s16 i;
    s16 color;
    f32 dx;
    f32 dy;
    f32 dz;

    if (bc->unk00 == -1) {
        count = hmf->unk1A;
    } else {
        count = hmf->unk60[bc->unk00].unk2E;
    }
    particle = bc->unk58;
    if (bc->unk02 >= 50) {
        if (!(bc->unk04 & 1)) {
            return;
        }
        bc->unk02 = 0;
    }
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            color = particle->unk24;
            particle->unk28 += 1.0f;
            particle->unk00[0] = D_80111C04_mstory4[color * 3 + 0];
            particle->unk00[1] = D_80111C04_mstory4[color * 3 + 1];
            particle->unk00[2] = D_80111C04_mstory4[color * 3 + 2];
            dx = particle->unk18 * particle->unk04;
            dy = particle->unk1C * particle->unk04;
            dz = particle->unk20 * particle->unk04;
            particle->unk0C += dx;
            particle->unk10 += dy;
            particle->unk14 += dz;
            particle->unk04 *= 0.9f;
            particle->unk08 -= 0.05f;
        }
    }
}

void func_801118F8_mstory4(s32 index, s32 seNo) {
    if (D_801122A0_mstory4[index].unk_0C == 0) {
        D_801122A0_mstory4[index].unk_0C = 1;
        D_801122A0_mstory4[index].unk_10 = seNo;
        if (index == 0) {
            D_801122A0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
        }
    }
}

void func_8011196C_mstory4(s32 index) {
    if (D_801122A0_mstory4[index].unk_0C == 1) {
        D_801122A0_mstory4[index].unk_0C = 0;
        if (index == 0) {
            HuAudFXStop((s16)D_801122A0_mstory4[0].unk_14);
        }
    }
}

void func_801119C0_mstory4(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 3; i++) {
            if (D_801122A0_mstory4[i].unk_0C == 1 && Hu3DData[D_801122A0_mstory4[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801122A0_mstory4[i].unk_10;
                if (i == 0) {
                    D_801122A0_mstory4[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                }
            }
        }
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112088_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_8011208C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120B8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120D4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120F4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112114_mstory4);
