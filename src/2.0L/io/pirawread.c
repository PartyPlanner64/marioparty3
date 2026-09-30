#include "common.h"

s32 __osPiRawReadIo(u32 devAddr, void *dramAddr) {
    u32 status;

    status = IO_READ(PI_STATUS_REG) & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY);
    if (status) {
        do {
            status = IO_READ(PI_STATUS_REG) & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY);
        } while (status);
    }

    *(u32 *)dramAddr = IO_READ((u32)osRomBase | devAddr);
    return 0;
}
