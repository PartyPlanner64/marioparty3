#include "common.h"

typedef struct UnkMstory3Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory3Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_80115260_mstory3;
extern Vec D_8011526C_mstory3;
extern Vec D_80115278_mstory3;
extern s16 D_80115286_mstory3;
extern s32 D_80115288_mstory3;
extern Vec D_801156E0_mstory3;
extern Vec D_80115728_mstory3;
extern s16 D_80115B92_mstory3;
extern u16 D_80115B94_mstory3;
extern s16 D_80115B96_mstory3;
extern s32 D_80115BBC_mstory3;
extern UnkMstory3Obj D_80115BC0_mstory3[6];

void func_80105C1C_mstory3(void);
void func_80105E9C_mstory3(omObjData *);
void func_80106DE0_mstory3(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80107070_mstory3(omObjData *obj, Vec *pos, s32 frames);
s32 func_80107290_mstory3(s16 model);
void func_80107674_mstory3(omObjData *obj, omObjData *target);
void func_80108A94_mstory3(omObjData *);
void func_8010643C_mstory3(void);
void func_80108CA8_mstory3(omObjData *);

void func_801059A0_mstory3(void) {
    func_80105C1C_mstory3();
}

void func_801059BC_mstory3(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory3(void) {
    D_800CE17C_main[0] = D_80115260_mstory3.x;
    D_800CE17C_main[1] = D_80115260_mstory3.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80115260_mstory3, &D_8011526C_mstory3, &D_80115278_mstory3);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105A64_mstory3);

void func_80105B44_mstory3(void) {
    HuWinInit();
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105B60_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105C1C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105D98_mstory3);

void func_80105E8C_mstory3(void) {
    D_80115286_mstory3 = 3;
}

void func_80105E9C_mstory3(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        SLCommonSet(1);
        omOvlReturnEx(1);
    }
}

void func_80105EE4_mstory3(omObjData *obj) {
    WipeCreateOut(2, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    obj->func = func_80105E9C_mstory3;
}

void func_80105F2C_mstory3(omObjData *obj) {
    if (D_800D530C_main == 1) {
        obj->func = func_80105EE4_mstory3;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80105F54_mstory3);

void func_8010603C_mstory3(void) {
    HuWinHomeClear(D_80115B92_mstory3);
    func_80060C14_main(D_80115B92_mstory3, 1);
}

void func_8010606C_mstory3(void) {
    func_80060EA8_main(D_80115B92_mstory3, 1);
}

void func_80106090_mstory3(s32 mess) {
    HuWinMesSet(D_80115B92_mstory3, mess, -1, -1);
    while (HuWinStatGet(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

void func_801060E4_mstory3(s32 mess) {
    HuWinMesSet(D_80115B92_mstory3, mess, -1, -1);
    HuWinInsertMesSet(D_80115B92_mstory3, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(D_80115B92_mstory3) != 0) {
        HuPrcVSleep();
    }
}

s16 func_80106154_mstory3(void) {
    return HuWinChoiceGet(D_80115B92_mstory3, 0, 1);
}

void func_80106184_mstory3(void) {
    espDispOn(D_80115B94_mstory3);
}

void func_801061A4_mstory3(void) {
    espDispOff(D_80115B94_mstory3);
}

void func_801061C4_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 0);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    Hu3DMotionTimeSet(D_80115B96_mstory3, 0.0f);
    Hu3DMotionSpeedSet(D_80115B96_mstory3, 2.0f);
}

void func_80106220_mstory3(void) {
    func_8001C814_main(D_80115B96_mstory3, 4, 4);
    func_8001C814_main(D_80115B96_mstory3, 1, 0);
    Hu3DMotionTimeSet(D_80115B96_mstory3, Hu3DData[D_80115B96_mstory3].motTime);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106284_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106340_mstory3);

void func_80106400_mstory3(s32 arg0) {
    D_80115BBC_mstory3 = arg0;
    D_80115288_mstory3 = 0;
    omAddPrcObj(func_8010643C_mstory3, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010643C_mstory3);

s32 func_80106CDC_mstory3(void) {
    return D_80115288_mstory3;
}

void func_80106CE8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106CF0_mstory3);

void func_80106DC4_mstory3(omObjData *obj, Vec *pos, s32 frames) {
    func_80106DE0_mstory3(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80106DE0_mstory3);

void func_80107014_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DC4_mstory3(obj, &pos, frames);
}

void func_80107040_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DE0_mstory3(obj, &pos, frames, arg3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107070_mstory3);

void func_80107218_mstory3(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80107070_mstory3(obj, &pos, frames);
}

void func_80107244_mstory3(s16 model) {
    HuPrcSleep(10);
    while (!func_80107290_mstory3(model)) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107290_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010733C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801074D8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107674_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_801077BC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107A18_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80107D80_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108084_mstory3);

void func_8010892C_mstory3(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010895C_mstory3);

void func_80108A94_mstory3(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108A9C_mstory3);

void func_80108C34_mstory3(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_80115BC0_mstory3[5].obj = obj;
    D_80115BC0_mstory3[5].unk_08 = 0;
    D_80115BC0_mstory3[5].func = func_80108CA8_mstory3;

    for (;;) {
        D_80115BC0_mstory3[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108CA8_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_80108E28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A23C_mstory3);

void func_8010A7C8_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A7D0_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010A8EC_mstory3);

void func_8010AB34_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AB54_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010ACBC_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010AF28_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B154_mstory3);

void func_8010B634_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B63C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B72C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010B998_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BBB4_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BC34_mstory3);

void func_8010BF40_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010BF48_mstory3);

void func_8010C15C_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C17C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C23C_mstory3);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C3F4_mstory3);

void func_8010C490_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C4B0_mstory3);

void func_8010C654_mstory3(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C65C_mstory3);

void func_8010C7A0_mstory3(omObjData *obj) {
    func_80107674_mstory3(obj, D_80115BC0_mstory3[1].obj);
}

void func_8010C7C0_mstory3(omObjData *obj) {
    Vec pos = D_801156E0_mstory3;

    func_80107070_mstory3(obj, &pos, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

void func_8010C810_mstory3(void) {
    Vec pos = D_80115728_mstory3;

    func_80107070_mstory3(D_80115BC0_mstory3[2].obj, &pos, 10);
    D_80115BC0_mstory3[3].func = func_80108A94_mstory3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory3/4B29E0", func_8010C870_mstory3);

void func_8010C9E0_mstory3(void) {
}
