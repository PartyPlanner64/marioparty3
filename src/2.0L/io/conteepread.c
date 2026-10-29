#include "common.h"
#include "controller.h"

void func_8007FA88_main(u8 address);

s32 osEepromRead(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    s32 i = 0;
    u16 type;
    u8 *ptr = (u8 *)&D_800D0470_main.ramarray;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    __osSiGetAccess();
    ret = __osEepStatus(mq, &sdata);
    type = sdata.type & (CONT_EEPROM | CONT_EEP16K);
    if (ret == 0) {
        switch (type) {
            case CONT_EEPROM:
                if (address >= EEPROM_MAXBLOCKS) {
                    ret = -1;
                }
                break;
            case CONT_EEPROM | CONT_EEP16K:
                D_800D2004_main = 1;
                break;
            default:
                ret = CONT_NO_RESPONSE_ERROR;
                break;
        }
    }
    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }

    while (sdata.status & CONT_EEPROM_BUSY) {
        __osEepStatus(mq, &sdata);
    }
    func_8007FA88_main(address);
    ret = __osSiRawStartDma(OS_WRITE, &D_800D0470_main);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &D_800D0470_main);
    D_800D1F58_main = CONT_CMD_READ_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 4; i++) {
        ptr++;
    }
    eepromformat = *(__OSContEepromFormat *)ptr;
    ret = CHNL_ERR(eepromformat);
    if (ret == 0) {
        for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

void func_8007FA88_main(u8 address) {
    u8 *ptr = (u8 *)&D_800D0470_main.ramarray;
    __OSContEepromFormat eepromformat;
    s32 i;

    D_800D0470_main.pifstatus = CONT_CMD_EXE;
    eepromformat.txsize = CONT_CMD_READ_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_READ_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_READ_EEPROM;
    eepromformat.address = address;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *)ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}
