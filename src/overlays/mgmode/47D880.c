#include "common.h"

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 espriteSlot;
} MgmodeEsprite;

void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116610_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_8011667C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116794_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_801168E0_mgmode);

void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3) {
    func_8000BBD4_main(arg0[index].espriteSlot, arg2, arg3);
}

void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index) {
    func_8000BB54_main(arg0[index].espriteSlot);
}

void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index) {
    func_8000BB94_main(arg0[index].espriteSlot);
}

void func_801169F0_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    func_8000BC48_main(arg0[index].espriteSlot, arg2);
}

void func_80116A1C_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2) {
    func_8000BC88_main(arg0[index].espriteSlot, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116A48_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116A78_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/47D880", func_80116AA8_mgmode);

void func_80116AEC_mgmode(MgmodeEsprite *arg0, s16 index, u16 arg2) {
    func_8000BCC8_main(arg0[index].espriteSlot, arg2);
}
