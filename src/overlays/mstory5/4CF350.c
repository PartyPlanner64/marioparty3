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

typedef struct UnkMstory5Particle {
    /* 0x00 */ f32 time;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec vel;
} UnkMstory5Particle; // sizeof 0x1C

extern Vec D_80114778_mstory5[];
extern Vec D_801147A8_mstory5[];
extern Vec D_80114828_mstory5[];
extern Vec D_80114858_mstory5[];
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011473C_mstory5;
extern Vec D_80114748_mstory5;
extern Vec D_80114754_mstory5;

extern s32 D_80114730_mstory5;
extern s32 D_80114734_mstory5;
extern s8 D_80114738_mstory5;
extern s32 D_80114760_mstory5;
extern s16 D_80114770_mstory5;
extern s32 D_80114774_mstory5;
extern s32 D_80114820_mstory5;
extern s32 D_80114824_mstory5;
extern const Vec D_80114948_mstory5;
extern Vec D_80114A88_mstory5;
extern Vec D_80114C44_mstory5;
extern const Vec D_80114D5C_mstory5;
extern const Vec D_80114C84_mstory5;
extern const Vec D_80114C90_mstory5;
extern Vec D_80114EB8_mstory5;
extern Vec D_80114EC4_mstory5;
extern Vec D_80114F78_mstory5;
extern Vec D_80114F84_mstory5;
extern Vec D_80114F90_mstory5;
extern Vec D_80114F9C_mstory5;
extern Vec D_80115134_mstory5;
extern s16 D_801151B0_mstory5;
extern s16 D_801151B2_mstory5;
extern s32 D_801151B4_mstory5;
extern void (*const D_801148A0_mstory5[])(void);
extern const s32 D_801148A8_mstory5[];
extern u16 D_801151B8_mstory5;
extern s32 D_801151E4_mstory5;
extern UnkStoryObj D_801151F0_mstory5[9];
extern UnkStoryObj D_801152C8_mstory5[2];
extern Vec D_80115340_mstory5;
extern s16 D_80115364_mstory5;
extern Vec D_80115328_mstory5;
extern const Vec D_80114930_mstory5;
extern s16 D_80115368_mstory5;
extern s16 D_80115372_mstory5;
extern s32 D_80115370_mstory5[4];
extern Vec D_80115304_mstory5;
extern const Vec D_8011490C_mstory5;
extern s16 D_8011537A_mstory5;
extern s16 D_80115380_mstory5;
extern s16 D_80115384_mstory5;
extern s16 D_8011538A_mstory5[4];
extern s16 D_80115382_mstory5[4];
extern const Vec D_80114C9C_mstory5;
extern const Vec D_80114CA8_mstory5;
extern UnkStoryObj D_801153A0_mstory5[8];
extern Vec D_8011549C_mstory5;
extern UnkMstory5Particle D_801154F8_mstory5[16];
extern const Vec D_80114D44_mstory5;
extern Vec D_801154A8_mstory5;
extern const Vec D_80114D50_mstory5;
extern Vec D_801154B4_mstory5;
extern Vec D_80115358_mstory5;
extern const Vec D_80114960_mstory5;
extern const s32 D_80114C78_mstory5[];
extern s16 D_80115366_mstory5;
extern Vec D_801147F0_mstory5[];
extern Vec D_80115310_mstory5;
extern const Vec D_80114918_mstory5;
extern Vec D_80115490_mstory5;
extern const Vec D_80114D38_mstory5;
extern s16 D_801154D8_mstory5;
extern s16 D_801154EE_mstory5;
extern s16 D_801154F0_mstory5;
extern s32 D_801154E4_mstory5[3];
extern s16 D_801154E6_mstory5;
extern Vec D_80115484_mstory5;
extern const Vec D_80114D2C_mstory5;
extern Vec D_801150E0_mstory5;
extern Vec D_801150EC_mstory5;
extern Vec D_801150F8_mstory5;
extern Vec D_80115110_mstory5;
extern Vec D_8011511C_mstory5;
extern Vec D_80115128_mstory5;
extern Vec D_801154CC_mstory5;
extern const Vec D_80114D74_mstory5;
extern s16 D_801154DA_mstory5;
extern const s32 D_8011514C_mstory5[];
extern Vec D_80115334_mstory5;
extern const Vec D_8011493C_mstory5;
extern Vec D_801154C0_mstory5;
extern const Vec D_80114D68_mstory5;
extern Vec D_80115038_mstory5;
extern Vec D_80115050_mstory5;
extern Vec D_80115068_mstory5;
extern Vec D_80115074_mstory5;

