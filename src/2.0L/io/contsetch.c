#include "common.h"
#include "controller.h"

s32 osContSetCh(u8 ch) {
    s32 ret = 0;

    __osSiGetAccess();
    if (ch > MAXCONTROLLERS) {
        D_800CE204 = MAXCONTROLLERS;
    } else {
        D_800CE204 = ch;
    }
    D_800D1F58_main = CONT_CMD_END;
    __osSiRelAccess();
    return ret;
}
