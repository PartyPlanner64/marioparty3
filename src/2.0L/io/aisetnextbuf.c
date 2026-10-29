#include "common.h"
#include "PR/osint.h"

extern u8 hdwrBugFlag;

s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    char *bptr;

    if (__osAiDeviceBusy()) {
        return -1;
    }

    bptr = bufPtr;
    if (hdwrBugFlag != 0) {
        bptr -= 0x2000;
    }

    if ((((u32)bufPtr + size) & 0x1FFF) == 0) {
        hdwrBugFlag = 1;
    } else {
        hdwrBugFlag = 0;
    }

    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);
    return 0;
}
