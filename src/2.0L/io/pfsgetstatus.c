#include "common.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/io/pfsgetstatus", __osPfsGetStatus);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/pfsgetstatus", __osPfsRequestOneChannel);

extern OSPifRam __osPfsPifRam;

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
