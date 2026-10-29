#include "common.h"
#include "controller.h"

void __osPackReadData(void);

s32 osContStartReadData(OSMesgQueue *mq) {
    s32 ret = 0;

    __osSiGetAccess();
    if (D_800D1F58_main != CONT_CMD_READ_BUTTON) {
        __osPackReadData();
        ret = __osSiRawStartDma(OS_WRITE, &D_800CC3F0_main);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    ret = __osSiRawStartDma(OS_READ, &D_800CC3F0_main);
    D_800D1F58_main = CONT_CMD_READ_BUTTON;
    __osSiRelAccess();
    return ret;
}

void osContGetReadData(OSContPad *data) {
    u8 *ptr = (u8 *)&D_800CC3F0_main.ramarray;
    __OSContReadFormat readformat;
    s32 i;

    for (i = 0; i < D_800CE204; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}

void __osPackReadData(void) {
    u8 *ptr = (u8 *)&D_800CC3F0_main.ramarray;
    __OSContReadFormat readformat;
    s32 i;

    for (i = 0; i < ARRLEN(D_800CC3F0_main.ramarray); i++) {
        D_800CC3F0_main.ramarray[i] = 0;
    }
    D_800CC3F0_main.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = -1;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < D_800CE204; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}
