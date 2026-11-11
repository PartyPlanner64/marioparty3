#include "common.h"
#include "game/hmfmath.h"

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

extern Vec D_80114778_mstory5[];
extern Vec D_801147A8_mstory5[];
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
extern const Vec D_80114948_mstory5;
extern Vec D_80114A88_mstory5;
extern Vec D_80114C44_mstory5;
extern const Vec D_80114C84_mstory5;
extern const Vec D_80114C90_mstory5;
extern Vec D_80114A0C_mstory5;
extern Vec D_80114A18_mstory5;
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
extern UnkStoryObj D_801151F0_mstory5[9];
extern UnkStoryObj D_801152C8_mstory5;
extern UnkStoryObj D_801152E0_mstory5;
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
extern Vec D_8011531C_mstory5;
extern const Vec D_80114924_mstory5;
extern const Vec D_80114C9C_mstory5;
extern const Vec D_80114CA8_mstory5;
extern Vec D_80115358_mstory5;
extern const Vec D_80114960_mstory5;
extern const s32 D_80114C78_mstory5[];
extern s16 D_80115366_mstory5;
extern Vec D_801147F0_mstory5[];
extern Vec D_80115310_mstory5;
extern const Vec D_80114918_mstory5;
extern Vec D_80115334_mstory5;
extern const Vec D_8011493C_mstory5;
extern Vec D_80114AB8_mstory5;
extern Vec D_80114AD0_mstory5;
extern Vec D_80114ADC_mstory5;
extern Vec D_80114AE8_mstory5;
extern Vec D_80114AF4_mstory5;
extern Vec D_80114B00_mstory5;
extern Vec D_80114B0C_mstory5;
extern Vec D_80114B18_mstory5;
extern Vec D_80114B24_mstory5;
extern s16 D_80115376_mstory5;
extern Vec D_80114AA0_mstory5;
extern Vec D_80114B54_mstory5;
extern Vec D_80114B60_mstory5;
extern Vec D_80114B9C_mstory5;
extern Vec D_80114BA8_mstory5;
extern Vec D_80114BB4_mstory5;
extern Vec D_80114BCC_mstory5;
extern Vec D_80114BD8_mstory5;
extern Vec D_80114BE4_mstory5;
extern Vec D_80114BF0_mstory5;
extern s16 D_8011537E_mstory5;
extern s32 D_800A178C_main[][6];
extern Vec D_801152F8_mstory5;
extern Vec D_8011534C_mstory5;
extern const Vec D_80114954_mstory5;
extern const Vec D_80114900_mstory5;
extern const s32 D_8011496C_mstory5[];
extern const s32 D_8011498C_mstory5[];
extern const s32 D_801149AC_mstory5[];
extern const s32 D_801149CC_mstory5[];
extern const s32 D_801149EC_mstory5[];

