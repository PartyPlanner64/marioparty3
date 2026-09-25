#include "common.h"
#include "ovl_81.h"

void func_800DC660_name_81(void);
void func_800DC700_name_81(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C4430", func_800DC660_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C4430", func_800DC700_name_81);

void func_800DC7A0_name_81(void) {
    omAddPrcObj(func_800DC700_name_81, 0xEFFF, 0, 0);
}

void func_800DC7CC_name_81(void) {
    omAddPrcObj(func_800DC660_name_81, 0xEFFF, 0, 0);
}