void func_8010F7D4_mstory5(MstoryPath *path, f32 t, Vec *out);
void func_80106028_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106DB4_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
s32 func_801072A0_mstory5(s16 model);
void func_801085D8_mstory5(omObjData *obj);
void func_80109B30_mstory5(omObjData *obj);
void func_8010CFE4_mstory5(void);
void func_8010D230_mstory5(void);
void func_8010E3F0_mstory5(omObjData *obj, omObjData *target);
void func_8010734C_mstory5(omObjData *obj, f32 speed, s16 frames);
void func_8010E8C0_mstory5(omObjData *obj);
void func_8010F14C_mstory5(s32 index, s32 seNo);
void func_8010F240_mstory5(s32 index);
void func_8010F41C_mstory5(omObjData *obj);
void func_801074E8_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
void func_80110200_mstory5(omObjData *obj);
MstoryPath *func_80107850_mstory5(Vec *points, s32 flags);
void func_80107B54_mstory5(MstoryPath *path, f32 t, Vec *out);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);
void func_80112994_mstory5(void);
void func_80113130_mstory5(void);
void func_8010DE7C_mstory5(void);
void func_8010AE0C_mstory5(void);
void func_8010AE14_mstory5(omObjData *obj);
void func_80111FE0_mstory5(void);
void func_80111FE8_mstory5(omObjData *obj);
void func_80111820_mstory5(omObjData *obj);
void func_80110208_mstory5(void);
void func_801114E8_mstory5(void);
void func_80111818_mstory5(void);
void func_80111DB8_mstory5(void);
void func_8011275C_mstory5(void);
void func_80112F38_mstory5(void);
void func_80113470_mstory5(void);
void func_801085E0_mstory5(void);
void func_801097B8_mstory5(void);
void func_80109B28_mstory5(void);
void func_8010ABE4_mstory5(void);
void func_8010AF44_mstory5(void);
void func_8010B77C_mstory5(void);
void func_8010B9CC_mstory5(void);
void func_8010C4B8_mstory5(void);
void func_8010CBE8_mstory5(void);
void func_8010E558_mstory5(void);
void func_8010E5D0_mstory5(void);
void func_8010DC78_mstory5(void);
void func_8010DB30_mstory5(void);
void func_8010F2BC_mstory5(void);
void func_8010C85C_mstory5(void);
void func_8010CBE0_mstory5(void);
void func_8011396C_mstory5(void);
void func_80113974_mstory5(void);
void func_80113D2C_mstory5(void);
void func_80113E58_mstory5(void);
void func_80112104_mstory5(void);
void func_801145DC_mstory5(void);
void func_8010C69C_mstory5(void);
void func_80113B64_mstory5(void);
void func_80114010_mstory5(void);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106028_mstory5);

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

void func_80107080_mstory5(omObjData *obj, Vec *target, s32 frames) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801074E8_mstory5);

MstoryPath *func_80107850_mstory5(Vec *points, s32 flags) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107B54_mstory5);

void func_801083FC_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010842C_mstory5(void) {
    func_801069B8_mstory5();
    D_80115364_mstory5 = func_8000B108_main(9, 0x2B9);
    D_80115368_mstory5 = func_8000B108_main(0x83, 0x2B9);
    omAddPrcObj(func_801085E0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_801097B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010ABE4_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010AF44_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010B77C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C4B8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010C85C_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010CBE8_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E558_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010E5D0_mstory5, 0x1002, 0x800, 0);
    omAddPrcObj(func_8010DC78_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_8010DB30_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010F2BC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115364_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(D_80115368_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_801085D8_mstory5(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801085E0_mstory5);

void func_80108A20_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148C4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114900_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011490C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114918_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114924_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114930_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011493C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114948_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114954_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114960_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011496C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011498C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149AC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149CC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801149EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A18_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80108A28_mstory5);

void func_80109698_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_8010975C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114A88_mstory5, 10);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

void func_80109790_mstory5(void) {
    func_8010E3F0_mstory5(D_801151F0_mstory5[0].obj, D_801151F0_mstory5[3].obj);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114A88_mstory5);

const char D_80114A94_mstory5[] = "c204n_0_DEF";

void func_801097B8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801151F0_mstory5[1].obj = obj;
    D_801151F0_mstory5[1].unk_08 = 0;
    D_801151F0_mstory5[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8000B460_main(obj, 2, 0x1D002A);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115304_mstory5 = D_8011490C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115304_mstory5.x, D_80115304_mstory5.y, D_80115304_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115304_mstory5.x, -5.0f, D_80115304_mstory5.z);
    data = DataRead(0xA007E);
    D_80115370_mstory5[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80114A94_mstory5);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_80115372_mstory5, 1, 0);
    Hu3DAnimBankSet(D_80115372_mstory5, 0);
    D_80115380_mstory5 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_80115372_mstory5, 0, D_80114A94_mstory5);
    D_80115370_mstory5[0] = D_800D1714_main[D_80115370_mstory5[0]].animIdx;
    data = DataRead(0xA0080);
    D_80115370_mstory5[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_80115370_mstory5[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0085);
    D_80115370_mstory5[3] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    omPrcSetDestructor(0, func_80109B28_mstory5);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80109B28_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AA0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109B30_mstory5);

void func_80109E70_mstory5(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_80109F48_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec orig;
    s32 i;

    orig.x = Hu3DData[model].pos.x;
    orig.y = Hu3DData[model].pos.y;
    orig.z = Hu3DData[model].pos.z;
    pos.y = Hu3DData[model].pos.y;
    for (i = 0; i < 12; i++) {
        pos.x = Hu3DData[model].pos.x;
        pos.z = Hu3DData[model].pos.z;
        Hu3DModelPosSet(model, pos.x, sindf(i * 15.0f) * 80.0f + pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, orig.x, orig.y, orig.z);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_8011537A_mstory5);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010A0A8_mstory5);

void func_8010ABC4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
}

void func_8010ABE4_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[2].obj = obj;
    D_801151F0_mstory5[2].unk_08 = 0;
    D_801151F0_mstory5[2].unk_0C = 0;
    if (func_80106B30_mstory5(0) == 0) {
        obj->model[1] = func_8000B108_main(0x200A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        func_8000B460_main(obj, 0, 0x20000);
        func_8000B460_main(obj, 1, 0x1D003C);
        func_8000B460_main(obj, 2, 0x1D003D);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115310_mstory5 = D_80114918_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115310_mstory5.x, D_80115310_mstory5.y, D_80115310_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115310_mstory5.x, -5.0f, D_80115310_mstory5.z);
    omPrcSetDestructor(0, func_8010AE0C_mstory5);
    D_801151F0_mstory5[2].func = func_8010AE14_mstory5;
    while (1) {
        D_801151F0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

void func_8010AE0C_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AD0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114ADC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AE8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114B9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BB4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BCC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114BF0_mstory5);

const Vec D_80114C08_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_8010AE14_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x26B, 0);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801151F0_mstory5[1].func = func_80109B30_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(0) == 0) {
        CharFXPlay(0x286, 0);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010F14C_mstory5(2, 40);
    func_80106B48_mstory5(obj, &D_80114C08_mstory5, 40);
    func_8010F240_mstory5(2);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[2].func = func_801085D8_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AF44_mstory5);

