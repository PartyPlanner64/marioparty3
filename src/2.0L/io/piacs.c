#include "common.h"

extern OSMesgQueue D_800D0550_main;

INCLUDE_ASM("asm/nonmatchings/2.0L/io/piacs", __osPiCrateAccessQueue);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/piacs", __osPiGetAccess);

void __osPiRelAccess(void) {
    osSendMesg(&D_800D0550_main, NULL, OS_MESG_NOBLOCK);
}
