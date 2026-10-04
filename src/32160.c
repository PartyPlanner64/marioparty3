#include "common.h"
#include "mallocblock.h"

typedef struct {
    char unk00[0x1C];
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    void *unk24;
    void *unk28;
} HmfPalData;

void func_80032950_main(void);
INCLUDE_ASM("asm/nonmatchings/32160", func_80031560_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031630_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_8003186C_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A08_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A44_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031A60_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031B30_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80031DF4_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032038_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032104_main);

void func_80032194_main(HmfPalData *pal) {
    pal->unk20 = 0;
    pal->unk24 = NULL;
    func_80019C00_main(pal->unk28);
}

INCLUDE_ASM("asm/nonmatchings/32160", func_800321B8_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800322AC_main);

void func_8003235C_main(void) {
    s16 i;

    D_800D1714_main = HuMemAlloc(0x600);
    for (i = 0; i < 0x80; i++) {
        D_800D1714_main[i].animIdx = -1;
    }
    func_80032950_main();
}

INCLUDE_ASM("asm/nonmatchings/32160", HmfAnimCreate);

INCLUDE_ASM("asm/nonmatchings/32160", func_80032694_main);

void func_80032950_main(void) {
    s16 i;

    D_800D408C_main = HuMemAlloc(0x300);
    for (i = 0; i < 0x20; i++) {
        D_800D408C_main[i].unk0C = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/32160", func_800329B4_main);

void func_80032FC0_main(s16 animIdx, u8 bitmask, u8 flags) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    anim->flags = (anim->flags & ~bitmask) | flags;
}

void func_80032FF8_main(s16 animIdx, u8 rot) {
    HmfAnim *anim = &D_800D1714_main[animIdx];

    anim->rot = rot;
    anim->frame = 0;
    anim->interp = 0;
}

INCLUDE_ASM("asm/nonmatchings/32160", func_8003302C_main);

u8 func_800330D4_main(s16 animIdx) {
    HmfAnim *anim = &D_800D1714_main[animIdx];
    u8 *rotFrames = (u8 *)&D_800D408C_main[anim->animIdx].rot[anim->rot];

    return rotFrames[1];
}

INCLUDE_ASM("asm/nonmatchings/32160", func_80033128_main);

void func_800332D4_main(s16 animIdx, f32 alpha) {
    D_800D1714_main[animIdx].alpha = (u8)(alpha * 16.0f);
}

INCLUDE_ASM("asm/nonmatchings/32160", func_80033354_main);

void func_800333B0_main(s16 animIdx) {
    if (D_800D408C_main[animIdx].unk0C != NULL) {
        D_800D408C_main[animIdx].refCount--;
        if (D_800D408C_main[animIdx].refCount == 0) {
            func_80019C68_main(animIdx + 0x4E20);
            D_800D408C_main[animIdx].unk0C = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/32160", func_80033430_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033450_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033510_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_800335BC_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033694_main);

void func_80033910_main(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 |= 0x80;
        }
    }
}

void func_80033970_main(HmfData *arg0) {
    s16 i;

    for (i = 0; i < arg0->unk12; i++) {
        if (arg0->unk84[i].unk3 != -1) {
            arg0->unk84[i].unk9 &= 0x7F;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/32160", func_800339D0_main);

INCLUDE_ASM("asm/nonmatchings/32160", func_80033D0C_main);

s32 func_80033F8C_main(void) {
    s16 i;

    for (i = 0; i < 0x80; i++) {
        if (D_800D1714_main[i].animIdx == -1) {
            return i;
        }
    }
    return -1;
}

s32 func_80033FEC_main(void) {
    s16 i;

    for (i = 0; i < 0x20; i++) {
        if (D_800D408C_main[i].unk0C == NULL) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/32160", func_80034048_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D44_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D4C_main);

INCLUDE_RODATA("asm/nonmatchings/32160", D_800A6D50_main);
