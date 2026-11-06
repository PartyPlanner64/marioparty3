#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/mgdata.h"

u16 D_800A11D0_main[6] = { 0, 0, 0, 0, 0, 0 };
u16 D_800A11DC_main[6] = { 20, 20, 20, 20, 20, -1 };

// The minigame table at rodata 0x800A6D40 (currently in hmfanim.c) likely belongs to this file.

s32 func_800341C0_main(void) {
    return 0x70;
}
