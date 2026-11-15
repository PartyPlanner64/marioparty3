#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "variables.h"
#include "game/siman.h"
#include "game/pad.h"

static OSContPad padReadBuf[8 * MAXCONTROLLERS];
static unkMesg padReadMesg[8];
static s16 padReadCnt;
static s16 padReadIdx;
static s16 padWriteIdx;
static s8 padRepCnt[MAXCONTROLLERS];
static u8 padConnectF[MAXCONTROLLERS];
static s8 padStkXLimit;
static s8 padStkYLimit;
static functionListEntry padSIClient;
static s16 padAutoReadF;
static OSMesgQueue padMesgQueue;
static OSMesg padMesgBuf;

s32 _InitController(u16 *channel) {
    OSContStatus contStat[MAXCONTROLLERS];
    u8 pattern;
    s16 i;

    osContInit(&siMesgQueue, &pattern, contStat);

    padReadCnt = padReadIdx = padWriteIdx = 0;
    gNumOfControllers = 0;

    for (i = 0; i < MAXCONTROLLERS; ++i) {
        if (((pattern >> i) & 1) && ((contStat[i].errno & CONT_NO_RESPONSE_ERROR) == 0)) {
            if (++gNumOfControllers == *channel) {
                break;
            }
        }

        HuPadBtn[i] =
            HuPadBtnDown[i] =
                HuPadBtnOld[i] =
                    HuPadBtnRep[i] =
                        0;
        HuPadStkXSum[i] =
            HuPadStkYSum[i] =
                0;
        HuPadStkY[i] = 0;
        HuPadStkX[i] = 0;
        padConnectF[i] = 0;
    }

    osContSetCh(*channel);
    return 0;
}

s16 InitController(s16 ch, s32 arg1) {
    unkMesg siMesg;
    RequestSIFunction(&siMesg, (void *)&_InitController, &ch, 1);

    padAutoReadF = 0;

    if (arg1 & 1) {
        SetAutoReadController();
    }

    SetStickValueLimit(0x46, 0x46);
    osCreateMesgQueue(&padMesgQueue, &padMesgBuf, 1);
    osSendMesg(&padMesgQueue, 0, 1);

    return gNumOfControllers;
}

s32 _ReadController(s32 arg0) {
    osRecvMesg(&padMesgQueue, 0, 1);

    if (padReadCnt < 8) {
        osSendMesg(&padMesgQueue, 0, 1);
        osContStartReadData(&siMesgQueue);
        osRecvMesg(&siMesgQueue, 0, 1);
        osContGetReadData(&padReadBuf[padWriteIdx * 4]); //?
        osRecvMesg(&padMesgQueue, 0, 1);

        ++padReadCnt;

        if (++padWriteIdx >= 8) {
            padWriteIdx = 0;
        }
    }

    osSendMesg(&padMesgQueue, 0, 1);
    return 0;
}

void ReadController(void) {
    osRecvMesg(&padMesgQueue, NULL, 1);
    if (padReadCnt < 8) {
        RequestSIFunction(&padReadMesg[padWriteIdx], &_ReadController, 0, 0);
    }
    osSendMesg(&padMesgQueue, NULL, 1);
}

void SetStickValueLimit(s8 arg0, s8 arg1) {
    padStkXLimit = arg0;
    padStkYLimit = arg1;
}

#define MAX_CONTROLLERS 4

s16 UpdateController(void) {
    s16 i;
    s16 temp_s0;
    u16 temp_v0_3;
    OSContPad *pads;
    u8 temp;

    osRecvMesg(&padMesgQueue, 0, 1);
    temp_s0 = padReadCnt;

    if (temp_s0 != 0) {
        --padReadCnt;

        pads = &padReadBuf[padReadIdx * 4];
        ++padReadIdx;
        if (padReadIdx >= 8) {
            padReadIdx = 0;
        }

        for (i = 0; i < MAX_CONTROLLERS; i++) {
            padConnectF[i] = pads[i].errno != 8;
            temp_v0_3 =
                HuPadBtn[i] = pads[i].button;
            HuPadStkX[i] = pads[i].stick_x;
            HuPadStkXSum[i] = HuPadStkX[i];
            HuPadStkYSum[i] =
                HuPadStkY[i] = pads[i].stick_y;
            HuPadBtnDown[i] = temp_v0_3 & (temp_v0_3 ^ HuPadBtnOld[i]);
            if (HuPadBtnOld[i] == temp_v0_3) {
                if (!(--padRepCnt[i] & 0xFF)) {
                    HuPadBtnRep[i] = temp_v0_3;
                    padRepCnt[i] = 0xA;
                } else {
                    HuPadBtnRep[i] = 0;
                }
            } else {
                HuPadBtnRep[i] = HuPadBtnDown[i];
                padRepCnt[i] = 0x1E;
            }

            temp = HuPadStkX[i] + 9;

            if (temp < 0x13) {
                HuPadStkX[i] = 0;
            } else if (HuPadStkX[i] > padStkXLimit) {
                HuPadStkX[i] = padStkXLimit;
            } else if (HuPadStkX[i] < -padStkXLimit) {
                HuPadStkX[i] = -padStkXLimit;
            }

            temp = HuPadStkY[i] + 9;

            if (temp < 0x13) {
                HuPadStkY[i] = 0;
            } else if (HuPadStkY[i] > padStkYLimit) {
                HuPadStkY[i] = padStkYLimit;
            } else {
                if (HuPadStkY[i] < -padStkYLimit) {
                    HuPadStkY[i] = -padStkYLimit;
                }
            }
            HuPadBtnOld[i] = temp_v0_3;
        }
    }
    osSendMesg(&padMesgQueue, 0, 1);
    return temp_s0;
}

s16 FlushController(void) {
    u16 held[MAXCONTROLLERS];
    u16 pressed[MAXCONTROLLERS];
    s16 count = 0;
    s16 i;

    if (UpdateController() > 0) {
        for (i = 0; i < MAXCONTROLLERS; i++) {
            held[i] = HuPadBtnDown[i];
            pressed[i] = HuPadBtnRep[i];
            HuPadStkXSum[i] = HuPadStkX[i];
            HuPadStkYSum[i] = HuPadStkY[i];
            HuPadStkXHis[i][count] = HuPadStkX[i];
            HuPadStkYHis[i][count] = HuPadStkY[i];
        }
        count++;
        while (UpdateController() != 0) {
            for (i = 0; i < MAXCONTROLLERS; i++) {
                held[i] |= HuPadBtnDown[i];
                pressed[i] |= HuPadBtnRep[i];
                HuPadStkXSum[i] += HuPadStkX[i];
                HuPadStkYSum[i] += HuPadStkY[i];
                HuPadStkXHis[i][count] = HuPadStkX[i];
                HuPadStkYHis[i][count] = HuPadStkY[i];
            }
            count++;
        }
        for (i = 0; i < MAXCONTROLLERS; i++) {
            HuPadBtnDown[i] = held[i];
            HuPadBtnRep[i] = pressed[i];
        }
    }
    HuPadReadNum = count;
    return count;
}

void _AutoReadController(void) {
    _ReadController(0);
}

void SetAutoReadController(void) {
    if (padAutoReadF != 0) {
        ResetAutoReadController();
    }
    AddSIClient(&padSIClient, 0, &_AutoReadController);
    padAutoReadF = 1;
}

void ResetAutoReadController(void) {
    if (padAutoReadF != 0) {
        RemoveSIClient(&padSIClient);
    }
    padAutoReadF = 0;
}

s32 CheckControllerRead(s16 padNum) {
    return padConnectF[padNum];
}