void func_8010B318_mstory5(void) {
}

void func_8010B320_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80105D4C_mstory5();
    HuPrcSleep(15);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    while (!(D_801151F0_mstory5[1].unk_08 & 2)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuAudFXVolSet(HuAudFXPlay(0x297), 90);
    func_80107254_mstory5(model);
    D_801151F0_mstory5[3].unk_08 |= 8;
    while (!(D_801151F0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 40);
    HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, 64);
    D_801152C8_mstory5[1].func = func_8010F41C_mstory5;
    func_801074E8_mstory5(obj, 150.0f, 0.0f, 384.0f, 180, 1);
    func_8010F240_mstory5(3);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[10]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].unk_08 |= 4;
    HuPrcSleep(60);
    func_801068E4_mstory5(D_801151F0_mstory5[1].obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].unk_08 |= 2;
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B5DC_mstory5(omObjData *obj) {
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(3);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B6F8_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010B77C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    D_801151F0_mstory5[4].obj = obj;
    D_801151F0_mstory5[4].unk_08 = 0;
    D_801151F0_mstory5[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    obj->model[3] = func_8000B108_main(0x1D0027, 0x2B9);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[3], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115328_mstory5 = D_80114930_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115328_mstory5.x, D_80115328_mstory5.y, D_80115328_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115328_mstory5.x, -5.0f, D_80115328_mstory5.z);
    omPrcSetDestructor(0, func_8010B9CC_mstory5);
    D_801151F0_mstory5[4].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_8010B9CC_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B9D4_mstory5);

void func_8010C4B8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[5].obj = obj;
    D_801151F0_mstory5[5].unk_08 = 0;
    D_801151F0_mstory5[5].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115334_mstory5 = D_8011493C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115334_mstory5.x, D_80115334_mstory5.y, D_80115334_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115334_mstory5.x, -5.0f, D_80115334_mstory5.z);
    omPrcSetDestructor(0, func_8010C69C_mstory5);
    D_801151F0_mstory5[5].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

void func_8010C69C_mstory5(void) {
}

void func_8010C6A4_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106FC8_mstory5(obj, 100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 210.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

void func_8010C85C_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801151F0_mstory5[6].obj = obj;
    D_801151F0_mstory5[6].unk_08 = 0;
    D_801151F0_mstory5[6].unk_0C = 0;
    src = D_801151F0_mstory5[5].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_80115340_mstory5 = D_80114948_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115340_mstory5.x, D_80115340_mstory5.y, D_80115340_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115340_mstory5.x, -5.0f, D_80115340_mstory5.z);
    omPrcSetDestructor(0, func_8010CBE0_mstory5);
    D_801151F0_mstory5[6].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

void func_8010CA04_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *src = D_801151F0_mstory5[5].obj;
    Vec pos;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[1]].motId, 0, 10, 2);
    func_80106FC8_mstory5(obj, -100.0f, pos.y, pos.z, 30);
    Hu3DMotionShiftSet(model, Hu3DData[src->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 200.0f, 0.0f, 10);
    while (!(D_801151F0_mstory5[0].unk_08 & 1)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[src->motion[2]].motId, 0, 10, 2);
        func_80107254_mstory5(model);
    }
}

void func_8010CBE0_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CBE8_mstory5);

void func_8010CFE4_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[5];
    func_8001C258_main(models[0], 4, 4);
    func_8001C258_main(models[1], 4, 0);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[5] = models[0];
}

void func_8010D214_mstory5(void) {
    func_8010CFE4_mstory5();
}

void func_8010D230_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    s16 models[2];

    models[0] = obj->model[1];
    models[1] = obj->model[8];
    func_8001C258_main(models[0], 4, 4);
    func_8001C258_main(models[1], 4, 0);
    Hu3DData[models[1]].pos.x = Hu3DData[models[0]].pos.x;
    Hu3DData[models[1]].pos.y = Hu3DData[models[0]].pos.y;
    Hu3DData[models[1]].pos.z = Hu3DData[models[0]].pos.z;
    Hu3DData[models[1]].rot.x = Hu3DData[models[0]].rot.x;
    Hu3DData[models[1]].rot.y = Hu3DData[models[0]].rot.y;
    Hu3DData[models[1]].rot.z = Hu3DData[models[0]].rot.z;
    Hu3DData[models[1]].scale.x = Hu3DData[models[0]].scale.x;
    Hu3DData[models[1]].scale.y = Hu3DData[models[0]].scale.y;
    Hu3DData[models[1]].scale.z = Hu3DData[models[0]].scale.z;
    obj->model[1] = models[1];
    obj->model[8] = models[0];
}

void func_8010D460_mstory5(void) {
    func_8010D230_mstory5();
}

void func_8010D47C_mstory5(void) {
}

void func_8010D484_mstory5(void) {
    omObjData *obj = D_801151F0_mstory5[7].obj;
    Vec pos;
    s16 model = obj->model[1];

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010D560_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114C44_mstory5, 20);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

void func_8010D594_mstory5(omObjData *obj) {
    s32 frames = 20;
    omObjData *objs[4];
    Vec dist;
    f32 speed[3];
    s32 i;
    s32 j;

    dist.x = 150.0f;
    dist.y = 350.0f;
    dist.z = 400.0f;
    speed[0] = dist.x / frames;
    speed[1] = dist.y / frames;
    speed[2] = dist.z / frames;

    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[1].obj;
    objs[2] = D_801151F0_mstory5[7].obj;
    objs[3] = D_801151F0_mstory5[3].obj;
    func_80107228_mstory5(objs[0], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[1], 0.0f, 90.0f, 0.0f, 10);
    func_80107228_mstory5(objs[2], 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].pos.x -= speed[j];
            Hu3DData[objs[j]->model[2]].pos.x -= speed[j];
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].unk_08 |= 1;
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C44_mstory5);

