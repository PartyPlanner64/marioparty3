#include "ultra64.h"
#include "types.h"
#include "macros.h"
#include "humath.h"
#include "game/rom.h"

extern OSPiHandle *cartRomHandle;
static OSMesgQueue dmaMesgQueue;
static OSMesg dmaMesgBuf[10];
extern void *piMesgBuf;
extern OSMesgQueue piMesgQueue;

void dmaInit(void) {
    osCreatePiManager(OS_PRIORITY_PIMGR, &piMesgQueue, &piMesgBuf, 0x2A);
    cartRomHandle = osCartRomInit();
    osCreateMesgQueue(&dmaMesgQueue, dmaMesgBuf, ARRAY_COUNT(dmaMesgBuf));
}

s32 dmaStart(OSIoMesg *msg, u8 pri, s32 direction, u8 *src, u8 *dest, u32 size, OSMesgQueue *retQueue) {
    msg->hdr.pri = pri;
    msg->hdr.retQueue = retQueue;
    msg->dramAddr = dest;
    msg->devAddr = (u32)src;
    msg->size = size;
    return osEPiStartDma(cartRomHandle, msg, direction);
}

s32 dmaRead(u32 src, u8 *dest, s32 size) {
    OSIoMesg msg;
    s32 curBlockOffset;
    u32 curBlockSize;
    s32 err;

    osInvalDCache(dest, OS_DCACHE_ROUNDUP_SIZE(size));

    curBlockOffset = 0;
    while (size > 0) {
        curBlockSize = size;
        if (size > 0x4000) {
            curBlockSize = 0x4000;
        }
        err = dmaStart(&msg, 0, 0, &((u8*)src)[curBlockOffset], &dest[curBlockOffset], curBlockSize, &dmaMesgQueue);

        if (err != 0) {
            return err;
        }

        osRecvMesg(&dmaMesgQueue, 0, 1);
        size -= 0x4000;
        curBlockOffset += 0x4000;
    }
    return err;
}

s32 dmaReadOvl(u32 src, u8 *dest, s32 size) {
    OSIoMesg msg;
    s32 curBlockOffset;
    u32 var_v1;
    s32 err;

    osInvalICache(dest, OS_DCACHE_ROUNDUP_SIZE(size));
    osInvalDCache(dest, OS_DCACHE_ROUNDUP_SIZE(size));

    curBlockOffset = 0;
    while (size > 0) {
        var_v1 = size;
        if (size > 0x4000) {
            var_v1 = 0x4000;
        }
        err = dmaStart(&msg, 0, 0, &((u8*)src)[curBlockOffset], &dest[curBlockOffset], var_v1, &dmaMesgQueue);

        if (err != 0) {
            return err;
        }

        osRecvMesg(&dmaMesgQueue, 0, 1);
        size -= 0x4000;
        curBlockOffset += 0x4000;
    }
    return err;
}