void func_80106028_mstory5(void);
void func_801068D4_mstory5(void);
void func_80106B64_mstory5(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106DB4_mstory5(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_80107080_mstory5(omObjData *obj, const Vec *pos, s32 frames);
void func_80107228_mstory5(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void func_80107254_mstory5(s16 model);
s32 func_801072A0_mstory5(s16 model);
void func_801085D8_mstory5(omObjData *obj);
void func_80108A20_mstory5(void);
void func_8010D47C_mstory5(void);
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
MstoryPath *func_80107850_mstory5(Vec *points, s32 flags);
void func_80107B54_mstory5(MstoryPath *path, f32 time, Vec *result);
void func_80105BDC_mstory5(omObjData *obj);
void func_80105CCC_mstory5(omObjData *obj);
void func_80105E34_mstory5(void);
void func_80105F5C_mstory5(omObjData *obj);
void func_8010DE7C_mstory5(void);
void func_8010AE0C_mstory5(void);
void func_8010AE14_mstory5(omObjData *obj);
void func_801085E0_mstory5(void);
void func_801097B8_mstory5(void);
void func_8010B318_mstory5(void);
void func_80108A28_mstory5(omObjData *obj);
void func_80109790_mstory5(omObjData *obj);
void func_80109E70_mstory5(omObjData *obj);
void func_80109F48_mstory5(omObjData *obj);
void func_8010A0A8_mstory5(omObjData *obj);
void func_8010B320_mstory5(omObjData *obj);
void func_8010B5DC_mstory5(omObjData *obj);
void func_8010B9D4_mstory5(omObjData *obj);
void func_8010C6A4_mstory5(omObjData *obj);
void func_8010CA04_mstory5(omObjData *obj);
void func_8010E538_mstory5(omObjData *obj);
void func_8010EA34_mstory5(omObjData *obj);
void func_8010D484_mstory5(omObjData *arg0);
void func_8010D560_mstory5(omObjData *obj);
void func_8010DE84_mstory5(omObjData *obj);
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
void func_8010E1A0_mstory5(omObjData *obj);
void func_8010E6B4_mstory5(omObjData *obj);
void func_8010E870_mstory5(omObjData *obj);
void func_8010ABC4_mstory5(omObjData *obj);
void func_8010EBCC_mstory5(omObjData *obj);
void func_8010EDFC_mstory5(omObjData *obj);
void func_8010F02C_mstory5(omObjData *obj);
void func_8010F0B8_mstory5(omObjData *obj);
void func_8010D214_mstory5(void);
void func_8010D594_mstory5(omObjData *obj);
void func_8010E648_mstory5(omObjData *obj);
void func_8010B6F8_mstory5(omObjData *obj);
void func_8010D7D8_mstory5(omObjData *obj);
void func_8010C69C_mstory5(void);

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

void func_80107B54_mstory5(MstoryPath *path, f32 time, Vec *result) {
    f32 values[4];
    f32 times[4];
    Vec *points;
    f32(*interval)[2];
    s16 i;

    if (time >= 1.0f) {
        result->x = path->points[path->count - 1].x;
        result->y = path->points[path->count - 1].y;
        result->z = path->points[path->count - 1].z;
        return;
    }
    interval = path->intervals;
    for (i = 0; i < path->count; i++, interval++) {
        if (time <= (*interval)[0]) {
            break;
        }
    }
    i--;
    if (i < 0) {
        i = 0;
    }
    if (i >= path->count - 1) {
        i--;
    }
    interval = path->intervals;
    if (path->flags & 1) {
        times[0] = i == 0 ? -(1.0f - interval[path->count - 1][0]) : interval[i - 1][0];
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[path->count - 1].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[0].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[0].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[0].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = interval[i - 1][0];
        }
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[0].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    }
}

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

void func_801085E0_mstory5(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 16, -1, NULL);
    D_801151F0_mstory5[0].obj = obj;
    D_801151F0_mstory5[0].unk_08 = 0;
    D_801151F0_mstory5[0].unk_0C = 0;
    chr = GwStory.unk1;
    obj->model[1] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    if (GwStory.unk1 == 5) {
        Hu3DModelScaleSet(obj->model[2], 1.5f, 1.0f, 1.5f);
    }
    obj->model[3] = func_8000B108_main(0x1D000A, 0x2B9);
    func_8001C258_main(obj->model[3], 4, 4);
    obj->model[4] = Hu3DModelLink(D_80115368_mstory5);
    func_8001C258_main(obj->model[4], 4, 4);
    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x9C));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 1));
    func_8000B460_main(obj, 4, func_80017BB8_main(chr, 0x21));
    func_8000B460_main(obj, 5, D_8011496C_mstory5[chr]);
    func_8000B460_main(obj, 6, D_8011498C_mstory5[chr]);
    func_8000B460_main(obj, 7, D_801149AC_mstory5[chr]);
    func_8000B460_main(obj, 8, func_80017BB8_main(chr, 0x33));
    func_8000B460_main(obj, 9, D_801149CC_mstory5[chr]);
    func_8000B460_main(obj, 10, D_801149EC_mstory5[chr]);
    func_8000B460_main(obj, 11, func_80017BB8_main(chr, 0x72));
    func_8000B460_main(obj, 12, func_80017BB8_main(chr, 0x9B));
    D_80115382_mstory5[0] = func_80017790_main(obj->model[1], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80115382_mstory5[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80115382_mstory5[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80115382_mstory5[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA9));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, GwStory.unk1, D_80115382_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[0]);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 120.0f, 0.0f);
    D_801152F8_mstory5 = D_80114900_mstory5;
    Hu3DModelPosSet(obj->model[1], D_801152F8_mstory5.x, D_801152F8_mstory5.y, D_801152F8_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_801152F8_mstory5.x, -5.0f, D_801152F8_mstory5.z);
    Hu3DModelPosSet(obj->model[4], D_801152F8_mstory5.x, D_801152F8_mstory5.y, D_801152F8_mstory5.z);
    omPrcSetDestructor(0, func_80108A20_mstory5);
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[0].func(obj);
        HuPrcVSleep();
    }
}

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

const Vec D_80114A24_mstory5 = { -100.0f, 0.0f, 350.0f };
const Vec D_80114A30_mstory5 = { -100.0f, 0.0f, 150.0f };
const Vec D_80114A3C_mstory5 = { 0.0f, 20.0f, 0.0f };
const Vec D_80114A48_mstory5 = { 0.0f, 0.0f, 0.0f };
const Vec D_80114A54_mstory5 = { 0.0f, -26.565f, 0.0f };
const Vec D_80114A60_mstory5 = { 0.0f, 45.0f, 0.0f };

const char D_80114A6C_mstory5[] = "item_hook";