void func_8010D7D8_mstory5(omObjData *obj) {
    omObjData *objs[3];
    f32 rotY[3] = { 90.0f, 135.0f, 135.0f };
    f32 rotX[3] = { 0.0f, 10.0f, 20.0f };
    s32 frames;
    s32 i;
    s32 j;

    frames = 20;
    objs[0] = D_801151F0_mstory5[0].obj;
    objs[1] = D_801151F0_mstory5[7].obj;
    objs[2] = D_801151F0_mstory5[1].obj;
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y += 90.0f / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].unk_08 & 2)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[3]].motId, 0, 10, 2);
    frames = 20;
    for (i = 0; i < frames; i++) {
        for (j = 0; j < 3; j++) {
            Hu3DData[objs[j]->model[1]].rot.y -= rotY[j] / frames;
            Hu3DData[objs[j]->model[1]].rot.x += rotX[j] / frames;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(objs[0]->model[1], Hu3DData[objs[0]->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

const s32 D_80114C68_mstory5[] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006 };

void func_8010DADC_mstory5(omObjData *obj) {
    HuPrcSleep(60);
    func_80107228_mstory5(obj, 0.0f, 30.0f, 0.0f, 50);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

#ifdef NON_MATCHING
void func_8010DB30_mstory5(void) {
    f32 angle = 0.0f;
    omObjData *obj;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114774_mstory5 != 0) {
        obj = D_801151F0_mstory5[7].obj;
        pos.y = Hu3DData[obj->model[1]].pos.y;
        while (TRUE) {
            model = obj->model[1];
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            if (D_80114770_mstory5 != 1) {
                Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            }
            HuPrcVSleep();
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DB30_mstory5);
#endif

void func_8010DC78_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801151F0_mstory5[8].obj = obj;
    D_801151F0_mstory5[8].unk_08 = 0;
    D_801151F0_mstory5[8].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_80114C78_mstory5[0], 0x20299);
    obj->model[2] = func_8000B108_main(D_80114C78_mstory5[1], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C814_main(obj->model[2], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_80115358_mstory5 = D_80114960_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115358_mstory5.x, D_80115358_mstory5.y, D_80115358_mstory5.z);
    D_80115366_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_80115366_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_80115366_mstory5, 60.0f);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    func_8001C258_main(D_80115366_mstory5, 4, 4);
    omPrcSetDestructor(0, func_8010DE7C_mstory5);
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
    while (1) {
        D_801151F0_mstory5[8].func(obj);
        HuPrcVSleep();
    }
}

void func_8010DE7C_mstory5(void) {
}

void func_8010DE84_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_80107850_mstory5(D_80114778_mstory5, 0);
    paths[1] = func_80107850_mstory5(D_801147A8_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_80115366_mstory5, 4, 0);
    func_800138EC_main(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801151F0_mstory5[7].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[3]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801151F0_mstory5[8].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_80107B54_mstory5(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    HuAudFXPlay(0x21A);
    func_801083FC_mstory5(paths[0]);
    func_801083FC_mstory5(paths[1]);
    D_801151F0_mstory5[8].unk_08 = 1;
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
}

void func_8010E1A0_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *path;
    s32 i;

    path = func_80107850_mstory5(D_801147F0_mstory5, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_800138EC_main(D_80115366_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(path, (i * 0.02f) * (i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    while (!(D_801151F0_mstory5[8].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 50; i++) {
        func_80107B54_mstory5(path, (1.0f - i * 0.02f) * (1.0f - i * 0.02f), &pos);
        pos.x += -100.0f;
        Hu3DModelPosSet(obj->model[2], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_80115366_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[2], 4, 4);
    func_800138EC_main(D_80115366_mstory5, 1, 0);
    func_801083FC_mstory5(path);
    D_801151F0_mstory5[8].unk_08 = 8;
    D_801151F0_mstory5[8].func = func_801085D8_mstory5;
}

void func_8010E3F0_mstory5(omObjData *obj, omObjData *target) {
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

void func_8010E538_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[3].obj);
}

void func_8010E558_mstory5(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801152C8_mstory5[0].obj = obj;
    D_801152C8_mstory5[0].unk_08 = 0;
    D_801152C8_mstory5[0].unk_0C = 0;
    D_801152C8_mstory5[0].func = func_801085D8_mstory5;

    for (;;) {
        D_801152C8_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}

void func_8010E5D0_mstory5(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801152C8_mstory5[1].obj = obj;
    D_801152C8_mstory5[1].unk_08 = 0;
    D_801152C8_mstory5[1].unk_0C = 0;
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;

    for (;;) {
        D_801152C8_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_8010E648_mstory5(omObjData *obj) {
    func_80106A20_mstory5();
    func_80106AC8_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A56 : 0x5B4A);
    func_80106AF4_mstory5();
    func_80106A50_mstory5();
    D_801151F0_mstory5[4].unk_08 |= 0x10;
    D_801152C8_mstory5[0].func = func_801085D8_mstory5;
}

void func_8010E6B4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    func_8010F14C_mstory5(3, 31);
    func_8010734C_mstory5(obj, 4.5f, 15);
    func_8010F240_mstory5(3);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    D_801152C8_mstory5[1].func = func_8010E8C0_mstory5;
}

void func_8010E7B0_mstory5(omObjData *obj) {
    while (TRUE) {
        if (Hu3DData[obj->model[1]].pos.y > 100.0f) {
            Hu3DData[obj->model[1]].pos.y -= 2.0f;
            HuPrcVSleep();
        } else {
            break;
        }
    }
    Hu3DData[obj->model[1]].pos.y = 100.0f;
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010E870_mstory5(omObjData *obj) {
    Vec pos = D_80114C84_mstory5;

    func_80107080_mstory5(obj, &pos, 10);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

void func_8010E8C0_mstory5(omObjData *obj) {
    omObjData *player = D_801151F0_mstory5[0].obj;

    func_8010E3F0_mstory5(player, D_801151F0_mstory5[3].obj);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[3]].motId, 0, 30, 2);
    func_8010F14C_mstory5(0, 31);
    func_8010734C_mstory5(player, 3.5f, 15);
    func_8010F240_mstory5(0);
    func_80017954_main(player->model[1], 2, GwStory.unk1, D_80115384_mstory5);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[11]].motId, 0, 30, 2);
    func_80017954_main(D_801151F0_mstory5[3].obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[11]].motId, 0, 30, 2);
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010EA34_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    Vec pos;
    Vec target = D_80114C90_mstory5;
    f32 y;
    s16 i;

    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_801068E4_mstory5(model, D_80115380_mstory5, D_8011537A_mstory5);
    for (i = 0; i < 13; i++) {
        y = sindf(i * 12.000001f) * 80.0f;
        Hu3DData[model].pos.y = y + pos.y;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &target, 5);
    func_801068E4_mstory5(model, D_80115380_mstory5, D_80115372_mstory5);
    D_801151F0_mstory5[1].unk_08 |= 2;
    D_801151F0_mstory5[1].func = func_8010E538_mstory5;
}

void func_8010EBCC_mstory5(omObjData *obj) {
    Vec pos = D_80114C9C_mstory5;
    Vec target;
    omObjData *player = D_801151F0_mstory5[0].obj;

    target.x = Hu3DData[player->model[1]].pos.x - 5.0f;
    target.y = Hu3DData[player->model[1]].pos.y;
    target.z = 500.0f;
    Hu3DModelRotSet(player->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(player->model[4], Hu3DData[player->model[1]].pos.x, Hu3DData[player->model[1]].pos.y, Hu3DData[player->model[1]].pos.z);
    Hu3DMotionTimeSet(player->model[4], 0.0f);
    func_8001C258_main(player->model[4], 4, 0);
    func_80017954_main(player->model[1], 2, GwStory.unk1, D_80115382_mstory5[3]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[4]].motId, 0, 30, 0);
    func_80106B48_mstory5(player, &target, 10);
    func_80107254_mstory5(player->model[1]);
    func_80017954_main(player->model[1], 2, GwStory.unk1, D_80115382_mstory5[0]);
    Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[0]].motId, 0, 30, 2);
    func_80107080_mstory5(player, &pos, 10);
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010EDFC_mstory5(omObjData *obj) {
    Vec pos = D_80114CA8_mstory5;
    Vec target;
    Vec tmp;

    tmp.x = Hu3DData[obj->model[1]].pos.x + 5.0f;
    tmp.y = Hu3DData[obj->model[1]].pos.y;
    tmp.z = 500.0f;
    target = tmp;
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelPosSet(obj->model[3], Hu3DData[obj->model[1]].pos.x, Hu3DData[obj->model[1]].pos.y, Hu3DData[obj->model[1]].pos.z);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80017954_main(obj->model[1], 2, 7, D_8011538A_mstory5[3]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[14]].motId, 0, 30, 0);
    func_80106B48_mstory5(obj, &target, 10);
    func_80107254_mstory5(obj->model[1]);
    func_80017954_main(obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    func_80107080_mstory5(obj, &pos, 10);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

void func_8010F02C_mstory5(omObjData *obj) {
    omObjData *target = D_801151F0_mstory5[0].obj;

    func_80107228_mstory5(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[8]].motId, 0, 10, 0);
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;
}

void func_8010F0B8_mstory5(omObjData *obj) {
    omObjData *target = D_801151F0_mstory5[3].obj;

    func_80107228_mstory5(target, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[13]].motId, 0, 10, 0);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114CA8_mstory5);

void func_8010F14C_mstory5(s32 index, s32 seNo) {
    if (D_801151F0_mstory5[index].unk_0C == 0) {
        D_801151F0_mstory5[index].unk_0C = 1;
        D_801151F0_mstory5[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106B30_mstory5(0) == 0) {
                    D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 0);
                } else {
                    D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 3:
                D_801151F0_mstory5[index].unk_14 = CharFXPlay(seNo, 7);
                break;
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

void func_8010F240_mstory5(s32 index) {
    if (D_801151F0_mstory5[index].unk_0C == 1) {
        D_801151F0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
            case 3:
                HuAudFXStop((s16)D_801151F0_mstory5[index].unk_14);
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

// Code matches, but the jump table is followed by alignment padding in rodata,
// which suggests a file boundary at func_8010F4D0_mstory5.
#ifdef NON_MATCHING
void func_8010F2BC_mstory5(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 9; i++) {
            if (D_801151F0_mstory5[i].unk_0C == 1 && Hu3DData[D_801151F0_mstory5[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801151F0_mstory5[i].unk_10;
                switch (i) {
                    case 0:
                        D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106B30_mstory5(0) == 0) {
                            D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 0);
                        } else {
                            D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 3:
                        D_801151F0_mstory5[i].unk_14 = CharFXPlay(seNo, 7);
                        break;
                    case 1:
                    case 4:
                    case 5:
                    case 6:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F2BC_mstory5);
#endif

// Code matches, but the target is followed by alignment padding, which suggests
// a file boundary at func_8010F4D0_mstory5.
#ifdef NON_MATCHING
void func_8010F41C_mstory5(omObjData *obj) {
    f32 step = 0.35f;
    f32 vol = 0.0f;
    s32 i;

    if (D_801151F0_mstory5[3].unk_0C == 1) {
        for (i = 0; i < 180; i++) {
            HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, (s32)vol + 64);
            vol += step;
            HuPrcVSleep();
        }
        HuAudFXVolSet((s16)D_801151F0_mstory5[3].unk_14, 127);
    }
    D_801152C8_mstory5[1].func = func_801085D8_mstory5;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F41C_mstory5);
#endif

MstoryPath *func_8010F4D0_mstory5(Vec *points, s32 flags) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F7D4_mstory5);

void func_8011007C_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_801100AC_mstory5(void) {
    func_801069B8_mstory5();
    D_801154D8_mstory5 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_80110208_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_801114E8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80111DB8_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_8011275C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80112F38_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113470_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113974_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113D2C_mstory5, 0x1001, 0x800, 0);
    omAddPrcObj(func_80113E58_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_80112104_mstory5, 0x384, 0x800, 0);
    omAddPrcObj(func_801145DC_mstory5, 0x1001, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_801154D8_mstory5, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80110200_mstory5(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110208_mstory5);

void func_80110618_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D20_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D2C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D38_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D68_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D74_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114D80_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DA0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114DE0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E00_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80110620_mstory5);

void func_801113BC_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_80111480_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114EB8_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

void func_801114B4_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114EC4_mstory5, 10);
    D_801153A0_mstory5[0].func = func_80110200_mstory5;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E54_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114E9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EA8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EB8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EC4_mstory5);

const char D_80114ED0_mstory5[] = "c204n_0_DEF";

void func_801114E8_mstory5(void) {
    omObjData *obj;
    void *data;

    obj = omAddObj(20, 4, 8, -1, NULL);
    D_801153A0_mstory5[1].obj = obj;
    D_801153A0_mstory5[1].unk_08 = 0;
    D_801153A0_mstory5[1].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0075, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA0076);
    func_8000B460_main(obj, 1, 0x1D0029);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 30.0f, 390.0f, 0.0f);
    D_80115484_mstory5 = D_80114D2C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115484_mstory5.x, D_80115484_mstory5.y, D_80115484_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115484_mstory5.x, -5.0f, D_80115484_mstory5.z);
    data = DataRead(0xA007E);
    D_801154E4_mstory5[0] = (s16)Hu3DAnimCreate(Hu3DData[obj->model[1]].hmf, data, 0, D_80114ED0_mstory5);
    HuMemMemoryFreePerm(data);
    Hu3DModelRemakeStatic(obj->model[1]);
    func_8001C514_main(obj->model[1]);
    func_80032FC0_main(D_801154E6_mstory5, 1, 0);
    Hu3DAnimBankSet(D_801154E6_mstory5, 0);
    D_801154F0_mstory5 = Hu3DAnimLink(Hu3DData[obj->model[1]].hmf, D_801154E6_mstory5, 0, D_80114ED0_mstory5);
    D_801154E4_mstory5[0] = D_800D1714_main[D_801154E4_mstory5[0]].animIdx;
    data = DataRead(0xA0080);
    D_801154E4_mstory5[1] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    data = DataRead(0xA0083);
    D_801154E4_mstory5[2] = (s16)func_800329B4_main(data);
    HuMemMemoryFreePerm(data);
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154E6_mstory5);
    omPrcSetDestructor(0, func_80111818_mstory5);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
    while (TRUE) {
        D_801153A0_mstory5[1].func(obj);
        HuPrcVSleep();
    }
}

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EDC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111820_mstory5);

void func_80111B60_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114F9C_mstory5, 20);
    func_80106B48_mstory5(obj, &D_80114F78_mstory5, 20);
    while (!(D_801153A0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, &D_80114F90_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106B48_mstory5(obj, &D_80114F84_mstory5, 30);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111C48_mstory5(omObjData *obj) {
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
    func_801068E4_mstory5(obj->model[1], D_801154F0_mstory5, D_801154EE_mstory5);
    D_801153A0_mstory5[1].func = func_80110200_mstory5;
}

void func_80111DB8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[2].obj = obj;
    D_801153A0_mstory5[2].unk_08 = 0;
    D_801153A0_mstory5[2].unk_0C = 0;
    if (func_80106B30_mstory5(2) == 0) {
        obj->model[1] = func_8000B108_main(0x700A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x70000);
        func_8000B460_main(obj, 1, 0x1D0050);
        func_8000B460_main(obj, 2, 0x1D0051);
    } else {
        obj->model[1] = func_8000B108_main(0x300A0, 0x2B9);
        obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
        func_8000B460_main(obj, 0, 0x30000);
        func_8000B460_main(obj, 1, 0x1D0046);
        func_8000B460_main(obj, 2, 0x1D0047);
    }
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 340.0f, 0.0f);
    D_80115490_mstory5 = D_80114D38_mstory5;
    Hu3DModelPosSet(obj->model[1], D_80115490_mstory5.x, D_80115490_mstory5.y, D_80115490_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_80115490_mstory5.x, -5.0f, D_80115490_mstory5.z);
    omPrcSetDestructor(0, func_80111FE0_mstory5);
    D_801153A0_mstory5[2].func = func_80111FE8_mstory5;
    while (1) {
        D_801153A0_mstory5[2].func(obj);
        HuPrcVSleep();
    }
}

void func_80111FE0_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EF4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F0C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F18_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F24_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F30_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F3C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F48_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F60_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F6C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114F9C_mstory5);

