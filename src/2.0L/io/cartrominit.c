#include "common.h"
#include "piint.h"

extern OSPiHandle D_800D0380_main;  /* __CartRomHandle */
extern OSPiHandle *D_800A2A4C_main; /* __osPiTable */
extern s32 D_800A2A60_main;         /* first */

OSPiHandle *osCartRomInit(void) {
    u32 value = 0;
    u32 saveMask;
    u32 stat;
    u32 latency;
    u32 pulse;
    u32 pageSize;
    u32 relDuration;

    __osPiGetAccess();
    if (!D_800A2A60_main) {
        __osPiRelAccess();
        return &D_800D0380_main;
    }

    D_800A2A60_main = FALSE;
    D_800D0380_main.type = DEVICE_TYPE_CART;
    D_800D0380_main.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR2);
    D_800D0380_main.domain = PI_DOMAIN1;
    D_800D0380_main.speed = 0;
    bzero(&D_800D0380_main.transferInfo, sizeof(__OSTranxInfo));

    WAIT_ON_IOBUSY(stat);

    latency = IO_READ(PI_BSD_DOM1_LAT_REG);
    pageSize = IO_READ(PI_BSD_DOM1_PGS_REG);
    relDuration = IO_READ(PI_BSD_DOM1_RLS_REG);
    pulse = IO_READ(PI_BSD_DOM1_PWD_REG);

    IO_WRITE(PI_BSD_DOM1_LAT_REG, 0xFF);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, 0);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, 3);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, 0xFF);

    value = IO_READ(D_800D0380_main.baseAddress);
    D_800D0380_main.latency = value & 0xFF;
    D_800D0380_main.pageSize = (value >> 16) & 0xF;
    D_800D0380_main.relDuration = (value >> 20) & 0xF;
    D_800D0380_main.pulse = (value >> 8) & 0xFF;

    IO_WRITE(PI_BSD_DOM1_LAT_REG, latency);
    IO_WRITE(PI_BSD_DOM1_PGS_REG, pageSize);
    IO_WRITE(PI_BSD_DOM1_RLS_REG, relDuration);
    IO_WRITE(PI_BSD_DOM1_PWD_REG, pulse);

    saveMask = __osDisableInt();
    D_800D0380_main.next = D_800A2A4C_main;
    D_800A2A4C_main = &D_800D0380_main;
    __osRestoreInt(saveMask);
    __osPiRelAccess();
    return &D_800D0380_main;
}