void func_80108A28_mstory5(omObjData *obj) {
    omObjData *obj0;
    omObjData *obj7;
    omObjData *obj1;
    s16 model;
    HmfMotionNode *node;
    s32 fx;
    s32 i;
    f32 scale;
    f32 time;
    Vec pos;

    HuPrcSleep(20);
    // obj0 is unused, but reading it first makes D_801151F0_mstory5 itself
    // the shared base address for the following holder accesses.
    obj0 = D_801151F0_mstory5[0].obj;
    obj7 = D_801151F0_mstory5[7].obj;
    obj1 = D_801151F0_mstory5[1].obj;
    (void)obj0;
    model = obj->model[1];
    HuPrcSleep(50);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[1]].motId, 0, 10, 2);
    func_80107228_mstory5(obj, 0.0f, 110.0f, 0.0f, 10);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[6]].motId, 0, 10, 0);
    HuPrcSleep(10);
    func_8001C258_main(obj->model[3], 0x4000, 0x4000);
    Hu3DModelHookSet(obj->model[3], model, D_80114A6C_mstory5);
    func_8001C258_main(obj->model[3], 4, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[5]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    while (!(D_801151F0_mstory5[8].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_8001C258_main(D_801151F0_mstory5[8].obj->model[1], 4, 4);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x45);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x46);
    func_8002FD8C_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x47);
    node = func_8001D33C_main(model, D_80114A6C_mstory5);
    for (i = 0; i < 10; i++) {
        scale = sindf(i * 18.0f) * 0.8 + 1.0;
        node->baseScale.x = scale;
        node->baseScale.y = scale;
        node->baseScale.z = scale;
        node->scale.x = scale;
        node->scale.y = scale;
        node->scale.z = scale;
        HuPrcVSleep();
    }
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x47);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x46);
    func_8002FDCC_main(model, Hu3DData[model].motId, D_80114A6C_mstory5, 0x1B, 0x45);
    func_80105FEC_mstory5(4);
    while (func_801068C8_mstory5() == 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4B : 0x5B3F);
    func_80106A50_mstory5();
    func_8001C5B4_main(model, obj->motion[5]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionSpeedSet(model, 2.0f);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    func_8001C5B4_main(model, obj->motion[6]);
    func_8001C814_main(model, 4, 4);
    Hu3DMotionTimeSet(model, D_800CCF58_main[Hu3DData[model].motId].unk02);
    do {
        time = Hu3DData[model].motTime;
        HuPrcVSleep();
    } while (time > 0.0f);
    Hu3DMotionSpeedSet(model, 1.0f);
    func_8001C258_main(obj->model[3], 0x4000, 0);
    func_8001C258_main(obj->model[3], 4, 4);
    HuAudSeqFadeOut(20);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 0);
    func_80107080_mstory5(obj, &D_80114A0C_mstory5, 10);
    HuAudSeqPlay(0x72);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[2]);
    func_80107254_mstory5(model);
    fx = CharFXPlay(0x262, GwStory.unk1);
    HuPrcSleep(30);
    func_80107080_mstory5(obj7, &D_80114A54_mstory5, 3);
    func_80106B48_mstory5(obj7, &D_80114A24_mstory5, 5);
    func_80107080_mstory5(obj7, &D_80114A3C_mstory5, 3);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuAudFXPlay(0x219);
    HuAudFXStop(fx);
    func_8001C258_main(obj->model[4], 4, 0);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[4]].motId, 0, 10, 0);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[3]);
    func_80107080_mstory5(obj7, &D_80114A48_mstory5, 3);
    func_80106B64_mstory5(obj7, &D_80114A30_mstory5, 10, 0);
    func_80107254_mstory5(model);
    func_80107080_mstory5(obj, &D_80114A18_mstory5, 10);
    HuAudSeqPlay(0x26);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_80017954_main(model, 2, GwStory.unk1, D_80115382_mstory5[0]);
    HuAudFXPlay(0x159);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4C : 0x5B40);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[8]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801151F0_mstory5[3].func = func_8010B320_mstory5;
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 0.0f, 158.46f, 0.0f, 5);
    D_801151F0_mstory5[1].func = func_8010EA34_mstory5;
    D_801151F0_mstory5[7].func = func_8010E538_mstory5;
    D_801152E0_mstory5.func = func_80109790_mstory5;
    func_80106FF4_mstory5(obj1, 238.0f, 100.0f, 214.0f, 10, 0);
    while (!(D_801151F0_mstory5[3].unk_08 & 8)) {
        HuPrcVSleep();
    }
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4D : 0x5B41);
    func_80106A50_mstory5();
    D_801151F0_mstory5[3].unk_08 |= 1;
    while (!(D_801151F0_mstory5[3].unk_08 & 4)) {
        HuPrcVSleep();
    }
    D_801152C8_mstory5.func = func_8010A0A8_mstory5;
    while (!(D_801151F0_mstory5[1].unk_08 & 1)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[4].func = func_8010B9D4_mstory5;
    while (!(D_801151F0_mstory5[4].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801152E0_mstory5.func = func_8010D484_mstory5;
    D_801151F0_mstory5[1].func = func_80109E70_mstory5;
    D_801151F0_mstory5[3].func = func_8010B5DC_mstory5;
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[3]].motId, 0, 10, 2);
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    func_8010F14C_mstory5(0, 0x1F);
    func_80107228_mstory5(obj, 0.0f, 90.0f, 0.0f, 20);
    func_80106FC8_mstory5(obj, pos.x + 1000.0f, pos.y, pos.z, 30);
    func_8010F240_mstory5(0);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    D_801151F0_mstory5[5].func = func_8010C6A4_mstory5;
    D_801151F0_mstory5[6].func = func_8010CA04_mstory5;
    HuPrcSleep(30);
    HuPrcSleep(40);
    HuAudFXPlay(0x2A0);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A57 : 0x5B4B);
    func_80106A50_mstory5();
    HuPrcSleep(30);
    D_801151F0_mstory5[0].unk_08 |= 1;
    HuPrcSleep(50);
    func_80105FDC_mstory5();
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
}

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