const Vec D_80114FB4_mstory5 = { 200.0f, 0.0f, 1200.0f };

void func_80111FE8_mstory5(omObjData *obj) {
    HuPrcSleep(10);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x26B, 2);
    } else {
        CharFXPlay(0x26B, 1);
    }
    HuPrcSleep(20);
    D_801153A0_mstory5[1].func = func_80111820_mstory5;
    HuPrcSleep(70);
    if (func_80106B30_mstory5(2) == 0) {
        CharFXPlay(0x286, 2);
    } else {
        CharFXPlay(0x286, 1);
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[2]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80114FB4_mstory5, 40);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801153A0_mstory5[2].func = func_80110200_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112104_mstory5);

void func_80112514_mstory5(omObjData *obj) {
    Vec pos;
    Vec rot;
    Vec ofs;
    omObjData *boat;
    s16 model;
    s32 i;

    if (D_80114820_mstory5 >= 3) {
        D_80114820_mstory5 = 0;
        boat = D_801153A0_mstory5[3].obj;
        model = boat->model[1];
        pos.x = Hu3DData[model].pos.x;
        pos.y = Hu3DData[model].pos.y;
        pos.z = Hu3DData[model].pos.z;
        rot.x = Hu3DData[model].rot.x;
        rot.y = Hu3DData[model].rot.y;
        rot.z = Hu3DData[model].rot.z;
        for (i = 0; i < 16; i++) {
            if (D_801154F8_mstory5[i].time < 0.0f) {
                ofs.x = 0.0f;
                ofs.y = 150.0f;
                ofs.z = 300.0f;
                D_801154F8_mstory5[i].pos.x = cosdf(rot.y) * ofs.x + pos.x - sindf(rot.y) * ofs.z;
                D_801154F8_mstory5[i].pos.y = pos.y + ofs.y;
                D_801154F8_mstory5[i].pos.z = sindf(rot.y) * ofs.x + pos.z + cosdf(rot.y) * ofs.z;
                D_801154F8_mstory5[i].vel.x = sindf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].vel.y = cosdf(120.0f) * 5.0f;
                D_801154F8_mstory5[i].vel.z = cosdf(rot.y) * 5.0f;
                D_801154F8_mstory5[i].time = 0.0f;
                func_8001C258_main(boat->model[i + 1], 4, 0);
                break;
            }
        }
    }
    D_80114820_mstory5++;
}

