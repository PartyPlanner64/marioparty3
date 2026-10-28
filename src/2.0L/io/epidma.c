#include "common.h"

extern s32 D_800A2A30_main; // __osPiDevMgr.active

extern OSMesgQueue *func_80080B30_main(void); // osPiGetCmdQueue

s32 osEPiStartDma(OSPiHandle *pihandle, OSIoMesg *mb, s32 direction) {
    register s32 ret;

    if (!D_800A2A30_main) {
        return -1;
    }

    mb->piHandle = pihandle;
    if (direction == OS_READ) {
        mb->hdr.type = OS_MESG_TYPE_EDMAREAD;
    } else {
        mb->hdr.type = OS_MESG_TYPE_EDMAWRITE;
    }

    if (mb->hdr.pri == OS_MESG_PRI_HIGH) {
        ret = osJamMesg(func_80080B30_main(), mb, OS_MESG_NOBLOCK);
    } else {
        ret = osSendMesg(func_80080B30_main(), mb, OS_MESG_NOBLOCK);
    }
    return ret;
}
