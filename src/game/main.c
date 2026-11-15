#include "ultra64.h"
#include "types.h"
#include "humath.h"
#include "game/main.h"
#include "game/graphics.h"
#include "game/profiler.h"
#include "game/vibrator.h"
#include "game/rom.h"
#include "game/data.h"
#include "ld_addrs.h"
#include "game/gameman.h"
#include "game/malloc.h"
#include "game/siman.h"
#include "game/pad.h"
#include "gcc/memory.h"
#include "PR/gs2dex.h"

void *HuGfxFBPool[3] = { (void *)0x80360000, (void *)0x80385800, (void *)0x803AB000 };
u64 *HuGfxTaskBufTbl[4] = { (u64 *)0x803F6000, (u64 *)0x803F6400, (u64 *)0x803FC400, (u64 *)0x803FC400 };

// RSP microcode text/data pairs
void *HuGfxUcodeTbl[] = {
    gspF3DEX2_fifoTextStart,     gspF3DEX2_fifoDataStart,
    gspF3DEX2_NoN_fifoTextStart, gspF3DEX2_NoN_fifoDataStart,
    gspF3DLX2_Rej_fifoTextStart, gspF3DLX2_Rej_fifoDataStart,
    gspS2DEX2_fifoTextStart,     gspS2DEX2_fifoDataStart,
    gspL3DEX2_fifoTextStart,     gspL3DEX2_fifoDataStart,
    gspF3DEX2_fifoTextStart,     gspF3DEX2_fifoDataStart,
    gspF3DEX2_NoN_fifoTextStart, gspF3DEX2_NoN_fifoDataStart,
    gspF3DLX2_Rej_fifoTextStart, gspF3DLX2_Rej_fifoDataStart,
};
s32 D_800A129C_main = 1000; // unreferenced

s32 mainFramePending = 0;
f32 mainUnkF32 = 0.0f;

extern s32 Hu3DExecCnt;
extern u8 HuGfxBufNum;
extern OSMesgQueue mainIntrQueue;
extern OSMesgQueue mainOtherQueue;
extern s32 Hu3DDrawDoneCnt;
extern u32 scRetraceCnt;


#define TV_TYPE_NTSC 1
#define TV_TYPE_PAL 0
#define INTR_MESG_BUF_SIZE 256
#define OTHER_MESG_BUF_SIZE 8

void main(void *arg) {
    s32 iVar5;
    s32 stopLooping;

    OSMesg msg;
    OSMesg intrMesgBuf[INTR_MESG_BUF_SIZE + 4];
    OSMesg otherMesgBuf[OTHER_MESG_BUF_SIZE + 4];
    OSMesg *msgTempVar;

    iVar5 = 0;
    stopLooping = FALSE;

    if (osTvType == TV_TYPE_NTSC) {
        InitScheduler(2, 1);
    } else if (osTvType != TV_TYPE_NTSC) {
        stopLooping = FALSE;
        InitScheduler(0x1E, 1);
    } else {
        goto spinloop;
    }

    HuMemHeapInitPerm((void *)0x80140000, 0x1A0000);
    HuMemHeapInitTemp((void *)0x80128000, 0x18000);

    HuGfxBufNum = 3;

    HuGfxInit(HuGfxFBPool, 3, 2, HuGfxTaskBufTbl, (s32 *)HuGfxUcodeTbl);

    if (osTvType == TV_TYPE_PAL) {
        while (TRUE) {}
    }

    HuProfInit(0, 0x20, 0xD2, 0x20, 0xD4);
    InitSI();
    InitController(4, 1);
    InitVibrator();
    ContDataInit();
    dmaInit();

    DataInit((u32)mainfs_ROM_START);

    HuPrcInit();

    msgTempVar = &intrMesgBuf[4];
    osCreateMesgQueue(&mainIntrQueue, msgTempVar, INTR_MESG_BUF_SIZE);
    AddSchedulerClient((void*)&intrMesgBuf, &mainIntrQueue, 1); //TODO: (void*) cast
    msgTempVar = &otherMesgBuf[4];
    osCreateMesgQueue(&mainOtherQueue, msgTempVar, OTHER_MESG_BUF_SIZE);
    AddSchedulerClient((void*)&otherMesgBuf, &mainOtherQueue, 2); //TODO: (void*) cast

    FlushController();
    osViSetSpecialFeatures(2);
    HuGfxModeSet(2);
    HuPrcCreate(GameManInitProc, 1, 0, 0);

    while (!stopLooping) {
        if (osRecvMesg(&mainOtherQueue, &msg, OS_MESG_NOBLOCK) != -1) {

            if (scRetraceCnt) // Mysteriously helpful, courtesy permuter.
            {}

            break;
        }

        osRecvMesg(&mainIntrQueue, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case 1: {
                s32 temp_s0;
                s16 temp_s1;

                if (scRetraceCnt - iVar5 >= 2) {
                    iVar5 = scRetraceCnt;
                    if (mainFramePending < HuGfxBufNum) {
                        HuProfFrameBegin();
                        temp_s1 = HuProfCpuBegin(0xC8, 0, 0);
                        FlushController();
                        ContDataUpdate();
                        temp_s0 = Hu3DExecCnt;
                        HuPrcCall(1);
                        if (temp_s0 != Hu3DExecCnt) {
                            mainFramePending++;
                        }
                        HuProfCpuEnd(temp_s1);
                        HuProfFrameEnd();
                    }
                }
            } break;

            case 777:
                mainFramePending--;
                Hu3DDrawDoneCnt++;
                break;

            case 2:
                stopLooping = TRUE;
                break;
        }
    }

spinloop:
    while (TRUE) {}
}

void FrameBufferClear(s16 count) {
    s16 i = 0;
    for (i = 0; i < count; i++) {
        memset(*(&HuGfxFBPool[i]), 0, 0x25800); // sizeof(gZBuffer) ?
    }
}