void func_80109790_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(D_801151F0_mstory5[0].obj, D_801151F0_mstory5[3].obj);
}

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

const Vec D_80114AAC_mstory5 = { 10.0f, 378.9f, 0.0f };

void func_80109B30_mstory5(omObjData *obj) {
    HuPrcSleep(40);
    HuPrcSleep(20);
    D_801151F0_mstory5[0].func = func_80109698_mstory5;
    D_801151F0_mstory5[7].func = func_8010D560_mstory5;
    func_80107080_mstory5(obj, &D_80114AAC_mstory5, 30);
    func_80106B48_mstory5(obj, &D_80114B0C_mstory5, 20);
    HuPrcSleep(30);
    func_80107080_mstory5(obj, &D_80114ADC_mstory5, 10);
    func_80106B48_mstory5(obj, &D_80114B00_mstory5, 15);
    D_801151F0_mstory5[0].func = func_8010975C_mstory5;
    func_80107080_mstory5(obj, &D_80114AB8_mstory5, 10);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115376_mstory5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A49 : 0x5B3D);
    func_80106A50_mstory5();
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_80115372_mstory5);
    func_80107228_mstory5(D_801151F0_mstory5[0].obj, 0.0f, 162.4744f, 0.0f, 10);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114B18_mstory5, 10);
    func_80107080_mstory5(obj, &D_80114AD0_mstory5, 20);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4A : 0x5B3E);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[0]].motId, 0, 10, 2);
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114B24_mstory5, 10);
    D_801151F0_mstory5[8].func = func_8010DE84_mstory5;
    func_80107080_mstory5(obj, &D_80114AA0_mstory5, 20);
    Hu3DMotionShiftSet(D_801151F0_mstory5[0].obj->model[1], Hu3DData[D_801151F0_mstory5[0].obj->motion[12]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[8].unk_08 & 2)) {
        HuPrcVSleep();
    }
    D_801151F0_mstory5[0].func = func_80108A28_mstory5;
    HuPrcSleep(40);
    func_80107080_mstory5(obj, &D_80114AF4_mstory5, 50);
    func_80107080_mstory5(obj, &D_80114AE8_mstory5, 40);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
}

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

