#include "common.h"

typedef struct MgResultBattleGroupSprites {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
} MgResultBattleGroupSprites; // Size 0x6

extern u16 D_80108F30_mgresultbattle[];
extern MgResultBattleGroupSprites D_80108F38_mgresultbattle[];

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80107D10_mgresultbattle);

void func_80107F94_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80107F9C_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_801080A0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108130_mgresultbattle);

void func_8010829C_mgresultbattle(void) {
}

void func_801082A4_mgresultbattle(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_801082AC_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_801082C0_mgresultbattle);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultbattle/4F5AF0", func_80108510_mgresultbattle);

void func_80108858_mgresultbattle(s16 group) {
    func_8000BB94_main(D_80108F30_mgresultbattle[group]);
    func_8000BB94_main(D_80108F38_mgresultbattle[group].unk_00);
    func_8000BB94_main(D_80108F38_mgresultbattle[group].unk_02);
    func_8000BB94_main(D_80108F38_mgresultbattle[group].unk_04);
}
