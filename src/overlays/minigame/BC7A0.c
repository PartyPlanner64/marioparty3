#include "common.h"

// Per-minigame-field work allocated in func_800E9C20_minigame, stored at D_800EBDF4_minigame
typedef struct D_800EBDF4_minigame_Entry {
    /* 0x00 */ s16 *unk_00;
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} D_800EBDF4_minigame_Entry; // Size 0x18

extern D_800EBDF4_minigame_Entry *D_800EBDF4_minigame;

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800E9C20_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800E9E28_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800E9F40_minigame);

void func_800EA0FC_minigame(s16 arg0, f32 arg1, f32 arg2) {
    D_800EBDF4_minigame[arg0].unk_08 = arg1;
    D_800EBDF4_minigame[arg0].unk_0C = arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA128_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA178_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA1E4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA2A8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA444_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/BC7A0", func_800EA518_minigame);
