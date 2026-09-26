#include "common.h"

void func_801059D0_slerror(void);

INCLUDE_ASM("asm/nonmatchings/overlays/slerror/468520", func_801059D0_slerror);

void func_80105E9C_slerror(void) {
    omInitObjMan(0xA, 0xA);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}

void func_80105EDC_slerror(void) {
    omInitObjMan(0xA, 0xA);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}
