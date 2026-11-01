#include "common.h"
#include "game/graphics.h"
#include "game/nnsched.h"

extern unkSchedStruct *D_800BBAC0_main;
extern OSMesgQueue D_800BBAC8_main;
extern OSMesg D_800BBAE0_main[8];
extern OSMesgQueue D_800BBB00_main;
extern OSMesg D_800BBB18_main[8];
extern OSMesgQueue D_800BBB38_main;
extern OSMesg D_800BBB50_main[8];
extern OSThread D_800BBB70_main;
extern u64 sSchedulerEventStack[0x80];
extern OSThread D_800BC120_main;
extern u64 sSchedulerAudioStack[0x80];
extern OSThread D_800BC6D0_main;
extern u64 sSchedulerGraphicsStack[0x80];
extern OSTask *D_800BCC80_main;
extern OSTask *D_800BCC84_main;
extern OSMesg D_800BCC88_main;
extern OSMesg D_800BCC90_main[8];
extern s32 D_800BCCB0_main;
extern OSMesgQueue D_800BCCB8_main;
extern OSMesg D_800BCCD0_main[1];
extern OSMesg D_800BCCD8_main[8];
extern OSMesgQueue D_800CC3A0_main;
extern OSMesgQueue D_800CC3C0_main;
extern s32 D_800CCF2C_main;
extern u32 D_800CE210_main;
extern u32 D_800CE2C8_main;
extern u32 D_800D2094_main;
extern OSViMode D_800A2E00_main[];
extern s32 _osPreNMI;

s32 __osAfterPreNMI(void);

void InitSchedulerEvent(void) {
    osCreateMesgQueue(&D_800BBAC8_main, D_800BBAE0_main, ARRAY_COUNT(D_800BBAE0_main));
    osSetEventMesg(OS_EVENT_PRENMI, &D_800BBAC8_main, (OSMesg)0x29D);
}

void InitScheduler(u8 mode, u8 retraceCount) {
    D_800CE2C8_main = retraceCount;
    D_800CCF2C_main = 0;
    D_800CE210_main = 0;
    D_800D2094_main = 0;
    D_800BBAC0_main = NULL;
    D_800BCC80_main = NULL;
    D_800BCC84_main = NULL;
    D_800BCC88_main = NULL;
    D_800BCCB0_main = 0;
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&D_800A2E00_main[mode]);
    osViSetYScale(1.0f);
    osViBlack(TRUE);
    osCreateMesgQueue(&D_800BBB00_main, D_800BBB18_main, ARRAY_COUNT(D_800BBB18_main));
    osCreateMesgQueue(&D_800BBB38_main, D_800BBB50_main, ARRAY_COUNT(D_800BBB50_main));
    osCreateMesgQueue(&D_800CC3C0_main, D_800BCC90_main, ARRAY_COUNT(D_800BCC90_main));
    osCreateMesgQueue(&D_800BCCB8_main, D_800BCCD0_main, ARRAY_COUNT(D_800BCCD0_main));
    osCreateMesgQueue(&D_800CC3A0_main, D_800BCCD8_main, ARRAY_COUNT(D_800BCCD8_main));
    osViSetEvent(&D_800BBAC8_main, (OSMesg)0x29A, retraceCount);
    osSetEventMesg(OS_EVENT_SP, &D_800BBB00_main, (OSMesg)0x29B);
    osSetEventMesg(OS_EVENT_DP, &D_800BBB38_main, (OSMesg)0x29C);
    osCreateThread(&D_800BBB70_main, 0x13, EventHandler, NULL, &sSchedulerEventStack[ARRAY_COUNT(sSchedulerEventStack)], 0x78);
    osStartThread(&D_800BBB70_main);
    while (_osPreNMI) {
    }
    osCreateThread(&D_800BC120_main, 0x12, ScExecuteAudio, NULL, &sSchedulerAudioStack[ARRAY_COUNT(sSchedulerAudioStack)], 0x6F);
    osStartThread(&D_800BC120_main);
    osCreateThread(&D_800BC6D0_main, 0x11, ScExecuteGraphics, NULL, &sSchedulerGraphicsStack[ARRAY_COUNT(sSchedulerGraphicsStack)], 0x65);
    osStartThread(&D_800BC6D0_main);
}