void func_8010A0A8_mstory5(omObjData *obj) {
    omObjData *obj1 = D_801151F0_mstory5[1].obj;
    omObjData *obj3 = D_801151F0_mstory5[3].obj;
    omObjData *obj7 = D_801151F0_mstory5[7].obj;
    omObjData *obj0 = D_801151F0_mstory5[0].obj;

    while (!(D_801151F0_mstory5[3].unk_08 & 2)) {
        HuPrcVSleep();
    }
    func_80106B64_mstory5(D_801151F0_mstory5[1].obj, &D_80114BE4_mstory5, 15, 0);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, &D_80114B9C_mstory5, 10);
    func_80106FF4_mstory5(obj7, 0.0f, 200.0f, 150.0f, 15, 0);
    Hu3DMotionShiftSet(D_801151F0_mstory5[0].obj->model[1], Hu3DData[D_801151F0_mstory5[0].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[9]].motId, 0, 30, 0);
    HuPrcSleep(10);
    Hu3DMotionShiftSet(D_801151F0_mstory5[1].obj->model[1], Hu3DData[D_801151F0_mstory5[1].obj->motion[2]].motId, 0, 30, 2);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[9]].motId, 0, 30, 0);
    func_80107254_mstory5(D_801151F0_mstory5[3].obj->model[1]);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[0]].motId, 0, 30, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[1].obj->model[1], Hu3DData[D_801151F0_mstory5[1].obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_80107080_mstory5(D_801151F0_mstory5[3].obj, &D_80114B54_mstory5, 5);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
    D_801151F0_mstory5[0].func = func_801085D8_mstory5;
    func_80107080_mstory5(D_801151F0_mstory5[7].obj, &D_80114BA8_mstory5, 5);
    func_80107080_mstory5(D_801151F0_mstory5[0].obj, &D_80114BB4_mstory5, 5);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4E : 0x5B42);
    func_80106A50_mstory5();
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BE4_mstory5, 10);
    func_80107228_mstory5(D_801151F0_mstory5[7].obj, 15.0f, 20.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[1]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A4F : 0x5B43);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    HuAudFXPlay(0x27C);
    func_80107228_mstory5(obj3, 0.0f, -110.0f, 0.0f, 5);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_8011537E_mstory5);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A50 : 0x5B44);
    func_80106A50_mstory5();
    func_80107228_mstory5(obj7, 0.0f, 0.0f, 0.0f, 5);
    D_801151F0_mstory5[8].func = func_8010E1A0_mstory5;
    HuPrcSleep(50);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[12]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    D_801152E0_mstory5.func = func_801085D8_mstory5;
    func_80107228_mstory5(obj0, 0.0f, 150.0f, 0.0f, 10);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_80115372_mstory5);
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[10]].motId, 0, 10, 2);
    HuPrcSleep(100);
    func_80106B48_mstory5(D_801151F0_mstory5[1].obj, &D_80114BF0_mstory5, 8);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A51 : 0x5B45);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj0->model[1], Hu3DData[obj0->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(D_801151F0_mstory5[3].obj->model[1], Hu3DData[D_801151F0_mstory5[3].obj->motion[1]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_8010E6B4_mstory5;
    D_801151F0_mstory5[7].func = func_8010E870_mstory5;
    HuPrcSleep(70);
    func_801068E4_mstory5(obj1->model[1], D_80115380_mstory5, D_80115376_mstory5);
    Hu3DMotionShiftSet(obj1->model[1], Hu3DData[obj1->motion[1]].motId, 0, 10, 2);
    D_801151F0_mstory5[1].func = func_8010ABC4_mstory5;
    func_80106FF4_mstory5(obj1, 238.0f, 100.0f, 214.0f, 60, 0);
    D_801151F0_mstory5[1].func = func_801085D8_mstory5;
    D_801151F0_mstory5[8].unk_08 |= 0x10;
    while (!(D_801151F0_mstory5[8].unk_08 & 8)) {
        HuPrcVSleep();
    }
    func_80107228_mstory5(obj1, 0.0f, -140.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A52 : 0x5B46);
    func_80106A50_mstory5();
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    HuPrcSleep(20);
    func_8010D214_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[0]].motId, 0, 10, 2);
    D_80114770_mstory5 = 1;
    func_80106B48_mstory5(D_801151F0_mstory5[7].obj, &D_80114BCC_mstory5, 3);
    HuAudFXPlay(0x219);
    CharFXPlay(0x2AB, GwStory.unk1);
    func_8004AC5C_main(0x2B3, 1);
    D_801152E0_mstory5.func = func_8010EBCC_mstory5;
    D_801151F0_mstory5[3].func = func_8010EDFC_mstory5;
    D_80114770_mstory5 = 0;
    func_80106B64_mstory5(D_801151F0_mstory5[7].obj, &D_80114BD8_mstory5, 5, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    HuPrcSleep(12);
    func_80107228_mstory5(D_801151F0_mstory5[1].obj, 0.0f, -135.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A53 : 0x5B47);
    func_80107080_mstory5(D_801151F0_mstory5[1].obj, &D_80114B60_mstory5, 10);
    func_8010CFE4_mstory5();
    HuAudFXPlay(0x21C);
    func_80107228_mstory5(obj7, 20.0f, 10.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[4]].motId, 0, 10, 2);
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A54 : 0x5B48);
    func_80106A50_mstory5();
    CharFXPlay(0x274, GwStory.unk1);
    func_8004AC5C_main(0x27C, 1);
    D_801152E0_mstory5.func = func_8010F02C_mstory5;
    D_801151F0_mstory5[3].func = func_8010F0B8_mstory5;
    HuPrcSleep(10);
    HuPrcSleep(40);
    D_801151F0_mstory5[1].unk_08 |= 1;
    D_801152C8_mstory5.func = func_801085D8_mstory5;
}

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

