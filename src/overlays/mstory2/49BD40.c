#include "common.h"

typedef struct UnkMstory2Obj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} UnkMstory2Obj; // sizeof 0x14

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_8011B920_mstory2;
extern Vec D_8011B92C_mstory2;
extern Vec D_8011B938_mstory2;

extern s16 D_8011B946_mstory2;
extern s32 D_8011B94C_mstory2;
extern const Vec D_8011C000_mstory2;
extern const Vec D_8011C1E0_mstory2;
extern const Vec D_8011C228_mstory2;
extern const Vec D_8011C3CC_mstory2;
extern const Vec D_8011C414_mstory2;
extern const Vec D_8011C5B8_mstory2;
extern const Vec D_8011C600_mstory2;
extern s16 D_8011C644_mstory2;
extern u16 D_8011C646_mstory2;
extern s16 D_8011C648_mstory2;
extern s32 D_8011C674_mstory2;
extern UnkMstory2Obj D_8011C680_mstory2[6];
extern UnkMstory2Obj D_8011C760_mstory2[6];
extern UnkMstory2Obj D_8011C840_mstory2[6];
extern UnkMstory2Obj D_8011C920_mstory2[6];
extern UnkMstory2Obj D_8011CA38_mstory2;

void func_80105C1C_mstory2(void);
void func_80105EC4_mstory2(omObjData *);
void func_80105F4C_mstory2(omObjData *);
void func_80106E48_mstory2(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801070D8_mstory2(omObjData *obj, Vec *pos, s32 frames);
s32 func_801072F8_mstory2(s16 model);
void func_801076DC_mstory2(omObjData *obj, omObjData *target);
void func_8010889C_mstory2(omObjData *);
void func_8010D21C_mstory2(omObjData *);
void func_80111EAC_mstory2(omObjData *);
void func_80116B6C_mstory2(omObjData *);
void func_801064AC_mstory2(void);
void func_8011AC08_mstory2(void);
void func_8011AC10_mstory2(omObjData *);
void func_80108AB0_mstory2(omObjData *);
void func_801120C0_mstory2(omObjData *);
void func_80116D80_mstory2(omObjData *);

void func_801059A0_mstory2(void) {
    func_80105C1C_mstory2();
}

void func_801059BC_mstory2(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void func_801059E4_mstory2(void) {
    D_800CE17C_main[0] = D_8011B920_mstory2.x;
    D_800CE17C_main[1] = D_8011B920_mstory2.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_8011B920_mstory2, &D_8011B92C_mstory2, &D_8011B938_mstory2);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105A64_mstory2);

void func_80105B44_mstory2(void) {
    HuWinInit();
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105B60_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105C1C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BDF4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105DB4_mstory2);

void func_80105EA4_mstory2(void) {
    D_8011B946_mstory2 = 3;
}

void func_80105EB4_mstory2(void) {
    D_8011B946_mstory2 = 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105EC4_mstory2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80105FBC_mstory2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801062F4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801063B0_mstory2);

void func_80106470_mstory2(s32 arg0) {
    D_8011C674_mstory2 = arg0;
    D_8011B94C_mstory2 = 0;
    omAddPrcObj(func_801064AC_mstory2, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801064AC_mstory2);

s32 func_80106D44_mstory2(void) {
    return D_8011B94C_mstory2;
}

void func_80106D50_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80106D58_mstory2);

void func_80106E2C_mstory2(omObjData *obj, Vec *pos, s32 frames) {
    func_80106E48_mstory2(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80106E48_mstory2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801070D8_mstory2);

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

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801072F8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801073A4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107540_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801076DC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107824_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107B90_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80107E94_mstory2);

void func_8010873C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010876C_mstory2);

void func_8010889C_mstory2(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801088A4_mstory2);

void func_80108A3C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C680_mstory2[5].obj = obj;
    D_8011C680_mstory2[5].unk_08 = 0;
    D_8011C680_mstory2[5].func = func_80108AB0_mstory2;

    for (;;) {
        D_8011C680_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80108AB0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80108C40_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80109D04_mstory2);

void func_8010A290_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE1C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE24_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE2C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE48_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE74_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE80_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE8C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BE98_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BEB0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BEE0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF28_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF88_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BF94_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFAC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFB8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFC4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFD0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFDC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010A298_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010A3B4_mstory2);

void func_8010A5FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010A61C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010A784_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010A9F0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010AC1C_mstory2);

void func_8010B108_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B110_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B200_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B46C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B688_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B738_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011BFF4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C000_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C00C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010B7B8_mstory2);

void func_8010BAC4_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010BACC_mstory2);

void func_8010BCE4_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010BD04_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010BDC4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010BF7C_mstory2);

void func_8010C018_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C038_mstory2);

void func_8010C1DC_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C1E4_mstory2);

void func_8010C328_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C680_mstory2[1].obj);
}

void func_8010C348_mstory2(omObjData *obj) {
    Vec pos = D_8011C000_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C680_mstory2[3].func = func_8010889C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C398_mstory2);

void func_8010C508_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C510_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010C814_mstory2);

void func_8010D0BC_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D0EC_mstory2);

void func_8010D21C_mstory2(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D224_mstory2);

void func_8010D430_mstory2(omObjData *);

void func_8010D3BC_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C760_mstory2[5].obj = obj;
    D_8011C760_mstory2[5].unk_08 = 0;
    D_8011C760_mstory2[5].func = func_8010D430_mstory2;

    for (;;) {
        D_8011C760_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D430_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010D5C0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010E9E0_mstory2);

