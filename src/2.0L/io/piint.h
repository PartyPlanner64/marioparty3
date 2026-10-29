#ifndef _PIINT_H
#define _PIINT_H

#include "PR/os_internal.h"

#define LEO_BASE_REG 0x05000000
#define LEO_STATUS (LEO_BASE_REG + 0x508)
#define LEO_BM_CTL (LEO_BASE_REG + 0x510)

#define LEO_STATUS_MECHANIC_INTERRUPT 0x02000000

#define LEO_BM_CTL_START 0x80000000
#define LEO_BM_CTL_RESET 0x10000000
#define LEO_BM_CTL_CLR_MECHANIC_INTR 0x01000000

#define LEO_CMD_TYPE_0 0
#define LEO_CMD_TYPE_1 1

#define LEO_ERROR_GOOD 0
#define LEO_ERROR_4 4
#define LEO_ERROR_29 29

extern OSPiHandle *__osCurrentHandle[2];

void __osPiGetAccess(void);
void __osPiRelAccess(void);
s32 __osPiRawReadIo(u32 devAddr, u32 *data);
s32 __osPiRawWriteIo(u32 devAddr, u32 data);
s32 __osEPiRawReadIo(OSPiHandle *pihandle, u32 devAddr, u32 *data);
s32 __osEPiRawWriteIo(OSPiHandle *pihandle, u32 devAddr, u32 data);

#define WAIT_ON_IOBUSY(stat)                                \
    stat = IO_READ(PI_STATUS_REG);                          \
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) \
        stat = IO_READ(PI_STATUS_REG);

#define UPDATE_REG(reg, var)           \
    if (cHandle->var != pihandle->var) \
        IO_WRITE(reg, pihandle->var);

#define EPI_SYNC(pihandle, stat, domain)                   \
    WAIT_ON_IOBUSY(stat)                                   \
                                                           \
    domain = pihandle->domain;                             \
    if (__osCurrentHandle[domain]->type != pihandle->type) { \
        OSPiHandle *cHandle = __osCurrentHandle[domain];     \
        if (domain == PI_DOMAIN1) {                        \
            UPDATE_REG(PI_BSD_DOM1_LAT_REG, latency);      \
            UPDATE_REG(PI_BSD_DOM1_PGS_REG, pageSize);     \
            UPDATE_REG(PI_BSD_DOM1_RLS_REG, relDuration);  \
            UPDATE_REG(PI_BSD_DOM1_PWD_REG, pulse);        \
        } else {                                           \
            UPDATE_REG(PI_BSD_DOM2_LAT_REG, latency);      \
            UPDATE_REG(PI_BSD_DOM2_PGS_REG, pageSize);     \
            UPDATE_REG(PI_BSD_DOM2_RLS_REG, relDuration);  \
            UPDATE_REG(PI_BSD_DOM2_PWD_REG, pulse);        \
        }                                                  \
        cHandle->type = pihandle->type;                    \
        cHandle->latency = pihandle->latency;              \
        cHandle->pageSize = pihandle->pageSize;            \
        cHandle->relDuration = pihandle->relDuration;      \
        cHandle->pulse = pihandle->pulse;                  \
    }

#endif
