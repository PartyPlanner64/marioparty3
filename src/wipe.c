#include "game/wipe.h"
#include "include_asm.h"

extern Gfx *D_800BDA7C_main;
extern u16 *D_800A26D4_main;
extern u16 *D_800D5550_main;
extern u16 *D_800BDA70_main;
extern u16 *D_800BDA74_main;
extern u8 D_800D5304_main;

INCLUDE_ASM("asm/nonmatchings/wipe", WipeInit);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeExecAlways);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeCreateIn);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeCreateOut);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeStatGet);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeColorSet);

INCLUDE_ASM("asm/nonmatchings/wipe", WipeMalloc);

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

INCLUDE_ASM("asm/nonmatchings/wipe", func_8006619C_main);

void func_800661D4_main(Gfx **arg0, s32 arg1, s32 arg2) {
    gSPDisplayList((*arg0)++, D_800BDA7C_main);
}

void func_800661F8_main(void) {
    D_800BDA70_main = D_800A26D4_main;
    D_800BDA74_main = D_800D5550_main;
    D_800D5304_main = 1;
}

INCLUDE_ASM("asm/nonmatchings/wipe", func_80066228_main);