void func_8010AF44_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(20, 4, 16, -1, NULL);
    D_801151F0_mstory5[3].obj = obj;
    D_801151F0_mstory5[3].unk_08 = 0;
    D_801151F0_mstory5[3].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0x90000, 0x2A9);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    obj->model[3] = Hu3DModelLink(D_80115368_mstory5);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8000B460_main(obj, 0, 0x90004);
    func_8000B460_main(obj, 1, func_80017BB8_main(7, 1));
    func_8000B460_main(obj, 2, func_80017BB8_main(7, 2));
    func_8000B460_main(obj, 3, 0x9000C);
    func_8000B460_main(obj, 4, 0x1D0079);
    func_8000B460_main(obj, 5, 0x1D007B);
    func_8000B460_main(obj, 6, 0x1D007C);
    func_8000B460_main(obj, 7, func_80017BB8_main(7, 0x7A));
    func_8000B460_main(obj, 8, 0x70003);
    func_8000B460_main(obj, 9, 0x1D0078);
    func_8000B460_main(obj, 10, func_80017BB8_main(7, 0x13));
    func_8000B460_main(obj, 11, func_80017BB8_main(7, 0x72));
    func_8000B460_main(obj, 12, func_80017BB8_main(7, 0x32));
    func_8000B460_main(obj, 13, func_80017BB8_main(7, 0x33));
    func_8000B460_main(obj, 14, func_80017BB8_main(7, 0x21));
    D_8011538A_mstory5[0] = func_80017790_main(obj->model[1], 2, 7, func_80017BB8_main(7, 0xA4));
    D_8011538A_mstory5[1] = func_80017AD8_main(func_80017BB8_main(7, 0xAA));
    D_8011538A_mstory5[2] = func_80017AD8_main(func_80017BB8_main(7, 0xA5));
    D_8011538A_mstory5[3] = func_80017AD8_main(func_80017BB8_main(7, 0xA6));
    func_8001C514_main(obj->model[1]);
    func_80017954_main(obj->model[1], 2, 7, D_8011538A_mstory5[0]);
    func_8001C5B4_main(obj->model[1], obj->motion[1]);
    func_8001C814_main(obj->model[1], 2, 2);
    func_8001C258_main(obj->model[1], 4, 4);
    func_8001C258_main(obj->model[2], 4, 4);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 0.0f, 0.0f);
    D_8011531C_mstory5 = D_80114924_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011531C_mstory5.x, D_8011531C_mstory5.y, D_8011531C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011531C_mstory5.x, -5.0f, D_8011531C_mstory5.z);
    omPrcSetDestructor(0, func_8010B318_mstory5);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    while (TRUE) {
        D_801151F0_mstory5[3].func(obj);
        HuPrcVSleep();
    }
}

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
    D_801152E0_mstory5.func = func_8010F41C_mstory5;
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

