#include "common.h"
#include <PR/viint.h>

void osViBlack(u8 active) {
    u32 intMask;

    intMask = __osDisableInt();
    if (active != 0) {
        __osViNext->state |= VI_STATE_BLACK;
    } else {
        __osViNext->state &= ~VI_STATE_BLACK;
    }
    __osRestoreInt(intMask);
}
