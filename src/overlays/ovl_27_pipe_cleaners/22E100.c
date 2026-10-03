#include "common.h"
#include "overlays/ovl_27.h"

// Per-pipe state used by the pipe cleaners (D_8010AB30_pipe_cleaners, one entry per pipe).
typedef struct PipeCleanerWork {
    /* 0x00 */ s32 motionId;
    /* 0x04 */ omObjData *object;
    /* 0x08 */ s32 counter;
    /* 0x0C */ s32 playerId;
    /* 0x10 */ s32 state;
    /* 0x14 */ f32 rotX;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ Vec pos;
    /* 0x28 */ char unk28[0x10];
} PipeCleanerWork; // Size 0x38

extern void func_800146DC_main(s16 arg0, u16 arg1, u16 arg2);
extern s16 D_8010A830_pipe_cleaners[4];
extern void func_80105C50_pipe_cleaners(omObjData *obj);
extern void func_80105DF0_pipe_cleaners(omObjData *obj);
extern void func_80108F18_pipe_cleaners(omObjData *obj);
extern void func_80105F00_pipe_cleaners(omObjData *obj);
extern void func_80106204_pipe_cleaners(omObjData *obj);
extern void func_80108194_pipe_cleaners(omObjData *obj);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801059A0_pipe_cleaners);

f32 func_801059BC_pipe_cleaners(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_pipe_cleaners(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105A74_pipe_cleaners);

void func_80105B3C_pipe_cleaners(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105BB4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105C50_pipe_cleaners);

void func_80105DB4_pipe_cleaners(void) {
    omAddObj(0x64, 1, 0, -1, func_80105C50_pipe_cleaners);
}

void func_80105DE8_pipe_cleaners(omObjData *object) {
}

void func_80105DF0_pipe_cleaners(omObjData *obj) {
    obj->model[0] = func_8000B108_main(0x480001, 0x299);
    obj->model[1] = func_8000B108_main(0x480002, 0x299);
    obj->trans.x = obj->trans.y = obj->trans.z = 0.0f;
    obj->func = func_80105DE8_pipe_cleaners;
}

void func_80105E60_pipe_cleaners(void) {
    omAddObj(0x6E, 2, 0, -1, func_80105DF0_pipe_cleaners);
}

void func_80105E94_pipe_cleaners(s32 arg0) {
    s16 modelId = D_8010A830_pipe_cleaners[arg0];

    func_8001C258_main(D_800CBB60_main[modelId].modelId, 4, 0);
    func_800146DC_main(modelId, 1, 0);
}

void func_80105EF8_pipe_cleaners(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80105F00_pipe_cleaners);

void func_80106078_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1F4, 1, 0, -1, func_80105F00_pipe_cleaners)->work[0] = i;
    }
}

void func_801060D4_pipe_cleaners(s32 arg0) {
    s32 *state = &D_8010A928_pipe_cleaners[arg0];

    if (*state == 0) {
        *state = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801060FC_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106204_pipe_cleaners);

void func_8010638C_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        omAddObj(0x190, 1, 1, -1, func_80106204_pipe_cleaners)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801063E8_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106540_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801066E4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_8010698C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106A70_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106B18_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A134_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A140_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A14C_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A158_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A164_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A170_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A17C_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A188_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106BF8_pipe_cleaners);

void func_80106CB4_pipe_cleaners(s32 arg0, PipeCleanerWork *work) {
    func_8001C258_main(work->object->model[2], 4, 4);
    work->state = 3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106CF4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106DA4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106E10_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80106FD8_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107114_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_8010731C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801073A4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_8010742C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107598_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107A48_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107B28_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107C08_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107D84_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80107E3C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_8010801C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801080F4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108194_pipe_cleaners);

void func_80108428_pipe_cleaners(void) {
    s32 i;

    for (i = 0; i < 0x10; i++) {
        omAddObj(0xC8, 1, 2, -1, func_80108194_pipe_cleaners)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108484_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108708_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801088AC_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108964_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108A4C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80108F18_pipe_cleaners);

void func_801091E4_pipe_cleaners(void) {
    omAddObj(0x258, 1, 0, -1, func_80108F18_pipe_cleaners);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109218_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801093A4_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801096C0_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109784_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_8010984C_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109884_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_801098DC_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109B74_pipe_cleaners);

void func_80109BF4_pipe_cleaners(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109BFC_pipe_cleaners);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", func_80109D70_pipe_cleaners);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_27_pipe_cleaners/22E100", D_8010A2A8_pipe_cleaners);
