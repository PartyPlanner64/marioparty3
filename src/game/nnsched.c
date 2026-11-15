#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "macros.h"
#include "game/profiler.h"
#include "game/vibrator.h"
#include "game/graphics.h"
#include "game/nnsched.h"

static unkSchedStruct *scClientList;
static OSMesgQueue scEventQueue;
static OSMesg scEventMesgBuf[8];
static OSMesgQueue scRspQueue;
static OSMesg scRspMesgBuf[8];
static OSMesgQueue scRdpQueue;
static OSMesg scRdpMesgBuf[8];
static OSThread scEventThread;
static u64 sSchedulerEventStack[0x80];
static OSThread scAudioThread;
static u64 sSchedulerAudioStack[0x80];
static OSThread scGraphicsThread;
static u64 sSchedulerGraphicsStack[0x80];
static OSTask *scCurAudioTask;
static OSTask *scCurGraphicsTask;
static OSMesg scYieldGraphicsTask;
static OSMesg scGraphicsTaskMesgBuf[8];
static s32 scGraphicsWaitF;
static OSMesgQueue scAudioDoneQueue;
static OSMesg scAudioDoneMesgBuf[1];
static OSMesg scAudioTaskMesgBuf[8];
extern OSMesgQueue scAudioTaskQueue;
extern OSMesgQueue scGraphicsTaskQueue;
extern s32 scPreNMIF;
extern u32 scPreNMICnt;
extern u32 scRetraceRate;
extern u32 scRetraceCnt;
extern s32 _osPreNMI;

s32 __osAfterPreNMI(void);

void InitSchedulerEvent(void) {
    osCreateMesgQueue(&scEventQueue, scEventMesgBuf, ARRAY_COUNT(scEventMesgBuf));
    osSetEventMesg(OS_EVENT_PRENMI, &scEventQueue, (OSMesg)0x29D);
}

void InitScheduler(u8 mode, u8 retraceCount) {
    scRetraceRate = retraceCount;
    scPreNMIF = 0;
    scPreNMICnt = 0;
    scRetraceCnt = 0;
    scClientList = NULL;
    scCurAudioTask = NULL;
    scCurGraphicsTask = NULL;
    scYieldGraphicsTask = NULL;
    scGraphicsWaitF = 0;
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    osViSetYScale(1.0f);
    osViBlack(TRUE);
    osCreateMesgQueue(&scRspQueue, scRspMesgBuf, ARRAY_COUNT(scRspMesgBuf));
    osCreateMesgQueue(&scRdpQueue, scRdpMesgBuf, ARRAY_COUNT(scRdpMesgBuf));
    osCreateMesgQueue(&scGraphicsTaskQueue, scGraphicsTaskMesgBuf, ARRAY_COUNT(scGraphicsTaskMesgBuf));
    osCreateMesgQueue(&scAudioDoneQueue, scAudioDoneMesgBuf, ARRAY_COUNT(scAudioDoneMesgBuf));
    osCreateMesgQueue(&scAudioTaskQueue, scAudioTaskMesgBuf, ARRAY_COUNT(scAudioTaskMesgBuf));
    osViSetEvent(&scEventQueue, (OSMesg)0x29A, retraceCount);
    osSetEventMesg(OS_EVENT_SP, &scRspQueue, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &scRdpQueue, (OSMesg)0x29C);
    osCreateThread(&scEventThread, 0x13, EventHandler, NULL, &sSchedulerEventStack[ARRAY_COUNT(sSchedulerEventStack)], 0x78);
    osStartThread(&scEventThread);
    while (_osPreNMI) {
    }
    osCreateThread(&scAudioThread, 0x12, ScExecuteAudio, NULL, &sSchedulerAudioStack[ARRAY_COUNT(sSchedulerAudioStack)], 0x6F);
    osStartThread(&scAudioThread);
    osCreateThread(&scGraphicsThread, 0x11, ScExecuteGraphics, NULL, &sSchedulerGraphicsStack[ARRAY_COUNT(sSchedulerGraphicsStack)], 0x65);
    osStartThread(&scGraphicsThread);
}

void AddSchedulerClient(unkSchedStruct *client, OSMesgQueue *queue, s32 eventMask) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->unk00 = scClientList;
    client->unk04 = queue;
    client->unk08 = eventMask;
    scClientList = client;
    osSetIntMask(mask);

    if ((eventMask & 2) && scPreNMIF) {
        osSendMesg(queue, (OSMesg)2, OS_MESG_NOBLOCK);
    }
}

void RemoveSchedulerClient(unkSchedStruct *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    unkSchedStruct *prevClient = NULL;
    unkSchedStruct *currClient = scClientList;

    while (currClient != NULL) {
        if (currClient == client) {
            if (prevClient != NULL) {
                prevClient->unk00 = currClient->unk00;
            } else {
                scClientList = client->unk00;
            }
            break;
        }
        prevClient = currClient;
        currClient = currClient->unk00;
    }

    osSetIntMask(mask);
}

