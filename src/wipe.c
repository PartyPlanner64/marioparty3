#include "game/wipe.h"
#include "include_asm.h"
#include "common.h"
#include "malloc.h"

extern u8 D_800A26D0_main;
extern u16 *D_800A26D4_main;
extern u16 *D_800BDA70_main;
extern u16 *D_800BDA74_main;
extern u8 D_800BDA78_main;
extern Gfx *D_800BDA7C_main;
extern u8 D_800CC0BA_main;
extern u8 D_800CCF84_main;
extern u8 D_800CDA74_main;
extern f32 D_800D0A3C_main;
extern u8 D_800D0598_main;
extern u8 *D_800D1F80_main[8];
extern f32 D_800D51F4_main;
extern u8 D_800D5304_main;
extern u8 D_800D212E_main;
extern u16 *D_800D5550_main;

void WipeInit(void) {
    s16 i;

    D_800CCF84_main = 0;
    D_800CC0BA_main = 0;
    D_800D212E_main = 0;
    D_800D0598_main = 0;
    D_800CDA74_main = 0;
    D_800D5304_main = 0;
    for (i = 0; i < 8; i++) {
        D_800D1F80_main[i] = NULL;
    }
    func_8003661C_main();
}

INCLUDE_ASM("asm/nonmatchings/wipe", WipeExecAlways);

void WipeCreateIn(s16 arg0, s16 arg1) {
    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 1;
        D_800CCF84_main = 1;
        if (arg0 != 0xFF) {
            D_800A26D0_main = arg0;
        }
        D_800D0A3C_main = arg1;
        D_800D51F4_main = 0.0f;
    }
}

void WipeCreateOut(s16 arg0, s16 arg1) {
    if (D_800CCF84_main == 0) {
        D_800CC0BA_main = 2;
        D_800CCF84_main = 1;
        if (arg0 != 0xFF) {
            D_800A26D0_main = arg0;
        }
        D_800D0A3C_main = arg1;
        D_800D51F4_main = 0.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/wipe", WipeStatGet);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeColorSet);

u8 *WipeMalloc(u32 size) {
    s16 i;

    for (i = 0; i < 8; i++) {
        if (D_800D1F80_main[i] == NULL) {
            break;
        }
    }
    if (i == 8) {
        return NULL;
    }
    D_800D1F80_main[i] = HuMemMemoryAllocPerm(size);
    return D_800D1F80_main[i];
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062168_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062244_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_8006231C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800623F0_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062584_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_8006265C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062844_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062884_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80062A30_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80063454_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80063510_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800635F4_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800636D8_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800640EC_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800641C8_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065094_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_8006515C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_800651F0_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065C9C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065D80_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065E88_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80065F8C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80066048_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_8006608C_main);

INCLUDE_ASM("asm/nonmatchings/wipe", func_80066164_main);

void func_8006619C_main(Gfx **arg0) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
    D_800BDA78_main++;
}

void func_800661D4_main(Gfx **arg0, s32 arg1, s32 arg2) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
}

void func_800661F8_main(void) {
    D_800BDA70_main = D_800A26D4_main;
    D_800BDA74_main = D_800D5550_main;
    D_800D5304_main = 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_80066228_main);
