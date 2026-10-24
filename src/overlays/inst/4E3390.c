#include "common.h"

typedef struct {
    s16 curGroup;       /* 0x00 */
    s16 unk_02[0xB];    /* 0x02 */
    s16 spriteGroup[4]; /* 0x18, unknown size */
    s16 unk_20[0x1C];   /* 0x20 */
    Vec2f pos;          /* 0x58 */
} UnkInst;              /* unknown size */

typedef struct {
    s16 curGroup;  /* 0x00 */
    s16 pad_02[5]; /* 0x02 */
    s16 member;    /* 0x0C */
} UnkInstWin;      /* sizeof 0x0E */

void func_8010AC30_inst(omObjData *); /* extern */
void func_8010BE78_inst(s32 arg0);    /* extern */

extern s8 D_8010D408_inst;
extern s8 D_8010D550_inst;
extern s8 D_8010D551_inst;
extern s8 D_8010D5B0_inst;
extern void (*D_8010DC94_inst)(omObjData *);
extern void (*D_8010DCA4_inst)(s32);
extern UnkInstWin D_8010DCA8_inst;
extern UnkInst D_8010DCE0_inst;
extern UnkInst D_8010DD58_inst;

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A1D0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A750_inst);

void func_8010AC04_inst(void) {
    if (D_8010D550_inst == 1) {
        D_8010DC94_inst = func_8010AC30_inst;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AC30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AD78_inst);

void func_8010B038_inst(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9C8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9E8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA34_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA44_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA54_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA64_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA74_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA84_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA94_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAA4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAB0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DABC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAC8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B040_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B0FC_inst);

s32 func_8010B10C_inst(void) {
    return D_8010D550_inst;
}

s32 func_8010B118_inst(void) {
    return D_8010D551_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B124_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B2A4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B628_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B990_inst);

void func_8010BE28_inst(void) {
    if (D_8010D408_inst == 1) {
        D_8010D5B0_inst = 1;
    }
    if (D_8010D5B0_inst == 1) {
        D_8010DCA4_inst = func_8010BE78_inst;
    }
}

void func_8010BE70_inst(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010BE78_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAF8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB04_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB10_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB1C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C124_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C55C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C5C4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C848_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C890_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C8B4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C8D0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C8E0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010CA74_inst);

void func_8010CBB8_inst(s32 arg0) {
    TextWindow *window = &D_800CC69C_main[D_8010DCA8_inst.curGroup];
    s16 member = D_8010DCA8_inst.member;

    func_80055024_main(window->unk_6C, member, window->unk_6E[member], arg0 & 0xFF);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010CC14_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010CDE4_inst);

void func_8010CED0_inst(s32 x, s32 y) {
    func_80054904_main(D_8010DCE0_inst.spriteGroup[D_8010DCE0_inst.curGroup], 0, x, y);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010CF14_inst);

void func_8010CF98_inst(void) {
    D_8010DD58_inst.pos.x = 216.0f;
    D_8010DD58_inst.pos.y = 90.0f;
    func_80054904_main(D_8010DD58_inst.spriteGroup[D_8010DD58_inst.curGroup], 0, 0xD8, 0x5A);
}

void func_8010CFF4_inst(void) {
    D_8010DD58_inst.pos.x = 512.0f;
    D_8010DD58_inst.pos.y = 512.0f;
    func_80054904_main(D_8010DD58_inst.spriteGroup[D_8010DD58_inst.curGroup], 0, 0x200, 0x200);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010D044_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010D1D4_inst);
