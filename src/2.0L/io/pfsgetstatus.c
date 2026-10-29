#include "common.h"
#include "controller.h"

s32 __osPfsGetStatus(OSMesgQueue *queue, int channel) {
    s32 ret = 0;
    OSMesg dummy;
    OSContStatus data;

    __osPfsInodeCacheBank = 250;
    __osPfsRequestOneChannel(channel, CONT_CMD_REQUEST_STATUS);
    ret = __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &__osPfsPifRam);
    osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
    __osPfsGetOneChannelData(channel, &data);
    if ((data.status & CONT_CARD_ON) && (data.status & CONT_CARD_PULL)) {
        return PFS_ERR_NEW_PACK;
    }
    if (data.errno != 0 || !(data.status & CONT_CARD_ON)) {
        return PFS_ERR_NOPACK;
    }
    if (data.status & CONT_ADDR_CRC_ER) {
        return PFS_ERR_CONTRFAIL;
    }
    return ret;
}

void __osPfsRequestOneChannel(s32 channel, s32 cmd) {
    u8 *ptr;
    __OSContRequesFormatShort requestformat;
    s32 i;

    __osContLastCmd = CONT_CMD_END;
    __osPfsPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)&__osPfsPifRam;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    for (i = 0; i < channel; i++) {
        *ptr++ = 0;
    }
    *(__OSContRequesFormatShort *)ptr = requestformat;
    ptr += sizeof(__OSContRequesFormatShort);
    *ptr = CONT_CMD_END;
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
