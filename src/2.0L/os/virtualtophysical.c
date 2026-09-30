#include "common.h"

extern u32 __osProbeTLB(void *);

u32 osVirtualToPhysical(void *addr) {
    if (IS_KSEG0(addr)) {
        return K0_TO_PHYS(addr);
    }

    if (IS_KSEG1(addr)) {
        return K0_TO_PHYS(addr);
    }

    return __osProbeTLB(addr);
}