void func_8010B9D4_mstory5(omObjData *obj) {
    s16 model = obj->model[1];
    omObjData *obj3 = D_801151F0_mstory5[3].obj;
    omObjData *obj7 = D_801151F0_mstory5[7].obj;
    omObjData *obj0 = D_801151F0_mstory5[0].obj;
    omObjData *obj1 = D_801151F0_mstory5[1].obj;
    Vec rot;
    Vec pos;
    Vec vel;
    f32 scale;
    f32 shadowScale;
    f32 t;

    func_8001C258_main(model, HU3D_ATTR_DISPOFF, 0);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, 0);
    func_8010D214_mstory5();
    HuAudSeqPlay(0x21);
    HuAudFXPlay(0x29D);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A55 : 0x5B49);
    func_80106A50_mstory5();
    D_801151F0_mstory5[7].func = func_8010D594_mstory5;
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    HuPrcSleep(40);
    func_80107228_mstory5(obj3, 0.0f, -90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[1]].motId, 0, 10, 2);
    func_8010F14C_mstory5(3, 31);
    func_80106FC8_mstory5(obj3, Hu3DData[obj3->model[1]].pos.x - 50.0f, Hu3DData[obj3->model[1]].pos.y, Hu3DData[obj3->model[1]].pos.z, 10);
    func_8010F240_mstory5(3);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    while (!(D_801151F0_mstory5[7].unk_08 & 1)) {
        HuPrcVSleep();
    }
    func_80106FC8_mstory5(obj, 300.0f, 0.0f, 380.0f, 30);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[2]].motId, 0, 10, 0);
    func_80107254_mstory5(model);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    func_801068E4_mstory5(obj->model[1], D_80115380_mstory5, D_8011537A_mstory5);
    func_80107228_mstory5(obj3, 0.0f, 90.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[7]].motId, 0, 10, 0);
    HuAudFXPlay(0x2B3);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[8]].motId, 0, 10, 0);
    HuPrcSleep(3);
    func_8001C814_main(obj3->model[1], 1, 1);
    HuPrcSleep(10);
    func_8001C814_main(obj3->model[1], 1, 0);
    HuPrcSleep(6);
    HuAudFXPlay(0x21D);
    D_801152C8_mstory5.func = func_8010E648_mstory5;
    D_801151F0_mstory5[3].func = func_8010B6F8_mstory5;
    Hu3DMotionTimeSet(obj0->model[4], 0.0f);
    Hu3DModelPosSet(obj0->model[4], 180.0f, 0.0f, 480.0f);
    func_8001C258_main(obj0->model[4], HU3D_ATTR_DISPOFF, 0);
    D_801151F0_mstory5[1].func = func_80109F48_mstory5;
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    D_801151F0_mstory5[7].func = func_8010D7D8_mstory5;
    pos.x = Hu3DData[model].pos.x;
    pos.y = Hu3DData[model].pos.y;
    pos.z = Hu3DData[model].pos.z;
    rot.x = Hu3DData[model].rot.x;
    rot.y = Hu3DData[model].rot.y;
    rot.z = Hu3DData[model].rot.z;
    scale = 1.0f;
    shadowScale = 3.0f;
    vel.x = -111.666664f;
    vel.y = 66.666664f;
    vel.z = -100.0f;
    t = 0.0f;
    while (TRUE) {
        pos.x += vel.x;
        pos.y += vel.y;
        pos.z += vel.z;
        vel.x *= 0.85f;
        vel.y *= 0.85f;
        vel.z *= 0.85f;
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(obj->model[2], pos.x, 0.0f, pos.z);
        rot.z += 2.25f;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        Hu3DModelScaleSet(model, scale, scale, scale);
        scale = vel.z / -100.0f;
        Hu3DModelScaleSet(obj->model[2], shadowScale, 1.0f, shadowScale);
        shadowScale -= 0.5f;
        if (shadowScale < 0.0f) {
            shadowScale = 0.0f;
        }
        if (t >= 20.0f) {
            break;
        }
        t += 1.0f;
        HuPrcVSleep();
    }
    func_8001C258_main(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[3], Hu3DData[model].pos.x, Hu3DData[model].pos.y, Hu3DData[model].pos.z);
    func_8001C258_main(obj->model[3], HU3D_ATTR_DISPOFF, 0);
    HuAudFXPlay(0x21E);
    while (!(D_801151F0_mstory5[4].unk_08 & 0x10)) {
        HuPrcVSleep();
    }
    HuPrcSleep(35);
    D_801151F0_mstory5[7].unk_08 |= 2;
    HuPrcSleep(50);
    func_80107228_mstory5(obj3, 0.0f, 0.0f, 0.0f, 10);
    func_80017954_main(obj3->model[1], 2, 7, D_8011538A_mstory5[2]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[4]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    HuAudFXPlay(0x27C);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[5]].motId, 0, 10, 2);
    HuPrcSleep(20);
    func_80107228_mstory5(obj3, 0.0f, -90.0f, 0.0f, 20);
    HuPrcSleep(10);
    func_80107228_mstory5(obj1, 0.0f, -30.0f, 0.0f, 10);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A58 : 0x5B4C);
    func_80106A50_mstory5();
    func_80107228_mstory5(obj1, 0.0f, 0.0f, 0.0f, 10);
    HuPrcSleep(60);
    func_80107228_mstory5(obj7, 0.0f, 20.0f, 0.0f, 10);
    Hu3DMotionShiftSet(D_801151F0_mstory5[7].obj->model[1], Hu3DData[D_801151F0_mstory5[7].obj->motion[2]].motId, 0, 10, 2);
    func_80106A20_mstory5();
    func_80106A74_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A59 : 0x5B4D);
    func_80106A50_mstory5();
    Hu3DMotionShiftSet(obj7->model[1], Hu3DData[obj7->motion[5]].motId, 0, 10, 2);
    func_80017954_main(obj3->model[1], 2, 7, D_8011538A_mstory5[0]);
    func_80107228_mstory5(obj3, 0.0f, 0.0f, 0.0f, 10);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[13]].motId, 0, 10, 0);
    func_80107254_mstory5(obj3->model[1]);
    Hu3DMotionShiftSet(obj3->model[1], Hu3DData[obj3->motion[0]].motId, 0, 10, 2);
    func_80107228_mstory5(obj3, 0.0f, 90.0f, 0.0f, 10);
    D_801151F0_mstory5[4].unk_08 |= 2;
    D_801151F0_mstory5[4].func = func_801085D8_mstory5;
}

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

const char D_80114C14_mstory5[] = "c208nk0-r_eye";
const char D_80114C24_mstory5[] = "r_eye";
const char D_80114C2C_mstory5[] = "l_eye";
const char D_80114C34_mstory5[] = "c208nk1-r_eye";

