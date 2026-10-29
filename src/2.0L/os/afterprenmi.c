#include "common.h"
#include "PR/os_internal.h"

s32 __osAfterPreNMI(void) {
    return __osSpSetPc(0);
}
