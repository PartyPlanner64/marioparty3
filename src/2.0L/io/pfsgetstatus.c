#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/io/pfsgetstatus", __osPfsGetStatus);

extern u8 D_800D1F58_main;
extern OSPifRam __osPfsPifRam;

void __osPfsRequestOneChannel(s32 cchannel, s32 cchnum) {
    // The request is staged on the stack; the union keeps it inside the 16-byte
    // stack frame the original allocated for it.
    union {
        __OSContRequesFormatShort req;
        u8 bytes[0x10];
    } request;
    u32 *status = &__osPfsPifRam.pifstatus;
    u8 *ptr = (u8 *)status - 0x3C;
    s32 i;

    D_800D1F58_main = 0xFE;
    __osPfsPifRam.pifstatus = 1;
    request.req.txsize = 1;
    request.req.rxsize = 3;
    request.req.cmd = cchnum;
    request.req.typeh = 0xFF;
    request.req.typel = 0xFF;
    request.req.status = 0xFF;

    // Spelled as an explicit guard plus a do/while rather than a for loop so
    // that GCC keeps ptr in $a2 and i in $a3, as in the original.
    i = 0;
    if (cchannel > 0) {
        do {
            *ptr++ = 0;
            i++;
        } while (i < cchannel);
    }

    *(__OSContRequesFormatShort *)ptr = request.req;
    ptr[6] = 0xFE;
}

void __osPfsGetOneChannelData(s32 chan, OSContStatus *data) {
    u8 *ptr = (u8 *)&__osPfsPifRam;
    __OSContRequesFormatShort format;
    s32 i;
    u8 chanerr;

    for (i = 0; i < chan; i++) {
        ptr++;
    }

    format = *((__OSContRequesFormatShort *)ptr);

    chanerr = (format.rxsize & CHNL_ERR_MASK) >> 4;
    data->errno = chanerr;
    if (chanerr) {
        return;
    }

    data->type = (format.typel << 8) | format.typeh;
    data->status = format.status;
}