void func_8011275C_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 16, 8, -1, NULL);
    D_801153A0_mstory5[3].obj = obj;
    D_801153A0_mstory5[3].unk_08 = 0;
    D_801153A0_mstory5[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA002F, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 3.0f, 1.0f, 3.0f);
    func_8000B460_main(obj, 0, 0xA0030);
    func_8000B460_main(obj, 1, 0xA0035);
    func_8000B460_main(obj, 2, 0xA0032);
    func_8000B460_main(obj, 3, 0xA003A);
    func_8000B460_main(obj, 4, 0xA003B);
    func_8000B460_main(obj, 5, 0x1D0031);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_8011549C_mstory5 = D_80114D44_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011549C_mstory5.x, D_8011549C_mstory5.y, D_8011549C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011549C_mstory5.x, -5.0f, D_8011549C_mstory5.z);
    omPrcSetDestructor(0, func_80112994_mstory5);
    D_801153A0_mstory5[3].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

void func_80112994_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011299C_mstory5);

void func_80112F38_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[4].obj = obj;
    D_801153A0_mstory5[4].unk_08 = 0;
    D_801153A0_mstory5[4].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA00EE, 0x2B9);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8000B460_main(obj, 0, 0xA00EF);
    func_8000B460_main(obj, 1, 0xA00F1);
    func_8000B460_main(obj, 2, 0xA00F0);
    func_8000B460_main(obj, 3, 0x1D0037);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801154A8_mstory5 = D_80114D50_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154A8_mstory5.x, D_801154A8_mstory5.y, D_801154A8_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154A8_mstory5.x, -5.0f, D_801154A8_mstory5.z);
    omPrcSetDestructor(0, func_80113130_mstory5);
    D_801153A0_mstory5[4].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[4].func(obj);
        HuPrcVSleep();
    }
}