void func_8010CBE8_mstory5(void) {
    omObjData *obj;

    obj = omAddObj(20, 10, 8, -1, NULL);
    D_801151F0_mstory5[7].obj = obj;
    D_801151F0_mstory5[7].unk_08 = 0;
    D_801151F0_mstory5[7].unk_0C = 0;
    obj->model[1] = func_8000B108_main(0xA0122, 0x2A9);
    Hu3DModelScaleSet(obj->model[1], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[1]);
    func_8000B460_main(obj, 0, 0xA0123);
    func_8000B460_main(obj, 1, 0xA0125);
    func_8000B460_main(obj, 2, 0xA012E);
    func_8000B460_main(obj, 3, 0xA0127);
    func_8000B460_main(obj, 4, 0xA0126);
    func_8000B460_main(obj, 5, 0xA012A);
    obj->model[2] = Hu3DModelLink(D_80115364_mstory5);
    Hu3DModelScaleSet(obj->model[2], 2.0f, 1.0f, 2.0f);
    obj->model[3] = func_8000B108_main(0x1D002E, 0x6B9);
    obj->model[4] = func_8000B108_main(0x1D002E, 0x6B9);
    func_8001C258_main(obj->model[3], 4, 4);
    func_8001C258_main(obj->model[4], 4, 4);
    obj->model[5] = func_8000B108_main(0xA0122, 0x2A9);
    func_8001C258_main(obj->model[5], 4, 4);
    Hu3DModelScaleSet(obj->model[5], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[5]);
    func_80017358_main(obj->model[3], D_80114C14_mstory5, obj->model[5], D_80114C24_mstory5);
    func_80017358_main(obj->model[4], D_80114C14_mstory5, obj->model[5], D_80114C2C_mstory5);
    obj->model[6] = func_8000B108_main(0x1D002F, 0x6B9);
    obj->model[7] = func_8000B108_main(0x1D002F, 0x6B9);
    func_8001C258_main(obj->model[6], 4, 4);
    func_8001C258_main(obj->model[7], 4, 4);
    obj->model[8] = func_8000B108_main(0xA0122, 0x2A9);
    func_8001C258_main(obj->model[8], 4, 4);
    Hu3DModelScaleSet(obj->model[8], 2.0f, 2.0f, 2.0f);
    func_800461B4_main(obj->model[8]);
    func_80017358_main(obj->model[6], D_80114C34_mstory5, obj->model[8], D_80114C24_mstory5);
    func_80017358_main(obj->model[7], D_80114C34_mstory5, obj->model[8], D_80114C2C_mstory5);
    func_8001C814_main(obj->model[1], 2, 2);
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(obj->model[1], 0.0f, 30.0f, 0.0f);
    D_8011534C_mstory5 = D_80114954_mstory5;
    Hu3DModelPosSet(obj->model[1], D_8011534C_mstory5.x, D_8011534C_mstory5.y, D_8011534C_mstory5.z);
    Hu3DModelPosSet(obj->model[2], D_8011534C_mstory5.x, -5.0f, D_8011534C_mstory5.z);
    omPrcSetDestructor(0, func_8010D47C_mstory5);
    D_801151F0_mstory5[7].func = func_801085D8_mstory5;
    D_80114774_mstory5 = 1;
    while (TRUE) {
        D_801151F0_mstory5[7].func(obj);
        HuPrcVSleep();
    }
}

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

void func_8010D484_mstory5(omObjData *arg0) {
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
    D_801152E0_mstory5.func = func_801085D8_mstory5;
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

    D_801152C8_mstory5.obj = obj;
    D_801152C8_mstory5.unk_08 = 0;
    D_801152C8_mstory5.unk_0C = 0;
    D_801152C8_mstory5.func = func_801085D8_mstory5;

    for (;;) {
        D_801152C8_mstory5.func(obj);
        HuPrcVSleep();
    }
}

void func_8010E5D0_mstory5(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801152E0_mstory5.obj = obj;
    D_801152E0_mstory5.unk_08 = 0;
    D_801152E0_mstory5.unk_0C = 0;
    D_801152E0_mstory5.func = func_801085D8_mstory5;

    for (;;) {
        D_801152E0_mstory5.func(obj);
        HuPrcVSleep();
    }
}

void func_8010E648_mstory5(omObjData *obj) {
    func_80106A20_mstory5();
    func_80106AC8_mstory5(func_80106B30_mstory5(0) == 0 ? 0x5A56 : 0x5B4A);
    func_80106AF4_mstory5();
    func_80106A50_mstory5();
    D_801151F0_mstory5[4].unk_08 |= 0x10;
    D_801152C8_mstory5.func = func_801085D8_mstory5;
}

void func_8010E6B4_mstory5(omObjData *obj) {
    func_8010E3F0_mstory5(obj, D_801151F0_mstory5[0].obj);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 30, 2);
    func_8010F14C_mstory5(3, 31);
    func_8010734C_mstory5(obj, 4.5f, 15);
    func_8010F240_mstory5(3);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[0]].motId, 0, 30, 2);
    D_801151F0_mstory5[3].func = func_801085D8_mstory5;
    D_801152E0_mstory5.func = func_8010E8C0_mstory5;
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
    D_801152E0_mstory5.func = func_801085D8_mstory5;
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
    D_801152E0_mstory5.func = func_801085D8_mstory5;
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
    D_801152E0_mstory5.func = func_801085D8_mstory5;
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
    D_801152E0_mstory5.func = func_801085D8_mstory5;
}