void func_8010EF6C_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C024_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C030_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C03C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C054_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C060_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C06C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C078_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C090_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C0C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C108_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C168_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C174_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C180_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C18C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C198_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1A4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1B0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1BC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010EF74_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F090_mstory2);

void func_8010F2D8_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F2F8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F460_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F6CC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010F8F8_mstory2);

void func_8010FDE4_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010FDEC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8010FEDC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110148_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110364_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1D4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C1EC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801103E4_mstory2);

void func_801106F0_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801106F8_mstory2);

void func_80110910_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110930_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801109F0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110BA8_mstory2);

void func_80110C44_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110C64_mstory2);

void func_80110E08_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80110E10_mstory2);

void func_80110F54_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C760_mstory2[1].obj);
}

void func_80110F74_mstory2(omObjData *obj) {
    Vec pos = D_8011C1E0_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C760_mstory2[3].func = func_8010D21C_mstory2;
}

void func_80110FC4_mstory2(void) {
    Vec pos = D_8011C228_mstory2;

    func_801070D8_mstory2(D_8011C760_mstory2[2].obj, &pos, 10);
    D_8011C760_mstory2[3].func = func_8010D21C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111024_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111194_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801111A0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801114A4_mstory2);

void func_80111D4C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111D7C_mstory2);

void func_80111EAC_mstory2(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80111EB4_mstory2);

void func_8011204C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C840_mstory2[5].obj = obj;
    D_8011C840_mstory2[5].unk_08 = 0;
    D_8011C840_mstory2[5].func = func_801120C0_mstory2;

    for (;;) {
        D_8011C840_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801120C0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80112250_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113670_mstory2);

void func_80113BFC_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C204_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C210_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C21C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C228_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C240_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C24C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C258_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C264_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C27C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C2F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C354_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C360_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C36C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C378_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C384_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C390_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C39C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3A8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113C04_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113D20_mstory2);

void func_80113F68_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80113F88_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801140F0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011435C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114588_mstory2);

void func_80114A9C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114AA4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114B94_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80114E00_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011501C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3C0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3CC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3D8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011509C_mstory2);

void func_801153A8_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801153B0_mstory2);

void func_801155C8_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801155E8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801156A8_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115860_mstory2);

void func_801158FC_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011591C_mstory2);

void func_80115AC0_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115AC8_mstory2);

void func_80115C0C_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C840_mstory2[1].obj);
}

void func_80115C2C_mstory2(omObjData *obj) {
    Vec pos = D_8011C3CC_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C840_mstory2[3].func = func_80111EAC_mstory2;
}

void func_80115C7C_mstory2(void) {
    Vec pos = D_8011C414_mstory2;

    func_801070D8_mstory2(D_8011C840_mstory2[2].obj, &pos, 10);
    D_8011C840_mstory2[3].func = func_80111EAC_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115CDC_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115E4C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80115E60_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116164_mstory2);

void func_80116A0C_mstory2(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116A3C_mstory2);

void func_80116B6C_mstory2(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116B74_mstory2);

void func_80116D0C_mstory2(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_8011C920_mstory2[5].obj = obj;
    D_8011C920_mstory2[5].unk_08 = 0;
    D_8011C920_mstory2[5].func = func_80116D80_mstory2;

    for (;;) {
        D_8011C920_mstory2[5].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116D80_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80116F0C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011831C_mstory2);

void func_801188A8_mstory2(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3F0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C3FC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C408_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C414_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C42C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C438_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C444_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C450_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C468_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C498_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C4E0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C540_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C54C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C558_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C564_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C570_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C57C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C588_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C594_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801188B0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_801189CC_mstory2);

void func_80118C14_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80118C34_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80118D9C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119008_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119234_mstory2);

void func_80119720_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119728_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119818_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119A84_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119CA0_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5AC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5B8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5C4_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_80119D20_mstory2);

void func_8011A02C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A034_mstory2);

void func_8011A24C_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A26C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A32C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A4E4_mstory2);

void func_8011A580_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[0].obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A5A0_mstory2);

void func_8011A744_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A74C_mstory2);

void func_8011A890_mstory2(omObjData *obj) {
    func_801076DC_mstory2(obj, D_8011C920_mstory2[1].obj);
}

void func_8011A8B0_mstory2(omObjData *obj) {
    Vec pos = D_8011C5B8_mstory2;

    func_801070D8_mstory2(obj, &pos, 10);
    D_8011C920_mstory2[3].func = func_80116B6C_mstory2;
}

void func_8011A900_mstory2(void) {
    Vec pos = D_8011C600_mstory2;

    func_801070D8_mstory2(D_8011C920_mstory2[2].obj, &pos, 10);
    D_8011C920_mstory2[3].func = func_80116B6C_mstory2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011A960_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AAD0_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AAE0_mstory2);

void func_8011AB7C_mstory2(void) {
}

void func_8011AB84_mstory2(void) {
    omObjData *obj;

    obj = omAddObj(0x14, 0, 0, -1, NULL);
    D_8011CA38_mstory2.obj = obj;
    D_8011CA38_mstory2.unk_08 = 0;
    D_8011CA38_mstory2.func = func_8011AC10_mstory2;
    omPrcSetDestructor(0, func_8011AC08_mstory2);
    while (1) {
        D_8011CA38_mstory2.func(obj);
        HuPrcVSleep();
    }
}

void func_8011AC08_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AC10_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011AD8C_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B080_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5DC_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5E8_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C5F4_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C600_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C60C_mstory2);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory2/49BD40", D_8011C618_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B198_mstory2);

void func_8011B45C_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B464_mstory2);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B64C_mstory2);

void func_8011B818_mstory2(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory2/49BD40", func_8011B820_mstory2);