void EventBroadcast(s32 msg) {
    unkSchedStruct *client = scClientList;

    while (client != NULL) {
        if (msg & client->unk08) {
            osSendMesg(client->unk04, (OSMesg)msg, OS_MESG_NOBLOCK);
        }
        client = client->unk00;
    }
}

void EventHandler(void *arg) {
    OSMesg msg;

    while (TRUE) {
        osRecvMesg(&scEventQueue, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case 0x29A:
                scRetraceCnt++;
                HuProfRecordAwaitRsp();
                EventBroadcast(1);
                if (scPreNMIF) {
                    scPreNMICnt++;
                    if (scPreNMICnt >= 10U / scRetraceRate) {
                        __osAfterPreNMI();
                    }
                }
                break;
            case 0x29D:
                osViSetYScale(1.0f);
                osViBlack(TRUE);
                EventBroadcast(2);
                PRENMICallbackVibrator();
                scPreNMIF = 1;
                break;
        }
    }
}

void ScExecuteAudio(void *arg) {
    unkSchedStruct client;
    OSMesgQueue queue;
    OSMesg msg;
    swapChainTaskQueue *audioTask = NULL;
    OSTask *graphicsTask;
    s32 graphicsState;

    osCreateMesgQueue(&queue, &msg, 1);
    AddSchedulerClient(&client, &queue, 1);
    while (TRUE) {
        osRecvMesg(&queue, NULL, OS_MESG_BLOCK);
        if (osRecvMesg(&scAudioTaskQueue, (OSMesg *)&audioTask, OS_MESG_NOBLOCK) != 0) {
            continue;
        }
        osWritebackDCacheAll();
        graphicsTask = scCurGraphicsTask;
        graphicsState = 0;
        if (graphicsTask != NULL && scYieldGraphicsTask == NULL) {
            graphicsState = 2;
            osSpTaskYield();
            osRecvMesg(&scRspQueue, NULL, OS_MESG_BLOCK);
            if (osSpTaskYielded(graphicsTask)) {
                graphicsState = 1;
            }
        }
        scCurAudioTask = &audioTask->task;
        osSpTaskLoad(&audioTask->task);
        osSpTaskStartGo(&audioTask->task);
        osRecvMesg(&scRspQueue, NULL, OS_MESG_BLOCK);
        scCurAudioTask = NULL;
        if (scGraphicsWaitF) {
            osSendMesg(&scAudioDoneQueue, NULL, OS_MESG_BLOCK);
        }
        switch (graphicsState) {
            case 1:
                osSpTaskLoad(graphicsTask);
                osSpTaskStartGo(graphicsTask);
                break;
            case 2:
                osSendMesg(&scRspQueue, (OSMesg)0x29B, OS_MESG_BLOCK);
                break;
        }
        osSendMesg(audioTask->completionQueue, audioTask->completionMsg, OS_MESG_BLOCK);
    }
}

void ScExecuteGraphics(void *arg) {
    swapChainTaskQueue *graphicsTask = NULL;
    OSIntMask mask;
    s16 rspSample;
    s16 rdpSample;

    while (TRUE) {
        osRecvMesg(&scGraphicsTaskQueue, (OSMesg *)&graphicsTask, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        mask = osSetIntMask(OS_IM_NONE);
        if (scCurAudioTask != NULL) {
            scGraphicsWaitF = 1;
            osSetIntMask(mask);
            osRecvMesg(&scAudioDoneQueue, NULL, OS_MESG_BLOCK);
            mask = osSetIntMask(OS_IM_NONE);
            scGraphicsWaitF = 0;
        }
        scCurGraphicsTask = &graphicsTask->task;
        osSpTaskLoad(&graphicsTask->task);
        osSpTaskStartGo(&graphicsTask->task);
        osSetIntMask(mask);
        rspSample = HuProfRspBegin(0, 0, 255);
        rdpSample = HuProfRspBegin(0, 255, 0);
        osRecvMesg(&scRspQueue, &scYieldGraphicsTask, OS_MESG_BLOCK);
        HuProfRspEnd(rspSample);
        mask = osSetIntMask(OS_IM_NONE);
        scCurGraphicsTask = NULL;
        scYieldGraphicsTask = NULL;
        osSetIntMask(mask);
        osRecvMesg(&scRdpQueue, NULL, OS_MESG_BLOCK);
        HuProfRspEnd(rdpSample);
        osSendMesg(graphicsTask->completionQueue, graphicsTask->completionMsg, OS_MESG_BLOCK);
        if ((s32)graphicsTask->completionMsg & 1) {
            HuProfDrawTask();
        }
    }
}
