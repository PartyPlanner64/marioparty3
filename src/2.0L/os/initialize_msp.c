#include "common.h"

#define MSCP_COMPARE 0x4B4D4300
#define MSCP_COMPARE_ADDR (*(vu32 *)0xBFF00000)
#define MSCP_STATUS_ADDR (*(vu32 *)0xBFF00010)

INCLUDE_ASM("asm/nonmatchings/2.0L/os/initialize_msp", msp_proutSyncPrintf);

INCLUDE_ASM("asm/nonmatchings/2.0L/os/initialize_msp", __osInitialize_msp);

u32 __checkHardware_msp(void) {
    if (MSCP_COMPARE_ADDR != MSCP_COMPARE) {
        return 0;
    }
    return MSCP_STATUS_ADDR == 0;
}
