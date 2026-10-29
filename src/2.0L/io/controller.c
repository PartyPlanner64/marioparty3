#include "common.h"
#include "controller.h"

#define HALF_A_SECOND OS_USEC_TO_CYCLES(500000)

extern u32 D_800A2D50_main; /* __osContinitialized */

s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (D_800A2D50_main) {
        return ret;
    }
    D_800A2D50_main = TRUE;
    t = osGetTime();
    if (t < HALF_A_SECOND) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, HALF_A_SECOND - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }
    D_800CE204 = MAXCONTROLLERS;
    __osPackRequestData(CONT_CMD_REQUEST_STATUS);
    ret = __osSiRawStartDma(OS_WRITE, &D_800CC3F0_main);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    ret = __osSiRawStartDma(OS_READ, &D_800CC3F0_main);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, data);
    D_800D1F58_main = CONT_CMD_REQUEST_STATUS;
    func_8007C720_main();
    osCreateMesgQueue(&D_800D6A28_main, &D_800D1F6C_main, 1);
    return ret;
}

void __osContGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)&D_800CC3F0_main;
    for (i = 0; i < D_800CE204; i++, ptr += sizeof(__OSContRequesFormat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;

    for (i = 0; i < ARRLEN(D_800CC3F0_main.ramarray); i++) {
        D_800CC3F0_main.ramarray[i] = 0;
    }
    D_800CC3F0_main.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)&D_800CC3F0_main.ramarray;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    for (i = 0; i < D_800CE204; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(__OSContRequesFormat);
    }
    ptr[0] = CONT_CMD_END;
}
