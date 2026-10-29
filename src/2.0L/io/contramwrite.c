#include "common.h"
#include "controller.h"

#define READFORMAT(ptr) ((__OSContRamReadFormat *)(ptr))

s32 __osContRamWrite(OSMesgQueue *mq, int channel, u16 address, u8 *buffer, int force) {
    s32 ret = 0;
    s32 i;
    u8 *ptr;
    s32 retry = 2;
    u8 crc;

    if (force != TRUE && address < PFS_LABEL_AREA && address != 0) {
        return 0;
    }

    __osSiGetAccess();
    do {
        ptr = (u8 *)&__osPfsPifRam;
        if (__osContLastCmd != CONT_CMD_WRITE_MEMPACK || __osPfsLastChannel != channel) {
            __osContLastCmd = CONT_CMD_WRITE_MEMPACK;
            __osPfsLastChannel = channel;
            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }
            __osPfsPifRam.pifstatus = CONT_CMD_EXE;
            READFORMAT(ptr)->dummy = CONT_CMD_NOP;
            READFORMAT(ptr)->txsize = CONT_CMD_WRITE_MEMPACK_TX;
            READFORMAT(ptr)->rxsize = CONT_CMD_WRITE_MEMPACK_RX;
            READFORMAT(ptr)->cmd = CONT_CMD_WRITE_MEMPACK;
            READFORMAT(ptr)->datacrc = CONT_CMD_NOP;
            ptr[sizeof(__OSContRamReadFormat)] = CONT_CMD_END;
        } else {
            ptr += channel;
        }
        READFORMAT(ptr)->hi = address >> 3;
        READFORMAT(ptr)->lo = __osContAddressCrc(address) | (address << 5);
        bcopy(buffer, READFORMAT(ptr)->data, BLOCKSIZE);
        __osSiRawStartDma(OS_WRITE, &__osPfsPifRam);
        crc = __osContDataCrc(buffer);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        __osSiRawStartDma(OS_READ, &__osPfsPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
        ret = CHNL_ERR(*READFORMAT(ptr));
        if (ret == 0) {
            if (crc != READFORMAT(ptr)->datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    break;
                }
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            ret = PFS_ERR_NOPACK;
        }
    } while (ret == PFS_ERR_CONTRFAIL && retry-- >= 0);
    __osSiRelAccess();
    return ret;
}