void func_80113130_mstory5(void) {
}

void func_80113138_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_8001C258_main(model, 4, 0);
    func_8001C258_main(obj->model[2], 4, 0);
    func_80106B48_mstory5(obj, &D_80115038_mstory5, 40);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80115074_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(50);
    func_80107080_mstory5(obj, &D_80115068_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80106B48_mstory5(obj, &D_80115050_mstory5, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_80115074_mstory5, 10);
    while (!(D_801153A0_mstory5[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, &D_80115068_mstory5, 30);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x20)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
        func_80107254_mstory5(model);
    }
}

void func_80113470_mstory5(void) {
    omObjData *obj;
    omObjData *src;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[5].obj = obj;
    D_801153A0_mstory5[5].unk_08 = 0;
    D_801153A0_mstory5[5].unk_0C = 0;
    src = D_801153A0_mstory5[4].obj;
    obj->model[1] = Hu3DModelLink(src->model[1]);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    func_8001C5B4_main(obj->model[1], src->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 90.0f, 0.0f);
    D_801154B4_mstory5 = D_80114D5C_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154B4_mstory5.x, D_801154B4_mstory5.y, D_801154B4_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154B4_mstory5.x, -5.0f, D_801154B4_mstory5.z);
    omPrcSetDestructor(0, func_8011396C_mstory5);
    D_801153A0_mstory5[5].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113618_mstory5);

void func_8011396C_mstory5(void) {
}

void func_80113974_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 4, 8, -1, NULL);
    D_801153A0_mstory5[6].obj = obj;
    D_801153A0_mstory5[6].unk_08 = 0;
    D_801153A0_mstory5[6].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA0127);
    obj->model[2] = Hu3DModelLink(D_801154D8_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_801154C0_mstory5 = D_80114D68_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154C0_mstory5.x, D_801154C0_mstory5.y, D_801154C0_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801154C0_mstory5.x, -5.0f, D_801154C0_mstory5.z);
    omPrcSetDestructor(0, func_80113B64_mstory5);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
    D_80114824_mstory5 = 1;
    while (1) {
        D_801153A0_mstory5[6].func(obj);
        HuPrcVSleep();
    }
}

