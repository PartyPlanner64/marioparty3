#include "common.h"

extern OSMesgQueue __osSiAccessQueue;

INCLUDE_ASM("asm/nonmatchings/2.0L/io/siacs", func_8007C720_main);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/siacs", __osSiGetAccess);

void __osSiRelAccess(void) {
    osSendMesg(&__osSiAccessQueue, NULL, OS_MESG_NOBLOCK);
}
