#include "common.h"

// Camera state reached through the pointer at 0x5C of the camera controller
// struct that the overlay's entry points receive.
typedef struct func_800D7084_minigame_Camera {
    /* 0x00 */ char unk00[0x58];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
} func_800D7084_minigame_Camera;

extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6B70_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6E14_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6E74_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6F20_minigame);

void func_800D7084_minigame(func_800D7084_minigame_Camera *arg0) {
    if (__builtin_fabs((f64)arg0->unk5C) > 1.0) {
        D_800EBE2C_minigame += arg0->unk5C * arg0->unk58;
    }
    if (__builtin_fabs((f64)arg0->unk64) > 1.0) {
        D_800EC5D8_minigame += arg0->unk64 * arg0->unk58;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D710C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D71F0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D72B0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7388_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D74AC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7AA8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7C14_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7FA8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D80DC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D81C8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D83D8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D853C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D861C_minigame);