void func_80113B64_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FC0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FD8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FE4_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114FF0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115014_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115020_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011502C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115038_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115050_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115068_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115074_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115080_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115098_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150B0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150BC_mstory5);

const Vec D_801150C8_mstory5 = { 250.0f, 0.0f, 150.0f };
const Vec D_801150D4_mstory5 = { 800.0f, 0.0f, 350.0f };

void func_80113B6C_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_801150F8_mstory5, 20);
    func_80106B48_mstory5(obj, &D_801150C8_mstory5, 20);
    while (!(D_801153A0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(obj, &D_801150E0_mstory5, 30, 0);
    while (!(D_801153A0_mstory5[3].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    func_80107080_mstory5(obj, &D_80115128_mstory5, 40);
    while (!(D_801153A0_mstory5[3].unk_08 & 1)) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80107080_mstory5(obj, &D_801150F8_mstory5, 15);
    func_80106B64_mstory5(obj, &D_801150EC_mstory5, 5, 0);
    func_80107080_mstory5(obj, &D_80115110_mstory5, 10);
    func_80107080_mstory5(obj, &D_8011511C_mstory5, 10);
    func_80106B64_mstory5(obj, &D_801150D4_mstory5, 20, 0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

void func_80113CF8_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80115134_mstory5, 20);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

void func_80113D2C_mstory5(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114824_mstory5 != 0) {
        model = D_801153A0_mstory5[6].obj->model[1];
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

void func_80113E58_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 8, 0, -1, NULL);
    D_801153A0_mstory5[7].obj = obj;
    D_801153A0_mstory5[7].unk_08 = 0;
    D_801153A0_mstory5[7].unk_0C = 0;
    obj->model[1] = func_8000B108_main(D_8011514C_mstory5[0], 0x20299);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_801154CC_mstory5 = D_80114D74_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801154CC_mstory5.x, D_801154CC_mstory5.y, D_801154CC_mstory5.z);
    D_801154DA_mstory5 = func_8000CED8_main(0xB0004, 0x6A9);
    func_8000CD00_main(D_801154DA_mstory5, 4.0f, 20.0f, 4.0f);
    func_8000D018_main(D_801154DA_mstory5, 60.0f);
    func_800138EC_main(D_801154DA_mstory5, 1, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    omPrcSetDestructor(0, func_80114010_mstory5);
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
    while (1) {
        D_801153A0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

void func_80114010_mstory5(void) {
}

void func_80114018_mstory5(omObjData *obj) {
    Vec pos;
    MstoryPath *paths[2];
    omObjData *target;
    f32 rotY;
    s32 i;

    paths[0] = func_8010F4D0_mstory5(D_80114828_mstory5, 0);
    paths[1] = func_8010F4D0_mstory5(D_80114858_mstory5, 0);
    func_8001C258_main(obj->model[1], 4, 0);
    func_8001C258_main(D_801154DA_mstory5, 4, 0);
    func_800138EC_main(D_801154DA_mstory5, 1, 1);
    HuAudFXPlay(0x215);
    for (i = 0; i < 50; i++) {
        func_8010F7D4_mstory5(paths[0], (i * 0.02f) * (i * 0.02f), &pos);
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    target = D_801153A0_mstory5[6].obj;
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[2]].motId, 0, 10, 0);
    HuPrcSleep(20);
    D_801153A0_mstory5[7].unk_08 |= 2;
    HuAudFXPlay(0x218);
    Hu3DMotionShiftSet(target->model[1], Hu3DData[target->motion[0]].motId, 0, 10, 2);
    rotY = 0.0f;
    for (i = 0; i < 120; i++) {
        func_8010F7D4_mstory5(paths[1], (i * 0.008333334f) * (i * 0.008333334f), &pos);
        rotY -= 24.0f;
        Hu3DModelPosSet(obj->model[1], pos.x, pos.y, pos.z);
        Hu3DModelRotSet(obj->model[1], 0.0f, rotY, 0.0f);
        func_8000CFA4_main(D_801154DA_mstory5, pos.x, pos.y - 40.0f, pos.z);
        HuPrcVSleep();
    }
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(D_801154DA_mstory5, 4, 4);
    HuAudFXPlay(0x21A);
    func_8011007C_mstory5(paths[0]);
    func_8011007C_mstory5(paths[1]);
    D_801153A0_mstory5[7].unk_08 = 1;
    D_801153A0_mstory5[7].func = func_80110200_mstory5;
}

void func_80114334_mstory5(omObjData *obj, omObjData *target) {
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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011514C_mstory5);

void func_8011447C_mstory5(s32 index, s32 seNo) {
    if (D_801153A0_mstory5[index].unk_0C == 0) {
        D_801153A0_mstory5[index].unk_0C = 1;
        D_801153A0_mstory5[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106B30_mstory5(2) == 0) {
                    D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, 2);
                } else {
                    D_801153A0_mstory5[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_80114560_mstory5(s32 index) {
    if (D_801153A0_mstory5[index].unk_0C == 1) {
        D_801153A0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801153A0_mstory5[index].unk_14);
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_801145DC_mstory5(void) {
    s32 i;
    s32 seNo;

    while (TRUE) {
        for (i = 0; i < 8; i++) {
            if (D_801153A0_mstory5[i].unk_0C == 1 && Hu3DData[D_801153A0_mstory5[i].obj->model[1]].motTime == 0.0f) {
                seNo = D_801153A0_mstory5[i].unk_10;
                switch (i) {
                    case 0:
                        D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                        break;
                    case 2:
                        if (func_80106B30_mstory5(2) == 0) {
                            D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, 2);
                        } else {
                            D_801153A0_mstory5[i].unk_14 = CharFXPlay(seNo, 1);
                        }
                        break;
                    case 1:
                    case 3:
                    case 4:
                    case 5:
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}
