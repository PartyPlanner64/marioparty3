#include "common.h"

typedef struct UnkStoryObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 stopSeNo;
} UnkStoryObj; // sizeof 0x18

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011473C_mstory5;
extern Vec D_80114748_mstory5;
extern Vec D_80114754_mstory5;

extern s32 D_80114730_mstory5;
extern s8 D_80114738_mstory5;
extern s32 D_80114760_mstory5;
extern Vec D_80114A88_mstory5;
extern Vec D_80114C44_mstory5;
extern const Vec D_80114C84_mstory5;
extern Vec D_80114EB8_mstory5;
extern Vec D_80114EC4_mstory5;
extern Vec D_80115134_mstory5;
extern s16 D_801151B0_mstory5;
extern s16 D_801151B2_mstory5;
extern s32 D_801151B4_mstory5;
extern u16 D_801151B8_mstory5;
extern s32 D_801151E4_mstory5;
extern UnkStoryObj D_801151F0_mstory5[9];
extern UnkStoryObj D_801152C8_mstory5[2];
extern UnkStoryObj D_801153A0_mstory5[8];

void func_80106028_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_80106DB4_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
s32 func_801072A0_mstory5(s16 model);
void func_801085D8_mstory5(omObjData *obj);
void func_8010CFE4_mstory5(void);
void func_8010D230_mstory5(void);
void func_8010E3F0_mstory5(omObjData *obj, omObjData *target);
void func_80110200_mstory5(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801059A0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148A0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801148A8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80105BDC_mstory5);

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

void func_80105F5C_mstory5(void) {
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

void func_80106B48_mstory5(omObjData *obj, Vec *pos, s32 frames) {
    func_80106B64_mstory5(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106B64_mstory5);

void func_80106D98_mstory5(omObjData *obj, Vec *pos, s32 frames) {
    func_80106DB4_mstory5(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80106DB4_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107080_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010734C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801074E8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107850_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80107B54_mstory5);

void func_801083FC_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010842C_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801097B8_mstory5);

void func_80109B28_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114AA0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109B30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109E70_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80109F48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010A0A8_mstory5);

void func_8010ABC4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010ABE4_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AE14_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010AF44_mstory5);

void func_8010B318_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B320_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B5DC_mstory5);

void func_8010B6F8_mstory5(omObjData *obj) {
    s16 model = obj->model[1];

    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B77C_mstory5);

void func_8010B9CC_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010B9D4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C4B8_mstory5);

void func_8010C69C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C6A4_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010C85C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CA04_mstory5);

void func_8010CBE0_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CBE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010CFE4_mstory5);

void func_8010D214_mstory5(void) {
    func_8010CFE4_mstory5();
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D230_mstory5);

void func_8010D460_mstory5(void) {
    func_8010D230_mstory5();
}

void func_8010D47C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D484_mstory5);

void func_8010D560_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80114C44_mstory5, 20);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D594_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010D7D8_mstory5);

void func_8010DADC_mstory5(omObjData *obj) {
    HuPrcSleep(60);
    func_80107228_mstory5(obj, 0.0f, 30.0f, 0.0f, 50);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DB30_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DC78_mstory5);

void func_8010DE7C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010DE84_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E1A0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E3F0_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E6B4_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010E8C0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EA34_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EBCC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010EDFC_mstory5);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C44_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C50_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C5C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C78_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C84_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C90_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114C9C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114CA8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F14C_mstory5);

void func_8010F240_mstory5(s32 index) {
    if (D_801151F0_mstory5[index].unk_0C == 1) {
        D_801151F0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
            case 3:
                HuAudFXStop(D_801151F0_mstory5[index].stopSeNo);
            case 1:
            case 4:
            case 5:
            case 6:
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F2BC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F41C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F4D0_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8010F7D4_mstory5);

void func_8011007C_mstory5(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801100AC_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801114E8_mstory5);

void func_80111818_mstory5(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80114EDC_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111820_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111B60_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111C48_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111DB8_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80111FE8_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112104_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112514_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011275C_mstory5);

void func_80112994_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011299C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80112F38_mstory5);

void func_80113130_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113138_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113470_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113618_mstory5);

void func_8011396C_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113974_mstory5);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113B6C_mstory5);

void func_80113CF8_mstory5(omObjData *obj) {
    func_80107080_mstory5(obj, &D_80115134_mstory5, 20);
    D_801153A0_mstory5[6].func = func_80110200_mstory5;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113D2C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80113E58_mstory5);

void func_80114010_mstory5(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114018_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_80114334_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150E0_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150EC_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_801150F8_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115110_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011511C_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115128_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_80115134_mstory5);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory5/4CF350", D_8011514C_mstory5);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_8011447C_mstory5);

void func_80114560_mstory5(s32 index) {
    if (D_801153A0_mstory5[index].unk_0C == 1) {
        D_801153A0_mstory5[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop(D_801153A0_mstory5[index].stopSeNo);
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory5/4CF350", func_801145DC_mstory5);
