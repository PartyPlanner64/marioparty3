#include "common.h"

s32 __osPiRawWriteIo(u32 devAddr, u32 val) {
    u32 status;

    status = IO_READ(PI_STATUS_REG) & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY);
    if (status) {
        do {
            status = IO_READ(PI_STATUS_REG) & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY);
        } while (status);
    }

    IO_WRITE((u32)osRomBase | devAddr, val);
    return 0;
}
