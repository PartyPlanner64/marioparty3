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

void *D_800A1240_main[3] = { (void *)0x80360000, (void *)0x80385800, (void *)0x803AB000 };
u64 *D_800A124C_main[4] = { (u64 *)0x803F6000, (u64 *)0x803F6400, (u64 *)0x803FC400, (u64 *)0x803FC400 };

// RSP microcode text/data pairs
void *D_800A125C_main[] = {
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

s32 D_800A12A0_main = 0;
f32 D_800A12A4_main = 0.0f;

extern s32 D_800A08B0_main;
extern u8 D_800CCF52_main;
extern OSMesgQueue D_800CCF38_main;
extern OSMesgQueue D_800CCF60_main;
extern s32 D_800D1F70_main;
extern u32 D_800D2094_main;


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

    D_800CCF52_main = 3;

    func_8000EA10_main(D_800A1240_main, 3, 2, D_800A124C_main, (s32 *)D_800A125C_main);

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
    osCreateMesgQueue(&D_800CCF38_main, msgTempVar, INTR_MESG_BUF_SIZE);
    AddSchedulerClient((void*)&intrMesgBuf, &D_800CCF38_main, 1); //TODO: (void*) cast
    msgTempVar = &otherMesgBuf[4];
    osCreateMesgQueue(&D_800CCF60_main, msgTempVar, OTHER_MESG_BUF_SIZE);
    AddSchedulerClient((void*)&otherMesgBuf, &D_800CCF60_main, 2); //TODO: (void*) cast

    FlushController();
    osViSetSpecialFeatures(2);
    func_8000F094_main(2);
    HuPrcCreate(func_8000E3C0_main, 1, 0, 0);

    while (!stopLooping) {
        if (osRecvMesg(&D_800CCF60_main, &msg, OS_MESG_NOBLOCK) != -1) {

            if (D_800D2094_main) // Mysteriously helpful, courtesy permuter.
            {}

            break;
        }

        osRecvMesg(&D_800CCF38_main, &msg, OS_MESG_BLOCK);
        switch ((s32)msg) {
            case 1: {
                s32 temp_s0;
                s16 temp_s1;

                if (D_800D2094_main - iVar5 >= 2) {
                    iVar5 = D_800D2094_main;
                    if (D_800A12A0_main < D_800CCF52_main) {
                        func_8004D7D8_main();
                        temp_s1 = func_8004D6AC_main(0xC8, 0, 0);
                        FlushController();
                        ContDataUpdate();
                        temp_s0 = D_800A08B0_main;
                        HuPrcCall(1);
                        if (temp_s0 != D_800A08B0_main) {
                            D_800A12A0_main++;
                        }
                        func_8004D6E8_main(temp_s1);
                        func_8004D814_main();
                    }
                }
            } break;

            case 777:
                D_800A12A0_main--;
                D_800D1F70_main++;
                break;

            case 2:
                stopLooping = TRUE;
                break;
        }
    }

spinloop:
    while (TRUE) {}
}

void func_800357AC_main(s16 count) {
    s16 i = 0;
    for (i = 0; i < count; i++) {
        memset(*(&D_800A1240_main[i]), 0, 0x25800); // sizeof(gZBuffer) ?
    }
}
