#include "common.h"
#include "controller.h"

#define READFORMAT(ptr) ((__OSContRamReadFormat *)(ptr))

#define PFS_MOTOR_INITIALIZED 0x8

#define CONT_BLOCK_DETECT 0x400
#define CONT_BLOCK_RUMBLE 0x600

extern OSPifRam __MotorDataBuf[MAXCONTROLLERS];

s32 __osMotorAccess(OSPfs *pfs, s32 flag) {
    s32 i;
    s32 ret;
    u8 *ptr = (u8 *)&__MotorDataBuf[pfs->channel];

    if (!(pfs->status & PFS_MOTOR_INITIALIZED)) {
        return PFS_ERR_INVALID;
    }

    __osSiGetAccess();
    __MotorDataBuf[pfs->channel].pifstatus = CONT_CMD_EXE;
    ptr += pfs->channel;
    for (i = 0; i < BLOCKSIZE; i++) {
        READFORMAT(ptr)->data[i] = flag;
    }

    __osContLastCmd = CONT_CMD_END;
    __osSiRawStartDma(OS_WRITE, &__MotorDataBuf[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &__MotorDataBuf[pfs->channel]);
    osRecvMesg(pfs->queue, NULL, OS_MESG_BLOCK);

    ret = READFORMAT(ptr)->rxsize & CHNL_ERR_MASK;
    if (!ret) {
        if (!flag) {
            if (READFORMAT(ptr)->datacrc != 0) {
                ret = PFS_ERR_CONTRFAIL;
            }
        } else {
            if (READFORMAT(ptr)->datacrc != 0xEB) {
                ret = PFS_ERR_CONTRFAIL;
            }
        }
    }

    __osSiRelAccess();
    return ret;
}

s32 osMotorInit(OSMesgQueue *mq, OSPfs *pfs, int channel) {
    s32 ret;
    u8 temp[BLOCKSIZE];
    u8 *ptr;
    __OSContRamReadFormat ramreadformat;
    s32 i;

    pfs->queue = mq;
    pfs->channel = channel;
    pfs->activebank = 0xFF;
    pfs->status = 0;

    ret = __osPfsSelectBank(pfs, 0xFE);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = __osPfsSelectBank(pfs, 0x80);
    }
    if (ret != 0) {
        return ret;
    }

    ret = __osContRamRead(mq, channel, CONT_BLOCK_DETECT, temp);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }
    if (ret != 0) {
        return ret;
    }
    if (temp[BLOCKSIZE - 1] == 0xFE) {
        return PFS_ERR_DEVICE;
    }

    ret = __osPfsSelectBank(pfs, 0x80);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }
    if (ret != 0) {
        return ret;
    }

    ret = __osContRamRead(mq, channel, CONT_BLOCK_DETECT, temp);
    if (ret == PFS_ERR_NEW_PACK) {
        ret = PFS_ERR_CONTRFAIL;
    }
    if (ret != 0) {
        return ret;
    }
    if (temp[BLOCKSIZE - 1] != 0x80) {
        return PFS_ERR_DEVICE;
    }

    if (!(pfs->status & PFS_MOTOR_INITIALIZED)) {
        ptr = (u8 *)__MotorDataBuf[channel].ramarray;
        ramreadformat.dummy = CONT_CMD_NOP;
        ramreadformat.txsize = CONT_CMD_WRITE_MEMPACK_TX;
        ramreadformat.rxsize = CONT_CMD_WRITE_MEMPACK_RX;
        ramreadformat.cmd = CONT_CMD_WRITE_MEMPACK;
        ramreadformat.hi = CONT_BLOCK_RUMBLE >> 3;
        ramreadformat.lo = __osContAddressCrc(CONT_BLOCK_RUMBLE) | (CONT_BLOCK_RUMBLE << 5);
        if (channel != 0) {
            for (i = 0; i < channel; i++) {
                *ptr++ = CONT_CMD_REQUEST_STATUS;
            }
        }
        *READFORMAT(ptr) = ramreadformat;
        ptr += sizeof(__OSContRamReadFormat);
        ptr[0] = CONT_CMD_END;
    }
    pfs->status = PFS_MOTOR_INITIALIZED;
    return 0;
}
