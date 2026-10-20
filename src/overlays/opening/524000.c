#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "mallocblock.h"
#include "opening.h"

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opObjectInit);

void opTitleObjectSetup(void) {
    opObjectInit();
    opTitleCreate();
}

void func_80105C2C_opening(void) {
    opObjectInit();
    opDemoCreate();
}

void opDemoObjectSetup(void) {
    opObjectInit();
    opDemoCreate();
}
