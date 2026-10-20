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

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoObjectSetup);

void opEventInit(void) {
    opDemoEndReset();
}

void opTitleCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opTitleMain, 0x5000, 0x800, 0);
}

void opDemoCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opDemoMain, 0x5000, 0x800, 0);
}

Process *opDemoEventCreate(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *eventPrc = omAddPrcObj(opDemoEvent, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, eventPrc);
    return eventPrc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opDemoMain);

Process *func_80105F68_opening(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *sprPrc = omAddPrcObj(opTitleSprMain, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, sprPrc);
    return sprPrc;
}

INCLUDE_ASM("asm/nonmatchings/overlays/opening/524000", opTitleMain);

s32 opBtnStartCheck(void) {
    if (GWContErrorGet() == 1) {
        return (D_800D5558_main[0] & 0x1000) != 0;
    }
    return 0;
}

void opDemoEndReset(void) {
    D_80114EA4_opening = 0;
}

void opDemoEndSet(s32 value) {
    D_80114EA4_opening = value;
}

s32 opDemoEndGet(void) {
    return D_80114EA4_opening;
}