void AddSchedulerClient(unkSchedStruct *client, OSMesgQueue *queue, s32 eventMask) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);

    client->unk00 = D_800BBAC0_main;
    client->unk04 = queue;
    client->unk08 = eventMask;
    D_800BBAC0_main = client;
    osSetIntMask(mask);

    if ((eventMask & 2) && D_800CCF2C_main) {
        osSendMesg(queue, (OSMesg)2, OS_MESG_NOBLOCK);
    }
}

void RemoveSchedulerClient(unkSchedStruct *client) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    unkSchedStruct *prevClient = NULL;
    unkSchedStruct *currClient = D_800BBAC0_main;

    while (currClient != NULL) {
        if (currClient == client) {
            if (prevClient != NULL) {
                prevClient->unk00 = currClient->unk00;
            } else {
                D_800BBAC0_main = client->unk00;
            }
            break;
        }
        prevClient = currClient;
        currClient = currClient->unk00;
    }

    osSetIntMask(mask);
}

void EventBroadcast(s32 msg) {
    unkSchedStruct *client = D_800BBAC0_main;

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
        osRecvMesg(&D_800BBAC8_main, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case 0x29A:
                D_800D2094_main++;
                HuProfRecordAwaitRsp();
                EventBroadcast(1);
                if (D_800CCF2C_main) {
                    D_800CE210_main++;
                    if (D_800CE210_main >= 10U / D_800CE2C8_main) {
                        __osAfterPreNMI();
                    }
                }
                break;
            case 0x29D:
                osViSetYScale(1.0f);
                osViBlack(TRUE);
                EventBroadcast(2);
                PRENMICallbackVibrator();
                D_800CCF2C_main = 1;
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
        if (osRecvMesg(&D_800CC3A0_main, (OSMesg *)&audioTask, OS_MESG_NOBLOCK) != 0) {
            continue;
        }
        osWritebackDCacheAll();
        graphicsTask = D_800BCC84_main;
        graphicsState = 0;
        if (graphicsTask != NULL && D_800BCC88_main == NULL) {
            graphicsState = 2;
            osSpTaskYield();
            osRecvMesg(&D_800BBB00_main, NULL, OS_MESG_BLOCK);
            if (osSpTaskYielded(graphicsTask)) {
                graphicsState = 1;
            }
        }
        D_800BCC80_main = &audioTask->task;
        osSpTaskLoad(&audioTask->task);
        osSpTaskStartGo(&audioTask->task);
        osRecvMesg(&D_800BBB00_main, NULL, OS_MESG_BLOCK);
        D_800BCC80_main = NULL;
        if (D_800BCCB0_main) {
            osSendMesg(&D_800BCCB8_main, NULL, OS_MESG_BLOCK);
        }
        switch (graphicsState) {
            case 1:
                osSpTaskLoad(graphicsTask);
                osSpTaskStartGo(graphicsTask);
                break;
            case 2:
                osSendMesg(&D_800BBB00_main, (OSMesg)0x29B, OS_MESG_BLOCK);
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
        osRecvMesg(&D_800CC3C0_main, (OSMesg *)&graphicsTask, OS_MESG_BLOCK);
        osWritebackDCacheAll();
        mask = osSetIntMask(OS_IM_NONE);
        if (D_800BCC80_main != NULL) {
            D_800BCCB0_main = 1;
            osSetIntMask(mask);
            osRecvMesg(&D_800BCCB8_main, NULL, OS_MESG_BLOCK);
            mask = osSetIntMask(OS_IM_NONE);
            D_800BCCB0_main = 0;
        }
        D_800BCC84_main = &graphicsTask->task;
        osSpTaskLoad(&graphicsTask->task);
        osSpTaskStartGo(&graphicsTask->task);
        osSetIntMask(mask);
        rspSample = func_8004D710_main(0, 0, 255);
        rdpSample = func_8004D710_main(0, 255, 0);
        osRecvMesg(&D_800BBB00_main, &D_800BCC88_main, OS_MESG_BLOCK);
        func_8004D788_main(rspSample);
        mask = osSetIntMask(OS_IM_NONE);
        D_800BCC84_main = NULL;
        D_800BCC88_main = NULL;
        osSetIntMask(mask);
        osRecvMesg(&D_800BBB38_main, NULL, OS_MESG_BLOCK);
        func_8004D788_main(rdpSample);
        osSendMesg(graphicsTask->completionQueue, graphicsTask->completionMsg, OS_MESG_BLOCK);
        if ((s32)graphicsTask->completionMsg & 1) {
            func_8004D888_main();
        }
    }
}
