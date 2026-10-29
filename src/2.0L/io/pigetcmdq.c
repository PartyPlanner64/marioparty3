#include "common.h"

extern OSDevMgr __osPiDevMgr;

OSMesgQueue *osPiGetCmdQueue(void) {
    if (__osPiDevMgr.active == 0) {
        return 0;
    }
    return __osPiDevMgr.cmdQueue;
}
