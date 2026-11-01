#include "common.h"
#include "game/printfunc.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"

// Per-player work for each of the four quads, allocated in func_80107584_mpiq
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ u32 flags;
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 index;
    /* 0x1C */ f32 scale;
    /* 0x20 */ s32 counter;
    /* 0x23 */ u8 unk_23;
    /* 0x24 */ s16 unk_24;
} MpiqObjWork; // Size 0x28

typedef struct {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 rotY;
    /* 0x0C */ s32 flags;
} MpiqDanceObjData; // Size 0x10

// Work for the marker object created in func_80107F28_mpiq
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 timer;
} MpiqMarkerObjWork; // Size 0x8

extern s32 D_8010CA90_mpiq[];
extern s32 D_8010CAA0_mpiq[];
extern omObjData *D_8010CA78_mpiq;
extern omObjData *D_8010CAC0_mpiq[];
extern MpiqObjWork *D_8010CA80_mpiq[];
extern omObjData *D_8010CAD0_mpiq;
extern omObjData *D_8010CAD4_mpiq;
extern s32 fontcolor;
extern s32 D_8010C9D8_mpiq;

void func_80107DE0_mpiq(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801059A0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105C60_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105D60_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105DA4_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105DC0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105DDC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105DF8_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80105E14_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010651C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80106658_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80106664_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801069F8_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80106B5C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80106E98_mpiq);

void func_80107168_mpiq(omObjData *obj);

void func_80107114_mpiq(void) {
    omObjData *obj = omAddObj(5, 0, 0, -1, func_80107168_mpiq);
    s32 *angle = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);

    obj->data = angle;
    *angle = 0;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C718_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C738_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C758_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C778_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C798_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7B8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7D8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C7F8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C818_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C838_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C858_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C878_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C898_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107168_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010720C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010747C_mpiq);

void func_80107558_mpiq(s32 index, s32 value) {
    D_8010CAA0_mpiq[index] = value;
    D_8010CA90_mpiq[index] |= 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107584_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107774_mpiq);

void func_80107C18_mpiq(s32 index) {
    MpiqObjWork *work = OM_GET_DATA_PTR(D_8010CAC0_mpiq[index], MpiqObjWork);
    work->flags |= 1;
    work->unk_08 = 4.0f;
    work->index = index;
}

void func_80107C50_mpiq(s32 index) {
    OM_GET_DATA_PTR(D_8010CAC0_mpiq[index], MpiqObjWork)->flags |= 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107C74_mpiq);

void func_80107D70_mpiq(void) {
    omObjData *obj;
    s32 *flags;

    obj = omAddObj(0xFF, 1, 0, -1, func_80107DE0_mpiq);
    D_8010CAD0_mpiq = obj;
    flags = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);
    obj->data = flags;
    *flags = 0;
    *obj->model = func_8000B108_main(8, 0x69D);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107DE0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107E90_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107F28_mpiq);

void func_80107FC4_mpiq(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80107FCC_mpiq);

void func_8010811C_mpiq(void) {
    MpiqMarkerObjWork *work = OM_GET_DATA_PTR(D_8010CAD4_mpiq, MpiqMarkerObjWork);

    if (--work->timer == 0) {
        func_8001C258_main(*D_8010CAD4_mpiq->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->flags &= ~1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108178_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108494_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801085F4_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108688_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801087F8_mpiq);

void func_801089A4_mpiq(s32 flags) {
    MpiqDanceObjData *work = OM_GET_DATA_PTR(D_8010CA78_mpiq, MpiqDanceObjData);
    work->flags &= ~2;
    work->flags &= ~4;
    work->flags |= flags;
}

s32 func_801089D0_mpiq(omObjData *objA, omObjData *objB) {
    s32 result = 0;
    f32 ax = objA->trans.x;
    f32 ay = objA->trans.y;
    f32 bx = objB->trans.x;
    f32 by = objB->trans.y;

    if (HuSqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) < 150.0f) {
        result = 1;
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108A3C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108B74_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108D10_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80108E20_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109018_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109414_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8A8_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8B4_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C8E4_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C904_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_801096C0_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010A010_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010A184_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AB44_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AEDC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AFAC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010B0CC_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010B900_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BA64_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BB74_mpiq);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", D_8010C964_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010BD1C_mpiq);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C2F0_mpiq);

s32 func_8010C4C0_mpiq(s32 index) {
    s32 result = 0;
    if (D_800EC598_minigame[index]->trans.y == D_8010CA80_mpiq[index]->scale) {
        result = 1;
    }
    return result;
}

void func_8010C558_mpiq(omObjData *obj);

void func_8010C504_mpiq(void) {
    omObjData *obj = omAddObj(0xA, 0, 0, -1, func_8010C558_mpiq);
    s32 *value = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);

    obj->data = value;
    *value = 0;
}

const char D_8010C988_mpiq[] = "ENDLESS";

void func_8010C558_mpiq(omObjData *obj) {
    s32 *counter = obj->data;

    if (((*counter += 1) & 0x10) != 0) {
        fontcolor = FONT_COLOR_WHITE;
        sprintf(D_800D5218_main, D_8010C988_mpiq);
        print8(0xE8, 0x10, D_800D5218_main);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010C5B8_mpiq);

const char D_8010C990_mpiq[] = "MOTION ERROR! WINNER=%d\n";
const char D_8010C9AC_mpiq[] = "";

void func_8010C624_mpiq(void) {
    fontcolor = FONT_COLOR_WHITE;
    sprintf(D_800D5218_main, D_8010C990_mpiq, D_8010C9D8_mpiq);
    print8(0x20, 0xB0, D_800D5218_main);
}
