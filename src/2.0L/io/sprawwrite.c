#include "common.h"
#include "PR/osint.h"

s32 __osSpRawWriteIo(u32 devAddr, u32 data) {
    if (__osSpDeviceBusy()) {
        return -1;
    }

    IO_WRITE(devAddr, data);
    return 0;
}
