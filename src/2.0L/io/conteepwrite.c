#include "common.h"
#include "controller.h"

void __osPackEepWriteData(u8 address, u8 *buffer);

s32 osEepromWrite(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    u16 type;
    u8 *ptr = (u8 *)&D_800D0470_main.ramarray;
    __OSContEepromFormat eepromformat;
    OSContStatus sdata;
    u8 temp[EEPROM_BLOCK_SIZE];

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
                if (D_800D2004_main != 0) {
                    D_800D2004_main = 0;
                    __osSiRelAccess();
                    osEepromRead(mq, address ^ 1, temp);
                    __osSiGetAccess();
                }
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
    __osPackEepWriteData(address, buffer);
    ret = __osSiRawStartDma(OS_WRITE, &D_800D0470_main);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &D_800D0470_main);
    D_800D1F58_main = CONT_CMD_WRITE_EEPROM;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    ptr += 4;
    eepromformat = *(__OSContEepromFormat *)ptr;
    ret = CHNL_ERR(eepromformat);
    __osSiRelAccess();
    return ret;
}

void __osPackEepWriteData(u8 address, u8 *buffer) {
    u8 *ptr = (u8 *)&D_800D0470_main.ramarray;
    __OSContEepromFormat eepromformat;
    s32 i;

    D_800D0470_main.pifstatus = CONT_CMD_EXE;
    eepromformat.txsize = CONT_CMD_WRITE_EEPROM_TX;
    eepromformat.rxsize = CONT_CMD_WRITE_EEPROM_RX;
    eepromformat.cmd = CONT_CMD_WRITE_EEPROM;
    eepromformat.address = address;
    for (i = 0; i < EEPROM_BLOCK_SIZE; i++) {
        eepromformat.data[i] = *buffer++;
    }
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *)ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    ptr[0] = CONT_CMD_END;
}

s32 __osEepStatus(OSMesgQueue *mq, OSContStatus *data) {
    s32 ret = 0;
    s32 i;
    u8 *ptr = (u8 *)D_800D0470_main.ramarray;
    __OSContRequesFormat requestformat;

    for (i = 0; i < ARRLEN(D_800D0470_main.ramarray) + 1; i++) {
        D_800D0470_main.ramarray[i] = 0;
    }
    D_800D0470_main.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)D_800D0470_main.ramarray;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = CONT_CMD_REQUEST_STATUS;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    *(__OSContRequesFormat *)ptr = requestformat;
    ptr += sizeof(__OSContRequesFormat);
    *ptr = CONT_CMD_END;

    ret = __osSiRawStartDma(OS_WRITE, &D_800D0470_main);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    D_800D1F58_main = CONT_CMD_END;
    ret = __osSiRawStartDma(OS_READ, &D_800D0470_main);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    if (ret != 0) {
        return ret;
    }

    ptr = (u8 *)&D_800D0470_main;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat = *(__OSContRequesFormat *)ptr;
    data->errno = CHNL_ERR(requestformat);
    data->type = (requestformat.typel << 8) | requestformat.typeh;
    data->status = requestformat.status;
    if (data->errno != 0) {
        return data->errno;
    }
    return 0;
}
