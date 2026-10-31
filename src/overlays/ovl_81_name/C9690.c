#include "common.h"
#include "ovl_81.h"

extern void func_800E1A24_name_81(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E18C0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E18D8_name_81);

void func_800E18E8_name_81(s16 arg0, s16 arg1) {
    s16 v0;
    s16 v1 = arg1;

    v0 = arg1;
    if (v0 == MBDGetCurrentPlayerIndex()) {
        D_80102BF0_name_81 = v1;
        D_80102BF2_name_81 = arg0;
    } else {
        D_80102BF0_name_81 = arg0;
        D_80102BF2_name_81 = v1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E1960_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E1A24_name_81);

void func_800E1F38_name_81(void) {
    Process *parent = HuPrcCurrentGet();

    HuPrcChildLink(parent, omAddPrcObj(func_800E1A24_name_81, 0x1003, 0, 0));
    HuPrcChildWatch();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E1F88_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E1F94_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E1FB8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E209C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E24AC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E2550_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C9690", func_800E27D4_name_81);
